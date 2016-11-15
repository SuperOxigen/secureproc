#include <limits.h>
#include <errno.h>
#include <unistd.h>

#include "secureproc/utils.h"

int read_data(int fd, void * buf, size_t nbytes)
{
    size_t  toread,
            nread = 0;
    ssize_t result;

    if (!buf)
    {
        return -1;
    }

    do
    {
        if ((nbytes - nread) > SSIZE_MAX) toread = SSIZE_MAX;
        else toread = nbytes - nread;

        result = read(fd, (char *) buf + nread, toread);

        if (result > 0) nread += result;
        /* OK if interrupted by signal, may resume. */
        else if (errno != EINTR) return -2;
    }
    while (nread < nbytes);

    return 0;
}

int write_data(int fd, const void * buf, size_t nbytes)
{
    size_t  towrite,
            written = 0;
    ssize_t result;

    if (!buf)
    {
        return -1;
    }

    do
    {
        if (nbytes - written > SSIZE_MAX) towrite = SSIZE_MAX;
        else towrite = nbytes - written;

        result = write(fd, (const char *) buf + written, towrite);

        if (result >= 0) written += result;
        else if (errno != EINTR) return -2;
    }
    while(written < nbytes);

    return 0;
}
