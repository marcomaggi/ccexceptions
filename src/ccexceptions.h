/*
  Part of: CCExceptions
  Contents: public header file
  Date: Sat Dec 17, 2016

  Abstract

	This is the  main header: it must be included  in all the source
	files using CCExceptions.  Notice that  the code needs the POSIX
	features, so it defines the following symbol:

	   #define _POSIX_C_SOURCE 200809L

  Copyright (C) 2016, 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

  This program is  free software: you can redistribute  it and/or modify
  it  under the  terms  of  the GNU  Lesser  General  Public License  as
  published by  the Free  Software Foundation, either  version 3  of the
  License, or (at your option) any later version.

  This program  is distributed in the  hope that it will  be useful, but
  WITHOUT   ANY  WARRANTY;   without  even   the  implied   warranty  of
  MERCHANTABILITY  or FITNESS  FOR A  PARTICULAR PURPOSE.   See  the GNU
  General Public License for more details.

  You  should have  received a  copy of  the GNU  Lesser General  Public
  License     along    with     this    program.      If    not,     see
  <http://www.gnu.org/licenses/>.
*/

#ifndef CCEXCEPTIONS_H
#define CCEXCEPTIONS_H 1


/** --------------------------------------------------------------------
 ** Preliminary definitions.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
extern "C" {
#endif

/* The macro CCE_UNUSED indicates that  a function, function argument or
   variable may potentially be unused. Usage examples:

   static int unused_function (char arg) CCE_UNUSED;
   int foo (char unused_argument CCE_UNUSED);
   int unused_variable CCE_UNUSED;
*/
#ifdef __GNUC__
#  define CCE_UNUSED		__attribute__((unused))
#else
#  define CCE_UNUSED		/* empty */
#endif

#ifndef __GNUC__
#  define __attribute__(...)	/* empty */
#endif

#ifndef __GNUC__
#  define __builtin_expect(...)	/* empty */
#endif

/* I found  the following chunk on  the Net.  (Marco Maggi;  Sun Feb 26,
   2012) */
#if defined _WIN32 || defined __CYGWIN__
#  ifdef BUILDING_DLL
#    ifdef __GNUC__
#      define cce_decl		__attribute__((dllexport))
#    else
#      define cce_decl		__declspec(dllexport)
#    endif
#  else
#    ifdef __GNUC__
#      define cce_decl		__attribute__((dllimport))
#    else
#      define cce_decl		__declspec(dllimport)
#    endif
#  endif
#  define cce_private_decl	extern
#else
#  if __GNUC__ >= 4
#    define cce_decl		__attribute__((visibility ("default")))
#    define cce_private_decl	__attribute__((visibility ("hidden")))
#  else
#    define cce_decl		extern
#    define cce_private_decl	extern
#  endif
#endif


/** --------------------------------------------------------------------
 ** Helper macros.
 ** ----------------------------------------------------------------- */

/* Pointer cast macro helper. */
#define CCE_PC(TYPE,X,Y)		TYPE * X = (TYPE *) (Y)

/* Cast pointer S to a location structure and evaluate to the pointer to
   condition object. */
#define CCE_CLOC(S)			(((cce_location_t *)(S))->condition)


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

/* Enable latest POSIX features. */
#define _POSIX_C_SOURCE		200809L

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h> /* for offsetof() */
#include <setjmp.h>
#include <errno.h>
#include <unistd.h>


/** --------------------------------------------------------------------
 ** Constants.
 ** ----------------------------------------------------------------- */

typedef enum {
  /* This code  represents the return  value of the first  evaluation of
     "setjmp()". */
  CCE_SUCCESS		= 0,
  CCE_ENTER		= 0,

  /* This  code  represents  the   return  value  of  the  "setjmp()"
     evaluation after a "cce_throw()" call. */
  CCE_ERROR,

  /* This  code  represents  the   return  value  of  the  "setjmp()"
     evaluation after a "cce_retry()" call. */
  CCE_RETRY,

  /* This  code  is  available  to  the  custom  code  to  define  other
     represents the return value of the "setjmp()" evaluation after a
     "cce_raise()" call. */
  CCE_FIRST_NEXT
} cce_code_t;


/** --------------------------------------------------------------------
 ** Version functions.
 ** ----------------------------------------------------------------- */

cce_decl const char *	cce_version_string		(void)
  __attribute__((leaf,pure));
cce_decl int		cce_version_interface_current	(void)
  __attribute__((leaf,pure));
cce_decl int		cce_version_interface_revision	(void)
  __attribute__((leaf,pure));
cce_decl int		cce_version_interface_age	(void)
  __attribute__((leaf,pure));


/** --------------------------------------------------------------------
 ** Forward declarations.
 ** ----------------------------------------------------------------- */

typedef struct cce_location_t			cce_location_t;
typedef struct cce_handler_t			cce_handler_t;

typedef struct cce_descriptor_t			cce_descriptor_t;
typedef struct cce_condition_t			cce_condition_t;

typedef struct cce_descriptor_root_t		cce_descriptor_root_t;
typedef struct cce_condition_root_t		cce_condition_root_t;

typedef struct cce_descriptor_unknown_t		cce_descriptor_unknown_t;
typedef struct cce_condition_unknown_t		cce_condition_unknown_t;

typedef struct cce_descriptor_unimplemented_t	cce_descriptor_unimplemented_t;
typedef struct cce_condition_unimplemented_t	cce_condition_unimplemented_t;

typedef struct cce_descriptor_invalid_argument_t cce_descriptor_invalid_argument_t;
typedef struct cce_condition_invalid_argument_t	cce_condition_invalid_argument_t;

typedef struct cce_descriptor_errno_t		cce_descriptor_errno_t;
typedef struct cce_condition_errno_t		cce_condition_errno_t;

typedef struct cce_descriptor_h_errno_t		cce_descriptor_h_errno_t;
typedef struct cce_condition_h_errno_t		cce_condition_h_errno_t;


/** --------------------------------------------------------------------
 ** Error and cleanup handlers.
 ** ----------------------------------------------------------------- */

typedef void cce_handler_fun_t (const cce_condition_t * L, cce_handler_t * H);

struct cce_handler_t {
  bool				is_cleanup_handler;
  cce_handler_fun_t *		handler_function;
  cce_handler_t *		next_handler;
};

cce_decl void cce_register_cleanup_handler (cce_location_t * L, cce_handler_t * H)
  __attribute__((leaf,nonnull(1,2)));

cce_decl void cce_register_error_handler (cce_location_t * L, cce_handler_t * H)
  __attribute__((leaf,nonnull(1,2)));

/* We do *not*  set the "leaf" attribute for this  function, because the
   cleanup  handlers  might  modify  data  in  the  current  compilation
   unit. */
cce_decl void cce_run_cleanup_handlers		(cce_location_t * L)
  __attribute__((nonnull(1)));

/* We do *not*  set the "leaf" attribute for this  function, because the
   error handlers might modify data in the current compilation unit. */
cce_decl void cce_run_error_handlers		(cce_location_t * L)
  __attribute__((nonnull(1)));


/** --------------------------------------------------------------------
 ** Exceptional condition descriptors.
 ** ----------------------------------------------------------------- */

typedef void cce_condition_final_fun_t (cce_condition_t * C)
  __attribute__((nonnull(1)));

typedef const char * cce_condition_static_message_fun_t	(const cce_condition_t * C)
  __attribute__((nonnull(1),returns_nonnull));

struct cce_descriptor_t {
  const cce_descriptor_t *		parent;
  cce_condition_final_fun_t *		final;
  cce_condition_static_message_fun_t *	static_message;
};

struct cce_condition_t {
  const cce_descriptor_t *		descriptor;
};

/* ------------------------------------------------------------------ */

cce_decl void cce_condition_init (cce_condition_t * C, const cce_descriptor_t * D)
  __attribute__((leaf,nonnull(1,2)));

cce_decl void cce_condition_final (cce_condition_t * C)
  __attribute__((leaf,nonnull(1)));

cce_decl bool cce_is_condition (const cce_condition_t * C, const cce_descriptor_t * D)
  __attribute__((leaf,nonnull(1,2)));

cce_decl const char * cce_condition_static_message (cce_condition_t * C)
  __attribute__((leaf,nonnull(1)));

/* ------------------------------------------------------------------ */

cce_decl bool cce_descriptor_child_and_parent (const cce_descriptor_t * child, const cce_descriptor_t * parent)
  __attribute__((leaf,nonnull(1,2)));


/** --------------------------------------------------------------------
 ** Exceptional condition objects: root exception.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_root_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_root_t {
  cce_condition_t	condition;
};

cce_decl void cce_descriptor_set_root_parent (cce_descriptor_t * D)
  __attribute__((nonnull(1)));

cce_decl bool cce_condition_is_root (const cce_condition_t * C)
  __attribute__((pure,nonnull(1)));


/** --------------------------------------------------------------------
 ** Exceptional condition objects: unknown exception.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_unknown_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_unknown_t {
  cce_condition_root_t	root;
};

cce_decl const cce_descriptor_unknown_t * const	cce_descriptor_unknown_ptr;
cce_decl const cce_condition_unknown_t * const	cce_condition_unknown_ptr;

__attribute__((const,always_inline))
static inline const cce_condition_t *
cce_condition_make_unknown (void)
{
  return &(cce_condition_unknown_ptr->root.condition);
}

__attribute__((pure,nonnull(1),always_inline))
static inline bool
cce_condition_is_unknown (const cce_condition_t * C)
{
  return cce_is_condition(C, &(cce_descriptor_unknown_ptr->descriptor));
}

/* ------------------------------------------------------------------ */

#define cce_condition_unknown(S)					\
  _Generic((S),								\
	   cce_condition_unknown_t		*: (S),			\
	   cce_location_t			*: (cce_condition_unknown_t *)CCE_CLOC(S), \
	   cce_condition_t			*: (cce_condition_unknown_t *)(S), \
	   cce_condition_root_t			*: (cce_condition_unknown_t *)(S), \
	   const cce_condition_t		*: (cce_condition_unknown_t *)(S), \
	   const cce_condition_root_t		*: (cce_condition_unknown_t *)(S), \
	   const cce_condition_unknown_t	*: (cce_condition_unknown_t *)(S))


/** --------------------------------------------------------------------
 ** Exceptional condition objects: unimplemented exception.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_unimplemented_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_unimplemented_t {
  cce_condition_root_t	root;
};

cce_decl const cce_descriptor_unimplemented_t * const	cce_descriptor_unimplemented_ptr;
cce_decl const cce_condition_unimplemented_t * const	cce_condition_unimplemented_ptr;

__attribute__((const,always_inline))
static inline const cce_condition_t *
cce_condition_make_unimplemented (void)
{
  return &(cce_condition_unimplemented_ptr->root.condition);
}

__attribute__((pure,nonnull(1),always_inline)) static inline bool
cce_condition_is_unimplemented (const cce_condition_t * C)
{
  return cce_is_condition(C, &(cce_descriptor_unimplemented_ptr->descriptor));
}

/* ------------------------------------------------------------------ */

#define cce_condition_unimplemented(S)						\
  _Generic((S),								\
	   cce_condition_unimplemented_t	*: (S),				\
	   cce_location_t		*: (cce_condition_unimplemented_t *)CCE_CLOC(S), \
	   cce_condition_t		*: (cce_condition_unimplemented_t *)(S), \
	   cce_condition_root_t			*: (cce_condition_unimplemented_t *)(S), \
	   const cce_condition_t	*: (cce_condition_unimplemented_t *)(S), \
	   const cce_condition_root_t		*: (cce_condition_unimplemented_t *)(S), \
	   const cce_condition_unimplemented_t	*: (cce_condition_unimplemented_t *)(S))


/** --------------------------------------------------------------------
 ** Exceptional condition objects: invalid function argument.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_invalid_argument_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_invalid_argument_t {
  cce_condition_root_t	root;
  /* Pointer to  a statically  allocated ASCIIZ string  representing the
     function name; usually generated with "__func__". */
  const char *		funcname;
  /* One-based index of the invalid argument. */
  unsigned		index;
};

cce_decl const cce_descriptor_invalid_argument_t * cce_descriptor_invalid_argument_ptr;

cce_decl cce_condition_t * cce_condition_make_invalid_argument (cce_location_t * L, const char * func, unsigned index)
  __attribute__((nonnull(1,2),returns_nonnull));

__attribute__((pure,nonnull(1),always_inline))
static inline bool
cce_condition_is_invalid_argument (const cce_condition_t * C)
{
  return cce_is_condition(C, &(cce_descriptor_invalid_argument_ptr->descriptor));
}

/* ------------------------------------------------------------------ */

#define cce_condition_invalid_argument(S)					\
  _Generic((S),								\
	   cce_condition_invalid_argument_t	*: (S),				\
	   cce_location_t		*: (cce_condition_invalid_argument_t *)CCE_CLOC(S), \
	   cce_condition_t		*: (cce_condition_invalid_argument_t *)(S), \
	   cce_condition_root_t			*: (cce_condition_invalid_argument_t *)(S), \
	   const cce_condition_t	*: (cce_condition_invalid_argument_t *)(S), \
	   const cce_condition_root_t		*: (cce_condition_invalid_argument_t *)(S), \
	   const cce_condition_invalid_argument_t *: (cce_condition_invalid_argument_t *)(S))


/** --------------------------------------------------------------------
 ** Exceptional condition objects: errno exception.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_errno_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_errno_t {
  cce_condition_root_t	root;
  int			errnum;
  const char *		message;
};

cce_decl const cce_descriptor_errno_t * const cce_descriptor_errno_ptr;

cce_decl const cce_condition_t * cce_condition_make_errno (int code)
  __attribute__((leaf,returns_nonnull));

__attribute__((returns_nonnull,always_inline))
static inline const cce_condition_t *
cce_condition_make_errno_clear (void)
{
  int	errnum = errno;
  errno = 0;
  return cce_condition_make_errno(errnum);
}

__attribute__((nonnull(1),always_inline)) static inline bool
cce_condition_is_errno (const cce_condition_t * C)
{
  return cce_is_condition(C, &(cce_descriptor_errno_ptr->descriptor));
}

/* ------------------------------------------------------------------ */

#define cce_condition_errno(S)							\
  _Generic((S),								\
	   cce_condition_errno_t		*: (S),				\
	   cce_location_t		*: (cce_condition_errno_t *)CCE_CLOC(S), \
	   cce_condition_t		*: (cce_condition_errno_t *)(S), \
	   cce_condition_root_t			*: (cce_condition_errno_t *)(S), \
	   const cce_condition_t	*: (cce_condition_errno_t *)(S), \
	   const cce_condition_root_t		*: (cce_condition_errno_t *)(S), \
	   const cce_condition_errno_t		*: (cce_condition_errno_t *)(S))


/** --------------------------------------------------------------------
 ** Exceptional condition objects: h_errno exception.
 ** ----------------------------------------------------------------- */

struct cce_descriptor_h_errno_t {
  cce_descriptor_t	descriptor;
};

struct cce_condition_h_errno_t {
  cce_condition_root_t	root;
  int			errnum;
  const char *		message;
};

cce_decl const cce_descriptor_h_errno_t * const cce_descriptor_h_errno_ptr;

cce_decl const cce_condition_t * cce_condition_make_h_errno (int code)
  __attribute__((leaf,returns_nonnull));

cce_decl const cce_condition_t * cce_condition_make_h_errno_clear (void)
  __attribute__((leaf,returns_nonnull));

__attribute__((nonnull(1),always_inline)) static inline bool
cce_condition_is_h_errno (const cce_condition_t * C)
{
  return cce_is_condition(C, &(cce_descriptor_h_errno_ptr->descriptor));
}

/* ------------------------------------------------------------------ */

#define cce_condition_h_errno(S)						\
  _Generic((S),								\
	   cce_condition_h_errno_t		*: (S),				\
	   cce_location_t		*: (cce_condition_h_errno_t *)CCE_CLOC(S), \
	   cce_condition_t		*: (cce_condition_h_errno_t *)(S), \
	   cce_condition_root_t			*: (cce_condition_h_errno_t *)(S), \
	   const cce_condition_t	*: (cce_condition_h_errno_t *)(S), \
	   const cce_condition_root_t		*: (cce_condition_h_errno_t *)(S), \
	   const cce_condition_h_errno_t	*: (cce_condition_h_errno_t *)(S))


/** --------------------------------------------------------------------
 ** Locations.
 ** ----------------------------------------------------------------- */

struct cce_location_t {
  /* The buffer must be the first member of this struct. */
  sigjmp_buf			buffer;
  const cce_condition_t *	condition;
  cce_handler_t *		first_handler;
};

cce_decl void cce_location_init	(cce_location_t * here)
  __attribute__((leaf,nonnull(1)));

#define cce_location(HERE)						\
  __builtin_expect((cce_location_init(HERE),sigsetjmp((void *)(HERE),0)),0)

cce_decl void cce_raise (cce_location_t * L, const cce_condition_t * C)
  __attribute__((noreturn,nonnull(1)));

cce_decl void cce_retry (cce_location_t * L)
  __attribute__((noreturn,nonnull(1)));


/** --------------------------------------------------------------------
 ** Post definitions.
 ** ----------------------------------------------------------------- */

__attribute__((nonnull(1),always_inline))
static inline void
cce_run_error_handlers_final (cce_location_t * L)
{
  cce_run_error_handlers(L);
  cce_condition_final((cce_condition_t *)(L->condition));
}

__attribute__((nonnull(1),always_inline))
static inline void
cce_run_cleanup_handlers_final (cce_location_t * L)
{
  cce_run_cleanup_handlers(L);
  cce_condition_final((cce_condition_t *)(L->condition));
}

/* ------------------------------------------------------------------ */

__attribute__((nonnull(1,2),always_inline))
static inline void
cce_run_error_handlers_raise (cce_location_t * L, cce_location_t * upper_L)
{
  cce_run_error_handlers(L);
  cce_raise(upper_L, L->condition);
}

__attribute__((nonnull(1,2),always_inline))
static inline void
cce_run_cleanup_handlers_raise (cce_location_t * L, cce_location_t * upper_L)
{
  cce_run_cleanup_handlers(L);
  cce_raise(upper_L, L->condition);
}


/** --------------------------------------------------------------------
 ** System call wrappers: memory allocation.
 ** ----------------------------------------------------------------- */

cce_decl void * cce_sys_malloc (cce_location_t * L, size_t size)
  __attribute__((nonnull(1),returns_nonnull));

cce_decl void * cce_sys_realloc (cce_location_t * L, void * ptr, size_t newsize)
  __attribute__((nonnull(1),returns_nonnull));

cce_decl void * cce_sys_calloc (cce_location_t * L, size_t count, size_t eltsize)
  __attribute__((nonnull(1),returns_nonnull));


/** --------------------------------------------------------------------
 ** Predefined POSIX exception handler: malloc pointer.
 ** ----------------------------------------------------------------- */

typedef struct cce_handler_malloc_t	cce_handler_malloc_t;

struct cce_handler_malloc_t {
  cce_handler_t	exception_handler[1];
  void *	pointer;
};

/* Output of: (my-c-insert-cast-function "cce" "handler" "handler_malloc") */
__attribute__((const,always_inline))
static inline cce_handler_malloc_t *
cce_cast_to_handler_malloc_from_handler (cce_handler_t * src)
{
  return (cce_handler_malloc_t *)src;
}
#define cce_cast_to_handler_malloc(SRC)					\
  _Generic((SRC), cce_handler_t *: cce_cast_to_handler_malloc_from_handler)(SRC)
/* End of output. */

cce_decl void cce_cleanup_handler_malloc_init (cce_location_t * L, cce_handler_malloc_t * H, void * pointer)
  __attribute__((nonnull(1,2,3)));

cce_decl void cce_error_handler_malloc_init (cce_location_t * L, cce_handler_malloc_t * H, void * pointer)
  __attribute__((nonnull(1,2,3)));


/** --------------------------------------------------------------------
 ** Generic macros.
 ** ----------------------------------------------------------------- */

/* Cast a pointer to condition descriptor. */
#define CCE_C001(S)	((cce_descriptor_t*)(S))

/* Cast a pointer to condition object. */
#define CCE_C002(S)	((cce_condition_t*)(S))

/* Cast a pointer  to condition object and evaluate to  a pointer to its
   descriptor. */
#define CCE_C003(S)	(CCE_C002(S)->descriptor)

/* Given  a pointer  to condition  object of  any type  or a  pointer to
   condition  descriptor of  any  type: return  a  pointer to  condition
   descriptor.

   This macro assumes  that: every struct in the  hierarchy of condition
   objects has  its parent struct  as first  field; every struct  in the
   hierarchy of  condition descriptors  has its  parent struct  as first
   field. */
#define cce_descriptor(S)					\
  _Generic((S),							\
	   cce_descriptor_t			*: (S),		\
	   cce_descriptor_root_t				*: CCE_C001(S), \
	   cce_descriptor_unknown_t			*: CCE_C001(S), \
	   cce_descriptor_unimplemented_t		*: CCE_C001(S), \
	   cce_descriptor_invalid_argument_t		*: CCE_C001(S), \
	   cce_descriptor_errno_t			*: CCE_C001(S), \
	   cce_descriptor_h_errno_t			*: CCE_C001(S), \
								\
	   const cce_descriptor_t		*: CCE_C001(S), \
	   const cce_descriptor_root_t			*: CCE_C001(S), \
	   const cce_descriptor_unknown_t		*: CCE_C001(S), \
	   const cce_descriptor_unimplemented_t		*: CCE_C001(S), \
	   const cce_descriptor_invalid_argument_t	*: CCE_C001(S), \
	   const cce_descriptor_errno_t			*: CCE_C001(S), \
	   const cce_descriptor_h_errno_t		*: CCE_C001(S), \
								\
	   cce_condition_t			*: CCE_C003(S),	\
	   cce_condition_root_t				*: CCE_C003(S),	\
	   cce_condition_unknown_t			*: CCE_C003(S),	\
	   cce_condition_unimplemented_t		*: CCE_C003(S),	\
	   cce_condition_invalid_argument_t		*: CCE_C003(S),	\
	   cce_condition_errno_t			*: CCE_C003(S),	\
	   cce_condition_h_errno_t			*: CCE_C003(S),	\
								\
	   const cce_condition_t		*: CCE_C003(S),	\
	   const cce_condition_root_t			*: CCE_C003(S),	\
	   const cce_condition_unknown_t		*: CCE_C003(S),	\
	   const cce_condition_unimplemented_t		*: CCE_C003(S),	\
	   const cce_condition_invalid_argument_t	*: CCE_C003(S),	\
	   const cce_condition_errno_t			*: CCE_C003(S),	\
	   const cce_condition_h_errno_t		*: CCE_C003(S))

/* ------------------------------------------------------------------ */

#define cce_condition(S)					\
  _Generic((S),							\
	   cce_condition_t			*: (S),		\
	   cce_condition_root_t				*: CCE_C002(S), \
	   cce_condition_unknown_t			*: CCE_C002(S), \
	   cce_condition_unimplemented_t		*: CCE_C002(S), \
	   cce_condition_invalid_argument_t		*: CCE_C002(S), \
	   cce_condition_errno_t			*: CCE_C002(S), \
	   cce_condition_h_errno_t			*: CCE_C002(S), \
								\
	   const cce_condition_t		*: CCE_C002(S), \
	   const cce_condition_root_t			*: CCE_C002(S), \
	   const cce_condition_unknown_t		*: CCE_C002(S), \
	   const cce_condition_unimplemented_t		*: CCE_C002(S), \
	   const cce_condition_invalid_argument_t	*: CCE_C002(S), \
	   const cce_condition_errno_t			*: CCE_C002(S), \
	   const cce_condition_h_errno_t		*: CCE_C002(S), \
								\
	   cce_location_t			*: CCE_C002(CCE_CLOC(S)))


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* CCEXCEPTIONS_H */

/* end of file */
