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


/** --------------------------------------------------------------------
 ** A data structure as value: my_coords_t.
 ** ----------------------------------------------------------------- */

typedef struct my_coords_t	my_coords_t;

struct my_coords_t {
  double * array;
};

my_coords_t
cclib_make(my_coords_t) (cce_destination_t L, double X, double Y)
/* This is the constructor for the data structure. */
{
  my_coords_t	self = {
    .array = cce_sys_malloc(L, sizeof(2 * sizeof(double)))
  };

  self.array[0] = X;
  self.array[1] = Y;
  return self;
}

void
cclib_unmake(my_coords_t) (my_coords_t self)
/* This is the destructor for the data structure. */
{
  fprintf(stderr, "%s: enter unmake\n", __func__);
  free(self.array);
  fprintf(stderr, "%s: unmade\n", __func__);
}

void
cclib_final(my_coords_t) (my_coords_t * selfp)
/* This is the destructor for the data structure. */
{
  fprintf(stderr, "%s: enter final\n", __func__);
  cclib_unmake(my_coords_t)(*selfp);
  fprintf(stderr, "%s: finalised\n", __func__);
}


/** --------------------------------------------------------------------
 ** The destructor trait as implemented by my_coords_t.
 ** ----------------------------------------------------------------- */

//CCLIB_DEFINE_TRAIT_IMPLEMENTATION(my_destructor_T, my_coords_t);

/* A prototype for every method in the destructor trait implementation. */
static cclib_method_type(my_destructor_T, destroy)
  cclib_method(my_destructor_T, destroy, my_coords_t);
static cclib_method_type(my_destructor_T, retrieve_cce_resource_destructor)
  cclib_method(my_destructor_T, retrieve_cce_resource_destructor, my_coords_t);

/* The table  of methods  for the  destructor trait as  implemented by  the structure
   "my_coords_t". */
static cclib_methods_table_type(my_destructor_T) const cclib_methods_table(my_destructor_T, my_coords_t) = {
  .destroy                          = cclib_method(my_destructor_T, destroy, my_coords_t),
  .retrieve_cce_resource_destructor = cclib_method(my_destructor_T, retrieve_cce_resource_destructor, my_coords_t)
};

my_destructor_T
cclib_make(my_destructor_T, my_coords_t) (my_coords_t const * self)
/* The constructor for my_destructor_T implemented by "my_coords_t". */
{
  return cclib_make(my_destructor_T)(cclib_resource_pointer(&self), &cclib_methods_table(my_destructor_T, my_coords_t));
}

void
cclib_method(my_destructor_T, destroy, my_coords_t) (my_destructor_T impl)
{
  fprintf(stderr, "%s: enter method destroy\n", __func__);
  {
    my_coords_t const	* self = cclib_trait_resource_pointer(impl);

    cclib_unmake(my_coords_t)(*self);
  }
  fprintf(stderr, "%s: method destroy done\n", __func__);
}

cce_resource_destructor_fun_t *
cclib_method(my_destructor_T, retrieve_cce_resource_destructor, my_coords_t) (my_destructor_T impl CCLIB_UNUSED)
{
  return cce_resource_destructor(cclib_final(my_coords_t));
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
/* Make the struct, then destroy it with the "unmake()" function. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    my_coords_t	A = cclib_make(my_coords_t)(L, 1.0, 2.0);

    fprintf(stderr, "%s: X=%f, Y=%f\n", __func__, A.array[0], A.array[1]);
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
    my_coords_t	A = cclib_make(my_coords_t)(L, 1.0, 2.0);

    fprintf(stderr, "%s: X=%f, Y=%f\n", __func__, A.array[0], A.array[1]);
    cclib_final(my_coords_t)(&A);
    cce_run_body_handlers(L);
  }
}

void
test_1_3 (cce_destination_t upper_L)
/* Make the  struct, then destroy  it with the  "destroy()" method of  the destructor
   trait. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    my_coords_t		A  = cclib_make(my_coords_t)(L, 1.0, 2.0);
    my_destructor_T	AD = cclib_make(my_destructor_T, my_coords_t)(&A);

    fprintf(stderr, "%s: X=%f, Y=%f\n", __func__, A.array[0], A.array[1]);
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
    cce_run_body_handlers(L);
    exit(EXIT_SUCCESS);
  }
}

/* end of file */