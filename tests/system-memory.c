/*
  Part of: CCExceptions
  Contents: tests for POSIX system functions, memory allocation
  Date: Fri Dec 15, 2017

  Abstract



  Copyright (C) 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

  See the COPYING file.
*/


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "ccexceptions.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


/** --------------------------------------------------------------------
 ** Guarded memory allocation.
 ** ----------------------------------------------------------------- */

void
test_1_1 (void)
/* Allocate and release  memory using "malloc()" and  a cleanup handler,
   successful execution path. */
{
  cce_location_t	L[1];
  cce_cleanup_handler_t	P_H[1];

  if (cce_location(L)) {
    fprintf(stderr, "%s: exception: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_error_handlers_final(L);
    exit(EXIT_FAILURE);
  } else {
    void *	P = cce_sys_malloc_guarded(L, P_H, 1024);
    assert(NULL != P);
    cce_run_cleanup_handlers(L);
    fprintf(stderr, "%s: all right, successful execution path\n", __func__);
  }
}

void
test_1_2 (void)
/* Allocate and release  memory using "malloc()" and  a cleanup handler,
   exception execution path. */
{
  cce_location_t	L[1];
  cce_cleanup_handler_t	P_H[1];

  if (cce_location(L)) {
    fprintf(stderr, "%s: all right: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_error_handlers_final(L);
  } else {
    void *	P = cce_sys_malloc_guarded(L, P_H, 1024);
    assert(NULL != P);
    cce_raise(L, cce_condition_new_error());
    cce_run_cleanup_handlers(L);
    fprintf(stderr, "%s: wrong execution path\n", __func__);
    exit(EXIT_FAILURE);
  }
}

/* ------------------------------------------------------------------ */

void
test_2_1 (void)
/* Allocate and release  memory using "malloc()" and  a error handler,
   successful execution path. */
{
  cce_location_t	L[1];
  cce_error_handler_t	P_H[1];

  if (cce_location(L)) {
    fprintf(stderr, "%s: exception: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_error_handlers_final(L);
    exit(EXIT_FAILURE);
  } else {
    void *	P = cce_sys_malloc_guarded(L, P_H, 1024);
    assert(NULL != P);
    cce_run_error_handlers(L);
    fprintf(stderr, "%s: all right, successful execution path\n", __func__);
  }
}

void
test_2_2 (void)
/* Allocate and  release memory  using "malloc()"  and a  error handler,
   exception execution path. */
{
  cce_location_t	L[1];
  cce_error_handler_t	P_H[1];

  if (cce_location(L)) {
    fprintf(stderr, "%s: all right: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_error_handlers_final(L);
  } else {
    void *	P = cce_sys_malloc_guarded(L, P_H, 1024);
    assert(NULL != P);
    cce_raise(L, cce_condition_new_error());
    cce_run_error_handlers(L);
    fprintf(stderr, "%s: wrong execution path\n", __func__);
    exit(EXIT_FAILURE);
  }
}


int
main (void)
{
  /* Guarded memory allocation. */
  if (1) { test_1_1(); }
  if (1) { test_1_2(); }
  if (1) { test_2_1(); }
  if (1) { test_2_2(); }

  exit(EXIT_SUCCESS);
}

/* end of file */
