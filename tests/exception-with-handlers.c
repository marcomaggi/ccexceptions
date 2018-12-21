/*
  Part of: CCExceptions
  Contents: test with error and clean handlers
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
#include <errno.h>


typedef struct test_no_exception_handler1_t {
  cce_clean_handler_t	handler;
  volatile bool *	flagp;
} test_no_exception_handler1_t;

typedef struct test_no_exception_handler2_t {
  cce_error_handler_t	handler;
  volatile bool *	flagp;
} test_no_exception_handler2_t;

static void
test_no_exception_handler1 (cce_condition_t const * C CCE_UNUSED, cce_handler_t * _data)
{
  test_no_exception_handler1_t *	data = (test_no_exception_handler1_t *)_data;
  *(data->flagp) = true;
}

static void
test_no_exception_handler2 (cce_condition_t const * C CCE_UNUSED, cce_handler_t * _data)
{
  test_no_exception_handler2_t *	data = (test_no_exception_handler2_t *)_data;
  *(data->flagp) = true;
}

static void
test_no_exception (void)
{
  cce_location_t	L[1];
  volatile bool		flag1 = false;
  volatile bool		flag2 = false;
  test_no_exception_handler1_t H1 = { .handler.handler.function = test_no_exception_handler1 , .flagp = &flag1 };
  test_no_exception_handler2_t H2 = { .handler.handler.function = test_no_exception_handler2 , .flagp = &flag2 };

  switch (cce_location(L)) {
  case CCE_ERROR:
    cce_run_catch_handlers(L);
    cce_condition_delete(cce_condition(L));
    break;

  default:
    cce_register_clean_handler(L, &H1.handler);
    cce_register_error_handler(L, &H2.handler);
    cce_run_body_handlers(L);
  }
  assert(true  == flag1);
  assert(false == flag2);
}


typedef struct test_with_error_handler1_t {
  cce_clean_handler_t	handler;
  volatile bool *	flagp;
} test_with_error_handler1_t;

typedef struct test_with_error_handler2_t {
  cce_error_handler_t	handler;
  volatile bool *	flagp;
} test_with_error_handler2_t;

static void
test_with_error_handler1 (cce_condition_t const * C CCE_UNUSED, cce_handler_t * _data)
{
  test_with_error_handler1_t *	data = (test_with_error_handler1_t *)_data;
  *(data->flagp) = true;
}

static void
test_with_error_handler2 (cce_condition_t const * C CCE_UNUSED, cce_handler_t * _data)
{
  test_with_error_handler2_t *	data = (test_with_error_handler2_t *)_data;
  *(data->flagp) = true;
}

static void
test_with_error (void)
{
  cce_location_t	L[1];
  volatile bool		flag1 = false;
  volatile bool		flag2 = false;
  test_with_error_handler1_t H1 = { .handler.handler.function = test_with_error_handler1 , .flagp = &flag1 };
  test_with_error_handler2_t H2 = { .handler.handler.function = test_with_error_handler2 , .flagp = &flag2 };

  switch (cce_location(L)) {
  case CCE_ERROR:
    cce_run_catch_handlers(L);
    cce_condition_delete(cce_condition(L));
    break;

  default:
    cce_register_clean_handler(L, &H1.handler);
    cce_register_error_handler(L, &H2.handler);
    if (1) {
      cce_raise(L, NULL);
    }
    cce_run_body_handlers(L);
  }
  assert(true == flag1);
  assert(true == flag2);
}


/** --------------------------------------------------------------------
 ** Dynamically allocated handlers.
 ** ----------------------------------------------------------------- */

typedef struct test_dynamically_allocated_clean_handler_t	test_dynamically_allocated_clean_handler_t;
typedef struct test_dynamically_allocated_error_handler_t	test_dynamically_allocated_error_handler_t;

struct test_dynamically_allocated_clean_handler_t {
  cce_clean_handler_t	handler;
  bool volatile *	flagp;
};

struct test_dynamically_allocated_error_handler_t {
  cce_error_handler_t	handler;
  bool volatile *	flagp;
};

/* ------------------------------------------------------------------ */
/* Handler functions. */

static void
test_dynamically_allocated_clean_handler (cce_condition_t const * C CCE_UNUSED, cce_handler_t * _H)
{
  CCE_PC(test_dynamically_allocated_clean_handler_t, H, _H);
  free(H->handler.handler.pointer);
  *(H->flagp) = true;
  free(H);
  if (1) { fprintf(stderr, "%s: done\n", __func__); }
}

static void
test_dynamically_allocated_error_handler (cce_condition_t const * C CCE_UNUSED, cce_handler_t * _H)
{
  CCE_PC(test_dynamically_allocated_error_handler_t, H, _H);
  free(H->handler.handler.pointer);
  *(H->flagp) = true;
  free(H);
  if (1) { fprintf(stderr, "%s: done\n", __func__); }
}

/* ------------------------------------------------------------------ */

static test_dynamically_allocated_clean_handler_t *
test_dynamically_allocated_new_clean_handler (cce_location_t * upper_L, bool volatile * flagp)
{
  test_dynamically_allocated_clean_handler_t *	H;

  H = cce_sys_malloc(upper_L, sizeof(test_dynamically_allocated_clean_handler_t));
  H->handler.handler.function	= test_dynamically_allocated_clean_handler;
  H->flagp			= flagp;
  return H;
}

static test_dynamically_allocated_error_handler_t *
test_dynamically_allocated_new_error_handler (cce_location_t * upper_L, bool volatile * flagp)
{
  test_dynamically_allocated_error_handler_t *	H;

  H = cce_sys_malloc(upper_L, sizeof(test_dynamically_allocated_error_handler_t));
  H->handler.handler.function	= test_dynamically_allocated_error_handler;
  H->flagp			= flagp;
  return H;
}

/* ------------------------------------------------------------------ */

static void
test_dynamically_allocated_handlers (void)
{
  cce_location_t	L[1];
  test_dynamically_allocated_clean_handler_t * volatile H1;
  test_dynamically_allocated_error_handler_t * volatile H2;
  volatile bool		flag1 = false;
  volatile bool		flag2 = false;

  if (cce_location(L)) {
    cce_run_catch_handlers_final(L);
  } else {
    H1 = test_dynamically_allocated_new_clean_handler(L, &flag1);
    cce_register_clean_handler(L, (cce_clean_handler_t *)&(H1->handler));

    H2 = test_dynamically_allocated_new_error_handler(L, &flag2);
    cce_register_error_handler(L, (cce_error_handler_t *)&(H2->handler));

    if (1) {
      cce_raise(L, NULL);
    }
    cce_run_body_handlers(L);
  }
  assert(true == flag1);
  assert(true == flag2);
}


int
main (int argc CCE_UNUSED, char const *const argv[] CCE_UNUSED)
{
  if (1) test_no_exception();
  if (1) test_with_error();
  if (1) test_dynamically_allocated_handlers();
  //
  exit(EXIT_SUCCESS);
}

/* end of file */
