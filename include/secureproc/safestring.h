#ifndef _SAFE_STRING_H_
#define _SAFE_STRING_H_

#include "secureproc/common.h"

/*
 *  Secure Proc - Safe String
 *
 *  Description:
 *      A small set of C-style string functions that perform common
 *      string operations in a more intuitive, consistent manor.
 *
 *  Author(s):
 *      Alex Dale (@superoxigen)
 */

#if (defined(__FreeBSD__) && (__FreeBSD__ >= 3)) || (defined(__OpenBSD__))
#define _STRL_INCLUDED_
/*
 *  The following functions are provided by the standard C library on:
 *      0)  OpenBSD 2.4 and newer
 *      1)  FreeBSD 3.3 and newer
 */
extern size_t
    strlcpy(char * dst, const char * src, size_t size);

extern size_t
    strlcat(char * dst, const char * src, size_t size);

#else /* Non-BSD or older BSD distribution */

/*
 *  strlcpy
 *
 *  Description:
 *      String copy, with the destination size known and with a
 *      guarantee NULL terminator on any non-zero sized buffer.
 *
 *      Will attempt to copy the entire contents of the source buffer
 *      to the destination buffer.  In the event that the destination
 *      buffer is not large enough, the source string is truncated to
 *      size -1 of the destination buffer and a NULL terminator is set
 *      as the last byte.
 *
 *  Parameters:
 *      src (const char *)
 *          - Pointer to the source buffer which stores the C-style
 *            string to be copied from.
 *      size (size_t)
 *          - The total size of the destination buffer in bytes.
 *      dst (char *) (output)
 *          - Pointer to the destination buffer to store the copied
 *            C-style string.  Must not be an alias of the destination
 *            buffer.
 *
 *  Returns:
 *      (size_t)
 *          - The size of the source string, excluding the NULL
 *            terminator.
 */
size_t strlcpy(char * dst, const char * src, size_t size);

/*
 *  strlcpy
 *
 *  Description:
 *      String concatinate, with the destination size known and with a
 *      guarantee NULL terminator on any non-zero sized buffer.
 *
 *      Will attempt to copy the entire contents of the source buffer
 *      to the end of the string already stored in the destination.
 *      In the event that the destination buffer is not large enough,
 *      the source string is truncated to fit as many characters to
 *      file size -1 of the destination buffer after the existing
 *      string, with a NULL terminator as the last byte.
 *
 *  Parameters:
 *      src (const char *)
 *          - Pointer to the source buffer which stores the C-style
 *            string to be copied from.
 *      size (size_t)
 *          - The total size of the destination buffer in bytes.
 *      dst (char *) (output)
 *          - Pointer to the destination buffer to store the copied
 *            C-style string.  Must not be an alias of the destination
 *            buffer.
 *
 *  Returns:
 *      (size_t)
 *          - The size of the source string plus the size of the
 *            string already stored in the destination, excluding the
 *            NULL terminator.
 */
size_t strlcat(char * dst, const char * src, size_t size);

#endif /* Non-BSD OS */

#endif
