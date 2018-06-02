/*
  Part of: CCExceptions
  Contents: exceptional condition descriptor functions
  Date: Dec 26, 2016

  Abstract



  Copyright (C) 2016, 2017, 2018 Marco Maggi <marco.maggi-ipsu@poste.it>

  This is free software; you can  redistribute it and/or modify it under
  the terms of the GNU Lesser General Public License as published by the
  Free Software  Foundation; either version  3.0 of the License,  or (at
  your option) any later version.

  This library  is distributed in the  hope that it will  be useful, but
  WITHOUT   ANY  WARRANTY;   without  even   the  implied   warranty  of
  MERCHANTABILITY  or FITNESS  FOR A  PARTICULAR PURPOSE.   See  the GNU
  Lesser General Public License for more details.

  You  should have  received a  copy of  the GNU  Lesser  General Public
  License along  with this library; if  not, write to  the Free Software
  Foundation, Inc.,  59 Temple Place,  Suite 330, Boston,  MA 02111-1307
  USA.

*/


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "ccexceptions-internals.h"
#include <limits.h>	// for INT_MAX


/** --------------------------------------------------------------------
 ** Condition objects operations.
 ** ----------------------------------------------------------------- */

void
cce_condition_init (cce_condition_t * const C, cce_descriptor_t const * D)
{
  C->descriptor = D;
}
void
cce_condition_final (cce_condition_t * const C)
{
  cce_descriptor_t const * D = C->descriptor;
  for (cce_descriptor_t const * iter = D; iter; iter = iter->parent) {
    if (iter->final) {
      iter->final(C);
    }
  }
}
void
cce_condition_delete (cce_condition_t * const C)
{
  cce_condition_final(C);
  {
    cce_condition_delete_fun_t * del = C->descriptor->delete;
    if (del) {
      del(C);
    }
  }
}
char const *
cce_condition_static_message (cce_condition_t const * const C)
{
  return C->descriptor->static_message(C);
}
bool
cce_is_condition (cce_condition_t const * const C, cce_descriptor_t const * const descriptor)
{
  return cce_descriptor_child_and_ancestor(C->descriptor, descriptor);
}
bool
cce_descriptor_child_and_ancestor (cce_descriptor_t const * const D, cce_descriptor_t const * const ancestor)
{
  for (cce_descriptor_t const * child = D; child; child = child->parent) {
    if (child == ancestor) {
      return true;
    }
  }
  return false;
}


/** --------------------------------------------------------------------
 ** Root condition.
 ** ----------------------------------------------------------------- */

static char const *
cce_condition_root_static_message_fun (cce_condition_t const * C CCE_UNUSED)
{
  return "Root exceptional condition";
}

/* This  condition descriptor  is  the  root of  the  tree of  condition
   descriptors. */
static cce_descriptor_root_t const cce_descriptor_root_stru = {
  .descriptor.parent		= NULL,
  .descriptor.delete		= NULL,
  .descriptor.final		= NULL,
  .descriptor.static_message	= cce_condition_root_static_message_fun
};

cce_descriptor_root_t const * const cce_descriptor_root_ptr = &cce_descriptor_root_stru;

void
cce_descriptor_set_root_parent (cce_descriptor_t * D)
{
  D->parent = &(cce_descriptor_root_stru.descriptor);
}

bool
cce_condition_is_root (cce_condition_t const * C)
{
  return cce_is_condition(C, &(cce_descriptor_root_stru.descriptor));
}


/** --------------------------------------------------------------------
 ** Unknown condition.
 ** ----------------------------------------------------------------- */

static char const *
cce_condition_unknown_static_message_fun (cce_condition_t const * C CCE_UNUSED)
{
  return "Unknown exceptional condition";
}

/* This   condition  descriptor   represents   an  unknown   exceptional
   condition.   This   descriptor  has  only  one   instance  statically
   allocated below: "cce_condition_unknown". */
static cce_descriptor_unknown_t const cce_descriptor_unknown_stru = {
  .descriptor.parent		= &(cce_descriptor_root_stru.descriptor),
  .descriptor.delete		= NULL,
  .descriptor.final		= NULL,
  .descriptor.static_message	= cce_condition_unknown_static_message_fun
};

cce_descriptor_unknown_t const * const cce_descriptor_unknown_ptr = &cce_descriptor_unknown_stru;

/* This is the single instance  of unknown exceptional condition.  It is
   used by "cce_raise()". */
static cce_condition_unknown_t const cce_condition_unknown_stru = {
  .root.condition.descriptor = &(cce_descriptor_unknown_stru.descriptor)
};

cce_condition_unknown_t const * const cce_condition_unknown_ptr = &cce_condition_unknown_stru;


/** --------------------------------------------------------------------
 ** Break condition.
 ** ----------------------------------------------------------------- */

static char const *
cce_condition_break_static_message_fun (cce_condition_t const * C CCE_UNUSED)
{
  return "Break exceptional condition";
}

/* This condition descriptor represents  an break exceptional condition.
   This  descriptor has  only one  instance statically  allocated below:
   "cce_condition_break". */
static cce_descriptor_break_t const cce_descriptor_break_stru = {
  .descriptor.parent		= &(cce_descriptor_root_stru.descriptor),
  .descriptor.delete		= NULL,
  .descriptor.final		= NULL,
  .descriptor.static_message	= cce_condition_break_static_message_fun
};

cce_descriptor_break_t const * const cce_descriptor_break_ptr = &cce_descriptor_break_stru;

/* This is  the single instance  of break exceptional condition.   It is
   used by "cce_raise()". */
static cce_condition_break_t const cce_condition_break_stru = {
  .root.condition.descriptor = &(cce_descriptor_break_stru.descriptor)
};

cce_condition_break_t const * const cce_condition_break_ptr = &cce_condition_break_stru;


/** --------------------------------------------------------------------
 ** Unspecified error condition.
 ** ----------------------------------------------------------------- */

static char const *
cce_condition_error_static_message_fun (cce_condition_t const * C CCE_UNUSED)
{
  return "Unspecified error exceptional condition";
}

/* This   condition  descriptor   represents   an  "unspecified   error"
   exceptional  condition.   This  descriptor   has  only  one  instance
   statically allocated below: "cce_condition_error". */
static cce_descriptor_error_t const cce_descriptor_error_stru = {
  .descriptor.parent		= &(cce_descriptor_root_stru.descriptor),
  .descriptor.delete		= NULL,
  .descriptor.final		= NULL,
  .descriptor.static_message	= cce_condition_error_static_message_fun
};

cce_descriptor_error_t const * const cce_descriptor_error_ptr = &cce_descriptor_error_stru;

/* This  is  the  single  instance of  "unspecified  error"  exceptional
   condition.  It is used by "cce_raise()". */
static cce_condition_error_t const cce_condition_error_stru = {
  .root.condition.descriptor = &(cce_descriptor_error_stru.descriptor)
};

cce_condition_error_t const * const cce_condition_error_ptr = &cce_condition_error_stru;


/** --------------------------------------------------------------------
 ** Runtime error condition.
 ** ----------------------------------------------------------------- */

static char const *
cce_condition_runtime_error_static_message_fun (cce_condition_t const * C CCE_UNUSED)
{
  return "Runtime error exceptional condition";
}

/* This condition  descriptor represents  a "runtime  error" exceptional
   condition.   This   descriptor  has  only  one   instance  statically
   allocated below: "cce_condition_runtime_error". */
static cce_descriptor_runtime_error_t const cce_descriptor_runtime_error_stru = {
  .descriptor.parent		= &(cce_descriptor_error_stru.descriptor),
  .descriptor.delete		= NULL,
  .descriptor.final		= NULL,
  .descriptor.static_message	= cce_condition_runtime_error_static_message_fun
};

cce_descriptor_runtime_error_t const * const cce_descriptor_runtime_error_ptr = &cce_descriptor_runtime_error_stru;

/* This is the single instance of "runtime error" exceptional condition.
   It is used by "cce_raise()". */
static cce_condition_runtime_error_t const cce_condition_runtime_error_stru = {
  .error.root.condition.descriptor = &(cce_descriptor_runtime_error_stru.descriptor)
};

cce_condition_runtime_error_t const * const cce_condition_runtime_error_ptr = &cce_condition_runtime_error_stru;


/** --------------------------------------------------------------------
 ** Logic error condition.
 ** ----------------------------------------------------------------- */

static char const *
cce_condition_logic_error_static_message_fun (cce_condition_t const * C CCE_UNUSED)
{
  return "Logic error exceptional condition";
}

/* This  condition descriptor  represents  a  "logic error"  exceptional
   condition.   This   descriptor  has  only  one   instance  statically
   allocated below: "cce_condition_logic_error". */
static cce_descriptor_logic_error_t const cce_descriptor_logic_error_stru = {
  .descriptor.parent		= &(cce_descriptor_error_stru.descriptor),
  .descriptor.delete		= NULL,
  .descriptor.final		= NULL,
  .descriptor.static_message	= cce_condition_logic_error_static_message_fun
};

cce_descriptor_logic_error_t const * const cce_descriptor_logic_error_ptr = &cce_descriptor_logic_error_stru;

/* This is the  single instance of "logic  error" exceptional condition.
   It is used by "cce_raise()". */
static cce_condition_logic_error_t const cce_condition_logic_error_stru = {
  .error.root.condition.descriptor = &(cce_descriptor_logic_error_stru.descriptor)
};

cce_condition_logic_error_t const * const cce_condition_logic_error_ptr = &cce_condition_logic_error_stru;


/** --------------------------------------------------------------------
 ** Exceptional condition descriptor: unreachable code.
 ** ----------------------------------------------------------------- */

static cce_condition_static_message_fun_t	cce_condition_static_message_unreachable;
static cce_condition_delete_fun_t		cce_condition_delete_unreachable;

static cce_descriptor_unreachable_t const cce_descriptor_unreachable_stru = {
  .descriptor.parent		= &cce_descriptor_logic_error_stru.descriptor,
  .descriptor.delete		= cce_condition_delete_unreachable,
  .descriptor.final		= NULL,
  .descriptor.static_message	= cce_condition_static_message_unreachable
};

cce_descriptor_unreachable_t const * const cce_descriptor_unreachable_ptr = &cce_descriptor_unreachable_stru;

/* ------------------------------------------------------------------ */

void
cce_condition_delete_unreachable (cce_condition_t * C)
{
  free(C);
}

char const *
cce_condition_static_message_unreachable (cce_condition_t const * C CCE_UNUSED)
{
  return "CCExceptions unreachable code was executed";
}

/* ------------------------------------------------------------------ */

void
cce_condition_init_unreachable (cce_condition_unreachable_t * C,
				char const * const filename,
				char const * const funcname,
				int const linenum)
{
  /* Initialise the parent type. */
  cce_condition_init_logic_error(&(C->logic_error));

  /* Initialise the fields of this type. */
  C->filename			= filename;
  C->funcname			= funcname;
  C->linenum			= linenum;
}

cce_condition_t const *
cce_condition_new_unreachable (cce_destination_t L,
			       char const * const filename, char const * const funcname, int const linenum)
{
  cce_condition_unreachable_t *	C = cce_sys_malloc(L, sizeof(cce_condition_unreachable_t));

  /* Initialise the basic condition fields. */
  cce_condition_init((cce_condition_t *)C, &cce_descriptor_unreachable_stru.descriptor);

  cce_condition_init_unreachable(C, filename, funcname, linenum);

  return (cce_condition_t const *)C;
}


/** --------------------------------------------------------------------
 ** Unimplemented condition.
 ** ----------------------------------------------------------------- */

static char const *
cce_condition_unimplemented_static_message_fun (cce_condition_t const * C CCE_UNUSED)
{
  return "Unimplemented exceptional condition";
}

/* This  condition descriptor  represents  an unimplemented  exceptional
   condition.   This   descriptor  has  only  one   instance  statically
   allocated below: "cce_condition_unimplemented". */
static cce_descriptor_unimplemented_t const cce_descriptor_unimplemented_stru = {
  .descriptor.parent		= &(cce_descriptor_logic_error_stru.descriptor),
  .descriptor.delete		= NULL,
  .descriptor.final		= NULL,
  .descriptor.static_message	= cce_condition_unimplemented_static_message_fun
};

cce_descriptor_unimplemented_t const * const cce_descriptor_unimplemented_ptr = &cce_descriptor_unimplemented_stru;

/* This is  the single instance of  unimplemented exceptional condition.
   It is used by "cce_raise()". */
static cce_condition_unimplemented_t const cce_condition_unimplemented_stru = {
  .logic_error.error.root.condition.descriptor = &(cce_descriptor_unimplemented_stru.descriptor)
};

cce_condition_unimplemented_t const * const cce_condition_unimplemented_ptr = &cce_condition_unimplemented_stru;


/** --------------------------------------------------------------------
 ** Invalid function argument condition.
 ** ----------------------------------------------------------------- */

static cce_condition_delete_fun_t		cce_condition_delete_invalid_argument;
static cce_condition_static_message_fun_t	cce_condition_static_message_invalid_argument;

static cce_descriptor_invalid_argument_t const cce_descriptor_invalid_argument_stru = {
  .descriptor.parent		= &(cce_descriptor_logic_error_stru.descriptor),
  .descriptor.delete		= cce_condition_delete_invalid_argument,
  .descriptor.final		= NULL,
  .descriptor.static_message	= cce_condition_static_message_invalid_argument
};

cce_descriptor_invalid_argument_t const * cce_descriptor_invalid_argument_ptr = &cce_descriptor_invalid_argument_stru;

/* ------------------------------------------------------------------ */

void
cce_condition_delete_invalid_argument (cce_condition_t * C CCE_UNUSED)
{
  free(C);
}

char const *
cce_condition_static_message_invalid_argument (cce_condition_t const * C CCE_UNUSED)
{
  return "invalid function argument";
}

/* ------------------------------------------------------------------ */

void
cce_condition_init_invalid_argument (cce_condition_invalid_argument_t * C, char const * func, unsigned index)
{
  cce_condition_init_logic_error(&(C->logic_error));
  C->funcname	= func;
  C->index	= index;
}

cce_condition_t const *
cce_condition_new_invalid_argument (cce_location_t * L, char const * func, unsigned index)
{
  cce_condition_invalid_argument_t *	C = cce_sys_malloc(L, sizeof(cce_condition_invalid_argument_t));

  cce_condition_init((cce_condition_t *) C, &(cce_descriptor_invalid_argument_stru.descriptor));
  cce_condition_init_invalid_argument(C, func, index);
  return &(C->logic_error.error.root.condition);
}


/** --------------------------------------------------------------------
 ** Mathematical error condition.
 ** ----------------------------------------------------------------- */

static char const *
cce_condition_static_message_math_error (cce_condition_t const * C CCE_UNUSED)
{
  return "error computing a mathematical expression";
}

/* This   condition   descriptor   represents  an   mathematical   error
   exceptional  condition.   This  descriptor   has  only  one  instance
   statically allocated below: "cce_condition_math_error". */
static cce_descriptor_math_error_t const cce_descriptor_math_error_stru = {
  .descriptor.parent		= &(cce_descriptor_runtime_error_stru.descriptor),
  .descriptor.delete		= NULL,
  .descriptor.final		= NULL,
  .descriptor.static_message	= cce_condition_static_message_math_error
};

cce_descriptor_math_error_t const * const cce_descriptor_math_error_ptr = &cce_descriptor_math_error_stru;

/* This is  the single instance  of "math error"  exceptional condition.
   It is used by "cce_raise()". */
static cce_condition_math_error_t const cce_condition_math_error_stru = {
  .runtime_error.error.root.condition.descriptor = &(cce_descriptor_math_error_stru.descriptor)
};

cce_condition_math_error_t const * const cce_condition_math_error_ptr = &cce_condition_math_error_stru;


/** --------------------------------------------------------------------
 ** Mathematical not-a-number error condition.
 ** ----------------------------------------------------------------- */

static char const *
cce_condition_static_message_math_nan (cce_condition_t const * C CCE_UNUSED)
{
  return "not-a-number result while computing a mathematical expression";
}

/* This  condition descriptor  represents  an mathematical  not-a-number
   error exceptional  condition.  This descriptor has  only one instance
   statically allocated below: "cce_condition_math_nan". */
static cce_descriptor_math_nan_t const cce_descriptor_math_nan_stru = {
  .descriptor.parent		= &(cce_descriptor_math_error_stru.descriptor),
  .descriptor.delete		= NULL,
  .descriptor.final		= NULL,
  .descriptor.static_message	= cce_condition_static_message_math_nan
};

cce_descriptor_math_nan_t const * const cce_descriptor_math_nan_ptr = &cce_descriptor_math_nan_stru;

/* This  is  the  single  instance   of  "math  nan  error"  exceptional
   condition.  It is used by "cce_raise()". */
static cce_condition_math_nan_t const cce_condition_math_nan_stru = {
  .math_error.runtime_error.error.root.condition.descriptor = &(cce_descriptor_math_nan_stru.descriptor)
};

cce_condition_math_nan_t const * const cce_condition_math_nan_ptr = &cce_condition_math_nan_stru;


/** --------------------------------------------------------------------
 ** Mathematical infinity error condition.
 ** ----------------------------------------------------------------- */

static char const *
cce_condition_static_message_math_infinity (cce_condition_t const * C CCE_UNUSED)
{
  return "infinite result while computing a mathematical expression";
}

/* This  condition descriptor  represents  an mathematical  not-a-number
   error exceptional  condition.  This descriptor has  only one instance
   statically allocated below: "cce_condition_math_infinity". */
static cce_descriptor_math_infinity_t const cce_descriptor_math_infinity_stru = {
  .descriptor.parent		= &(cce_descriptor_math_error_stru.descriptor),
  .descriptor.delete		= NULL,
  .descriptor.final		= NULL,
  .descriptor.static_message	= cce_condition_static_message_math_infinity
};

cce_descriptor_math_infinity_t const * const cce_descriptor_math_infinity_ptr = &cce_descriptor_math_infinity_stru;

/* This  is the  single instance  of "math  infinity error"  exceptional
   condition.  It is used by "cce_raise()". */
static cce_condition_math_infinity_t const cce_condition_math_infinity_stru = {
  .math_error.runtime_error.error.root.condition.descriptor = &(cce_descriptor_math_infinity_stru.descriptor)
};

cce_condition_math_infinity_t const * const cce_condition_math_infinity_ptr = &cce_condition_math_infinity_stru;


/** --------------------------------------------------------------------
 ** Mathematical overflow error condition.
 ** ----------------------------------------------------------------- */

static char const *
cce_condition_static_message_math_overflow (cce_condition_t const * C CCE_UNUSED)
{
  return "overflow error while computing a mathematical expression";
}

/* This condition  descriptor represents an mathematical  overflow error
   exceptional  condition.   This  descriptor   has  only  one  instance
   statically allocated below: "cce_condition_math_overflow". */
static cce_descriptor_math_overflow_t const cce_descriptor_math_overflow_stru = {
  .descriptor.parent		= &(cce_descriptor_math_error_stru.descriptor),
  .descriptor.delete		= NULL,
  .descriptor.final		= NULL,
  .descriptor.static_message	= cce_condition_static_message_math_overflow
};

cce_descriptor_math_overflow_t const * const cce_descriptor_math_overflow_ptr = &cce_descriptor_math_overflow_stru;

/* This  is the  single instance  of "math  overflow error"  exceptional
   condition.  It is used by "cce_raise()". */
static cce_condition_math_overflow_t const cce_condition_math_overflow_stru = {
  .math_error.runtime_error.error.root.condition.descriptor = &(cce_descriptor_math_overflow_stru.descriptor)
};

cce_condition_math_overflow_t const * const cce_condition_math_overflow_ptr = &cce_condition_math_overflow_stru;


/** --------------------------------------------------------------------
 ** Mathematical underflow error condition.
 ** ----------------------------------------------------------------- */

static char const *
cce_condition_static_message_math_underflow (cce_condition_t const * C CCE_UNUSED)
{
  return "underflow error while computing a mathematical expression";
}

/* This condition descriptor represents  an mathematical underflow error
   exceptional  condition.   This  descriptor   has  only  one  instance
   statically allocated below: "cce_condition_math_underflow". */
static cce_descriptor_math_underflow_t const cce_descriptor_math_underflow_stru = {
  .descriptor.parent		= &(cce_descriptor_math_error_stru.descriptor),
  .descriptor.delete		= NULL,
  .descriptor.final		= NULL,
  .descriptor.static_message	= cce_condition_static_message_math_underflow
};

cce_descriptor_math_underflow_t const * const cce_descriptor_math_underflow_ptr = &cce_descriptor_math_underflow_stru;

/* This is  the single  instance of  "math underflow  error" exceptional
   condition.  It is used by "cce_raise()". */
static cce_condition_math_underflow_t const cce_condition_math_underflow_stru = {
  .math_error.runtime_error.error.root.condition.descriptor = &(cce_descriptor_math_underflow_stru.descriptor)
};

cce_condition_math_underflow_t const * const cce_condition_math_underflow_ptr = &cce_condition_math_underflow_stru;


/** --------------------------------------------------------------------
 ** Errno condition.
 ** ----------------------------------------------------------------- */

static char const *
cce_condition_errno_static_message_fun (cce_condition_t const * C)
{
  CCE_PC(cce_condition_errno_t const, EC, C);
  return EC->message;
}

/* This condition descriptor  represents "errno" exceptional conditions.
   It is a child of the "runtime error" descriptor. */
cce_descriptor_errno_t const cce_descriptor_errno_stru = {
  .descriptor.parent		= &(cce_descriptor_runtime_error_stru.descriptor),
  .descriptor.delete		= NULL,
  .descriptor.final		= NULL,
  .descriptor.static_message	= cce_condition_errno_static_message_fun
};

cce_descriptor_errno_t const * const cce_descriptor_errno_ptr = (cce_descriptor_errno_t const *) &cce_descriptor_errno_stru;

#define CCE_DECLARE_ERRNO_CONDITION(ERRNO,MESSAGE)			\
  { .runtime_error.error.root.condition.descriptor = &(cce_descriptor_errno_stru.descriptor), .errnum = ERRNO, .message = MESSAGE }

#define ERRNO_CONDITIONS_NUM		148
#define LAST_ERRNO_CONDITION		147

static cce_condition_errno_t const
errno_conditions[ERRNO_CONDITIONS_NUM] = {
  /* 000 */ CCE_DECLARE_ERRNO_CONDITION(0,			"(errno=0) Success"),
  /* Whenever  an  errno  constant  is not  defined  by  the  underlying
     platform: the "configure" script  defines the associated "VALUEOF_"
     constant as  -1.  Here  we intercept  the -1  value so  that, while
     performing a  linear search,  it is not  mistaken for  an undefined
     constant. */
  /* 001 */ CCE_DECLARE_ERRNO_CONDITION(-1,			"Invalid errno value"),
  /* 002 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EPERM,		"(errno=EPERM) Permission denied"),
  /* 003 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOENT,		"(errno=ENOENT) No such file or directory"),
  /* 004 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ESRCH,		"(errno=ESRCH) No such process"),
  /* 005 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EINTR,		"(errno=EINTR) Interrupted system call"),
  /* 006 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EIO,		"(errno=EIO) Input/output error"),
  /* 007 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENXIO,		"(errno=ENXIO) No such device or address"),
  /* 008 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_E2BIG,		"(errno=E2BIG) Argument list too long"),
  /* 009 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOEXEC,	"(errno=ENOEXEC) Exec format error"),
  /* 010 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EBADF,		"(errno=EBADF) Bad file descriptor"),
  /* 011 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ECHILD,		"(errno=ECHILD) No child processes"),
  /* 012 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EPROCLIM,	"(errno=EPROCLIM) Too many processes"),
  /* 013 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EAGAIN,		"(errno=EAGAIN) Resource temporarily unavailable"),
  /* 014 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOMEM,		"(errno=ENOMEM) Cannot allocate memory"),
  /* 015 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EACCES,		"(errno=EACCES) Access permission denied"),
  /* 016 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EFAULT,		"(errno=EFAULT) Bad address"),
  /* 017 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOTBLK,	"(errno=ENOTBLK) Block device required"),
  /* 018 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EBUSY,		"(errno=EBUSY) Device or resource busy"),
  /* 019 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EEXIST,		"(errno=EEXIST) File exists"),
  /* 020 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EXDEV,		"(errno=EXDEV) Invalid cross-device link"),
  /* 021 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENODEV,		"(errno=ENODEV) No such device"),
  /* 022 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOTDIR,	"(errno=ENOTDIR) Not a directory"),
  /* 023 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EISDIR,		"(errno=EISDIR) Is a directory"),
  /* 024 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EINVAL,		"(errno=EINVAL) Invalid argument"),
  /* 025 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENFILE,		"(errno=ENFILE) Too many open files in system"),
  /* 026 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EMFILE,		"(errno=EMFILE) Too many open files"),
  /* 027 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOTTY,		"(errno=ENOTTY) Inappropriate ioctl for device"),
  /* 028 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ETXTBSY,	"(errno=ETXTBSY) Text file busy"),
  /* 029 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EFBIG,		"(errno=EFBIG) File too large"),
  /* 030 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOSPC,		"(errno=ENOSPC) No space left on device"),
  /* 031 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ESPIPE,		"(errno=ESPIPE) Illegal seek"),
  /* 032 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EROFS,		"(errno=EROFS) Read-only file system"),
  /* 033 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EMLINK,		"(errno=EMLINK) Too many links"),
  /* 034 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EPIPE,		"(errno=EPIPE) Broken pipe"),
  /* 035 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EDOM,		"(errno=EDOM) Argument out of domain"),
  /* 036 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ERANGE,		"(errno=ERANGE) Result out of range"),
  /* 037 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EDEADLK,	"(errno=EDEADLK) Resource deadlock avoided"),
  /* 038 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENAMETOOLONG,	"(errno=ENAMETOOLONG) File name too long"),
  /* 039 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOLCK,		"(errno=ENOLCK) No locks available"),
  /* 040 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOSYS,		"(errno=ENOSYS) Operation not implemented"),
  /* 041 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOTEMPTY,	"(errno=ENOTEMPTY) Directory not empty"),
  /* 042 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ELOOP,		"(errno=ELOOP) Too many levels of symbolic links"),
  /* 043 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EWOULDBLOCK,	"(errno=EWOULDBLOCK) Operation would block"),
  /* 044 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOMSG,		"(errno=ENOMSG) No message of desired type"),
  /* 045 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EIDRM,		"(errno=EIDRM) Identifier removed"),
  /* 046 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ECHRNG,		"(errno=ECHRNG) Channel number out of range"),
  /* 047 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EL2NSYNC,	"(errno=EL2NSYNC) Level 2 not synchronized"),
  /* 048 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EL3HLT,		"(errno=EL3HLT) Level 3 halted"),
  /* 049 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EL3RST,		"(errno=EL3RST) Level 3 reset"),
  /* 050 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ELNRNG,		"(errno=ELNRNG) Link number out of range"),
  /* 051 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EUNATCH,	"(errno=EUNATCH) Protocol driver not attached"),
  /* 052 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOCSI,		"(errno=ENOCSI) No CSI structure available"),
  /* 053 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EL2HLT,		"(errno=EL2HLT) Level 2 halted"),
  /* 054 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EBADE,		"(errno=EBADE) Invalid exchange"),
  /* 055 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EBADR,		"(errno=EBADR) Invalid request descriptor"),
  /* 056 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EXFULL,		"(errno=EXFULL) Exchange full"),
  /* 057 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOANO,		"(errno=ENOANO) No anode"),
  /* 058 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EBADRQC,	"(errno=EBADRQC) Invalid request code"),
  /* 059 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EBADSLT,	"(errno=EBADSLT) Invalid slot"),
  /* 060 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EDEADLOCK,	"(errno=EDEADLOCK) File locking deadlock error"),
  /* 061 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EBFONT,		"(errno=EBFONT) Bad font file format"),
  /* 062 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOSTR,		"(errno=ENOSTR) Device not a stream"),
  /* 063 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENODATA,	"(errno=ENODATA) No data available"),
  /* 064 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ETIME,		"(errno=ETIME) Timer expired"),
  /* 065 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOSR,		"(errno=ENOSR) Out of streams resources"),
  /* 066 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENONET,		"(errno=ENONET) Machine is not on the network"),
  /* 067 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOPKG,		"(errno=ENOPKG) Package not installed"),
  /* 068 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EREMOTE,	"(errno=EREMOTE) Object is remote"),
  /* 069 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOLINK,	"(errno=ENOLINK)"),
  /* 070 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EADV,		"(errno=EADV) Advertise error"),
  /* 071 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ESRMNT,		"(errno=ESRMNT) Srmount error"),
  /* 072 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ECOMM,		"(errno=ECOMM) Communication error on send"),
  /* 073 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EPROTO,		"(errno=EPROTO) Protocol error"),
  /* 074 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EMULTIHOP,	"(errno=EMULTIHOP) Multihop attempted"),
  /* 075 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EDOTDOT,	"(errno=EDOTDOT) RFS specific error"),
  /* 076 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EBADMSG,	"(errno=EBADMSG) Bad message"),
  /* 077 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EOVERFLOW,	"(errno=EOVERFLOW) Value too large for defined data type"),
  /* 078 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOTUNIQ,	"(errno=ENOTUNIQ) Name not unique on network"),
  /* 079 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EBADFD,		"(errno=EBADFD) File descriptor in bad state"),
  /* 080 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EREMCHG,	"(errno=EREMCHG) Remote address changed"),
  /* 081 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ELIBACC,	"(errno=ELIBACC) Can not access a needed shared library"),
  /* 082 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ELIBBAD,	"(errno=ELIBBAD) Accessing a corrupted shared library"),
  /* 083 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ELIBSCN,	"(errno=ELIBSCN) .lib section in a.out corrupted"),
  /* 084 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ELIBMAX,	"(errno=ELIBMAX) Attempting to link in too many shared libraries"),
  /* 085 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ELIBEXEC,	"(errno=ELIBEXEC) Cannot exec a shared library directly"),
  /* 086 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EILSEQ,		"(errno=EILSEQ) Invalid or incomplete multibyte or wide character"),
  /* 087 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ERESTART,	"(errno=ERESTART) Interrupted system call should be restarted"),
  /* 088 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ESTRPIPE,	"(errno=ESTRPIPE) Streams pipe error"),
  /* 089 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EUSERS,		"(errno=EUSERS) Too many users"),
  /* 090 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOTSOCK,	"(errno=ENOTSOCK) Socket operation on non-socket"),
  /* 091 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EDESTADDRREQ,	"(errno=EDESTADDRREQ) Destination address required"),
  /* 092 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EMSGSIZE,	"(errno=EMSGSIZE) Message too long"),
  /* 093 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EPROTOTYPE,	"(errno=EPROTOTYPE) Protocol wrong type for socket"),
  /* 094 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOPROTOOPT,	"(errno=ENOPROTOOPT) Protocol not available"),
  /* 095 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EPROTONOSUPPORT,"(errno=EPROTONOSUPPORT) Protocol not supported"),
  /* 096 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ESOCKTNOSUPPORT,"(errno=ESOCKTNOSUPPORT) Socket type not supported"),
  /* 097 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EOPNOTSUPP,	"(errno=EOPNOTSUPP) Operation not supported"),
  /* 098 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EPFNOSUPPORT,	"(errno=EPFNOSUPPORT) Protocol family not supported"),
  /* 099 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EAFNOSUPPORT,	"(errno=EAFNOSUPPORT) Address family not supported by protocol"),
  /* 100 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EADDRINUSE,	"(errno=EADDRINUSE) Address already in use"),
  /* 101 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EADDRNOTAVAIL,	"(errno=EADDRNOTAVAIL) Cannot assign requested address"),
  /* 102 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENETDOWN,	"(errno=ENETDOWN) Network is down"),
  /* 103 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENETUNREACH,	"(errno=ENETUNREACH) Network is unreachable"),
  /* 104 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENETRESET,	"(errno=ENETRESET) Network dropped connection on reset"),
  /* 105 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ECONNABORTED,	"(errno=ECONNABORTED) Software caused connection abort"),
  /* 106 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ECONNRESET,	"(errno=ECONNRESET) Connection reset by peer"),
  /* 107 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOBUFS,	"(errno=ENOBUFS) No buffer space available"),
  /* 108 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EISCONN,	"(errno=EISCONN) Transport endpoint is already connected"),
  /* 109 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOTCONN,	"(errno=ENOTCONN) Transport endpoint is not connected"),
  /* 110 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ESHUTDOWN,	"(errno=ESHUTDOWN) Cannot send after transport endpoint shutdown"),
  /* 111 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ETOOMANYREFS,	"(errno=ETOOMANYREFS) Too many references: cannot splice"),
  /* 112 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ETIMEDOUT,	"(errno=ETIMEDOUT) Connection timed out"),
  /* 113 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ECONNREFUSED,	"(errno=ECONNREFUSED) Connection refused"),
  /* 114 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EHOSTDOWN,	"(errno=EHOSTDOWN) Host is down"),
  /* 115 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EHOSTUNREACH,	"(errno=EHOSTUNREACH) No route to host"),
  /* 116 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EALREADY,	"(errno=EALREADY) Operation already in progress"),
  /* 117 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EINPROGRESS,	"(errno=EINPROGRESS) Operation now in progress"),
  /* 118 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ESTALE,		"(errno=ESTALE) Stale NFS file handle"),
  /* 119 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EUCLEAN,	"(errno=EUCLEAN) Structure needs cleaning"),
  /* 120 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOTNAM,	"(errno=ENOTNAM) Not a XENIX named type file"),
  /* 121 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENAVAIL,	"(errno=ENAVAIL) No XENIX semaphores available"),
  /* 122 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EISNAM,		"(errno=EISNAM) Is a named type file"),
  /* 123 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EREMOTEIO,	"(errno=EREMOTEIO) Remote I/O error"),
  /* 124 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EDQUOT,		"(errno=EDQUOT) Disk quota exceeded"),
  /* 125 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOMEDIUM,	"(errno=ENOMEDIUM) No medium found"),
  /* 126 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EMEDIUMTYPE,	"(errno=EMEDIUMTYPE) Wrong medium type"),
  /* 127 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ECANCELED,	"(errno=ECANCELED) Operation canceled"),
  /* 128 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOKEY,		"(errno=ENOKEY) Required key not available"),
  /* 129 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EKEYEXPIRED,	"(errno=EKEYEXPIRED) Key has expired"),
  /* 130 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EKEYREVOKED,	"(errno=EKEYREVOKED) Key has been revoked"),
  /* 131 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EKEYREJECTED,	"(errno=EKEYREJECTED) Key was rejected by service"),
  /* 132 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EOWNERDEAD,	"(errno=EOWNERDEAD) Owner died"),
  /* 133 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOTRECOVERABLE,"(errno=ENOTRECOVERABLE) State not recoverable"),
  /* 134 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EBADRPC,	"(errno=EBADRPC) RPC struct is bad"),
  /* 135 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ERPCMISMATCH,	"(errno=ERPCMISMATCH) RPC version wrong"),
  /* 136 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EPROGUNAVAIL,	"(errno=EPROGUNAVAIL) RPC program not available"),
  /* 137 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EPROGMISMATCH,	"(errno=EPROGMISMATCH) RPC program version wrong"),
  /* 138 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EPROCUNAVAIL,	"(errno=EPROCUNAVAIL) RPC bad procedure for program"),
  /* 139 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EFTYPE,		"(errno=EFTYPE) Inappropriate file type or format"),
  /* 140 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EAUTH,		"(errno=EAUTH) Authentication error"),
  /* 141 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENEEDAUTH,	"(errno=ENEEDAUTH) Need authenticator"),
  /* 142 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOTSUP,	"(errno=ENOTSUP) Not supported"),
  /* 143 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EBACKGROUND,	"(errno=EBACKGROUND) Inappropriate operation for background process"),
  /* 144 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EDIED,		"(errno=EDIED) Translator died"),
  /* 145 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ERFKILL,	"(errno=ERFKILL) Operation not possible due to RF-kill"),
  /* 146 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EHWPOISON,	"(errno=EHWPOISON) Memory page has hardware error"),
  /* 147 */ CCE_DECLARE_ERRNO_CONDITION(INT_MAX,		"Unknown errno code")
};

cce_condition_t const *
cce_condition_new_errno (int errnum)
{
  for (int i = 0; i < ERRNO_CONDITIONS_NUM; ++i) {
    if (errnum == errno_conditions[i].errnum) {
      return &(errno_conditions[i].runtime_error.error.root.condition);
    }
  }
  /* If  we  are  here  ERRNUM  is an  invalid  "errno"  value  for  the
     underlying platform. */
  return &(errno_conditions[LAST_ERRNO_CONDITION].runtime_error.error.root.condition);
}

cce_condition_t const *
cce_condition_new_errno_clear (void)
{
  int	errnum = errno;
  errno = 0;
  return cce_condition_new_errno(errnum);
}

/* end of file */
