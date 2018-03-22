/*
  Part of: CCExceptions
  Contents: implementation of locations
  Date: Sat Dec 17, 2016

  Abstract



  Copyright (C) 2016, 2017, 2018 Marco Maggi <marco.maggi-ipsu@poste.it>

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

#include "ccexceptions-internals.h"


/** --------------------------------------------------------------------
 ** Helpers.
 ** ----------------------------------------------------------------- */

__attribute__((__always_inline__,__returns_nonnull__))
static inline cce_condition_t const *
cce_condition_or_default (cce_condition_t const * C)
{
  return ((C)? C : &(cce_condition_unknown_ptr->root.condition));
}


/** --------------------------------------------------------------------
 ** Mechanism.
 ** ----------------------------------------------------------------- */

__attribute__((hot))
void
cce_location_init (cce_location_t * L)
{
  L->first_handler	= NULL;
  L->condition		= &(cce_condition_unknown_ptr->root.condition);
}

__attribute__((hot))
void
cce_p_raise (cce_location_t * L, cce_condition_t const * C)
{
  if (L->condition) { cce_condition_delete((cce_condition_t*)L->condition); }
  L->condition = cce_condition_or_default(C);
  siglongjmp(L->buffer, (int)CCE_EXCEPT);
}

__attribute__((hot))
void
cce_register_cleanup_handler (cce_location_t * L, cce_handler_t * H)
{
  H->is_cleanup_handler = true;
  H->next_handler	= L->first_handler;
  L->first_handler	= H;
}

__attribute__((hot))
void
cce_register_error_handler (cce_location_t * L, cce_handler_t * H)
{
  H->is_cleanup_handler = false;
  H->next_handler	= L->first_handler;
  L->first_handler	= H;
}

void
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

__attribute__((hot))
void
cce_run_cleanup_handlers (cce_location_t * L)
/* Traverse the linked  list of registered handlers and  run the cleanup
   ones.   This  is a  destructive  function:  once  the list  has  been
   traversed, it is not valid anymore.
*/
{
  cce_handler_t *	next = L->first_handler;
  L->first_handler = NULL;
  for (cce_handler_t * H = next; H && H->function; H = next) {
    next = H->next_handler;
    if (true == H->is_cleanup_handler) {
      H->function(L->condition, H);
    }
  }
}

__attribute__((hot))
void
cce_run_error_handlers (cce_location_t * L)
/* Traverse the  linked list  of registered handlers  and run  the error
   ones.   This  is a  destructive  function:  once  the list  has  been
   traversed, it is not valid anymore.
*/
{
  cce_handler_t *	next = L->first_handler;
  L->first_handler = NULL;
  for (cce_handler_t * H = next; H && H->function; H = next) {
    next = H->next_handler;
    H->function(L->condition, H);
  }
}


/** --------------------------------------------------------------------
 ** Tracing.
 ** ----------------------------------------------------------------- */

int
cce_trace_init (cce_destination_t L, int rv, char const * filename, char const * funcname, int linenum)
{
  if (CCE_EXCEPT == rv) {
    fprintf(stderr, "%-11s %s:%d, %s(): %s\n", "catching:", filename, linenum, funcname,
	    cce_condition_static_message(L->condition));
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

void
cce_trace_reraise (cce_destination_t L, char const * filename, char const * funcname, int linenum)
{
  cce_condition_t const * C = L->condition;
  cce_condition_t const * K = cce_condition_or_default(C);
  fprintf(stderr, "%-11s %s:%d, %s(): %s\n", "re-raising:", filename, linenum, funcname,
	  cce_condition_static_message(K));
}

void
cce_trace_final (cce_destination_t L, char const * filename, char const * funcname, int linenum)
{
  cce_condition_t const * C = L->condition;
  cce_condition_t const * K = cce_condition_or_default(C);
  fprintf(stderr, "%-11s %s:%d, %s(): %s\n", "finalising:", filename, linenum, funcname,
	  cce_condition_static_message(K));
}

/* end of file */
