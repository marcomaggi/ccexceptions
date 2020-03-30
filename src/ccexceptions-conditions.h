/*
  Part of: CCExceptions
  Contents: public header file, exceptional-condition objects
  Date: Apr 19, 2019

  Abstract

	This is a  subordinate header file: it is sourced  by "ccexceptions.h" and it
	must not be included by itself.

  Copyright (C) 2016-2020 Marco Maggi <mrc.mgg@gmail.com>

  This program is free  software: you can redistribute it and/or  modify it under the
  terms of the  GNU Lesser General Public  License as published by  the Free Software
  Foundation, either version 3 of the License, or (at your option) any later version.

  This program  is distributed in the  hope that it  will be useful, but  WITHOUT ANY
  WARRANTY; without  even the implied  warranty of  MERCHANTABILITY or FITNESS  FOR A
  PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License along with
  this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CCEXCEPTIONS_CONDITIONS_H
#define CCEXCEPTIONS_CONDITIONS_H	1


/** --------------------------------------------------------------------
 ** Exceptional condition descriptors and basic conditions API.
 ** ----------------------------------------------------------------- */

typedef void cce_condition_delete_fun_t (cce_condition_t * C)
  __attribute__((__nonnull__(1)));

typedef void cce_condition_final_fun_t (cce_condition_t * C)
  __attribute__((__nonnull__(1)));

typedef char const * cce_condition_static_message_fun_t	(cce_condition_t const * C)
  __attribute__((__nonnull__(1)));

struct cce_descriptor_t {
  cce_descriptor_t const *		parent;
  cce_condition_delete_fun_t *		delete;
  cce_condition_final_fun_t *		final;
  cce_condition_static_message_fun_t *	static_message;
};

struct cce_condition_t {
  cce_descriptor_t const *		descriptor;
};

/* ------------------------------------------------------------------ */

cclib_decl void cce_condition_init (cce_condition_t * C, cce_descriptor_t const * D)
  __attribute__((__leaf__,__nonnull__(1,2)));

cclib_decl void cce_condition_final (cce_condition_t * C)
  __attribute__((__leaf__,__nonnull__(1)));

cclib_decl void cce_condition_delete (cce_condition_t * C)
  __attribute__((__leaf__,__nonnull__(1)));

cclib_decl bool cce_condition_is (cce_condition_t const * C, cce_descriptor_t const * D)
  __attribute__((__leaf__,__nonnull__(1,2)));

cclib_decl char const * cce_condition_static_message (cce_condition_t const * C)
  __attribute__((__leaf__,__nonnull__(1)));

/* ------------------------------------------------------------------ */

cclib_decl bool cce_descriptor_child_and_ancestor (cce_descriptor_t const * child, cce_descriptor_t const * ancestor)
  __attribute__((__leaf__,__nonnull__(1,2)));

#define cce_descriptor_set_parent_to(TYPE)	cce_descriptor_set_parent_to ## TYPE

#define cce_descriptor_pointer(EXCEPTIONAL_CONDITION_DESCRIPTOR_VARIABLE)	\
  &((EXCEPTIONAL_CONDITION_DESCRIPTOR_VARIABLE).descriptor)


/** --------------------------------------------------------------------
 ** Exceptional condition objects: root exception.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_root_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_root_t {
  cce_condition_t	condition;
};

cclib_decl void cce_descriptor_set_parent_to(cce_descriptor_root_t) (cce_descriptor_t * const D)
  __attribute__((__leaf__,__nonnull__(1)));

/* ------------------------------------------------------------------ */

cclib_decl void cce_condition_init_root (cce_condition_root_t * C)
  __attribute__((__leaf__,__nonnull__(1)));

cclib_decl bool cce_condition_is_root (cce_condition_t const * C)
  __attribute__((__leaf__,__pure__,__nonnull__(1)));


/** --------------------------------------------------------------------
 ** Exceptional condition objects: unknown exception.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_unknown_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_unknown_t {
  cce_condition_root_t	root;
};

cclib_decl void cce_descriptor_set_parent_to(cce_descriptor_unknown_t) (cce_descriptor_t * const D)
  __attribute__((__leaf__,__nonnull__(1)));

/* ------------------------------------------------------------------ */

cclib_decl void cce_condition_init_unknown (cce_condition_unknown_t * C)
  __attribute__((__leaf__,__nonnull__(1)));

cclib_decl cce_condition_t const * cce_condition_new_unknown (void)
  __attribute__((__leaf__,__const__,__returns_nonnull__));

cclib_decl bool cce_condition_is_unknown (cce_condition_t const * C)
  __attribute__((__leaf__,__pure__,__nonnull__(1)));


/** --------------------------------------------------------------------
 ** Exceptional condition objects: break exception.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_break_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_break_t {
  cce_condition_root_t	root;
};

cclib_decl void cce_descriptor_set_parent_to(cce_descriptor_break_t) (cce_descriptor_t * const D)
  __attribute__((__leaf__,__nonnull__(1)));

/* ------------------------------------------------------------------ */

cclib_decl void cce_condition_init_break (cce_condition_break_t * C)
  __attribute__((__leaf__,__nonnull__(1)));

cclib_decl cce_condition_t const * cce_condition_new_break (void)
  __attribute__((__leaf__,__const__,__returns_nonnull__));

cclib_decl bool cce_condition_is_break (cce_condition_t const * C)
  __attribute__((__leaf__,__pure__,__nonnull__(1)));


/** --------------------------------------------------------------------
 ** Exceptional condition objects: generic error exception.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_error_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_error_t {
  cce_condition_root_t	root;
};

cclib_decl void cce_descriptor_set_parent_to(cce_descriptor_error_t) (cce_descriptor_t * const D)
  __attribute__((__leaf__,__nonnull__(1)));

/* ------------------------------------------------------------------ */

cclib_decl void cce_condition_init_error (cce_condition_error_t * C)
  __attribute__((__leaf__,__nonnull__(1)));

cclib_decl cce_condition_t const * cce_condition_new_error (void)
  __attribute__((__leaf__,__const__,__returns_nonnull__));

cclib_decl bool cce_condition_is_error (cce_condition_t const * C)
  __attribute__((__leaf__,__pure__,__nonnull__(1)));


/** --------------------------------------------------------------------
 ** Exceptional condition objects: runtime error exception.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_runtime_error_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_runtime_error_t {
  cce_condition_error_t	error;
};

cclib_decl void cce_descriptor_set_parent_to(cce_descriptor_runtime_error_t) (cce_descriptor_t * const D)
  __attribute__((__leaf__,__nonnull__(1)));

/* ------------------------------------------------------------------ */

cclib_decl void cce_condition_init_runtime_error (cce_condition_runtime_error_t * C)
  __attribute__((__leaf__,__nonnull__(1)));

cclib_decl cce_condition_t const * cce_condition_new_runtime_error (void)
  __attribute__((__leaf__,__const__,__returns_nonnull__));

cclib_decl bool cce_condition_is_runtime_error (cce_condition_t const * C)
  __attribute__((__leaf__,__pure__,__nonnull__(1)));


/** --------------------------------------------------------------------
 ** Exceptional condition objects: logic error exception.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_logic_error_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_logic_error_t {
  cce_condition_error_t	error;
};

cclib_decl void cce_descriptor_set_parent_to(cce_descriptor_logic_error_t) (cce_descriptor_t * const D)
  __attribute__((__leaf__,__nonnull__(1)));

/* ------------------------------------------------------------------ */

cclib_decl void cce_condition_init_logic_error (cce_condition_logic_error_t * C)
  __attribute__((__leaf__,__nonnull__(1)));

cclib_decl cce_condition_t const * cce_condition_new_logic_error (void)
  __attribute__((__leaf__,__const__,__returns_nonnull__));

cclib_decl bool cce_condition_is_logic_error (cce_condition_t const * C)
  __attribute__((__leaf__,__pure__,__nonnull__(1)));


/** --------------------------------------------------------------------
 ** Exceptional condition objects: unreachable code exception.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_unreachable_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_unreachable_t {
  cce_condition_logic_error_t	logic_error;
  char const *			filename;
  char const *			funcname;
  int				linenum;
};

cclib_decl void cce_descriptor_set_parent_to(cce_descriptor_unreachable_t) (cce_descriptor_t * const D)
  __attribute__((__leaf__,__nonnull__(1)));

/* ------------------------------------------------------------------ */

cclib_decl void cce_condition_init_unreachable (cce_condition_unreachable_t * C,
					      char const * const filename,
					      char const * const funcname,
					      int const linenum)
  __attribute__((__leaf__,__nonnull__(1,2,3)));

cclib_decl cce_condition_t const * cce_condition_new_unreachable (cce_destination_t L,
								char const * const filename,
								char const * const funcname,
								int const linenum)
  __attribute__((__leaf__,__nonnull__(1,2,3),__returns_nonnull__));

#if (defined CCEXCEPTIONS_EXCLUDE_UNREACHABLE)
#  define cce_raise_unreachable(L)		/* empty */
#else
#  define cce_raise_unreachable(L)		\
     cce_raise((L), cce_condition_new_unreachable((L), __FILE__, __func__, __LINE__))
#endif

cclib_decl bool cce_condition_is_unreachable (cce_condition_t const * C)
  __attribute__((__leaf__,__pure__,__nonnull__(1)));


/** --------------------------------------------------------------------
 ** Exceptional condition objects: unimplemented exception.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_unimplemented_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_unimplemented_t {
  cce_condition_logic_error_t	logic_error;
};

cclib_decl void cce_descriptor_set_parent_to(cce_descriptor_unimplemented_t) (cce_descriptor_t * const D)
  __attribute__((__leaf__,__nonnull__(1)));

/* ------------------------------------------------------------------ */

cclib_decl void cce_condition_init_unimplemented (cce_condition_unimplemented_t * C)
  __attribute__((__leaf__,__nonnull__(1)));

cclib_decl cce_condition_t const * cce_condition_new_unimplemented (void)
  __attribute__((__leaf__,__const__,__returns_nonnull__));

cclib_decl bool cce_condition_is_unimplemented (cce_condition_t const * C)
  __attribute__((__leaf__,__pure__,__nonnull__(1)));


/** --------------------------------------------------------------------
 ** Exceptional condition objects: invalid function argument.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_invalid_argument_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_invalid_argument_t {
  cce_condition_logic_error_t	logic_error;
  /* Pointer to  a statically  allocated ASCIIZ string  representing the
     function name; usually generated with "__func__". */
  char const *		funcname;
  /* One-based index of the invalid argument. */
  unsigned		index;
};

cclib_decl void cce_descriptor_set_parent_to(cce_descriptor_invalid_argument_t) (cce_descriptor_t * const D)
  __attribute__((__leaf__,__nonnull__(1)));

/* ------------------------------------------------------------------ */

cclib_decl void cce_condition_init_invalid_argument (cce_condition_invalid_argument_t * C, char const * func, unsigned index);

cclib_decl cce_condition_t const * cce_condition_new_invalid_argument (cce_destination_t L, char const * func, unsigned index)
  __attribute__((__leaf__,__nonnull__(1,2),__returns_nonnull__));

cclib_decl bool cce_condition_is_invalid_argument (cce_condition_t const * C)
  __attribute__((__leaf__,__pure__,__nonnull__(1)));

#define cce_check_argument(L,EXPR,ARGNUM) \
  if (! (EXPR)) { cce_raise((L), cce_condition_new_invalid_argument((L), __func__, (ARGNUM))); }


/** --------------------------------------------------------------------
 ** Exceptional condition objects: mathematical error exception.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_math_error_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_math_error_t {
  cce_condition_runtime_error_t	runtime_error;
};

cclib_decl void cce_descriptor_set_parent_to(cce_descriptor_math_error_t) (cce_descriptor_t * const D)
  __attribute__((__leaf__,__nonnull__(1)));

/* ------------------------------------------------------------------ */

cclib_decl void cce_condition_init_math_error (cce_condition_math_error_t * C)
  __attribute__((__leaf__,__nonnull__(1)));

cclib_decl cce_condition_t const * cce_condition_new_math_error (void)
  __attribute__((__leaf__,__const__,__returns_nonnull__));

cclib_decl bool cce_condition_is_math_error (cce_condition_t const * C)
  __attribute__((__leaf__,__pure__,__nonnull__(1)));


/** --------------------------------------------------------------------
 ** Exceptional condition objects: mathematical not-a-number exception.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_math_nan_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_math_nan_t {
  cce_condition_math_error_t	math_error;
};

cclib_decl void cce_descriptor_set_parent_to(cce_descriptor_math_nan_t) (cce_descriptor_t * const D)
  __attribute__((__leaf__,__nonnull__(1)));

/* ------------------------------------------------------------------ */

cclib_decl void cce_condition_init_math_nan (cce_condition_math_nan_t * C)
  __attribute__((__leaf__,__nonnull__(1)));

cclib_decl cce_condition_t const * cce_condition_new_math_nan (void)
  __attribute__((__leaf__,__const__,__returns_nonnull__));

cclib_decl bool cce_condition_is_math_nan (cce_condition_t const * C)
  __attribute__((__leaf__,__pure__,__nonnull__(1)));


/** --------------------------------------------------------------------
 ** Exceptional condition objects: mathematical infinity exception.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_math_infinity_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_math_infinity_t {
  cce_condition_math_error_t	math_error;
};

cclib_decl void cce_descriptor_set_parent_to(cce_descriptor_math_infinity_t) (cce_descriptor_t * const D)
  __attribute__((__leaf__,__nonnull__(1)));

/* ------------------------------------------------------------------ */

cclib_decl void cce_condition_init_math_infinity (cce_condition_math_infinity_t * C)
  __attribute__((__leaf__,__nonnull__(1)));

cclib_decl cce_condition_t const * cce_condition_new_math_infinity (void)
  __attribute__((__leaf__,__const__,__returns_nonnull__));

cclib_decl bool cce_condition_is_math_infinity (cce_condition_t const * C)
  __attribute__((__leaf__,__pure__,__nonnull__(1)));


/** --------------------------------------------------------------------
 ** Exceptional condition objects: mathematical overflow exception.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_math_overflow_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_math_overflow_t {
  cce_condition_math_error_t	math_error;
};

cclib_decl void cce_descriptor_set_parent_to(cce_descriptor_math_overflow_t) (cce_descriptor_t * const D)
  __attribute__((__leaf__,__nonnull__(1)));

/* ------------------------------------------------------------------ */

cclib_decl void cce_condition_init_math_overflow (cce_condition_math_overflow_t * C)
  __attribute__((__leaf__,__nonnull__(1)));

cclib_decl cce_condition_t const * cce_condition_new_math_overflow (void)
  __attribute__((__leaf__,__const__,__returns_nonnull__));

cclib_decl bool cce_condition_is_math_overflow (cce_condition_t const * C)
  __attribute__((__leaf__,__pure__,__nonnull__(1)));


/** --------------------------------------------------------------------
 ** Exceptional condition objects: mathematical underflow exception.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_math_underflow_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_math_underflow_t {
  cce_condition_math_error_t	math_error;
};

cclib_decl void cce_descriptor_set_parent_to(cce_descriptor_math_underflow_t) (cce_descriptor_t * const D)
  __attribute__((__leaf__,__nonnull__(1)));

/* ------------------------------------------------------------------ */

cclib_decl void cce_condition_init_math_underflow (cce_condition_math_underflow_t * C)
  __attribute__((__leaf__,__nonnull__(1)));

cclib_decl cce_condition_t const * cce_condition_new_math_underflow (void)
  __attribute__((__leaf__,__const__,__returns_nonnull__));

cclib_decl bool cce_condition_is_math_underflow (cce_condition_t const * C)
  __attribute__((__leaf__,__pure__,__nonnull__(1)));


/** --------------------------------------------------------------------
 ** Exceptional condition objects: errno exception.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_errno_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_errno_t {
  cce_condition_runtime_error_t	runtime_error;
  int			errnum;
  char const *		message;
};

cclib_decl void cce_descriptor_set_parent_to(cce_descriptor_errno_t) (cce_descriptor_t * const D)
  __attribute__((__leaf__,__nonnull__(1)));

/* ------------------------------------------------------------------ */

cclib_decl cce_condition_t const * cce_condition_new_errno (int code)
  __attribute__((__leaf__,__returns_nonnull__));

cclib_decl cce_condition_t const * cce_condition_new_errno_clear (void)
  __attribute__((__leaf__,__returns_nonnull__));

cclib_decl bool cce_condition_is_errno (cce_condition_t const * C)
  __attribute__((__leaf__,__pure__,__nonnull__(1)));

cclib_decl bool cce_condition_is_errno_with_code (cce_condition_t const * C, int errnum)
  __attribute__((__leaf__,__pure__,__nonnull__(1)));

/* ------------------------------------------------------------------ */

__attribute__((__always_inline__,__pure__))
static inline int
cce_condition_ref_errno_errnum (cce_condition_t const * const C)
{
  CCLIB_PC(cce_condition_errno_t const, K, C);
  return K->errnum;
}

__attribute__((__always_inline__,__pure__,__returns_nonnull__))
static inline char const *
cce_condition_ref_errno_message (cce_condition_t const * const C)
{
  CCLIB_PC(cce_condition_errno_t const, K, C);
  return K->message;
}


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#endif /* CCEXCEPTIONS_CONDITIONS_H */

/* end of file */
