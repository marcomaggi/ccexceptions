/*
  Part of: CCExceptions
  Contents: implementation of locations
  Date: Sat Dec 17, 2016

  Abstract



  Copyright (C) 2016, 2017, 2018, 2019 Marco Maggi <marco.maggi-ipsu@poste.it>

  This is free software; you  can redistribute it and/or modify it under
  the terms of the GNU Lesser General Public License as published by the
  Free Software  Foundation; either version  3.0 of the License,  or (at
  your option) any later version.

  This library  is distributed in the  hope that it will  be useful, but
  WITHOUT   ANY  WARRANTY;   without  even   the  implied   warranty  of
  MERCHANTABILITY  or FITNESS  FOR A  PARTICULAR PURPOSE.   See  the GNU
  Lesser General Public License for more details.

  You  should have  received a  copy of  the GNU  Lesser  General Public
  License along  with this library; if  not, write to  the Free Software
  Foundation, Inc.,  59 Temple Place,  Suite 330, Boston,  MA 02111-1307
  USA.

*/


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "ccexceptions-internals.h"
#include <stdio.h>
#include <stdint.h>


/** --------------------------------------------------------------------
 ** Helpers.
 ** ----------------------------------------------------------------- */

__attribute__((__always_inline__,__returns_nonnull__))
static inline cce_condition_t const *
cce_condition_or_default (cce_condition_t const * C)
{
  return ((C)? C : cce_condition_new_unknown());
}

#if (! (defined CCE_DONT_USE_TAGGED_POINTERS))

__attribute__((__always_inline__,__pure__,__nonnull__(1)))
static inline bool
cce_handler_is_error (cce_handler_t const * const H)
{
  return ((((uintptr_t)(H->function)) & 1)? true : false);
}

__attribute__((__always_inline__,__pure__,__nonnull__(1)))
static inline bool
cce_handler_is_clean (cce_handler_t const * const H)
{
  return (! cce_handler_is_error(H));
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline void
cce_error_handler_mark_as_clean (cce_clean_handler_t const * const H CCE_UNUSED)
{
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline void
cce_error_handler_mark_as_error (cce_error_handler_t * const H)
{
  H->handler.function = (cce_handler_fun_t *)(((uintptr_t)(H->handler.function)) | 1);
}

__attribute__((__always_inline__,__pure__,__nonnull__(1),__returns_nonnull__))
static inline cce_handler_fun_t *
cce_handler_get_function (cce_handler_t const * const H)
{
  return (cce_handler_fun_t *)((((uintptr_t)(H->function)) >> 1) << 1);
}

#else

/* Some CPU do not allow function pointers to be tagged in the least significant bit;
   for example ARM processors.  So we also  support using a boolean field to indicate
   if a handler is "clean" or "error". */

__attribute__((__always_inline__,__pure__,__nonnull__(1)))
static inline bool
cce_handler_is_error (cce_handler_t const * const H)
{
  return (! H->is_clean_handler);
}

__attribute__((__always_inline__,__pure__,__nonnull__(1)))
static inline bool
cce_handler_is_clean (cce_handler_t const * const H)
{
  return H->is_clean_handler;
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline void
cce_error_handler_mark_as_clean (cce_error_handler_t * const H)
{
  H->is_clean_handler = false;
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline void
cce_error_handler_mark_as_error (cce_error_handler_t * const H)
{
  H->is_clean_handler = true;
}

__attribute__((__always_inline__,__pure__,__nonnull__(1),__returns_nonnull__))
static inline cce_handler_fun_t *
cce_handler_get_function (cce_handler_t const * const H)
{
  return H->function;
}

#endif


/** --------------------------------------------------------------------
 ** Location mechanism.
 ** ----------------------------------------------------------------- */

__attribute__((__hot__))
void
cce_location_init (cce_destination_t L)
{
  L->first_handler	= NULL;
  L->condition		= cce_condition_new_unknown();
}

__attribute__((__hot__))
void
cce_p_raise (cce_destination_t L, cce_condition_t const * C)
{
  if (cce_condition(L)) { cce_condition_delete(cce_condition(L)); }
  L->condition = cce_condition_or_default(C);
  siglongjmp(L->buffer, (int)CCE_EXCEPT);
}

void
cce_p_retry (cce_destination_t L)
{
  if (cce_condition(L)) { cce_condition_delete(cce_condition(L)); }
  L->condition = cce_condition_new_unknown();
  siglongjmp(L->buffer, (int)CCE_RETRY);
}

__attribute__((__hot__))
void
cce_register_clean_handler (cce_destination_t L, cce_clean_handler_t * H)
{
  cce_error_handler_mark_as_clean(H);
  H->handler.next_handler	= L->first_handler;
  L->first_handler		= cce_clean_handler_handler(H);
}

__attribute__((__hot__))
void
cce_register_error_handler (cce_destination_t L, cce_error_handler_t * H)
{
  cce_error_handler_mark_as_error(H);
  H->handler.next_handler	= L->first_handler;
  L->first_handler		= cce_error_handler_handler(H);
}


/** --------------------------------------------------------------------
 ** Running handlers.
 ** ----------------------------------------------------------------- */

__attribute__((__hot__))
void
cce_run_body_handlers (cce_destination_t L)
/* Traverse the  linked list  of registered handlers  and run  the clean
   ones.   This  is a  destructive  function:  once  the list  has  been
   traversed, it is not valid anymore.
*/
{
  cce_handler_t *	next = L->first_handler;
  L->first_handler = NULL;
  for (cce_handler_t * H = next; H && H->function; H = next) {
    /* First acquire the next handler... */
    next = H->next_handler;
    if (cce_handler_is_clean(H)) {
      /* ... then  run the current  handler.  Remember that  the current
	 handler might release the memory referenced by "H". */
      cce_handler_fun_t	*fun = cce_handler_get_function(H);
      fun(L->condition, H);
    }
  }
}

__attribute__((__hot__))
void
cce_run_catch_handlers (cce_destination_t L)
/* Traverse the  linked list  of registered handlers  and run  the error
   ones.   This  is a  destructive  function:  once  the list  has  been
   traversed, it is not valid anymore.
*/
{
  cce_handler_t *	next = L->first_handler;
  L->first_handler = NULL;
  for (cce_handler_t * H = next; H && H->function; H = next) {
    /* First acquire the next handler... */
    next = H->next_handler;
    /* ...  then  run the  current handler.   Remember that  the current
       handler might release the memory referenced by "H". */
    {
      cce_handler_fun_t	*fun = cce_handler_get_function(H);
      fun(L->condition, H);
    }
  }
}

/* ------------------------------------------------------------------ */

__attribute__((__hot__))
void
cce_p_run_catch_handlers_final (cce_destination_t L)
{
  cce_run_catch_handlers(L);
  cce_condition_delete((cce_condition_t *)(L->condition));
}

__attribute__((__hot__))
void
cce_p_run_body_handlers_final (cce_destination_t L)
{
  cce_run_body_handlers(L);
  cce_condition_delete((cce_condition_t *)(L->condition));
}

/* ------------------------------------------------------------------ */

void
cce_p_run_catch_handlers_raise (cce_destination_t L, cce_destination_t upper_L)
{
  cce_run_catch_handlers(L);
  cce_p_raise(upper_L, L->condition);
}

void
cce_p_run_body_handlers_raise (cce_destination_t L, cce_destination_t upper_L)
{
  cce_run_body_handlers(L);
  cce_p_raise(upper_L, L->condition);
}


/** --------------------------------------------------------------------
 ** Exception handlers: initialisation only.
 ** ----------------------------------------------------------------- */

inline void
cce_init_only_handler_3 (cce_handler_t * H, void * pointer, cce_handler_fun_t * fun)
{
  H->pointer	= pointer;
  H->function	= fun;
  H->destructor	= NULL;
}

inline void
cce_init_only_handler_4 (cce_handler_t * H, void * pointer, cce_handler_fun_t * fun, cce_destructor_fun_t * destructor)
{
  H->pointer	= pointer;
  H->function	= fun;
  H->destructor	= destructor;
}

/* ------------------------------------------------------------------ */

void
cce_init_only_clean_handler_3 (cce_clean_handler_t * H, void * pointer, cce_handler_fun_t * fun)
{
  cce_init_only_handler_3(cce_clean_handler_handler(H), pointer, fun);
}

void
cce_init_only_clean_handler_4 (cce_clean_handler_t * H, void * pointer, cce_handler_fun_t * fun, cce_destructor_fun_t * destructor)
{
  cce_init_only_handler_4(cce_clean_handler_handler(H), pointer, fun, destructor);
}

/* ------------------------------------------------------------------ */

void
cce_init_only_error_handler_3 (cce_error_handler_t * H, void * pointer, cce_handler_fun_t * fun)
{
  cce_init_only_handler_3(cce_error_handler_handler(H), pointer, fun);
}

void
cce_init_only_error_handler_4 (cce_error_handler_t * H, void * pointer, cce_handler_fun_t * fun, cce_destructor_fun_t * destructor)
{
  cce_init_only_handler_4(cce_error_handler_handler(H), pointer, fun, destructor);
}


/** --------------------------------------------------------------------
 ** Exception handlers: initialisation and registration.
 ** ----------------------------------------------------------------- */

void
cce_init_and_register_clean_handler_4 (cce_destination_t L, cce_clean_handler_t * H, void * pointer,
				       cce_handler_fun_t * fun)
{
  cce_init_only_clean_handler_3(H, pointer, fun);
  cce_register_clean_handler(L, H);
}
void
cce_init_and_register_clean_handler_5 (cce_destination_t L, cce_clean_handler_t * H, void * pointer,
				       cce_handler_fun_t * fun, cce_destructor_fun_t * destructor)
{
  cce_init_only_clean_handler_4(H, pointer, fun, destructor);
  cce_register_clean_handler(L, H);
}

/* ------------------------------------------------------------------ */

void
cce_init_and_register_error_handler_4 (cce_destination_t L, cce_error_handler_t * H, void * pointer,
				       cce_handler_fun_t * fun)
{
  cce_init_only_error_handler_3(H, pointer, fun);
  cce_register_error_handler(L, H);
}
void
cce_init_and_register_error_handler_5 (cce_destination_t L, cce_error_handler_t * H, void * pointer,
				       cce_handler_fun_t * fun, cce_destructor_fun_t * destructor)
{
  cce_init_only_error_handler_4(H, pointer, fun, destructor);
  cce_register_error_handler(L, H);
}


/** --------------------------------------------------------------------
 ** Forgetting handlers.
 ** ----------------------------------------------------------------- */

static void
cce_forget_handler (cce_destination_t L, cce_handler_t * H)
{
  if (L->first_handler == H) {
    L->first_handler = H->next_handler;
    H->next_handler  = NULL;
  } else {
    for (cce_handler_t * iter = L->first_handler; iter; iter = iter->next_handler) {
      if (iter->next_handler == H) {
	iter->next_handler = H->next_handler;
	H->next_handler    = NULL;
      }
    }
  }
}

void
cce_forget_clean_handler (cce_destination_t L, cce_clean_handler_t * H)
{
  cce_forget_handler(L, cce_handler_handler(H));
}

void
cce_forget_error_handler (cce_destination_t L, cce_error_handler_t * H)
{
  cce_forget_handler(L, cce_handler_handler(H));
}


/** --------------------------------------------------------------------
 ** Running handlers from a handler.
 ** ----------------------------------------------------------------- */

__attribute__((__nonnull__(1,2)))
static void
run_body_handlers (cce_condition_t const * C CCE_UNUSED, cce_handler_t * inner_H)
{
  CCE_PC(cce_location_t, L, inner_H->pointer);

  cce_run_body_handlers(L);
  cce_condition_delete(cce_condition(L));
}

__attribute__((__nonnull__(1,2)))
static void
run_catch_handlers (cce_condition_t const * C CCE_UNUSED, cce_handler_t * inner_H)
{
  CCE_PC(cce_location_t, L, inner_H->pointer);

  cce_run_catch_handlers(L);
  cce_condition_delete(cce_condition(L));
}

/* ------------------------------------------------------------------ */

void
cce_register_clean_handler_to_run_body_handlers (cce_destination_t inner_L, cce_clean_handler_t * inner_H, cce_destination_t outer_L)
{
  cce_init_handler(inner_H, outer_L, run_body_handlers);
  cce_register_handler(inner_L, inner_H);
}

void
cce_register_clean_handler_to_run_catch_handlers (cce_destination_t inner_L, cce_clean_handler_t * inner_H, cce_destination_t outer_L)
{
  cce_init_handler(inner_H, outer_L, run_catch_handlers);
  cce_register_handler(inner_L, inner_H);
}

/* ------------------------------------------------------------------ */

void
cce_register_error_handler_to_run_body_handlers (cce_destination_t inner_L, cce_error_handler_t * inner_H, cce_destination_t outer_L)
{
  cce_init_handler(inner_H, outer_L, run_body_handlers);
  cce_register_handler(inner_L, inner_H);
}

void
cce_register_error_handler_to_run_catch_handlers (cce_destination_t inner_L, cce_error_handler_t * inner_H, cce_destination_t outer_L)
{
  cce_init_handler(inner_H, outer_L, run_catch_handlers);
  cce_register_handler(inner_L, inner_H);
}


/** --------------------------------------------------------------------
 ** Tracing.
 ** ----------------------------------------------------------------- */

int
cce_trace_setjmp (cce_destination_t L, int rv, char const * filename, char const * funcname, int linenum)
{
  if (CCE_EXCEPT == rv) {
    fprintf(stderr, "%-11s %s:%d, %s(): %s\n", "catching:", filename, linenum, funcname,
	    cce_condition_static_message(cce_condition(L)));
  }
  return rv;
}

cce_condition_t const *
cce_trace_raise (cce_condition_t const * C, char const * filename, char const * funcname, int linenum)
{
  cce_condition_t const * K = cce_condition_or_default(C);
  fprintf(stderr, "%-11s %s:%d, %s(): %s\n", "raising:", filename, linenum, funcname,
	  cce_condition_static_message(K));
  return C;
}

cce_destination_t
cce_trace_retry (cce_destination_t L, char const * filename, char const * funcname, int linenum)
{
  fprintf(stderr, "%-11s %s:%d, %s()\n", "retrying:", filename, linenum, funcname);
  return L;
}

void
cce_trace_reraise (cce_destination_t L, char const * filename, char const * funcname, int linenum)
{
  cce_condition_t const * C = cce_condition(L);
  cce_condition_t const * K = cce_condition_or_default(C);
  fprintf(stderr, "%-11s %s:%d, %s(): %s\n", "re-raising:", filename, linenum, funcname,
	  cce_condition_static_message(K));
}

void
cce_trace_final (cce_destination_t L, char const * filename, char const * funcname, int linenum)
{
  cce_condition_t const * C = cce_condition(L);
  cce_condition_t const * K = cce_condition_or_default(C);
  fprintf(stderr, "%-11s %s:%d, %s(): %s\n", "finalising:", filename, linenum, funcname,
	  cce_condition_static_message(K));
}


/** --------------------------------------------------------------------
 ** Miscellaneous.
 ** ----------------------------------------------------------------- */

void
cce_default_destructor_handler (cce_condition_t const * const C CCE_UNUSED, cce_handler_t * H)
{
  if (H->destructor) {
    H->destructor(H->pointer);
  }
}

/* end of file */
