/*
  Part of: CCExceptions
  Contents: public header file
  Date: Sat Dec 17, 2016

  Abstract



  Copyright (C) 2016, 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

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

/* Enable latest POSIX features. */
//#define _POSIX_C_SOURCE		200809L

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <setjmp.h>

/** --------------------------------------------------------------------
 ** Constants.
 ** ----------------------------------------------------------------- */

typedef enum {
  /* This code  represents the return  value of the first  evaluation of
     "setjmp()". */
  CCE_SUCCESS		= 0,

  /* This  code  represents  the   return  value  of  the  "setjmp()"
     evaluation after a "cce_throw()" call. */
  CCE_ERROR,

  /* This  code  represents  the   return  value  of  the  "setjmp()"
     evaluation after a "cce_retry()" call. */
  CCE_RETRY,

  /* This  code  is  available  to  the  custom  code  to  define  other
     represents the return value of the "setjmp()" evaluation after a
     "cce_raise()" call. */
  CCE_FIRST_NEXT
} cce_code_t;

/** --------------------------------------------------------------------
 ** Version functions.
 ** ----------------------------------------------------------------- */

cce_decl const char *	cce_version_string		(void)
  __attribute__((pure));
cce_decl int		cce_version_interface_current	(void)
  __attribute__((pure));
cce_decl int		cce_version_interface_revision	(void)
  __attribute__((pure));
cce_decl int		cce_version_interface_age	(void)
  __attribute__((pure));

/** --------------------------------------------------------------------
 ** Error and cleanup handlers.
 ** ----------------------------------------------------------------- */

typedef struct cce_location_t		cce_location_t;
typedef struct cce_handler_t		cce_handler_t;

typedef void cce_handler_fun_t (cce_location_t * L, cce_handler_t * H);

struct cce_handler_t {
  bool				is_cleanup_handler;
  cce_handler_fun_t *		handler_function;
  cce_handler_t *		next_handler;
};

cce_decl void cce_register_cleanup_handler	(cce_location_t * L, cce_handler_t * H)
  __attribute__((nonnull(1,2)));
cce_decl void cce_register_error_handler	(cce_location_t * L, cce_handler_t * H)
  __attribute__((nonnull(1,2)));
cce_decl void cce_run_cleanup_handlers		(cce_location_t * L)
  __attribute__((nonnull(1)));
cce_decl void cce_run_error_handlers		(cce_location_t * L)
  __attribute__((nonnull(1)));

/** --------------------------------------------------------------------
 ** Exceptional condition descriptors.
 ** ----------------------------------------------------------------- */

/* Forward declaration. */
typedef struct cce_condition_t		cce_condition_t;

typedef void		cce_condition_free_fun_t		(cce_condition_t * condition)
  __attribute__((nonnull(1)));
typedef const char *	cce_condition_static_message_fun_t	(const cce_condition_t * condition)
  __attribute__((nonnull(1)));

typedef struct cce_condition_descriptor_t {
  const struct cce_condition_descriptor_t *	parent;
  cce_condition_free_fun_t *			free;
  cce_condition_static_message_fun_t *		static_message;
} cce_condition_descriptor_t;

struct cce_condition_t {
  const cce_condition_descriptor_t *		descriptor;
};

cce_decl const cce_condition_descriptor_t *	cce_root_condition_descriptor;

/* ------------------------------------------------------------------ */

cce_decl const cce_condition_descriptor_t *	cce_unknown_condition_descriptor;
cce_decl const cce_condition_t *		cce_unknown_condition;

/* ------------------------------------------------------------------ */

typedef struct cce_errno_condition_descriptor_t {
  cce_condition_descriptor_t;
} cce_errno_condition_descriptor_t;

typedef struct cce_errno_condition_t {
  cce_condition_t;
  int						errnum;
  const char *					message;
} cce_errno_condition_t;

cce_decl cce_condition_t * cce_errno_condition (int code);
cce_decl const cce_condition_descriptor_t *	cce_errno_condition_descriptor;

/* ------------------------------------------------------------------ */

cce_decl void		cce_condition_init (cce_condition_t * condition,
					    const cce_condition_descriptor_t * descriptor)
  __attribute__((nonnull(1,2)));
cce_decl bool		cce_condition_is_a (const cce_condition_t * condition,
					    const cce_condition_descriptor_t * descriptor)
  __attribute__((nonnull(1,2)));
cce_decl bool		cce_condition_descriptor_child_and_parent (const cce_condition_descriptor_t * child,
								   const cce_condition_descriptor_t * parent)
  __attribute__((nonnull(1,2)));
cce_decl const cce_condition_descriptor_t * cce_condition_descriptor (const cce_condition_t * condition)
  __attribute__((nonnull(1)));
cce_decl void		cce_condition_free		(cce_condition_t * condition)
  __attribute__((nonnull(1)));
cce_decl const char *	cce_condition_static_message	(cce_condition_t * condition)
  __attribute__((nonnull(1)));

/** --------------------------------------------------------------------
 ** Locations.
 ** ----------------------------------------------------------------- */

struct cce_location_t {
  /* The buffer must be the first member of this struct. */
  jmp_buf			buffer;
  const cce_condition_t *	condition;
  cce_handler_t *		next_handler;
};

cce_decl void cce_location_init	(cce_location_t * here)
  __attribute__((nonnull(1)));
cce_decl void cce_raise		(cce_location_t * L, const cce_condition_t * condition)
  __attribute__((noreturn,nonnull(1)));
cce_decl void cce_retry		(cce_location_t * L)
  __attribute__((noreturn,nonnull(1)));
cce_decl cce_condition_t * cce_location_condition (cce_location_t * L)
  __attribute__((nonnull(1)));

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
  (cce_location_init(HERE), setjmp((void *)(HERE)))

/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* CCEXCEPTIONS_H */

/* end of file */
