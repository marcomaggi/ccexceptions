/*
  Part of: CCExceptions
  Contents: implementation of locations
  Date: Sat Dec 17, 2016

  Abstract



  Copyright (C) 2016, 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

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

__attribute__((hot))
void
cce_location_init (cce_location_t * L)
{
  L->first_handler	= NULL;
  L->condition		= &(cce_condition_unknown_ptr->root_C.condition_C);
}

__attribute__((hot))
void
cce_raise (cce_location_t * L, const cce_condition_t * C)
{
  if (L->condition) { cce_condition_final((cce_condition_t*)L->condition); }
  L->condition = (C)? C : &(cce_condition_unknown_ptr->root_C.condition_C);
  siglongjmp(L->buffer, (int)CCE_ERROR);
}

__attribute__((hot))
void
cce_retry (cce_location_t * L)
{
  if (L->condition) { cce_condition_final((cce_condition_t*)L->condition); }
  L->condition = &(cce_condition_unknown_ptr->root_C.condition_C);
  siglongjmp(L->buffer, (int)CCE_RETRY);
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
  for (cce_handler_t * H = next; H && H->handler_function; H = next) {
    next = H->next_handler;
    if (true == H->is_cleanup_handler) {
      H->handler_function(L->condition, H);
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
  for (cce_handler_t * H = next; H && H->handler_function; H = next) {
    next = H->next_handler;
    H->handler_function(L->condition, H);
  }
}

/* end of file */
