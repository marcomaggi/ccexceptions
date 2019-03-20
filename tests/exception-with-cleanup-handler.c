/*
  Part of: CCExceptions
  Contents: test with clean handler
  Date: Fri Dec 23, 2016

  Abstract

	Test raising an exception with a clean handler.

  Copyright (C) 2016, 2017, 2018, 2019 Marco Maggi <marco.maggi-ipsu@poste.it>

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

#include <ccexceptions.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


/** --------------------------------------------------------------------
 ** Handlers.
 ** ----------------------------------------------------------------- */

static void
handler1 (cce_condition_t const * const C CCE_UNUSED, cce_handler_t * _H)
{
  CCE_PC(cce_clean_handler_t const, const H, _H);
  bool	* flagp = cce_handler_handler(H)->pointer;

  *flagp = true;
}

static void
handler2 (cce_condition_t const * const C CCE_UNUSED, cce_handler_t * _H)
{
  CCE_PC(cce_clean_handler_t const , const H, _H);
  bool	* flagp = cce_handler_handler(H)->pointer;

  *flagp = true;
}


/** --------------------------------------------------------------------
 ** Let's go.
 ** ----------------------------------------------------------------- */

int
main (void)
{
  /* no exception */
  {
    cce_location_t	L[1];
    bool	flag1 = false;
    bool	flag2 = false;
    cce_clean_handler_t	H1[1];
    cce_clean_handler_t	H2[1];

    if (cce_location(L)) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_init_clean_handler(H1, &flag1, handler1);
      cce_init_clean_handler(H2, &flag2, handler2);

      cce_register_clean_handler(L, H1);
      cce_register_clean_handler(L, H2);
      cce_run_body_handlers(L);
    }
    assert(true == flag1);
    assert(true == flag2);
  }

  /* raise an exception */
  {
    cce_location_t	L[1];
    bool	flag1 = false;
    bool	flag2 = false;
    cce_clean_handler_t	H1[1];
    cce_clean_handler_t	H2[1];

    if (cce_location(L)) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_init_clean_handler(H1, &flag1, handler1);
      cce_init_clean_handler(H2, &flag2, handler2);

      cce_register_clean_handler(L, H1);
      cce_register_clean_handler(L, H2);
      cce_raise(L, NULL);
      cce_run_body_handlers(L);
    }
    assert(true == flag1);
    assert(true == flag2);
  }

  exit(EXIT_SUCCESS);
}

/* end of file */
