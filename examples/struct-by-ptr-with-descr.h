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

#ifndef STRUCT_BY_PTR_WITH_DESCR_H
#define STRUCT_BY_PTR_WITH_DESCR_H 1

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

MY_DEFINE_PARM(real_part)
MY_DEFINE_PARM(imag_part)
MY_DEFINE_PARM(magnitude)
MY_DEFINE_PARM(angle)

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
static inline my_real_part_t
cclib_make(my_real_part_t, pol) (my_magnitude_t magnitude, my_angle_t angle)
{
  return (my_real_part_t) { .val = magnitude.val * cos(angle.val) };
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
static inline my_imag_part_t
cclib_make(my_imag_part_t, pol) (my_magnitude_t magnitude, my_angle_t angle)
{
  return (my_imag_part_t) { .val = magnitude.val * sin(angle.val) };
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
static inline my_magnitude_t
cclib_make(my_magnitude_t, pol) (my_real_part_t real_part, my_imag_part_t imag_part)
{
  return (my_magnitude_t) { .val = hypot(real_part.val, imag_part.val) };
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
static inline my_angle_t
cclib_make(my_angle_t, pol) (my_real_part_t real_part, my_imag_part_t imag_part)
{
  return (my_angle_t) { .val = atan2(imag_part.val, real_part.val) };
}


/** --------------------------------------------------------------------
 ** Type definitions: data struct "my_complex_t".
 ** ----------------------------------------------------------------- */

CCLIB_DEFINE_STRUCT_WITH_DESCRIPTOR(my_complex_t);

typedef struct my_complex_t	my_complex_t;

struct my_complex_t {
  cclib_struct_descriptor(my_complex_t);
  my_real_part_t	re;
  my_imag_part_t	im;
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
cclib_decl void cclib_init(my_complex_t, rec) (my_complex_t * S, my_real_part_t re, my_imag_part_t im)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1);

/* Initialisation  function  that  initialises  an already  allocated  struct.   This
   constructor initialises the structure from polar coordinates. */
cclib_decl void cclib_init(my_complex_t, pol) (my_complex_t * S, my_magnitude_t magnitude, my_angle_t angle)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1);

/* ------------------------------------------------------------------ */

/* Constructor function  that allocates  the struct  on the  heap using  the standard
   memory allocator  implemented by  CCExceptions.  This constructor  initialises the
   structure from polar coordinates. */
cclib_decl my_complex_t const * cclib_new(my_complex_t, rec) (cce_destination_t L, my_real_part_t re, my_imag_part_t im)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL;

/* Constructor function  that allocates  the struct  on the  heap using  the standard
   memory allocator  implemented by  CCExceptions.  This constructor  initialises the
   structure from polar coordinates. */
cclib_decl my_complex_t const * cclib_new(my_complex_t, pol) (cce_destination_t L, my_magnitude_t magnitude, my_angle_t angle)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL;

/* ------------------------------------------------------------------ */

cclib_decl void cclib_final(my_complex_t) (my_complex_t const * S)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1);

cclib_decl void cclib_delete(my_complex_t) (my_complex_t const * S)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1);


/** --------------------------------------------------------------------
 ** Function prototypes: plain exception handlers.
 ** ----------------------------------------------------------------- */

typedef struct cclib_exception_handler_type(my_complex_t, clean)  cclib_exception_handler_type(my_complex_t, clean);
typedef struct cclib_exception_handler_type(my_complex_t, error)  cclib_exception_handler_type(my_complex_t, error);

struct cclib_exception_handler_type(my_complex_t, clean) {
  cce_clean_handler_t	handler;
};

struct cclib_exception_handler_type(my_complex_t, error) {
  cce_error_handler_t	handler;
};

/* Initialises a "clean" exception handler that calls "cclib_final(my_complex_t)()" as
   destructor function. */
cclib_decl void cclib_exception_handler_init_and_register(my_complex_t, clean, embedded)
  (cce_destination_t L, cclib_exception_handler_type(my_complex_t, clean) * H, my_complex_t const * self)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3);

/* Initialises an  "error" exception handler that  calls "cclib_final(my_complex_t)()"
   as destructor function. */
cclib_decl void cclib_exception_handler_init_and_register(my_complex_t, error, embedded)
  (cce_destination_t L, struct cclib_exception_handler_type(my_complex_t, error) * H, my_complex_t const * self)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3);

/* Initialises a  "clean" exception handler that  calls "cclib_delete(my_complex_t)()"
   as destructor function. */
cclib_decl void cclib_exception_handler_init_and_register(my_complex_t, clean, standalone)
  (cce_destination_t L, cclib_exception_handler_type(my_complex_t, clean) * H, my_complex_t const * self)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3);

/* Initialises an "error" exception  handler that calls "cclib_delete(my_complex_t)()"
   as destructor function. */
cclib_decl void cclib_exception_handler_init_and_register(my_complex_t, error, standalone)
  (cce_destination_t L, cclib_exception_handler_type(my_complex_t, error) * H, my_complex_t const * self)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3);


/** --------------------------------------------------------------------
 ** Guarded constructors.
 ** ----------------------------------------------------------------- */

cclib_decl void cclib_init(my_complex_t, rec, guarded, clean)
  (cce_destination_t L, cclib_exception_handler_type(my_complex_t, clean) * S_H, my_complex_t * S, my_real_part_t X, my_imag_part_t Y)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3);

cclib_decl void cclib_init(my_complex_t, rec, guarded, error)
  (cce_destination_t L, cclib_exception_handler_type(my_complex_t, error) * S_H, my_complex_t * S, my_real_part_t X, my_imag_part_t Y)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3);

/* ------------------------------------------------------------------ */

cclib_decl void cclib_init(my_complex_t, pol, guarded, clean)
  (cce_destination_t L, cclib_exception_handler_type(my_complex_t, clean) * S_H, my_complex_t * S, my_magnitude_t MAGNITUDE, my_angle_t ANGLE)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3);

cclib_decl void cclib_init(my_complex_t, pol, guarded, error)
  (cce_destination_t L, cclib_exception_handler_type(my_complex_t, error) * S_H, my_complex_t * S, my_magnitude_t MAGNITUDE, my_angle_t ANGLE)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3);

/* ------------------------------------------------------------------ */

cclib_decl my_complex_t const * cclib_new(my_complex_t, rec, guarded, clean)
  (cce_destination_t L, cclib_exception_handler_type(my_complex_t, clean) * S_H, my_real_part_t X, my_imag_part_t Y)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2);

cclib_decl my_complex_t const * cclib_new(my_complex_t, rec, guarded, error)
  (cce_destination_t L, cclib_exception_handler_type(my_complex_t, error) * S_H, my_real_part_t X, my_imag_part_t Y)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2);

/* ------------------------------------------------------------------ */

cclib_decl my_complex_t const * cclib_new(my_complex_t, pol, guarded, clean)
  (cce_destination_t L, cclib_exception_handler_type(my_complex_t, clean) * S_H, my_magnitude_t MAGNITUDE, my_angle_t ANGLE)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2);

cclib_decl my_complex_t const * cclib_new(my_complex_t, pol, guarded, error)
  (cce_destination_t L, cclib_exception_handler_type(my_complex_t, error) * S_H, my_magnitude_t MAGNITUDE, my_angle_t ANGLE)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2);


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* defined STRUCT_BY_PTR_WITH_DESCR_H */

/* end of file */
