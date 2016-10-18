#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#include "secureproc/logger.h"

static int outfd = STDERR_FILENO;

static const char * severity_string(int severity)
{
    switch (severity)
    {
        case SECLOG_EMERG:
            return "EMERG";
        case SECLOG_ALERT:
            return "ALERT";
        case SECLOG_CRIT:
            return "CRIT";
        case SECLOG_ERR:
            return "ERROR";
        case SECLOG_WARN:
            return "WARN";
        case SECLOG_NOTICE:
            return "NOTICE";
        case SECLOG_INFO:
            return "INFO";
        case SECLOG_DEBUG:
            return "DEBUG";
        default:
            return "";
    }
}

int seclogf(int severity,
            const char * filename, int lineno, const char * funcname,
            const char * format, ...)
{
    int         total = 0,
                last = 0;
    va_list     args;

    last = dprintf(outfd, "[%6s] %s:%d (%s) ",
                   severity_string(severity),
                   filename,
                   lineno,
                   funcname);

    if (last < 0)
        return -1;
    total += last;

    va_start(args, format);
    last = vdprintf(outfd, format, args);
    va_end(args);

    if (last < 0)
        return -1;
    total += last;

    return total;
}

int seclog_init(int fd)
{
    int     oldfd = outfd;

    if (fd >= 0)
    {
        outfd = fd;
    }
    else
    {
        return -1; /* ERROR - Invalid File Descriptor */
    }
    return oldfd;
}
