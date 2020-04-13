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
cclib_init(my_complex_t, rec) (my_complex_t * S, double re, double im)
{
  cclib_struct_descriptor_set_methods_table_pointer(S, &cclib_methods_table(my_complex_t, embedded));
  S->re		= re;
  S->im		= im;
}

void
cclib_init(my_complex_t, pol) (my_complex_t * S, double RHO, double THETA)
{
  cclib_struct_descriptor_set_methods_table_pointer(S, &cclib_methods_table(my_complex_t, embedded));
  S->re		= RHO * cos(THETA);
  S->im		= RHO * sin(THETA);
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
cclib_new(my_complex_t, rec) (cce_destination_t L, double re, double im)
{
  my_complex_t *	S = cclib_alloc(my_complex_t)(L);

  cclib_init(my_complex_t, rec)(S, re, im);
  cclib_struct_descriptor_set_methods_table_pointer(S, &cclib_methods_table(my_complex_t, standalone));
  return (my_complex_t const *) S;
}

my_complex_t const *
cclib_new(my_complex_t, pol) (cce_destination_t L, double RHO, double THETA)
{
  my_complex_t *	S = cclib_alloc(my_complex_t)(L);

  cclib_init(my_complex_t, pol)(S, RHO, THETA);
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
 ** Guarded constructors.
 ** ----------------------------------------------------------------- */

void
cclib_init(my_complex_t, rec, guarded, clean) (my_complex_t * S, cce_destination_t L, cce_clean_handler_t * S_H, double re, double im)
{
  cclib_init(my_complex_t, rec)(S, re, im);
  cce_init_and_register_handler(L, S_H, cce_default_clean_handler_function,
				cce_resource_pointer(S),
				cce_resource_destructor(cclib_method_pointer(S, destroy)));
}

void
cclib_init(my_complex_t, rec, guarded, error) (my_complex_t * S, cce_destination_t L, cce_error_handler_t * S_H, double re, double im)
{
  cclib_init(my_complex_t, rec)(S, re, im);
  cce_init_and_register_handler(L, S_H, cce_default_error_handler_function,
				cce_resource_pointer(S),
				cce_resource_destructor(cclib_method_pointer(S, destroy)));
}

/* ------------------------------------------------------------------ */

void
cclib_init(my_complex_t, pol, guarded, clean) (my_complex_t * S, cce_destination_t L, cce_clean_handler_t * S_H, double rho, double theta)
{
  cclib_init(my_complex_t, pol)(S, rho, theta);
  cce_init_and_register_handler(L, S_H, cce_default_clean_handler_function,
				cce_resource_pointer(S),
				cce_resource_destructor(cclib_method_pointer(S, destroy)));
}

void
cclib_init(my_complex_t, pol, guarded, error) (my_complex_t * S, cce_destination_t L, cce_error_handler_t * S_H, double rho, double theta)
{
  cclib_init(my_complex_t, pol)(S, rho, theta);
  cce_init_and_register_handler(L, S_H, cce_default_error_handler_function,
				cce_resource_pointer(S),
				cce_resource_destructor(cclib_method_pointer(S, destroy)));
}

/* ------------------------------------------------------------------ */

my_complex_t const *
cclib_new(my_complex_t, rec, guarded, clean) (cce_destination_t L, cce_clean_handler_t *S_H, double re, double im)
{
  my_complex_t const *	S = cclib_new(my_complex_t, rec)(L, re, im);

  cce_init_and_register_handler(L, S_H, cce_default_clean_handler_function,
				cce_resource_pointer(S),
				cce_resource_destructor(cclib_method_pointer(S, destroy)));
  return S;
}

my_complex_t const *
cclib_new(my_complex_t, rec, guarded, error) (cce_destination_t L, cce_error_handler_t *S_H, double re, double im)
{
  my_complex_t const *	S = cclib_new(my_complex_t, rec)(L, re, im);

  cce_init_and_register_handler(L, S_H, cce_default_error_handler_function,
				cce_resource_pointer(S),
				cce_resource_destructor(cclib_method_pointer(S, destroy)));
  return S;
}

/* ------------------------------------------------------------------ */

my_complex_t const *
cclib_new(my_complex_t, pol, guarded, clean) (cce_destination_t L, cce_clean_handler_t *S_H, double rho, double theta)
{
  my_complex_t const *	S = cclib_new(my_complex_t, pol)(L, rho, theta);

  cce_init_and_register_handler(L, S_H, cce_default_clean_handler_function,
				cce_resource_pointer(S),
				cce_resource_destructor(cclib_method_pointer(S, destroy)));
  return S;
}

my_complex_t const *
cclib_new(my_complex_t, pol, guarded, error) (cce_destination_t L, cce_error_handler_t *S_H, double rho, double theta)
{
  my_complex_t const *	S = cclib_new(my_complex_t, pol)(L, rho, theta);

  cce_init_and_register_handler(L, S_H, cce_default_error_handler_function,
				cce_resource_pointer(S),
				cce_resource_destructor(cclib_method_pointer(S, destroy)));
  return S;
}


/** --------------------------------------------------------------------
 ** Method implementations: destructor methods.
 ** ----------------------------------------------------------------- */

void
cclib_method(my_complex_t, destroy, embedded) (my_complex_t const * self)
{
  cclib_final(my_complex_t)(self);
}

void
cclib_method(my_complex_t, destroy, standalone) (my_complex_t const * self)
{
  cclib_delete(my_complex_t)(self);
}

void
cclib_method(my_complex_t, print) (my_complex_t const * self, FILE * stream)
{
  fprintf(stream, "my_complex_t: %s: re=%f, im=%f\n", __func__, self->re, self->im);
}


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

/* end of file */
