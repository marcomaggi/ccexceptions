/*
  Part of: CCExceptions
  Contents: example of data structure type implementing the common API
  Date: Apr 12, 2020

  Abstract

	This source file defines the struct "my_coords_t", passed as value, using the
	common structs API, using the struct descriptor API.

  Copyright (C) 2020 Marco Maggi <mrc.mgg@gmail.com>

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

#include "struct-as-value-with-descr.h"


/** --------------------------------------------------------------------
 ** Data struct "my_coords_t": methods table.
 ** ----------------------------------------------------------------- */

/* A prototype for every method. */
static cclib_method_type(my_coords_t, destroy)	cclib_method(my_coords_t, destroy);
static cclib_method_type(my_coords_t, print)	cclib_method(my_coords_t, print);

/* The methods tble */
static cclib_methods_table_type(my_coords_t) const cclib_methods_table(my_coords_t) = {
  .destroy	= cclib_method(my_coords_t, destroy),
  .print	= cclib_method(my_coords_t, print)
};


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

    cclib_struct_descriptor_set_methods_table_pointer(&S, &cclib_methods_table(my_coords_t));
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
  cclib_unmake(my_coords_t)(*SP);
}


/** --------------------------------------------------------------------
 ** Method implementations: destructor methods.
 ** ----------------------------------------------------------------- */

void
cclib_method(my_coords_t, destroy) (my_coords_t self)
{
  cclib_unmake(my_coords_t)(self);
}

void
cclib_method(my_coords_t, print) (my_coords_t self, FILE * stream)
{
  fprintf(stream, "my_coords_t: %s: X=%f, Y=%f\n", __func__, self.X->val, self.Y->val);
}


/** --------------------------------------------------------------------
 ** Exception handlers.
 ** ----------------------------------------------------------------- */

void
cclib_exception_handler_init_and_register(my_coords_t, clean)
  (cce_destination_t L, cclib_exception_handler_type(my_coords_t, clean) * self_H, my_coords_t self)
{
  self_H->resource = self;
  /* Notice that  the resource pointer we  store in the  handler is a pointer  to the
     field in the handler itself!  The data  structure is passed by value, so we need
     to store a copy for it to be available if the exception handler is called. */
  cce_init_and_register_handler(L, &(self_H->handler),
				cce_default_clean_handler_function,
                                cce_resource_pointer(&(self_H->resource)),
				cce_resource_destructor(cclib_final(my_coords_t)));
}

void
cclib_exception_handler_init_and_register(my_coords_t, error)
  (cce_destination_t L, cclib_exception_handler_type(my_coords_t, error) * self_H, my_coords_t self)
{
  self_H->resource = self;
  /* Notice that  the resource pointer we  store in the  handler is a pointer  to the
     field in the handler itself!  The data  structure is passed by value, so we need
     to store a copy for it to be available if the exception handler is called. */
  cce_init_and_register_handler(L, &(self_H->handler),
				cce_default_error_handler_function,
                                cce_resource_pointer(&(self_H->resource)),
				cce_resource_destructor(cclib_final(my_coords_t)));
}


/** --------------------------------------------------------------------
 ** Guarded constructors.
 ** ----------------------------------------------------------------- */

my_coords_t
cclib_make(my_coords_t, rec, guarded, clean)
  (cce_destination_t L, cclib_exception_handler_type(my_coords_t, clean) * S_H, my_x_t X, my_y_t Y)
{
  my_coords_t	S = cclib_make(my_coords_t, rec)(L, X, Y);

  cclib_exception_handler_init_and_register(my_coords_t, clean)(L, S_H, S);
  return S;
}

my_coords_t
cclib_make(my_coords_t, rec, guarded, error)
  (cce_destination_t L, cclib_exception_handler_type(my_coords_t, error) * S_H, my_x_t X, my_y_t Y)
{
  my_coords_t	S = cclib_make(my_coords_t, rec)(L, X, Y);

  cclib_exception_handler_init_and_register(my_coords_t, error)(L, S_H, S);
  return S;
}

my_coords_t
cclib_make(my_coords_t, pol, guarded, clean)
  (cce_destination_t L, cclib_exception_handler_type(my_coords_t, clean) * S_H, my_rho_t RHO, my_theta_t THETA)
{
  my_coords_t	S = cclib_make(my_coords_t, pol)(L, RHO, THETA);

  cclib_exception_handler_init_and_register(my_coords_t, clean)(L, S_H, S);
  return S;
}

my_coords_t
cclib_make(my_coords_t, pol, guarded, error)
  (cce_destination_t L, cclib_exception_handler_type(my_coords_t, error) * S_H, my_rho_t RHO, my_theta_t THETA)
{
  my_coords_t	S = cclib_make(my_coords_t, pol)(L, RHO, THETA);

  cclib_exception_handler_init_and_register(my_coords_t, error)(L, S_H, S);
  return S;
}

/* end of file */
