/*
  Part of: CCStructs
  Contents: test file for sample struct with descriptor
  Date: Dec 27, 2018

  Abstract

	This  test   program  checks  the  behaviour   of  the  API  of   the  struct
	"my_complex_t" implemented as "struct with descr".  See the documentation for
	details.

  Copyright (C) 2018-2020 Marco Maggi <mrc.mgg@gmail.com>

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

#include "struct-by-ptr-with-descr.h"
#include <stdio.h>
#include <stdlib.h>


/** --------------------------------------------------------------------
 ** Flagging handlers.
 ** ----------------------------------------------------------------- */

/* This handler is used to signal that the "clean" handlers have been executed. */
static void
flag_clean_handler (cce_condition_t const * C CCLIB_UNUSED, cce_clean_handler_t const * H CCLIB_UNUSED)
{
  fprintf(stderr, "%-35s: clean handler fired\n", __func__);
}

static void
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

static void
flag_register_error_handler (cce_destination_t L, cce_error_handler_t * H)
{
  cce_init_and_register_handler(L, H, flag_error_handler, cce_resource_pointer(NULL));
}


/** --------------------------------------------------------------------
 ** Allocation and destruction, explicit destructor call.
 ** ----------------------------------------------------------------- */

void
test_1_1_1 (cce_destination_t upper_L)
/* Allocate  the  struct on  the  stack,  then  destroy  by excplicitly  calling  the
   "final()" function. */
{
  cce_location_t	L[1];
  my_complex_t		A[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    cclib_init(my_complex_t, rec)(A,
				  cclib_make(my_real_part_t)(1.0),
				  cclib_make(my_imag_part_t)(2.0));

    cclib_call(print, A, stderr);
    cclib_final(my_complex_t)(A);
    cce_run_body_handlers(L);
  }
}

void
test_1_1_2 (cce_destination_t upper_L)
/* Allocate  the  struct on  the  stack,  then  destroy  by excplicitly  calling  the
   "destroy()" method. */
{
  cce_location_t	L[1];
  my_complex_t		A[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    cclib_init(my_complex_t, rec)(A,
				  cclib_make(my_real_part_t)(1.0),
				  cclib_make(my_imag_part_t)(2.0));

    cclib_call(print, A, stderr);
    cclib_call(destroy, A);
    cce_run_body_handlers(L);
  }
}

void
test_1_2_1 (cce_destination_t upper_L)
/* Allocate  the struct  on  the heap,  then  destroy it  by  explicitly calling  the
   "delete()" function. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    my_complex_t const *A = cclib_new(my_complex_t, rec)(L,
							 cclib_make(my_real_part_t)(1.0),
							 cclib_make(my_imag_part_t)(2.0));

    cclib_call(print, A, stderr);
    cclib_delete(my_complex_t)(A);
    cce_run_body_handlers(L);
  }
}

void
test_1_2_2 (cce_destination_t upper_L)
/* Allocate  the struct  on  the heap,  then  destroy it  by  explicitly calling  the
   "destroy()" method. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    my_complex_t const *A = cclib_new(my_complex_t, rec)(L,
							 cclib_make(my_real_part_t)(1.0),
							 cclib_make(my_imag_part_t)(2.0));

    cclib_call(print, A, stderr);
    cclib_call(destroy, A);
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Allocation and destruction, generic exception-handler API.
 ** ----------------------------------------------------------------- */

void
test_2_1_1 (cce_destination_t upper_L)
/* Allocate the struct on  the stack, then destroy it with  a generic "clean" handler
   using the "final()" function. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	FC_H[1];
  cce_error_handler_t	FE_H[1];
  cce_clean_handler_t	A_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    my_complex_t		A[1];

    cclib_init(my_complex_t, rec)(A, cclib_make(my_real_part_t)(1.0), cclib_make(my_imag_part_t)(2.0));
    cce_init_and_register_handler(L, A_H, cce_default_clean_handler_function,
				  cce_resource_pointer(A),
				  cce_resource_destructor(cclib_final(my_complex_t)));

    flag_register_clean_handler(L, FC_H);
    flag_register_error_handler(L, FE_H);

    cclib_call(print, A, stderr);
    cce_run_body_handlers(L);
  }
}

void
test_2_1_2 (cce_destination_t upper_L)
/* Allocate the struct on  the stack, then destroy it with  a generic "error" handler
   using the "final()" function. */
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
    my_complex_t		A[1];

    cclib_init(my_complex_t, rec)(A, cclib_make(my_real_part_t)(1.0), cclib_make(my_imag_part_t)(2.0));
    cce_init_and_register_handler(L, A_H, cce_default_error_handler_function,
				  cce_resource_pointer(A),
				  cce_resource_destructor(cclib_final(my_complex_t)));

    flag_register_clean_handler(L, FC_H);
    flag_register_error_handler(L, FE_H);

    cclib_call(print, A, stderr);
    cce_raise(L, cce_condition_new_logic_error());
    cce_run_body_handlers(L);
  }
}

void
test_2_2_1 (cce_destination_t upper_L)
/* Allocate the struct  on the heap, then  destroy it with a  generic "clean" handler
   using the "delete()" function. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	FC_H[1];
  cce_error_handler_t	FE_H[1];
  cce_clean_handler_t	A_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    my_complex_t const *	A = cclib_new(my_complex_t, rec)(L, cclib_make(my_real_part_t)(1.0), cclib_make(my_imag_part_t)(2.0));
    cce_init_and_register_handler(L, A_H, cce_default_clean_handler_function,
				  cce_resource_pointer(A),
				  cce_resource_destructor(cclib_delete(my_complex_t)));

    flag_register_clean_handler(L, FC_H);
    flag_register_error_handler(L, FE_H);

    cclib_call(print, A, stderr);
    cce_run_body_handlers(L);
  }
}

void
test_2_2_2 (cce_destination_t upper_L)
/* Allocate the struct  on the heap, then  destroy it with a  generic "error" handler
   using the "delete()" function. */
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
    my_complex_t const *	A = cclib_new(my_complex_t, rec)(L, cclib_make(my_real_part_t)(1.0), cclib_make(my_imag_part_t)(2.0));
    cce_init_and_register_handler(L, A_H, cce_default_error_handler_function,
				  cce_resource_pointer(A),
				  cce_resource_destructor(cclib_delete(my_complex_t)));

    flag_register_clean_handler(L, FC_H);
    flag_register_error_handler(L, FE_H);

    cclib_call(print, A, stderr);
    cce_raise(L, cce_condition_new_logic_error());
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Allocation and destruction, custom exception-handler API.
 ** ----------------------------------------------------------------- */

void
test_3_1_1 (cce_destination_t upper_L)
/* Allocate  the struct  on the  stack,  then destroy  it with  a customised  "clean"
   handler. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	FC_H[1];
  cce_error_handler_t	FE_H[1];
  cclib_exception_handler_type(my_complex_t, clean)	A_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    my_complex_t		A[1];

    cclib_init(my_complex_t, rec)(A, cclib_make(my_real_part_t)(1.0), cclib_make(my_imag_part_t)(2.0));
    cclib_exception_handler_init_and_register(my_complex_t, clean, embedded)(L, A_H, A);

    flag_register_clean_handler(L, FC_H);
    flag_register_error_handler(L, FE_H);

    cclib_call(print, A, stderr);
    cce_run_body_handlers(L);
  }
}

void
test_3_1_2 (cce_destination_t upper_L)
/* Allocate  the struct  on the  stack,  then destroy  it with  a customised  "error"
   handler. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	FC_H[1];
  cce_error_handler_t	FE_H[1];
  cclib_exception_handler_type(my_complex_t, error)	A_H[1];

  if (cce_location(L)) {
    if (cce_condition_is_logic_error(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    my_complex_t		A[1];

    cclib_init(my_complex_t, rec)(A, cclib_make(my_real_part_t)(1.0), cclib_make(my_imag_part_t)(2.0));
    cclib_exception_handler_init_and_register(my_complex_t, error, embedded)(L, A_H, A);

    flag_register_clean_handler(L, FC_H);
    flag_register_error_handler(L, FE_H);

    cclib_call(print, A, stderr);
    cce_raise(L, cce_condition_new_logic_error());
    cce_run_body_handlers(L);
  }
}

void
test_3_2_1 (cce_destination_t upper_L)
/* Allocate  the struct  on  the heap,  then  destroy it  with  a customised  "clean"
   handler. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	FC_H[1];
  cce_error_handler_t	FE_H[1];
  cclib_exception_handler_type(my_complex_t, clean)	A_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    my_complex_t const *	A =
      cclib_new(my_complex_t, rec)(L, cclib_make(my_real_part_t)(1.0), cclib_make(my_imag_part_t)(2.0));
    cclib_exception_handler_init_and_register(my_complex_t, clean, standalone)(L, A_H, A);

    flag_register_clean_handler(L, FC_H);
    flag_register_error_handler(L, FE_H);

    cclib_call(print, A, stderr);
    cce_run_body_handlers(L);
  }
}

void
test_3_2_2 (cce_destination_t upper_L)
/* Allocate  the struct  on  the heap,  then  destroy it  with  a customised  "error"
   handler. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	FC_H[1];
  cce_error_handler_t	FE_H[1];
  cclib_exception_handler_type(my_complex_t, error)	A_H[1];

  if (cce_location(L)) {
    if (cce_condition_is_logic_error(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    my_complex_t const *	A =
      cclib_new(my_complex_t, rec)(L, cclib_make(my_real_part_t)(1.0), cclib_make(my_imag_part_t)(2.0));
    cclib_exception_handler_init_and_register(my_complex_t, error, standalone)(L, A_H, A);

    flag_register_clean_handler(L, FC_H);
    flag_register_error_handler(L, FE_H);

    cclib_call(print, A, stderr);
    cce_raise(L, cce_condition_new_logic_error());
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Allocation and destruction, guarded constructors API.
 ** ----------------------------------------------------------------- */

void
test_4_1_1 (cce_destination_t upper_L)
/* Allocate the struct on the stack, use a clean guarded constructor. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	FC_H[1];
  cce_error_handler_t	FE_H[1];
  cclib_exception_handler_type(my_complex_t, clean)	A_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    my_complex_t		A[1];

    cclib_init(my_complex_t, rec, guarded, clean)(L, A_H, A, cclib_make(my_real_part_t)(1.0), cclib_make(my_imag_part_t)(2.0));

    flag_register_clean_handler(L, FC_H);
    flag_register_error_handler(L, FE_H);

    cclib_call(print, A, stderr);
    cce_run_body_handlers(L);
  }
}

void
test_4_1_2 (cce_destination_t upper_L)
/* Allocate the struct on the stack, use an error guarded constructor. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	FC_H[1];
  cce_error_handler_t	FE_H[1];
  cclib_exception_handler_type(my_complex_t, error)	A_H[1];

  if (cce_location(L)) {
    if (cce_condition_is_logic_error(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    my_complex_t		A[1];

    cclib_init(my_complex_t, rec, guarded, error)(L, A_H, A, cclib_make(my_real_part_t)(1.0), cclib_make(my_imag_part_t)(2.0));

    flag_register_clean_handler(L, FC_H);
    flag_register_error_handler(L, FE_H);

    cclib_call(print, A, stderr);
    cce_raise(L, cce_condition_new_logic_error());
    cce_run_body_handlers(L);
  }
}

void
test_4_1_3 (cce_destination_t upper_L)
/* Allocate  the  struct on  the  stack,  use  a  clean guarded  constructor.   Polar
   coordinates. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	FC_H[1];
  cce_error_handler_t	FE_H[1];
  cclib_exception_handler_type(my_complex_t, clean)	A_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    my_complex_t		A[1];

    cclib_init(my_complex_t, pol, guarded, clean)(L, A_H, A, cclib_make(my_magnitude_t)(1.0), cclib_make(my_angle_t)(2.0));

    flag_register_clean_handler(L, FC_H);
    flag_register_error_handler(L, FE_H);

    cclib_call(print, A, stderr);
    cce_run_body_handlers(L);
  }
}

void
test_4_2_1 (cce_destination_t upper_L)
/* Allocate the struct on the heap, use a guarded clean constructor. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	FC_H[1];
  cce_error_handler_t	FE_H[1];
  cclib_exception_handler_type(my_complex_t, clean)	A_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    my_complex_t const *	A =
      cclib_new(my_complex_t, rec, guarded, clean)(L, A_H, cclib_make(my_real_part_t)(1.0), cclib_make(my_imag_part_t)(2.0));

    flag_register_clean_handler(L, FC_H);
    flag_register_error_handler(L, FE_H);

    cclib_call(print, A, stderr);
    cce_run_body_handlers(L);
  }
}

void
test_4_2_2 (cce_destination_t upper_L)
/* Allocate the struct on the heap, use a guarded clean constructor. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	FC_H[1];
  cce_error_handler_t	FE_H[1];
  cclib_exception_handler_type(my_complex_t, error)	A_H[1];

  if (cce_location(L)) {
    if (cce_condition_is_logic_error(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    my_complex_t const *	A =
      cclib_new(my_complex_t, rec, guarded, error)(L, A_H, cclib_make(my_real_part_t)(1.0), cclib_make(my_imag_part_t)(2.0));

    flag_register_clean_handler(L, FC_H);
    flag_register_error_handler(L, FE_H);

    cclib_call(print, A, stderr);
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
    test_1_1_1(L);
    test_1_1_2(L);
    test_1_2_1(L);
    test_1_2_2(L);

    test_2_1_1(L);
    test_2_1_2(L);
    test_2_2_1(L);
    test_2_2_2(L);

    test_3_1_1(L);
    test_3_1_2(L);
    test_3_2_1(L);
    test_3_2_2(L);

    test_4_1_1(L);
    test_4_1_2(L);
    test_4_1_3(L);
    test_4_2_1(L);
    test_4_2_2(L);

    cce_run_body_handlers(L);
    exit(EXIT_SUCCESS);
  }
}

/* end of file */
