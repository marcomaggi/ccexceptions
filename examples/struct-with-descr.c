/*
  Part of: CCStructs
  Contents: body file for sample struct
  Date: Dec 27, 2018

  Abstract

	This  body file  defines the  API to  handle the  struct "my_complex_t"  as a
	"struct with descr".  See the documentation for details.

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
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "struct-with-descr.h"
#include <stdio.h>
#include <stdlib.h>


/** --------------------------------------------------------------------
 ** Data struct "my_complex_t": methods table.
 ** ----------------------------------------------------------------- */

/* A prototype for every method. */
static cclib_method_type(my_complex_t, destroy) cclib_method(my_complex_t, destroy, embedded);
static cclib_method_type(my_complex_t, destroy) cclib_method(my_complex_t, destroy, standalone);
static cclib_method_type(my_complex_t, print)	cclib_method(my_complex_t, print);

/* Table of methods  for data structures allocated  on the stack or  embedded into an
   enveloping structure. */
static cclib_methods_table_type(my_complex_t) const cclib_methods_table(my_complex_t, embedded) = {
  .destroy	= cclib_method(my_complex_t, destroy, embedded),
  .print	= cclib_method(my_complex_t, print)
};

/* Table of methods for data structures allocated on the heap. */
static cclib_methods_table_type(my_complex_t) const cclib_methods_table(my_complex_t, standalone) = {
  .destroy	= cclib_method(my_complex_t, destroy, standalone),
  .print	= cclib_method(my_complex_t, print)
};


/** --------------------------------------------------------------------
 ** Data struct "my_complex_t": well known API functions.
 ** ----------------------------------------------------------------- */

void
cclib_init(my_complex_t, rec) (my_complex_t * S, my_real_part_t re, my_imag_part_t im)
{
  cclib_struct_descriptor_set_methods_table_pointer(S, &cclib_methods_table(my_complex_t, embedded));
  S->re		= re;
  S->im		= im;
}

void
cclib_init(my_complex_t, pol) (my_complex_t * S, my_magnitude_t rho, my_angle_t theta)
{
  cclib_struct_descriptor_set_methods_table_pointer(S, &cclib_methods_table(my_complex_t, embedded));
  S->re		= cclib_make(my_real_part_t, pol)(rho, theta);
  S->im		= cclib_make(my_imag_part_t, pol)(rho, theta);
}

/* ------------------------------------------------------------------ */

void
cclib_final(my_complex_t) (my_complex_t const * S CCLIB_UNUSED)
{
  if (1) { fprintf(stderr, "%-35s: finalised\n", __func__); }
}

/* ------------------------------------------------------------------ */

static my_complex_t *
cclib_alloc(my_complex_t) (cce_destination_t L)
{
  return (my_complex_t *)cce_sys_malloc(L, sizeof(my_complex_t));
}

/* ------------------------------------------------------------------ */

static void
cclib_release(my_complex_t) (my_complex_t const * S)
{
  if (1) { fprintf(stderr, "%-35s: enter release function\n", __func__); }
  free((void *)S);
  if (1) { fprintf(stderr, "%-35s: released\n", __func__); }
}

/* ------------------------------------------------------------------ */

my_complex_t const *
cclib_new(my_complex_t, rec) (cce_destination_t L, my_real_part_t re, my_imag_part_t im)
{
  my_complex_t *	S = cclib_alloc(my_complex_t)(L);

  cclib_init(my_complex_t, rec)(S, re, im);
  cclib_struct_descriptor_set_methods_table_pointer(S, &cclib_methods_table(my_complex_t, standalone));
  return (my_complex_t const *) S;
}

my_complex_t const *
cclib_new(my_complex_t, pol) (cce_destination_t L, my_magnitude_t rho, my_angle_t theta)
{
  my_complex_t *	S = cclib_alloc(my_complex_t)(L);

  cclib_init(my_complex_t, pol)(S, rho, theta);
  cclib_struct_descriptor_set_methods_table_pointer(S, &cclib_methods_table(my_complex_t, standalone));
  return (my_complex_t const *) S;
}

/* ------------------------------------------------------------------ */

void
cclib_delete(my_complex_t) (my_complex_t const * S)
{
  if (1) { fprintf(stderr, "%-35s: enter delete destructor\n", __func__); }
  cclib_final(my_complex_t)(S);
  cclib_release(my_complex_t)(S);
  if (1) { fprintf(stderr, "%-35s: deleted\n", __func__); }
}


/** --------------------------------------------------------------------
 ** Plain exception handlers.
 ** ----------------------------------------------------------------- */

static void
cclib_exception_handler_function(my_complex_t, clean, embedded) (cce_condition_t const * C CCLIB_UNUSED, cce_clean_handler_t const * const H)
/* Destructor handler for embedded instances.  Release all the asynchronous resources
   associated to the struct instance; does not touch the struct itself. */
{
  CCLIB_PC(my_complex_t, self, cce_handler_resource_pointer(H));

  cclib_final(my_complex_t)(self);
  if (1) { fprintf(stderr, "%-35s: finalised by plain handler\n", __func__); }
}

static void
cclib_exception_handler_function(my_complex_t, error, embedded) (cce_condition_t const * C CCLIB_UNUSED, cce_error_handler_t const * const H)
/* Destructor handler for embedded instances.  Release all the asynchronous resources
   associated to the struct instance; does not touch the struct itself. */
{
  CCLIB_PC(my_complex_t, self, cce_handler_resource_pointer(H));

  cclib_final(my_complex_t)(self);
  if (1) { fprintf(stderr, "%-35s: finalised by plain handler\n", __func__); }
}

void
cclib_exception_handler_init_and_register(my_complex_t, clean, embedded)
  (cce_destination_t L, cclib_exception_handler_type(my_complex_t, clean) * H, my_complex_t const * self)
{
  cce_init_and_register_handler(L, &(H->handler),
				cclib_exception_handler_function(my_complex_t, clean, embedded),
				cce_resource_pointer(self));
}

void
cclib_exception_handler_init_and_register(my_complex_t, error, embedded)
  (cce_destination_t L, struct cclib_exception_handler_type(my_complex_t, error) * H, my_complex_t const * self)
{
  cce_init_and_register_handler(L, &(H->handler),
				cclib_exception_handler_function(my_complex_t, error, embedded),
				cce_resource_pointer(self));
}

/* ------------------------------------------------------------------ */

static void
cclib_exception_handler_function(my_complex_t, clean, standalone) (cce_condition_t const * C CCLIB_UNUSED, cce_clean_handler_t const * const H)
/* Destructor  handler  for  standalone  instances.   Release  all  the  asynchronous
   aresources associated  to the struct  instance; release the memory  block allocated
   for  the  struct instance  using  the  standard  memory allocator  implemented  by
   CCMemory.

   To be used to destroy instances dynamically allocated on the heap. */
{
  CCLIB_PC(my_complex_t, self, cce_handler_resource_pointer(H));

  cclib_delete(my_complex_t)(self);
  if (1) { fprintf(stderr, "%-35s: deleted by plain handler\n", __func__); }
}

static void
cclib_exception_handler_function(my_complex_t, error, standalone) (cce_condition_t const * C CCLIB_UNUSED, cce_error_handler_t const * const H)
/* Destructor  handler  for  standalone  instances.   Release  all  the  asynchronous
   aresources associated  to the struct  instance; release the memory  block allocated
   for  the  struct instance  using  the  standard  memory allocator  implemented  by
   CCMemory.

   To be used to destroy instances dynamically allocated on the heap. */
{
  CCLIB_PC(my_complex_t, self, cce_handler_resource_pointer(H));

  cclib_delete(my_complex_t)(self);
  if (1) { fprintf(stderr, "%-35s: deleted by plain handler\n", __func__); }
}

void
cclib_exception_handler_init_and_register(my_complex_t, clean, standalone)
  (cce_destination_t L, cclib_exception_handler_type(my_complex_t, clean) * H, my_complex_t const * self)
{
  cce_init_and_register_handler(L, &(H->handler),
				cclib_exception_handler_function(my_complex_t, clean, standalone),
				cce_resource_pointer(self));
}

void
cclib_exception_handler_init_and_register(my_complex_t, error, standalone)
  (cce_destination_t L, cclib_exception_handler_type(my_complex_t, error) * H, my_complex_t const * self)
{
  cce_init_and_register_handler(L, &(H->handler),
				cclib_exception_handler_function(my_complex_t, error, standalone),
				cce_resource_pointer(self));
}


/** --------------------------------------------------------------------
 ** Guarded constructors.
 ** ----------------------------------------------------------------- */

void
cclib_init(my_complex_t, rec, guarded, clean)
  (cce_destination_t L, cclib_exception_handler_type(my_complex_t, clean) * S_H, my_complex_t * S, my_real_part_t X, my_imag_part_t Y)
{
  cclib_init(my_complex_t, rec)(S, X, Y);
  cclib_exception_handler_init_and_register(my_complex_t, clean, embedded)(L, S_H, S);
}

void
cclib_init(my_complex_t, rec, guarded, error)
  (cce_destination_t L, cclib_exception_handler_type(my_complex_t, error) * S_H, my_complex_t * S, my_real_part_t X, my_imag_part_t Y)
{
  cclib_init(my_complex_t, rec)(S, X, Y);
  cclib_exception_handler_init_and_register(my_complex_t, error, embedded)(L, S_H, S);
}

/* ------------------------------------------------------------------ */

void
cclib_init(my_complex_t, pol, guarded, clean)
  (cce_destination_t L, cclib_exception_handler_type(my_complex_t, clean) * S_H, my_complex_t * S, my_magnitude_t MAGNITUDE, my_angle_t ANGLE)
{
  cclib_init(my_complex_t, pol)(S, MAGNITUDE, ANGLE);
  cclib_exception_handler_init_and_register(my_complex_t, clean, embedded)(L, S_H, S);
}

void
cclib_init(my_complex_t, pol, guarded, error)
  (cce_destination_t L, cclib_exception_handler_type(my_complex_t, error) * S_H, my_complex_t * S, my_magnitude_t MAGNITUDE, my_angle_t ANGLE)
{
  cclib_init(my_complex_t, pol)(S, MAGNITUDE, ANGLE);
  cclib_exception_handler_init_and_register(my_complex_t, error, embedded)(L, S_H, S);
}

/* ------------------------------------------------------------------ */

my_complex_t const *
cclib_new(my_complex_t, rec, guarded, clean)
  (cce_destination_t L, cclib_exception_handler_type(my_complex_t, clean) * S_H, my_real_part_t X, my_imag_part_t Y)
{
  my_complex_t const *	S = cclib_new(my_complex_t, rec)(L, X, Y);

  cclib_exception_handler_init_and_register(my_complex_t, clean, standalone)(L, S_H, S);
  return S;
}

my_complex_t const *
cclib_new(my_complex_t, rec, guarded, error)
  (cce_destination_t L, cclib_exception_handler_type(my_complex_t, error) * S_H, my_real_part_t X, my_imag_part_t Y)
{
  my_complex_t const *	S = cclib_new(my_complex_t, rec)(L, X, Y);

  cclib_exception_handler_init_and_register(my_complex_t, error, standalone)(L, S_H, S);
  return S;
}

/* ------------------------------------------------------------------ */

my_complex_t const *
cclib_new(my_complex_t, pol, guarded, clean)
  (cce_destination_t L, cclib_exception_handler_type(my_complex_t, clean) * S_H, my_magnitude_t MAGNITUDE, my_angle_t ANGLE)
{
  my_complex_t const *	S = cclib_new(my_complex_t, pol)(L, MAGNITUDE, ANGLE);

  cclib_exception_handler_init_and_register(my_complex_t, clean, standalone)(L, S_H, S);
  return S;
}

my_complex_t const *
cclib_new(my_complex_t, pol, guarded, error)
  (cce_destination_t L, cclib_exception_handler_type(my_complex_t, error) * S_H, my_magnitude_t MAGNITUDE, my_angle_t ANGLE)
{
  my_complex_t const *	S = cclib_new(my_complex_t, pol)(L, MAGNITUDE, ANGLE);

  cclib_exception_handler_init_and_register(my_complex_t, error, standalone)(L, S_H, S);
  return S;
}


/** --------------------------------------------------------------------
 ** Method implementations: destructor methods.
 ** ----------------------------------------------------------------- */

void
cclib_method(my_complex_t, destroy, embedded) (my_complex_t const * self)
{
  if (1) { fprintf(stderr, "%-35s: enter method destroy\n", __func__); }
  cclib_final(my_complex_t)(self);
  if (1) { fprintf(stderr, "%-35s: method destroy done\n", __func__); }
}

void
cclib_method(my_complex_t, destroy, standalone) (my_complex_t const * self)
{
  if (1) { fprintf(stderr, "%-35s: enter method destroy\n", __func__); }
  cclib_delete(my_complex_t)(self);
  if (1) { fprintf(stderr, "%-35s: method destroy done\n", __func__); }
}

void
cclib_method(my_complex_t, print) (my_complex_t const * self, FILE * stream)
{
  fprintf(stream, "my_complex_t: %s: re=%f, im=%f\n", __func__, self->re.val, self->im.val);
}


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

/* end of file */
