/*
  Part of: CCExceptions
  Contents: implementation of locations mechanism
  Date: Sat Dec 17, 2016

  Abstract

	This module implementas the basics of the locations mechanism.

  Copyright (C) 2016-2020 Marco Maggi <mrc.mgg@gmail.com>

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


/** --------------------------------------------------------------------
 ** Location mechanism.
 ** ----------------------------------------------------------------- */

__attribute__((__hot__))
void
cce_location_init (cce_destination_t L)
{
  L->condition			= cce_condition_new_unknown();
  L->first_clean_handler	= NULL;
  L->first_error_handler	= NULL;
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
  H->handler.next_handler	= L->first_clean_handler;
  L->first_clean_handler	= cce_clean_handler_handler(H);
}

__attribute__((__hot__))
void
cce_register_error_handler (cce_destination_t L, cce_error_handler_t * H)
{
  H->handler.next_handler	= L->first_error_handler;
  L->first_error_handler	= cce_error_handler_handler(H);
}


/** --------------------------------------------------------------------
 ** Running handlers.
 ** ----------------------------------------------------------------- */

__attribute__((__hot__))
static void
run_handlers (cce_destination_t L, cce_handler_t * next)
{
  for (cce_handler_t * H = next; H && H->handler_function; H = next) {
    next = H->next_handler;
    H->handler_function(cce_condition(L), H);
  }
}

__attribute__((__hot__))
void
cce_run_body_handlers (cce_destination_t L)
/* Traverse the  linked list of  registered clean handlers and  run them.  This  is a
   destructive  function:  once  the  list  has  been  traversed,  it  is  not  valid
   anymore. */
{
  cce_handler_t *	next = L->first_clean_handler;
  L->first_clean_handler = NULL;
  run_handlers(L, next);
}

__attribute__((__hot__))
void
cce_run_catch_handlers (cce_destination_t L)
/* Traverse the linked list of registered  clean handlers and run them; then traverse
   the list of error handlers and run them.  This is a destructive function: once the
   lists have been traversed, they are not valid anymore. */
{
  {
    cce_handler_t *	next = L->first_clean_handler;
    L->first_clean_handler = NULL;
    run_handlers(L, next);
  }
  {
    cce_handler_t *	next = L->first_error_handler;
    L->first_error_handler = NULL;
    run_handlers(L, next);
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

__attribute__((__always_inline__,__nonnull__(1,3)))
static inline void
cce_p_init_handler_3 (cce_handler_t * H, cce_handler_fun_t * handler_function, cce_resource_data_t * resource_pointer)
{
  H->resource_pointer		= resource_pointer;
  H->handler_function		= handler_function;
  H->resource_destructor	= NULL;
}

__attribute__((__always_inline__,__nonnull__(1,3)))
static inline void
cce_p_init_handler_4 (cce_handler_t * H, cce_handler_fun_t * handler_function,
		      cce_resource_data_t * resource_pointer, cce_resource_destructor_fun_t * resource_destructor)
{
  H->resource_pointer		= resource_pointer;
  H->handler_function		= handler_function;
  H->resource_destructor	= resource_destructor;
}

/* ------------------------------------------------------------------ */

void
cce_init_clean_handler_3 (cce_clean_handler_t * H, cce_clean_handler_fun_t * handler_function, cce_resource_data_t * resource_pointer)
{
  cce_p_init_handler_3(cce_clean_handler_handler(H), (cce_handler_fun_t *)handler_function, resource_pointer);
}

void
cce_init_clean_handler_4 (cce_clean_handler_t * H, cce_clean_handler_fun_t * handler_function,
			  cce_resource_data_t * resource_pointer, cce_resource_destructor_fun_t * resource_destructor)
{
  cce_p_init_handler_4(cce_clean_handler_handler(H), (cce_handler_fun_t *)handler_function, resource_pointer, resource_destructor);
}

/* ------------------------------------------------------------------ */

void
cce_init_error_handler_3 (cce_error_handler_t * H, cce_error_handler_fun_t * handler_function, cce_resource_data_t * resource_pointer)
{
  cce_p_init_handler_3(cce_error_handler_handler(H), (cce_handler_fun_t *)handler_function, resource_pointer);
}

void
cce_init_error_handler_4 (cce_error_handler_t * H, cce_error_handler_fun_t * handler_function,
			  cce_resource_data_t * resource_pointer, cce_resource_destructor_fun_t * resource_destructor)
{
  cce_p_init_handler_4(cce_error_handler_handler(H), (cce_handler_fun_t *)handler_function, resource_pointer, resource_destructor);
}


/** --------------------------------------------------------------------
 ** Exception handlers: initialisation and registration.
 ** ----------------------------------------------------------------- */

void
cce_init_and_register_clean_handler_4 (cce_destination_t L,
				       cce_clean_handler_t * H, cce_clean_handler_fun_t * handler_function,
				       cce_resource_data_t * resource_pointer)
{
  cce_init_clean_handler_3(H, handler_function, resource_pointer);
  cce_register_clean_handler(L, H);
}

void
cce_init_and_register_clean_handler_5 (cce_destination_t L,
				       cce_clean_handler_t * H, cce_clean_handler_fun_t * handler_function,
				       cce_resource_data_t * resource_pointer, cce_resource_destructor_fun_t * resource_destructor)
{
  cce_init_clean_handler_4(H, handler_function, resource_pointer, resource_destructor);
  cce_register_clean_handler(L, H);
}

/* ------------------------------------------------------------------ */

void
cce_init_and_register_error_handler_4 (cce_destination_t L,
				       cce_error_handler_t * H, cce_error_handler_fun_t * handler_function,
				       cce_resource_data_t * resource_pointer)
{
  cce_init_error_handler_3(H, handler_function, resource_pointer);
  cce_register_error_handler(L, H);
}

void
cce_init_and_register_error_handler_5 (cce_destination_t L,
				       cce_error_handler_t * H, cce_error_handler_fun_t * handler_function,
				       cce_resource_data_t * resource_pointer, cce_resource_destructor_fun_t * resource_destructor)
{
  cce_init_error_handler_4(H, handler_function, resource_pointer, resource_destructor);
  cce_register_error_handler(L, H);
}


/** --------------------------------------------------------------------
 ** Forgetting handlers.
 ** ----------------------------------------------------------------- */

static void
forget_handler (cce_handler_t ** first_handler_p, cce_handler_t * H)
{
  cce_handler_t * first_handler = *first_handler_p;

  if (first_handler == H) {
    *first_handler_p = H->next_handler;
    H->next_handler  = NULL;
  } else {
    for (cce_handler_t * iter = first_handler; iter; iter = iter->next_handler) {
      if (iter->next_handler == H) {
	iter->next_handler = H->next_handler;
	H->next_handler    = NULL;
      }
    }
  }
}

void
cce_forget_clean_handler (cce_destination_t L, cce_clean_handler_t * target_handler)
{
  forget_handler(&(L->first_clean_handler), cce_handler_handler(target_handler));
}

void
cce_forget_error_handler (cce_destination_t L, cce_error_handler_t * target_handler)
{
  forget_handler(&(L->first_error_handler), cce_handler_handler(target_handler));
}


/** --------------------------------------------------------------------
 ** Running handlers from a handler.
 ** ----------------------------------------------------------------- */

__attribute__((__nonnull__(1,2)))
static void
run_body_handlers (cce_condition_t const * C CCLIB_UNUSED, cce_handler_t const * inner_H)
{
  CCLIB_PC(cce_location_t, L, inner_H->resource_pointer);

  cce_run_body_handlers(L);
  cce_condition_delete(cce_condition(L));
}

__attribute__((__nonnull__(1,2)))
static void
run_catch_handlers (cce_condition_t const * C CCLIB_UNUSED, cce_handler_t const * inner_H)
{
  CCLIB_PC(cce_location_t, L, inner_H->resource_pointer);

  cce_run_catch_handlers(L);
  cce_condition_delete(cce_condition(L));
}

/* ------------------------------------------------------------------ */

void
cce_register_clean_handler_to_run_body_handlers (cce_destination_t inner_L, cce_clean_handler_t * inner_H, cce_destination_t outer_L)
{
  cce_init_handler(inner_H, (cce_clean_handler_fun_t *)run_body_handlers, outer_L);
  cce_register_handler(inner_L, inner_H);
}

void
cce_register_clean_handler_to_run_catch_handlers (cce_destination_t inner_L, cce_clean_handler_t * inner_H, cce_destination_t outer_L)
{
  cce_init_handler(inner_H, (cce_clean_handler_fun_t *)run_catch_handlers, outer_L);
  cce_register_handler(inner_L, inner_H);
}

/* ------------------------------------------------------------------ */

void
cce_register_error_handler_to_run_body_handlers (cce_destination_t inner_L, cce_error_handler_t * inner_H, cce_destination_t outer_L)
{
  cce_init_handler(inner_H, (cce_error_handler_fun_t *)run_body_handlers, outer_L);
  cce_register_handler(inner_L, inner_H);
}

void
cce_register_error_handler_to_run_catch_handlers (cce_destination_t inner_L, cce_error_handler_t * inner_H, cce_destination_t outer_L)
{
  cce_init_handler(inner_H, (cce_error_handler_fun_t *)run_catch_handlers, outer_L);
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

__attribute__((__always_inline__,__nonnull__(1,2)))
static inline void
cce_default_handler_function (cce_condition_t const * C CCLIB_UNUSED, cce_handler_t const * H)
{
  if (H->resource_destructor) {
    H->resource_destructor(H->resource_pointer);
  }
}

void
cce_default_clean_handler_function (cce_condition_t const * C, cce_clean_handler_t const * H)
{
  cce_default_handler_function(C, cce_handler_handler(H));
}

void
cce_default_error_handler_function (cce_condition_t const * C, cce_error_handler_t const * H)
{
  cce_default_handler_function(C, cce_handler_handler(H));
}

/* end of file */
