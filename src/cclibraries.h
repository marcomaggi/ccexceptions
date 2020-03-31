/*
  Part of: CCLibraries
  Contents: public header file for CCLibraries projects
  Date: Mar 30, 2020

  Abstract

	This header file contains  definitions to be used by all  the packages in the
	CCLibraries project.

  Copyright (C) 2020 Marco Maggi <mrc.mgg@gmail.com>

  This is free software; you can redistribute  it and/or modify it under the terms of
  the GNU Lesser General Public License as published by the Free Software Foundation;
  either version 3.0 of the License, or (at your option) any later version.

  This library  is distributed in the  hope that it  will be useful, but  WITHOUT ANY
  WARRANTY; without  even the implied  warranty of  MERCHANTABILITY or FITNESS  FOR A
  PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License along with
  this library; if not, write to the Free Software Foundation, Inc., 59 Temple Place,
  Suite 330, Boston, MA 02111-1307 USA.
*/

#ifndef CCLIBRARIES_H
#define CCLIBRARIES_H 1


/** --------------------------------------------------------------------
 ** Header files.
 ** ----------------------------------------------------------------- */

#include <cclibraries-config.h>


/** --------------------------------------------------------------------
 ** Compiler attributes.
 ** ----------------------------------------------------------------- */

#ifdef MMUX_HAVE_FUNC_ATTRIBUTE_ALWAYS_INLINE
#  define CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE	__attribute__((__always_inline__))
#else
#  define CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE	/* the empty string */
#endif

#ifdef MMUX_HAVE_FUNC_ATTRIBUTE_CONST
#  define CCLIB_FUNC_ATTRIBUTE_CONST		__attribute__((__const__))
#else
#  define CCLIB_FUNC_ATTRIBUTE_CONST		/* the empty string */
#endif

#ifdef MMUX_HAVE_FUNC_ATTRIBUTE_DLLEXPORT
#  define CCLIB_FUNC_ATTRIBUTE_DLLEXPORT	__attribute__((__dllexport__))
#else
#  define CCLIB_FUNC_ATTRIBUTE_DLLEXPORT	/* the empty string */
#endif

#ifdef MMUX_HAVE_FUNC_ATTRIBUTE_DLLIMPORT
#  define CCLIB_FUNC_ATTRIBUTE_DLLIMPORT	__attribute__((__dllimport__))
#else
#  define CCLIB_FUNC_ATTRIBUTE_DLLIMPORT	/* the empty string */
#endif

#ifdef MMUX_HAVE_FUNC_ATTRIBUTE_FORMAT
#  define CCLIB_FUNC_ATTRIBUTE_FORMAT(...)	__attribute__((__format__(__VA_ARGS__)))
#else
#  define CCLIB_FUNC_ATTRIBUTE_FORMAT(...)	/* the empty string */
#endif

#ifdef MMUX_HAVE_FUNC_ATTRIBUTE_HOT
#  define CCLIB_FUNC_ATTRIBUTE_HOT		__attribute__((__hot__))
#else
#  define CCLIB_FUNC_ATTRIBUTE_HOT		/* the empty string */
#endif

#ifdef MMUX_HAVE_FUNC_ATTRIBUTE_LEAF
#  define CCLIB_FUNC_ATTRIBUTE_LEAF		__attribute__((__leaf__))
#else
#  define CCLIB_FUNC_ATTRIBUTE_LEAF		/* the empty string */
#endif

#ifdef MMUX_HAVE_FUNC_ATTRIBUTE_NONNULL
#  define CCLIB_FUNC_ATTRIBUTE_NONNULL(...)	__attribute__((__nonnull__(__VA_ARGS__)))
#else
#  define CCLIB_FUNC_ATTRIBUTE_NONNULL(...)	/* the empty string */
#endif

#ifdef MMUX_HAVE_FUNC_ATTRIBUTE_NORETURN
#  define CCLIB_FUNC_ATTRIBUTE_NORETURN		__attribute__((__noreturn__))
#else
#  define CCLIB_FUNC_ATTRIBUTE_NORETURN		/* the empty string */
#endif

#ifdef MMUX_HAVE_FUNC_ATTRIBUTE_PURE
#  define CCLIB_FUNC_ATTRIBUTE_PURE		__attribute__((__pure__))
#else
#  define CCLIB_FUNC_ATTRIBUTE_PURE		/* the empty string */
#endif

#ifdef MMUX_HAVE_FUNC_ATTRIBUTE_RETURNS_NONNULL
#  define CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL	__attribute__((__returns_nonnull__))
#else
#  define CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL	/* the empty string */
#endif

#ifdef MMUX_HAVE_FUNC_ATTRIBUTE_UNUSED
#  define CCLIB_FUNC_ATTRIBUTE_UNUSED		__attribute__((__unused__))
#else
#  define CCLIB_FUNC_ATTRIBUTE_UNUSED		/* the empty string */
#endif

#ifdef MMUX_HAVE_FUNC_ATTRIBUTE_USED
#  define CCLIB_FUNC_ATTRIBUTE_USED		__attribute__((__used__))
#else
#  define CCLIB_FUNC_ATTRIBUTE_USED		/* the empty string */
#endif

#ifdef MMUX_HAVE_FUNC_ATTRIBUTE_VISIBILITY
#  define CCLIB_FUNC_ATTRIBUTE_VISIBILITY(...)	__attribute__((__visibility__(__VA_ARGS__)))
#else
#  define CCLIB_FUNC_ATTRIBUTE_VISIBILITY(...)	/* the empty string */
#endif


/** --------------------------------------------------------------------
 ** Preliminary definitions.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
extern "C" {
#endif

/* The macro  CCLIB_UNUSED indicates that  a function, function argument  or variable
   may potentially be unused. Usage examples:

   static int unused_function (char arg) CCLIB_UNUSED;
   int foo (char unused_argument CCLIB_UNUSED);
   int unused_variable CCLIB_UNUSED;
*/
#define CCLIB_UNUSED		CCLIB_FUNC_ATTRIBUTE_UNUSED

#ifndef __GNUC__
#  define __builtin_expect(...)	/* empty */
#endif

#if defined _WIN32 || defined __CYGWIN__
#  ifdef BUILDING_DLL
#    ifdef __GNUC__
#      define cclib_decl	CCLIB_FUNC_ATTRIBUTE_DLLEXPORT extern
#    else
#      define cclib_decl	__declspec(dllexport) extern
#    endif
#  else
#    ifdef __GNUC__
#      define cclib_decl	CCLIB_FUNC_ATTRIBUTE_DLLIMPORT extern
#    else
#      define cclib_decl	__declspec(dllimport) extern
#    endif
#  endif
#  define cclib_private_decl	extern
#else
#  if __GNUC__ >= 4
#    define cclib_decl		CCLIB_FUNC_ATTRIBUTE_VISIBILITY("default") extern
#    define cclib_private_decl	CCLIB_FUNC_ATTRIBUTE_VISIBILITY("hidden")  extern
#  else
#    define cclib_decl		extern
#    define cclib_private_decl	extern
#  endif
#endif


/** --------------------------------------------------------------------
 ** Variadic macros mechanism.
 ** ----------------------------------------------------------------- */

/* The  following  macros are  adapted  from  Stack Overflow  (URL  last
 * accessed Jan 2, 2019):
 *
 *   <https://stackoverflow.com/a/26408195>
 */

/* The macro use:
 *
 *   _CCLIB__NARG__(__VA_ARGS__)
 *
 * expands into the number of arguments in __VA_ARGS__.
 */
#define _CCLIB__NARG__(...)	_CCLIB__NARG_I_(__VA_ARGS__,_CCLIB__RSEQ_N())
#define _CCLIB__NARG_I_(...)	_CCLIB__ARG_N(__VA_ARGS__)
#define _CCLIB__ARG_N( \
      _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
     _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
     _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
     _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
     _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
     _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
     _61,_62,_63,N,...)		N
#define _CCLIB__RSEQ_N() \
     63,62,61,60,                   \
     59,58,57,56,55,54,53,52,51,50, \
     49,48,47,46,45,44,43,42,41,40, \
     39,38,37,36,35,34,33,32,31,30, \
     29,28,27,26,25,24,23,22,21,20, \
     19,18,17,16,15,14,13,12,11,10, \
     9,8,7,6,5,4,3,2,1,0

/* The macro uses:
 *
 *    _CCLIB_VFUNC(cce_new, alpha)
 *    _CCLIB_VFUNC(cce_new, alpha, beta)
 *
 * respectively expand into:
 *
 *    cce_new_1(alpha)
 *    cce_new_2(alpha, beta)
 *
 */
#define _CCLIB___VFUNC(NAME, N)	NAME ## _ ## N
#define _CCLIB__VFUNC(NAME, N)	_CCLIB___VFUNC(NAME, N)
#define _CCLIB_VFUNC(FUNC, ...)	_CCLIB__VFUNC(FUNC, _CCLIB__NARG__(__VA_ARGS__))(__VA_ARGS__)


/** --------------------------------------------------------------------
 ** Helper macros.
 ** ----------------------------------------------------------------- */

/* Pointer cast macro helper. */
#define CCLIB_PC(TYPE,X,Y)		TYPE * X = (TYPE *) (Y)

/* Type cast macro helper. */
#define CCLIB_CAST(TYPE,X,Y)		TYPE X = (TYPE) (Y)


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#endif /* defined CCLIBRARIES_H */

/* end of file */
