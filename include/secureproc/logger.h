#ifndef _SECURE_PROC_LOGGER_H_
#define _SECURE_PROC_LOGGER_H_

#include "secureproc/_preproc_.h"

/*
 *  Secure Proc - Logger
 *
 *  Description:
 *      A small logging library intended for the internal use of the
 *      Secure Proc library for both testing and debug purposes.
 *      Defines a logging function which takes the severity, filename,
 *      line number, function name, format string and format string
 *      arguments to produce a log output.
 *
 *  Author(s):
 *      Alex Dale (@superoxigen)
 */

/*
 *  Log Severity Specifiers
 *
 *  Description:
 *      A set of numeric values which represent the severity of the
 *      output being logged in the logging function.
 */
#define SECLOG_EMERG 0
#define SECLOG_ALERT 1
#define SECLOG_CRIT 2
#define SECLOG_ERR 3
#define SECLOG_WARN 4
#define SECLOG_NOTICE 5
#define SECLOG_INFO 6
#define SECLOG_DEBUG 7

#ifdef _DEBUG_
#ifdef __GNUC__
/*
 *  GNU C provides better Variadic Macro extensions for easier use.
 *  Specifically, the '##' operator which removes the last character
 *  if the variable argument list is empty.
 */

#define SECERR(format, ...) seclogf(SECLOG_ERR, __FILE__, __LINE__,\
                                    __FUNCTION__, format, ##__VA_ARGS__)
#define SECWARN(format, ...) seclogf(SECLOG_WARN, __FILE__, __LINE__,\
                                     __FUNCTION__, format, ##__VA_ARGS__)
#define SECINFO(format, ...) seclogf(SECLOG_INFO, __FILE__, __LINE__,\
                                     __FUNCTION__, format, ##__VA_ARGS__)
#define SECDEBUG(format, ...) seclogf(SECLOG_DEBUG, __FILE__, __LINE__,\
                                      __FUNCTION__, format, ##__VA_ARGS__)
#else /* Non-GNU-C */
/*
 *  Without the '##' operator provided by GNU C, the best option is
 *  to use the format string as the first argument in the variadic
 *  macro.
 */
#define SECERR(...) seclogf(SECLOG_ERR, __FILE__, __LINE__,\
                            __FUNCTION__, __VA_ARGS__)
#define SECWARN(...) seclogf(SECLOG_WARN, __FILE__, __LINE__,\
                             __FUNCTION__, __VA_ARGS__)
#define SECINFO(...) seclogf(SECLOG_INFO, __FILE__, __LINE__,\
                             __FUNCTION__, __VA_ARGS__)
#define SECDEBUG(...) seclogf(SECLOG_DEBUG, __FILE__, __LINE__,\
                              __FUNCTION__, __VA_ARGS__)
#endif /* end GNU-C */

#else /* Not Debug Build */

/*
 *  If non debug mode, logging functions are replaced with an empty statement.
 */

#define SECERR(...)
#define SECWARN(...)
#define SECINFO(...)
#define SECDEBUG(...)

#endif /* End _DEBUG_ */

/*
 *  Function: seclogf
 *
 *  Description:
 *      A logging function which will log to the file specified by the
 *      initialized file descriptor (see seclog_init).  The function
 *      takes set of arguments which was used to produce more
 *      meaningful output for tracing to the source of the log.
 *
 *  Parameters:
 *      severity (int)
 *          - An integer representing the severity of the log.  The
 *            value should be a value specified by the Log Severity
 *            Specifiers defined in the logger.h file.  The severity
 *            of the log increases with the small value of the
 *            severity.
 *      filename (const char *)
 *          - A C-style string of the filename where the function is
 *            being called from; however, this can be specified as any
 *            C-style string.
 *      lineno (int)
 *          - The integer of the line number from where the function
 *            is called.  This number can be specified as anything.
 *      funcname (const char *)
 *          - A C-style string of the function name from where this
 *            function is called from.  The string can be any C-style
 *            string.
 *      format (const char *)
 *          - A *printf style format C-style string.
 *      ... (variadic function arguments)
 *          - A variable number of arguments that are to supply the
 *            format string with the appropriate arguments to propery
 *            fill all of the format string values.  Behaviour is
 *            undefined if the arguments do no match the format string
 *            type and quantity.
 *  Returns:
 *      (int)
 *          - The total number of characters that were printed to the
 *            log output.
 */
int seclogf(int severity, const char * filename, int lineno,
            const char * funcname, const char * format, ...);

/*
 *  Function: seclog_init
 *
 *  Description:
 *      Initializes the output file descriptor of the logger function
 *      to a new value.
 *  Parameters:
 *      fd (int)
 *          - The file descriptor of the desired output file.
 *            Negative values are considered invalid and will result
 *            in a error return.
 *  Returns:
 *      (int)
 *          - Upon succussful assignment of the file descriptor, the
 *            value of the old file descriptor is returned with the
 *            intention of closing it if need.  If error occurs, the
 *            value of -1 is returned.
 */
int seclog_init(int fd);

#endif /* endif _SECURE_PROC_LOGGER_H_ */
