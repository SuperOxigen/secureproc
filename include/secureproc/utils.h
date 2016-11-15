#ifndef _SECURE_PROC_UTILS_H_
#define _SECURE_PROC_UTILS_H_

#include "secureproc/common.h"

/*
 *  Secure Proc - Utilities
 *
 *  Description:
 *      A small set of function and macros for making common tasks more
 *      convient.
 *
 *  Author(s):
 *      Alex Dale (@superoxigen)
 */

/*
 *  lenof(buf)
 *
 *  Description:
 *      Determines the length of a stack allocated or global buffer.  Simular
 *      to sizeof() but divides the total byte size by the per-element byte
 *      size.
 *
 *  Parameters:
 *      buf
 *          - A stack or globally allocated buffer
 *  Returns:
 *      (size_t)
 *          - The length of the buffer in units of base type size.
 */
#ifndef lenof
#define lenof(buf) (sizeof(buf) / sizeof(*(buf)))
#endif

/*
 *  read_data
 *
 *  Description:
 *      Safely reads the specified number of bytes from a given file
 *      descriptor.  The bytes will be placed into the given buffer.
 *
 *  Parameters:
 *      fd  - The file descriptor of a readable file.
 *      buf - A pointer to a buffer that must be at least 'nbytes' in
 *            length.
 *      nbytes
 *          - The number of bytes to read from the files.
 *  Returns:
 *      (int)
 *          - A value to specify the outcome of the process.  A value of
 *            0 indicates complete success.  A value of -1 indicates a
 *            general error, and no data has been read.  A value of -2
 *            means an IO error occurred, and that some data had been read.
 */
int read_data(int fd, void * buf, size_t nbytes);

/*
 *  write_data
 *
 *  Description:
 *      Safely writes the specified number of bytes from a given file
 *      descriptor.  The bytes to write will be the given buffer.
 *
 *  Parameters:
 *      fd  - The file descriptor of a readable file.
 *      buf - A pointer to a buffer that must be at least 'nbytes' in
 *            length.
 *      nbytes
 *          - The number of bytes to write to the files.
 *  Returns:
 *      (int)
 *          - A value to specify the outcome of the process.  A value of
 *            0 indicates complete success.  A value of -1 indicates a
 *            general error, and no data has been written.  A value of -2
 *            means an IO error occurred, and that some data had been
 *            written.
 */
int write_data(int fd, const void * buf, size_t nbytes);

#endif
