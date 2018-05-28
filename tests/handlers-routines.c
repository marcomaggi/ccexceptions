/*
  Part of: CCExceptions
  Contents: tests with error and clean handlers
  Date: Dec 26, 2016

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


static void
handler1 (cce_condition_t const * C CCE_UNUSED, cce_handler_t * H)
{
  bool *	flagp = H->pointer;
  *flagp = true;
}
static void
handler2 (cce_condition_t const * C CCE_UNUSED, cce_handler_t * H)
{
  bool *	flagp = H->pointer;
  *flagp = true;
}
static void
handler3 (cce_condition_t const * C CCE_UNUSED, cce_handler_t * H)
{
  bool *	flagp = H->pointer;
  *flagp = true;
}


static void
test_just_run_body_handlers()
/* Just run clean handlers. */
{
  cce_location_t	L[1];
  bool			flag1 = false;
  bool			flag2 = false;
  bool			flag3 = false;
  cce_clean_handler_t	H1 = { .handler.function = handler1, .handler.pointer = &flag1 };
  cce_clean_handler_t	H2 = { .handler.function = handler2, .handler.pointer = &flag2 };
  cce_clean_handler_t	H3 = { .handler.function = handler3, .handler.pointer = &flag3 };

  cce_location_init(L);
  cce_register_clean_handler(L, &H1);
  cce_register_clean_handler(L, &H2);
  cce_register_clean_handler(L, &H3);
  cce_run_body_handlers(L);

  assert(true == flag1);
  assert(true == flag2);
  assert(true == flag3);
}


static void
test_just_run_catch_handlers (void)
/* Just run clean handlers. */
{
  cce_location_t	L[1];
  bool			flag1 = false;
  bool			flag2 = false;
  bool			flag3 = false;
  cce_error_handler_t	H1 = { .handler.function = handler1, .handler.pointer = &flag1 };
  cce_error_handler_t	H2 = { .handler.function = handler2, .handler.pointer = &flag2 };
  cce_error_handler_t	H3 = { .handler.function = handler3, .handler.pointer = &flag3 };

  cce_location_init(L);
  cce_register_error_handler(L, &H1);
  cce_register_error_handler(L, &H2);
  cce_register_error_handler(L, &H3);
  cce_run_catch_handlers(L);

  assert(true == flag1);
  assert(true == flag2);
  assert(true == flag3);
}


typedef struct test_amse_t {
  cce_clean_handler_t	handler;
  bool *		flagp;
} test_amse_t;
static void
test_amse_handler (cce_condition_t const * C CCE_UNUSED, cce_handler_t * _H)
{
  test_amse_t *	H = (test_amse_t *)_H;
  void *	P = H->handler.handler.pointer;
  free(P);
  *(H->flagp) = true;
}
static void
test_allocating_memory_success_execution (void)
/* Allocating memory: success execution path. */
{
  cce_location_t	L[1];
  void *		P = NULL;
  bool			flag = false;
  test_amse_t		H = {
    .handler.handler.function	= test_amse_handler,
    .handler.handler.pointer	= P,
    .flagp			= &flag
  };

  switch (cce_location(L)) {
  case CCE_ERROR:
    cce_run_catch_handlers(L);
    break;

  default:
    P = malloc(4096);
    if (P) {
      cce_register_clean_handler(L, &H.handler);
    } else {
      cce_raise(L, NULL);
    }
    // do something here
    cce_run_body_handlers(L);
  }
  assert(true == flag);
}


typedef struct test_amee_t {
  cce_clean_handler_t	handler;
  bool *		flagp;
} test_amee_t;
static void
test_amee_handler (cce_condition_t const * C CCE_UNUSED, cce_handler_t * _H)
{
  test_amee_t *	H = (test_amee_t *)_H;
  void *	P = H->handler.handler.pointer;
  free(P);
  *(H->flagp) = true;
}
static void
test_allocating_memory_exceptional_execution (void)
/* Allocating memory: exceptional execution path. */
{
  cce_location_t	L[1];
  void *		P = NULL;
  bool			flag = false;
  test_amee_t		H = {
    .handler.handler.function	= test_amee_handler,
    .handler.handler.pointer	= P,
    .flagp			= &flag
  };

  switch (cce_location(L)) {
  case CCE_ERROR:
    cce_run_catch_handlers(L);
    break;

  default:
    P = malloc(4096);
    if (P) {
      cce_register_clean_handler(L, &H.handler);
    } else {
      cce_raise(L, NULL);
    }
    // do something here
    if (1) {
      cce_raise(L, NULL);
    }
    cce_run_body_handlers(L);
  }
  assert(true == flag);
}


static void
test_csse_constructor_handler (cce_condition_t const * C CCE_UNUSED, cce_handler_t * H)
{
  void **	PP = H->pointer;
  void *	P  = *PP;
  free(P);
}
static void *
test_csse_constructor (cce_location_t * upper_L)
{
  cce_location_t	L[1];
  void *		P = NULL;
  cce_error_handler_t	H = {
    .handler.function	= test_csse_constructor_handler,
    .handler.pointer	= &P
  };

  switch (cce_location(L)) {
  case CCE_ERROR:
    cce_run_catch_handlers(L);
    cce_raise(upper_L, NULL);
    break;

  default:
    P = malloc(4096);
    if (P) {
      cce_register_error_handler(L, &H);
    } else {
      cce_raise(L, NULL);
    }
    // do something here
    if (0) {
      cce_raise(L, NULL);
    }
    cce_run_body_handlers(L);
  }
  return P;
}

/* ------------------------------------------------------------------ */

typedef struct test_csse_t {
  cce_clean_handler_t	handler;
  bool *		flagp;
} test_csse_t;

static void
test_csse_caller_handler (cce_condition_t const * C CCE_UNUSED, cce_handler_t * _H)
{
  test_csse_t *	H  = (test_csse_t *)_H;
  void **	PP = H->handler.handler.pointer;
  void *	P  = *PP;
  free(P);
  *(H->flagp) = true;
}
static void
test_csse_caller (void)
{
  cce_location_t	L[1];
  void *		P;
  bool			flag = false;
  test_csse_t		H = {
    .handler.handler.function	= test_csse_caller_handler,
    .handler.handler.pointer	= &P,
    .flagp			= &flag
  };

  switch (cce_location(L)) {
  case CCE_ERROR:
    cce_run_catch_handlers(L);
    break;

  default:
    P = test_csse_constructor(L);
    assert(NULL != P);
    cce_register_clean_handler(L, &H.handler);
    // do_something_with(P);
    cce_run_body_handlers(L);
  }
  assert(true == flag);
}

static void
test_constructor_scheme_success_execution (void)
/* Constructor scheme: success path. */
{
  test_csse_caller();
}


static void
test_csee_constructor_handler (cce_condition_t const * C CCE_UNUSED, cce_handler_t * H)
{
  void **	PP = H->pointer;
  void *	P  = *PP;
  free(P);
}
static void *
test_csee_constructor (cce_location_t * upper_L)
{
  cce_location_t	L[1];
  void *		P = NULL;
  cce_error_handler_t	H = {
    .handler.function	= test_csee_constructor_handler,
    .handler.pointer	= &P
  };

  switch (cce_location(L)) {
  case CCE_ERROR:
    cce_run_catch_handlers(L);
    cce_raise(upper_L, NULL);
    break;

  default:
    P = malloc(4096);
    if (P) {
      cce_register_error_handler(L, &H);
    } else {
      cce_raise(L, NULL);
    }
    // do something here
    if (1) {
      cce_raise(L, NULL);
    }
    cce_run_body_handlers(L);
  }
  return P;
}

/* ------------------------------------------------------------------ */

typedef struct test_csee_t {
  cce_clean_handler_t	handler;
  bool *		flagp;
} test_csee_t;

static void
test_csee_caller_handler (cce_condition_t const * C CCE_UNUSED, cce_handler_t * _H)
{
  test_csee_t *	H  = (test_csee_t *)_H;
  void **	PP = H->handler.handler.pointer;
  void *	P  = *PP;
  free(P);
  *(H->flagp) = true;
}

static void
test_constructor_scheme_exceptional_execution (void)
/* Constructor scheme: exceptional path. */
{
  cce_location_t	L[1];
  void *		P;
  bool			flag = false;
  test_csee_t		H = {
    .handler.handler.function	= test_csee_caller_handler,
    .handler.handler.pointer	= &P,
    .flagp			= &flag
  };

  switch (cce_location(L)) {
  case CCE_ERROR:
    cce_run_catch_handlers(L);
    flag = true;
    break;

  default:
    P = test_csee_constructor(L);
    assert(NULL != P);
    cce_register_clean_handler(L, &H.handler);
    // do_something_with(P);
    cce_run_body_handlers(L);
  }
  assert(true == flag);
}


static void
handler_removal_function (cce_condition_t const * C CCE_UNUSED, cce_handler_t * H)
{
  bool	* flag = H->pointer;
  *flag = true;
}

void
test_handler_removal_1_0 (void)
/* No handler removal in this function: it just tests the code logic. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	H1, H2, H3;
  bool			flag1 = false, flag2 = false, flag3 = false;

  if (cce_location(L)) {
    cce_run_catch_handlers_final(L);
  } else {
    H1.handler.function = handler_removal_function;
    H2.handler.function = handler_removal_function;
    H3.handler.function = handler_removal_function;
    H1.handler.pointer  = &flag1;
    H2.handler.pointer  = &flag2;
    H3.handler.pointer  = &flag3;
    cce_register_clean_handler(L, &H1);
    cce_register_clean_handler(L, &H2);
    cce_register_clean_handler(L, &H3);
    cce_run_body_handlers(L);
  }

  assert(true == flag1);
  assert(true == flag2);
  assert(true == flag3);
}

void
test_handler_removal_1_1 (void)
/* Remove the first handler. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	H1, H2, H3;
  bool			flag1 = false, flag2 = false, flag3 = false;

  if (cce_location(L)) {
    cce_run_catch_handlers_final(L);
  } else {
    H1.handler.function = handler_removal_function;
    H2.handler.function = handler_removal_function;
    H3.handler.function = handler_removal_function;
    H1.handler.pointer  = &flag1;
    H2.handler.pointer  = &flag2;
    H3.handler.pointer  = &flag3;
    cce_register_clean_handler(L, &H1);
    cce_register_clean_handler(L, &H2);
    cce_register_clean_handler(L, &H3);
    cce_forget_handler(L, &H1.handler);
    cce_run_body_handlers(L);
  }

  assert(false == flag1);
  assert(true  == flag2);
  assert(true  == flag3);
}

void
test_handler_removal_1_2 (void)
/* Remove the second handler. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	H1, H2, H3;
  bool			flag1 = false, flag2 = false, flag3 = false;

  if (cce_location(L)) {
    cce_run_catch_handlers_final(L);
  } else {
    H1.handler.function = handler_removal_function;
    H2.handler.function = handler_removal_function;
    H3.handler.function = handler_removal_function;
    H1.handler.pointer  = &flag1;
    H2.handler.pointer  = &flag2;
    H3.handler.pointer  = &flag3;
    cce_register_clean_handler(L, &H1);
    cce_register_clean_handler(L, &H2);
    cce_register_clean_handler(L, &H3);
    cce_forget_handler(L, &H2.handler);
    cce_run_body_handlers(L);
  }

  assert(true  == flag1);
  assert(false == flag2);
  assert(true  == flag3);
}

void
test_handler_removal_1_3 (void)
/* Remove the third handler. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	H1, H2, H3;
  bool			flag1 = false, flag2 = false, flag3 = false;

  if (cce_location(L)) {
    cce_run_catch_handlers_final(L);
  } else {
    H1.handler.function = handler_removal_function;
    H2.handler.function = handler_removal_function;
    H3.handler.function = handler_removal_function;
    H1.handler.pointer  = &flag1;
    H2.handler.pointer  = &flag2;
    H3.handler.pointer  = &flag3;
    cce_register_clean_handler(L, &H1);
    cce_register_clean_handler(L, &H2);
    cce_register_clean_handler(L, &H3);
    cce_forget_handler(L, &H3.handler);
    cce_run_body_handlers(L);
  }

  assert(true  == flag1);
  assert(true  == flag2);
  assert(false == flag3);
}


int
main (int argc CCE_UNUSED, char const *const argv[] CCE_UNUSED)
{
  test_just_run_body_handlers();
  test_just_run_catch_handlers();
  test_allocating_memory_success_execution();
  test_allocating_memory_exceptional_execution();
  test_constructor_scheme_success_execution();
  test_constructor_scheme_exceptional_execution();

  test_handler_removal_1_0();
  test_handler_removal_1_1();
  test_handler_removal_1_2();
  test_handler_removal_1_3();

  exit(EXIT_SUCCESS);
}

/* end of file */
