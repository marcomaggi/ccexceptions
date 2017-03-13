/*
  Part of: CCExceptions
  Contents: POSIX system calls wrappers
  Date: Wed Feb 15, 2017

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

#include "ccexceptions-internals.h"
#include <errno.h>
#include <sys/stat.h>
#include <sys/mman.h>


/** --------------------------------------------------------------------
 ** System wrappers: memory allocation.
 ** ----------------------------------------------------------------- */

void *
cce_sys_malloc (cce_location_t * L, size_t size)
{
  void *	rv;
  errno = 0;
  rv = malloc (size);
  if (NULL != rv) {
    return rv;
  } else {
    cce_raise(L, cce_errno_C_clear());
  }
}

void *
cce_sys_realloc (cce_location_t * L, void * ptr, size_t newsize)
{
  void *	rv;
  errno = 0;
  rv = realloc(ptr, newsize);
  if (NULL != rv) {
    return rv;
  } else {
    cce_raise(L, cce_errno_C_clear());
  }
}

void *
cce_sys_calloc (cce_location_t * L, size_t count, size_t eltsize)
{
  void *	rv;
  errno = 0;
  rv = calloc(count, eltsize);
  if (NULL != rv) {
    return rv;
  } else {
    cce_raise(L, cce_errno_C_clear());
  }
}


/** --------------------------------------------------------------------
 ** System wrappers: locking memory pages.
 ** ----------------------------------------------------------------- */

void
cce_sys_mlock (cce_location_t * L, const void * addr, size_t len)
{
#ifdef HAVE_MLOCK
  int	rv;
  errno = 0;
  rv = mlock(addr, len);
  if (-1 == rv) {
    cce_raise(L, cce_errno_C_clear());
  }
#else
  cce_raise(L, cce_unimplemented_C);
#endif
}

void
cce_sys_munlock (cce_location_t * L, const void * addr, size_t len)
{
#ifdef HAVE_MUNLOCK
  int	rv;
  errno = 0;
  rv = munlock(addr, len);
  if (-1 == rv) {
    cce_raise(L, cce_errno_C_clear());
  }
#else
  cce_raise(L, cce_unimplemented_C);
#endif
}

void
cce_sys_mlockall (cce_location_t * L, int flags)
{
#ifdef HAVE_MLOCKALL
  int	rv;
  errno = 0;
  rv = mlockall(flags);
  if (-1 == rv) {
    cce_raise(L, cce_errno_C_clear());
  }
#else
  cce_raise(L, cce_unimplemented_C);
#endif
}

void
cce_sys_munlockall (cce_location_t * L)
{
#ifdef HAVE_MUNLOCKALL
  int	rv;
  errno = 0;
  rv = munlockall();
  if (-1 == rv) {
    cce_raise(L, cce_errno_C_clear());
  }
#else
  cce_raise(L, cce_unimplemented_C);
#endif
}


/** --------------------------------------------------------------------
 ** System wrappers: input/output and file descriptors.
 ** ----------------------------------------------------------------- */

int
cce_sys_open (cce_location_t * L, const char *filename, int flags, mode_t mode)
{
  int	rv;
  errno = 0;
  rv = open(filename, flags, mode);
  if (-1 == rv) {
    cce_raise(L, cce_errno_C_clear());
  } else {
    return rv;
  }
}

int
cce_sys_openat (cce_location_t * L, int dirfd, const char *filename, int flags, mode_t mode)
{
  int	rv;
  errno = 0;
  rv = openat(dirfd, filename, flags, mode);
  if (-1 == rv) {
    cce_raise(L, cce_errno_C_clear());
  } else {
    return rv;
  }
}

int
cce_sys_close (cce_location_t * L, int filedes)
{
  int	rv;
  errno = 0;
  rv = close(filedes);
  if (-1 == rv) {
    cce_raise(L, cce_errno_C_clear());
  } else {
    return rv;
  }
}

/* ------------------------------------------------------------------ */

size_t
cce_sys_read (cce_location_t * L, int filedes, void * buffer, size_t size)
{
  ssize_t	rv;
  errno = 0;
  rv = read(filedes, buffer, size);
  if (rv >= 0) {
    return (size_t)rv;
  } else {
    cce_raise(L, cce_errno_C_clear());
  }
}

size_t
cce_sys_pread (cce_location_t * L, int filedes, void * buffer, size_t size, off_t offset)
{
  ssize_t	rv;
  errno = 0;
  rv = pread(filedes, buffer, size, offset);
  if (rv >= 0) {
    return (size_t)rv;
  } else {
    cce_raise(L, cce_errno_C_clear());
  }
}

size_t
cce_sys_write (cce_location_t * L, int filedes, const void *buffer, size_t size)
{
  ssize_t	rv;
  errno = 0;
  rv = write(filedes, buffer, size);
  if (rv >= 0) {
    return (size_t)rv;
  } else {
    cce_raise(L, cce_errno_C_clear());
  }
}

size_t
cce_sys_pwrite (cce_location_t * L, int filedes, const void *buffer, size_t size, off_t offset)
{
  ssize_t	rv;
  errno = 0;
  rv = pwrite(filedes, buffer, size, offset);
  if (rv >= 0) {
    return (size_t)rv;
  } else {
    cce_raise(L, cce_errno_C_clear());
  }
}

/* ------------------------------------------------------------------ */

off_t
cce_sys_lseek (cce_location_t * L, int filedes, off_t offset, int whence)
{
  off_t		rv;
  errno = 0;
  rv = lseek (filedes, offset, whence);
  if (rv >= 0) {
    return rv;
  } else {
    cce_raise(L, cce_errno_C_clear());
  }
}

/* ------------------------------------------------------------------ */

size_t
cce_sys_readv (cce_location_t * L, int filedes, const struct iovec * vector, int count)
{
  ssize_t	rv;
  errno = 0;
  rv = readv(filedes, vector, count);
  if (rv >= 0) {
    return (size_t)rv;
  } else {
    cce_raise(L, cce_errno_C_clear());
  }
}

size_t
cce_sys_writev (cce_location_t * L, int filedes, const struct iovec * vector, int count)
{
  ssize_t	rv;
  errno = 0;
  rv = writev(filedes, vector, count);
  if (rv >= 0) {
    return (size_t)rv;
  } else {
    cce_raise(L, cce_errno_C_clear());
  }
}


/** --------------------------------------------------------------------
 ** System wrappers: file descriptor operations.
 ** ----------------------------------------------------------------- */

int
cce_sys_select (cce_location_t * L, int nfds, fd_set * read_fds, fd_set * write_fds, fd_set * except_fds, struct timeval * timeout)
{
  int	rv;
  errno = 0;
  rv = select(nfds, read_fds, write_fds, except_fds, timeout);
  if (-1 != rv) {
    return rv;
  } else {
    cce_raise(L, cce_errno_C_clear());
  }
}

/* ------------------------------------------------------------------ */

int
cce_sys_dup (cce_location_t * L, int old)
{
  int	rv;
  errno = 0;
  rv = dup(old);
  if (-1 != rv) {
    return rv;
  } else {
    cce_raise(L, cce_errno_C_clear());
  }
}

int
cce_sys_dup2 (cce_location_t * L, int old, int new)
{
  int	rv;
  errno = 0;
  rv = dup2(old, new);
  if (-1 != rv) {
    return rv;
  } else {
    cce_raise(L, cce_errno_C_clear());
  }
}

void
cce_sys_pipe (cce_location_t * L, int pipefd[2])
{
  int	rv;
  errno = 0;
  rv = pipe(pipefd);
  if (-1 == rv) {
    cce_raise(L, cce_errno_C_clear());
  }
}


/** --------------------------------------------------------------------
 ** System wrappers: memory mapping.
 ** ----------------------------------------------------------------- */

void *
cce_sys_mmap (cce_location_t * L, void * address, size_t length, int protect, int flags, int filedes, off_t offset)
{
  void *	rv;
  errno = 0;
  rv = mmap(address, length, protect, flags, filedes, offset);
  if (MAP_FAILED != rv) {
    return rv;
  } else {
    cce_raise(L, cce_errno_C_clear());
  }
}

int
cce_sys_munmap (cce_location_t * L, void * addr, size_t length)
{
  int	rv;
  errno = 0;
  rv = munmap(addr, length);
  if (-1 != rv) {
    return rv;
  } else {
    cce_raise(L, cce_errno_C_clear());
  }
}

int
cce_sys_msync (cce_location_t * L, void *address, size_t length, int flags)
{
  int	rv;
  errno = 0;
  rv = msync(address, length, flags);
  if (-1 != rv) {
    return rv;
  } else {
    cce_raise(L, cce_errno_C_clear());
  }
}

int
cce_sys_mprotect (cce_location_t * L, void * addr, size_t len, int prot)
{
  int	rv;
  errno = 0;
  rv = mprotect(addr, len, prot);
  if (-1 != 0) {
    return rv;
  } else {
    cce_raise(L, cce_errno_C_clear());
  }
}

/* ------------------------------------------------------------------ */

void *
cce_sys_mremap (cce_location_t * L, void * address, size_t length, size_t new_length, int flag)
{
#ifdef HAVE_MREMAP
  void *	rv;
  errno = 0;
  rv = mremap(address, length, new_length, flag);
  if (rv) {
    return rv;
  } else {
    cce_raise(L, cce_errno_C_clear());
  }
#else
  cce_raise(L, cce_unimplemented_C);
#endif
}


/** --------------------------------------------------------------------
 ** System wrappers: file system operations.
 ** ----------------------------------------------------------------- */

void
cce_sys_stat (cce_location_t * L, const char * pathname, struct stat * buf)
{
  int	rv;
  errno = 0;
  rv = stat(pathname, buf);
  if (-1 == rv) {
    cce_raise(L, cce_errno_C_clear());
  }
}

void
cce_sys_fstat (cce_location_t * L, int fd, struct stat * buf)
{
  int	rv;
  errno = 0;
  rv = fstat(fd, buf);
  if (-1 == rv) {
    cce_raise(L, cce_errno_C_clear());
  }
}

void
cce_sys_lstat (cce_location_t * L, const char * pathname, struct stat * buf)
{
  int	rv;
  errno = 0;
  rv = lstat(pathname, buf);
  if (-1 == rv) {
    cce_raise(L, cce_errno_C_clear());
  }
}

/* ------------------------------------------------------------------ */

void
cce_sys_mkdir (cce_location_t * L, const char * pathname, mode_t mode)
{
  int	rv;
  errno = 0;
  rv = mkdir(pathname, mode);
  if (-1 == rv) {
    cce_raise(L, cce_errno_C_clear());
  }
}

void
cce_sys_rmdir (cce_location_t * L, const char * pathname)
{
  int	rv;
  errno = 0;
  rv = rmdir(pathname);
  if (-1 == rv) {
    cce_raise(L, cce_errno_C_clear());
  }
}


/** --------------------------------------------------------------------
 ** System wrappers: temporary files and directories.
 ** ----------------------------------------------------------------- */

int
cce_sys_mkstemp (cce_location_t * L, char * template)
{
  int	rv;
  errno = 0;
  /* Remember that this call will mutate TEMPLATE. */
  rv = mkstemp(template);
  if (-1 == rv) {
    cce_raise(L, cce_errno_C_clear());
  } else {
    return rv;
  }
}

char *
cce_sys_mkdtemp (cce_location_t * L, char * template)
{
#ifdef HAVE_MKDTEMP
  char *	rv;
  errno = 0;
  /* Remember that this call will mutate TEMPLATE. */
  rv = mkdtemp(template);
  if (NULL != rv) {
    return rv;
  } else {
    cce_raise(L, cce_errno_C_clear());
  }
#else
  cce_raise(L, cce_unimplemented_C);
#endif
}


/** --------------------------------------------------------------------
 ** System wrappers: process handling.
 ** ----------------------------------------------------------------- */

int
cce_sys_fork (cce_location_t * L)
{
  int	rv;
  errno = 0;
  rv = fork();
  if (-1 == rv) {
    cce_raise(L, cce_errno_C_clear());
  } else {
    return rv;
  }
}

void
cce_sys_waitpid (cce_location_t * L, pid_t pid, int * wstatus, int options)
{
  int	rv;
  errno = 0;
  rv = waitpid(pid, wstatus, options);
  if (-1 == rv) {
    cce_raise(L, cce_errno_C_clear());
  }
}

/* end of file */
