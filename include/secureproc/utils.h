#ifndef _SECURE_PROC_UTILS_H_
#define _SECURE_PROC_UTILS_H_

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



#endif
