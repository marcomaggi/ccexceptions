/*
  Part of: CCExceptions
  Contents: test program for the example destructor trait
  Date: Apr 12, 2020

  Abstract

	This  test program  checks  the  behaviour of  the  example destructor  trait
	defined in the header file "examples/destructor-trait.h".

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
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "destructor-trait.h"
#include "struct-with-descr.h"
#include "struct-as-value-with-descr.h"


/** --------------------------------------------------------------------
 ** The destructor trait as implemented by my_coords_t.
 ** ----------------------------------------------------------------- */

/* A prototype for every method in the destructor trait implementation. */
static cclib_method_type(my_destructor_T, destroy)
  cclib_method(my_destructor_T, destroy, my_coords_t);
static cclib_method_type(my_destructor_T, retrieve_cce_resource_destructor)
  cclib_method(my_destructor_T, retrieve_cce_resource_destructor, my_coords_t);

/* The table  of methods  for the  destructor trait as  implemented by  the structure
   "my_coords_t". */
static cclib_methods_table_type(my_destructor_T) const cclib_methods_table(my_destructor_T, my_coords_t) = {
  .destroy                          = cclib_method(my_destructor_T, destroy,                          my_coords_t),
  .retrieve_cce_resource_destructor = cclib_method(my_destructor_T, retrieve_cce_resource_destructor, my_coords_t)
};

my_destructor_T
cclib_make(my_destructor_T, my_coords_t) (my_coords_t const * self)
/* The constructor for my_destructor_T implemented by "my_coords_t". */
{
  return cclib_make(my_destructor_T)(cclib_resource_pointer(self), &cclib_methods_table(my_destructor_T, my_coords_t));
}

void
cclib_method(my_destructor_T, destroy, my_coords_t) (my_destructor_T impl)
/* Implementation  of  the  method  "destroy()" of  the  trait  "my_destructor_T"  as
   implemented by the data type "my_coords_t". */
{
  fprintf(stderr, "%s: enter method destroy\n", __func__);
  {
    my_coords_t const	* self = cclib_trait_resource_pointer(impl);

    cclib_vcall(destroy, *self);
  }
  fprintf(stderr, "%s: method destroy done\n", __func__);
}

cce_resource_destructor_fun_t *
cclib_method(my_destructor_T, retrieve_cce_resource_destructor, my_coords_t) (my_destructor_T impl CCLIB_UNUSED)
/* Implementation  of the  method "retrieve_cce_resource_destructor()"  of the  trait
   "my_destructor_T" as implemented by the data type "my_coords_t". */
{
  return cce_resource_destructor(cclib_final(my_coords_t));
}


/** --------------------------------------------------------------------
 ** The destructor trait as implemented by my_complex_t.
 ** ----------------------------------------------------------------- */

/* A prototype for every method in the destructor trait implementation. */
static cclib_method_type(my_destructor_T, destroy)
  cclib_method(my_destructor_T, destroy, my_complex_t);
static cclib_method_type(my_destructor_T, retrieve_cce_resource_destructor)
  cclib_method(my_destructor_T, retrieve_cce_resource_destructor, my_complex_t);

/* The table  of methods  for the  destructor trait as  implemented by  the structure
   "my_complex_t". */
static cclib_methods_table_type(my_destructor_T) const cclib_methods_table(my_destructor_T, my_complex_t) = {
  .destroy                          = cclib_method(my_destructor_T, destroy,                          my_complex_t),
  .retrieve_cce_resource_destructor = cclib_method(my_destructor_T, retrieve_cce_resource_destructor, my_complex_t)
};

my_destructor_T
cclib_make(my_destructor_T, my_complex_t) (my_complex_t const * self)
/* The constructor for my_destructor_T implemented by "my_complex_t". */
{
  return cclib_make(my_destructor_T)(cclib_resource_pointer(self), &cclib_methods_table(my_destructor_T, my_complex_t));
}

void
cclib_method(my_destructor_T, destroy, my_complex_t) (my_destructor_T impl)
/* Implementation  of  the  method  "destroy()" of  the  trait  "my_destructor_T"  as
   implemented by the data type "my_complex_t". */
{
  fprintf(stderr, "%s: enter method destroy\n", __func__);
  {
    my_complex_t const	* self = cclib_trait_resource_pointer(impl);

    cclib_call(destroy, self);
  }
  fprintf(stderr, "%s: method destroy done\n", __func__);
}

cce_resource_destructor_fun_t *
cclib_method(my_destructor_T, retrieve_cce_resource_destructor, my_complex_t) (my_destructor_T impl CCLIB_UNUSED)
/* Implementation  of the  method "retrieve_cce_resource_destructor()"  of the  trait
   "my_destructor_T" as implemented by the data type "my_complex_t". */
{
  my_complex_t const	* self = cclib_trait_resource_pointer(impl);

  return cce_resource_destructor(cclib_method_pointer(self, destroy));
}


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
 ** Test for the data structure as value.
 ** ----------------------------------------------------------------- */

void
test_1_1 (cce_destination_t upper_L)
/* Make the struct, then destroy it with the "unmake()" common function. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    my_coords_t	A = cclib_make(my_coords_t, rec)(L, 1.0, 2.0);

    cclib_vcall(print, A, stderr);
    cclib_unmake(my_coords_t)(A);
    cce_run_body_handlers(L);
  }
}

void
test_1_2 (cce_destination_t upper_L)
/* Make the struct, then destroy it with the "final()" common function. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    my_coords_t	A = cclib_make(my_coords_t, rec)(L, 1.0, 2.0);

    cclib_vcall(print, A, stderr);
    cclib_final(my_coords_t)(&A);
    cce_run_body_handlers(L);
  }
}

void
test_1_3 (cce_destination_t upper_L)
/* Make the struct, then destroy it with the "destroy()" method of "my_coords_t". */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    my_coords_t		A  = cclib_make(my_coords_t, rec)(L, 1.0, 2.0);

    cclib_vcall(print, A, stderr);
    cclib_vcall(destroy, A);
    cce_run_body_handlers(L);
  }
}

void
test_1_4 (cce_destination_t upper_L)
/* Make the  struct, then destroy  it with the  "destroy()" method of  the destructor
   trait. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    my_coords_t		A  = cclib_make(my_coords_t, rec)(L, 1.0, 2.0);
    my_destructor_T	AD = cclib_make(my_destructor_T, my_coords_t)(&A);

    cclib_vcall(print, A, stderr);
    cclib_vcall(destroy, AD);
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Test for the data structure as value.
 ** ----------------------------------------------------------------- */

void
test_2_1 (cce_destination_t upper_L)
/* Allocate  the struct  on the  heap,  then destroy  it with  the "delete()"  common
   function. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    my_complex_t const *	A =
      cclib_new(my_complex_t, rec)(L, cclib_make(my_real_part_t)(1.0), cclib_make(my_imag_part_t)(2.0));

    cclib_call(print, A, stderr);
    cclib_delete(my_complex_t)(A);
    cce_run_body_handlers(L);
  }
}

void
test_2_2 (cce_destination_t upper_L)
/* Allocate  the struct  on the  stack,  then destroy  it with  the "final()"  common
   function. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    my_complex_t	A[1];

    cclib_init(my_complex_t, rec)(A, cclib_make(my_real_part_t)(1.0), cclib_make(my_imag_part_t)(2.0));

    cclib_call(print, A, stderr);
    cclib_final(my_complex_t)(A);
    cce_run_body_handlers(L);
  }
}

void
test_2_3 (cce_destination_t upper_L)
/* Allocate the struct  on the heap, then  destroy it with the  "destroy()" method of
   "my_complex_t". */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    my_complex_t const *	A =
      cclib_new(my_complex_t, rec)(L, cclib_make(my_real_part_t)(1.0), cclib_make(my_imag_part_t)(2.0));

    cclib_call(print, A, stderr);
    cclib_call(destroy, A);
    cce_run_body_handlers(L);
  }
}

void
test_2_4 (cce_destination_t upper_L)
/* Allocate the struct on  the stack, then destroy it with  the "destroy()" method of
   "my_complex_t". */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    my_complex_t	A[1];

    cclib_init(my_complex_t, rec)(A, cclib_make(my_real_part_t)(1.0), cclib_make(my_imag_part_t)(2.0));

    cclib_call(print, A, stderr);
    cclib_call(destroy, A);
    cce_run_body_handlers(L);
  }
}

void
test_2_5 (cce_destination_t upper_L)
/* Allocate the struct  on the heap, then  destroy it with the  "destroy()" method of
   the destructor trait. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    my_complex_t const *	A  =
      cclib_new(my_complex_t, rec)(L, cclib_make(my_real_part_t)(1.0), cclib_make(my_imag_part_t)(2.0));
    my_destructor_T		AD = cclib_make(my_destructor_T, my_complex_t)(A);

    cclib_call(print, A, stderr);
    cclib_vcall(destroy, AD);
    cce_run_body_handlers(L);
  }
}

void
test_2_6 (cce_destination_t upper_L)
/* Allocate the struct on  the stack, then destroy it with  the "destroy()" method of
   the destructor trait. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    my_complex_t	A[1];
    my_destructor_T	AD;

    cclib_init(my_complex_t, rec)(A, cclib_make(my_real_part_t)(1.0), cclib_make(my_imag_part_t)(2.0));
    AD = cclib_make(my_destructor_T, my_complex_t)(A);

    cclib_call(print, A, stderr);
    cclib_vcall(destroy, AD);
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
    test_1_3(L);
    test_1_4(L);

    test_2_1(L);
    test_2_2(L);
    test_2_3(L);
    test_2_4(L);
    test_2_5(L);
    test_2_6(L);

    cce_run_body_handlers(L);
    exit(EXIT_SUCCESS);
  }
}

/* end of file */
