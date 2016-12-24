/*
  Part of: CCExceptions
  Contents: basic test with exception thrown and no handlers
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

int
main (int argc CCE_UNUSED, const char *const CCE_UNUSED argv[])
{
  /* "if" statement */
  {
    cce_location_t	L;
    bool		flag = false;

    if (cce_location(L)) { // the error handler
      flag = false;
      cce_run_error_handlers(L);
    } else { // the body
      cce_throw(L, NULL);
      flag = true;
      cce_run_cleanup_handlers(L);
    }
    assert(NULL == L->condition);
    assert(false == flag);
  }

  /* "switch" statement, error */
  {
    cce_location_t	L;
    bool		flag = false;

    switch (cce_location(L)) {
    case CCE_ERROR:
      flag = false;
      cce_run_error_handlers(L);
      break;

    default:
      cce_throw(L, NULL);
      flag = true;
      cce_run_cleanup_handlers(L);
    }
    assert(NULL == L->condition);
    assert(false == flag);
  }

  /* "switch" statement, retry */
  {
    cce_location_t	L;
    bool		flag = false;

    switch (cce_location(L)) {
    case CCE_ERROR:
      flag = false;
      cce_run_error_handlers(L);
      break;

    case CCE_RETRY:
      flag = true;
      cce_run_cleanup_handlers(L);
      break;

    default:
      cce_retry(L);
      flag = true;
      cce_run_cleanup_handlers(L);
    }
    assert(true == flag);
  }

  exit(EXIT_SUCCESS);
}

/* end of file */
