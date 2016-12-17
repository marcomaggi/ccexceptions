/*
  Part of: CCExceptions
  Contents: public header file
  Date: Sat Dec 17, 2016

  Abstract



  Copyright (C) 2016 Marco Maggi <marco.maggi-ipsu@poste.it>

  This program is  free software: you can redistribute  it and/or modify
  it  under the  terms  of  the GNU  Lesser  General  Public License  as
  published by  the Free  Software Foundation, either  version 3  of the
  License, or (at your option) any later version.

  This program  is distributed in the  hope that it will  be useful, but
  WITHOUT   ANY  WARRANTY;   without  even   the  implied   warranty  of
  MERCHANTABILITY  or FITNESS  FOR A  PARTICULAR PURPOSE.   See  the GNU
  General Public License for more details.

  You  should have  received a  copy of  the GNU  Lesser General  Public
  License     along    with     this    program.      If    not,     see
  <http://www.gnu.org/licenses/>.
*/

#ifndef CCEXCEPTIONS_H
#define CCEXCEPTIONS_H 1


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
extern "C" {
#endif

/* The  macro  CCEXCEPTIONS_UNUSED  indicates  that a  function,  function
   argument or variable may potentially be unused. Usage examples:

   static int unused_function (char arg) CCEXCEPTIONS_UNUSED;
   int foo (char unused_argument CCEXCEPTIONS_UNUSED);
   int unused_variable CCEXCEPTIONS_UNUSED;
*/
#ifdef __GNUC__
#  define CCEXCEPTIONS_UNUSED		__attribute__((unused))
#else
#  define CCEXCEPTIONS_UNUSED		/* empty */
#endif

#ifndef __GNUC__
#  define __attribute__(...)	/* empty */
#endif

/* I found  the following chunk on  the Net.  (Marco Maggi;  Sun Feb 26,
   2012) */
#if defined _WIN32 || defined __CYGWIN__
#  ifdef BUILDING_DLL
#    ifdef __GNUC__
#      define ccexceptions_decl		__attribute__((dllexport))
#    else
#      define ccexceptions_decl		__declspec(dllexport)
#    endif
#  else
#    ifdef __GNUC__
#      define ccexceptions_decl		__attribute__((dllimport))
#    else
#      define ccexceptions_decl		__declspec(dllimport)
#    endif
#  endif
#  define ccexceptions_private_decl	extern
#else
#  if __GNUC__ >= 4
#    define ccexceptions_decl		__attribute__((visibility ("default")))
#    define ccexceptions_private_decl	__attribute__((visibility ("hidden")))
#  else
#    define ccexceptions_decl		extern
#    define ccexceptions_private_decl	extern
#  endif
#endif


/** --------------------------------------------------------------------
 ** Constants.
 ** ----------------------------------------------------------------- */




/** --------------------------------------------------------------------
 ** Version functions.
 ** ----------------------------------------------------------------- */

ccexceptions_decl const char *	cce_version_string		(void);
ccexceptions_decl int		cce_version_interface_current	(void);
ccexceptions_decl int		cce_version_interface_revision	(void);
ccexceptions_decl int		cce_version_interface_age	(void);


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* CCEXCEPTIONS_H */

/* end of file */
