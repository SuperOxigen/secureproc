#include "secureproc/safestring.h"
#include <string.h>
#include "secureproc/_preproc_.h"

#ifndef _STRL_INCLUDED_

__const__ size_t strlcpy(char * restrict dst, const char * restrict src, size_t size)
{
    char       *dstptr = dst;
    size_t      tocopy = size;
    const char *srcptr = src;

    if (tocopy && --tocopy) /* If size is greater than 1 */
    {
        do
        {
            /* Copy and break if source character is NULL */
            if (!(*dstptr++ = *srcptr++)) break;
        }
        while (--tocopy);
    }

    if (!tocopy)
    {
        if (size) *dstptr = 0;
        while (*srcptr++);      /* Get to end of src string */
    }

    return (srcptr - src - 1);  /* Return number of bytes needed to write
                                 * correctly to the buffer. */
}

__const__ size_t strlcat(char * restrict dst, const char * restrict src, size_t size)
{
    char       *dstptr = dst;
    size_t      dstlen,
                tocopy=size;
    const char *srcptr = src;

    while (tocopy-- && *dstptr) dstptr++;
    dstlen = dstptr - dst;

    if (!(tocopy = size - dstlen)) return (dstlen + strlen(src));

    while (*srcptr)
    {
        if (tocopy != 1)
        {
            *dstptr++ = *srcptr;
            tocopy--;
        }
        srcptr++;
    }

    if (size) *dstptr = 0;

    return (dstlen + (srcptr - src));
}

#endif
