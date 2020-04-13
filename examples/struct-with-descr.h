/*
  Part of: CCExceptions
  Contents: header file for sample struct with descriptor
  Date: Dec 27, 2018

  Abstract

	This header file defines the struct  "my_complex_t" as a "struct with descr".
	See the documentation for details.

  Copyright (C) 2018, 2019, 2020 Marco Maggi <mrc.mgg@gmail.com>

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

#ifndef STRUCT_WITH_DESCR_H
#define STRUCT_WITH_DESCR_H 1

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
 ** Type definitions: data struct "my_complex_t".
 ** ----------------------------------------------------------------- */

CCLIB_DEFINE_STRUCT_WITH_DESCRIPTOR(my_complex_t);

typedef struct my_complex_t	my_complex_t;

struct my_complex_t {
  cclib_struct_descriptor(my_complex_t);
  double	re;
  double	im;
};

/* A typedef for every method. */
typedef void cclib_method_type(my_complex_t, destroy) (my_complex_t const * self);
typedef void cclib_method_type(my_complex_t, print)   (my_complex_t const * self, FILE * stream);

/* The methods table declaration. */
struct cclib_methods_table_type(my_complex_t) {
  cclib_method_type(my_complex_t, destroy) *	destroy;
  cclib_method_type(my_complex_t, print) *	print;
};


/** --------------------------------------------------------------------
 ** Data struct "my_complex_t": well known functions API.
 ** ----------------------------------------------------------------- */

/* Initialisation  function  that  initialises  an already  allocated  struct.   This
   constructor initialises the structure from rectangular coordinates. */
cclib_decl void cclib_init(my_complex_t, rec) (my_complex_t * S, double re, double im)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1);

/* Initialisation  function  that  initialises  an already  allocated  struct.   This
   constructor initialises the structure from polar coordinates. */
cclib_decl void cclib_init(my_complex_t, pol) (my_complex_t * S, double RHO, double THETA)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1);

/* ------------------------------------------------------------------ */

/* Constructor function  that allocates  the struct  on the  heap using  the standard
   memory allocator  implemented by  CCExceptions.  This constructor  initialises the
   structure from polar coordinates. */
cclib_decl my_complex_t const * cclib_new(my_complex_t, rec) (cce_destination_t L, double re, double im)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL;

/* Constructor function  that allocates  the struct  on the  heap using  the standard
   memory allocator  implemented by  CCExceptions.  This constructor  initialises the
   structure from polar coordinates. */
cclib_decl my_complex_t const * cclib_new(my_complex_t, pol) (cce_destination_t L, double RHO, double THETA)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL;

/* ------------------------------------------------------------------ */

cclib_decl void cclib_final(my_complex_t) (my_complex_t const * S)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1);

cclib_decl void cclib_delete(my_complex_t) (my_complex_t const * S)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1);


/** --------------------------------------------------------------------
 ** Guarded constructors.
 ** ----------------------------------------------------------------- */

cclib_decl void cclib_init(my_complex_t, rec, guarded, clean)
  (my_complex_t * S, cce_destination_t L, cce_clean_handler_t * S_H, double re, double im)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2);

cclib_decl void cclib_init(my_complex_t, rec, guarded, error)
  (my_complex_t * S, cce_destination_t L, cce_error_handler_t * S_H, double re, double im)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2);

/* ------------------------------------------------------------------ */

cclib_decl void cclib_init(my_complex_t, pol, guarded, clean)
  (my_complex_t * S, cce_destination_t L, cce_clean_handler_t * S_H, double rho, double theta)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2);

cclib_decl void cclib_init(my_complex_t, pol, guarded, error)
  (my_complex_t * S, cce_destination_t L, cce_error_handler_t * S_H, double rho, double theta)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2);

/* ------------------------------------------------------------------ */

cclib_decl my_complex_t const * cclib_new(my_complex_t, rec, guarded, clean)
  (cce_destination_t L, cce_clean_handler_t *S_H, double re, double im)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2)
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL;

cclib_decl my_complex_t const * cclib_new(my_complex_t, rec, guarded, error)
  (cce_destination_t L, cce_error_handler_t *S_H, double re, double im)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2)
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL;

/* ------------------------------------------------------------------ */

cclib_decl my_complex_t const * cclib_new(my_complex_t, pol, guarded, clean)
  (cce_destination_t L, cce_clean_handler_t *S_H, double rho, double theta)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2)
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL;

cclib_decl my_complex_t const * cclib_new(my_complex_t, pol, guarded, error)
  (cce_destination_t L, cce_error_handler_t *S_H, double rho, double theta)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2)
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL;


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* defined STRUCT_WITH_DESCR_H */

/* end of file */
