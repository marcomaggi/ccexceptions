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
#ifdef __GNUC__
#  define CCLIB_UNUSED		__attribute__((__unused__))
#else
#  define CCLIB_UNUSED		/* empty */
#endif

#ifndef __GNUC__
#  define __attribute__(...)	/* empty */
#endif

#ifndef __GNUC__
#  define __builtin_expect(...)	/* empty */
#endif

#if defined _WIN32 || defined __CYGWIN__
#  ifdef BUILDING_DLL
#    ifdef __GNUC__
#      define cclib_decl		__attribute__((__dllexport__)) extern
#    else
#      define cclib_decl		__declspec(dllexport) extern
#    endif
#  else
#    ifdef __GNUC__
#      define cclib_decl		__attribute__((__dllimport__)) extern
#    else
#      define cclib_decl		__declspec(dllimport) extern
#    endif
#  endif
#  define cclib_private_decl	extern
#else
#  if __GNUC__ >= 4
#    define cclib_decl		__attribute__((__visibility__("default"))) extern
#    define cclib_private_decl	__attribute__((__visibility__("hidden")))  extern
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
