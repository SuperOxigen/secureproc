#ifndef _SECURE_PROC_SANITIZE_H_
#define _SECURE_PROC_SANITIZE_H_

/*
 *  Secure Proc - Sanitize
 *
 *  Description:
 *      A set of one-time functions that help initialize the programs
 *      environment for safe usage.
 *
 *  Author(s):
 *      Alex Dale (@superoxigen)
 */

/*
 *  Function: secureproc_sanitize_environment
 *      Sanitizes the process's environmental variables by removing
 *      unnecessary variables, and setting important variables to
 *      their system default values.
 *
 *  Reset Variables:
 *    - PATH variable will be set to the system's default value as
 *      specified by _PATH_STDPATH
 *    - IFS variable (represents shell white space) will be set to the
 *      charcters [:space:], [:tab:], and [:line feed:].
 *  Default Preserve:
 *    - TZ (timezone) variable will be preserved from the previous
 *      environment.
 *  Note: preservec of 0 specifies no additional variables should be
 *      preserved.
 *
 *  preservec (int)
 *    - Number of variables to preserve (as specified in preservev).
 *  preservev (char const * const *)
 *    - A list of strings of variable names to preserve in addition
 *      to the defaults.
 */
void secureproc_sanitize_environment(int preservec,
                                     char const * const * preservev);
/*
 *  Function: secureproc_drop_privileges
 *      Drops all the privileges of the current process to only that
 *      of the process's real UID.
 *
 *  permanent (bool)
 *      By specifying true, both the effective UID and saved UID will
 *      be set to that of the real UID, making the change
 *      irreversible.  Otherwise, the saved UID will be kept the same
 *      value as effective UID before the function call, making the
 *      call reversible so long as the program does not alter the
 *      effective UID.
 */
void secureproc_drop_privileges(int permanent);

/*
 *  Function: secureproc_restore_privileges
 *      Restores the privileges of the process to those before the
 *      call to secureproc_drop_privileges() was made.  This requires
 *      that the call to secureproc_drop_privileges() was with
 *      permanent 'false' option, otherwise this will cause the
 *      current process to exit abrutly.
 */
void secureproc_restore_privileges(void);

#endif /* end header guard */
