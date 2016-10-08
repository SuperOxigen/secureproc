#ifndef _SECURE_PROC_LOGGER_H_
#define _SECURE_PROC_LOGGER_H_

#include "secureproc/_preproc_.h"

#define SECLOG_EMERG 0
#define SECLOG_ALERT 1
#define SECLOG_CRIT 2
#define SECLOG_ERR 3
#define SECLOG_WARN 4
#define SECLOG_NOTICE 5
#define SECLOG_INFO 6
#define SECLOG_DEBUG 7

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
#else
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
#endif


int seclogf(int severity, const char * filename, const char * lineno,
            const char * funcname, const char * format, ...);

int seclog_init(int fd);

#endif
