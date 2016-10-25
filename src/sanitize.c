
#include <grp.h>
#include <paths.h>
#include <string.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/types.h>
#include <unistd.h>

#include "secureproc/sanitize.h"
#include "secureproc/logger.h"


/*
 *  environ -  This is an external variable to the process's inherited
 *  from the parent process.
 */
extern char ** environ;

/*
 *  secureproc_restricted_environment - Default environment variables and
 *      values.
 */
static const char * secureproc_restricted_environment[] = {
    "IFS= \t\n",
    "PATH=" _PATH_STDPATH,
    NULL
};

/*
 *  secureproc_preserve_environment - Default environment variables that get
 *      inherited.
 */
static const char * secureproc_preserve_environment[] = {
    "TZ",
    NULL
};

void secureproc_sanitize_environment(int preservec,
                                     char const * const * preservev)
{
    int         i;              /* for loop index */
    char      **new_environ,    /* Holds new environ during creation */
               *new_var_ptr;    /* Holds a variable during creation */
    const char *var_ptr,        /* Points to static variables */
               *var_value,      /* Holds a variable value during copying */
               *var_name;       /* Holds a variable name during copying */
    size_t      new_environ_count = 1, /* Number of variables in environ
                                       +1 for list terminator */
                new_var_idx = 0,
                new_size = 0,   /* Total size of new environ in bytes */
                name_len,       /* String lengths of variable name */
                value_len;      /* String lengths of variable name */

    /*
     *  Determine the total size of the new environ.
     *      Note: Will be one block for the entire environ.
     */

     /* Default sanitized variables */
    for (i = 0; (var_ptr = secureproc_restricted_environment[i]) != NULL; ++i)
    {
        new_size += strlen(var_ptr) + 1;   /* +1 for NULL terminator */
        ++new_environ_count;
    }

    /* Default preserved variables */
    for (i = 0; (var_name = secureproc_preserve_environment[i]) != NULL; ++i)
    {
        if ((var_value = getenv(var_name)) == NULL)
            continue; /* Preserved enviromental variable does not exist. */

        /* +2 for '=' and NULL terminator */
        new_size += strlen(var_name) + strlen(var_value) + 2;
        ++new_environ_count;
    }

    /* Programmer specified preserved variables */
    if (preservec && preservev)
    {
        for (i = 0; i < preservec && ((var_name = preservev[i]) != NULL); ++i)
        {
            if ((var_value = getenv(var_name)) == NULL)
                continue; /* Preserved enviromental variable does not exist. */

            /* +2 for '=' and NULL terminator */
            new_size = strlen(var_name) + strlen(var_value) + 2;
            ++new_environ_count;
        }
    }

    /* Additional space for variable list */
    new_size += (new_environ_count * sizeof(char *));

    /*
     *  The new environ is one large block.  The first section of bytes are
     *  for pointers to positions further in the block representing the
     *  begining of the variable strings.  The pointer list is NULL terminated.
     *  Each section after that are NULL terminated strings.
     */
    new_environ = (char **) malloc(new_size);

    /* Check for allocation errors */
    if (new_environ == NULL)
    {
        SECERR("Failed to allocate %ld bytes of memory.\n", new_size);
        abort(); /* Program exits directly from this point in the process */
    }

    /* Set NULL terminator for string array. */
    new_environ[new_environ_count - 1] = NULL;

    /* Get the position of the first string in memory block */
    new_var_ptr = (char *) new_environ + (new_environ_count * sizeof(char *));

    /*
     *  Copy all the appropriate variables to the new environ variable.
     */

    /* Copy default sanitized variables to new environ */
    for (i = 0; (var_name = secureproc_restricted_environment[i]) != NULL; ++i)
    {
        new_environ[new_var_idx++] = new_var_ptr;

        name_len = strlen(var_name);
        /* +1 for string NULL terminator */
        memcpy(new_var_ptr, var_name, name_len + 1);

        new_var_ptr += name_len + 1;
    }

    /* Copy default preserved variables to new environ */
    for (i = 0; (var_name = secureproc_preserve_environment[i]) != NULL; ++i)
    {
        if ((var_value = getenv(var_name)) == NULL)
            continue;  /* Same variables will fail as before */

        new_environ[new_var_idx++] = new_var_ptr;

        name_len = strlen(var_name);
        value_len = strlen(var_value);

        /* +1 for string NULL terminator */
        /* +2 for '=' and string NULL terminator */
        memcpy(new_var_ptr, var_name, name_len);
        *(new_var_ptr + name_len + 1) = '=';
        memcpy(new_var_ptr + name_len + 2, var_value, value_len + 1);

        new_var_ptr += name_len + value_len + 2;
    }

    /* Copy user specified preserve variables to new environ */
    if (preservec && preservev)
    {
        for (i = 0; i < preservec && ((var_name = preservev[i]) != NULL); ++i)
        {
            if ((var_value = getenv(var_name)) == NULL)
                continue; /* Same variables will fail as before */

            new_environ[new_var_idx++] = new_var_ptr;

            name_len = strlen(var_name);
            value_len = strlen(var_value);

            /* +1 for string NULL terminator */
            memcpy(new_var_ptr, var_name, name_len);
            *(new_var_ptr + name_len + 1) = '=';
            /* +2 for '=' and string NULL terminator */
            memcpy(new_var_ptr + name_len + 2, var_value, value_len + 1);

            new_var_ptr += name_len + value_len + 2;
        }
    }

    /* Assign the new environ variable to the process's environment */
    environ = new_environ;
} /* secureproc_sanitize_environment() */

/*
 *  orig_ngroups - number of original group IDs
 *  orig_gid     - original effective GID
 *  orig_uid     - original effective UID
 *  orig_groups  - list of original group IDs
 */
static int      orig_ngroups = -1;
static gid_t    orig_gid = -1;
static uid_t    orig_uid = -1;
static gid_t    orig_groups[NGROUPS_MAX];

void secureproc_drop_privileges(int permanent)
{
    gid_t new_gid = getgid(), old_gid = getegid();
    uid_t new_uid = getuid(), old_uid = geteuid();

    if (!permanent)
    {
        /*
         * Save information about the pribileges that are being dropped so that
         * they can be restored later.
         */
        orig_gid = old_gid;
        orig_uid = old_uid;
        orig_ngroups = getgroups(NGROUPS_MAX, orig_groups);
    }

    /*
     *  If root privileges are to be dropped, be sure to pare down the ancillary
     *  groups for the process before doing anythin else because the setgroups()
     *  system call requires root privileges. Drop ancillary groups regardless
     *  of whether privileges are being dropped temporarily or permanently.
     */
    if (old_uid == 0) /* if root */
    {
        setgroups(1, &new_gid);
    }

    if (old_gid != new_gid)
    {
#ifdef linux
        if (permanent && setregid(new_gid, new_gid) < 0)
        {
            SECERR("Failed to permanently set Real GID and Effective GID.\n");
            abort();
        }
        /* The -1 will keep the Saved GID to the previous value. */
        else if (!permanent && setregid(-1, new_gid) < 0)
        {
            SECERR("Failed to temporarily set Effective GID.\n");
            abort();
        }
#else
        setegid(new_gid);
        if (permanent && setgid(new_gid) < 0)
        {
            SECERR("Failed to permanently set Real GID.\n");
            abort();
        }
#endif
    }

    if (old_uid != new_uid)
    {
#ifdef linux
        if (permanent && setreuid(new_uid, new_uid) < 0)
        {
            SECERR("Failed to permanently set Real UID and Effective UID.\n");
            abort();
        }
        /* The -1 will keep the Saved UID to the previous value. */
        else if (!permanent && setreuid(-1, new_uid))
        {
            SECERR("Failed to temporarily set Effective UID.\n");
            abort();
        }
#else
        seteuid(new_uid);
        if (permanent && setuid(new_uid) < 0)
        {
            SECERR("Failed to permanently set Real UID.\n");
            abort();
        }
#endif
    }

    /* Verify that the changes were successful */

    if (permanent)
    {
        if (new_gid != old_gid
            && (setegid(old_gid) != -1 || getegid() != new_gid))
        {
            SECERR("GID verification failed.\n");
            abort();
        }
        if (new_uid != old_uid
            && (seteuid(old_uid) != -1 || geteuid() != new_uid))
        {
            SECERR("UID verification failed.\n");
            abort();
        }
    }
    else /* if not permanent*/
    {
        if (new_gid != old_gid && getegid() != new_gid)
        {
            SECERR("GID verification failed.\n");
            abort();
        }
        if (new_uid != old_uid && geteuid() != new_uid)
        {
            SECERR("UID verification failed.\n");
            abort();
        }
    }
} /* secureproc_drop_privileges() */

void secureproc_restore_privileges(void)
{
    if (geteuid() != orig_uid)
    {
        if (seteuid(orig_uid) < 0 || geteuid() != orig_uid)
        {
            SECERR("Failed to restore UID.\n");
            abort();
        }
    }

    if (getegid() != orig_gid)
    {
        if (setegid(orig_gid) < 0 || getegid() != orig_uid)
        {
            SECERR("Failed to restore GID.\n");
            abort();
        }
    }

    /*
     *  If restoring to root, it is possible to restore the original
     *  group permissions that were present before.
     */
    if (orig_uid == 0) /* if root */
    {
        setgroups(orig_ngroups, orig_groups);
    }
} /* secureproc_restore_privileges */
