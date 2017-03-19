/*
  Part of: CCExceptions
  Contents: system calls for memory management
  Date: Sun Mar 19, 2017

  Abstract



  Copyright (C) 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

  This is free software; you  can redistribute it and/or modify it under
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

#ifndef CCEXCEPTIONS_MEMORY_H
#define CCEXCEPTIONS_MEMORY_H 1

#ifdef __cplusplus
extern "C" {
#endif


/** --------------------------------------------------------------------
 ** Header files.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include <dirent.h>
#include <utime.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/mman.h>
#include <sys/wait.h>


/** --------------------------------------------------------------------
 ** System call wrappers: locking memory pages.
 ** ----------------------------------------------------------------- */

cce_decl void cce_sys_mlock (cce_location_t * L, const void * addr, size_t len)
  __attribute__((nonnull(1,2)));

cce_decl void cce_sys_munlock (cce_location_t * L, const void * addr, size_t len)
  __attribute__((nonnull(1,2)));

cce_decl void cce_sys_mlockall (cce_location_t * L, int flags)
  __attribute__((nonnull(1)));

cce_decl void cce_sys_munlockall (cce_location_t * L)
  __attribute__((nonnull(1)));


/** --------------------------------------------------------------------
 ** System call wrappers: memory mapping.
 ** ----------------------------------------------------------------- */

cce_decl void * cce_sys_mmap (cce_location_t * L, void * address, size_t length, int protect, int flags, int filedes, off_t offset)
  __attribute__((nonnull(1,2)));

cce_decl int cce_sys_munmap (cce_location_t * L, void * address, size_t length)
  __attribute__((nonnull(1,2)));

cce_decl int cce_sys_msync (cce_location_t * L, void * address, size_t length, int flags)
  __attribute__((nonnull(1,2)));

cce_decl int cce_sys_mprotect (cce_location_t * L, void * address, size_t length, int prot)
  __attribute__((nonnull(1,2)));

/* ------------------------------------------------------------------ */

cce_decl void * cce_sys_mremap (cce_location_t * L, void * address, size_t length, size_t new_length, int flag)
  __attribute__((nonnull(1,2),returns_nonnull));

cce_decl void cce_sys_madvise (cce_location_t * L, void * address, size_t length, int advice)
  __attribute__((nonnull(1,2)));


/** --------------------------------------------------------------------
 ** System call wrappers: input/output and file descriptors.
 ** ----------------------------------------------------------------- */

cce_decl int cce_sys_open (cce_location_t * L, const char *filename, int flags, mode_t mode)
  __attribute__((nonnull(1,2)));

cce_decl int cce_sys_openat (cce_location_t * L, int dirfd, const char *filename, int flags, mode_t mode)
  __attribute__((nonnull(1, 3)));

cce_decl int cce_sys_close (cce_location_t * L, int filedes)
  __attribute__((nonnull(1)));

/* ------------------------------------------------------------------ */

cce_decl size_t cce_sys_read (cce_location_t * L, int filedes, void * buffer, size_t size)
  __attribute__((nonnull(1,3)));
cce_decl size_t cce_sys_pread (cce_location_t * L, int filedes, void * buffer, size_t size, off_t offset)
  __attribute__((nonnull(1,3)));
cce_decl size_t cce_sys_write (cce_location_t * L, int filedes, const void *buffer, size_t size)
  __attribute__((nonnull(1,3)));
cce_decl size_t cce_sys_pwrite (cce_location_t * L, int filedes, const void *buffer, size_t size, off_t offset)
  __attribute__((nonnull(1,3)));

cce_decl off_t cce_sys_lseek (cce_location_t * L, int filedes, off_t offset, int whence)
  __attribute__((nonnull(1)));

cce_decl size_t cce_sys_readv (cce_location_t * L, int filedes, const struct iovec * vector, int count)
  __attribute__((nonnull(1,3)));
cce_decl size_t cce_sys_writev (cce_location_t * L, int filedes, const struct iovec * vector, int count)
  __attribute__((nonnull(1,3)));

cce_decl int cce_sys_select (cce_location_t * L, int nfds, fd_set * read_fds, fd_set * write_fds, fd_set * except_fds,
			     struct timeval * timeout)
  __attribute__((nonnull(1,3,4,5)));

cce_decl int cce_sys_dup (cce_location_t * L, int old)
  __attribute__((nonnull(1)));
cce_decl int cce_sys_dup2 (cce_location_t * L, int old, int new)
  __attribute__((nonnull(1)));

cce_decl void cce_sys_pipe (cce_location_t * L, int pipefd[2])
  __attribute__((nonnull(1,2)));

cce_decl void cce_sys_mkfifo (cce_location_t * L, const char * pathname, mode_t mode)
  __attribute__((nonnull(1,2)));


/** --------------------------------------------------------------------
 ** System call wrappers: file system operations.
 ** ----------------------------------------------------------------- */

cce_decl void cce_sys_getcwd (cce_location_t * L, char * buffer, size_t size)
  __attribute__((nonnull(1)));

cce_decl void cce_sys_chdir (cce_location_t * L, const char * pathname)
  __attribute__((nonnull(1,2)));

cce_decl void cce_sys_fchdir (cce_location_t * L, int dirfd)
  __attribute__((nonnull(1)));

/* ------------------------------------------------------------------ */

cce_decl DIR * cce_sys_opendir (cce_location_t * L, const char * pathname)
  __attribute__((nonnull(1,2)));

cce_decl DIR * cce_sys_fdopendir (cce_location_t * L, int dirfd)
  __attribute__((nonnull(1)));

cce_decl struct dirent * cce_sys_readdir (cce_location_t * L, DIR * dirstream)
  __attribute__((nonnull(1,2)));

cce_decl void cce_sys_closedir (cce_location_t * L, DIR * dirstream)
  __attribute__((nonnull(1,2)));

/* ------------------------------------------------------------------ */

cce_decl void cce_sys_stat (cce_location_t * L, const char * pathname, struct stat * buf)
  __attribute__((nonnull(1,2,3)));

cce_decl void cce_sys_fstat (cce_location_t * L, int fd, struct stat * buf)
  __attribute__((nonnull(1,3)));

cce_decl void cce_sys_lstat (cce_location_t * L, const char * pathname, struct stat * buf)
  __attribute__((nonnull(1,2,3)));

/* ------------------------------------------------------------------ */

cce_decl void cce_sys_mkdir (cce_location_t * L, const char * pathname, mode_t mode)
  __attribute__((nonnull(1,2)));

cce_decl void cce_sys_rmdir (cce_location_t * L, const char * pathname)
  __attribute__((nonnull(1,2)));

/* ------------------------------------------------------------------ */

cce_decl int cce_sys_mkstemp (cce_location_t * L, char * template)
  __attribute__((nonnull(1,2)));

cce_decl char * cce_sys_mkdtemp (cce_location_t * L, char * template)
  __attribute__((nonnull(1,2)));

/* ------------------------------------------------------------------ */

cce_decl void cce_sys_link (cce_location_t * L, const char * oldname, const char * newname)
  __attribute__((nonnull(1,2,3)));

cce_decl void cce_sys_linkat (cce_location_t * L,
			      int oldfd, const char * oldname,
			      int newfd, const char * newname,
			      int flags)
  __attribute__((nonnull(1,3,5)));

cce_decl void cce_sys_symlink (cce_location_t * L, const char * oldname, const char * newname)
  __attribute__((nonnull(1,2,3)));

cce_decl void cce_sys_symlinkat (cce_location_t * L, const char * oldname, int newdirfd, const char * newname)
  __attribute__((nonnull(1,2,4)));

cce_decl size_t cce_sys_readlink (cce_location_t * L, const char * filename, char * buffer, size_t size)
  __attribute__((nonnull(1,2,3)));

cce_decl size_t cce_sys_readlinkat (cce_location_t * L, int dirfd, const char * filename, char * buffer, size_t size)
  __attribute__((nonnull(1,3,4)));

cce_decl char * cce_sys_realpath (cce_location_t * L, const char * pathname, char * resolved_path)
  __attribute__((nonnull(1,2),returns_nonnull));

/* ------------------------------------------------------------------ */

cce_decl void cce_sys_unlink (cce_location_t * L, const char * pathname)
  __attribute__((nonnull(1,2)));

cce_decl void cce_sys_unlinkat (cce_location_t * L, int dirfc, const char * pathname, int flags)
  __attribute__((nonnull(1,3)));

cce_decl void cce_sys_remove (cce_location_t * L, const char * pathname)
  __attribute__((nonnull(1,2)));

/* ------------------------------------------------------------------ */

cce_decl void cce_sys_rename (cce_location_t * L, const char * oldname, const char * newname)
  __attribute__((nonnull(1,2,3)));

/* ------------------------------------------------------------------ */

cce_decl void cce_sys_chown (cce_location_t * L, const char * pathname, uid_t owner, gid_t group)
  __attribute__((nonnull(1,2)));

cce_decl void cce_sys_fchown (cce_location_t * L, int filedes, uid_t owner, gid_t group)
  __attribute__((nonnull(1)));

cce_decl void cce_sys_lchown (cce_location_t * L, const char * pathname, uid_t owner, gid_t group)
  __attribute__((nonnull(1,2)));

cce_decl void cce_sys_fchownat (cce_location_t * L, int dirfd, const char * pathname, uid_t owner, gid_t group, int flags)
  __attribute__((nonnull(1,3)));

/* ------------------------------------------------------------------ */

cce_decl void cce_sys_chmod (cce_location_t * L, const char * pathname, mode_t mode)
  __attribute__((nonnull(1,2)));

cce_decl void cce_sys_fchmod (cce_location_t * L, int filedes, mode_t mode)
  __attribute__((nonnull(1)));

cce_decl void cce_sys_fchmodat (cce_location_t * L, int dirfd, const char * pathname, mode_t mode, int flags)
  __attribute__((nonnull(1,3)));

/* ------------------------------------------------------------------ */

cce_decl int cce_sys_access (cce_location_t * L, const char * pathname, int how)
  __attribute__((nonnull(1,2)));

cce_decl int cce_sys_faccessat (cce_location_t * L, int dirfd, const char * pathname, int how, int flags)
  __attribute__((nonnull(1,3)));

/* ------------------------------------------------------------------ */

cce_decl void cce_sys_utime (cce_location_t * L, const char * pathname, const struct utimbuf * times)
  __attribute__((nonnull(1,2)));

cce_decl void cce_sys_utimes (cce_location_t * L, const char * pathname, const struct timeval TVP[2])
  __attribute__((nonnull(1,2,3)));

cce_decl void cce_sys_lutimes (cce_location_t * L, const char * pathname, const struct timeval TVP[2])
  __attribute__((nonnull(1,2,3)));

cce_decl void cce_sys_futimes (cce_location_t * L, int filedes, const struct timeval TVP[2])
  __attribute__((nonnull(1,3)));

/* ------------------------------------------------------------------ */

cce_decl void cce_sys_truncate (cce_location_t * L, const char * pathname, off_t length)
  __attribute__((nonnull(1,2)));

cce_decl void cce_sys_ftruncate (cce_location_t * L, int filedes, off_t length)
  __attribute__((nonnull(1)));


/** --------------------------------------------------------------------
 ** System call wrappers: process handling.
 ** ----------------------------------------------------------------- */

cce_decl int cce_sys_system (cce_location_t * L, const char * command)
  __attribute__((nonnull(1,2)));

cce_decl pid_t cce_sys_fork (cce_location_t * L)
  __attribute__((nonnull(1)));

/* ------------------------------------------------------------------ */

cce_decl void cce_sys_execv (cce_location_t * L, const char * filename, char * const argv [])
  __attribute__((nonnull(1,2,3)));

cce_decl void cce_sys_execve (cce_location_t * L, const char * filename, char * const argv [], char * const env [])
  __attribute__((nonnull(1,2,3,4)));

cce_decl void cce_sys_execvp (cce_location_t * L, const char * filename, char * const argv [])
  __attribute__((nonnull(1,2,3)));

/* ------------------------------------------------------------------ */

cce_decl void cce_sys_waitpid (cce_location_t * L, pid_t pid, int * wstatus, int options)
  __attribute__((nonnull(1,3)));


/** --------------------------------------------------------------------
 ** Predefined POSIX exception handler: file descriptor.
 ** ----------------------------------------------------------------- */

typedef struct cce_handler_filedes_t	cce_handler_filedes_t;

struct cce_handler_filedes_t {
  cce_handler_t;
  int		filedes;
};

/* Output of: (my-c-insert-cast-function "cce" "handler" "handler_filedes") */
__attribute__((const,always_inline))
static inline cce_handler_filedes_t *
cce_cast_to_handler_filedes_from_handler (cce_handler_t * src)
{
  return (cce_handler_filedes_t *)src;
}
#define cce_cast_to_handler_filedes(SRC)				\
  _Generic((SRC), cce_handler_t *: cce_cast_to_handler_filedes_from_handler)(SRC)
/* End of output. */

cce_decl void cce_cleanup_handler_filedes_init (cce_location_t * L, cce_handler_filedes_t * H, int filedes)
  __attribute__((nonnull(1,2)));

cce_decl void cce_error_handler_filedes_init (cce_location_t * L, cce_handler_filedes_t * H, int filedes)
  __attribute__((nonnull(1,2)));


/** --------------------------------------------------------------------
 ** Predefined POSIX exception handler: pipe descriptors.
 ** ----------------------------------------------------------------- */

typedef struct cce_handler_pipedes_t	cce_handler_pipedes_t;

struct cce_handler_pipedes_t {
  cce_handler_t;
  int		pipedes[2];
};

/* Output of: (my-c-insert-cast-function "cce" "handler" "handler_pipedes") */
__attribute__((const,always_inline))
static inline cce_handler_pipedes_t *
cce_cast_to_handler_pipedes_from_handler (cce_handler_t * src)
{
  return (cce_handler_pipedes_t *)src;
}
#define cce_cast_to_handler_pipedes(SRC)				\
  _Generic((SRC), cce_handler_t *: cce_cast_to_handler_pipedes_from_handler)(SRC)
/* End of output. */

cce_decl void cce_cleanup_handler_pipedes_init (cce_location_t * L, cce_handler_pipedes_t * H, int pipedes[2])
  __attribute__((nonnull(1,2,3)));

cce_decl void cce_error_handler_pipedes_init (cce_location_t * L, cce_handler_pipedes_t * H, int pipedes[2])
  __attribute__((nonnull(1,2,3)));


/** --------------------------------------------------------------------
 ** Predefined POSIX exception handler: removal of temporary file.
 ** ----------------------------------------------------------------- */

typedef struct cce_handler_tmpfile_t	cce_handler_tmpfile_t;

struct cce_handler_tmpfile_t {
  cce_handler_t;
  char *	pathname;
};

/* Output of: (my-c-insert-cast-function "cce" "handler" "handler_tmpfile") */
__attribute__((const,always_inline))
static inline cce_handler_tmpfile_t *
cce_cast_to_handler_tmpfile_from_handler (cce_handler_t * src)
{
  return (cce_handler_tmpfile_t *)src;
}
#define cce_cast_to_handler_tmpfile(SRC)				\
  _Generic((SRC), cce_handler_t *: cce_cast_to_handler_tmpfile_from_handler)(SRC)
/* End of output. */

cce_decl void cce_cleanup_handler_tmpfile_init (cce_location_t * L, cce_handler_tmpfile_t * H, const char * pathname)
  __attribute__((nonnull(1,2,3)));

cce_decl void cce_error_handler_tmpfile_init (cce_location_t * L, cce_handler_tmpfile_t * H, const char * pathname)
  __attribute__((nonnull(1,2,3)));


/** --------------------------------------------------------------------
 ** Predefined POSIX exception handler: removal of temporary directory.
 ** ----------------------------------------------------------------- */

typedef struct cce_handler_tmpdir_t	cce_handler_tmpdir_t;

struct cce_handler_tmpdir_t {
  cce_handler_t;
  char *	pathname;
};

/* Output of: (my-c-insert-cast-function "cce" "handler" "handler_tmpdir") */
__attribute__((const,always_inline))
static inline cce_handler_tmpdir_t *
cce_cast_to_handler_tmpdir_from_handler (cce_handler_t * src)
{
  return (cce_handler_tmpdir_t *)src;
}
#define cce_cast_to_handler_tmpdir(SRC)				\
  _Generic((SRC), cce_handler_t *: cce_cast_to_handler_tmpdir_from_handler)(SRC)
/* End of output. */

cce_decl void cce_cleanup_handler_tmpdir_init (cce_location_t * L, cce_handler_tmpdir_t * H, const char * pathname)
  __attribute__((nonnull(1,2,3)));

cce_decl void cce_error_handler_tmpdir_init (cce_location_t * L, cce_handler_tmpdir_t * H, const char * pathname)
  __attribute__((nonnull(1,2,3)));


/** --------------------------------------------------------------------
 ** Predefined POSIX exception handler: directory streams.
 ** ----------------------------------------------------------------- */

typedef struct cce_handler_dirstream_t	cce_handler_dirstream_t;

struct cce_handler_dirstream_t {
  cce_handler_t;
  DIR *		dirstream;
};

/* Output of: (my-c-insert-cast-function "cce" "handler" "handler_dirstream") */
__attribute__((const,always_inline))
static inline cce_handler_dirstream_t *
cce_cast_to_handler_dirstream_from_handler (cce_handler_t * src)
{
  return (cce_handler_dirstream_t *)src;
}
#define cce_cast_to_handler_dirstream(SRC)				\
  _Generic((SRC), cce_handler_t *: cce_cast_to_handler_dirstream_from_handler)(SRC)
/* End of output. */

cce_decl void cce_cleanup_handler_dirstream_init (cce_location_t * L, cce_handler_dirstream_t * H, DIR * dirstream)
  __attribute__((nonnull(1,2,3)));

cce_decl void cce_error_handler_dirstream_init (cce_location_t * L, cce_handler_dirstream_t * H, DIR * dirstream)
  __attribute__((nonnull(1,2,3)));


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* CCEXCEPTIONS_MEMORY_H */

/* end of file */
