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

void
cce_location_init (cce_location_tag_t * L)
{
  L->next_handler	= NULL;
  L->condition		= NULL;
}
cce_condition_t *
cce_location_condition (cce_location_tag_t * L)
{
  return (cce_condition_t *) L->condition;
}
void
cce_raise (struct cce_location_tag_t * L, const cce_condition_t * condition)
{
  L->condition		= (condition)? condition : cce_unknown_condition;
  longjmp(L->buffer, (int)CCE_ERROR);
}
void
cce_retry (struct cce_location_tag_t * L)
{
  L->condition		= (cce_condition_t *)cce_unknown_condition;
  longjmp(L->buffer, (int)CCE_RETRY);
}
void
cce_register_cleanup_handler (cce_location_tag_t * L, void * _H)
{
  cce_handler_tag_t *	H = _H;
  H->is_cleanup_handler = true;
  H->next_handler = L->next_handler;
  L->next_handler = H;
}
void
cce_register_error_handler (cce_location_tag_t * L, void * _H)
{
  cce_handler_tag_t *	H = _H;
  H->is_cleanup_handler = false;
  H->next_handler = L->next_handler;
  L->next_handler = H;
}
void
cce_run_cleanup_handlers (cce_location_tag_t * L)
{
  for (cce_handler_tag_t * H = L->next_handler; H && H->handler_function; H = H->next_handler) {
    if (true == H->is_cleanup_handler) {
      H->handler_function(L, H);
      /* Null the  handler pointer so  that we do  not call it  twice by
	 mistake. */
      H->handler_function = NULL;
    }
  }
}
void
cce_run_error_handlers (cce_location_tag_t * L)
{
  for (cce_handler_tag_t * H = L->next_handler; H && H->handler_function; H = H->next_handler) {
    H->handler_function(L, H);
    /* Null  the handler  pointer so  that we  do not  call it  twice by
       mistake. */
    H->handler_function = NULL;
  }
}

/* end of file */
