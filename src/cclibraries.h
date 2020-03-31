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
