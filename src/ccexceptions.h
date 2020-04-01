/*
  Part of: CCExceptions
  Contents: public header file
  Date: Sat Dec 17, 2016

  Abstract

	This is the  main header: it must  be included in all the  source files using
	CCExceptions.  Notice that  the code needs the POSIX features,  so it defines
	the following symbol:

	   #define _POSIX_C_SOURCE 200809L

  Copyright (C) 2016, 2017, 2018, 2019, 2020 Marco Maggi <mrc.mgg@gmail.com>

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
 ** Headers.
 ** ----------------------------------------------------------------- */

/* Enable latest POSIX features. */
#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE		200809L

#include <cclibraries.h>
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

cclib_decl char const *	cce_version_string		(void)
  CCLIB_FUNC_ATTRIBUTE_LEAF
  CCLIB_FUNC_ATTRIBUTE_PURE;

cclib_decl int		cce_version_interface_current	(void)
  CCLIB_FUNC_ATTRIBUTE_LEAF
  CCLIB_FUNC_ATTRIBUTE_PURE;

cclib_decl int		cce_version_interface_revision	(void)
  CCLIB_FUNC_ATTRIBUTE_LEAF
  CCLIB_FUNC_ATTRIBUTE_PURE;

cclib_decl int		cce_version_interface_age	(void)
  CCLIB_FUNC_ATTRIBUTE_LEAF
  CCLIB_FUNC_ATTRIBUTE_PURE;


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

cclib_decl void cce_location_init	(cce_destination_t here)
  CCLIB_FUNC_ATTRIBUTE_LEAF
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1);

cclib_decl void cce_p_raise (cce_destination_t L, cce_condition_t const * C)
  CCLIB_FUNC_ATTRIBUTE_NORETURN
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1);

cclib_decl void cce_p_retry (cce_destination_t L)
  CCLIB_FUNC_ATTRIBUTE_NORETURN
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1);

/* ------------------------------------------------------------------ */

cclib_decl int cce_trace_setjmp (cce_destination_t L, int rv, char const * filename, char const * funcname, int linenum)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,3,4);

cclib_decl cce_condition_t const * cce_trace_raise (cce_condition_t const * C, char const * filename, char const * funcname, int linenum)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(2,3);

cclib_decl cce_destination_t cce_trace_retry (cce_destination_t L, char const * filename, char const * funcname, int linenum)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3);

/* ------------------------------------------------------------------ */

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_CONST
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

cclib_decl void cce_p_run_catch_handlers_final (cce_destination_t L)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1);

cclib_decl void cce_p_run_body_handlers_final (cce_destination_t L)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1);

cclib_decl void cce_trace_final (cce_destination_t L, char const * filename, char const * funcname, int linenum)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3);

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

cclib_decl void cce_p_run_catch_handlers_raise (cce_destination_t L, cce_destination_t upper_L)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2)
  CCLIB_FUNC_ATTRIBUTE_NORETURN;

cclib_decl void cce_p_run_body_handlers_raise (cce_destination_t L, cce_destination_t upper_L)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2)
  CCLIB_FUNC_ATTRIBUTE_NORETURN;

/* ------------------------------------------------------------------ */

cclib_decl void cce_trace_reraise (cce_destination_t L, char const * filename, char const * funcname, int linenum)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3);

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

cclib_decl void cce_register_clean_handler_to_run_body_handlers  (cce_destination_t inner_L, cce_clean_handler_t * inner_H,
								cce_destination_t outer_L)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3)
  CCLIB_FUNC_ATTRIBUTE_LEAF;

cclib_decl void cce_register_clean_handler_to_run_catch_handlers (cce_destination_t inner_L, cce_clean_handler_t * inner_H,
								  cce_destination_t outer_L)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3)
  CCLIB_FUNC_ATTRIBUTE_LEAF;

cclib_decl void cce_register_error_handler_to_run_body_handlers  (cce_destination_t inner_L, cce_error_handler_t * inner_H,
								  cce_destination_t outer_L)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3)
  CCLIB_FUNC_ATTRIBUTE_LEAF;

cclib_decl void cce_register_error_handler_to_run_catch_handlers (cce_destination_t inner_L, cce_error_handler_t * inner_H,
								  cce_destination_t outer_L)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3)
  CCLIB_FUNC_ATTRIBUTE_LEAF;


/** --------------------------------------------------------------------
 ** System call wrappers: memory allocation.
 ** ----------------------------------------------------------------- */

cclib_decl void * cce_sys_malloc (cce_destination_t L, size_t size)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL
  CCLIB_FUNC_ATTRIBUTE_LEAF;

cclib_decl void * cce_sys_realloc (cce_destination_t L, void * ptr, size_t newsize)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL
  CCLIB_FUNC_ATTRIBUTE_LEAF;

cclib_decl void * cce_sys_calloc (cce_destination_t L, size_t count, size_t eltsize)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL
  CCLIB_FUNC_ATTRIBUTE_LEAF;

/* ------------------------------------------------------------------ */

cclib_decl void cce_init_and_register_clean_handler_malloc (cce_destination_t L, cce_clean_handler_t * H, void * pointer)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3)
  CCLIB_FUNC_ATTRIBUTE_LEAF;

cclib_decl void cce_init_and_register_error_handler_malloc (cce_destination_t L, cce_error_handler_t * H, void * pointer)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3)
  CCLIB_FUNC_ATTRIBUTE_LEAF;

#define cce_init_and_register_handler_malloc(L,P_H,P)			\
  _Generic((P_H),							\
	   cce_clean_handler_t	*: cce_init_and_register_clean_handler_malloc, \
	   cce_error_handler_t	*: cce_init_and_register_error_handler_malloc)((L),(P_H),(P))

/* ------------------------------------------------------------------ */

cclib_decl void * cce_sys_malloc_guarded_clean (cce_location_t * L, cce_clean_handler_t * P_H, size_t size)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2)
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL
  CCLIB_FUNC_ATTRIBUTE_LEAF;

cclib_decl void * cce_sys_malloc_guarded_error (cce_location_t * L, cce_error_handler_t *   P_H, size_t size)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2)
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL
  CCLIB_FUNC_ATTRIBUTE_LEAF;

#define cce_sys_malloc_guarded(L,P_H,size)				\
  _Generic((P_H),							\
	   cce_clean_handler_t	*: cce_sys_malloc_guarded_clean,	\
	   cce_error_handler_t	*: cce_sys_malloc_guarded_error)((L),(P_H),(size))

/* ------------------------------------------------------------------ */

cclib_decl void * cce_sys_realloc_guarded_clean (cce_location_t * L, cce_clean_handler_t * P_H, void * P, size_t newsize)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2)
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL
  CCLIB_FUNC_ATTRIBUTE_LEAF;

cclib_decl void * cce_sys_realloc_guarded_error (cce_location_t * L, cce_error_handler_t * P_H, void * P, size_t newsize)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2)
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL
  CCLIB_FUNC_ATTRIBUTE_LEAF;

#define cce_sys_realloc_guarded(L,P_H,old_P,newsize)			\
  _Generic((P_H),							\
	   cce_clean_handler_t	*: cce_sys_realloc_guarded_clean,	\
	   cce_error_handler_t	*: cce_sys_realloc_guarded_error)((L),(P_H),(old_P),(newsize))

/* ------------------------------------------------------------------ */

cclib_decl void * cce_sys_calloc_guarded_clean (cce_location_t * L, cce_clean_handler_t * P_H, size_t count, size_t eltsize)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2)
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL
  CCLIB_FUNC_ATTRIBUTE_LEAF;

cclib_decl void * cce_sys_calloc_guarded_error (cce_location_t * L, cce_error_handler_t * P_H, size_t count, size_t eltsize)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2)
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL
  CCLIB_FUNC_ATTRIBUTE_LEAF;

#define cce_sys_calloc_guarded(L,P_H,count,eltsize)			\
  _Generic((P_H),							\
	   cce_clean_handler_t	*: cce_sys_calloc_guarded_clean,	\
	   cce_error_handler_t	*: cce_sys_calloc_guarded_error)((L),(P_H),(count),(eltsize))


/** --------------------------------------------------------------------
 ** Generic macros.
 ** ----------------------------------------------------------------- */

/* Cast pointer S to a location structure and evaluate to the pointer to
   condition object. */
#define CCE_CLOC(S)			(((cce_location_t *)(S))->condition)

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
