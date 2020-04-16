/*
  Part of: CCExceptions
  Contents: tests with error and clean handlers
  Date: Dec 26, 2016

  Abstract



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
 ** Just run body handlers.
 ** ----------------------------------------------------------------- */

static void
just_run_body_handler1 (cce_condition_t const * C CCLIB_UNUSED, cce_clean_handler_t const * const H)
{
  bool *	flagp = cce_handler_resource_pointer(H);
  *flagp = true;
}

static void
just_run_body_handler2 (cce_condition_t const * C CCLIB_UNUSED, cce_clean_handler_t const * const H)
{
  bool *	flagp = cce_handler_resource_pointer(H);
  *flagp = true;
}

static void
just_run_body_handler3 (cce_condition_t const * C CCLIB_UNUSED, cce_clean_handler_t const * const H)
{
  bool *	flagp = cce_handler_resource_pointer(H);
  *flagp = true;
}

/* ------------------------------------------------------------------ */

static void
test_just_run_body_handlers()
/* Just run clean handlers. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	H1;
  cce_clean_handler_t	H2;
  cce_clean_handler_t	H3;
  bool			flag1 = false;
  bool			flag2 = false;
  bool			flag3 = false;

  cce_location_init(L);
  cce_init_handler(&H1, just_run_body_handler1, cce_resource_pointer(&flag1));
  cce_init_handler(&H2, just_run_body_handler2, cce_resource_pointer(&flag2));
  cce_init_handler(&H3, just_run_body_handler3, cce_resource_pointer(&flag3));
  cce_register_handler(L, &H1);
  cce_register_handler(L, &H2);
  cce_register_handler(L, &H3);
  cce_run_body_handlers(L);

  assert(true == flag1);
  assert(true == flag2);
  assert(true == flag3);
}


/** --------------------------------------------------------------------
 ** Just run body handlers.
 ** ----------------------------------------------------------------- */

static void
just_run_catch_handler1 (cce_condition_t const * C CCLIB_UNUSED, cce_error_handler_t const * const H)
{
  bool *	flagp = cce_handler_resource_pointer(H);
  *flagp = true;
}

static void
just_run_catch_handler2 (cce_condition_t const * C CCLIB_UNUSED, cce_error_handler_t const * const H)
{
  bool *	flagp = cce_handler_resource_pointer(H);
  *flagp = true;
}

static void
just_run_catch_handler3 (cce_condition_t const * C CCLIB_UNUSED, cce_error_handler_t const * const H)
{
  bool *	flagp = cce_handler_resource_pointer(H);
  *flagp = true;
}

/* ------------------------------------------------------------------ */

static void
test_just_run_catch_handlers (void)
/* Just run clean handlers. */
{
  cce_location_t	L[1];
  cce_error_handler_t	H1;
  cce_error_handler_t	H2;
  cce_error_handler_t	H3;
  bool			flag1 = false;
  bool			flag2 = false;
  bool			flag3 = false;

  cce_location_init(L);
  cce_init_handler(&H1, just_run_catch_handler1, cce_resource_pointer(&flag1));
  cce_init_handler(&H2, just_run_catch_handler2, cce_resource_pointer(&flag2));
  cce_init_handler(&H3, just_run_catch_handler3, cce_resource_pointer(&flag3));
  cce_register_handler(L, &H1);
  cce_register_handler(L, &H2);
  cce_register_handler(L, &H3);
  cce_run_catch_handlers(L);

  assert(true == flag1);
  assert(true == flag2);
  assert(true == flag3);
}


/** --------------------------------------------------------------------
 ** Allocating memory with successful execution.
 ** ----------------------------------------------------------------- */

CCLIB_STRUCT_TYPEDEF(test_amse_t);

struct test_amse_t {
  cce_clean_handler_t	handler;
  bool volatile *	flagp;
};

static void
test_amse_handler (cce_condition_t const * C CCLIB_UNUSED, cce_clean_handler_t const * const H)
{
  void *	P = cce_handler_resource_pointer(H);
  free(P);
  {
    CCLIB_PC(test_amse_t, W, H);
    *(W->flagp) = true;
  }
}

static void
test_allocating_memory_success_execution (void)
/* Allocating memory: success execution path. */
{
  cce_location_t	L[1];
  void *		P = NULL;
  bool volatile		flag = false;
  test_amse_t		H = { .flagp = &flag };

  if (cce_location(L)) {
    cce_run_catch_handlers_final(L);
  } else {
    P = malloc(4096);
    if (P) {
      cce_init_and_register_handler(L, &(H.handler), test_amse_handler, P);
    } else {
      cce_raise(L, NULL);
    }
    // do something here
    cce_run_body_handlers(L);
  }
  assert(true == flag);
}


/** --------------------------------------------------------------------
 ** Allocating memory with error execution.
 ** ----------------------------------------------------------------- */

typedef struct test_amee_t {
  cce_clean_handler_t	handler;
  bool volatile *	flagp;
} test_amee_t;

static void
test_amee_handler (cce_condition_t const * C CCLIB_UNUSED, cce_clean_handler_t const * const H)
{
  void *	P = cce_handler_resource_pointer(H);
  free(P);
  {
    CCLIB_PC(test_amee_t, W, H);
    *(W->flagp) = true;
  }
}

static void
test_allocating_memory_exceptional_execution (void)
/* Allocating memory: exceptional execution path. */
{
  cce_location_t	L[1];
  void *		P = NULL;
  bool volatile		flag = false;
  test_amee_t		H = { .flagp = &flag };

  if (cce_location(L)) {
    cce_run_catch_handlers_final(L);
  } else {
    P = malloc(4096);
    if (P) {
      cce_init_and_register_handler(L, &(H.handler), test_amee_handler, P);
    } else {
      cce_raise(L, NULL);
    }
    // do something here
    cce_raise(L, NULL);
  }
  assert(true == flag);
}


/** --------------------------------------------------------------------
 ** Constructor scheme with successful execution.
 ** ----------------------------------------------------------------- */

static void
test_csse_constructor_handler (cce_condition_t const * C CCLIB_UNUSED, cce_error_handler_t const * const H)
{
  void **	PP = cce_handler_resource_pointer(H);
  void *	P  = *PP;
  free(P);
}

static void *
test_csse_constructor (cce_location_t * upper_L)
{
  cce_location_t	L[1];
  void *		P = NULL;
  cce_error_handler_t	H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(upper_L, L);
  } else {
    P = malloc(4096);
    if (P) {
      cce_init_and_register_handler(L, H, test_csse_constructor_handler, cce_resource_pointer(&P));
    } else {
      cce_raise(L, NULL);
    }
    // do_something_with(P);
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
  bool volatile *	flagp;
} test_csse_t;

static void
test_csse_caller_handler (cce_condition_t const * C CCLIB_UNUSED, cce_clean_handler_t const * const H)
{
  void **	PP = cce_handler_resource_pointer(H);
  void *	P  = *PP;
  free(P);
  {
    CCLIB_PC(test_csse_t, W, H);
    *(W->flagp) = true;
  }
}

static void
test_csse_caller (void)
{
  cce_location_t	L[1];
  bool volatile		flag = false;
  test_csse_t		H = { .flagp = &flag };

  if (cce_location(L)) {
    cce_run_catch_handlers_final(L);
  } else {
    void *	P = test_csse_constructor(L);
    assert(NULL != P);
    cce_init_and_register_handler(L, &H.handler, test_csse_caller_handler, P);
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


/** --------------------------------------------------------------------
 ** Constructor scheme with error execution.
 ** ----------------------------------------------------------------- */

static void
test_csee_constructor_handler (cce_condition_t const * C CCLIB_UNUSED, cce_error_handler_t const * const H)
{
  void **	PP = cce_handler_resource_pointer(H);
  void *	P  = *PP;
  free(P);
}

static void *
test_csee_constructor (cce_location_t * upper_L)
{
  cce_location_t	L[1];
  void *		P = NULL;
  cce_error_handler_t	H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(upper_L, L);
  } else {
    P = malloc(4096);
    if (P) {
      cce_init_and_register_handler(L, H, test_csee_constructor_handler, cce_resource_pointer(&P));
    } else {
      cce_raise(L, NULL);
    }
    // do_something_with(P);
    if (0) {
      cce_raise(L, NULL);
    }
    cce_run_body_handlers(L);
  }
  return P;
}

/* ------------------------------------------------------------------ */

typedef struct test_csee_t {
  cce_clean_handler_t	handler;
  bool volatile *	flagp;
} test_csee_t;

static void
test_csee_caller_handler (cce_condition_t const * C CCLIB_UNUSED, cce_clean_handler_t const * const H)
{
  void **	PP = cce_handler_resource_pointer(H);
  void *	P  = *PP;
  free(P);
  {
    CCLIB_PC(test_csee_t, W, H);
    *(W->flagp) = true;
  }
}

static void
test_constructor_scheme_exceptional_execution (void)
/* Constructor scheme: exceptional path. */
{
  cce_location_t	L[1];
  bool volatile		flag = false;
  test_csee_t		H = { .flagp = &flag };

  if (cce_location(L)) {
    cce_run_catch_handlers_final(L);
  } else {
    void *	P = test_csee_constructor(L);
    assert(NULL != P);
    cce_init_and_register_handler(L, &H.handler, test_csee_caller_handler, P);
    // do_something_with(P);
    cce_run_body_handlers(L);
  }
  assert(true == flag);
}


/** --------------------------------------------------------------------
 ** Handler removal.
 ** ----------------------------------------------------------------- */

static void
handler_removal_function (cce_condition_t const * C CCLIB_UNUSED, cce_clean_handler_t const * const H)
{
  bool	* flag = cce_handler_resource_pointer(H);
  *flag = true;
}

void
test_handler_removal_1_0 (void)
/* No handler removal in this function: it just tests the code logic. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	H1[1], H2[1], H3[1];
  bool volatile		flag1 = false, flag2 = false, flag3 = false;

  if (cce_location(L)) {
    cce_run_catch_handlers_final(L);
  } else {
    cce_init_handler(H1, handler_removal_function, cce_resource_pointer(&flag1));
    cce_init_handler(H2, handler_removal_function, cce_resource_pointer(&flag2));
    cce_init_handler(H3, handler_removal_function, cce_resource_pointer(&flag3));
    cce_register_handler(L, H1);
    cce_register_handler(L, H2);
    cce_register_handler(L, H3);
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
  cce_clean_handler_t	H1[1], H2[1], H3[1];
  bool volatile		flag1 = false, flag2 = false, flag3 = false;

  if (cce_location(L)) {
    cce_run_catch_handlers_final(L);
  } else {
    cce_init_handler(H1, handler_removal_function, cce_resource_pointer(&flag1));
    cce_init_handler(H2, handler_removal_function, cce_resource_pointer(&flag2));
    cce_init_handler(H3, handler_removal_function, cce_resource_pointer(&flag3));
    cce_register_handler(L, H1);
    cce_register_handler(L, H2);
    cce_register_handler(L, H3);
    cce_forget_handler(L, H1);
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
  cce_clean_handler_t	H1[1], H2[1], H3[1];
  bool volatile		flag1 = false, flag2 = false, flag3 = false;

  if (cce_location(L)) {
    cce_run_catch_handlers_final(L);
  } else {
    cce_init_handler(H1, handler_removal_function, cce_resource_pointer(&flag1));
    cce_init_handler(H2, handler_removal_function, cce_resource_pointer(&flag2));
    cce_init_handler(H3, handler_removal_function, cce_resource_pointer(&flag3));
    cce_register_handler(L, H1);
    cce_register_handler(L, H2);
    cce_register_handler(L, H3);
    cce_forget_handler(L, H2);
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
  cce_clean_handler_t	H1[1], H2[1], H3[1];
  bool volatile		flag1 = false, flag2 = false, flag3 = false;

  if (cce_location(L)) {
    cce_run_catch_handlers_final(L);
  } else {
    cce_init_handler(H1, handler_removal_function, cce_resource_pointer(&flag1));
    cce_init_handler(H2, handler_removal_function, cce_resource_pointer(&flag2));
    cce_init_handler(H3, handler_removal_function, cce_resource_pointer(&flag3));
    cce_register_handler(L, H1);
    cce_register_handler(L, H2);
    cce_register_handler(L, H3);
    cce_forget_handler(L, H3);
    cce_run_body_handlers(L);
  }

  assert(true  == flag1);
  assert(true  == flag2);
  assert(false == flag3);
}


/** --------------------------------------------------------------------
 ** Let's go.
 ** ----------------------------------------------------------------- */

int
main (void)
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
