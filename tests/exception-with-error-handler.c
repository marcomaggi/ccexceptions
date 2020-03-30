/*
  Part of: CCExceptions
  Contents: test with error handler
  Date: Fri Dec 23, 2016

  Abstract

	Test raising an exception with a error handler.

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

#include <ccexceptions.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


/** --------------------------------------------------------------------
 ** Handlers.
 ** ----------------------------------------------------------------- */

static void
handler1 (cce_condition_t const * const C CCLIB_UNUSED, cce_error_handler_t const * const H)
{
  bool	* flagp = cce_handler_resource_pointer(H);

  *flagp = true;
}

static void
handler2 (cce_condition_t const * const C CCLIB_UNUSED, cce_error_handler_t const * const H)
{
  bool	* flagp = cce_handler_resource_pointer(H);

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
    volatile bool	flag1 = false;
    volatile bool	flag2 = false;
    cce_error_handler_t	H1[1];
    cce_error_handler_t	H2[1];

    if (cce_location(L)) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_init_handler(H1, handler1, cce_resource_pointer(&flag1));
      cce_init_handler(H2, handler2, cce_resource_pointer(&flag2));

      cce_register_handler(L, H1);
      cce_register_handler(L, H2);
      cce_run_body_handlers(L);
    }
    assert(false == flag1);
    assert(false == flag2);
  }

  /* raise an exception */
  {
    cce_location_t	L[1];
    bool		flag1 = false;
    bool		flag2 = false;
    cce_error_handler_t	H1[1];
    cce_error_handler_t	H2[1];

    if (cce_location(L)) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_init_handler(H1, handler1, cce_resource_pointer(&flag1));
      cce_init_handler(H2, handler2, cce_resource_pointer(&flag2));

      cce_register_handler(L, H1);
      cce_register_handler(L, H2);
      cce_raise(L, NULL);
      cce_run_body_handlers(L);
    }
    assert(true == flag1);
    assert(true == flag2);
  }

  exit(EXIT_SUCCESS);
}

/* end of file */
