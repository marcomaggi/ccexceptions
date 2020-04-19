/*
  Part of: CCExceptions
  Contents: adapter API for exceptional-condition objects
  Date: Apr 16, 2020

  Abstract

	This  header file  defines a  public API  adapting the  exceptional-condition
	objects API to the one defined by the "cclibraries.h" file.  All the features
	are exactly  the same; the  type name are  different; the function  names are
	different.

  Copyright (C) 2020 Marco Maggi <mrc.mgg@gmail.com>

  This is free software; you can redistribute  it and/or modify it under the terms of
  the GNU Lesser General Public License as published by the Free Software Foundation;
  either version 3.0 of the License, or (at your option) any later version.

  This library  is distributed in the  hope that it  will be useful, but  WITHOUT ANY
  WARRANTY; without  even the implied  warranty of  MERCHANTABILITY or FITNESS  FOR A
  PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License along with
  this library; if not, write to the Free Software Foundation, Inc., 59 Temple Place,
  Suite 330, Boston, MA 02111-1307 USA.

*/

#ifndef CCEXCEPTIONS_CCLIB_CONDITIONS_H
#define CCEXCEPTIONS_CCLIB_CONDITIONS_H 1


/** --------------------------------------------------------------------
 ** Exceptional condition objects: root exception.
 ** ----------------------------------------------------------------- */

typedef cce_descriptor_root_t	cclib_exceptional_condition_descriptor_type(cce_root);
typedef cce_condition_root_t	cclib_exceptional_condition_object_type(cce_root);

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline void
cclib_exceptional_condition_descriptor_set_parent_to(cce_root) (cce_descriptor_t * const D)
{
  cce_descriptor_set_parent_to(cce_descriptor_root_t)(D);
}

/* ------------------------------------------------------------------ */

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline void
cclib_init(cclib_exceptional_condition_object_type(cce_root)) (cclib_exceptional_condition_object_type(cce_root) * C)
{
  cce_condition_init_root(C);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline bool
cclib_is(cclib_exceptional_condition_object_type(cce_root)) (cce_condition_t const * C)
{
  return cce_condition_is_root(C);
}


/** --------------------------------------------------------------------
 ** Exceptional condition objects: unknown exception.
 ** ----------------------------------------------------------------- */

typedef cce_descriptor_unknown_t	cclib_exceptional_condition_descriptor_type(cce_unknown);
typedef cce_condition_unknown_t		cclib_exceptional_condition_object_type(cce_unknown);

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline void
cclib_exceptional_condition_descriptor_set_parent_to(cce_unknown) (cce_descriptor_t * const D)
{
  cce_descriptor_set_parent_to(cce_descriptor_unknown_t)(D);
}

/* ------------------------------------------------------------------ */

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline void
cclib_init(cclib_exceptional_condition_object_type(cce_unknown)) (cclib_exceptional_condition_object_type(cce_unknown) * C)
{
  cce_condition_init_unknown(C);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
static inline cce_condition_t const *
cclib_new(cclib_exceptional_condition_object_type(cce_unknown)) (void)
{
  return cce_condition_new_unknown();
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline bool
cclib_is(cclib_exceptional_condition_object_type(cce_unknown)) (cce_condition_t const * C)
{
  return cce_condition_is_unknown(C);
}


/** --------------------------------------------------------------------
 ** Exceptional condition objects: break exception.
 ** ----------------------------------------------------------------- */

typedef cce_descriptor_break_t		cclib_exceptional_condition_descriptor_type(cce_break);
typedef cce_condition_break_t		cclib_exceptional_condition_object_type(cce_break);

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline void
cclib_exceptional_condition_descriptor_set_parent_to(cce_break) (cce_descriptor_t * const D)
{
  cce_descriptor_set_parent_to(cce_descriptor_break_t)(D);
}

/* ------------------------------------------------------------------ */

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline void
cclib_init(cclib_exceptional_condition_object_type(cce_break)) (cclib_exceptional_condition_object_type(cce_break) * C)
{
  cce_condition_init_break(C);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
static inline cce_condition_t const *
cclib_new(cclib_exceptional_condition_object_type(cce_break)) (void)
{
  return cce_condition_new_break();
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline bool
cclib_is(cclib_exceptional_condition_object_type(cce_break)) (cce_condition_t const * C)
{
  return cce_condition_is_break(C);
}


/** --------------------------------------------------------------------
 ** Exceptional condition objects: generic error exception.
 ** ----------------------------------------------------------------- */

typedef cce_descriptor_error_t		cclib_exceptional_condition_descriptor_type(cce_error);
typedef cce_condition_error_t		cclib_exceptional_condition_object_type(cce_error);

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline void
cclib_exceptional_condition_descriptor_set_parent_to(cce_error) (cce_descriptor_t * const D)
{
  cce_descriptor_set_parent_to(cce_descriptor_error_t)(D);
}

/* ------------------------------------------------------------------ */

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline void
cclib_init(cclib_exceptional_condition_object_type(cce_error)) (cclib_exceptional_condition_object_type(cce_error) * C)
{
  cce_condition_init_error(C);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
static inline cce_condition_t const *
cclib_new(cclib_exceptional_condition_object_type(cce_error)) (void)
{
  return cce_condition_new_error();
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline bool
cclib_is(cclib_exceptional_condition_object_type(cce_error)) (cce_condition_t const * C)
{
  return cce_condition_is_error(C);
}


/** --------------------------------------------------------------------
 ** Exceptional condition objects: runtime error exception.
 ** ----------------------------------------------------------------- */

typedef cce_descriptor_runtime_error_t		cclib_exceptional_condition_descriptor_type(cce_runtime_error);
typedef cce_condition_runtime_error_t		cclib_exceptional_condition_object_type(cce_runtime_error);

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline void
cclib_exceptional_condition_descriptor_set_parent_to(cce_runtime_error) (cce_descriptor_t * const D)
{
  cce_descriptor_set_parent_to(cce_descriptor_runtime_error_t)(D);
}

/* ------------------------------------------------------------------ */

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline void
cclib_init(cclib_exceptional_condition_object_type(cce_runtime_error)) (cclib_exceptional_condition_object_type(cce_runtime_error) * C)
{
  cce_condition_init_runtime_error(C);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
static inline cce_condition_t const *
cclib_new(cclib_exceptional_condition_object_type(cce_runtime_error)) (void)
{
  return cce_condition_new_runtime_error();
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline bool
cclib_is(cclib_exceptional_condition_object_type(cce_runtime_error)) (cce_condition_t const * C)
{
  return cce_condition_is_runtime_error(C);
}


/** --------------------------------------------------------------------
 ** Exceptional condition objects: logic error exception.
 ** ----------------------------------------------------------------- */

typedef cce_descriptor_logic_error_t	cclib_exceptional_condition_descriptor_type(cce_logic_error);
typedef cce_condition_logic_error_t	cclib_exceptional_condition_object_type(cce_logic_error);

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline void
cclib_exceptional_condition_descriptor_set_parent_to(cce_logic_error) (cce_descriptor_t * const D)
{
  cce_descriptor_set_parent_to(cce_descriptor_logic_error_t)(D);
}

/* ------------------------------------------------------------------ */

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline void
cclib_init(cclib_exceptional_condition_object_type(cce_logic_error)) (cclib_exceptional_condition_object_type(cce_logic_error) * C)
{
  cce_condition_init_logic_error(C);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
static inline cce_condition_t const *
cclib_new(cclib_exceptional_condition_object_type(cce_logic_error)) (void)
{
  return cce_condition_new_logic_error();
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline bool
cclib_is(cclib_exceptional_condition_object_type(cce_logic_error)) (cce_condition_t const * C)
{
  return cce_condition_is_logic_error(C);
}


/** --------------------------------------------------------------------
 ** Exceptional condition objects: unreachable code exception.
 ** ----------------------------------------------------------------- */

typedef cce_descriptor_unreachable_t	cclib_exceptional_condition_descriptor_type(cce_unreachable);
typedef cce_condition_unreachable_t	cclib_exceptional_condition_object_type(cce_unreachable);

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline void
cclib_exceptional_condition_descriptor_set_parent_to(cce_unreachable) (cce_descriptor_t * const D)
{
  cce_descriptor_set_parent_to(cce_descriptor_unreachable_t)(D);
}

/* ------------------------------------------------------------------ */

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3)
static inline void
cclib_init(cclib_exceptional_condition_object_type(cce_unreachable))
  (cclib_exceptional_condition_object_type(cce_unreachable) * C,
   char const * const filename, char const * const funcname, int const linenum)
{
  cce_condition_init_unreachable(C, filename, funcname, linenum);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3)
static inline cce_condition_t const *
cclib_new(cclib_exceptional_condition_object_type(cce_unreachable))
  (cce_destination_t L, char const * const filename, char const * const funcname, int const linenum)
{
  return cce_condition_new_unreachable(L, filename, funcname, linenum);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline bool
cclib_is(cclib_exceptional_condition_object_type(cce_unreachable)) (cce_condition_t const * C)
{
  return cce_condition_is_unreachable(C);
}


/** --------------------------------------------------------------------
 ** Exceptional condition objects: unimplemented exception.
 ** ----------------------------------------------------------------- */

typedef cce_descriptor_unimplemented_t	cclib_exceptional_condition_descriptor_type(cce_unimplemented);
typedef cce_condition_unimplemented_t	cclib_exceptional_condition_object_type(cce_unimplemented);

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline void
cclib_exceptional_condition_descriptor_set_parent_to(cce_unimplemented) (cce_descriptor_t * const D)
{
  cce_descriptor_set_parent_to(cce_descriptor_unimplemented_t)(D);
}

/* ------------------------------------------------------------------ */

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline void
cclib_init(cclib_exceptional_condition_object_type(cce_unimplemented)) (cclib_exceptional_condition_object_type(cce_unimplemented) * C)
{
  cce_condition_init_unimplemented(C);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
static inline cce_condition_t const *
cclib_new(cclib_exceptional_condition_object_type(cce_unimplemented)) (void)
{
  return cce_condition_new_unimplemented();
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline bool
cclib_is(cclib_exceptional_condition_object_type(cce_unimplemented)) (cce_condition_t const * C)
{
  return cce_condition_is_unimplemented(C);
}


/** --------------------------------------------------------------------
 ** Exceptional condition objects: invalid function argument.
 ** ----------------------------------------------------------------- */

typedef cce_descriptor_invalid_argument_t	cclib_exceptional_condition_descriptor_type(cce_invalid_argument);
typedef cce_condition_invalid_argument_t	cclib_exceptional_condition_object_type(cce_invalid_argument);

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline void
cclib_exceptional_condition_descriptor_set_parent_to(cce_invalid_argument) (cce_descriptor_t * const D)
{
  cce_descriptor_set_parent_to(cce_descriptor_invalid_argument_t)(D);
}

/* ------------------------------------------------------------------ */

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2)
static inline void
cclib_init(cclib_exceptional_condition_object_type(cce_invalid_argument))
  (cclib_exceptional_condition_object_type(cce_invalid_argument) * C, char const * const func, unsigned const index)
{
  cce_condition_init_invalid_argument(C, func, index);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2)
static inline cce_condition_t const *
cclib_new(cclib_exceptional_condition_object_type(cce_invalid_argument))
  (cce_destination_t L, char const * const func, unsigned const index)
{
  return cce_condition_new_invalid_argument(L, func, index);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline bool
cclib_is(cclib_exceptional_condition_object_type(cce_invalid_argument)) (cce_condition_t const * C)
{
  return cce_condition_is_invalid_argument(C);
}


/** --------------------------------------------------------------------
 ** Exceptional condition objects: mathematical error exception.
 ** ----------------------------------------------------------------- */

typedef cce_descriptor_math_error_t	cclib_exceptional_condition_descriptor_type(cce_math_error);
typedef cce_condition_math_error_t	cclib_exceptional_condition_object_type(cce_math_error);

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline void
cclib_exceptional_condition_descriptor_set_parent_to(cce_math_error) (cce_descriptor_t * const D)
{
  cce_descriptor_set_parent_to(cce_descriptor_math_error_t)(D);
}

/* ------------------------------------------------------------------ */

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline void
cclib_init(cclib_exceptional_condition_object_type(cce_math_error)) (cclib_exceptional_condition_object_type(cce_math_error) * C)
{
  cce_condition_init_math_error(C);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
static inline cce_condition_t const *
cclib_new(cclib_exceptional_condition_object_type(cce_math_error)) (void)
{
  return cce_condition_new_math_error();
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline bool
cclib_is(cclib_exceptional_condition_object_type(cce_math_error)) (cce_condition_t const * C)
{
  return cce_condition_is_math_error(C);
}


/** --------------------------------------------------------------------
 ** Exceptional condition objects: mathematical not-a-number exception.
 ** ----------------------------------------------------------------- */

typedef cce_descriptor_math_nan_t	cclib_exceptional_condition_descriptor_type(cce_math_nan);
typedef cce_condition_math_nan_t	cclib_exceptional_condition_object_type(cce_math_nan);

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline void
cclib_exceptional_condition_descriptor_set_parent_to(cce_math_nan) (cce_descriptor_t * const D)
{
  cce_descriptor_set_parent_to(cce_descriptor_math_nan_t)(D);
}

/* ------------------------------------------------------------------ */

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline void
cclib_init(cclib_exceptional_condition_object_type(cce_math_nan)) (cclib_exceptional_condition_object_type(cce_math_nan) * C)
{
  cce_condition_init_math_nan(C);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
static inline cce_condition_t const *
cclib_new(cclib_exceptional_condition_object_type(cce_math_nan)) (void)
{
  return cce_condition_new_math_nan();
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline bool
cclib_is(cclib_exceptional_condition_object_type(cce_math_nan)) (cce_condition_t const * C)
{
  return cce_condition_is_math_nan(C);
}


/** --------------------------------------------------------------------
 ** Exceptional condition objects: mathematical infinity exception.
 ** ----------------------------------------------------------------- */

typedef cce_descriptor_math_infinity_t	cclib_exceptional_condition_descriptor_type(cce_math_infinity);
typedef cce_condition_math_infinity_t	cclib_exceptional_condition_object_type(cce_math_infinity);

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline void
cclib_exceptional_condition_descriptor_set_parent_to(cce_math_infinity) (cce_descriptor_t * const D)
{
  cce_descriptor_set_parent_to(cce_descriptor_math_infinity_t)(D);
}

/* ------------------------------------------------------------------ */

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline void
cclib_init(cclib_exceptional_condition_object_type(cce_math_infinity)) (cclib_exceptional_condition_object_type(cce_math_infinity) * C)
{
  cce_condition_init_math_infinity(C);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
static inline cce_condition_t const *
cclib_new(cclib_exceptional_condition_object_type(cce_math_infinity)) (void)
{
  return cce_condition_new_math_infinity();
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline bool
cclib_is(cclib_exceptional_condition_object_type(cce_math_infinity)) (cce_condition_t const * C)
{
  return cce_condition_is_math_infinity(C);
}


/** --------------------------------------------------------------------
 ** Exceptional condition objects: mathematical overflow exception.
 ** ----------------------------------------------------------------- */

typedef cce_descriptor_math_overflow_t	cclib_exceptional_condition_descriptor_type(cce_math_overflow);
typedef cce_condition_math_overflow_t	cclib_exceptional_condition_object_type(cce_math_overflow);

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline void
cclib_exceptional_condition_descriptor_set_parent_to(cce_math_overflow) (cce_descriptor_t * const D)
{
  cce_descriptor_set_parent_to(cce_descriptor_math_overflow_t)(D);
}

/* ------------------------------------------------------------------ */

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline void
cclib_init(cclib_exceptional_condition_object_type(cce_math_overflow)) (cclib_exceptional_condition_object_type(cce_math_overflow) * C)
{
  cce_condition_init_math_overflow(C);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
static inline cce_condition_t const *
cclib_new(cclib_exceptional_condition_object_type(cce_math_overflow)) (void)
{
  return cce_condition_new_math_overflow();
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline bool
cclib_is(cclib_exceptional_condition_object_type(cce_math_overflow)) (cce_condition_t const * C)
{
  return cce_condition_is_math_overflow(C);
}


/** --------------------------------------------------------------------
 ** Exceptional condition objects: mathematical underflow exception.
 ** ----------------------------------------------------------------- */

typedef cce_descriptor_math_underflow_t	cclib_exceptional_condition_descriptor_type(cce_math_underflow);
typedef cce_condition_math_underflow_t	cclib_exceptional_condition_object_type(cce_math_underflow);

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline void
cclib_exceptional_condition_descriptor_set_parent_to(cce_math_underflow) (cce_descriptor_t * const D)
{
  cce_descriptor_set_parent_to(cce_descriptor_math_underflow_t)(D);
}

/* ------------------------------------------------------------------ */

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline void
cclib_init(cclib_exceptional_condition_object_type(cce_math_underflow)) (cclib_exceptional_condition_object_type(cce_math_underflow) * C)
{
  cce_condition_init_math_underflow(C);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
static inline cce_condition_t const *
cclib_new(cclib_exceptional_condition_object_type(cce_math_underflow)) (void)
{
  return cce_condition_new_math_underflow();
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline bool
cclib_is(cclib_exceptional_condition_object_type(cce_math_underflow)) (cce_condition_t const * C)
{
  return cce_condition_is_math_underflow(C);
}


/** --------------------------------------------------------------------
 ** Exceptional condition objects: errno exception.
 ** ----------------------------------------------------------------- */

typedef cce_descriptor_errno_t		cclib_exceptional_condition_descriptor_type(cce_errno);
typedef cce_condition_errno_t		cclib_exceptional_condition_object_type(cce_errno);

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline void
cclib_exceptional_condition_descriptor_set_parent_to(cce_errno) (cce_descriptor_t * const D)
{
  cce_descriptor_set_parent_to(cce_descriptor_errno_t)(D);
}

/* ------------------------------------------------------------------ */

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline void
cclib_init(cclib_exceptional_condition_object_type(cce_errno)) (cclib_exceptional_condition_object_type(cce_errno) * C, int errnum)
{
  cce_condition_init_errno(C, errnum);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline void
cclib_init(cclib_exceptional_condition_object_type(cce_errno, clear)) (cclib_exceptional_condition_object_type(cce_errno) * C)
{
  cce_condition_init_errno_clear(C);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
static inline cce_condition_t const *
cclib_new(cclib_exceptional_condition_object_type(cce_errno)) (int errnum)
{
  return cce_condition_new_errno(errnum);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
static inline cce_condition_t const *
cclib_new(cclib_exceptional_condition_object_type(cce_errno), clear) (void)
{
  return cce_condition_new_errno_clear();
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline bool
cclib_is(cclib_exceptional_condition_object_type(cce_errno)) (cce_condition_t const * C)
{
  return cce_condition_is_errno(C);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline bool
cclib_is(cclib_exceptional_condition_object_type(cce_errno), with_code) (cce_condition_t const * C, int errnum)
{
  return cce_condition_is_errno_with_code(C, errnum);
}


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#endif /* defined CCEXCEPTIONS_CCLIB_CONDITIONS_H */

/* end of file */
