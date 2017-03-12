/*
  Part of: CCExceptions
  Contents: exception handlers for POSIX stuff
  Date: Sat Mar 11, 2017

  Abstract



  Copyright (C) 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

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


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "ccexceptions.h"
#include <string.h>


/** --------------------------------------------------------------------
 ** Predefined POSIX exception handler: malloc pointer.
 ** ----------------------------------------------------------------- */

__attribute__((nonnull(1,2)))
static void
cce_handler_malloc_function (const cce_condition_t * C CCE_UNUSED, cce_handler_t * _H)
{
  cce_handler_malloc_t *	H = cce_cast_to_handler_malloc(_H);
  free(H->pointer);
  if (0) { fprintf(stderr, "%s: done\n", __func__); }
}

void
cce_cleanup_handler_malloc_init (cce_location_t * L, cce_handler_malloc_t * H, void * pointer)
{
  H->handler_function	= cce_handler_malloc_function;
  H->pointer		= pointer;
  cce_register_cleanup_handler(L, H);
}

void
cce_error_handler_malloc_init (cce_location_t * L, cce_handler_malloc_t * H, void * pointer)
{
  H->handler_function	= cce_handler_malloc_function;
  H->pointer		= pointer;
  cce_register_error_handler(L, H);
}


/** --------------------------------------------------------------------
 ** Predefined POSIX exception handler: file descriptor.
 ** ----------------------------------------------------------------- */

__attribute__((nonnull(1,2)))
static void
cce_handler_filedes_function (const cce_condition_t * C CCE_UNUSED, cce_handler_t * _H)
{
  cce_handler_filedes_t *	H = cce_cast_to_handler_filedes(_H);
  close(H->filedes);
  if (0) { fprintf(stderr, "%s: done\n", __func__); }
}

void
cce_cleanup_handler_filedes_init (cce_location_t * L, cce_handler_filedes_t * H, int filedes)
{
  H->handler_function	= cce_handler_filedes_function;
  H->filedes		= filedes;
  cce_register_cleanup_handler(L, H);
}

void
cce_error_handler_filedes_init (cce_location_t * L, cce_handler_filedes_t * H, int filedes)
{
  H->handler_function	= cce_handler_filedes_function;
  H->filedes		= filedes;
  cce_register_error_handler(L, H);
}


/** --------------------------------------------------------------------
 ** Predefined POSIX exception handler: pipe descriptors.
 ** ----------------------------------------------------------------- */

__attribute__((nonnull(1,2)))
static void
cce_handler_pipedes_function (const cce_condition_t * C CCE_UNUSED, cce_handler_t * _H)
{
  cce_handler_pipedes_t *	H = cce_cast_to_handler_pipedes(_H);
  close(H->pipedes[0]);
  close(H->pipedes[1]);
  if (0) { fprintf(stderr, "%s: done\n", __func__); }
}

void
cce_cleanup_handler_pipedes_init (cce_location_t * L, cce_handler_pipedes_t * H, int pipedes[2])
{
  H->handler_function	= cce_handler_pipedes_function;
  H->pipedes[0]		= pipedes[0];
  H->pipedes[1]		= pipedes[1];
  cce_register_cleanup_handler(L, H);
}

void
cce_error_handler_pipedes_init (cce_location_t * L, cce_handler_pipedes_t * H, int pipedes[2])
{
  H->handler_function	= cce_handler_pipedes_function;
  H->pipedes[0]		= pipedes[0];
  H->pipedes[1]		= pipedes[1];
  cce_register_error_handler(L, H);
}


/** --------------------------------------------------------------------
 ** Predefined POSIX exception handler: pipe descriptors.
 ** ----------------------------------------------------------------- */

__attribute__((nonnull(1,2)))
static void
cce_handler_tmpfile_function (const cce_condition_t * C CCE_UNUSED, cce_handler_t * _H)
{
  cce_handler_tmpfile_t *	H = cce_cast_to_handler_tmpfile(_H);
  remove(H->pathname);
  free(H->pathname);
  if (0) { fprintf(stderr, "%s: done\n", __func__); }
}

void
cce_cleanup_handler_tmpfile_init (cce_location_t * L, cce_handler_tmpfile_t * H, const char * pathname)
{
  size_t	len = 1+strlen(pathname);
  char *	ptr = cce_sys_malloc(L, len);
  strncpy(ptr, pathname, len);
  ptr[len] = '\n';
  H->handler_function	= cce_handler_tmpfile_function;
  H->pathname		= ptr;
  cce_register_cleanup_handler(L, H);
}

void
cce_error_handler_tmpfile_init (cce_location_t * L, cce_handler_tmpfile_t * H, const char * pathname)
{
  size_t	len = 1+strlen(pathname);
  char *	ptr = cce_sys_malloc(L, len);
  strncpy(ptr, pathname, len);
  ptr[len] = '\n';
  H->handler_function	= cce_handler_tmpfile_function;
  H->pathname		= ptr;
  cce_register_error_handler(L, H);
}

/* end of file */
