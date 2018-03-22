/*
  Part of: CCExceptions
  Contents: test with cleanup handler
  Date: Fri Dec 23, 2016

  Abstract



  Copyright (C) 2016, 2017, 2018 Marco Maggi <marco.maggi-ipsu@poste.it>

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


#include <ccexceptions.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct handler1_t {
  cce_handler_t		exception_handler[1];
  bool *		flagp;
} handler1_t;
static void
handler1 (cce_condition_t const * C CCE_UNUSED, cce_handler_t * _data)
{
  handler1_t *	data = (handler1_t *)_data;
  *(data->flagp) = true;
}

typedef struct handler2_t {
  cce_handler_t		exception_handler[1];
  bool *		flagp;
} handler2_t;
static void
handler2 (cce_condition_t const * C CCE_UNUSED, cce_handler_t * _data)
{
  handler1_t *	data = (handler1_t *)_data;
  *(data->flagp) = true;
}

int
main (int argc CCE_UNUSED, char const *const argv[] CCE_UNUSED)
{
  /* no exception */
  {
    cce_location_t	L[1];
    bool		flag1 = false;
    bool		flag2 = false;
    handler1_t		H1 = { .exception_handler[0] = { .function = handler1 }, .flagp = &flag1 };
    handler2_t		H2 = { .exception_handler[0] = { .function = handler2 }, .flagp = &flag2 };

    switch (cce_location(L)) {
    case CCE_ERROR:
      cce_run_error_handlers(L);
      break;

    default:
      cce_register_cleanup_handler(L, H1.exception_handler);
      cce_register_cleanup_handler(L, H2.exception_handler);
      cce_run_cleanup_handlers(L);
    }
    assert(true == flag1);
    assert(true == flag2);
  }

  /* with error */
  {
    cce_location_t	L[1];
    bool		flag1 = false;
    bool		flag2 = false;
    handler1_t		H1 = { .exception_handler[0] = { .function = handler1 }, .flagp = &flag1 };
    handler2_t		H2 = { .exception_handler[0] = { .function = handler2 }, .flagp = &flag2 };

    switch (cce_location(L)) {
    case CCE_ERROR:
      cce_run_error_handlers(L);
      break;

    default:
      cce_register_cleanup_handler(L, H1.exception_handler);
      cce_register_cleanup_handler(L, H2.exception_handler);
      cce_raise(L, NULL);
      cce_run_cleanup_handlers(L);
    }
    assert(true == flag1);
    assert(true == flag2);
  }

  exit(EXIT_SUCCESS);
}

/* end of file */
