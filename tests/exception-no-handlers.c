/*
  Part of: CCExceptions
  Contents: basic test with exception thrown and no handlers
  Date: Fri Dec 23, 2016

  Abstract



  Copyright (C) 2016, 2017, 2018, 2019, 2020 Marco Maggi <mrc.mgg@gmail.com>

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


#include <ccexceptions.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int
main (int argc CCLIB_UNUSED, char const *const CCLIB_UNUSED argv[] CCLIB_UNUSED)
{
  /* "if" statement */
  {
    cce_location_t	L[1];
    bool		flag = false;

    if (cce_location(L)) { // the error handler
      flag = false;
      cce_run_catch_handlers_final(L);
    } else { // the body
      cce_raise(L, NULL);
      flag = true;
      cce_run_body_handlers(L);
    }
    assert(false == flag);
  }

  /* "switch" statement, error */
  {
    cce_location_t	L[1];
    bool		flag = false;

    switch (cce_location(L)) {
    case CCE_ERROR:
      flag = false;
      cce_run_catch_handlers_final(L);
      break;

    default:
      cce_raise(L, NULL);
      flag = true;
      cce_run_body_handlers(L);
    }
    assert(false == flag);
  }

  exit(EXIT_SUCCESS);
}

/* end of file */
