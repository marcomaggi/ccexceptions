/*
  Part of: CCExceptions
  Contents: public header file
  Date: Sat Dec 17, 2016

  Abstract

	This is the  main header: it must  be included in all the  source files using
	CCExceptions.  Notice that  the code needs the POSIX features,  so it defines
	the following symbol:

	   #define _POSIX_C_SOURCE 200809L

  Copyright (C) 2016, 2017, 2018, 2019 Marco Maggi <marco.maggi-ipsu@poste.it>

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
 ** Variadic macros mechanism.
 ** ----------------------------------------------------------------- */

/* The  following  macros are  adapted  from  Stack Overflow  (URL  last
 * accessed Jan 2, 2019):
 *
 *   <https://stackoverflow.com/a/26408195>
 */

/* The macro use:
 *
 *   _CCE__NARG__(__VA_ARGS__)
 *
 * expands into the number of arguments in __VA_ARGS__.
 */
#define _CCE__NARG__(...)	_CCE__NARG_I_(__VA_ARGS__,_CCE__RSEQ_N())
#define _CCE__NARG_I_(...)	_CCE__ARG_N(__VA_ARGS__)
#define _CCE__ARG_N( \
      _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
     _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
     _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
     _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
     _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
     _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
     _61,_62,_63,N,...)		N
#define _CCE__RSEQ_N() \
     63,62,61,60,                   \
     59,58,57,56,55,54,53,52,51,50, \
     49,48,47,46,45,44,43,42,41,40, \
     39,38,37,36,35,34,33,32,31,30, \
     29,28,27,26,25,24,23,22,21,20, \
     19,18,17,16,15,14,13,12,11,10, \
     9,8,7,6,5,4,3,2,1,0

/* The macro uses:
 *
 *    _CCE_VFUNC(cce_new, alpha)
 *    _CCE_VFUNC(cce_new, alpha, beta)
 *
 * respectively expand into:
 *
 *    cce_new_1(alpha)
 *    cce_new_2(alpha, beta)
 *
 */
#define _CCE___VFUNC(NAME, N)	NAME ## _ ## N
#define _CCE__VFUNC(NAME, N)	_CCE___VFUNC(NAME, N)
#define _CCE_VFUNC(FUNC, ...)	_CCE__VFUNC(FUNC, _CCE__NARG__(__VA_ARGS__))(__VA_ARGS__)


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

/* Enable latest POSIX features. */
#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE		200809L

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
 ** Include files.
 ** ----------------------------------------------------------------- */

#include <ccexceptions-handlers.h>
#include <ccexceptions-conditions.h>


/** --------------------------------------------------------------------
 ** Locations.
 ** ----------------------------------------------------------------- */

struct cce_location_t {
  /* The buffer must be the first member of this struct. */
  sigjmp_buf			buffer;
  cce_condition_t const *	condition;
  cce_handler_t *		first_clean_handler;
  cce_handler_t *		first_error_handler;
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

cce_decl void cce_p_run_body_handlers_raise (cce_destination_t L, cce_destination_t upper_L)
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
  __attribute__((__leaf__,__nonnull__(1,2,3)));

cce_decl void cce_register_clean_handler_to_run_catch_handlers (cce_destination_t inner_L, cce_clean_handler_t * inner_H,
								cce_destination_t outer_L)
  __attribute__((__leaf__,__nonnull__(1,2,3)));

cce_decl void cce_register_error_handler_to_run_body_handlers  (cce_destination_t inner_L, cce_error_handler_t * inner_H,
								cce_destination_t outer_L)
  __attribute__((__leaf__,__nonnull__(1,2,3)));

cce_decl void cce_register_error_handler_to_run_catch_handlers (cce_destination_t inner_L, cce_error_handler_t * inner_H,
								cce_destination_t outer_L)
  __attribute__((__leaf__,__nonnull__(1,2,3)));


/** --------------------------------------------------------------------
 ** System call wrappers: memory allocation.
 ** ----------------------------------------------------------------- */

cce_decl void * cce_sys_malloc (cce_destination_t L, size_t size)
  __attribute__((__leaf__,__nonnull__(1),__returns_nonnull__));

cce_decl void * cce_sys_realloc (cce_destination_t L, void * ptr, size_t newsize)
  __attribute__((__leaf__,__nonnull__(1),__returns_nonnull__));

cce_decl void * cce_sys_calloc (cce_destination_t L, size_t count, size_t eltsize)
  __attribute__((__leaf__,__nonnull__(1),__returns_nonnull__));

/* ------------------------------------------------------------------ */

cce_decl void cce_init_and_register_clean_handler_malloc (cce_destination_t L, cce_clean_handler_t * H, void * pointer)
  __attribute__((__leaf__,__nonnull__(1,2,3)));

cce_decl void cce_init_and_register_error_handler_malloc (cce_destination_t L, cce_error_handler_t * H, void * pointer)
  __attribute__((__leaf__,__nonnull__(1,2,3)));

#define cce_init_and_register_handler_malloc(L,P_H,P)			\
  _Generic((P_H),							\
	   cce_clean_handler_t	*: cce_init_and_register_clean_handler_malloc, \
	   cce_error_handler_t	*: cce_init_and_register_error_handler_malloc)((L),(P_H),(P))

/* ------------------------------------------------------------------ */

cce_decl void * cce_sys_malloc_guarded_clean (cce_location_t * L, cce_clean_handler_t * P_H, size_t size)
  __attribute__((__leaf__,__nonnull__(1,2),__returns_nonnull__));

cce_decl void * cce_sys_malloc_guarded_error (cce_location_t * L, cce_error_handler_t *   P_H, size_t size)
  __attribute__((__leaf__,__nonnull__(1,2),__returns_nonnull__));

#define cce_sys_malloc_guarded(L,P_H,size)				\
  _Generic((P_H),							\
	   cce_clean_handler_t	*: cce_sys_malloc_guarded_clean,	\
	   cce_error_handler_t	*: cce_sys_malloc_guarded_error)((L),(P_H),(size))

/* ------------------------------------------------------------------ */

cce_decl void * cce_sys_realloc_guarded_clean (cce_location_t * L, cce_clean_handler_t * P_H, void * P, size_t newsize)
  __attribute__((__leaf__,__nonnull__(1,2),__returns_nonnull__));

cce_decl void * cce_sys_realloc_guarded_error (cce_location_t * L, cce_error_handler_t * P_H, void * P, size_t newsize)
  __attribute__((__leaf__,__nonnull__(1,2),__returns_nonnull__));

#define cce_sys_realloc_guarded(L,P_H,old_P,newsize)			\
  _Generic((P_H),							\
	   cce_clean_handler_t	*: cce_sys_realloc_guarded_clean,	\
	   cce_error_handler_t	*: cce_sys_realloc_guarded_error)((L),(P_H),(old_P),(newsize))

/* ------------------------------------------------------------------ */

cce_decl void * cce_sys_calloc_guarded_clean (cce_location_t * L, cce_clean_handler_t * P_H, size_t count, size_t eltsize)
  __attribute__((__leaf__,__nonnull__(1,2),__returns_nonnull__));

cce_decl void * cce_sys_calloc_guarded_error (cce_location_t * L, cce_error_handler_t * P_H, size_t count, size_t eltsize)
  __attribute__((__leaf__,__nonnull__(1,2),__returns_nonnull__));

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
