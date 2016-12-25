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
 ** Preliminary definitions.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
extern "C" {
#endif

/* The macro CCE_UNUSED indicates that  a function, function argument or
   variable may potentially be unused. Usage examples:

   static int unused_function (char arg) CCE_UNUSED;
   int foo (char unused_argument CCE_UNUSED);
   int unused_variable CCE_UNUSED;
*/
#ifdef __GNUC__
#  define CCE_UNUSED		__attribute__((unused))
#else
#  define CCE_UNUSED		/* empty */
#endif

#ifndef __GNUC__
#  define __attribute__(...)	/* empty */
#endif

/* I found  the following chunk on  the Net.  (Marco Maggi;  Sun Feb 26,
   2012) */
#if defined _WIN32 || defined __CYGWIN__
#  ifdef BUILDING_DLL
#    ifdef __GNUC__
#      define cce_decl		__attribute__((dllexport))
#    else
#      define cce_decl		__declspec(dllexport)
#    endif
#  else
#    ifdef __GNUC__
#      define cce_decl		__attribute__((dllimport))
#    else
#      define cce_decl		__declspec(dllimport)
#    endif
#  endif
#  define cce_private_decl	extern
#else
#  if __GNUC__ >= 4
#    define cce_decl		__attribute__((visibility ("default")))
#    define cce_private_decl	__attribute__((visibility ("hidden")))
#  else
#    define cce_decl		extern
#    define cce_private_decl	extern
#  endif
#endif


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <setjmp.h>


/** --------------------------------------------------------------------
 ** Constants.
 ** ----------------------------------------------------------------- */

typedef enum {
  /* This code  represents the return  value of the first  evaluation of
     "sigsetjmp()". */
  CCE_SUCCESS		= 0,

  /* This  code  represents  the   return  value  of  the  "sigsetjmp()"
     evaluation after a "cce_throw()" call. */
  CCE_ERROR,

  /* This  code  represents  the   return  value  of  the  "sigsetjmp()"
     evaluation after a "cce_retry()" call. */
  CCE_RETRY,

  /* This  code  is  available  to  the  custom  code  to  define  other
     represents the return value of the "sigsetjmp()" evaluation after a
     "cce_throw()" call. */
  CCE_FIRST_NEXT
} cce_code_t;


/** --------------------------------------------------------------------
 ** Version functions.
 ** ----------------------------------------------------------------- */

cce_decl const char *	cce_version_string		(void);
cce_decl int		cce_version_interface_current	(void);
cce_decl int		cce_version_interface_revision	(void);
cce_decl int		cce_version_interface_age	(void);


/** --------------------------------------------------------------------
 ** Type declarations.
 ** ----------------------------------------------------------------- */

struct cce_location_tag_t;
struct cce_handler_tag_t;

typedef void cce_handler_fun_t (struct cce_location_tag_t * L, void * data);

typedef struct cce_handler_tag_t {
  bool				is_cleanup_handler;
  cce_handler_fun_t *		handler_function;
  struct cce_handler_tag_t *	next_handler;
} cce_handler_tag_t;

typedef cce_handler_tag_t		cce_handler_t[1];

typedef struct cce_location_tag_t {
  /* The buffer must be the first member of this struct. */
  sigjmp_buf			buffer;
  void *			condition;
  cce_handler_tag_t *		next_handler;
} cce_location_tag_t;

typedef cce_location_tag_t		cce_location_t[1];


/** --------------------------------------------------------------------
 ** Location functions.
 ** ----------------------------------------------------------------- */

cce_decl void cce_location_init			(cce_location_tag_t * here);
cce_decl void cce_raise				(cce_location_tag_t * L, void * condition);
cce_decl void cce_retry				(cce_location_tag_t * L);
cce_decl void cce_register_cleanup_handler	(cce_location_tag_t * L, void * H);
cce_decl void cce_register_error_handler	(cce_location_tag_t * L, void * H);
cce_decl void cce_run_cleanup_handlers		(cce_location_tag_t * L);
cce_decl void cce_run_error_handlers		(cce_location_tag_t * L);

/* The following macro is meant to be used like this:

	cce_location_t	here;

	if (cce_location(here)) {
	  cce_run_error_handlers(here);
	} else {
	  ...
	  if (error) cce_throw(here, NULL);
          ...
	  cce_run_cleanup_handlers(here);
        }
*/
#define cce_location(HERE)	\
  (cce_location_init(HERE), sigsetjmp((void *)(HERE),0))

/* The following macros are meant to be used like this:

   cce_location_t	here;

   cce_enter(here);
   {
     ...
   }
   cce_leave(here);

*/
#define cce_enter(HERE)					\
							\
  if (cce_location((HERE))) {

#define cce_leave(HERE)					\
							\
  cce_run_cleanup_handlers(HERE); }


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* CCEXCEPTIONS_H */

/* end of file */
