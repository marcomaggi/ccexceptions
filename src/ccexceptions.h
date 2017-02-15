/*
  Part of: CCExceptions
  Contents: public header file
  Date: Sat Dec 17, 2016

  Abstract



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
 ** Headers.
 ** ----------------------------------------------------------------- */

/* Enable latest POSIX features. */
#define _POSIX_C_SOURCE		200809L

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <setjmp.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/select.h>

/** --------------------------------------------------------------------
 ** Constants.
 ** ----------------------------------------------------------------- */

typedef enum {
  /* This code  represents the return  value of the first  evaluation of
     "setjmp()". */
  CCE_SUCCESS		= 0,

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
typedef struct cce_condition_descriptor_t	cce_condition_descriptor_t;
typedef struct cce_condition_t			cce_condition_t;

/** --------------------------------------------------------------------
 ** Error and cleanup handlers.
 ** ----------------------------------------------------------------- */

typedef void cce_handler_fun_t (const cce_condition_t * L, cce_handler_t * H);

struct cce_handler_t {
  bool				is_cleanup_handler;
  cce_handler_fun_t *		handler_function;
  cce_handler_t *		next_handler;
};

cce_decl void cce_register_cleanup_handler	(cce_location_t * L, cce_handler_t * H)
  __attribute__((leaf,nonnull(1,2)));
cce_decl void cce_register_error_handler	(cce_location_t * L, cce_handler_t * H)
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

typedef void		cce_condition_free_fun_t		(cce_condition_t * condition)
  __attribute__((nonnull(1)));
typedef const char *	cce_condition_static_message_fun_t	(const cce_condition_t * condition)
  __attribute__((nonnull(1),returns_nonnull));

struct cce_condition_descriptor_t {
  const cce_condition_descriptor_t *	parent;
  cce_condition_free_fun_t *		free;
  cce_condition_static_message_fun_t *	static_message;
};

struct cce_condition_t {
  const cce_condition_descriptor_t *		descriptor;
};

cce_decl const cce_condition_descriptor_t *	cce_root_D;

/* ------------------------------------------------------------------ */

cce_decl void cce_condition_init (cce_condition_t * condition,
				  const cce_condition_descriptor_t * descriptor)
  __attribute__((leaf,nonnull(1,2)));
cce_decl bool cce_condition_is_a (const cce_condition_t * condition,
				  const cce_condition_descriptor_t * descriptor)
  __attribute__((leaf,nonnull(1,2)));
cce_decl bool cce_condition_descriptor_child_and_parent (const cce_condition_descriptor_t * child,
							 const cce_condition_descriptor_t * parent)
  __attribute__((leaf,nonnull(1,2)));
cce_decl void cce_condition_free (cce_condition_t * condition)
  __attribute__((leaf,nonnull(1)));
cce_decl const char * cce_condition_static_message (cce_condition_t * condition)
  __attribute__((leaf,nonnull(1)));

__attribute__((pure,nonnull(1),returns_nonnull,always_inline))
static inline const cce_condition_descriptor_t *
cce_condition_descriptor (const cce_condition_t * C)
{
  return C->descriptor;
}

/* ------------------------------------------------------------------ */

cce_decl const cce_condition_descriptor_t *	cce_unknown_D;
cce_decl const cce_condition_t *		cce_unknown_E;

__attribute__((pure,nonnull(1),always_inline)) static inline bool
cce_unknown_condition_is_a (const cce_condition_t * condition)
{
  return cce_condition_is_a(condition, cce_unknown_D);
}

/* ------------------------------------------------------------------ */

typedef struct cce_errno_D_t {
  cce_condition_descriptor_t;
} cce_errno_D_t;

typedef struct cce_errno_C_t {
  cce_condition_t;
  int						errnum;
  const char *					message;
} cce_errno_C_t;

cce_decl const cce_condition_descriptor_t *	cce_errno_D;

cce_decl cce_condition_t * cce_errno_condition (int code)
  __attribute__((leaf,returns_nonnull));

__attribute__((nonnull(1),always_inline)) static inline bool
cce_errno_condition_is_a (const cce_condition_t * condition)
{
  return cce_condition_is_a(condition, cce_errno_D);
}

/** --------------------------------------------------------------------
 ** Locations.
 ** ----------------------------------------------------------------- */

struct cce_location_t {
  /* The buffer must be the first member of this struct. */
  jmp_buf			buffer;
  const cce_condition_t *	condition;
  cce_handler_t *		first_handler;
};

cce_decl void cce_location_init	(cce_location_t * here)
  __attribute__((leaf,nonnull(1)));
cce_decl void cce_raise (cce_location_t * L, const cce_condition_t * condition)
  __attribute__((noreturn,nonnull(1)));
cce_decl void cce_retry (cce_location_t * L)
  __attribute__((noreturn,nonnull(1)));

__attribute__((pure,nonnull(1),returns_nonnull,always_inline))
static inline cce_condition_t *
cce_condition (cce_location_t * L)
{
  return (cce_condition_t *)(L->condition);
}

#define cce_location(HERE)	(cce_location_init(HERE),setjmp((void *)(HERE)))

/** --------------------------------------------------------------------
 ** POSIX wrappers.
 ** ----------------------------------------------------------------- */

cce_decl int cce_sys_open (cce_location_t * L, const char *filename, int flags, mode_t mode)
  __attribute__((nonnull(1,2)));
cce_decl int cce_sys_close (cce_location_t * L, int filedes)
  __attribute__((nonnull(1)));

cce_decl ssize_t cce_sys_read (cce_location_t * L, int filedes, void * buffer, size_t size)
  __attribute__((nonnull(1,3)));
cce_decl ssize_t cce_sys_pread (cce_location_t * L, int filedes, void * buffer, size_t size, off_t offset)
  __attribute__((nonnull(1,3)));
cce_decl ssize_t cce_sys_write (cce_location_t * L, int filedes, const void *buffer, size_t size)
  __attribute__((nonnull(1,3)));
cce_decl ssize_t cce_sys_pwrite (cce_location_t * L, int filedes, const void *buffer, size_t size, off_t offset)
  __attribute__((nonnull(1,3)));

cce_decl off_t cce_sys_lseek (cce_location_t * L, int filedes, off_t offset, int whence)
  __attribute__((nonnull(1)));

cce_decl ssize_t cce_sys_readv (cce_location_t * L, int filedes, const struct iovec * vector, int count)
  __attribute__((nonnull(1,3)));
cce_decl ssize_t cce_sys_writev (cce_location_t * L, int filedes, const struct iovec * vector, int count)
  __attribute__((nonnull(1,3)));

cce_decl void * cce_sys_mmap (cce_location_t * L, void * address, size_t length, int protect, int flags, int filedes, off_t offset)
  __attribute__((nonnull(1)));
cce_decl int cce_sys_munmap (cce_location_t * L, void * addr, size_t length)
  __attribute__((nonnull(1,2)));
cce_decl int cce_sys_msync (cce_location_t * L, void *address, size_t length, int flags)
  __attribute__((nonnull(1,2)));
cce_decl int cce_sys_mprotect (cce_location_t * L, void * addr, size_t len, int prot)
  __attribute__((nonnull(1,2)));

cce_decl int cce_sys_select (cce_location_t * L, int nfds, fd_set * read_fds, fd_set * write_fds, fd_set * except_fds,
			     struct timeval * timeout)
  __attribute__((nonnull(1,3,4,5)));

cce_decl int cce_sys_dup (cce_location_t * L, int old)
  __attribute__((nonnull(1)));
cce_decl int cce_sys_dup2 (cce_location_t * L, int old, int new)
  __attribute__((nonnull(1)));

/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* CCEXCEPTIONS_H */

/* end of file */
