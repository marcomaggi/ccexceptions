/*
  Part of: CCExceptions
  Contents: test with error and clean handlers
  Date: Fri Dec 23, 2016

  Abstract



  Copyright (C) 2016-2019 Marco Maggi <marco.maggi-ipsu@poste.it>

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
#include <errno.h>


/** --------------------------------------------------------------------
 ** No exceptions raised.
 ** ----------------------------------------------------------------- */

static void
test_no_exception_handler1 (cce_condition_t const * C CCE_UNUSED, cce_clean_handler_t const * const H)
{
  bool volatile *	flagp = cce_handler_resource_pointer(H);
  *flagp = true;
}

static void
test_no_exception_handler2 (cce_condition_t const * C CCE_UNUSED, cce_error_handler_t const * const H)
{
  bool volatile *	flagp = cce_handler_resource_pointer(H);
  *flagp = true;
}

static void
test_no_exception (void)
{
  cce_location_t	L[1];
  cce_clean_handler_t	H1[1];
  cce_error_handler_t	H2[1];
  volatile bool		flag1 = false;
  volatile bool		flag2 = false;

  if (cce_location(L)) {
    cce_run_catch_handlers_final(L);
  } else {
    cce_init_and_register_handler(L, H1, test_no_exception_handler1, (cce_resource_data_t *)&flag1);
    cce_init_and_register_handler(L, H2, test_no_exception_handler2, (cce_resource_data_t *)&flag2);
    cce_run_body_handlers(L);
  }
  assert(true  == flag1);
  assert(false == flag2);
}


/** --------------------------------------------------------------------
 ** Exception raised.
 ** ----------------------------------------------------------------- */

static void
test_with_error_handler1 (cce_condition_t const * C CCE_UNUSED, cce_clean_handler_t const * const H)
{
  bool *	flagp = cce_handler_resource_pointer(H);
  *flagp = true;
}

static void
test_with_error_handler2 (cce_condition_t const * C CCE_UNUSED, cce_error_handler_t const * const H)
{
  bool *	flagp = cce_handler_resource_pointer(H);
  *flagp = true;
}

static void
test_with_error (void)
{
  cce_location_t	L[1];
  cce_clean_handler_t	H1[1];
  cce_error_handler_t	H2[1];
  volatile bool		flag1 = false;
  volatile bool		flag2 = false;

  if (cce_location(L)) {
    cce_run_catch_handlers_final(L);
  } else {
    cce_init_and_register_handler(L, H1, test_with_error_handler1, (cce_resource_data_t *)&flag1);
    cce_init_and_register_handler(L, H2, test_with_error_handler2, (cce_resource_data_t *)&flag2);
    cce_raise(L, NULL);
  }
  assert(true == flag1);
  assert(true == flag2);
}


/** --------------------------------------------------------------------
 ** Let's go.
 ** ----------------------------------------------------------------- */

int
main (void)
{
  if (1) test_no_exception();
  if (1) test_with_error();
  //
  exit(EXIT_SUCCESS);
}

/* end of file */
