/*
  Part of: CCExceptions
  Contents: tests destructors API
  Date: Mar 20, 2019

  Abstract



  Copyright (C) 2019 Marco Maggi <mrc.mgg@gmail.com>

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
 ** Destructors: dynamic memory.
 ** ----------------------------------------------------------------- */

static volatile bool	dynamic_memory_destroyed = false;
static volatile bool	dynamic_memory_handled = false;

static void
dynamic_memory_destructor (void * pointer)
{
  dynamic_memory_destroyed = true;
  free(pointer);
  if (1) { fprintf(stderr, "%s: done\n", __func__); }
}

static void
dynamic_memory_clean_handler (cce_condition_t const * const C CCE_UNUSED, cce_clean_handler_t const * H)
{
  cce_resource_destructor_fun_t *	destructor = cce_handler_resource_destructor(H);

  dynamic_memory_handled = true;
  destructor(cce_handler_resource_pointer(H));
  if (1) { fprintf(stderr, "%s: done\n", __func__); }
}

static void
dynamic_memory_error_handler (cce_condition_t const * const C CCE_UNUSED, cce_error_handler_t const * H)
{
  cce_resource_destructor_fun_t *	destructor = cce_handler_resource_destructor(H);

  dynamic_memory_handled = true;
  destructor(cce_handler_resource_pointer(H));
  if (1) { fprintf(stderr, "%s: done\n", __func__); }
}

/* ------------------------------------------------------------------ */

void
test_dynamic_memory_clean_handler (void)
{
  cce_location_t	L[1];
  cce_clean_handler_t	P_H[1];

  if (1) { fprintf(stderr, "%s: enter\n", __func__); }
  dynamic_memory_destroyed = false;
  dynamic_memory_handled   = false;

  if (cce_location(L)) {
    cce_run_catch_handlers_final(L);
  } else {
    void	*P = cce_sys_malloc(L, 256);
    cce_init_handler(P_H, dynamic_memory_clean_handler, P, dynamic_memory_destructor);
    cce_register_handler(L, P_H);

    cce_run_body_handlers(L);
  }
  assert(true == dynamic_memory_destroyed);
  assert(true == dynamic_memory_handled);
}

void
test_dynamic_memory_error_handler (void)
{
  cce_location_t	L[1];
  cce_error_handler_t	P_H[1];

  dynamic_memory_destroyed = false;
  dynamic_memory_handled   = false;

  if (1) { fprintf(stderr, "%s: enter\n", __func__); }
  if (cce_location(L)) {
    cce_run_catch_handlers_final(L);
  } else {
    void	*P = cce_sys_malloc(L, 256);
    cce_init_handler(P_H, dynamic_memory_error_handler, P, dynamic_memory_destructor);
    cce_register_handler(L, P_H);

    cce_raise(L, NULL);
    cce_run_body_handlers(L);
  }
  assert(true == dynamic_memory_destroyed);
  assert(true == dynamic_memory_handled);
}

/* ------------------------------------------------------------------ */

void
test_dynamic_memory_clean_handler_default_destructor (void)
{
  cce_location_t	L[1];
  cce_clean_handler_t	P_H[1];

  if (1) { fprintf(stderr, "%s: enter\n", __func__); }
  dynamic_memory_destroyed = false;

  if (cce_location(L)) {
    cce_run_catch_handlers_final(L);
  } else {
    void	*P = cce_sys_malloc(L, 256);
    cce_init_handler(P_H, dynamic_memory_clean_handler, P, dynamic_memory_destructor);
    cce_register_handler(L, P_H);

    cce_run_body_handlers(L);
  }
  assert(true == dynamic_memory_destroyed);
}

void
test_dynamic_memory_error_handler_default_destructor (void)
{
  cce_location_t	L[1];
  cce_error_handler_t	P_H[1];

  if (1) { fprintf(stderr, "%s: enter\n", __func__); }
  dynamic_memory_destroyed = false;

  if (cce_location(L)) {
    cce_run_catch_handlers_final(L);
  } else {
    void	*P = cce_sys_malloc(L, 256);
    cce_init_handler(P_H, dynamic_memory_error_handler, P, dynamic_memory_destructor);
    cce_register_handler(L, P_H);

    cce_raise(L, NULL);
    cce_run_body_handlers(L);
  }
  assert(true == dynamic_memory_destroyed);
}

/* ------------------------------------------------------------------ */

void
test_dynamic_memory_init_and_register_clean_handler_default_destructor (void)
{
  cce_location_t	L[1];
  cce_clean_handler_t	P_H[1];

  if (1) { fprintf(stderr, "%s: enter\n", __func__); }

  if (cce_location(L)) {
    cce_run_catch_handlers_final(L);
  } else {
    void	*P = cce_sys_malloc(L, 256);
    cce_init_and_register_handler(L, P_H, cce_default_clean_handler_function, P, free);
    cce_run_body_handlers(L);
  }
}

void
test_dynamic_memory_init_and_register_error_handler_default_destructor (void)
{
  cce_location_t	L[1];
  cce_error_handler_t	P_H[1];

  if (1) { fprintf(stderr, "%s: enter\n", __func__); }

  if (cce_location(L)) {
    cce_run_catch_handlers_final(L);
  } else {
    void	*P = cce_sys_malloc(L, 256);
    cce_init_and_register_handler(L, P_H, cce_default_error_handler_function, P, free);
    cce_raise(L, NULL);
    cce_run_body_handlers(L);
  }
}


int
main (void)
{
  if (1) { test_dynamic_memory_clean_handler(); }
  if (1) { test_dynamic_memory_error_handler(); }
  if (1) { test_dynamic_memory_clean_handler_default_destructor(); }
  if (1) { test_dynamic_memory_error_handler_default_destructor(); }
  if (1) { test_dynamic_memory_init_and_register_clean_handler_default_destructor(); }
  if (1) { test_dynamic_memory_init_and_register_error_handler_default_destructor(); }

  exit(EXIT_SUCCESS);
}

/* end of file */
