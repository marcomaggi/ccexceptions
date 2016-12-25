/*
  Part of: CCExceptions
  Contents: test with error and cleanup handlers
  Date: Fri Dec 23, 2016

  Abstract



  Copyright (C) 2016 Marco Maggi <marco.maggi-ipsu@poste.it>

  This is free software; you can  redistribute it and/or modify it under
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


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ccexceptions.h>

typedef struct handler1_t {
  cce_handler_tag_t	handler;
  bool *		flagp;
} handler1_t;
static void
handler1 (cce_location_tag_t * L, void * _data)
{
  handler1_t *	data = _data;
  *(data->flagp) = true;
}

typedef struct handler2_t {
  cce_handler_tag_t	handler;
  bool *		flagp;
} handler2_t;
static void
handler2 (cce_location_tag_t * L, void * _data)
{
  handler1_t *	data = _data;
  *(data->flagp) = true;
}

int
main (int argc CCE_UNUSED, const char *const CCE_UNUSED argv[])
{
  /* no exception */
  {
    cce_location_t	L;
    bool		flag1 = false;
    bool		flag2 = false;
    handler1_t		H1 = { .handler.handler_function = handler1, .flagp = &flag1 };
    handler2_t		H2 = { .handler.handler_function = handler2, .flagp = &flag2 };

    switch (cce_location(L)) {
    case CCE_ERROR:
      cce_run_error_handlers(L);
      break;

    default:
      cce_register_cleanup_handler(L, &H1);
      cce_register_error_handler(L, &H2);
      cce_run_cleanup_handlers(L);
    }
    assert(true  == flag1);
    assert(false == flag2);
  }

  /* with error */
  {
    cce_location_t	L;
    bool		flag1 = false;
    bool		flag2 = false;
    handler1_t		H1 = { .handler.handler_function = handler1, .flagp = &flag1 };
    handler2_t		H2 = { .handler.handler_function = handler2, .flagp = &flag2 };

    switch (cce_location(L)) {
    case CCE_ERROR:
      cce_run_error_handlers(L);
      break;

    default:
      cce_register_cleanup_handler(L, &H1);
      cce_register_error_handler(L, &H2);
      if (1) {
	cce_raise(L, NULL);
      }
      cce_run_cleanup_handlers(L);
    }
    assert(NULL == L->condition);
    assert(true == flag1);
    assert(true == flag2);
  }

  /* with retry */
  {
    cce_location_t	L;
    bool		flag1 = false;
    bool		flag2 = false;
    handler1_t		H1 = { .handler.handler_function = handler1, .flagp = &flag1 };
    handler2_t		H2 = { .handler.handler_function = handler2, .flagp = &flag2 };

    switch (cce_location(L)) {
    case CCE_ERROR:
      cce_run_error_handlers(L);
      break;

    case CCE_SUCCESS:
      cce_register_cleanup_handler(L, &H1);
      cce_register_error_handler(L, &H2);
      if (1) {
	cce_retry(L);
      }
      // else fall through

    default:
      cce_run_cleanup_handlers(L);
    }
    assert(NULL == L->condition);
    assert(true  == flag1);
    assert(false == flag2);
  }

  exit(EXIT_SUCCESS);
}

/* end of file */
