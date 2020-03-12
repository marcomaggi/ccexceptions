/*
  Part of: CCExceptions
  Contents: tests for running handlers from handlers
  Date: May 22, 2018

  Abstract



  Copyright (C) 2018, 2019 Marco Maggi <mrc.mgg@gmail.com>

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
#include <stdbool.h>
#include <assert.h>


/** --------------------------------------------------------------------
 ** Flag handlers.
 ** ----------------------------------------------------------------- */

static void
flag_clean_handler (cce_condition_t const * C CCE_UNUSED, cce_clean_handler_t const * const H)
{
  bool volatile	*flagp = cce_handler_resource_pointer(H);
  *flagp = true;
}

static void
flag_error_handler (cce_condition_t const * C CCE_UNUSED, cce_error_handler_t const * const H)
{
  bool volatile	*flagp = cce_handler_resource_pointer(H);
  *flagp = true;
}

/* ------------------------------------------------------------------ */

void
register_clean_flag_handler (cce_destination_t L, cce_clean_handler_t * H, bool volatile * flagp)
{
  cce_init_and_register_handler(L, H, flag_clean_handler, cce_resource_pointer(flagp));
}

void
register_error_flag_handler (cce_destination_t L, cce_error_handler_t * H, bool volatile * flagp)
{
  cce_init_and_register_handler(L, H, flag_error_handler, cce_resource_pointer(flagp));
}


/** --------------------------------------------------------------------
 ** Running outer clean handlers from an inner clean handler.
 ** ----------------------------------------------------------------- */

void
test_run_body_handlers_from_clean_handler__no_exception (void)
{
  cce_location_t	outer_L[1];
  cce_clean_handler_t	outer_clean_H[1];
  cce_error_handler_t	outer_error_H[1];
  bool volatile		outer_clean_flag = false;
  bool volatile		outer_error_flag = false;
  cce_clean_handler_t	inner_clean_H[1];
  cce_error_handler_t	inner_error_H[1];
  bool volatile		inner_clean_flag = false;
  bool volatile		inner_error_flag = false;

  if (cce_location(outer_L)) {
    cce_location_t	inner_L[1];
    cce_clean_handler_t	inner_H[1];

    if (cce_location(inner_L)) {
      cce_run_catch_handlers_final(inner_L);
      assert(false);
    } else {
      cce_register_clean_handler_to_run_body_handlers(inner_L, inner_H, outer_L);
      register_clean_flag_handler(inner_L, inner_clean_H, &inner_clean_flag);
      register_error_flag_handler(inner_L, inner_error_H, &inner_error_flag);
      cce_run_body_handlers(inner_L);
    }
  } else {
    register_clean_flag_handler(outer_L, outer_clean_H, &outer_clean_flag);
    register_error_flag_handler(outer_L, outer_error_H, &outer_error_flag);
    cce_raise(outer_L, NULL);
    assert(false);
  }
  /* We raised  no exception from  the inner  body, so: the  inner clean
     handlers  are run;  the  inner error  handlers  are skipped.   This
     means: the outer  clean handlers are run; the  outer error handlers
     are skipped. */
  assert(true  == inner_clean_flag);
  assert(false == inner_error_flag);
  assert(true  == outer_clean_flag);
  assert(false == outer_error_flag);
}

void
test_run_body_handlers_from_clean_handler__exception_raised (void)
{
  cce_location_t	outer_L[1];
  cce_clean_handler_t	outer_clean_H[1];
  cce_error_handler_t	outer_error_H[1];
  bool volatile		outer_clean_flag = false;
  bool volatile		outer_error_flag = false;
  cce_clean_handler_t	inner_clean_H[1];
  cce_error_handler_t	inner_error_H[1];
  bool volatile		inner_clean_flag = false;
  bool volatile		inner_error_flag = false;

  if (cce_location(outer_L)) {
    cce_location_t	inner_L[1];
    cce_clean_handler_t	inner_H[1];

    if (cce_location(inner_L)) {
      cce_run_catch_handlers_final(inner_L);
    } else {
      cce_register_clean_handler_to_run_body_handlers(inner_L, inner_H, outer_L);
      register_clean_flag_handler(inner_L, inner_clean_H, &inner_clean_flag);
      register_error_flag_handler(inner_L, inner_error_H, &inner_error_flag);
      cce_raise(inner_L, NULL);
      assert(false);
    }
  } else {
    register_clean_flag_handler(outer_L, outer_clean_H, &outer_clean_flag);
    register_error_flag_handler(outer_L, outer_error_H, &outer_error_flag);
    cce_raise(outer_L, NULL);
    assert(false);
  }

  /* We raised  an exception  from the  inner body,  so: both  the inner
     clean handlers and  the inner error handlers are  run.  This means:
     the  outer clean  handlers are  run; the  outer error  handlers are
     skipped. */
  assert(true  == inner_clean_flag);
  assert(true  == inner_error_flag);
  assert(true  == outer_clean_flag);
  assert(false == outer_error_flag);
}


/** --------------------------------------------------------------------
 ** Running outer error handlers from an inner clean handler.
 ** ----------------------------------------------------------------- */

void
test_run_catch_handlers_from_clean_handler__no_exception (void)
{
  cce_location_t	outer_L[1];
  cce_clean_handler_t	outer_clean_H[1];
  cce_error_handler_t	outer_error_H[1];
  bool volatile		outer_clean_flag = false;
  bool volatile		outer_error_flag = false;
  cce_clean_handler_t	inner_clean_H[1];
  cce_error_handler_t	inner_error_H[1];
  bool volatile		inner_clean_flag = false;
  bool volatile		inner_error_flag = false;

  if (cce_location(outer_L)) {
    cce_location_t	inner_L[1];
    cce_clean_handler_t	inner_H[1];

    if (cce_location(inner_L)) {
      cce_run_catch_handlers_final(inner_L);
      assert(false);
    } else {
      cce_register_clean_handler_to_run_catch_handlers(inner_L, inner_H, outer_L);
      register_clean_flag_handler(inner_L, inner_clean_H, &inner_clean_flag);
      register_error_flag_handler(inner_L, inner_error_H, &inner_error_flag);
      cce_run_body_handlers(inner_L);
    }
  } else {
    register_clean_flag_handler(outer_L, outer_clean_H, &outer_clean_flag);
    register_error_flag_handler(outer_L, outer_error_H, &outer_error_flag);
    cce_raise(outer_L, NULL);
    assert(false);
  }

  /* We raised  no exception from  the inner  body, so: the  inner clean
     handlers are run; the inner error handlers are skipped.  This means
     both the outer error handlers and outer clean handlers are run. */
  assert(true  == inner_clean_flag);
  assert(false == inner_error_flag);
  assert(true  == outer_clean_flag);
  assert(true  == outer_error_flag);
}

void
test_run_catch_handlers_from_clean_handler__exception_raised (void)
{
  cce_location_t	outer_L[1];
  cce_clean_handler_t	outer_clean_H[1];
  cce_error_handler_t	outer_error_H[1];
  bool volatile		outer_clean_flag = false;
  bool volatile		outer_error_flag = false;
  cce_clean_handler_t	inner_clean_H[1];
  cce_error_handler_t	inner_error_H[1];
  bool volatile		inner_clean_flag = false;
  bool volatile		inner_error_flag = false;

  if (cce_location(outer_L)) {
    cce_location_t	inner_L[1];
    cce_clean_handler_t	inner_H[1];

    if (cce_location(inner_L)) {
      cce_run_catch_handlers_final(inner_L);
    } else {
      cce_register_clean_handler_to_run_catch_handlers(inner_L, inner_H, outer_L);
      register_clean_flag_handler(inner_L, inner_clean_H, &inner_clean_flag);
      register_error_flag_handler(inner_L, inner_error_H, &inner_error_flag);
      cce_raise(inner_L, NULL);
      assert(false);
    }
  } else {
    register_clean_flag_handler(outer_L, outer_clean_H, &outer_clean_flag);
    register_error_flag_handler(outer_L, outer_error_H, &outer_error_flag);
    cce_raise(outer_L, NULL);
    assert(false);
  }

  /* We have raised an exception from the inner body, so: both the inner
     clean handlers  and the inner  error handlers are run.   This means
     both the outer error handlers and outer clean handlers are run. */
  assert(true  == inner_clean_flag);
  assert(true  == inner_error_flag);
  assert(true  == outer_clean_flag);
  assert(true  == outer_error_flag);
}


/** --------------------------------------------------------------------
 ** Running outer clean handlers from an inner error handler.
 ** ----------------------------------------------------------------- */

void
test_run_body_handlers_from_error_handler__no_exception (void)
{
  cce_location_t	outer_L[1];
  cce_clean_handler_t	outer_clean_H[1];
  cce_error_handler_t	outer_error_H[1];
  bool volatile		outer_clean_flag = false;
  bool volatile		outer_error_flag = false;
  cce_clean_handler_t	inner_clean_H[1];
  cce_error_handler_t	inner_error_H[1];
  bool volatile		inner_clean_flag = false;
  bool volatile		inner_error_flag = false;

  if (cce_location(outer_L)) {
    cce_location_t	inner_L[1];
    cce_error_handler_t	inner_H[1];

    if (cce_location(inner_L)) {
      cce_run_catch_handlers_final(inner_L);
      assert(false);
    } else {
      cce_register_error_handler_to_run_body_handlers(inner_L, inner_H, outer_L);
      register_clean_flag_handler(inner_L, inner_clean_H, &inner_clean_flag);
      register_error_flag_handler(inner_L, inner_error_H, &inner_error_flag);
      cce_run_body_handlers(inner_L);
    }
  } else {
    register_clean_flag_handler(outer_L, outer_clean_H, &outer_clean_flag);
    register_error_flag_handler(outer_L, outer_error_H, &outer_error_flag);
    cce_raise(outer_L, NULL);
    assert(false);
  }
  /* We raised  no exception from  the inner  body, so: the  inner clean
     handlers  are run;  the  inner error  handlers  are skipped.   This
     means: both the  outer clean handlers and the  outer error handlers
     are skipped. */
  assert(true  == inner_clean_flag);
  assert(false == inner_error_flag);
  assert(false == outer_clean_flag);
  assert(false == outer_error_flag);
}

void
test_run_body_handlers_from_error_handler__exception_raised (void)
{
  cce_location_t	outer_L[1];
  cce_clean_handler_t	outer_clean_H[1];
  cce_error_handler_t	outer_error_H[1];
  bool volatile		outer_clean_flag = false;
  bool volatile		outer_error_flag = false;
  cce_clean_handler_t	inner_clean_H[1];
  cce_error_handler_t	inner_error_H[1];
  bool volatile		inner_clean_flag = false;
  bool volatile		inner_error_flag = false;

  if (cce_location(outer_L)) {
    cce_location_t	inner_L[1];
    cce_error_handler_t	inner_H[1];

    if (cce_location(inner_L)) {
      cce_run_catch_handlers_final(inner_L);
    } else {
      cce_register_error_handler_to_run_body_handlers(inner_L, inner_H, outer_L);
      register_clean_flag_handler(inner_L, inner_clean_H, &inner_clean_flag);
      register_error_flag_handler(inner_L, inner_error_H, &inner_error_flag);
      cce_raise(inner_L, NULL);
      assert(false);
    }
  } else {
    register_clean_flag_handler(outer_L, outer_clean_H, &outer_clean_flag);
    register_error_flag_handler(outer_L, outer_error_H, &outer_error_flag);
    cce_raise(outer_L, NULL);
    assert(false);
  }

  /* We raised  an exception  from the  inner body,  so: both  the inner
     clean handlers and  the inner error handlers are  run.  This means:
     the  outer clean  handlers are  run; the  outer error  handlers are
     skipped. */
  assert(true  == inner_clean_flag);
  assert(true  == inner_error_flag);
  assert(true  == outer_clean_flag);
  assert(false == outer_error_flag);
}


/** --------------------------------------------------------------------
 ** Running outer error handlers from an inner error handler.
 ** ----------------------------------------------------------------- */

void
test_run_catch_handlers_from_error_handler__no_exception (void)
{
  cce_location_t	outer_L[1];
  cce_clean_handler_t	outer_clean_H[1];
  cce_error_handler_t	outer_error_H[1];
  bool volatile		outer_clean_flag = false;
  bool volatile		outer_error_flag = false;
  cce_clean_handler_t	inner_clean_H[1];
  cce_error_handler_t	inner_error_H[1];
  bool volatile		inner_clean_flag = false;
  bool volatile		inner_error_flag = false;

  if (cce_location(outer_L)) {
    cce_location_t	inner_L[1];
    cce_error_handler_t	inner_H[1];

    if (cce_location(inner_L)) {
      cce_run_catch_handlers_final(inner_L);
      assert(false);
    } else {
      cce_register_error_handler_to_run_catch_handlers(inner_L, inner_H, outer_L);
      register_clean_flag_handler(inner_L, inner_clean_H, &inner_clean_flag);
      register_error_flag_handler(inner_L, inner_error_H, &inner_error_flag);
      cce_run_body_handlers(inner_L);
    }
  } else {
    register_clean_flag_handler(outer_L, outer_clean_H, &outer_clean_flag);
    register_error_flag_handler(outer_L, outer_error_H, &outer_error_flag);
    cce_raise(outer_L, NULL);
    assert(false);
  }

  /* We raised  no exception from  the inner  body, so: the  inner clean
     handlers  are run;  the  inner error  handlers  are skipped.   This
     means: both the  outer clean handlers and the  outer error handlers
     are skipped. */
  assert(true  == inner_clean_flag);
  assert(false == inner_error_flag);
  assert(false == outer_clean_flag);
  assert(false == outer_error_flag);
}

void
test_run_catch_handlers_from_error_handler__exception_raised (void)
{
  cce_location_t	outer_L[1];
  cce_clean_handler_t	outer_clean_H[1];
  cce_error_handler_t	outer_error_H[1];
  bool volatile		outer_clean_flag = false;
  bool volatile		outer_error_flag = false;
  cce_clean_handler_t	inner_clean_H[1];
  cce_error_handler_t	inner_error_H[1];
  bool volatile		inner_clean_flag = false;
  bool volatile		inner_error_flag = false;

  if (cce_location(outer_L)) {
    cce_location_t	inner_L[1];
    cce_error_handler_t	inner_H[1];

    if (cce_location(inner_L)) {
      cce_run_catch_handlers_final(inner_L);
    } else {
      cce_register_error_handler_to_run_catch_handlers(inner_L, inner_H, outer_L);
      register_clean_flag_handler(inner_L, inner_clean_H, &inner_clean_flag);
      register_error_flag_handler(inner_L, inner_error_H, &inner_error_flag);
      cce_raise(inner_L, NULL);
      assert(false);
    }
  } else {
    register_clean_flag_handler(outer_L, outer_clean_H, &outer_clean_flag);
    register_error_flag_handler(outer_L, outer_error_H, &outer_error_flag);
    cce_raise(outer_L, NULL);
    assert(false);
  }

  /* We raised  an exception  from the  inner body,  so: both  the inner
     clean handlers and  the inner error handlers are  run.  This means:
     both  the outer  clean handlers  and the  outer error  handlers are
     run. */
  assert(true  == inner_clean_flag);
  assert(true  == inner_error_flag);
  assert(true  == outer_clean_flag);
  assert(true  == outer_error_flag);
}


int
main (void)
{
  if (1) { test_run_body_handlers_from_clean_handler__no_exception();     }
  if (1) { test_run_body_handlers_from_clean_handler__exception_raised(); }

  if (1) { test_run_catch_handlers_from_clean_handler__no_exception(); }
  if (1) { test_run_catch_handlers_from_clean_handler__exception_raised(); }

  if (1) { test_run_body_handlers_from_error_handler__no_exception();     }
  if (1) { test_run_body_handlers_from_error_handler__exception_raised(); }

  if (1) { test_run_catch_handlers_from_error_handler__no_exception();     }
  if (1) { test_run_catch_handlers_from_error_handler__exception_raised(); }

  exit(EXIT_SUCCESS);
}

/* end of file */
