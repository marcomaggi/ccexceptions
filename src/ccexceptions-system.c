/*
  Part of: CCExceptions
  Contents: some system functions adapters
  Date: Mon Jun 26, 2017

  Abstract



  Copyright (C) 2017, 2018, 2019 Marco Maggi <marco.maggi-ipsu@poste.it>

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

void
cce_init_and_register_clean_handler_malloc (cce_location_t * L, cce_clean_handler_t * const H, void * const pointer)
{
  cce_init_and_register_handler(L, H, cce_default_clean_handler_function, pointer, free);
}

void
cce_init_and_register_error_handler_malloc (cce_location_t * L, cce_error_handler_t * const H, void * const pointer)
{
  cce_init_and_register_handler(L, H, cce_default_error_handler_function, pointer, free);
}


/** --------------------------------------------------------------------
 ** System wrappers: guarded memory allocation.
 ** ----------------------------------------------------------------- */

void *
cce_sys_malloc_guarded_clean (cce_location_t * L, cce_clean_handler_t * P_H, size_t size)
{
  void *	P = cce_sys_malloc(L, size);
  cce_init_and_register_clean_handler_malloc(L, P_H, P);
  return P;
}

void *
cce_sys_malloc_guarded_error (cce_location_t * L, cce_error_handler_t * P_H, size_t size)
{
  void *	P = cce_sys_malloc(L, size);
  cce_init_and_register_error_handler_malloc(L, P_H, P);
  return P;
}

/* ------------------------------------------------------------------ */

void *
cce_sys_realloc_guarded_clean (cce_location_t * L, cce_clean_handler_t * P_H, void * old_P, size_t newsize)
{
  if (cce_handler_handler(P_H)->resource_pointer == old_P) {
    void *	P = cce_sys_realloc(L, old_P, newsize);
    P_H->handler.resource_pointer = P;
    return P;
  } else {
    cce_raise(L, cce_condition_new_invalid_argument(L, __func__, 2));
  }
}

void *
cce_sys_realloc_guarded_error (cce_location_t * L, cce_error_handler_t * P_H, void * old_P, size_t newsize)
{
  if (cce_handler_handler(P_H)->resource_pointer == old_P) {
    void *	P = cce_sys_realloc(L, old_P, newsize);
    P_H->handler.resource_pointer = P;
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
  cce_init_and_register_clean_handler_malloc(L, P_H, P);
  return P;
}

void *
cce_sys_calloc_guarded_error (cce_location_t * L, cce_error_handler_t * P_H, size_t count, size_t eltsize)
{
  void *	P = cce_sys_calloc(L, count, eltsize);
  cce_init_and_register_error_handler_malloc(L, P_H, P);
  return P;
}

/* end of file */
