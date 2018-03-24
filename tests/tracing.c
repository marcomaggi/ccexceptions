/*
  Part of: CCExceptions
  Contents: tests tracing features
  Date: Feb 24, 2018

  Abstract



  Copyright (C) 2018 Marco Maggi <marco.maggi-ipsu@poste.it>

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

#define CCEXCEPTIONS_TRACE	1
#include <ccexceptions.h>
#include <stdio.h>
#include <stdlib.h>


/** --------------------------------------------------------------------
 ** Tracing test.
 ** ----------------------------------------------------------------- */

void
test_tracing_sub_sub_sub (cce_destination_t upper_L)
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    cce_raise(L, cce_condition_new_unknown());
    cce_run_cleanup_handlers(L);
  }
}

void
test_tracing_sub_sub (cce_destination_t upper_L)
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    test_tracing_sub_sub_sub(L);
    cce_run_cleanup_handlers(L);
  }
}

void
test_tracing_sub (cce_destination_t upper_L)
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    test_tracing_sub_sub(L);
    cce_run_cleanup_handlers(L);
  }
}

void
test_tracing (void)
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_error_handlers_final(L);
  } else {
    test_tracing_sub(L);
    cce_run_cleanup_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Retrying test.
 ** ----------------------------------------------------------------- */

void
test_retrying_sub (cce_destination_t upper_L, bool * retry_flag_p)
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    if (*retry_flag_p) {
      *retry_flag_p = false;
      cce_retry(L);
    }
    cce_run_cleanup_handlers(L);
  }
}

void
test_retrying (void)
{
  cce_location_t	L[1];
  bool			retry_flag = true;

  if (cce_location(L)) {
    cce_run_error_handlers_final(L);
  } else {
    test_retrying_sub(L, &retry_flag);
    cce_run_cleanup_handlers(L);
  }
}


int
main (void)
{
  if (1) { test_tracing(); }
  if (1) { test_retrying(); }

  exit(EXIT_SUCCESS);
}

/* end of file */
