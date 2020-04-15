/*
  Part of: CCExceptions
  Contents: example of data structure types common API
  Date: Apr 11, 2020

  Abstract

	This body file  defines the struct "my_coords_t", passed as  value, using the
	common structs API, without struct descriptor API.

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
cclib_make(my_coords_t, rec) (cce_destination_t upper_L, my_x_t X, my_y_t Y)
{
  cce_location_t	L[1];
  cce_error_handler_t	X_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    my_coords_t	S = {
      .X = cce_sys_malloc_guarded(L, X_H, sizeof(my_x_t)),
      .Y = cce_sys_malloc(L, sizeof(my_y_t))
    };

    *(S.X) = X;
    *(S.Y) = Y;
    cce_run_body_handlers(L);
    return S;
  }
}

my_coords_t
cclib_make(my_coords_t, pol) (cce_destination_t L, my_rho_t RHO, my_theta_t THETA)
{
  return cclib_make(my_coords_t, rec)(L, cclib_make(my_x_t, pol)(RHO, THETA), cclib_make(my_y_t, pol)(RHO, THETA));
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
  fprintf(stderr, "%s: enter final function\n", __func__);
  cclib_unmake(my_coords_t)(*SP);
  fprintf(stderr, "%s: finalised \n", __func__);
}


/** --------------------------------------------------------------------
 ** Plain exception handlers.
 ** ----------------------------------------------------------------- */

static void
cclib_exception_handler_function(my_coords_t, clean) (cce_condition_t const * C CCLIB_UNUSED, cce_clean_handler_t const * const _self_H)
{
  if (1) { fprintf(stderr, "%-35s: enter exception handler\n", __func__); }
  {
    CCLIB_PC(cclib_exception_handler_type(my_coords_t, clean) const, self_H, _self_H);

    cclib_unmake(my_coords_t)(self_H->resource);
  }
  if (1) { fprintf(stderr, "%-35s: exception handling done\n", __func__); }
}

static void
cclib_exception_handler_function(my_coords_t, error) (cce_condition_t const * C CCLIB_UNUSED, cce_error_handler_t const * const _self_H)
{
  if (1) { fprintf(stderr, "%-35s: enter exception handler\n", __func__); }
  {
    CCLIB_PC(cclib_exception_handler_type(my_coords_t, error) const, self_H, _self_H);

    cclib_unmake(my_coords_t)(self_H->resource);
  }
  if (1) { fprintf(stderr, "%-35s: exception handling done\n", __func__); }
}

void
cclib_exception_handler_init_and_register(my_coords_t, clean)
  (cce_destination_t L, cclib_exception_handler_type(my_coords_t, clean) * self_H, my_coords_t self)
{
  self_H->resource = self;
  /* We could very well use  "cce_default_error_handler_function()", but for the sake
     of  showing  how  to  do  it:  we use  the  custom  exception  handler  function
     "cclib_exception_handler_function(my_coords_t, clean)()". */
  cce_init_and_register_handler(L, &(self_H->handler),
				cclib_exception_handler_function(my_coords_t, clean),
				cce_resource_pointer(&(self_H->resource)));
}

void
cclib_exception_handler_init_and_register(my_coords_t, error)
  (cce_destination_t L, struct cclib_exception_handler_type(my_coords_t, error) * self_H, my_coords_t self)
{
  self_H->resource = self;
  /* We could very well use  "cce_default_error_handler_function()", but for the sake
     of  showing  how  to  do  it:  we use  the  custom  exception  handler  function
     "cclib_exception_handler_function(my_coords_t, error)()". */
  cce_init_and_register_handler(L, &(self_H->handler),
				cclib_exception_handler_function(my_coords_t, error),
				cce_resource_pointer(&(self_H->resource)));
}


/** --------------------------------------------------------------------
 ** Guarded constructors.
 ** ----------------------------------------------------------------- */

my_coords_t
cclib_make(my_coords_t, rec, guarded, clean)
  (cce_destination_t L, cclib_exception_handler_type(my_coords_t, clean) * self_H, my_x_t X, my_y_t Y)
{
  my_coords_t	self = cclib_make(my_coords_t, rec)(L, X, Y);

  cclib_exception_handler_init_and_register(my_coords_t, clean)(L, self_H, self);
  return self;
}

my_coords_t
cclib_make(my_coords_t, rec, guarded, error)
  (cce_destination_t L, cclib_exception_handler_type(my_coords_t, error) * self_H, my_x_t X, my_y_t Y)
{
  my_coords_t	self = cclib_make(my_coords_t, rec)(L, X, Y);

  cclib_exception_handler_init_and_register(my_coords_t, error)(L, self_H, self);
  return self;
}

/* ------------------------------------------------------------------ */

my_coords_t
cclib_make(my_coords_t, pol, guarded, clean)
  (cce_destination_t L, cclib_exception_handler_type(my_coords_t, clean) * self_H, my_rho_t RHO, my_theta_t THETA)
{
  my_coords_t	self = cclib_make(my_coords_t, pol)(L, RHO, THETA);

  cclib_exception_handler_init_and_register(my_coords_t, clean)(L, self_H, self);
  return self;
}

my_coords_t
cclib_make(my_coords_t, pol, guarded, error)
  (cce_destination_t L, cclib_exception_handler_type(my_coords_t, error) * self_H, my_rho_t RHO, my_theta_t THETA)
{
  my_coords_t	self = cclib_make(my_coords_t, pol)(L, RHO, THETA);

  cclib_exception_handler_init_and_register(my_coords_t, error)(L, self_H, self);
  return self;
}

/* end of file */
