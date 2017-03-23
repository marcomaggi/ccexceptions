/*
  Part of: CCExceptions
  Contents: test with error and cleanup handlers
  Date: Fri Dec 23, 2016

  Abstract



  Copyright (C) 2016, 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

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

static void
test_no_exception (void)
{
  typedef struct handler1_t {
    cce_handler_t;
    bool * flagp;
  } handler1_t;
  void handler1 (const cce_condition_t * C CCE_UNUSED, cce_handler_t * _data)
  {
    handler1_t *	data = (handler1_t *)_data;
    *(data->flagp) = true;
  }

  typedef struct handler2_t {
    cce_handler_t;
    bool * flagp;
  } handler2_t;
  void handler2 (const cce_condition_t * C CCE_UNUSED, cce_handler_t * _data)
  {
    handler1_t *	data = (handler1_t *)_data;
    *(data->flagp) = true;
  }

  cce_location_t	L[1];
  bool		flag1 = false;
  bool		flag2 = false;
  handler1_t		H1 = { .handler_function = handler1, .flagp = &flag1 };
  handler2_t		H2 = { .handler_function = handler2, .flagp = &flag2 };

  switch (cce_location(L)) {
  case CCE_ERROR:
    cce_run_error_handlers(L);
    cce_condition_free(cce_condition(L));
    break;

  default:
    cce_register_cleanup_handler(L, &H1);
    cce_register_error_handler(L, &H2);
    cce_run_cleanup_handlers(L);
  }
  assert(true  == flag1);
  assert(false == flag2);
}

static void
test_with_error (void)
{
  typedef struct handler1_t {
    cce_handler_t;
    bool * flagp;
  } handler1_t;
  void handler1 (const cce_condition_t * C CCE_UNUSED, cce_handler_t * _data)
  {
    handler1_t *	data = (handler1_t *)_data;
    *(data->flagp) = true;
  }

  typedef struct handler2_t {
    cce_handler_t;
    bool * flagp;
  } handler2_t;
  void handler2 (const cce_condition_t * C CCE_UNUSED, cce_handler_t * _data)
  {
    handler1_t *	data = (handler1_t *)_data;
    *(data->flagp) = true;
  }

  cce_location_t	L[1];
  bool		flag1 = false;
  bool		flag2 = false;
  handler1_t		H1 = { .handler_function = handler1, .flagp = &flag1 };
  handler2_t		H2 = { .handler_function = handler2, .flagp = &flag2 };

  switch (cce_location(L)) {
  case CCE_ERROR:
    cce_run_error_handlers(L);
    cce_condition_free(cce_condition(L));
    break;

  default:
    cce_register_cleanup_handler(L, &H1);
    cce_register_error_handler(L, &H2);
    if (1) {
      cce_raise(L, NULL);
    }
    cce_run_cleanup_handlers(L);
  }
  assert(true == flag1);
  assert(true == flag2);
}

static void
test_with_retry (void)
{
  typedef struct handler1_t {
    cce_handler_t;
    bool * flagp;
  } handler1_t;
  void handler1 (const cce_condition_t * C CCE_UNUSED, cce_handler_t * _H)
  {
    handler1_t *	H = (handler1_t *)_H;
    *(H->flagp) = true;
  }

  typedef struct handler2_t {
    cce_handler_t;
    bool * flagp;
  } handler2_t;
  void handler2 (const cce_condition_t * C CCE_UNUSED, cce_handler_t * _H)
  {
    handler1_t *	H = (handler1_t *)_H;
    *(H->flagp) = true;
  }

  cce_location_t	L[1];
  bool		flag1 = false;
  bool		flag2 = false;
  handler1_t		H1 = { .handler_function = handler1, .flagp = &flag1 };
  handler2_t		H2 = { .handler_function = handler2, .flagp = &flag2 };

  switch (cce_location(L)) {
  case CCE_ERROR:
    cce_run_error_handlers(L);
    cce_condition_free(cce_condition(L));
    break;

  case CCE_SUCCESS:
    cce_register_cleanup_handler(L, &H1);
    cce_register_error_handler(L, &H2);
    if (1) {
      cce_retry(L);
    }
    // else fall through

  default:
    cce_run_cleanup_handlers(L);
  }
  assert(true  == flag1);
  assert(false == flag2);
}

static void
test_dynamically_allocated_handlers (void)
{
  typedef struct handler1_t {
    cce_handler_t;
    bool * flagp;
  } handler1_t;
  void handler1 (const cce_condition_t * C CCE_UNUSED, cce_handler_t * _H)
  {
    handler1_t *	H = (handler1_t *)_H;
    *(H->flagp) = true;
    free(H);
  }
  handler1_t * alloc_handler1 (cce_location_t * there, cce_handler_fun_t * handler, bool * flagp)
  {
    handler1_t *	H;
    errno = 0;
    H = malloc(sizeof(handler1_t));
    if (NULL != H) {
      H->handler_function = handler;
      H->flagp            = flagp;
      return H;
    } else {
      cce_raise(there, cce_errno_C(errno));
    }
  }

  typedef struct handler2_t {
    cce_handler_t;
    bool * flagp;
  } handler2_t;
  void handler2 (const cce_condition_t * C CCE_UNUSED, cce_handler_t * _H)
  {
    handler1_t *	H = (handler1_t *)_H;
    *(H->flagp) = true;
    free(H);
  }
  handler2_t * alloc_handler2 (cce_location_t * there, cce_handler_fun_t * handler, bool * flagp)
  {
    handler2_t *	H;
    errno = 0;
    H = malloc(sizeof(handler2_t));
    if (NULL != H) {
      H->handler_function = handler;
      H->flagp		= flagp;
      return H;
    } else {
      cce_raise(there, cce_errno_C(errno));
    }
  }

  cce_location_t	L[1];
  bool			flag1 = false;
  bool			flag2 = false;
  handler1_t *		H1;
  handler2_t *		H2;

  if (cce_location(L)) {
    cce_run_error_handlers(L);
    cce_condition_free(cce_condition(L));
  } else {
    H1 = alloc_handler1(L, handler1, &flag1);
    H2 = alloc_handler2(L, handler1, &flag2);
    cce_register_cleanup_handler(L, H1);
    cce_register_error_handler(L, H2);
    if (1) {
      cce_raise(L, NULL);
    }
    cce_run_cleanup_handlers(L);
  }
  assert(true == flag1);
  assert(true == flag2);
}

int
main (int argc CCE_UNUSED, const char *const argv[] CCE_UNUSED)
{
  if (1) test_no_exception();
  if (1) test_with_error();
  if (1) test_with_retry();
  if (1) test_dynamically_allocated_handlers();
  //
  exit(EXIT_SUCCESS);
}

/* end of file */
