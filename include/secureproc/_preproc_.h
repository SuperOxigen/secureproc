#ifndef _SECURE_PROC_PREPROC_H_
#define _SECURE_PROC_PREPROC_H_
/*
 *  Secure Proc - Preprocessor and Compiler Directives
 *
 *  Description:
 *      A set of compiler attributes and preprocessor macro wrappers
 *      aid in the programming, debuging, and optimization processes.
 *
 *  Author(s):
 *      Alex Dale (@superoxigen)
 */

#ifdef __GNUC__
/* The library is being built using the GNU C Compiler */

/*
 *  Function Attributes
 */

/*
 *  __pure__
 *
 *  Indicates that the output of the function relies only on its input
 *  parameters and global variables.  The function has no side effect on
 *  global variables.  Only other __pure__ or __const__ functions may be called
 *  from within __pure__ functions.
 */
#ifndef __pure__
#define __pure__ __attribute__((pure))
#endif

/*
 *  __const__
 *
 *  Indicates that the output of the function relies only on its input
 *  parameters.  The function has no side effect on any global variables.
 *  Only other __const__ functions may be called from within __const__
 *  functions.
 */
#ifndef __const__
#define __const__ __attribute__((const))
#endif

/*
 *  __noreturn__
 *
 *  Indicates that calling this function will terminate the program before
 *  returning.
 */
#ifndef __noreturn__
#define __noreturn__ __attribute__((noreturn))
#endif

/*
 *  __format__
 *
 *  Indicates that the function takes arguments in a simular style as a
 *  *printf() family function.
 */
#ifndef __format__
#define __format__ __attribute__((format))
#endif

#else
/* The library is being built using a non GNU C Compiler */

#ifndef __pure__
#define __pure__
#endif

#ifndef __const__
#define __const__
#endif

#ifndef __noreturn__
#define __noreturn__
#endif

#ifndef __format__
#define __format__
#endif


#endif

#endif
