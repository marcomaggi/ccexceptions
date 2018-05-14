/*
  Part of: CCExceptions
  Contents: public header file
  Date: Sat Dec 17, 2016

  Abstract

	This is the  main header: it must be included  in all the source
	files using CCExceptions.  Notice that  the code needs the POSIX
	features, so it defines the following symbol:

	   #define _POSIX_C_SOURCE 200809L

  Copyright (C) 2016, 2017, 2018 Marco Maggi <marco.maggi-ipsu@poste.it>

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
#  define CCE_UNUSED		__attribute__((__unused__))
#else
#  define CCE_UNUSED		/* empty */
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
#      define cce_decl		__attribute__((__dllexport__)) extern
#    else
#      define cce_decl		__declspec(dllexport) extern
#    endif
#  else
#    ifdef __GNUC__
#      define cce_decl		__attribute__((__dllimport__)) extern
#    else
#      define cce_decl		__declspec(dllimport) extern
#    endif
#  endif
#  define cce_private_decl	extern
#else
#  if __GNUC__ >= 4
#    define cce_decl		__attribute__((__visibility__("default"))) extern
#    define cce_private_decl	__attribute__((__visibility__("hidden")))  extern
#  else
#    define cce_decl		extern
#    define cce_private_decl	extern
#  endif
#endif


/** --------------------------------------------------------------------
 ** Helper macros.
 ** ----------------------------------------------------------------- */

/* Pointer cast macro helper. */
#define CCE_PC(TYPE,X,Y)		TYPE * X = (TYPE *) (Y)

/* Cast pointer S to a location structure and evaluate to the pointer to
   condition object. */
#define CCE_CLOC(S)			(((cce_location_t *)(S))->condition)


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

/* Enable latest POSIX features. */
#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE		200809L

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h> /* for offsetof() */
#include <setjmp.h>
#include <errno.h>
#include <unistd.h>


/** --------------------------------------------------------------------
 ** Constants.
 ** ----------------------------------------------------------------- */

typedef enum {
  /* This code  represents the return  value of the first  evaluation of
     "setjmp()". */
  CCE_SUCCESS		= 0,
  CCE_ENTER		= 0,

  /* This code represents the return  value of the "setjmp()" evaluation
     after a "cce_raise()" call. */
  CCE_ERROR		= 1,
  CCE_EXCEPT		= 1,

  /* This code represents the return  value of the "setjmp()" evaluation
     after a "cce_retry()" call. */
  CCE_RETRY		= 2,

  CCE_FIRST_NEXT
} cce_code_t;


/** --------------------------------------------------------------------
 ** Version functions.
 ** ----------------------------------------------------------------- */

cce_decl char const *	cce_version_string		(void)
  __attribute__((__leaf__,__pure__));
cce_decl int		cce_version_interface_current	(void)
  __attribute__((__leaf__,__pure__));
cce_decl int		cce_version_interface_revision	(void)
  __attribute__((__leaf__,__pure__));
cce_decl int		cce_version_interface_age	(void)
  __attribute__((__leaf__,__pure__));


/** --------------------------------------------------------------------
 ** Forward declarations.
 ** ----------------------------------------------------------------- */

typedef struct cce_location_t			cce_location_t;
typedef struct cce_handler_t			cce_handler_t;
typedef struct cce_clean_handler_t		cce_clean_handler_t;
typedef struct cce_error_handler_t		cce_error_handler_t;

typedef struct cce_descriptor_t			cce_descriptor_t;
typedef struct cce_condition_t			cce_condition_t;

typedef struct cce_descriptor_root_t		cce_descriptor_root_t;
typedef struct cce_condition_root_t		cce_condition_root_t;

typedef struct cce_descriptor_unknown_t		cce_descriptor_unknown_t;
typedef struct cce_condition_unknown_t		cce_condition_unknown_t;

typedef struct cce_descriptor_break_t		cce_descriptor_break_t;
typedef struct cce_condition_break_t		cce_condition_break_t;

typedef struct cce_descriptor_unimplemented_t	cce_descriptor_unimplemented_t;
typedef struct cce_condition_unimplemented_t	cce_condition_unimplemented_t;

typedef struct cce_descriptor_error_t		cce_descriptor_error_t;
typedef struct cce_condition_error_t		cce_condition_error_t;

typedef struct cce_descriptor_runtime_error_t	cce_descriptor_runtime_error_t;
typedef struct cce_condition_runtime_error_t	cce_condition_runtime_error_t;

typedef struct cce_descriptor_logic_error_t	cce_descriptor_logic_error_t;
typedef struct cce_condition_logic_error_t	cce_condition_logic_error_t;

typedef struct cce_descriptor_invalid_argument_t cce_descriptor_invalid_argument_t;
typedef struct cce_condition_invalid_argument_t	cce_condition_invalid_argument_t;

typedef struct cce_descriptor_unreachable_t	cce_descriptor_unreachable_t;
typedef struct cce_condition_unreachable_t	cce_condition_unreachable_t;

typedef struct cce_descriptor_math_error_t	cce_descriptor_math_error_t;
typedef struct cce_condition_math_error_t	cce_condition_math_error_t;

typedef struct cce_descriptor_math_nan_t	cce_descriptor_math_nan_t;
typedef struct cce_condition_math_nan_t		cce_condition_math_nan_t;

typedef struct cce_descriptor_math_infinity_t	cce_descriptor_math_infinity_t;
typedef struct cce_condition_math_infinity_t	cce_condition_math_infinity_t;

typedef struct cce_descriptor_math_overflow_t	cce_descriptor_math_overflow_t;
typedef struct cce_condition_math_overflow_t	cce_condition_math_overflow_t;

typedef struct cce_descriptor_math_underflow_t	cce_descriptor_math_underflow_t;
typedef struct cce_condition_math_underflow_t	cce_condition_math_underflow_t;

typedef struct cce_descriptor_errno_t		cce_descriptor_errno_t;
typedef struct cce_condition_errno_t		cce_condition_errno_t;

typedef cce_location_t *			cce_destination_t;


/** --------------------------------------------------------------------
 ** Error and cleanup handlers.
 ** ----------------------------------------------------------------- */

typedef void cce_handler_fun_t (cce_condition_t const * C, cce_handler_t * H);

struct cce_handler_t {
  bool			is_clean_handler;
  cce_handler_fun_t *	function;
  cce_handler_t *	next_handler;
  union {
    void *		pointer;
    char *		pathname;
    int			filedes;
    int			pipedes[2];
  };
};

struct cce_clean_handler_t {
  cce_handler_t		handler;
};

struct cce_error_handler_t {
  cce_handler_t		handler;
};

cce_decl void cce_register_clean_handler (cce_destination_t L, cce_handler_t * H)
  __attribute__((__leaf__,__nonnull__(1,2)));

cce_decl void cce_register_error_handler (cce_destination_t L, cce_handler_t * H)
  __attribute__((__leaf__,__nonnull__(1,2)));

cce_decl void cce_forget_handler (cce_destination_t L, cce_handler_t * H)
  __attribute__((__leaf__,__nonnull__(1,2)));

/* We do *not*  set the "leaf" attribute for this  function, because the
   cleanup  handlers  might  modify  data  in  the  current  compilation
   unit. */
cce_decl void cce_run_clean_handlers (cce_destination_t L)
  __attribute__((__nonnull__(1)));

/* We do *not*  set the "leaf" attribute for this  function, because the
   error handlers might modify data in the current compilation unit. */
cce_decl void cce_run_error_handlers (cce_destination_t L)
  __attribute__((__nonnull__(1)));

/* For compatibility with old versions. */
#define cce_cleanup_handler_t		cce_clean_handler_t
#define cce_run_cleanup_handlers	cce_run_clean_handlers
#define cce_register_cleanup_handler	cce_register_clean_handler


/** --------------------------------------------------------------------
 ** Exceptional condition descriptors.
 ** ----------------------------------------------------------------- */

typedef void cce_condition_delete_fun_t (cce_condition_t * C)
  __attribute__((__nonnull__(1)));

typedef void cce_condition_final_fun_t (cce_condition_t * C)
  __attribute__((__nonnull__(1)));

typedef char const * cce_condition_static_message_fun_t	(cce_condition_t const * C)
  __attribute__((__nonnull__(1)));

struct cce_descriptor_t {
  cce_descriptor_t const *		parent;
  cce_condition_delete_fun_t *		delete;
  cce_condition_final_fun_t *		final;
  cce_condition_static_message_fun_t *	static_message;
};

struct cce_condition_t {
  cce_descriptor_t const *		descriptor;
};

/* ------------------------------------------------------------------ */

cce_decl void cce_condition_init (cce_condition_t * C, cce_descriptor_t const * D)
  __attribute__((__leaf__,__nonnull__(1,2)));

cce_decl void cce_condition_final (cce_condition_t * C)
  __attribute__((__leaf__,__nonnull__(1)));

cce_decl void cce_condition_delete (cce_condition_t * C)
  __attribute__((__leaf__,__nonnull__(1)));

cce_decl bool cce_is_condition (cce_condition_t const * C, cce_descriptor_t const * D)
  __attribute__((__leaf__,__nonnull__(1,2)));

cce_decl char const * cce_condition_static_message (cce_condition_t const * C)
  __attribute__((__leaf__,__nonnull__(1)));

/* ------------------------------------------------------------------ */

cce_decl bool cce_descriptor_child_and_ancestor (cce_descriptor_t const * child, cce_descriptor_t const * ancestor)
  __attribute__((__leaf__,__nonnull__(1,2)));


/** --------------------------------------------------------------------
 ** Exceptional condition objects: root exception.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_root_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_root_t {
  cce_condition_t	condition;
};

cce_decl cce_descriptor_root_t const * const cce_descriptor_root_ptr;

cce_decl void cce_descriptor_set_root_parent (cce_descriptor_t * D)
  __attribute__((__nonnull__(1)));

static inline void
cce_condition_init_root (cce_condition_root_t * C CCE_UNUSED)
{
  /* We  do   nothing  here.   We   need  to  remember  that   the  true
     initialisation   of  the   field   "condition"   is  performed   by
     "cce_condition_init()",  which   must  be  always  called   by  the
     "condition_new" function. */
}

cce_decl bool cce_condition_is_root (cce_condition_t const * C)
  __attribute__((__pure__,__nonnull__(1)));


/** --------------------------------------------------------------------
 ** Exceptional condition objects: unknown exception.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_unknown_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_unknown_t {
  cce_condition_root_t	root;
};

cce_decl cce_descriptor_unknown_t const * const	cce_descriptor_unknown_ptr;
cce_decl cce_condition_unknown_t const  * const	cce_condition_unknown_ptr;

__attribute__((__always_inline__,__const__))
static inline cce_condition_t const *
cce_condition_new_unknown (void)
{
  return (cce_condition_t const *) cce_condition_unknown_ptr;
}

__attribute__((__pure__,__nonnull__(1),__always_inline__))
static inline bool
cce_condition_is_unknown (cce_condition_t const * C)
{
  return cce_is_condition(C, &(cce_descriptor_unknown_ptr->descriptor));
}

/* ------------------------------------------------------------------ */

#define cce_condition_unknown(S)					\
  _Generic((S),								\
	   cce_location_t			*: (cce_condition_unknown_t const *)CCE_CLOC(S), \
	   cce_location_t[1]			 : (cce_condition_unknown_t const *)CCE_CLOC(S), \
	   cce_condition_t			*: (cce_condition_unknown_t const *)(S), \
	   cce_condition_unknown_t		*: (cce_condition_unknown_t const *)(S), \
	   cce_condition_t		const	*: (cce_condition_unknown_t const *)(S), \
	   cce_condition_unknown_t	const	*: (cce_condition_unknown_t const *)(S), \
	   cce_condition_t		const	* const: (cce_condition_unknown_t const *)(S), \
	   cce_condition_unknown_t	const	* const: (cce_condition_unknown_t const *)(S))


/** --------------------------------------------------------------------
 ** Exceptional condition objects: break exception.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_break_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_break_t {
  cce_condition_root_t	root;
};

cce_decl cce_descriptor_break_t const * const	cce_descriptor_break_ptr;
cce_decl cce_condition_break_t  const  * const	cce_condition_break_ptr;

__attribute__((__always_inline__,__nonnull__(1)))
static inline void
cce_condition_init_break (cce_condition_break_t * C)
{
  cce_condition_init_root(&(C->root));
}

__attribute__((__always_inline__,__const__))
static inline cce_condition_t const *
cce_condition_new_break (void)
{
  return (cce_condition_t const *) cce_condition_break_ptr;
}

__attribute__((__pure__,__nonnull__(1),__always_inline__))
static inline bool
cce_condition_is_break (cce_condition_t const * C)
{
  return cce_is_condition(C, &(cce_descriptor_break_ptr->descriptor));
}

/* ------------------------------------------------------------------ */

#define cce_condition_break(S)					\
  _Generic((S),								\
	   cce_location_t			*: (cce_condition_break_t const *)CCE_CLOC(S), \
	   cce_location_t[1]			 : (cce_condition_break_t const *)CCE_CLOC(S), \
	   cce_condition_t			*: (cce_condition_break_t const *)(S), \
	   cce_condition_break_t		*: (cce_condition_break_t const *)(S), \
	   cce_condition_t		const	*: (cce_condition_break_t const *)(S), \
	   cce_condition_break_t	const	*: (cce_condition_break_t const *)(S), \
	   cce_condition_t		const	* const: (cce_condition_break_t const *)(S), \
	   cce_condition_break_t	const	* const: (cce_condition_break_t const *)(S))


/** --------------------------------------------------------------------
 ** Exceptional condition objects: generic error exception.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_error_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_error_t {
  cce_condition_root_t	root;
};

cce_decl cce_descriptor_error_t const * const	cce_descriptor_error_ptr;
cce_decl cce_condition_error_t  const * const	cce_condition_error_ptr;

__attribute__((__always_inline__,__nonnull__(1)))
static inline void
cce_condition_init_error (cce_condition_error_t * C)
{
  cce_condition_init_root(&(C->root));
}

__attribute__((__always_inline__,__const__))
static inline cce_condition_t const *
cce_condition_new_error (void)
{
  return (cce_condition_t const *) cce_condition_error_ptr;
}

__attribute__((__pure__,__nonnull__(1),__always_inline__))
static inline bool
cce_condition_is_error (cce_condition_t const * C)
{
  return cce_is_condition(C, &(cce_descriptor_error_ptr->descriptor));
}

/* ------------------------------------------------------------------ */

#define cce_condition_error(S)						\
  _Generic((S),								\
	   cce_location_t			*: (cce_condition_error_t const *)CCE_CLOC(S), \
	   cce_location_t[1]			 : (cce_condition_error_t const *)CCE_CLOC(S), \
	   cce_condition_t			*: (cce_condition_error_t const *)(S), \
	   cce_condition_error_t		*: (cce_condition_error_t const *)(S), \
	   cce_condition_t		const	*: (cce_condition_error_t const *)(S), \
	   cce_condition_error_t	const	*: (cce_condition_error_t const *)(S), \
	   cce_condition_t		const	* const: (cce_condition_error_t const *)(S), \
	   cce_condition_error_t	const	* const: (cce_condition_error_t const *)(S))


/** --------------------------------------------------------------------
 ** Exceptional condition objects: runtime error exception.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_runtime_error_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_runtime_error_t {
  cce_condition_error_t	error;
};

cce_decl cce_descriptor_runtime_error_t const * const	cce_descriptor_runtime_error_ptr;
cce_decl cce_condition_runtime_error_t  const * const	cce_condition_runtime_error_ptr;

__attribute__((__always_inline__,__nonnull__(1)))
static inline void
cce_condition_init_runtime_error (cce_condition_runtime_error_t * C CCE_UNUSED)
{
}

__attribute__((__always_inline__,__const__))
static inline cce_condition_t const *
cce_condition_new_runtime_error (void)
{
  return (cce_condition_t const *) cce_condition_runtime_error_ptr;
}

__attribute__((__pure__,__nonnull__(1),__always_inline__))
static inline bool
cce_condition_is_runtime_error (cce_condition_t const * C)
{
  return cce_is_condition(C, &(cce_descriptor_runtime_error_ptr->descriptor));
}

/* ------------------------------------------------------------------ */

#define cce_condition_runtime_error(S)					\
  _Generic((S),								\
	   cce_location_t				*: (cce_condition_runtime_error_t const *)CCE_CLOC(S), \
	   cce_location_t[1]				 : (cce_condition_runtime_error_t const *)CCE_CLOC(S), \
	   cce_condition_t				*: (cce_condition_runtime_error_t const *)(S), \
	   cce_condition_runtime_error_t		*: (cce_condition_runtime_error_t const *)(S), \
	   cce_condition_t			const	*: (cce_condition_runtime_error_t const *)(S), \
	   cce_condition_runtime_error_t	const	*: (cce_condition_runtime_error_t const *)(S), \
	   cce_condition_t			const	* const: (cce_condition_runtime_error_t const *)(S), \
	   cce_condition_runtime_error_t	const	* const: (cce_condition_runtime_error_t const *)(S))


/** --------------------------------------------------------------------
 ** Exceptional condition objects: logic error exception.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_logic_error_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_logic_error_t {
  cce_condition_error_t	error;
};

cce_decl cce_descriptor_logic_error_t const * const	cce_descriptor_logic_error_ptr;
cce_decl cce_condition_logic_error_t  const * const	cce_condition_logic_error_ptr;

__attribute__((__always_inline__,__nonnull__(1)))
static inline void
cce_condition_init_logic_error (cce_condition_logic_error_t * C CCE_UNUSED)
{
}

__attribute__((__always_inline__,__const__))
static inline cce_condition_t const *
cce_condition_new_logic_error (void)
{
  return (cce_condition_t const *) cce_condition_logic_error_ptr;
}

__attribute__((__pure__,__nonnull__(1),__always_inline__))
static inline bool
cce_condition_is_logic_error (cce_condition_t const * C)
{
  return cce_is_condition(C, &(cce_descriptor_logic_error_ptr->descriptor));
}

/* ------------------------------------------------------------------ */

#define cce_condition_logic_error(S)					\
  _Generic((S),								\
	   cce_location_t			*: (cce_condition_logic_error_t const *)CCE_CLOC(S), \
	   cce_location_t[1]			 : (cce_condition_logic_error_t const *)CCE_CLOC(S), \
	   cce_condition_t			*: (cce_condition_logic_error_t const *)(S), \
	   cce_condition_logic_error_t		*: (cce_condition_logic_error_t const *)(S), \
	   cce_condition_t		const	*: (cce_condition_logic_error_t const *)(S), \
	   cce_condition_logic_error_t	const	*: (cce_condition_logic_error_t const *)(S), \
	   cce_condition_t		const	* const: (cce_condition_logic_error_t const *)(S), \
	   cce_condition_logic_error_t	const	* const: (cce_condition_logic_error_t const *)(S))


/** --------------------------------------------------------------------
 ** Exceptional condition objects: unreachable code exception.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_unreachable_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_unreachable_t {
  cce_condition_logic_error_t	logic_error;
  char const *			filename;
  char const *			funcname;
  int				linenum;
};

cce_decl cce_descriptor_unreachable_t const * const	cce_descriptor_unreachable_ptr;
cce_decl cce_condition_unreachable_t  const * const	cce_condition_unreachable_ptr;

cce_decl void cce_condition_init_unreachable (cce_condition_unreachable_t * C,
					      char const * const filename,
					      char const * const funcname,
					      int const linenum)
  __attribute__((__nonnull__(1,2,3)));

cce_decl cce_condition_t const * cce_condition_new_unreachable (cce_destination_t L,
								char const * const filename,
								char const * const funcname,
								int const linenum)
  __attribute__((__nonnull__(1,2,3),__returns_nonnull__));

#if (defined CCEXCEPTIONS_EXCLUDE_UNREACHABLE)
#  define cce_raise_unreachable(L)		/* empty */
#else
#  define cce_raise_unreachable(L)		\
     cce_raise((L), cce_condition_new_unreachable((L), __FILE__, __func__, __LINE__))
#endif

__attribute__((__pure__,__nonnull__(1),__always_inline__))
static inline bool
cce_condition_is_unreachable (cce_condition_t const * C)
{
  return cce_is_condition(C, &(cce_descriptor_unreachable_ptr->descriptor));
}

/* ------------------------------------------------------------------ */

#define cce_condition_unreachable(S)					\
  _Generic((S),								\
	   cce_location_t			*: (cce_condition_unreachable_t const *)CCE_CLOC(S), \
	   cce_location_t[1]			 : (cce_condition_unreachable_t const *)CCE_CLOC(S), \
	   cce_condition_t			*: (cce_condition_unreachable_t const *)(S), \
	   cce_condition_unreachable_t		*: (cce_condition_unreachable_t const *)(S), \
	   cce_condition_t		const	*: (cce_condition_unreachable_t const *)(S), \
	   cce_condition_unreachable_t	const	*: (cce_condition_unreachable_t const *)(S), \
	   cce_condition_t		const	* const: (cce_condition_unreachable_t const *)(S), \
	   cce_condition_unreachable_t	const	* const: (cce_condition_unreachable_t const *)(S))


/** --------------------------------------------------------------------
 ** Exceptional condition objects: unimplemented exception.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_unimplemented_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_unimplemented_t {
  cce_condition_logic_error_t	logic_error;
};

cce_decl cce_descriptor_unimplemented_t const * const	cce_descriptor_unimplemented_ptr;
cce_decl cce_condition_unimplemented_t const  * const	cce_condition_unimplemented_ptr;

__attribute__((__always_inline__,__nonnull__(1)))
static inline void
cce_condition_init_unimplemented (cce_condition_unimplemented_t * C)
{
  cce_condition_init_logic_error(&(C->logic_error));
}

__attribute__((__const__,__always_inline__))
static inline cce_condition_t const *
cce_condition_new_unimplemented (void)
{
  return (cce_condition_t const *) cce_condition_unimplemented_ptr;
}

__attribute__((__pure__,__nonnull__(1),__always_inline__)) static inline bool
cce_condition_is_unimplemented (cce_condition_t const * C)
{
  return cce_is_condition(C, &(cce_descriptor_unimplemented_ptr->descriptor));
}

/* ------------------------------------------------------------------ */

#define cce_condition_unimplemented(S)					\
  _Generic((S),								\
	   cce_location_t				*: (cce_condition_unimplemented_t const *)CCE_CLOC(S), \
	   cce_location_t[1]				 : (cce_condition_unimplemented_t const *)CCE_CLOC(S), \
	   cce_condition_t				*: (cce_condition_unimplemented_t const *)(S), \
	   cce_condition_unimplemented_t		*: (cce_condition_unimplemented_t const *)(S), \
	   cce_condition_t			const	*: (cce_condition_unimplemented_t const *)(S), \
	   cce_condition_unimplemented_t	const	*: (cce_condition_unimplemented_t const *)(S), \
	   cce_condition_t			const	* const: (cce_condition_unimplemented_t const *)(S), \
	   cce_condition_unimplemented_t	const	* const: (cce_condition_unimplemented_t const *)(S))


/** --------------------------------------------------------------------
 ** Exceptional condition objects: invalid function argument.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_invalid_argument_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_invalid_argument_t {
  cce_condition_logic_error_t	logic_error;
  /* Pointer to  a statically  allocated ASCIIZ string  representing the
     function name; usually generated with "__func__". */
  char const *		funcname;
  /* One-based index of the invalid argument. */
  unsigned		index;
};

cce_decl cce_descriptor_invalid_argument_t const * cce_descriptor_invalid_argument_ptr;

cce_decl void cce_condition_init_invalid_argument (cce_condition_invalid_argument_t * C, char const * func, unsigned index);

cce_decl cce_condition_t const * cce_condition_new_invalid_argument (cce_destination_t L, char const * func, unsigned index)
  __attribute__((__nonnull__(1,2),__returns_nonnull__));

__attribute__((__pure__,__nonnull__(1),__always_inline__))
static inline bool
cce_condition_is_invalid_argument (cce_condition_t const * C)
{
  return cce_is_condition(C, &(cce_descriptor_invalid_argument_ptr->descriptor));
}

/* ------------------------------------------------------------------ */

#define cce_condition_invalid_argument(S)				\
  _Generic((S),								\
	   cce_location_t				*: (cce_condition_invalid_argument_t const *)CCE_CLOC(S), \
	   cce_location_t[1]				 : (cce_condition_invalid_argument_t const *)CCE_CLOC(S), \
	   cce_condition_t				*: (cce_condition_invalid_argument_t const *)(S), \
	   cce_condition_invalid_argument_t		*: (cce_condition_invalid_argument_t const *)(S), \
	   cce_condition_t			const	*: (cce_condition_invalid_argument_t const *)(S), \
	   cce_condition_invalid_argument_t	const	*: (cce_condition_invalid_argument_t const *)(S), \
	   cce_condition_t			const	* const: (cce_condition_invalid_argument_t const *)(S), \
	   cce_condition_invalid_argument_t	const	* const: (cce_condition_invalid_argument_t const *)(S))


/** --------------------------------------------------------------------
 ** Exceptional condition objects: errno exception.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_errno_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_errno_t {
  cce_condition_runtime_error_t	runtime_error;
  int			errnum;
  char const *		message;
};

cce_decl cce_descriptor_errno_t const * const cce_descriptor_errno_ptr;

cce_decl cce_condition_t const * cce_condition_new_errno (int code)
  __attribute__((__leaf__,__returns_nonnull__));

__attribute__((__returns_nonnull__,__always_inline__))
static inline cce_condition_t const *
cce_condition_new_errno_clear (void)
{
  int	errnum = errno;
  errno = 0;
  return cce_condition_new_errno(errnum);
}

__attribute__((__nonnull__(1),__always_inline__)) static inline bool
cce_condition_is_errno (cce_condition_t const * C)
{
  return cce_is_condition(C, &(cce_descriptor_errno_ptr->descriptor));
}

/* ------------------------------------------------------------------ */

#define cce_condition_errno(S)						\
  _Generic((S),								\
	   cce_location_t			*: (cce_condition_errno_t const *)CCE_CLOC(S), \
	   cce_location_t[1]			 : (cce_condition_errno_t const *)CCE_CLOC(S), \
	   cce_condition_t			*: (cce_condition_errno_t const *)(S), \
	   cce_condition_errno_t		*: (cce_condition_errno_t const *)(S), \
	   cce_condition_t		const	*: (cce_condition_errno_t const *)(S), \
	   cce_condition_errno_t	const	*: (cce_condition_errno_t const *)(S), \
	   cce_condition_t		const	* const: (cce_condition_errno_t const *)(S), \
	   cce_condition_errno_t	const	* const: (cce_condition_errno_t const *)(S))

/* ------------------------------------------------------------------ */

__attribute__((__always_inline__,__pure__))
static inline int
cce_ref_condition_errno_errnum (cce_condition_t const * const C)
{
  CCE_PC(cce_condition_errno_t const, K, C);
  return K->errnum;
}

__attribute__((__always_inline__,__pure__,__returns_nonnull__))
static inline char const *
cce_ref_condition_errno_message (cce_condition_t const * const C)
{
  CCE_PC(cce_condition_errno_t const, K, C);
  return K->message;
}


/** --------------------------------------------------------------------
 ** Exceptional condition objects: mathematical error exception.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_math_error_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_math_error_t {
  cce_condition_runtime_error_t	runtime_error;
};

cce_decl cce_descriptor_math_error_t const * const	cce_descriptor_math_error_ptr;
cce_decl cce_condition_math_error_t  const * const	cce_condition_math_error_ptr;

__attribute__((__always_inline__,__nonnull__(1)))
static inline void
cce_condition_init_math_error (cce_condition_math_error_t * C)
{
  cce_condition_init_runtime_error(&(C->runtime_error));
}

__attribute__((__always_inline__,__const__))
static inline cce_condition_t const *
cce_condition_new_math_error (void)
{
  return (cce_condition_t const *) cce_condition_math_error_ptr;
}

__attribute__((__pure__,__nonnull__(1),__always_inline__))
static inline bool
cce_condition_is_math_error (cce_condition_t const * C)
{
  return cce_is_condition(C, &(cce_descriptor_math_error_ptr->descriptor));
}

/* ------------------------------------------------------------------ */

#define cce_condition_math_error(S)					\
  _Generic((S),								\
	   cce_location_t			*: (cce_condition_math_error_t const *)CCE_CLOC(S), \
	   cce_location_t[1]			 : (cce_condition_math_error_t const *)CCE_CLOC(S), \
	   cce_condition_t			*: (cce_condition_math_error_t const *)(S), \
	   cce_condition_math_error_t		*: (cce_condition_math_error_t const *)(S), \
	   cce_condition_t		const	*: (cce_condition_math_error_t const *)(S), \
	   cce_condition_math_error_t	const	*: (cce_condition_math_error_t const *)(S), \
	   cce_condition_t		const	* const: (cce_condition_math_error_t const *)(S), \
	   cce_condition_math_error_t	const	* const: (cce_condition_math_error_t const *)(S))


/** --------------------------------------------------------------------
 ** Exceptional condition objects: mathematical not-a-number exception.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_math_nan_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_math_nan_t {
  cce_condition_math_error_t	math_error;
};

cce_decl cce_descriptor_math_nan_t const * const	cce_descriptor_math_nan_ptr;
cce_decl cce_condition_math_nan_t  const * const	cce_condition_math_nan_ptr;

__attribute__((__always_inline__,__nonnull__(1)))
static inline void
cce_condition_init_math_nan (cce_condition_math_nan_t * C)
{
  cce_condition_init_math_error(&(C->math_error));
}

__attribute__((__always_inline__,__const__))
static inline cce_condition_t const *
cce_condition_new_math_nan (void)
{
  return (cce_condition_t const *) cce_condition_math_nan_ptr;
}

__attribute__((__pure__,__nonnull__(1),__always_inline__))
static inline bool
cce_condition_is_math_nan (cce_condition_t const * C)
{
  return cce_is_condition(C, &(cce_descriptor_math_nan_ptr->descriptor));
}

/* ------------------------------------------------------------------ */

#define cce_condition_math_nan(S)					\
  _Generic((S),								\
	   cce_location_t			*: (cce_condition_math_nan_t const *)CCE_CLOC(S), \
	   cce_location_t[1]			 : (cce_condition_math_nan_t const *)CCE_CLOC(S), \
	   cce_condition_t			*: (cce_condition_math_nan_t const *)(S), \
	   cce_condition_math_nan_t		*: (cce_condition_math_nan_t const *)(S), \
	   cce_condition_t		const	*: (cce_condition_math_nan_t const *)(S), \
	   cce_condition_math_nan_t	const	*: (cce_condition_math_nan_t const *)(S), \
	   cce_condition_t		const	* const: (cce_condition_math_nan_t const *)(S), \
	   cce_condition_math_nan_t	const	* const: (cce_condition_math_nan_t const *)(S))


/** --------------------------------------------------------------------
 ** Exceptional condition objects: mathematical not-a-number exception.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_math_infinity_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_math_infinity_t {
  cce_condition_math_error_t	math_error;
};

cce_decl cce_descriptor_math_infinity_t const * const	cce_descriptor_math_infinity_ptr;
cce_decl cce_condition_math_infinity_t  const * const	cce_condition_math_infinity_ptr;

__attribute__((__always_inline__,__nonnull__(1)))
static inline void
cce_condition_init_math_infinity (cce_condition_math_infinity_t * C)
{
  cce_condition_init_math_error(&(C->math_error));
}

__attribute__((__always_inline__,__const__))
static inline cce_condition_t const *
cce_condition_new_math_infinity (void)
{
  return (cce_condition_t const *) cce_condition_math_infinity_ptr;
}

__attribute__((__pure__,__nonnull__(1),__always_inline__))
static inline bool
cce_condition_is_math_infinity (cce_condition_t const * C)
{
  return cce_is_condition(C, &(cce_descriptor_math_infinity_ptr->descriptor));
}

/* ------------------------------------------------------------------ */

#define cce_condition_math_infinity(S)					\
  _Generic((S),								\
	   cce_location_t				*: (cce_condition_math_infinity_t const *)CCE_CLOC(S), \
	   cce_location_t[1]				 : (cce_condition_math_infinity_t const *)CCE_CLOC(S), \
	   cce_condition_t				*: (cce_condition_math_infinity_t const *)(S), \
	   cce_condition_math_infinity_t		*: (cce_condition_math_infinity_t const *)(S), \
	   cce_condition_t			const	*: (cce_condition_math_infinity_t const *)(S), \
	   cce_condition_math_infinity_t	const	*: (cce_condition_math_infinity_t const *)(S), \
	   cce_condition_t			const	* const: (cce_condition_math_infinity_t const *)(S), \
	   cce_condition_math_infinity_t	const	* const: (cce_condition_math_infinity_t const *)(S))


/** --------------------------------------------------------------------
 ** Exceptional condition objects: mathematical overflow exception.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_math_overflow_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_math_overflow_t {
  cce_condition_math_error_t	math_error;
};

cce_decl cce_descriptor_math_overflow_t const * const	cce_descriptor_math_overflow_ptr;
cce_decl cce_condition_math_overflow_t  const * const	cce_condition_math_overflow_ptr;

__attribute__((__always_inline__,__nonnull__(1)))
static inline void
cce_condition_init_math_overflow (cce_condition_math_overflow_t * C)
{
  cce_condition_init_math_error(&(C->math_error));
}

__attribute__((__always_inline__,__const__))
static inline cce_condition_t const *
cce_condition_new_math_overflow (void)
{
  return (cce_condition_t const *) cce_condition_math_overflow_ptr;
}

__attribute__((__pure__,__nonnull__(1),__always_inline__))
static inline bool
cce_condition_is_math_overflow (cce_condition_t const * C)
{
  return cce_is_condition(C, &(cce_descriptor_math_overflow_ptr->descriptor));
}

/* ------------------------------------------------------------------ */

#define cce_condition_math_overflow(S)					\
  _Generic((S),								\
	   cce_location_t				*: (cce_condition_math_overflow_t const *)CCE_CLOC(S), \
	   cce_location_t[1]				 : (cce_condition_math_overflow_t const *)CCE_CLOC(S), \
	   cce_condition_t				*: (cce_condition_math_overflow_t const *)(S), \
	   cce_condition_math_overflow_t		*: (cce_condition_math_overflow_t const *)(S), \
	   cce_condition_t			const	*: (cce_condition_math_overflow_t const *)(S), \
	   cce_condition_math_overflow_t	const	*: (cce_condition_math_overflow_t const *)(S), \
	   cce_condition_t			const	* const: (cce_condition_math_overflow_t const *)(S), \
	   cce_condition_math_overflow_t	const	* const: (cce_condition_math_overflow_t const *)(S))


/** --------------------------------------------------------------------
 ** Exceptional condition objects: mathematical underflow exception.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_math_underflow_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_math_underflow_t {
  cce_condition_math_error_t	math_error;
};

cce_decl cce_descriptor_math_underflow_t const * const	cce_descriptor_math_underflow_ptr;
cce_decl cce_condition_math_underflow_t  const * const	cce_condition_math_underflow_ptr;

__attribute__((__always_inline__,__nonnull__(1)))
static inline void
cce_condition_init_math_underflow (cce_condition_math_underflow_t * C)
{
  cce_condition_init_math_error(&(C->math_error));
}

__attribute__((__always_inline__,__const__))
static inline cce_condition_t const *
cce_condition_new_math_underflow (void)
{
  return (cce_condition_t const *) cce_condition_math_underflow_ptr;
}

__attribute__((__pure__,__nonnull__(1),__always_inline__))
static inline bool
cce_condition_is_math_underflow (cce_condition_t const * C)
{
  return cce_is_condition(C, &(cce_descriptor_math_underflow_ptr->descriptor));
}

/* ------------------------------------------------------------------ */

#define cce_condition_math_underflow(S)					\
  _Generic((S),								\
	   cce_location_t				*: (cce_condition_math_underflow_t const *)CCE_CLOC(S), \
	   cce_location_t[1]				 : (cce_condition_math_underflow_t const *)CCE_CLOC(S), \
	   cce_condition_t				*: (cce_condition_math_underflow_t const *)(S), \
	   cce_condition_math_underflow_t		*: (cce_condition_math_underflow_t const *)(S), \
	   cce_condition_t			const	*: (cce_condition_math_underflow_t const *)(S), \
	   cce_condition_math_underflow_t	const	*: (cce_condition_math_underflow_t const *)(S), \
	   cce_condition_t			const	* const: (cce_condition_math_underflow_t const *)(S), \
	   cce_condition_math_underflow_t	const	* const: (cce_condition_math_underflow_t const *)(S))


/** --------------------------------------------------------------------
 ** Locations.
 ** ----------------------------------------------------------------- */

struct cce_location_t {
  /* The buffer must be the first member of this struct. */
  sigjmp_buf			buffer;
  cce_condition_t const *	condition;
  cce_handler_t *		first_handler;
};

cce_decl void cce_location_init	(cce_destination_t here)
  __attribute__((__leaf__,__nonnull__(1)));

cce_decl void cce_p_raise (cce_destination_t L, cce_condition_t const * C)
  __attribute__((__noreturn__,__nonnull__(1)));

cce_decl void cce_p_retry (cce_destination_t L)
  __attribute__((__noreturn__,__nonnull__(1)));

/* ------------------------------------------------------------------ */

cce_decl int cce_trace_setjmp (cce_destination_t L, int rv, char const * filename, char const * funcname, int linenum)
  __attribute__((__nonnull__(1,3,4)));

cce_decl cce_condition_t const * cce_trace_raise (cce_condition_t const * C, char const * filename, char const * funcname, int linenum)
  __attribute__((__nonnull__(2,3)));

cce_decl cce_destination_t cce_trace_retry (cce_destination_t L, char const * filename, char const * funcname, int linenum)
  __attribute__((__nonnull__(1,2,3)));

/* ------------------------------------------------------------------ */

__attribute__((__always_inline__,__const__))
static inline int
cce_code (int const code)
{
  return (((CCE_ENTER == code) || (CCE_RETRY == code))? CCE_ENTER : code);
}

#define CCE_SETJMP(THERE)	__builtin_expect(cce_code(sigsetjmp((void *)(THERE),0)),CCE_ENTER)

#if (! defined CCEXCEPTIONS_TRACE)
#  define cce_location(HERE)		(cce_location_init(HERE), CCE_SETJMP(HERE))
#  define cce_raise(THERE, CONDITION)	cce_p_raise((THERE), (CONDITION))
#  define cce_retry(THERE)		cce_p_retry(THERE)
#else
#  define cce_location(HERE)		(cce_location_init(HERE), \
					 cce_trace_setjmp((HERE), CCE_SETJMP(HERE), __FILE__, __func__, __LINE__))
#  define cce_raise(THERE, CONDITION)	cce_p_raise((THERE), cce_trace_raise(CONDITION, __FILE__, __func__, __LINE__))
#  define cce_retry(THERE)		cce_p_retry(cce_trace_retry(THERE, __FILE__, __func__, __LINE__))
#endif


/** --------------------------------------------------------------------
 ** Running handlers and catching exceptions as final step.
 ** ----------------------------------------------------------------- */

__attribute__((__nonnull__(1),__always_inline__))
static inline void
cce_p_run_error_handlers_final (cce_destination_t L)
{
  cce_run_error_handlers(L);
  cce_condition_delete((cce_condition_t *)(L->condition));
}

__attribute__((__nonnull__(1),__always_inline__))
static inline void
cce_p_run_clean_handlers_final (cce_destination_t L)
{
  cce_run_clean_handlers(L);
  cce_condition_delete((cce_condition_t *)(L->condition));
}

cce_decl void cce_trace_final (cce_destination_t L, char const * filename, char const * funcname, int linenum)
  __attribute__((__nonnull__(1,2,3)));

#if (! defined CCEXCEPTIONS_TRACE)
#  define cce_run_error_handlers_final(L)	cce_p_run_error_handlers_final(L)
#  define cce_run_clean_handlers_final(L)	cce_p_run_clean_handlers_final(L)
#else
#  define cce_run_error_handlers_final(L)			\
  (cce_trace_final(L, __FILE__, __func__, __LINE__), cce_p_run_error_handlers_final(L))
#  define cce_run_clean_handlers_final(L)			\
  (cce_trace_final(L, __FILE__, __func__, __LINE__), cce_p_run_clean_handlers_final(L))
#endif

/* For compatibility with old versions. */
#define cce_run_cleanup_handlers_final		cce_run_clean_handlers_final


/** --------------------------------------------------------------------
 ** Running handlers and re-raising exceptions.
 ** ----------------------------------------------------------------- */

__attribute__((__always_inline__,__nonnull__(1,2),__noreturn__))
static inline void
cce_p_run_error_handlers_raise (cce_destination_t L, cce_destination_t upper_L)
{
  cce_run_error_handlers(L);
  cce_p_raise(upper_L, L->condition);
}

__attribute__((__always_inline__,__nonnull__(1,2),__noreturn__))
static inline void
cce_p_run_clean_handlers_raise (cce_destination_t L, cce_destination_t upper_L)
{
  cce_run_clean_handlers(L);
  cce_p_raise(upper_L, L->condition);
}

cce_decl void cce_trace_reraise (cce_destination_t L, char const * filename, char const * funcname, int linenum)
  __attribute__((__nonnull__(1,2,3)));

#if (! defined CCEXCEPTIONS_TRACE)
#  define cce_run_error_handlers_raise(L,upper_L)	cce_p_run_error_handlers_raise((L),(upper_L))
#  define cce_run_clean_handlers_raise(L,upper_L)	cce_p_run_clean_handlers_raise((L),(upper_L))
#else
#  define cce_run_error_handlers_raise(L,upper_L)			\
  (cce_trace_reraise(L, __FILE__, __func__, __LINE__), cce_p_run_error_handlers_raise((L), (upper_L)))
#  define cce_run_clean_handlers_raise(L,upper_L)			\
  (cce_trace_reraise(L, __FILE__, __func__, __LINE__), cce_p_run_clean_handlers_raise((L), (upper_L)))
#endif

/* For compatibility with old versions. */
#define cce_run_cleanup_handlers_raise		cce_run_clean_handlers_raise


/** --------------------------------------------------------------------
 ** System call wrappers: memory allocation.
 ** ----------------------------------------------------------------- */

cce_decl void * cce_sys_malloc (cce_destination_t L, size_t size)
  __attribute__((__nonnull__(1),__returns_nonnull__));

cce_decl void * cce_sys_realloc (cce_destination_t L, void * ptr, size_t newsize)
  __attribute__((__nonnull__(1),__returns_nonnull__));

cce_decl void * cce_sys_calloc (cce_destination_t L, size_t count, size_t eltsize)
  __attribute__((__nonnull__(1),__returns_nonnull__));

/* ------------------------------------------------------------------ */

cce_decl void cce_clean_handler_malloc_init (cce_destination_t L, cce_handler_t * H, void * pointer)
  __attribute__((__nonnull__(1,2,3)));

cce_decl void cce_error_handler_malloc_init (cce_destination_t L, cce_handler_t * H, void * pointer)
  __attribute__((__nonnull__(1,2,3)));

#define cce_handler_malloc_init(L,P_H,P) \
  _Generic((P_H),								\
	   cce_clean_handler_t	*: cce_clean_handler_malloc_init,	\
	   cce_error_handler_t	*: cce_error_handler_malloc_init)(L,&(P_H->handler),P)

/* ------------------------------------------------------------------ */

cce_decl void * cce_sys_malloc_guarded_clean (cce_location_t * L, cce_clean_handler_t * P_H, size_t size)
  __attribute__((__nonnull__(1,2),__returns_nonnull__));

cce_decl void * cce_sys_malloc_guarded_error (cce_location_t * L, cce_error_handler_t *   P_H, size_t size)
  __attribute__((__nonnull__(1,2),__returns_nonnull__));

#define cce_sys_malloc_guarded(L,P_H,size) \
  _Generic((P_H),								\
	   cce_clean_handler_t	*: cce_sys_malloc_guarded_clean,	\
	   cce_error_handler_t	*: cce_sys_malloc_guarded_error)(L,P_H,size)

/* ------------------------------------------------------------------ */

cce_decl void * cce_sys_realloc_guarded_clean (cce_location_t * L, cce_clean_handler_t * P_H, void * P, size_t newsize)
  __attribute__((__nonnull__(1,2),__returns_nonnull__));

cce_decl void * cce_sys_realloc_guarded_error (cce_location_t * L, cce_error_handler_t *   P_H, void * P, size_t newsize)
  __attribute__((__nonnull__(1,2),__returns_nonnull__));

#define cce_sys_realloc_guarded(L,P_H,old_P,newsize) \
  _Generic((P_H),								\
	   cce_clean_handler_t	*: cce_sys_realloc_guarded_clean,	\
	   cce_error_handler_t	*: cce_sys_realloc_guarded_error)(L,P_H,old_P,newsize)

/* ------------------------------------------------------------------ */

cce_decl void * cce_sys_calloc_guarded_clean (cce_location_t * L, cce_clean_handler_t * P_H, size_t count, size_t eltsize)
  __attribute__((__nonnull__(1,2),__returns_nonnull__));

cce_decl void * cce_sys_calloc_guarded_error (cce_location_t * L, cce_error_handler_t *   P_H, size_t count, size_t eltsize)
  __attribute__((__nonnull__(1,2),__returns_nonnull__));

#define cce_sys_calloc_guarded(L,P_H,count,eltsize) \
  _Generic((P_H),								\
	   cce_clean_handler_t	*: cce_sys_calloc_guarded_clean,	\
	   cce_error_handler_t	*: cce_sys_calloc_guarded_error)(L,P_H,count,eltsize)

/* ------------------------------------------------------------------ */

/* For compatibility with old versions. */
#define cce_cleanup_handler_malloc_init		cce_clean_handler_malloc_init
#define cce_sys_malloc_guarded_cleanup		cce_sys_malloc_guarded_clean
#define cce_sys_realloc_guarded_cleanup		cce_sys_realloc_guarded_clean
#define cce_sys_calloc_guarded_cleanup		cce_sys_calloc_guarded_clean


/** --------------------------------------------------------------------
 ** Generic macros.
 ** ----------------------------------------------------------------- */

/* Cast a pointer to condition descriptor. */
#define CCE_C001(S)	((cce_descriptor_t*)(S))

/* Cast a pointer to condition object. */
#define CCE_C002(S)	((cce_condition_t*)(S))

/* Cast a pointer  to condition object and evaluate to  a pointer to its
   descriptor. */
#define CCE_C003(S)	(CCE_C002(S)->descriptor)

/* Given  a pointer  to condition  object of  any type  or a  pointer to
   condition  descriptor of  any  type: return  a  pointer to  condition
   descriptor.

   This macro assumes  that: every struct in the  hierarchy of condition
   objects has  its parent struct  as first  field; every struct  in the
   hierarchy of  condition descriptors  has its  parent struct  as first
   field. */
#define cce_descriptor(S)						\
  _Generic((S),								\
	   cce_descriptor_t				*: (S),		\
	   cce_descriptor_root_t			*: CCE_C001(S), \
	   cce_descriptor_unknown_t			*: CCE_C001(S), \
	   cce_descriptor_break_t			*: CCE_C001(S), \
	   cce_descriptor_unimplemented_t		*: CCE_C001(S), \
	   cce_descriptor_error_t			*: CCE_C001(S), \
	   cce_descriptor_runtime_error_t		*: CCE_C001(S), \
	   cce_descriptor_logic_error_t			*: CCE_C001(S), \
	   cce_descriptor_invalid_argument_t		*: CCE_C001(S), \
	   cce_descriptor_unreachable_t			*: CCE_C001(S), \
	   cce_descriptor_errno_t			*: CCE_C001(S), \
	   cce_descriptor_math_error_t			*: CCE_C001(S), \
	   cce_descriptor_math_nan_t			*: CCE_C001(S), \
	   cce_descriptor_math_infinity_t		*: CCE_C001(S), \
	   cce_descriptor_math_overflow_t		*: CCE_C001(S), \
	   cce_descriptor_math_underflow_t		*: CCE_C001(S), \
									\
	   cce_descriptor_t			const   *: CCE_C001(S), \
	   cce_descriptor_root_t		const	*: CCE_C001(S), \
	   cce_descriptor_unknown_t		const	*: CCE_C001(S), \
	   cce_descriptor_break_t		const	*: CCE_C001(S), \
	   cce_descriptor_unimplemented_t	const	*: CCE_C001(S), \
	   cce_descriptor_error_t		const	*: CCE_C001(S), \
	   cce_descriptor_runtime_error_t	const	*: CCE_C001(S), \
	   cce_descriptor_logic_error_t		const	*: CCE_C001(S), \
	   cce_descriptor_invalid_argument_t	const	*: CCE_C001(S), \
	   cce_descriptor_unreachable_t		const	*: CCE_C001(S), \
	   cce_descriptor_errno_t		const	*: CCE_C001(S), \
	   cce_descriptor_math_error_t		const	*: CCE_C001(S), \
	   cce_descriptor_math_nan_t		const	*: CCE_C001(S), \
	   cce_descriptor_math_infinity_t	const	*: CCE_C001(S), \
	   cce_descriptor_math_overflow_t	const	*: CCE_C001(S), \
	   cce_descriptor_math_underflow_t	const	*: CCE_C001(S), \
									\
	   cce_descriptor_t			const	* const: CCE_C001(S), \
	   cce_descriptor_root_t		const	* const: CCE_C001(S), \
	   cce_descriptor_unknown_t		const	* const: CCE_C001(S), \
	   cce_descriptor_break_t		const	* const: CCE_C001(S), \
	   cce_descriptor_unimplemented_t	const	* const: CCE_C001(S), \
	   cce_descriptor_error_t		const	* const: CCE_C001(S), \
	   cce_descriptor_runtime_error_t	const	* const: CCE_C001(S), \
	   cce_descriptor_logic_error_t		const	* const: CCE_C001(S), \
	   cce_descriptor_invalid_argument_t	const	* const: CCE_C001(S), \
	   cce_descriptor_unreachable_t		const	* const: CCE_C001(S), \
	   cce_descriptor_errno_t		const	* const: CCE_C001(S), \
	   cce_descriptor_math_error_t		const	* const: CCE_C001(S), \
	   cce_descriptor_math_nan_t		const	* const: CCE_C001(S), \
	   cce_descriptor_math_infinity_t	const	* const: CCE_C001(S), \
	   cce_descriptor_math_overflow_t	const	* const: CCE_C001(S), \
	   cce_descriptor_math_underflow_t	const	* const: CCE_C001(S), \
									\
	   cce_condition_t				*: CCE_C003(S),	\
	   cce_condition_root_t				*: CCE_C003(S),	\
	   cce_condition_unknown_t			*: CCE_C003(S),	\
	   cce_condition_break_t			*: CCE_C003(S),	\
	   cce_condition_unimplemented_t		*: CCE_C003(S),	\
	   cce_condition_error_t			*: CCE_C003(S),	\
	   cce_condition_runtime_error_t		*: CCE_C003(S),	\
	   cce_condition_logic_error_t			*: CCE_C003(S),	\
	   cce_condition_invalid_argument_t		*: CCE_C003(S),	\
	   cce_condition_unreachable_t			*: CCE_C003(S),	\
	   cce_condition_errno_t			*: CCE_C003(S),	\
	   cce_condition_math_error_t			*: CCE_C003(S), \
	   cce_condition_math_nan_t			*: CCE_C003(S), \
	   cce_condition_math_infinity_t		*: CCE_C003(S), \
	   cce_condition_math_overflow_t		*: CCE_C003(S), \
	   cce_condition_math_underflow_t		*: CCE_C003(S), \
									\
	   cce_condition_t			const	*: CCE_C003(S),	\
	   cce_condition_root_t			const	*: CCE_C003(S),	\
	   cce_condition_unknown_t		const	*: CCE_C003(S),	\
	   cce_condition_break_t		const	*: CCE_C003(S),	\
	   cce_condition_unimplemented_t	const	*: CCE_C003(S),	\
	   cce_condition_error_t		const	*: CCE_C003(S),	\
	   cce_condition_runtime_error_t	const	*: CCE_C003(S),	\
	   cce_condition_logic_error_t		const	*: CCE_C003(S),	\
	   cce_condition_invalid_argument_t	const	*: CCE_C003(S),	\
	   cce_condition_unreachable_t		const	*: CCE_C003(S),	\
	   cce_condition_errno_t		const	*: CCE_C003(S),	\
	   cce_condition_math_error_t		const	*: CCE_C003(S), \
	   cce_condition_math_nan_t		const	*: CCE_C003(S), \
	   cce_condition_math_infinity_t	const	*: CCE_C003(S), \
	   cce_condition_math_overflow_t	const	*: CCE_C003(S), \
	   cce_condition_math_underflow_t	const	*: CCE_C003(S), \
									\
	   cce_condition_root_t			const	* const: CCE_C003(S),	\
	   cce_condition_unknown_t		const	* const: CCE_C003(S),	\
	   cce_condition_break_t		const	* const: CCE_C003(S),	\
	   cce_condition_unimplemented_t	const	* const: CCE_C003(S),	\
	   cce_condition_error_t		const	* const: CCE_C003(S),	\
	   cce_condition_runtime_error_t	const	* const: CCE_C003(S),	\
	   cce_condition_logic_error_t		const	* const: CCE_C003(S),	\
	   cce_condition_invalid_argument_t	const	* const: CCE_C003(S),	\
	   cce_condition_unreachable_t		const	* const: CCE_C003(S),	\
	   cce_condition_errno_t		const	* const: CCE_C003(S),	\
	   cce_condition_math_error_t		const	* const: CCE_C003(S),	\
	   cce_condition_math_nan_t		const	* const: CCE_C003(S),	\
	   cce_condition_math_infinity_t	const	* const: CCE_C003(S),	\
	   cce_condition_math_overflow_t	const	* const: CCE_C003(S),	\
	   cce_condition_math_underflow_t	const	* const: CCE_C003(S))


/* ------------------------------------------------------------------ */

#define cce_condition(S)						\
  _Generic((S),								\
	   cce_condition_t				*: (S),		\
	   cce_condition_root_t				*: CCE_C002(S), \
	   cce_condition_unknown_t			*: CCE_C002(S), \
	   cce_condition_break_t			*: CCE_C002(S), \
	   cce_condition_unimplemented_t		*: CCE_C002(S), \
	   cce_condition_error_t			*: CCE_C002(S), \
	   cce_condition_runtime_error_t		*: CCE_C002(S), \
	   cce_condition_logic_error_t			*: CCE_C002(S), \
	   cce_condition_invalid_argument_t		*: CCE_C002(S), \
	   cce_condition_unreachable_t			*: CCE_C002(S), \
	   cce_condition_errno_t			*: CCE_C002(S), \
	   cce_condition_math_error_t			*: CCE_C002(S), \
	   cce_condition_math_nan_t			*: CCE_C002(S), \
	   cce_condition_math_infinity_t		*: CCE_C002(S), \
	   cce_condition_math_overflow_t		*: CCE_C002(S), \
	   cce_condition_math_underflow_t		*: CCE_C002(S), \
									\
	   cce_condition_t			const	* const: CCE_C002(S), \
	   cce_condition_root_t			const	* const: CCE_C002(S), \
	   cce_condition_unknown_t		const	* const: CCE_C002(S), \
	   cce_condition_break_t		const	* const: CCE_C002(S), \
	   cce_condition_unimplemented_t	const	* const: CCE_C002(S), \
	   cce_condition_error_t		const	* const: CCE_C002(S), \
	   cce_condition_runtime_error_t	const	* const: CCE_C002(S), \
	   cce_condition_logic_error_t		const	* const: CCE_C002(S), \
	   cce_condition_invalid_argument_t	const	* const: CCE_C002(S), \
	   cce_condition_unreachable_t		const	* const: CCE_C002(S), \
	   cce_condition_errno_t		const	* const: CCE_C002(S), \
	   cce_condition_math_error_t		const	* const: CCE_C002(S), \
	   cce_condition_math_nan_t		const	* const: CCE_C002(S), \
	   cce_condition_math_infinity_t	const	* const: CCE_C002(S), \
	   cce_condition_math_overflow_t	const	* const: CCE_C002(S), \
	   cce_condition_math_underflow_t	const	* const: CCE_C002(S), \
									\
	   cce_condition_t			const	*: CCE_C002(S), \
	   cce_condition_root_t			const	*: CCE_C002(S), \
	   cce_condition_unknown_t		const	*: CCE_C002(S), \
	   cce_condition_break_t		const	*: CCE_C002(S), \
	   cce_condition_unimplemented_t	const	*: CCE_C002(S), \
	   cce_condition_error_t		const	*: CCE_C002(S), \
	   cce_condition_runtime_error_t	const	*: CCE_C002(S), \
	   cce_condition_logic_error_t		const	*: CCE_C002(S), \
	   cce_condition_invalid_argument_t	const	*: CCE_C002(S), \
	   cce_condition_unreachable_t		const	*: CCE_C002(S), \
	   cce_condition_errno_t		const	*: CCE_C002(S), \
	   cce_condition_math_error_t		const	*: CCE_C002(S), \
	   cce_condition_math_nan_t		const	*: CCE_C002(S), \
	   cce_condition_math_infinity_t	const	*: CCE_C002(S), \
	   cce_condition_math_overflow_t	const	*: CCE_C002(S), \
	   cce_condition_math_underflow_t	const	*: CCE_C002(S), \
	   \
	   cce_location_t[1]				 : CCE_C002(CCE_CLOC(S)), \
	   cce_location_t				*: CCE_C002(CCE_CLOC(S)))


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* CCEXCEPTIONS_H */

/* end of file */
