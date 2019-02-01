/*
  Part of: CCExceptions
  Contents: public header file
  Date: Sat Dec 17, 2016

  Abstract

	This is the  main header: it must  be included in all the  source files using
	CCExceptions.  Notice that  the code needs the POSIX features,  so it defines
	the following symbol:

	   #define _POSIX_C_SOURCE 200809L

  Copyright (C) 2016-2019 Marco Maggi <marco.maggi-ipsu@poste.it>

  This program is free  software: you can redistribute it and/or  modify it under the
  terms of the  GNU Lesser General Public  License as published by  the Free Software
  Foundation, either version 3 of the License, or (at your option) any later version.

  This program  is distributed in the  hope that it  will be useful, but  WITHOUT ANY
  WARRANTY; without  even the implied  warranty of  MERCHANTABILITY or FITNESS  FOR A
  PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License along with
  this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CCEXCEPTIONS_H
#define CCEXCEPTIONS_H 1


/** --------------------------------------------------------------------
 ** Preliminary definitions.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
extern "C" {
#endif

/* The macro CCE_UNUSED indicates that a  function, function argument or variable may
   potentially be unused. Usage examples:

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

#include <stdlib.h>
#include <stdbool.h>
#include <setjmp.h>
#include <ccnames.h>


/** --------------------------------------------------------------------
 ** Constants.
 ** ----------------------------------------------------------------- */

typedef enum {
  /* This code represents the return value of the first evaluation of "setjmp()". */
  CCE_SUCCESS		= 0,
  CCE_ENTER		= 0,

  /* This  code represents  the return  value of  the "setjmp()"  evaluation after  a
     "cce_raise()" call. */
  CCE_ERROR		= 1,
  CCE_EXCEPT		= 1,

  /* This  code represents  the return  value of  the "setjmp()"  evaluation after  a
     "cce_retry()" call. */
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
typedef cce_location_t *			cce_destination_t;

typedef struct cce_descriptor_t			cce_descriptor_t;
typedef struct cce_condition_t			cce_condition_t;

typedef struct ccname_type(cce_descriptor_t, root)		ccname_type(cce_descriptor_t, root);
typedef struct ccname_type(cce_condition_t,  root)		ccname_type(cce_condition_t,  root);

typedef struct ccname_type(cce_descriptor_t, unknown)		ccname_type(cce_descriptor_t, unknown);
typedef struct ccname_type(cce_condition_t,  unknown)		ccname_type(cce_condition_t,  unknown);

typedef struct ccname_type(cce_descriptor_t, break)		ccname_type(cce_descriptor_t, break);
typedef struct ccname_type(cce_condition_t,  break)		ccname_type(cce_condition_t,  break);

typedef struct ccname_type(cce_descriptor_t, unimplemented)	ccname_type(cce_descriptor_t, unimplemented);
typedef struct ccname_type(cce_condition_t,  unimplemented)	ccname_type(cce_condition_t,  unimplemented);

typedef struct ccname_type(cce_descriptor_t, error)		ccname_type(cce_descriptor_t, error);
typedef struct ccname_type(cce_condition_t,  error)		ccname_type(cce_condition_t,  error);

typedef struct ccname_type(cce_descriptor_t, runtime_error)	ccname_type(cce_descriptor_t, runtime_error);
typedef struct ccname_type(cce_condition_t,  runtime_error)	ccname_type(cce_condition_t,  runtime_error);

typedef struct ccname_type(cce_descriptor_t, logic_error)	ccname_type(cce_descriptor_t, logic_error);
typedef struct ccname_type(cce_condition_t,  logic_error)	ccname_type(cce_condition_t,  logic_error);

typedef struct ccname_type(cce_descriptor_t, invalid_argument)	ccname_type(cce_descriptor_t, invalid_argument);
typedef struct ccname_type(cce_condition_t,  invalid_argument)	ccname_type(cce_condition_t,  invalid_argument);

typedef struct ccname_type(cce_descriptor_t, unreachable)	ccname_type(cce_descriptor_t, unreachable);
typedef struct ccname_type(cce_condition_t,  unreachable)	ccname_type(cce_condition_t,  unreachable);

typedef struct ccname_type(cce_descriptor_t, math_error)	ccname_type(cce_descriptor_t, math_error);
typedef struct ccname_type(cce_condition_t,  math_error)		ccname_type(cce_condition_t,  math_error);

typedef struct ccname_type(cce_descriptor_t, math_nan)		ccname_type(cce_descriptor_t, math_nan);
typedef struct ccname_type(cce_condition_t,  math_nan)		ccname_type(cce_condition_t,  math_nan);

typedef struct ccname_type(cce_descriptor_t, math_infinity)	ccname_type(cce_descriptor_t, math_infinity);
typedef struct ccname_type(cce_condition_t,  math_infinity)	ccname_type(cce_condition_t,  math_infinity);

typedef struct ccname_type(cce_descriptor_t, math_overflow)	ccname_type(cce_descriptor_t, math_overflow);
typedef struct ccname_type(cce_condition_t,  math_overflow)	ccname_type(cce_condition_t,  math_overflow);

typedef struct ccname_type(cce_descriptor_t, math_underflow)	ccname_type(cce_descriptor_t, math_underflow);
typedef struct ccname_type(cce_condition_t,  math_underflow)	ccname_type(cce_condition_t,  math_underflow);

typedef struct ccname_type(cce_descriptor_t, system)		ccname_type(cce_descriptor_t, system);
typedef struct ccname_type(cce_condition_t,  system)		ccname_type(cce_condition_t,  system);


/** --------------------------------------------------------------------
 ** Error and clean handlers.
 ** ----------------------------------------------------------------- */

typedef void cce_handler_fun_t (cce_condition_t const * C, cce_handler_t * H);

struct cce_handler_t {
  bool			is_clean_handler;
  cce_handler_fun_t *	function;
  cce_handler_t *	next_handler;
  union {
    void *		pointer;
    char *		pathname;
    cce_destination_t	location;
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

__attribute__((__always_inline__,__nonnull__(1,2,3)))
static inline void
cce_handler_set (cce_handler_t * H, void * pointer, cce_handler_fun_t * fun)
{
  H->pointer	= pointer;
  H->function	= fun;
}

__attribute__((__always_inline__,__nonnull__(1,2,3)))
static inline void
cce_clean_handler_set (cce_clean_handler_t * H, void * pointer, cce_handler_fun_t * fun)
{
  cce_handler_set(&(H->handler), pointer, fun);
}

__attribute__((__always_inline__,__nonnull__(1,2,3)))
static inline void
cce_error_handler_set (cce_error_handler_t * H, void * pointer, cce_handler_fun_t * fun)
{
  cce_handler_set(&(H->handler), pointer, fun);
}

/* ------------------------------------------------------------------ */

cce_decl void cce_register_clean_handler (cce_destination_t L, cce_clean_handler_t * H)
  __attribute__((__leaf__,__nonnull__(1,2)));

cce_decl void cce_register_error_handler (cce_destination_t L, cce_error_handler_t * H)
  __attribute__((__leaf__,__nonnull__(1,2)));

cce_decl void cce_forget_handler (cce_destination_t L, cce_handler_t * H)
  __attribute__((__leaf__,__nonnull__(1,2)));

#define cce_register_handler(L,H)					\
  _Generic((H),								\
	   cce_clean_handler_t *: cce_register_clean_handler,		\
	   cce_error_handler_t *: cce_register_error_handler)((L),(H))

/* We do *not* set the "leaf" attribute for this function, because the clean handlers
   might modify data in the current compilation unit. */
cce_decl void cce_run_body_handlers (cce_destination_t L)
  __attribute__((__nonnull__(1)));

/* We do *not* set the "leaf" attribute for this function, because the error handlers
   might modify data in the current compilation unit. */
cce_decl void cce_run_catch_handlers (cce_destination_t L)
  __attribute__((__nonnull__(1)));


/** --------------------------------------------------------------------
 ** Exceptional condition descriptors.
 ** ----------------------------------------------------------------- */

typedef void ccname_method_type(cce_condition_t, release) (cce_condition_t * C);
typedef void ccname_method_type(cce_condition_t, final)   (cce_condition_t * C);
typedef char const * ccname_method_type(cce_condition_t, static_message) (cce_condition_t const * C);

struct cce_descriptor_t {
  cce_descriptor_t const				*parent;
  ccname_method_type(cce_condition_t, release)		*release;
  ccname_method_type(cce_condition_t, final)		*final;
  ccname_method_type(cce_condition_t, static_message)	*static_message;
};

struct cce_condition_t {
  cce_descriptor_t const	*descriptor;
};

/* ------------------------------------------------------------------ */

cce_decl void ccname_init(cce_condition_t) (cce_condition_t * C, cce_descriptor_t const * D)
  __attribute__((__leaf__,__nonnull__(1,2)));

cce_decl void ccname_final(cce_condition_t) (cce_condition_t * C)
  __attribute__((__leaf__,__nonnull__(1)));

cce_decl void ccname_delete(cce_condition_t) (cce_condition_t * C)
  __attribute__((__leaf__,__nonnull__(1)));

cce_decl bool ccname_is(cce_condition_t) (cce_condition_t const * C, cce_descriptor_t const * D)
  __attribute__((__leaf__,__nonnull__(1,2)));

cce_decl char const * cce_condition_static_message (cce_condition_t const * C)
  __attribute__((__leaf__,__nonnull__(1)));

/* ------------------------------------------------------------------ */

cce_decl bool cce_descriptor_child_and_ancestor (cce_descriptor_t const * child, cce_descriptor_t const * ancestor)
  __attribute__((__leaf__,__nonnull__(1,2)));


/** --------------------------------------------------------------------
 ** Exceptional condition objects: root exception.
 ** ----------------------------------------------------------------- */

struct ccname_type(cce_descriptor_t, root) {
  cce_descriptor_t	descriptor;
};

struct ccname_type(cce_condition_t, root) {
  cce_condition_t	condition;
};

cce_decl ccname_type(cce_descriptor_t, root) const * const cce_descriptor_root_ptr;

cce_decl void ccname_init(cce_condition_t, root) (ccname_type(cce_condition_t, root) * C CCE_UNUSED)
  __attribute__((__nonnull__(1)));

cce_decl bool ccname_is(cce_condition_t, root) (cce_condition_t const * C)
  __attribute__((__pure__,__nonnull__(1)));

cce_decl void cce_descriptor_set_root_parent (cce_descriptor_t * D)
  __attribute__((__nonnull__(1)));


/** --------------------------------------------------------------------
 ** Exceptional condition objects: unknown exception.
 ** ----------------------------------------------------------------- */

struct ccname_type(cce_descriptor_t, unknown) {
  cce_descriptor_t	descriptor;
};

struct ccname_type(cce_condition_t, unknown) {
  ccname_type(cce_condition_t, root)	root;
};

cce_decl ccname_type(cce_descriptor_t, unknown) const * const	cce_descriptor_unknown_ptr;
cce_decl ccname_type(cce_condition_t,  unknown) const * const	cce_condition_unknown_ptr;

cce_decl cce_condition_t const * ccname_new(cce_condition_t, unknown) (void)
  __attribute__((__const__,__returns_nonnull__));

cce_decl bool ccname_is(cce_condition_t, unknown) (cce_condition_t const * C)
  __attribute__((__pure__,__nonnull__(1)));

/* ------------------------------------------------------------------ */

#define cce_condition_unknown(S)					\
  _Generic((S),								\
	   cce_location_t			*: (ccname_type(cce_condition_t, unknown) const *)CCE_CLOC(S), \
	   cce_location_t[1]			 : (ccname_type(cce_condition_t, unknown) const *)CCE_CLOC(S), \
	   cce_condition_t			*: (ccname_type(cce_condition_t, unknown) const *)(S), \
	   ccname_type(cce_condition_t, unknown)		*: (ccname_type(cce_condition_t, unknown) const *)(S), \
	   cce_condition_t		const	*: (ccname_type(cce_condition_t, unknown) const *)(S), \
	   ccname_type(cce_condition_t, unknown)	const	*: (ccname_type(cce_condition_t, unknown) const *)(S), \
	   cce_condition_t		const	* const: (ccname_type(cce_condition_t, unknown) const *)(S), \
	   ccname_type(cce_condition_t, unknown)	const	* const: (ccname_type(cce_condition_t, unknown) const *)(S))


/** --------------------------------------------------------------------
 ** Exceptional condition objects: break exception.
 ** ----------------------------------------------------------------- */

struct ccname_type(cce_descriptor_t, break) {
  cce_descriptor_t	descriptor;
};

struct ccname_type(cce_condition_t, break) {
  ccname_type(cce_condition_t, root)	root;
};

cce_decl ccname_type(cce_descriptor_t, break) const * const	cce_descriptor_break_ptr;
cce_decl ccname_type(cce_condition_t,  break) const * const	cce_condition_break_ptr;

cce_decl void ccname_init(cce_condition_t, break) (ccname_type(cce_condition_t, break) * C)
  __attribute__((__nonnull__(1)));

cce_decl cce_condition_t const * ccname_new(cce_condition_t, break) (void)
  __attribute__((__const__,__returns_nonnull__));

cce_decl bool ccname_is(cce_condition_t, break) (cce_condition_t const * C)
  __attribute__((__pure__,__nonnull__(1)));

/* ------------------------------------------------------------------ */

#define cce_condition_break(S)					\
  _Generic((S),								\
	   cce_location_t			*: (ccname_type(cce_condition_t, break) const *)CCE_CLOC(S), \
	   cce_location_t[1]			 : (ccname_type(cce_condition_t, break) const *)CCE_CLOC(S), \
	   cce_condition_t			*: (ccname_type(cce_condition_t, break) const *)(S), \
	   ccname_type(cce_condition_t, break)		*: (ccname_type(cce_condition_t, break) const *)(S), \
	   cce_condition_t		const	*: (ccname_type(cce_condition_t, break) const *)(S), \
	   ccname_type(cce_condition_t, break)	const	*: (ccname_type(cce_condition_t, break) const *)(S), \
	   cce_condition_t		const	* const: (ccname_type(cce_condition_t, break) const *)(S), \
	   ccname_type(cce_condition_t, break)	const	* const: (ccname_type(cce_condition_t, break) const *)(S))


/** --------------------------------------------------------------------
 ** Exceptional condition objects: generic error exception.
 ** ----------------------------------------------------------------- */

struct ccname_type(cce_descriptor_t, error) {
  cce_descriptor_t	descriptor;
};

struct ccname_type(cce_condition_t, error) {
  ccname_type(cce_condition_t, root)	root;
};

cce_decl ccname_type(cce_descriptor_t, error) const * const	cce_descriptor_error_ptr;
cce_decl ccname_type(cce_condition_t,  error) const * const	cce_condition_error_ptr;

cce_decl void ccname_init(cce_condition_t, error) (ccname_type(cce_condition_t, error) * C)
  __attribute__((__nonnull__(1)));

cce_decl cce_condition_t const * ccname_new(cce_condition_t, error) (void)
  __attribute__((__const__,__returns_nonnull__));

cce_decl bool ccname_is(cce_condition_t, error) (cce_condition_t const * C)
  __attribute__((__pure__,__nonnull__(1)));

/* ------------------------------------------------------------------ */

#define cce_condition_error(S)						\
  _Generic((S),								\
	   cce_location_t			*: (ccname_type(cce_condition_t, error) const *)CCE_CLOC(S), \
	   cce_location_t[1]			 : (ccname_type(cce_condition_t, error) const *)CCE_CLOC(S), \
	   cce_condition_t			*: (ccname_type(cce_condition_t, error) const *)(S), \
	   ccname_type(cce_condition_t, error)		*: (ccname_type(cce_condition_t, error) const *)(S), \
	   cce_condition_t		const	*: (ccname_type(cce_condition_t, error) const *)(S), \
	   ccname_type(cce_condition_t, error)	const	*: (ccname_type(cce_condition_t, error) const *)(S), \
	   cce_condition_t		const	* const: (ccname_type(cce_condition_t, error) const *)(S), \
	   ccname_type(cce_condition_t, error)	const	* const: (ccname_type(cce_condition_t, error) const *)(S))


/** --------------------------------------------------------------------
 ** Exceptional condition objects: runtime error exception.
 ** ----------------------------------------------------------------- */

struct ccname_type(cce_descriptor_t, runtime_error) {
  cce_descriptor_t	descriptor;
};

struct ccname_type(cce_condition_t, runtime_error) {
  ccname_type(cce_condition_t, error)	error;
};

cce_decl ccname_type(cce_descriptor_t, runtime_error) const * const	cce_descriptor_runtime_error_ptr;
cce_decl ccname_type(cce_condition_t,  runtime_error) const * const	cce_condition_runtime_error_ptr;

cce_decl void ccname_init(cce_condition_t, runtime_error) (ccname_type(cce_condition_t, runtime_error) * C CCE_UNUSED)
  __attribute__((__nonnull__(1)));

cce_decl cce_condition_t const * ccname_new(cce_condition_t, runtime_error) (void)
  __attribute__((__const__,__returns_nonnull__));

cce_decl bool ccname_is(cce_condition_t, runtime_error) (cce_condition_t const * C)
  __attribute__((__pure__,__nonnull__(1)));

/* ------------------------------------------------------------------ */

#define cce_condition_runtime_error(S)					\
  _Generic((S),								\
	   cce_location_t				*: (ccname_type(cce_condition_t, runtime_error) const *)CCE_CLOC(S), \
	   cce_location_t[1]				 : (ccname_type(cce_condition_t, runtime_error) const *)CCE_CLOC(S), \
	   cce_condition_t				*: (ccname_type(cce_condition_t, runtime_error) const *)(S), \
	   ccname_type(cce_condition_t, runtime_error)		*: (ccname_type(cce_condition_t, runtime_error) const *)(S), \
	   cce_condition_t			const	*: (ccname_type(cce_condition_t, runtime_error) const *)(S), \
	   ccname_type(cce_condition_t, runtime_error)	const	*: (ccname_type(cce_condition_t, runtime_error) const *)(S), \
	   cce_condition_t			const	* const: (ccname_type(cce_condition_t, runtime_error) const *)(S), \
	   ccname_type(cce_condition_t, runtime_error)	const	* const: (ccname_type(cce_condition_t, runtime_error) const *)(S))


/** --------------------------------------------------------------------
 ** Exceptional condition objects: logic error exception.
 ** ----------------------------------------------------------------- */

struct ccname_type(cce_descriptor_t, logic_error) {
  cce_descriptor_t	descriptor;
};

struct ccname_type(cce_condition_t, logic_error) {
  ccname_type(cce_condition_t, error)	error;
};

cce_decl ccname_type(cce_descriptor_t, logic_error) const * const	cce_descriptor_logic_error_ptr;
cce_decl ccname_type(cce_condition_t,  logic_error) const * const	cce_condition_logic_error_ptr;

cce_decl void ccname_init(cce_condition_t, logic_error) (ccname_type(cce_condition_t, logic_error) * C CCE_UNUSED)
  __attribute__((__nonnull__(1)));

cce_decl cce_condition_t const * ccname_new(cce_condition_t, logic_error) (void)
  __attribute__((__const__,__returns_nonnull__));

cce_decl bool ccname_is(cce_condition_t, logic_error) (cce_condition_t const * C)
  __attribute__((__pure__,__nonnull__(1)));

/* ------------------------------------------------------------------ */

#define cce_condition_logic_error(S)					\
  _Generic((S),								\
	   cce_location_t			*: (ccname_type(cce_condition_t, logic_error) const *)CCE_CLOC(S), \
	   cce_location_t[1]			 : (ccname_type(cce_condition_t, logic_error) const *)CCE_CLOC(S), \
	   cce_condition_t			*: (ccname_type(cce_condition_t, logic_error) const *)(S), \
	   ccname_type(cce_condition_t, logic_error)		*: (ccname_type(cce_condition_t, logic_error) const *)(S), \
	   cce_condition_t		const	*: (ccname_type(cce_condition_t, logic_error) const *)(S), \
	   ccname_type(cce_condition_t, logic_error)	const	*: (ccname_type(cce_condition_t, logic_error) const *)(S), \
	   cce_condition_t		const	* const: (ccname_type(cce_condition_t, logic_error) const *)(S), \
	   ccname_type(cce_condition_t, logic_error)	const	* const: (ccname_type(cce_condition_t, logic_error) const *)(S))


/** --------------------------------------------------------------------
 ** Exceptional condition objects: unreachable code exception.
 ** ----------------------------------------------------------------- */

struct ccname_type(cce_descriptor_t, unreachable) {
  cce_descriptor_t	descriptor;
};

struct ccname_type(cce_condition_t, unreachable) {
  ccname_type(cce_condition_t, logic_error)	logic_error;
  char const *			filename;
  char const *			funcname;
  int				linenum;
};

cce_decl ccname_type(cce_descriptor_t, unreachable) const * const	cce_descriptor_unreachable_ptr;
cce_decl ccname_type(cce_condition_t,  unreachable) const * const	cce_condition_unreachable_ptr;

cce_decl void ccname_init(cce_condition_t, unreachable) (ccname_type(cce_condition_t, unreachable) * C,
							 char const * const filename,
							 char const * const funcname,
							 int const linenum)
  __attribute__((__nonnull__(1,2,3)));

cce_decl cce_condition_t const * ccname_new(cce_condition_t, unreachable) (cce_destination_t L,
									   char const * const filename,
									   char const * const funcname,
									   int const linenum)
  __attribute__((__nonnull__(1,2,3),__returns_nonnull__));

#if (defined CCEXCEPTIONS_EXCLUDE_UNREACHABLE)
#  define cce_raise_unreachable(L)		/* empty */
#else
#  define cce_raise_unreachable(L)		\
     cce_raise((L), ccname_new(cce_condition_t, unreachable)((L), __FILE__, __func__, __LINE__))
#endif

cce_decl bool ccname_is(cce_condition_t, unreachable) (cce_condition_t const * C)
  __attribute__((__pure__,__nonnull__(1)));

/* ------------------------------------------------------------------ */

#define cce_condition_unreachable(S)					\
  _Generic((S),								\
	   cce_location_t			*: (ccname_type(cce_condition_t, unreachable) const *)CCE_CLOC(S), \
	   cce_location_t[1]			 : (ccname_type(cce_condition_t, unreachable) const *)CCE_CLOC(S), \
	   cce_condition_t			*: (ccname_type(cce_condition_t, unreachable) const *)(S), \
	   ccname_type(cce_condition_t, unreachable)		*: (ccname_type(cce_condition_t, unreachable) const *)(S), \
	   cce_condition_t		const	*: (ccname_type(cce_condition_t, unreachable) const *)(S), \
	   ccname_type(cce_condition_t, unreachable)	const	*: (ccname_type(cce_condition_t, unreachable) const *)(S), \
	   cce_condition_t		const	* const: (ccname_type(cce_condition_t, unreachable) const *)(S), \
	   ccname_type(cce_condition_t, unreachable)	const	* const: (ccname_type(cce_condition_t, unreachable) const *)(S))


/** --------------------------------------------------------------------
 ** Exceptional condition objects: unimplemented exception.
 ** ----------------------------------------------------------------- */

struct ccname_type(cce_descriptor_t, unimplemented) {
  cce_descriptor_t	descriptor;
};

struct ccname_type(cce_condition_t, unimplemented) {
  ccname_type(cce_condition_t, logic_error)	logic_error;
};

cce_decl ccname_type(cce_descriptor_t, unimplemented) const * const	cce_descriptor_unimplemented_ptr;
cce_decl ccname_type(cce_condition_t, unimplemented) const  * const	cce_condition_unimplemented_ptr;

cce_decl void ccname_init(cce_condition_t, unimplemented) (ccname_type(cce_condition_t, unimplemented) * C)
  __attribute__((__nonnull__(1)));

cce_decl cce_condition_t const * ccname_new(cce_condition_t, unimplemented) (void)
  __attribute__((__const__,__returns_nonnull__));

cce_decl bool ccname_is(cce_condition_t, unimplemented) (cce_condition_t const * C)
  __attribute__((__pure__,__nonnull__(1)));

/* ------------------------------------------------------------------ */

#define cce_condition_unimplemented(S)					\
  _Generic((S),								\
	   cce_location_t				*: (ccname_type(cce_condition_t, unimplemented) const *)CCE_CLOC(S), \
	   cce_location_t[1]				 : (ccname_type(cce_condition_t, unimplemented) const *)CCE_CLOC(S), \
	   cce_condition_t				*: (ccname_type(cce_condition_t, unimplemented) const *)(S), \
	   ccname_type(cce_condition_t, unimplemented)		*: (ccname_type(cce_condition_t, unimplemented) const *)(S), \
	   cce_condition_t			const	*: (ccname_type(cce_condition_t, unimplemented) const *)(S), \
	   ccname_type(cce_condition_t, unimplemented)	const	*: (ccname_type(cce_condition_t, unimplemented) const *)(S), \
	   cce_condition_t			const	* const: (ccname_type(cce_condition_t, unimplemented) const *)(S), \
	   ccname_type(cce_condition_t, unimplemented)	const	* const: (ccname_type(cce_condition_t, unimplemented) const *)(S))


/** --------------------------------------------------------------------
 ** Exceptional condition objects: invalid function argument.
 ** ----------------------------------------------------------------- */

struct ccname_type(cce_descriptor_t, invalid_argument) {
  cce_descriptor_t	descriptor;
};

struct ccname_type(cce_condition_t, invalid_argument) {
  ccname_type(cce_condition_t, logic_error)	logic_error;
  /* Pointer to a statically allocated  ASCIIZ string representing the function name;
     usually generated with "__func__". */
  char const *		funcname;
  /* One-based index of the invalid argument. */
  unsigned		index;
};

cce_decl ccname_type(cce_descriptor_t, invalid_argument) const * cce_descriptor_invalid_argument_ptr;

cce_decl void ccname_init(cce_condition_t, invalid_argument)
  (ccname_type(cce_condition_t, invalid_argument) * C, char const * func, unsigned index)
  __attribute__((__nonnull__(1,2)));

cce_decl cce_condition_t const * ccname_new(cce_condition_t, invalid_argument) (cce_destination_t L, char const * func, unsigned index)
  __attribute__((__nonnull__(1,2),__returns_nonnull__));

cce_decl bool ccname_is(cce_condition_t, invalid_argument) (cce_condition_t const * C)
  __attribute__((__pure__,__nonnull__(1)));

#define cce_check_argument(L,EXPR,ARGNUM) \
  if (! (EXPR)) { cce_raise((L), ccname_new(cce_condition_t, invalid_argument)((L), __func__, (ARGNUM))); }

/* ------------------------------------------------------------------ */

#define cce_condition_invalid_argument(S)				\
  _Generic((S),								\
	   cce_location_t				*: (ccname_type(cce_condition_t, invalid_argument) const *)CCE_CLOC(S), \
	   cce_location_t[1]				 : (ccname_type(cce_condition_t, invalid_argument) const *)CCE_CLOC(S), \
	   cce_condition_t				*: (ccname_type(cce_condition_t, invalid_argument) const *)(S), \
	   ccname_type(cce_condition_t, invalid_argument)		*: (ccname_type(cce_condition_t, invalid_argument) const *)(S), \
	   cce_condition_t			const	*: (ccname_type(cce_condition_t, invalid_argument) const *)(S), \
	   ccname_type(cce_condition_t, invalid_argument)	const	*: (ccname_type(cce_condition_t, invalid_argument) const *)(S), \
	   cce_condition_t			const	* const: (ccname_type(cce_condition_t, invalid_argument) const *)(S), \
	   ccname_type(cce_condition_t, invalid_argument)	const	* const: (ccname_type(cce_condition_t, invalid_argument) const *)(S))


/** --------------------------------------------------------------------
 ** Exceptional condition objects: errno exception.
 ** ----------------------------------------------------------------- */

struct ccname_type(cce_descriptor_t, system) {
  cce_descriptor_t	descriptor;
};

struct ccname_type(cce_condition_t, system) {
  ccname_type(cce_condition_t, runtime_error)	runtime_error;
  int			errnum;
  char const *		message;
};

cce_decl ccname_type(cce_descriptor_t, system) const * const cce_descriptor_system_ptr;

cce_decl cce_condition_t const * ccname_new(cce_condition_t, system) (int code)
  __attribute__((__leaf__,__returns_nonnull__));

cce_decl cce_condition_t const * ccname_new(cce_condition_t, system_clear) (void)
  __attribute__((__returns_nonnull__));

cce_decl bool ccname_is(cce_condition_t, system) (cce_condition_t const * C)
  __attribute__((__nonnull__(1)));

/* ------------------------------------------------------------------ */

#define cce_condition_system(S)						\
  _Generic((S),								\
	   cce_location_t			*: (ccname_type(cce_condition_t, system) const *)CCE_CLOC(S), \
	   cce_location_t[1]			 : (ccname_type(cce_condition_t, system) const *)CCE_CLOC(S), \
	   cce_condition_t			*: (ccname_type(cce_condition_t, system) const *)(S), \
	   ccname_type(cce_condition_t, system)		*: (ccname_type(cce_condition_t, system) const *)(S), \
	   cce_condition_t		const	*: (ccname_type(cce_condition_t, system) const *)(S), \
	   ccname_type(cce_condition_t, system)	const	*: (ccname_type(cce_condition_t, system) const *)(S), \
	   cce_condition_t		const	* const: (ccname_type(cce_condition_t, system) const *)(S), \
	   ccname_type(cce_condition_t, system)	const	* const: (ccname_type(cce_condition_t, system) const *)(S))

/* ------------------------------------------------------------------ */

__attribute__((__always_inline__,__pure__))
static inline int
cce_condition_ref_system_errnum (cce_condition_t const * const C)
{
  CCE_PC(ccname_type(cce_condition_t, system) const, K, C);
  return K->errnum;
}

__attribute__((__always_inline__,__pure__,__returns_nonnull__))
static inline char const *
cce_condition_ref_system_message (cce_condition_t const * const C)
{
  CCE_PC(ccname_type(cce_condition_t, system) const, K, C);
  return K->message;
}


/** --------------------------------------------------------------------
 ** Exceptional condition objects: mathematical error exception.
 ** ----------------------------------------------------------------- */

struct ccname_type(cce_descriptor_t, math_error) {
  cce_descriptor_t	descriptor;
};

struct ccname_type(cce_condition_t, math_error) {
  ccname_type(cce_condition_t, runtime_error)	runtime_error;
};

cce_decl ccname_type(cce_descriptor_t, math_error) const * const	cce_descriptor_math_error_ptr;
cce_decl ccname_type(cce_condition_t,  math_error) const * const	cce_condition_math_error_ptr;

cce_decl void ccname_init(cce_condition_t, math_error) (ccname_type(cce_condition_t, math_error) * C)
  __attribute__((__nonnull__(1)));

cce_decl cce_condition_t const * ccname_new(cce_condition_t, math_error) (void)
  __attribute__((__const__,__returns_nonnull__));

cce_decl bool ccname_is(cce_condition_t, math_error) (cce_condition_t const * C)
  __attribute__((__pure__,__nonnull__(1)));

/* ------------------------------------------------------------------ */

#define cce_condition_math_error(S)					\
  _Generic((S),								\
	   cce_location_t			*: (ccname_type(cce_condition_t, math_error) const *)CCE_CLOC(S), \
	   cce_location_t[1]			 : (ccname_type(cce_condition_t, math_error) const *)CCE_CLOC(S), \
	   cce_condition_t			*: (ccname_type(cce_condition_t, math_error) const *)(S), \
	   ccname_type(cce_condition_t, math_error)		*: (ccname_type(cce_condition_t, math_error) const *)(S), \
	   cce_condition_t		const	*: (ccname_type(cce_condition_t, math_error) const *)(S), \
	   ccname_type(cce_condition_t, math_error)	const	*: (ccname_type(cce_condition_t, math_error) const *)(S), \
	   cce_condition_t		const	* const: (ccname_type(cce_condition_t, math_error) const *)(S), \
	   ccname_type(cce_condition_t, math_error)	const	* const: (ccname_type(cce_condition_t, math_error) const *)(S))


/** --------------------------------------------------------------------
 ** Exceptional condition objects: mathematical not-a-number exception.
 ** ----------------------------------------------------------------- */

struct ccname_type(cce_descriptor_t, math_nan) {
  cce_descriptor_t	descriptor;
};

struct ccname_type(cce_condition_t, math_nan) {
  ccname_type(cce_condition_t, math_error)	math_error;
};

cce_decl ccname_type(cce_descriptor_t, math_nan) const * const	cce_descriptor_math_nan_ptr;
cce_decl ccname_type(cce_condition_t,  math_nan) const * const	cce_condition_math_nan_ptr;

cce_decl void ccname_init(cce_condition_t, math_nan) (ccname_type(cce_condition_t, math_nan) * C)
  __attribute__((__nonnull__(1)));

cce_decl cce_condition_t const * ccname_new(cce_condition_t, math_nan) (void)
  __attribute__((__const__,__returns_nonnull__));

cce_decl bool ccname_is(cce_condition_t, math_nan) (cce_condition_t const * C)
  __attribute__((__pure__,__nonnull__(1)));

/* ------------------------------------------------------------------ */

#define cce_condition_math_nan(S)					\
  _Generic((S),								\
	   cce_location_t			*: (ccname_type(cce_condition_t, math_nan) const *)CCE_CLOC(S), \
	   cce_location_t[1]			 : (ccname_type(cce_condition_t, math_nan) const *)CCE_CLOC(S), \
	   cce_condition_t			*: (ccname_type(cce_condition_t, math_nan) const *)(S), \
	   ccname_type(cce_condition_t, math_nan)		*: (ccname_type(cce_condition_t, math_nan) const *)(S), \
	   cce_condition_t		const	*: (ccname_type(cce_condition_t, math_nan) const *)(S), \
	   ccname_type(cce_condition_t, math_nan)	const	*: (ccname_type(cce_condition_t, math_nan) const *)(S), \
	   cce_condition_t		const	* const: (ccname_type(cce_condition_t, math_nan) const *)(S), \
	   ccname_type(cce_condition_t, math_nan)	const	* const: (ccname_type(cce_condition_t, math_nan) const *)(S))


/** --------------------------------------------------------------------
 ** Exceptional condition objects: mathematical infinity exception.
 ** ----------------------------------------------------------------- */

struct ccname_type(cce_descriptor_t, math_infinity) {
  cce_descriptor_t	descriptor;
};

struct ccname_type(cce_condition_t, math_infinity) {
  ccname_type(cce_condition_t, math_error)	math_error;
};

cce_decl ccname_type(cce_descriptor_t, math_infinity) const * const	cce_descriptor_math_infinity_ptr;
cce_decl ccname_type(cce_condition_t, math_infinity)  const * const	cce_condition_math_infinity_ptr;

cce_decl void ccname_init(cce_condition_t, math_infinity) (ccname_type(cce_condition_t, math_infinity) * C)
  __attribute__((__nonnull__(1)));

cce_decl cce_condition_t const * ccname_new(cce_condition_t, math_infinity) (void)
  __attribute__((__const__,__returns_nonnull__));

cce_decl bool ccname_is(cce_condition_t, math_infinity) (cce_condition_t const * C)
  __attribute__((__pure__,__nonnull__(1)));

/* ------------------------------------------------------------------ */

#define cce_condition_math_infinity(S)					\
  _Generic((S),								\
	   cce_location_t				*: (ccname_type(cce_condition_t, math_infinity) const *)CCE_CLOC(S), \
	   cce_location_t[1]				 : (ccname_type(cce_condition_t, math_infinity) const *)CCE_CLOC(S), \
	   cce_condition_t				*: (ccname_type(cce_condition_t, math_infinity) const *)(S), \
	   ccname_type(cce_condition_t, math_infinity)		*: (ccname_type(cce_condition_t, math_infinity) const *)(S), \
	   cce_condition_t			const	*: (ccname_type(cce_condition_t, math_infinity) const *)(S), \
	   ccname_type(cce_condition_t, math_infinity)	const	*: (ccname_type(cce_condition_t, math_infinity) const *)(S), \
	   cce_condition_t			const	* const: (ccname_type(cce_condition_t, math_infinity) const *)(S), \
	   ccname_type(cce_condition_t, math_infinity)	const	* const: (ccname_type(cce_condition_t, math_infinity) const *)(S))


/** --------------------------------------------------------------------
 ** Exceptional condition objects: mathematical overflow exception.
 ** ----------------------------------------------------------------- */

struct ccname_type(cce_descriptor_t, math_overflow) {
  cce_descriptor_t	descriptor;
};

struct ccname_type(cce_condition_t, math_overflow) {
  ccname_type(cce_condition_t, math_error)	math_error;
};

cce_decl ccname_type(cce_descriptor_t, math_overflow) const * const	cce_descriptor_math_overflow_ptr;
cce_decl ccname_type(cce_condition_t,  math_overflow) const * const	cce_condition_math_overflow_ptr;

cce_decl void ccname_init(cce_condition_t, math_overflow) (ccname_type(cce_condition_t, math_overflow) * C)
  __attribute__((__nonnull__(1)));

cce_decl cce_condition_t const * ccname_new(cce_condition_t, math_overflow) (void)
  __attribute__((__const__,__returns_nonnull__));

cce_decl bool ccname_is(cce_condition_t, math_overflow) (cce_condition_t const * C)
  __attribute__((__pure__,__nonnull__(1)));

/* ------------------------------------------------------------------ */

#define cce_condition_math_overflow(S)					\
  _Generic((S),								\
	   cce_location_t				*: (ccname_type(cce_condition_t, math_overflow) const *)CCE_CLOC(S), \
	   cce_location_t[1]				 : (ccname_type(cce_condition_t, math_overflow) const *)CCE_CLOC(S), \
	   cce_condition_t				*: (ccname_type(cce_condition_t, math_overflow) const *)(S), \
	   ccname_type(cce_condition_t, math_overflow)		*: (ccname_type(cce_condition_t, math_overflow) const *)(S), \
	   cce_condition_t			const	*: (ccname_type(cce_condition_t, math_overflow) const *)(S), \
	   ccname_type(cce_condition_t, math_overflow)	const	*: (ccname_type(cce_condition_t, math_overflow) const *)(S), \
	   cce_condition_t			const	* const: (ccname_type(cce_condition_t, math_overflow) const *)(S), \
	   ccname_type(cce_condition_t, math_overflow)	const	* const: (ccname_type(cce_condition_t, math_overflow) const *)(S))


/** --------------------------------------------------------------------
 ** Exceptional condition objects: mathematical underflow exception.
 ** ----------------------------------------------------------------- */

struct ccname_type(cce_descriptor_t, math_underflow) {
  cce_descriptor_t	descriptor;
};

struct ccname_type(cce_condition_t, math_underflow) {
  ccname_type(cce_condition_t, math_error)	math_error;
};

cce_decl ccname_type(cce_descriptor_t, math_underflow) const * const	cce_descriptor_math_underflow_ptr;
cce_decl ccname_type(cce_condition_t,  math_underflow) const * const	cce_condition_math_underflow_ptr;

cce_decl void ccname_init(cce_condition_t, math_underflow) (ccname_type(cce_condition_t, math_underflow) * C)
  __attribute__((__nonnull__(1)));

cce_decl cce_condition_t const * ccname_new(cce_condition_t, math_underflow) (void)
  __attribute__((__const__,__returns_nonnull__));

cce_decl bool ccname_is(cce_condition_t, math_underflow) (cce_condition_t const * C)
  __attribute__((__pure__,__nonnull__(1)));

/* ------------------------------------------------------------------ */

#define cce_condition_math_underflow(S)					\
  _Generic((S),								\
	   cce_location_t				*: (ccname_type(cce_condition_t, math_underflow) const *)CCE_CLOC(S), \
	   cce_location_t[1]				 : (ccname_type(cce_condition_t, math_underflow) const *)CCE_CLOC(S), \
	   cce_condition_t				*: (ccname_type(cce_condition_t, math_underflow) const *)(S), \
	   ccname_type(cce_condition_t, math_underflow)		*: (ccname_type(cce_condition_t, math_underflow) const *)(S), \
	   cce_condition_t			const	*: (ccname_type(cce_condition_t, math_underflow) const *)(S), \
	   ccname_type(cce_condition_t, math_underflow)	const	*: (ccname_type(cce_condition_t, math_underflow) const *)(S), \
	   cce_condition_t			const	* const: (ccname_type(cce_condition_t, math_underflow) const *)(S), \
	   ccname_type(cce_condition_t, math_underflow)	const	* const: (ccname_type(cce_condition_t, math_underflow) const *)(S))


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

cce_decl void cce_p_run_catch_handlers_final (cce_destination_t L)
  __attribute__((__nonnull__(1)));

cce_decl void cce_p_run_body_handlers_final (cce_destination_t L)
  __attribute__((__nonnull__(1)));

cce_decl void cce_trace_final (cce_destination_t L, char const * filename, char const * funcname, int linenum)
  __attribute__((__nonnull__(1,2,3)));

#if (! defined CCEXCEPTIONS_TRACE)
#  define cce_run_body_handlers_final(L)	cce_p_run_body_handlers_final(L)
#  define cce_run_catch_handlers_final(L)	cce_p_run_catch_handlers_final(L)
#else
#  define cce_run_body_handlers_final(L)			\
  (cce_trace_final(L, __FILE__, __func__, __LINE__), cce_p_run_body_handlers_final(L))
#  define cce_run_catch_handlers_final(L)			\
  (cce_trace_final(L, __FILE__, __func__, __LINE__), cce_p_run_catch_handlers_final(L))
#endif


/** --------------------------------------------------------------------
 ** Running handlers and re-raising exceptions.
 ** ----------------------------------------------------------------- */

cce_decl void cce_p_run_catch_handlers_raise (cce_destination_t L, cce_destination_t upper_L)
  __attribute__((__nonnull__(1,2),__noreturn__));

cce_decl void cce_p_run_body_handlers_raise  (cce_destination_t L, cce_destination_t upper_L)
  __attribute__((__nonnull__(1,2),__noreturn__));

/* ------------------------------------------------------------------ */

cce_decl void cce_trace_reraise (cce_destination_t L, char const * filename, char const * funcname, int linenum)
  __attribute__((__nonnull__(1,2,3)));

#if (! defined CCEXCEPTIONS_TRACE)
#  define cce_run_catch_handlers_raise(L,upper_L)	cce_p_run_catch_handlers_raise((L),(upper_L))
#  define cce_run_body_handlers_raise(L,upper_L)	cce_p_run_body_handlers_raise((L),(upper_L))
#else
#  define cce_run_body_handlers_raise(L,upper_L)			\
  (cce_trace_reraise(L, __FILE__, __func__, __LINE__), cce_p_run_body_handlers_raise((L), (upper_L)))
#  define cce_run_catch_handlers_raise(L,upper_L)			\
  (cce_trace_reraise(L, __FILE__, __func__, __LINE__), cce_p_run_catch_handlers_raise((L), (upper_L)))
#endif


/** --------------------------------------------------------------------
 ** Registering handlers to run handlers.
 ** ----------------------------------------------------------------- */

cce_decl void cce_register_clean_handler_to_run_body_handlers  (cce_destination_t inner_L, cce_clean_handler_t * inner_H,
								cce_destination_t outer_L)
  __attribute__((__nonnull__(1,2,3)));

cce_decl void cce_register_clean_handler_to_run_catch_handlers (cce_destination_t inner_L, cce_clean_handler_t * inner_H,
								cce_destination_t outer_L)
  __attribute__((__nonnull__(1,2,3)));

cce_decl void cce_register_error_handler_to_run_body_handlers  (cce_destination_t inner_L, cce_error_handler_t * inner_H,
								cce_destination_t outer_L)
  __attribute__((__nonnull__(1,2,3)));

cce_decl void cce_register_error_handler_to_run_catch_handlers (cce_destination_t inner_L, cce_error_handler_t * inner_H,
								cce_destination_t outer_L)
  __attribute__((__nonnull__(1,2,3)));


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

cce_decl void cce_init_clean_handler_malloc (cce_destination_t L, cce_clean_handler_t * H, void * pointer)
  __attribute__((__nonnull__(1,2,3)));

cce_decl void cce_init_error_handler_malloc (cce_destination_t L, cce_error_handler_t * H, void * pointer)
  __attribute__((__nonnull__(1,2,3)));

#define cce_init_handler_malloc(L,P_H,P)				\
  _Generic((P_H),							\
	   cce_clean_handler_t	*: cce_init_clean_handler_malloc,	\
	   cce_error_handler_t	*: cce_init_error_handler_malloc)((L),(P_H),(P))

/* ------------------------------------------------------------------ */

cce_decl void * cce_sys_malloc_guarded_clean (cce_location_t * L, cce_clean_handler_t * P_H, size_t size)
  __attribute__((__nonnull__(1,2),__returns_nonnull__));

cce_decl void * cce_sys_malloc_guarded_error (cce_location_t * L, cce_error_handler_t *   P_H, size_t size)
  __attribute__((__nonnull__(1,2),__returns_nonnull__));

#define cce_sys_malloc_guarded(L,P_H,size)				\
  _Generic((P_H),							\
	   cce_clean_handler_t	*: cce_sys_malloc_guarded_clean,	\
	   cce_error_handler_t	*: cce_sys_malloc_guarded_error)((L),(P_H),(size))

/* ------------------------------------------------------------------ */

cce_decl void * cce_sys_realloc_guarded_clean (cce_location_t * L, cce_clean_handler_t * P_H, void * P, size_t newsize)
  __attribute__((__nonnull__(1,2),__returns_nonnull__));

cce_decl void * cce_sys_realloc_guarded_error (cce_location_t * L, cce_error_handler_t * P_H, void * P, size_t newsize)
  __attribute__((__nonnull__(1,2),__returns_nonnull__));

#define cce_sys_realloc_guarded(L,P_H,old_P,newsize)			\
  _Generic((P_H),							\
	   cce_clean_handler_t	*: cce_sys_realloc_guarded_clean,	\
	   cce_error_handler_t	*: cce_sys_realloc_guarded_error)((L),(P_H),(old_P),(newsize))

/* ------------------------------------------------------------------ */

cce_decl void * cce_sys_calloc_guarded_clean (cce_location_t * L, cce_clean_handler_t * P_H, size_t count, size_t eltsize)
  __attribute__((__nonnull__(1,2),__returns_nonnull__));

cce_decl void * cce_sys_calloc_guarded_error (cce_location_t * L, cce_error_handler_t * P_H, size_t count, size_t eltsize)
  __attribute__((__nonnull__(1,2),__returns_nonnull__));

#define cce_sys_calloc_guarded(L,P_H,count,eltsize)			\
  _Generic((P_H),							\
	   cce_clean_handler_t	*: cce_sys_calloc_guarded_clean,	\
	   cce_error_handler_t	*: cce_sys_calloc_guarded_error)((L),(P_H),(count),(eltsize))


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
	   ccname_type(cce_descriptor_t, root)			*: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, unknown)			*: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, break)			*: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, unimplemented)		*: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, error)			*: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, runtime_error)		*: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, logic_error)			*: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, invalid_argument)		*: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, unreachable)			*: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, system)			*: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, math_error)			*: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, math_nan)			*: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, math_infinity)		*: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, math_overflow)		*: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, math_underflow)		*: CCE_C001(S), \
									\
	   cce_descriptor_t			const   *: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, root)		const	*: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, unknown)		const	*: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, break)		const	*: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, unimplemented)	const	*: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, error)		const	*: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, runtime_error)	const	*: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, logic_error)		const	*: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, invalid_argument)	const	*: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, unreachable)		const	*: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, system)		const	*: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, math_error)		const	*: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, math_nan)		const	*: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, math_infinity)	const	*: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, math_overflow)	const	*: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, math_underflow)	const	*: CCE_C001(S), \
									\
	   cce_descriptor_t			const	* const: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, root)		const	* const: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, unknown)		const	* const: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, break)		const	* const: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, unimplemented)	const	* const: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, error)		const	* const: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, runtime_error)	const	* const: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, logic_error)		const	* const: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, invalid_argument)	const	* const: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, unreachable)		const	* const: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, system)		const	* const: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, math_error)		const	* const: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, math_nan)		const	* const: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, math_infinity)	const	* const: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, math_overflow)	const	* const: CCE_C001(S), \
	   ccname_type(cce_descriptor_t, math_underflow)	const	* const: CCE_C001(S), \
									\
	   cce_condition_t				*: CCE_C003(S),	\
	   ccname_type(cce_condition_t, root)				*: CCE_C003(S),	\
	   ccname_type(cce_condition_t, unknown)			*: CCE_C003(S),	\
	   ccname_type(cce_condition_t, break)			*: CCE_C003(S),	\
	   ccname_type(cce_condition_t, unimplemented)		*: CCE_C003(S),	\
	   ccname_type(cce_condition_t, error)			*: CCE_C003(S),	\
	   ccname_type(cce_condition_t, runtime_error)		*: CCE_C003(S),	\
	   ccname_type(cce_condition_t, logic_error)			*: CCE_C003(S),	\
	   ccname_type(cce_condition_t, invalid_argument)		*: CCE_C003(S),	\
	   ccname_type(cce_condition_t, unreachable)			*: CCE_C003(S),	\
	   ccname_type(cce_condition_t, system)			*: CCE_C003(S),	\
	   ccname_type(cce_condition_t, math_error)			*: CCE_C003(S), \
	   ccname_type(cce_condition_t, math_nan)			*: CCE_C003(S), \
	   ccname_type(cce_condition_t, math_infinity)		*: CCE_C003(S), \
	   ccname_type(cce_condition_t, math_overflow)		*: CCE_C003(S), \
	   ccname_type(cce_condition_t, math_underflow)		*: CCE_C003(S), \
									\
	   cce_condition_t			const	*: CCE_C003(S),	\
	   ccname_type(cce_condition_t, root)			const	*: CCE_C003(S),	\
	   ccname_type(cce_condition_t, unknown)		const	*: CCE_C003(S),	\
	   ccname_type(cce_condition_t, break)		const	*: CCE_C003(S),	\
	   ccname_type(cce_condition_t, unimplemented)	const	*: CCE_C003(S),	\
	   ccname_type(cce_condition_t, error)		const	*: CCE_C003(S),	\
	   ccname_type(cce_condition_t, runtime_error)	const	*: CCE_C003(S),	\
	   ccname_type(cce_condition_t, logic_error)		const	*: CCE_C003(S),	\
	   ccname_type(cce_condition_t, invalid_argument)	const	*: CCE_C003(S),	\
	   ccname_type(cce_condition_t, unreachable)		const	*: CCE_C003(S),	\
	   ccname_type(cce_condition_t, system)		const	*: CCE_C003(S),	\
	   ccname_type(cce_condition_t, math_error)		const	*: CCE_C003(S), \
	   ccname_type(cce_condition_t, math_nan)		const	*: CCE_C003(S), \
	   ccname_type(cce_condition_t, math_infinity)	const	*: CCE_C003(S), \
	   ccname_type(cce_condition_t, math_overflow)	const	*: CCE_C003(S), \
	   ccname_type(cce_condition_t, math_underflow)	const	*: CCE_C003(S), \
									\
	   ccname_type(cce_condition_t, root)			const	* const: CCE_C003(S),	\
	   ccname_type(cce_condition_t, unknown)		const	* const: CCE_C003(S),	\
	   ccname_type(cce_condition_t, break)		const	* const: CCE_C003(S),	\
	   ccname_type(cce_condition_t, unimplemented)	const	* const: CCE_C003(S),	\
	   ccname_type(cce_condition_t, error)		const	* const: CCE_C003(S),	\
	   ccname_type(cce_condition_t, runtime_error)	const	* const: CCE_C003(S),	\
	   ccname_type(cce_condition_t, logic_error)		const	* const: CCE_C003(S),	\
	   ccname_type(cce_condition_t, invalid_argument)	const	* const: CCE_C003(S),	\
	   ccname_type(cce_condition_t, unreachable)		const	* const: CCE_C003(S),	\
	   ccname_type(cce_condition_t, system)		const	* const: CCE_C003(S),	\
	   ccname_type(cce_condition_t, math_error)		const	* const: CCE_C003(S),	\
	   ccname_type(cce_condition_t, math_nan)		const	* const: CCE_C003(S),	\
	   ccname_type(cce_condition_t, math_infinity)	const	* const: CCE_C003(S),	\
	   ccname_type(cce_condition_t, math_overflow)	const	* const: CCE_C003(S),	\
	   ccname_type(cce_condition_t, math_underflow)	const	* const: CCE_C003(S))


/* ------------------------------------------------------------------ */

#define cce_condition(S)						\
  _Generic((S),								\
	   cce_condition_t				*: (S),		\
	   ccname_type(cce_condition_t, root)				*: CCE_C002(S), \
	   ccname_type(cce_condition_t, unknown)			*: CCE_C002(S), \
	   ccname_type(cce_condition_t, break)			*: CCE_C002(S), \
	   ccname_type(cce_condition_t, unimplemented)		*: CCE_C002(S), \
	   ccname_type(cce_condition_t, error)			*: CCE_C002(S), \
	   ccname_type(cce_condition_t, runtime_error)		*: CCE_C002(S), \
	   ccname_type(cce_condition_t, logic_error)			*: CCE_C002(S), \
	   ccname_type(cce_condition_t, invalid_argument)		*: CCE_C002(S), \
	   ccname_type(cce_condition_t, unreachable)			*: CCE_C002(S), \
	   ccname_type(cce_condition_t, system)			*: CCE_C002(S), \
	   ccname_type(cce_condition_t, math_error)			*: CCE_C002(S), \
	   ccname_type(cce_condition_t, math_nan)			*: CCE_C002(S), \
	   ccname_type(cce_condition_t, math_infinity)		*: CCE_C002(S), \
	   ccname_type(cce_condition_t, math_overflow)		*: CCE_C002(S), \
	   ccname_type(cce_condition_t, math_underflow)		*: CCE_C002(S), \
									\
	   cce_condition_t			const	* const: CCE_C002(S), \
	   ccname_type(cce_condition_t, root)			const	* const: CCE_C002(S), \
	   ccname_type(cce_condition_t, unknown)		const	* const: CCE_C002(S), \
	   ccname_type(cce_condition_t, break)		const	* const: CCE_C002(S), \
	   ccname_type(cce_condition_t, unimplemented)	const	* const: CCE_C002(S), \
	   ccname_type(cce_condition_t, error)		const	* const: CCE_C002(S), \
	   ccname_type(cce_condition_t, runtime_error)	const	* const: CCE_C002(S), \
	   ccname_type(cce_condition_t, logic_error)		const	* const: CCE_C002(S), \
	   ccname_type(cce_condition_t, invalid_argument)	const	* const: CCE_C002(S), \
	   ccname_type(cce_condition_t, unreachable)		const	* const: CCE_C002(S), \
	   ccname_type(cce_condition_t, system)		const	* const: CCE_C002(S), \
	   ccname_type(cce_condition_t, math_error)		const	* const: CCE_C002(S), \
	   ccname_type(cce_condition_t, math_nan)		const	* const: CCE_C002(S), \
	   ccname_type(cce_condition_t, math_infinity)	const	* const: CCE_C002(S), \
	   ccname_type(cce_condition_t, math_overflow)	const	* const: CCE_C002(S), \
	   ccname_type(cce_condition_t, math_underflow)	const	* const: CCE_C002(S), \
									\
	   cce_condition_t			const	*: CCE_C002(S), \
	   ccname_type(cce_condition_t, root)			const	*: CCE_C002(S), \
	   ccname_type(cce_condition_t, unknown)		const	*: CCE_C002(S), \
	   ccname_type(cce_condition_t, break)		const	*: CCE_C002(S), \
	   ccname_type(cce_condition_t, unimplemented)	const	*: CCE_C002(S), \
	   ccname_type(cce_condition_t, error)		const	*: CCE_C002(S), \
	   ccname_type(cce_condition_t, runtime_error)	const	*: CCE_C002(S), \
	   ccname_type(cce_condition_t, logic_error)		const	*: CCE_C002(S), \
	   ccname_type(cce_condition_t, invalid_argument)	const	*: CCE_C002(S), \
	   ccname_type(cce_condition_t, unreachable)		const	*: CCE_C002(S), \
	   ccname_type(cce_condition_t, system)		const	*: CCE_C002(S), \
	   ccname_type(cce_condition_t, math_error)		const	*: CCE_C002(S), \
	   ccname_type(cce_condition_t, math_nan)		const	*: CCE_C002(S), \
	   ccname_type(cce_condition_t, math_infinity)	const	*: CCE_C002(S), \
	   ccname_type(cce_condition_t, math_overflow)	const	*: CCE_C002(S), \
	   ccname_type(cce_condition_t, math_underflow)	const	*: CCE_C002(S), \
	   \
	   cce_location_t[1]				 : CCE_C002(CCE_CLOC(S)), \
	   cce_location_t				*: CCE_C002(CCE_CLOC(S)))


/** --------------------------------------------------------------------
 ** Deprecated.
 ** ----------------------------------------------------------------- */

cce_decl bool cce_is_condition (cce_condition_t const * C, cce_descriptor_t const * D)
  __attribute__((__leaf__,__nonnull__(1,2),__deprecated__("use ccname_is(cce_condition_t) instead")));

/* ------------------------------------------------------------------ */

cce_decl void cce_run_clean_handlers (cce_destination_t L)
  __attribute__((__nonnull__(1),__deprecated__("use cce_run_body_handlers instead")));

cce_decl void cce_run_error_handlers (cce_destination_t L)
  __attribute__((__nonnull__(1),__deprecated__("use cce_run_catch_handlers instead")));

/* ------------------------------------------------------------------ */

__attribute__((__nonnull__(1),__always_inline__,__deprecated__("use cce_run_catch_handlers_final instead")))
static inline void
cce_p_run_error_handlers_final (cce_destination_t L)
{
  cce_run_catch_handlers(L);
  ccname_delete(cce_condition_t)((cce_condition_t *)(L->condition));
}

__attribute__((__nonnull__(1),__always_inline__,__deprecated__("use cce_run_body_handlers_final instead")))
static inline void
cce_p_run_clean_handlers_final (cce_destination_t L)
{
  cce_run_body_handlers(L);
  ccname_delete(cce_condition_t)((cce_condition_t *)(L->condition));
}

#if (! defined CCEXCEPTIONS_TRACE)
#  define cce_run_clean_handlers_final(L)	cce_p_run_clean_handlers_final(L)
#  define cce_run_error_handlers_final(L)	cce_p_run_error_handlers_final(L)
#else
#  define cce_run_error_handlers_final(L)			\
  (cce_trace_final(L, __FILE__, __func__, __LINE__), cce_p_run_error_handlers_final(L))
#  define cce_run_clean_handlers_final(L)			\
  (cce_trace_final(L, __FILE__, __func__, __LINE__), cce_p_run_clean_handlers_final(L))
#endif

/* ------------------------------------------------------------------ */

__attribute__((__always_inline__,__nonnull__(1,2),__noreturn__,__deprecated__("use cce_run_catch_handlers_raise instead")))
static inline void
cce_p_run_error_handlers_raise (cce_destination_t L, cce_destination_t upper_L)
{
  cce_run_catch_handlers(L);
  cce_p_raise(upper_L, L->condition);
}

__attribute__((__always_inline__,__nonnull__(1,2),__noreturn__,__deprecated__("use cce_run_body_handlers_raise instead")))
static inline void
cce_p_run_clean_handlers_raise (cce_destination_t L, cce_destination_t upper_L)
{
  cce_run_body_handlers(L);
  cce_p_raise(upper_L, L->condition);
}

#if (! defined CCEXCEPTIONS_TRACE)
#  define cce_run_error_handlers_raise(L,upper_L)	cce_p_run_error_handlers_raise((L),(upper_L))
#  define cce_run_clean_handlers_raise(L,upper_L)	cce_p_run_clean_handlers_raise((L),(upper_L))
#else
#  define cce_run_error_handlers_raise(L,upper_L)			\
  (cce_trace_reraise(L, __FILE__, __func__, __LINE__), cce_p_run_error_handlers_raise((L), (upper_L)))
#  define cce_run_clean_handlers_raise(L,upper_L)			\
  (cce_trace_reraise(L, __FILE__, __func__, __LINE__), cce_p_run_clean_handlers_raise((L), (upper_L)))
#endif

/* ------------------------------------------------------------------ */

cce_decl void cce_clean_handler_malloc_init (cce_destination_t L, cce_clean_handler_t * H, void * pointer)
  __attribute__((__nonnull__(1,2,3),__deprecated__("use cce_init_clean_handler_malloc instead")));

cce_decl void cce_error_handler_malloc_init (cce_destination_t L, cce_error_handler_t * H, void * pointer)
  __attribute__((__nonnull__(1,2,3),__deprecated__("use cce_init_error_handler_malloc instead")));

#define cce_handler_malloc_init(L,P_H,P)				\
  _Generic((P_H),							\
	   cce_clean_handler_t	*: cce_clean_handler_malloc_init,	\
	   cce_error_handler_t	*: cce_error_handler_malloc_init)((L),(P_H),(P))


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* CCEXCEPTIONS_H */

/* end of file */
