/*
  Part of: CCExceptions
  Contents: example of data structure types common API
  Date: Apr 11, 2020

  Abstract

	This header file defines the struct "my_coords_t", passed as value, using the
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

#ifndef STRUCT_AS_VALUE_NO_DESCR_H
#define STRUCT_AS_VALUE_NO_DESCR_H

#ifdef __cplusplus
extern "C" {
#endif


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/** --------------------------------------------------------------------
 ** Preliminary type definitions.
 ** ----------------------------------------------------------------- */

#undef  MY_DEFINE_PARM
#define MY_DEFINE_PARM(NAME)						\
  typedef struct my_ ## NAME ## _t		my_ ## NAME ## _t;	\
									\
  struct my_ ## NAME ## _t {						\
    double	val;							\
  };									\
									\
  CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE					\
  static inline my_ ## NAME ## _t					\
  cclib_make(my_ ## NAME ## _t) (double val)				\
  {									\
    return (my_ ## NAME ## _t) { .val = val };				\
  }

MY_DEFINE_PARM(x)
MY_DEFINE_PARM(y)
MY_DEFINE_PARM(rho)
MY_DEFINE_PARM(theta)

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
static inline my_x_t
cclib_make(my_x_t, pol) (my_rho_t rho, my_theta_t theta)
{
  return (my_x_t) { .val = rho.val * cos(theta.val) };
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
static inline my_y_t
cclib_make(my_y_t, pol) (my_rho_t rho, my_theta_t theta)
{
  return (my_y_t) { .val = rho.val * sin(theta.val) };
}


/** --------------------------------------------------------------------
 ** Type definitions: data struct "my_coords_t".
 ** ----------------------------------------------------------------- */

typedef struct my_coords_t	my_coords_t;

struct my_coords_t {
  /* We implement the coordinates storage with  dynamic memory allocation to show how
     to handle asynchronous resources. */
  my_x_t	*X;
  my_y_t	*Y;
};


/** --------------------------------------------------------------------
 ** Data struct "my_coords_t": well known functions API.
 ** ----------------------------------------------------------------- */

/* Maker function.  This initialises from rectangular coordinates. */
cclib_decl my_coords_t cclib_make(my_coords_t, rec) (cce_destination_t L, my_x_t X, my_y_t Y);

/* Maker function.  This initialises from polar coordinates. */
cclib_decl my_coords_t cclib_make(my_coords_t, pol) (cce_destination_t L, my_rho_t RHO, my_theta_t THETA);

/* Destructor function. */
cclib_decl void cclib_unmake(my_coords_t) (my_coords_t S);

/* Destructor function. */
cclib_decl void cclib_final(my_coords_t) (my_coords_t * S);


/** --------------------------------------------------------------------
 ** Function prototypes: plain exception handlers.
 ** ----------------------------------------------------------------- */

typedef struct cclib_exception_handler_type(my_coords_t, clean) cclib_exception_handler_type(my_coords_t, clean);
typedef struct cclib_exception_handler_type(my_coords_t, error)	cclib_exception_handler_type(my_coords_t, error);

struct cclib_exception_handler_type(my_coords_t, clean) {
  cce_clean_handler_t	handler;
  my_coords_t		resource;
};

struct cclib_exception_handler_type(my_coords_t, error) {
  cce_error_handler_t	handler;
  my_coords_t		resource;
};

cclib_decl void cclib_exception_handler_init_and_register(my_coords_t, clean)
  (cce_destination_t L, cclib_exception_handler_type(my_coords_t, clean) * self_H, my_coords_t self)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2);

cclib_decl void cclib_exception_handler_init_and_register(my_coords_t, error)
  (cce_destination_t L, cclib_exception_handler_type(my_coords_t, error) * self_H, my_coords_t self)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2);


/** --------------------------------------------------------------------
 ** Guarded constructors.
 ** ----------------------------------------------------------------- */

cclib_decl my_coords_t cclib_make(my_coords_t, rec, guarded, clean)
  (cce_destination_t L, cclib_exception_handler_type(my_coords_t, clean) * S_H, my_x_t X, my_y_t Y)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2);

cclib_decl my_coords_t cclib_make(my_coords_t, rec, guarded, error)
  (cce_destination_t L, cclib_exception_handler_type(my_coords_t, error) * S_H, my_x_t X, my_y_t Y)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2);

/* ------------------------------------------------------------------ */

cclib_decl my_coords_t cclib_make(my_coords_t, pol, guarded, clean)
  (cce_destination_t L, cclib_exception_handler_type(my_coords_t, clean) * S_H, my_rho_t RHO, my_theta_t THETA)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2);

cclib_decl my_coords_t cclib_make(my_coords_t, pol, guarded, error)
  (cce_destination_t L, cclib_exception_handler_type(my_coords_t, error) * S_H, my_rho_t RHO, my_theta_t THETA)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2);


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* define STRUCT_AS_VALUE_NO_DESCR_H */

/* end of file */
