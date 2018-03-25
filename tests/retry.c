/*
  Part of: CCExceptions
  Contents: tests retrying features
  Date: Mar 25, 2018

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

#include <ccexceptions.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


/** --------------------------------------------------------------------
 ** Retrying from body.
 ** ----------------------------------------------------------------- */

void
test_retry_from_body (void)
{
  cce_location_t	L[1];
  int volatile		body_flag   = 0;
  int volatile		except_flag = 0;
  int volatile		retry_flag  = 0;

  if (cce_location(L)) {
    ++except_flag;
    cce_run_error_handlers_final(L);
  } else {
    ++body_flag;
    if (0 == retry_flag) {
      ++retry_flag;
      cce_retry(L);
    }
    cce_run_cleanup_handlers(L);
  }
  fprintf(stderr, "%s: body_flag=%d, retry_flag=%d, except_flag=%d\n", __func__,
	  body_flag, retry_flag, except_flag);
  assert(2 == body_flag);
  assert(1 == retry_flag);
  assert(0 == except_flag);
}

void
test_retry_from_body_twice (void)
{
  cce_location_t	L[1];
  int volatile		body_flag    = 0;
  int volatile		except_flag  = 0;
  int volatile		retry_flag   = 0;
  int volatile		reretry_flag = 0;

  if (cce_location(L)) {
    ++except_flag;
    cce_run_error_handlers_final(L);
  } else {
    ++body_flag;
    if (0 == retry_flag) {
      ++retry_flag;
      cce_retry(L);
    }
    if (0 == reretry_flag) {
      ++reretry_flag;
      cce_retry(L);
    }
    cce_run_cleanup_handlers(L);
  }
  fprintf(stderr, "%s: body_flag=%d, retry_flag=%d, reretry_flag=%d, except_flag=%d\n", __func__,
	  body_flag, retry_flag, reretry_flag, except_flag);
  assert(3 == body_flag);
  assert(1 == retry_flag);
  assert(1 == reretry_flag);
  assert(0 == except_flag);
}


/** --------------------------------------------------------------------
 ** Retrying from handler.
 ** ----------------------------------------------------------------- */

void
test_retry_from_handler (void)
{
  cce_location_t	L[1];
  int volatile		body_flag   = 0;
  int volatile		except_flag = 0;
  int volatile		retry_flag  = 0;

  if (cce_location(L)) {
    ++except_flag;
    if (0 == retry_flag) {
      ++retry_flag;
      cce_retry(L);
    }
    cce_run_error_handlers_final(L);
  } else {
    ++body_flag;
    if (0 == retry_flag) {
      cce_raise(L, cce_condition_new_unknown());
    }
    cce_run_cleanup_handlers(L);
  }
  fprintf(stderr, "%s: body_flag=%d, retry_flag=%d, except_flag=%d\n", __func__,
	  body_flag, retry_flag, except_flag);
  assert(2 == body_flag);
  assert(1 == retry_flag);
  assert(1 == except_flag);
}

void
test_retry_from_handler_twice (void)
{
  cce_location_t	L[1];
  int volatile		body_flag    = 0;
  int volatile		except_flag  = 0;
  int volatile		retry_flag   = 0;
  int volatile		reretry_flag = 0;

  if (cce_location(L)) {
    ++except_flag;
    if (0 == retry_flag) {
      ++retry_flag;
      cce_retry(L);
    }
    if (0 == reretry_flag) {
      ++reretry_flag;
      cce_retry(L);
    }
    cce_run_error_handlers_final(L);
  } else {
    ++body_flag;
    if (2 > retry_flag) {
      cce_raise(L, cce_condition_new_unknown());
    }
    cce_run_cleanup_handlers(L);
  }
  fprintf(stderr, "%s: body_flag=%d, retry_flag=%d, reretry_flag=%d, except_flag=%d\n", __func__,
	  body_flag, retry_flag, reretry_flag, except_flag);
  assert(3 == body_flag);
  assert(1 == retry_flag);
  assert(1 == reretry_flag);
  assert(3 == except_flag);
}


int
main (void)
{
  if (1) { test_retry_from_body(); }
  if (1) { test_retry_from_body_twice(); }
  if (1) { test_retry_from_handler(); }
  if (1) { test_retry_from_handler_twice(); }

  exit(EXIT_SUCCESS);
}

/* end of file */
