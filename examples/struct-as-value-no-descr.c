/*
  Part of: CCExceptions
  Contents: demo program for CCLibraries, struct as value with no descriptor
  Date: Apr 11, 2020

  Abstract

	This body  file implements functions  for the struct "my_coords_t"  as value,
	which implements the common API.

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

#include "struct-as-value-no-descr.h"
#include <math.h>


/** --------------------------------------------------------------------
 ** Data struct "my_coords_t": well known functions.
 ** ----------------------------------------------------------------- */

my_coords_t
cclib_make(my_coords_t, rec) (cce_destination_t upper_L, double X, double Y)
{
  cce_location_t	L[1];
  cce_error_handler_t	X_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    my_coords_t	S = {
      .X = cce_sys_malloc_guarded(L, X_H, sizeof(double)),
      .Y = cce_sys_malloc(L, sizeof(double))
    };

    *(S.X) = X;
    *(S.Y) = Y;
    cce_run_body_handlers(L);
    return S;
  }
}

my_coords_t
cclib_make(my_coords_t, pol) (cce_destination_t upper_L, double RHO, double THETA)
{
  cce_location_t	L[1];
  cce_error_handler_t	X_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    my_coords_t	S = {
      .X = cce_sys_malloc_guarded(L, X_H, sizeof(double)),
      .Y = cce_sys_malloc(L, sizeof(double))
    };

    *(S.X) = RHO * cos(THETA);
    *(S.Y) = RHO * sin(THETA);
    cce_run_body_handlers(L);
    return S;
  }
}

void
cclib_unmake(my_coords_t) (my_coords_t S)
{
  fprintf(stderr, "%s: enter unmake function\n", __func__);
  free(S.X);
  free(S.Y);
  fprintf(stderr, "%s: unmade \n", __func__);
}

void
cclib_final(my_coords_t) (my_coords_t * SP)
{
  cclib_unmake(my_coords_t)(*SP);
}

/* end of file */