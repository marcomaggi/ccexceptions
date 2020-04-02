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

#ifdef __cplusplus
extern "C" {
#endif


/** --------------------------------------------------------------------
 ** Header files.
 ** ----------------------------------------------------------------- */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif


/** --------------------------------------------------------------------
 ** Compiler attributes.
 ** ----------------------------------------------------------------- */

#ifdef HAVE_FUNC_ATTRIBUTE_ALWAYS_INLINE
#  define CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE	__attribute__((__always_inline__))
#else
#  define CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE	/* empty string */
#endif

#ifdef HAVE_FUNC_ATTRIBUTE_CONST
#  define CCLIB_FUNC_ATTRIBUTE_CONST		__attribute__((__const__))
#else
#  define CCLIB_FUNC_ATTRIBUTE_CONST	/* empty string */
#endif

#ifdef HAVE_FUNC_ATTRIBUTE_DLLEXPORT
#  define CCLIB_FUNC_ATTRIBUTE_DLLEXPORT	__attribute__((__dllexport__))
#else
#  define CCLIB_FUNC_ATTRIBUTE_DLLEXPORT	/* empty string */
#endif

#ifdef HAVE_FUNC_ATTRIBUTE_DLLIMPORT
#  define CCLIB_FUNC_ATTRIBUTE_DLLIMPORT	__attribute__((__dllimport__))
#else
#  define CCLIB_FUNC_ATTRIBUTE_DLLIMPORT	/* empty string */
#endif

#ifdef HAVE_FUNC_ATTRIBUTE_FORMAT
#  define CCLIB_FUNC_ATTRIBUTE_FORMAT(...)	__attribute__((__format__(__VA_ARGS__)))
#else
#  define CCLIB_FUNC_ATTRIBUTE_FORMAT	/* empty string */
#endif

#ifdef HAVE_FUNC_ATTRIBUTE_HOT
#  define CCLIB_FUNC_ATTRIBUTE_HOT		__attribute__((__hot__))
#else
#  define CCLIB_FUNC_ATTRIBUTE_HOT	/* empty string */
#endif

#ifdef HAVE_FUNC_ATTRIBUTE_LEAF
#  define CCLIB_FUNC_ATTRIBUTE_LEAF		__attribute__((__leaf__))
#else
#  define CCLIB_FUNC_ATTRIBUTE_LEAF	/* empty string */
#endif

#ifdef HAVE_FUNC_ATTRIBUTE_NONNULL
#  define CCLIB_FUNC_ATTRIBUTE_NONNULL(...)	__attribute__((__nonnull__(__VA_ARGS__)))
#else
#  define CCLIB_FUNC_ATTRIBUTE_NONNULL	/* empty string */
#endif

#ifdef HAVE_FUNC_ATTRIBUTE_NORETURN
#  define CCLIB_FUNC_ATTRIBUTE_NORETURN		__attribute__((__noreturn__))
#else
#  define CCLIB_FUNC_ATTRIBUTE_NORETURN	/* empty string */
#endif

#ifdef HAVE_FUNC_ATTRIBUTE_PURE
#  define CCLIB_FUNC_ATTRIBUTE_PURE		__attribute__((__pure__))
#else
#  define CCLIB_FUNC_ATTRIBUTE_PURE	/* empty string */
#endif

#ifdef HAVE_FUNC_ATTRIBUTE_RETURNS_NONNULL
#  define CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL	__attribute__((__returns_nonnull__))
#else
#  define CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL	/* empty string */
#endif

#ifdef HAVE_FUNC_ATTRIBUTE_UNUSED
#  define CCLIB_FUNC_ATTRIBUTE_UNUSED		__attribute__((__unused__))
#else
#  define CCLIB_FUNC_ATTRIBUTE_UNUSED	/* empty string */
#endif

#ifdef HAVE_FUNC_ATTRIBUTE_USED
#  define CCLIB_FUNC_ATTRIBUTE_USED		__attribute__((__used__))
#else
#  define CCLIB_FUNC_ATTRIBUTE_USED	/* empty string */
#endif

#ifdef HAVE_FUNC_ATTRIBUTE_VISIBILITY
#  define CCLIB_FUNC_ATTRIBUTE_VISIBILITY(...)	__attribute__((__visibility__(__VA_ARGS__)))
#else
#  define CCLIB_FUNC_ATTRIBUTE_VISIBILITY	/* empty string */
#endif


/** --------------------------------------------------------------------
 ** Preliminary definitions.
 ** ----------------------------------------------------------------- */

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

#if (defined _WIN32 || defined __CYGWIN__)
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

/* The following  macros are adapted  from Stack Overflow  (URL last accessed  Jan 2,
 * 2019):
 *
 *   <https://stackoverflow.com/a/26408195>
 *
 * for a full explanation, see also (URL last accessed Apr  1, 2020):
 *
 *   <https://gustedt.wordpress.com/2010/06/03/default-arguments-for-c99/>
 *
 * NOTE I know that the project P99 by implements an extensino to this mechanism that
 * allows  using zero  optional  arguments in  the call  to  "CCLIB_VFUNC()"; but  it
 * involves defining even more complex preprocessor macors, so I do not implement it.
 * Anyway, here is the project's link (URL last accessed Apr 1, 2020):
 *
 *   <https://p99.gforge.inria.fr/>
 *
 * (Marco Maggi; Apr  1, 2020)
 */

/* The macro use:
 *
 *   CCLIB_VFUNC_PRIVATE_COUNT_ARGS(__VA_ARGS__)
 *
 * expands into the number of arguments in __VA_ARGS__.
 */
#define CCLIB_VFUNC_PRIVATE_COUNT_ARGS(...)	\
  CCLIB_VFUNC_PRIVATE_COUNT_ARGS_I(__VA_ARGS__,CCLIB_VFUNC_PRIVATE_REVERSED_SEQUENCE)

/* This   is   a  worker   macro   that   just   merges   the  arguments   given   to
 * "CCLIB_VFUNC_PRIVATE_COUNT_ARGS(...)" into a single "__VA_ARGS__".
 *
 *   CCLIB_VFUNC_PRIVATE_COUNT_ARGS(alpha,beta,delta)
 *   ==> CCLIB_VFUNC_PRIVATE_COUNT_ARGS_I(alpha,beta,delta,CCLIB_VFUNC_PRIVATE_REVERSED_SEQUENCE())
 *   ==> CCLIB_VFUNC_PRIVATE_ARG_N(alpha,beta,delta,63,62,...,1,0)
 */
#define CCLIB_VFUNC_PRIVATE_COUNT_ARGS_I(...)	CCLIB_VFUNC_PRIVATE_ARG_N(__VA_ARGS__)

/* This macro  accepts at least  64 arguments: from ARG_01  to ARG_63, plus  at least
 * one.   The  result of  the  expansion  equals the  number  of  arguments given  to
 * "CCLIB_VFUNC_PRIVATE_COUNT_ARGS()".
 *
 *   CCLIB_VFUNC_PRIVATE_COUNT_ARGS(alpha,beta,delta)
 *   ==> CCLIB_VFUNC_PRIVATE_ARG_N(alpha,beta,delta,63,62,---,1,0)
 *   ==> 3
 *
 * In the macro use:
 *
 *   CCLIB_VFUNC_PRIVATE_ARG_N(alpha,beta,delta,63,62,---,1,0)
 *
 * the arguments are bound as follows:
 *
 *   ARG_01 = alpha
 *   ARG_02 = beta
 *   ARG_03 = delta
 *   ARG_04 = 63
 *   ARG_05 = 62
 *   ---
 *   ARG_63 = 4
 *   N      = 3
 *   __VA_ARGS__ = 2,1,0
 */
#define CCLIB_VFUNC_PRIVATE_ARG_N(ARG_01, ARG_02, ARG_03, ARG_04, ARG_05, ARG_06, ARG_07, ARG_08, ARG_09, ARG_10,	\
				  ARG_11, ARG_12, ARG_13, ARG_14, ARG_15, ARG_16, ARG_17, ARG_18, ARG_19, ARG_20,	\
				  ARG_21, ARG_22, ARG_23, ARG_24, ARG_25, ARG_26, ARG_27, ARG_28, ARG_29, ARG_30,	\
				  ARG_31, ARG_32, ARG_33, ARG_34, ARG_35, ARG_36, ARG_37, ARG_38, ARG_39, ARG_40,	\
				  ARG_41, ARG_42, ARG_43, ARG_44, ARG_45, ARG_46, ARG_47, ARG_48, ARG_49, ARG_50,	\
				  ARG_51, ARG_52, ARG_53, ARG_54, ARG_55, ARG_56, ARG_57, ARG_58, ARG_59, ARG_60,	\
				  ARG_61, ARG_62, ARG_63, N, ...)		N

/* This macro just expands into the reversed integers sequence:
 *
 *   63,62,...,1,0
 */
#define CCLIB_VFUNC_PRIVATE_REVERSED_SEQUENCE		    \
  63,62,61,60,						    \
    59,58,57,56,55,54,53,52,51,50,			    \
    49,48,47,46,45,44,43,42,41,40,			    \
    39,38,37,36,35,34,33,32,31,30,			    \
    29,28,27,26,25,24,23,22,21,20,			    \
    19,18,17,16,15,14,13,12,11,10,			    \
    9,8,7,6,5,4,3,2,1,0

/* This macro builds the output name.
 *
 *   CCLIB_VFUNC_PRIVATE_COMPOSE_NAME(my_new, 2)
 *   ==> my_new_2
 */
#define CCLIB_VFUNC_PRIVATE_COMPOSE_NAME(NAME, N)	NAME ## _ ## N

/* This is an intermediate step that makes sure that:
 *
 *   CCLIB_VFUNC_PRIVATE_COUNT_ARGS(__VA_ARGS__)
 *
 * in the expansion of "CCLIB_VFUNC()"  is itself expanded before the stringification
 * performed by "##".
 */
#define CCLIB_VFUNC_PRIVATE__VFUNC(NAME, N)	CCLIB_VFUNC_PRIVATE_COMPOSE_NAME(NAME, N)

/* The macro uses:
 *
 *    CCLIB_VFUNC(cce_new, alpha)
 *    CCLIB_VFUNC(cce_new, alpha, beta)
 *
 * respectively expand into:
 *
 *    cce_new_1(alpha)
 *    cce_new_2(alpha, beta)
 */
#define CCLIB_VFUNC(FUNC, ...)		\
  CCLIB_VFUNC_PRIVATE__VFUNC(FUNC, CCLIB_VFUNC_PRIVATE_COUNT_ARGS(__VA_ARGS__))(__VA_ARGS__)


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

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* defined CCLIBRARIES_H */

/* end of file */
