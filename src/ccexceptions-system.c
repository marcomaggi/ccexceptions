/*
  Part of: CCExceptions
  Contents: some system functions adapters
  Date: Mon Jun 26, 2017

  Abstract



  Copyright (C) 2017, 2018, 2019 Marco Maggi <marco.maggi-ipsu@poste.it>

  This is free software; you  can redistribute it and/or modify it under
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

#include "ccexceptions-internals.h"
#include <stdio.h>
#include <errno.h>


/** --------------------------------------------------------------------
 ** System wrappers: memory allocation.
 ** ----------------------------------------------------------------- */

void *
cce_sys_malloc (cce_location_t * L, size_t size)
{
  void *	rv;
  errno = 0;
  rv = malloc (size);
  if (NULL != rv) {
    return rv;
  } else {
    cce_raise(L, cce_condition_new_errno_clear());
  }
}

void *
cce_sys_realloc (cce_location_t * L, void * ptr, size_t newsize)
{
  void *	rv;
  errno = 0;
  rv = realloc(ptr, newsize);
  if (NULL != rv) {
    return rv;
  } else {
    cce_raise(L, cce_condition_new_errno_clear());
  }
}

void *
cce_sys_calloc (cce_location_t * L, size_t count, size_t eltsize)
{
  void *	rv;
  errno = 0;
  rv = calloc(count, eltsize);
  if (NULL != rv) {
    return rv;
  } else {
    cce_raise(L, cce_condition_new_errno_clear());
  }
}


/** --------------------------------------------------------------------
 ** Predefined POSIX exception handler: malloc pointer.
 ** ----------------------------------------------------------------- */

__attribute__((__nonnull__(1,2)))
static void
cce_handler_malloc_function (cce_condition_t const * C CCE_UNUSED, cce_handler_t * H)
{
  free(H->pointer);
  if (0) { fprintf(stderr, "%s: done\n", __func__); }
}

void
cce_init_clean_handler_malloc (cce_location_t * L, cce_clean_handler_t * H, void * pointer)
{
  cce_clean_handler_set(H, pointer, cce_handler_malloc_function);
  cce_register_clean_handler(L, H);
}

void
cce_init_error_handler_malloc (cce_location_t * L, cce_error_handler_t * H, void * pointer)
{
  cce_error_handler_set(H, pointer, cce_handler_malloc_function);
  cce_register_error_handler(L, H);
}


/** --------------------------------------------------------------------
 ** System wrappers: guarded memory allocation.
 ** ----------------------------------------------------------------- */

void *
cce_sys_malloc_guarded_clean (cce_location_t * L, cce_clean_handler_t * P_H, size_t size)
{
  void *	P = cce_sys_malloc(L, size);
  cce_init_clean_handler_malloc(L, P_H, P);
  return P;
}

void *
cce_sys_malloc_guarded_error (cce_location_t * L, cce_error_handler_t * P_H, size_t size)
{
  void *	P = cce_sys_malloc(L, size);
  cce_init_error_handler_malloc(L, P_H, P);
  return P;
}

/* ------------------------------------------------------------------ */

void *
cce_sys_realloc_guarded_clean (cce_location_t * L, cce_clean_handler_t * P_H, void * old_P, size_t newsize)
{
  if (P_H->handler.pointer == old_P) {
    void *	P = cce_sys_realloc(L, old_P, newsize);
    P_H->handler.pointer = P;
    return P;
  } else {
    cce_raise(L, cce_condition_new_invalid_argument(L, __func__, 2));
  }
}

void *
cce_sys_realloc_guarded_error (cce_location_t * L, cce_error_handler_t * P_H, void * old_P, size_t newsize)
{
  if (P_H->handler.pointer == old_P) {
    void *	P = cce_sys_realloc(L, old_P, newsize);
    P_H->handler.pointer = P;
    return P;
  } else {
    cce_raise(L, cce_condition_new_invalid_argument(L, __func__, 2));
  }
}

/* ------------------------------------------------------------------ */

void *
cce_sys_calloc_guarded_clean (cce_location_t * L, cce_clean_handler_t * P_H, size_t count, size_t eltsize)
{
  void *	P = cce_sys_calloc(L, count, eltsize);
  cce_init_clean_handler_malloc(L, P_H, P);
  return P;
}

void *
cce_sys_calloc_guarded_error (cce_location_t * L, cce_error_handler_t * P_H, size_t count, size_t eltsize)
{
  void *	P = cce_sys_calloc(L, count, eltsize);
  cce_init_error_handler_malloc(L, P_H, P);
  return P;
}

/* end of file */
