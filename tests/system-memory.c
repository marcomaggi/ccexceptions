/*
  Part of: CCExceptions
  Contents: tests for POSIX system functions, memory allocation
  Date: Fri Dec 15, 2017

  Abstract



  Copyright (C) 2017, 2018, 2019 Marco Maggi <mrc.mgg@gmail.com>

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
 ** Guarded memory allocation: malloc.
 ** ----------------------------------------------------------------- */

void
test_1_1 (void)
/* Allocate and release  memory using "malloc()" and  a clean handler,
   successful execution path. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    fprintf(stderr, "%s: exception: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_catch_handlers_final(L);
    exit(EXIT_FAILURE);
  } else {
    void *	P = cce_sys_malloc_guarded(L, P_H, 1024);
    assert(NULL != P);
    cce_run_body_handlers(L);
    fprintf(stderr, "%s: all right, successful execution path\n", __func__);
  }
}

void
test_1_2 (void)
/* Allocate and release  memory using "malloc()" and  a clean handler,
   exception execution path. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    fprintf(stderr, "%s: all right: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_catch_handlers_final(L);
  } else {
    void *	P = cce_sys_malloc_guarded(L, P_H, 1024);
    assert(NULL != P);
    cce_raise(L, cce_condition_new_error());
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
    cce_run_catch_handlers_final(L);
    exit(EXIT_FAILURE);
  } else {
    void *	P = cce_sys_malloc_guarded(L, P_H, 1024);
    assert(NULL != P);
    cce_run_catch_handlers(L);
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
    cce_run_catch_handlers_final(L);
  } else {
    void *	P = cce_sys_malloc_guarded(L, P_H, 1024);
    assert(NULL != P);
    cce_raise(L, cce_condition_new_error());
  }
}


/** --------------------------------------------------------------------
 ** Guarded memory allocation: calloc.
 ** ----------------------------------------------------------------- */

void
test_3_1 (void)
/* Allocate and release  memory using "calloc()" and  a clean handler,
   successful execution path. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    fprintf(stderr, "%s: exception: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_catch_handlers_final(L);
    exit(EXIT_FAILURE);
  } else {
    void *	P = cce_sys_calloc_guarded(L, P_H, 4, 1024);
    assert(NULL != P);
    cce_run_body_handlers(L);
    fprintf(stderr, "%s: all right, successful execution path\n", __func__);
  }
}

void
test_3_2 (void)
/* Allocate and release  memory using "calloc()" and  a clean handler,
   exception execution path. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    fprintf(stderr, "%s: all right: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_catch_handlers_final(L);
  } else {
    void *	P = cce_sys_calloc_guarded(L, P_H, 4, 1024);
    assert(NULL != P);
    cce_raise(L, cce_condition_new_error());
  }
}

/* ------------------------------------------------------------------ */

void
test_4_1 (void)
/* Allocate and release  memory using "calloc()" and  a error handler,
   successful execution path. */
{
  cce_location_t	L[1];
  cce_error_handler_t	P_H[1];

  if (cce_location(L)) {
    fprintf(stderr, "%s: exception: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_catch_handlers_final(L);
    exit(EXIT_FAILURE);
  } else {
    void *	P = cce_sys_calloc_guarded(L, P_H, 4, 1024);
    assert(NULL != P);
    cce_run_catch_handlers(L);
    fprintf(stderr, "%s: all right, successful execution path\n", __func__);
  }
}

void
test_4_2 (void)
/* Allocate and  release memory  using "calloc()"  and a  error handler,
   exception execution path. */
{
  cce_location_t	L[1];
  cce_error_handler_t	P_H[1];

  if (cce_location(L)) {
    fprintf(stderr, "%s: all right: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_catch_handlers_final(L);
  } else {
    void *	P = cce_sys_calloc_guarded(L, P_H, 4, 1024);
    assert(NULL != P);
    cce_raise(L, cce_condition_new_error());
  }
}


/** --------------------------------------------------------------------
 ** Guarded memory allocation: realloc.
 ** ----------------------------------------------------------------- */

void
test_5_1 (void)
/* Allocate and release memory using  "realloc()" and a clean handler,
   successful execution path. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    fprintf(stderr, "%s: exception: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_catch_handlers_final(L);
    exit(EXIT_FAILURE);
  } else {
    void *	P = cce_sys_malloc_guarded(L, P_H, 1024);
    assert(NULL != P);
    if (0) { fprintf(stderr, "%s: reallocating...\n", __func__); }
    P = cce_sys_realloc_guarded(L, P_H, P, 4096);
    assert(NULL != P);
    cce_run_body_handlers(L);
    fprintf(stderr, "%s: all right, successful execution path\n", __func__);
  }
}

void
test_5_2 (void)
/* Allocate and release memory using  "realloc()" and a clean handler,
   exception execution path. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    fprintf(stderr, "%s: all right: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_catch_handlers_final(L);
  } else {
    void *	P = cce_sys_malloc_guarded(L, P_H, 1024);
    assert(NULL != P);
    P = cce_sys_realloc_guarded(L, P_H, P, 4096);
    assert(NULL != P);
    cce_raise(L, cce_condition_new_error());
  }
}

/* ------------------------------------------------------------------ */

void
test_6_1 (void)
/* Allocate and release  memory using "realloc()" and  an error handler,
   successful execution path. */
{
  cce_location_t	L[1];
  cce_error_handler_t	P_H[1];

  if (cce_location(L)) {
    fprintf(stderr, "%s: exception: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_catch_handlers_final(L);
    exit(EXIT_FAILURE);
  } else {
    void *	P = cce_sys_malloc_guarded(L, P_H, 1024);
    assert(NULL != P);
    P = cce_sys_realloc_guarded(L, P_H, P, 4096);
    assert(NULL != P);
    cce_run_catch_handlers(L);
    fprintf(stderr, "%s: all right, successful execution path\n", __func__);
  }
}

void
test_6_2 (void)
/* Allocate and release  memory using "realloc()" and  an error handler,
   exception execution path. */
{
  cce_location_t	L[1];
  cce_error_handler_t	P_H[1];

  if (cce_location(L)) {
    fprintf(stderr, "%s: all right: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_catch_handlers_final(L);
  } else {
    void *	P = cce_sys_malloc_guarded(L, P_H, 1024);
    assert(NULL != P);
    P = cce_sys_realloc_guarded(L, P_H, P, 4096);
    assert(NULL != P);
    cce_raise(L, cce_condition_new_error());
  }
}

/* ------------------------------------------------------------------ */

void
test_7_1 (void)
/* Calling the guarded "realloc()" with the wrong handler argument. */
{
  cce_location_t	L[1];
  cce_error_handler_t	P_H[1];
  cce_error_handler_t	Q_H[1];

  if (cce_location(L)) {
    fprintf(stderr, "%s: all right, got exception: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    if (! cce_condition_is_invalid_argument(cce_condition(L))) {
      exit(EXIT_FAILURE);
    }
    cce_run_catch_handlers_final(L);
  } else {
    void *	P = cce_sys_malloc_guarded(L, P_H, 1024);
    assert(NULL != P);
    void *	Q = cce_sys_malloc_guarded(L, Q_H, 1024);
    assert(NULL != Q);
    P = cce_sys_realloc_guarded(L, Q_H, P, 4096);
    fprintf(stderr, "%s: unexpected execution path\n", __func__);
    exit(EXIT_FAILURE);
  }
}


int
main (void)
{
  /* Guarded memory allocation: malloc. */
  if (1) { test_1_1(); }
  if (1) { test_1_2(); }
  if (1) { test_2_1(); }
  if (1) { test_2_2(); }

  /* Guarded memory allocation: calloc. */
  if (1) { test_3_1(); }
  if (1) { test_3_2(); }
  if (1) { test_4_1(); }
  if (1) { test_4_2(); }

  /* Guarded memory allocation: realloc. */
  if (1) { test_5_1(); }
  if (1) { test_5_2(); }
  if (1) { test_6_1(); }
  if (1) { test_6_2(); }
  if (1) { test_7_1(); }

  exit(EXIT_SUCCESS);
}

/* end of file */
