/*
  Part of: CCExceptions
  Contents: test with error handler
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


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


/** --------------------------------------------------------------------
 ** Handlers definitions.
 ** ----------------------------------------------------------------- */

typedef struct handler1_t	handler1_t;

struct handler1_t {
  cce_error_handler_t	handler;
  bool volatile *	flagp;
};

static void
handler1 (cce_condition_t const * C CCE_UNUSED, cce_handler_t * _H)
{
  CCE_PC(handler1_t, H, _H);
  *(H->flagp) = true;
}

/* ------------------------------------------------------------------ */

typedef struct handler2_t	handler2_t;

struct handler2_t {
  cce_error_handler_t	handler;
  bool volatile *	flagp;
};

static void
handler2 (cce_condition_t const * C CCE_UNUSED, cce_handler_t * _H)
{
  CCE_PC(handler1_t, H, _H);
  *(H->flagp) = true;
}


int
main (void)
{
  /* no exception */
  {
    cce_location_t	L[1];
    bool volatile	flag1 = false;
    bool volatile	flag2 = false;
    handler1_t		H1 = { .handler.handler = { .function = handler1 }, .flagp = &flag1 };
    handler2_t		H2 = { .handler.handler = { .function = handler2 }, .flagp = &flag2 };

    switch (cce_location(L)) {
    case CCE_ERROR:
      cce_run_catch_handlers(L);
      break;

    default:
      cce_register_error_handler(L, &H1.handler);
      cce_register_error_handler(L, &H2.handler);
      cce_run_body_handlers(L);
    }
    assert(false == flag1);
    assert(false == flag2);
  }

  /* with error */
  {
    cce_location_t	L[1];
    bool volatile	flag1 = false;
    bool volatile	flag2 = false;
    handler1_t		H1 = { .handler.handler = { .function = handler1 }, .flagp = &flag1 };
    handler2_t		H2 = { .handler.handler = { .function = handler2 }, .flagp = &flag2 };

    switch (cce_location(L)) {
    case CCE_ERROR:
      cce_run_catch_handlers(L);
      break;

    default:
      cce_register_error_handler(L, &H1.handler);
      cce_register_error_handler(L, &H2.handler);
      if (1) {
	cce_raise(L, NULL);
      }
      cce_run_body_handlers(L);
    }
    assert(true == flag1);
    assert(true == flag2);
  }

  exit(EXIT_SUCCESS);
}

/* end of file */
