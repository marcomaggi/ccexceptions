/*
  Part of: CCExceptions
  Contents: demo program for structs as values with no descriptor, test program
  Date: Apr 11, 2020

  Abstract

	This  test   program  checks  the  behaviour   of  the  API  of   the  struct
	"my_coords_t", passed as value, using  the common structs API, without struct
	descriptor API.

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
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "struct-as-value-no-descr.h"


 /** --------------------------------------------------------------------
 ** Flagging handlers.
 ** ----------------------------------------------------------------- */

/* This handler is used to signal that the "clean" handlers have been executed. */
static void
flag_clean_handler (cce_condition_t const * C CCLIB_UNUSED, cce_clean_handler_t const * H CCLIB_UNUSED)
{
  fprintf(stderr, "%-35s: clean handler fired\n", __func__);
}

void
flag_register_clean_handler (cce_destination_t L, cce_clean_handler_t * H)
{
  cce_init_and_register_handler(L, H, flag_clean_handler, cce_resource_pointer(NULL));
}

/* ------------------------------------------------------------------ */

/* This handler is used to signal that the "error" handlers have been executed. */
static void
flag_error_handler (cce_condition_t const * C CCLIB_UNUSED, cce_error_handler_t const * H CCLIB_UNUSED)
{
  fprintf(stderr, "%-35s: error handler fired\n", __func__);
}

void
flag_register_error_handler (cce_destination_t L, cce_error_handler_t * H)
{
  cce_init_and_register_handler(L, H, flag_error_handler, cce_resource_pointer(NULL));
}


/** --------------------------------------------------------------------
 ** Allocation on the stack, no handlers.
 ** ----------------------------------------------------------------- */

void
test_1_1 (cce_destination_t upper_L)
/* Make the struct, then destroy it with the "unmake()" function. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    my_coords_t	A = cclib_make(my_coords_t, rec)(L, cclib_make(my_x_t)(1.0), cclib_make(my_y_t)(2.0));

    fprintf(stderr, "%s: X=%f, Y=%f\n", __func__, A.X->val, A.Y->val);
    cclib_unmake(my_coords_t)(A);
    cce_run_body_handlers(L);
  }
}

void
test_1_2 (cce_destination_t upper_L)
/* Make the struct, then destroy it with the "final()" function. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    my_coords_t	A = cclib_make(my_coords_t, rec)(L, cclib_make(my_x_t)(1.0), cclib_make(my_y_t)(2.0));

    fprintf(stderr, "%s: X=%f, Y=%f\n", __func__, A.X->val, A.Y->val);
    cclib_final(my_coords_t)(&A);
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Allocation on the stack, plain handler destructors.
 ** ----------------------------------------------------------------- */

void
test_2_1 (cce_destination_t upper_L)
/* Make  the  struct, then  destroy  with  a  "clean"  handler using  the  "final()"
   function. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	FC_H[1];
  cce_error_handler_t	FE_H[1];
  cce_clean_handler_t	A_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    my_coords_t	A = cclib_make(my_coords_t, rec)(L, cclib_make(my_x_t)(1.0), cclib_make(my_y_t)(2.0));
    cce_init_and_register_handler(L, A_H, cce_default_clean_handler_function,
				  cce_resource_pointer(&A),
				  cce_resource_destructor(cclib_final(my_coords_t)));

    flag_register_clean_handler(L, FC_H);
    flag_register_error_handler(L, FE_H);

    fprintf(stderr, "%s: X=%f, Y=%f\n", __func__, A.X->val, A.Y->val);
    cce_run_body_handlers(L);
  }
}

void
test_2_2 (cce_destination_t upper_L)
/* Make the  struct, then  destroy it  with an "error"  handler using  the "final()"
   function. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	FC_H[1];
  cce_error_handler_t	FE_H[1];
  cce_error_handler_t	A_H[1];

  if (cce_location(L)) {
    if (cce_condition_is_logic_error(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    my_coords_t	A = cclib_make(my_coords_t, rec)(L, cclib_make(my_x_t)(1.0), cclib_make(my_y_t)(2.0));
    cce_init_and_register_handler(L, A_H, cce_default_error_handler_function,
				  cce_resource_pointer(&A),
				  cce_resource_destructor(cclib_final(my_coords_t)));

    flag_register_clean_handler(L, FC_H);
    flag_register_error_handler(L, FE_H);

    fprintf(stderr, "%s: X=%f, Y=%f\n", __func__, A.X->val, A.Y->val);
    cce_raise(L, cce_condition_new_logic_error());
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Allocation on the stack, guarded constructors.
 ** ----------------------------------------------------------------- */

void
test_3_1 (cce_destination_t upper_L)
/* Make the struct, use the guarded clean constructor. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	FC_H[1];
  cce_error_handler_t	FE_H[1];
  cclib_exception_handler_type(my_coords_t, clean)	A_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    my_coords_t	A = cclib_make(my_coords_t, rec, guarded, clean)(L, A_H, cclib_make(my_x_t)(1.0), cclib_make(my_y_t)(2.0));

    flag_register_clean_handler(L, FC_H);
    flag_register_error_handler(L, FE_H);

    fprintf(stderr, "%s: X=%f, Y=%f\n", __func__, A.X->val, A.Y->val);
    cce_run_body_handlers(L);
  }
}

void
test_3_2 (cce_destination_t upper_L)
/* Make the struct, use the guarded error constructor. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	FC_H[1];
  cce_error_handler_t	FE_H[1];
  cclib_exception_handler_type(my_coords_t, error)	A_H[1];

  if (cce_location(L)) {
    if (cce_condition_is_logic_error(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    my_coords_t	A = cclib_make(my_coords_t, rec, guarded, error)(L, A_H, cclib_make(my_x_t)(1.0), cclib_make(my_y_t)(2.0));

    flag_register_clean_handler(L, FC_H);
    flag_register_error_handler(L, FE_H);

    fprintf(stderr, "%s: X=%f, Y=%f\n", __func__, A.X->val, A.Y->val);
    cce_raise(L, cce_condition_new_logic_error());
    cce_run_body_handlers(L);
  }
}


int
main (void)
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_final(L);
    exit(EXIT_FAILURE);
  } else {
    test_1_1(L);
    test_1_2(L);

    test_2_1(L);
    test_2_2(L);

    test_3_1(L);
    test_3_2(L);
    cce_run_body_handlers(L);
    exit(EXIT_SUCCESS);
  }
}

/* end of file */
