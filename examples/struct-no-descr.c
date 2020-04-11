/*
  Part of: CCExceptions
  Contents: demo program for CCLibraries, struct with no descriptor
  Date: Jan  4, 2019

  Abstract

	This  body file  implements  functions for  the  struct "my_coords_t",  which
	implements the  common API.

  Copyright (C) 2019-2020 Marco Maggi <mrc.mgg@gmail.com>

  The author  hereby grant permission to  use, copy, modify, distribute,  and license
  this  software  and its  documentation  for  any  purpose, provided  that  existing
  copyright  notices are  retained in  all copies  and that  this notice  is included
  verbatim in  any distributions. No  written agreement,  license, or royalty  fee is
  required for  any of the  authorized uses.  Modifications  to this software  may be
  copyrighted by  their authors  and need  not follow  the licensing  terms described
  here, provided that the  new terms are clearly indicated on the  first page of each
  file where they apply.

  IN NO  EVENT SHALL THE AUTHOR  OR DISTRIBUTORS BE  LIABLE TO ANY PARTY  FOR DIRECT,
  INDIRECT, SPECIAL, INCIDENTAL,  OR CONSEQUENTIAL DAMAGES ARISING OUT OF  THE USE OF
  THIS SOFTWARE,  ITS DOCUMENTATION, OR ANY  DERIVATIVES THEREOF, EVEN IF  THE AUTHOR
  HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  THE AUTHOR  AND DISTRIBUTORS SPECIFICALLY  DISCLAIM ANY WARRANTIES,  INCLUDING, BUT
  NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
  PURPOSE, AND NON-INFRINGEMENT.  THIS SOFTWARE IS  PROVIDED ON AN "AS IS" BASIS, AND
  THE AUTHOR  AND DISTRIBUTORS  HAVE NO OBLIGATION  TO PROVIDE  MAINTENANCE, SUPPORT,
  UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
*/


/** --------------------------------------------------------------------
 ** Descrs.
 ** ----------------------------------------------------------------- */

#include "struct-no-descr.h"
#include <errno.h>
#include <math.h>
#include <stdarg.h>


/** --------------------------------------------------------------------
 ** Data struct "my_coords_t": well known functions.
 ** ----------------------------------------------------------------- */

void
cclib_init(my_coords_t, rec) (my_coords_t * S, double X, double Y)
{
  S->X = X;
  S->Y = Y;
}

void
cclib_init(my_coords_t, pol) (my_coords_t * S, double RHO, double THETA)
{
  S->X = RHO * cos(THETA);
  S->Y = RHO * sin(THETA);
}

/* ------------------------------------------------------------------ */

void
cclib_final(my_coords_t) (my_coords_t const * S CCLIB_UNUSED)
{
  if (1) { fprintf(stderr, "%-35s: finalised\n", __func__); }
}

/* ------------------------------------------------------------------ */

static my_coords_t *
cclib_alloc(my_coords_t) (cce_destination_t L)
{
  return (my_coords_t *)cce_sys_malloc(L, sizeof(my_coords_t));
}

/* ------------------------------------------------------------------ */

static void
cclib_release(my_coords_t) (my_coords_t const * S)
{
  free((void *)S);
  if (1) { fprintf(stderr, "%-35s: released\n", __func__); }
}

/* ------------------------------------------------------------------ */

my_coords_t const *
cclib_new(my_coords_t, rec) (cce_destination_t L, double X, double Y)
{
  my_coords_t * S = cclib_alloc(my_coords_t)(L);

  cclib_init(my_coords_t, rec)(S, X, Y);
  return S;
}

my_coords_t const *
cclib_new(my_coords_t, pol) (cce_destination_t L, double RHO, double THETA)
{
  my_coords_t * S = cclib_alloc(my_coords_t)(L);

  cclib_init(my_coords_t, pol)(S, RHO, THETA);
  return S;
}

/* ------------------------------------------------------------------ */

void
cclib_delete(my_coords_t) (my_coords_t const * S)
{
  cclib_final(my_coords_t)(S);
  cclib_release(my_coords_t)(S);
  if (1) { fprintf(stderr, "%-35s: delete\n", __func__); }
}


/** --------------------------------------------------------------------
 ** Plain exception handlers.
 ** ----------------------------------------------------------------- */

static void
my_coords_clean_handler_final (cce_condition_t const * C CCLIB_UNUSED, cce_clean_handler_t const * const H)
/* Destructor handler for embedded instances.  Release all the asynchronous resources
   associated to the struct instance; does not touch the struct itself. */
{
  CCLIB_PC(my_coords_t, self, cce_handler_resource_pointer(H));

  cclib_final(my_coords_t)(self);
  if (1) { fprintf(stderr, "%-35s: finalised by plain handler\n", __func__); }
}

static void
my_coords_error_handler_final (cce_condition_t const * C CCLIB_UNUSED, cce_error_handler_t const * const H)
/* Destructor handler for embedded instances.  Release all the asynchronous resources
   associated to the struct instance; does not touch the struct itself. */
{
  CCLIB_PC(my_coords_t, self, cce_handler_resource_pointer(H));

  cclib_final(my_coords_t)(self);
  if (1) { fprintf(stderr, "%-35s: finalised by plain handler\n", __func__); }
}

void
my_coords_register_clean_handler_final (cce_destination_t L, cce_clean_handler_t * H, my_coords_t const * self)
{
  cce_init_and_register_handler(L, H, my_coords_clean_handler_final, cce_resource_pointer(self));
}

void
my_coords_register_error_handler_final (cce_destination_t L, cce_error_handler_t * H, my_coords_t const * self)
{
  cce_init_and_register_handler(L, H, my_coords_error_handler_final, cce_resource_pointer(self));
}

/* ------------------------------------------------------------------ */

static void
my_coords_clean_handler_delete (cce_condition_t const * C CCLIB_UNUSED, cce_clean_handler_t const * const H)
/* Destructor  handler  for  standalone  instances.   Release  all  the  asynchronous
   aresources associated  to the struct  instance; release the memory  block allocated
   for  the  struct instance  using  the  standard  memory allocator  implemented  by
   CCMemory.

   To be used to destroy instances dynamically allocated on the heap. */
{
  CCLIB_PC(my_coords_t, self, cce_handler_resource_pointer(H));

  cclib_delete(my_coords_t)(self);
  if (1) { fprintf(stderr, "%-35s: deleted by plain handler\n", __func__); }
}

static void
my_coords_error_handler_delete (cce_condition_t const * C CCLIB_UNUSED, cce_error_handler_t const * const H)
/* Destructor  handler  for  standalone  instances.   Release  all  the  asynchronous
   aresources associated  to the struct  instance; release the memory  block allocated
   for  the  struct instance  using  the  standard  memory allocator  implemented  by
   CCMemory.

   To be used to destroy instances dynamically allocated on the heap. */
{
  CCLIB_PC(my_coords_t, self, cce_handler_resource_pointer(H));

  cclib_delete(my_coords_t)(self);
  if (1) { fprintf(stderr, "%-35s: deleted by plain handler\n", __func__); }
}

void
my_coords_register_clean_handler_delete (cce_destination_t L, cce_clean_handler_t * H, my_coords_t const * self)
{
  cce_init_and_register_handler(L, H, my_coords_clean_handler_delete, cce_resource_pointer(self));
}

void
my_coords_register_error_handler_delete (cce_destination_t L, cce_error_handler_t * H, my_coords_t const * self)
{
  cce_init_and_register_handler(L, H, my_coords_error_handler_delete, cce_resource_pointer(self));
}

/* end of file */
