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


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "ccexceptions-internals.h"
#include "ccexceptions-system.h"
#include "ccexceptions-networking.h"


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
    cce_raise(L, cce_condition_make_errno_clear());
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
    cce_raise(L, cce_condition_make_errno_clear());
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
    cce_raise(L, cce_condition_make_errno_clear());
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
    cce_raise(L, cce_condition_make_errno_clear());
  }
#else
  cce_raise(L, cce_condition_unimplemented);
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
    cce_raise(L, cce_condition_make_errno_clear());
  }
#else
  cce_raise(L, cce_condition_unimplemented);
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
    cce_raise(L, cce_condition_make_errno_clear());
  }
#else
  cce_raise(L, cce_condition_unimplemented);
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
    cce_raise(L, cce_condition_make_errno_clear());
  }
#else
  cce_raise(L, cce_condition_unimplemented);
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
    cce_raise(L, cce_condition_make_errno_clear());
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
    cce_raise(L, cce_condition_make_errno_clear());
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
    cce_raise(L, cce_condition_make_errno_clear());
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
    cce_raise(L, cce_condition_make_errno_clear());
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
    cce_raise(L, cce_condition_make_errno_clear());
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
    cce_raise(L, cce_condition_make_errno_clear());
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
    cce_raise(L, cce_condition_make_errno_clear());
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
    cce_raise(L, cce_condition_make_errno_clear());
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
    cce_raise(L, cce_condition_make_errno_clear());
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
    cce_raise(L, cce_condition_make_errno_clear());
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
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

int
cce_sys_dup (cce_location_t * L, int old)
{
  int	rv;
  errno = 0;
  rv = dup(old);
  if (-1 != rv) {
    return rv;
  } else {
    cce_raise(L, cce_condition_make_errno_clear());
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
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

void
cce_sys_pipe (cce_location_t * L, int pipefd[2])
{
  int	rv;
  errno = 0;
  rv = pipe(pipefd);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

void
cce_sys_mkfifo (cce_location_t * L, const char * pathname, mode_t mode)
{
  int	rv;
  errno = 0;
  rv = mkfifo(pathname, mode);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
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
    cce_raise(L, cce_condition_make_errno_clear());
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
    cce_raise(L, cce_condition_make_errno_clear());
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
    cce_raise(L, cce_condition_make_errno_clear());
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
    cce_raise(L, cce_condition_make_errno_clear());
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
    cce_raise(L, cce_condition_make_errno_clear());
  }
#else
  cce_raise(L, cce_condition_unimplemented);
#endif
}

void
cce_sys_madvise (cce_location_t * L, void * address, size_t length, int advice)
{
#ifdef HAVE_MADVISE
  int	rv;
  errno = 0;
  rv = madvise(address, length, advice);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
#else
  cce_raise(L, cce_condition_unimplemented);
#endif
}


/** --------------------------------------------------------------------
 ** System wrappers: file system operations.
 ** ----------------------------------------------------------------- */

void
cce_sys_getcwd (cce_location_t * L, char * buffer, size_t size)
{
  char *	rv;
  errno = 0;
  rv = getcwd(buffer, size);
  if (NULL == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

void
cce_sys_chdir (cce_location_t * L, const char * pathname)
{
  int	rv;
  errno = 0;
  rv = chdir(pathname);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

void
cce_sys_fchdir (cce_location_t * L, int dirfd)
{
  int	rv;
  errno = 0;
  rv = fchdir(dirfd);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

/* ------------------------------------------------------------------ */

DIR *
cce_sys_opendir (cce_location_t * L, const char * pathname)
{
  DIR *	rv;
  errno = 0;
  rv = opendir(pathname);
  if (NULL != rv) {
    return rv;
  } else {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

DIR *
cce_sys_fdopendir (cce_location_t * L, int dirfd)
{
  DIR *	rv;
  errno = 0;
  rv = fdopendir(dirfd);
  if (NULL != rv) {
    return rv;
  } else {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

struct dirent *
cce_sys_readdir (cce_location_t * L, DIR * dirstream)
{
  struct dirent *	rv;
  errno = 0;
  rv = readdir(dirstream);
  if (NULL != rv) {
    return rv;
  } else if (0 == errno) {
    return NULL;
  } else {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

void
cce_sys_closedir (cce_location_t * L, DIR * dirstream)
{
  int	rv;
  errno = 0;
  rv = closedir(dirstream);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

/* ------------------------------------------------------------------ */

void
cce_sys_stat (cce_location_t * L, const char * pathname, struct stat * buf)
{
  int	rv;
  errno = 0;
  rv = stat(pathname, buf);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

void
cce_sys_fstat (cce_location_t * L, int fd, struct stat * buf)
{
  int	rv;
  errno = 0;
  rv = fstat(fd, buf);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

void
cce_sys_lstat (cce_location_t * L, const char * pathname, struct stat * buf)
{
  int	rv;
  errno = 0;
  rv = lstat(pathname, buf);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
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
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

void
cce_sys_rmdir (cce_location_t * L, const char * pathname)
{
  int	rv;
  errno = 0;
  rv = rmdir(pathname);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

/* ------------------------------------------------------------------ */

void
cce_sys_link (cce_location_t * L, const char * oldname, const char * newname)
{
  int	rv;
  errno = 0;
  rv = link(oldname, newname);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

void
cce_sys_linkat (cce_location_t * L,
		int oldfd, const char * oldname,
		int newfd, const char * newname,
		int flags)
{
  int	rv;
  errno = 0;
  rv = linkat(oldfd, oldname, newfd, newname, flags);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

/* ------------------------------------------------------------------ */

void
cce_sys_symlink (cce_location_t * L, const char * oldname, const char * newname)
{
  int	rv;
  errno = 0;
  rv = symlink(oldname, newname);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

void
cce_sys_symlinkat (cce_location_t * L, const char * oldname, int newdirfd, const char * newname)
{
  int	rv;
  errno = 0;
  rv = symlinkat(oldname, newdirfd, newname);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

size_t
cce_sys_readlink (cce_location_t * L, const char * filename, char * buffer, size_t size)
{
  ssize_t	rv;
  errno = 0;
  rv = readlink(filename, buffer, size);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  } else {
    return (size_t)rv;
  }
}

size_t
cce_sys_readlinkat (cce_location_t * L, int dirfd, const char * filename, char * buffer, size_t size)
{
  ssize_t	rv;
  errno = 0;
  rv = readlinkat(dirfd, filename, buffer, size);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  } else {
    return (size_t)rv;
  }
}

char *
cce_sys_realpath (cce_location_t * L, const char * pathname, char * resolved_path)
{
  char *	rv;
  errno = 0;
  rv = realpath(pathname, resolved_path);
  if (rv) {
    return rv;
  } else {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

/* ------------------------------------------------------------------ */

void
cce_sys_unlink (cce_location_t * L, const char * pathname)
{
  int	rv;
  errno = 0;
  rv = unlink(pathname);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

void
cce_sys_unlinkat (cce_location_t * L, int dirfd, const char * pathname, int flags)
{
  int	rv;
  errno = 0;
  rv = unlinkat(dirfd, pathname, flags);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

void
cce_sys_remove (cce_location_t * L, const char * pathname)
{
  int	rv;
  errno = 0;
  rv = remove(pathname);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

/* ------------------------------------------------------------------ */

void
cce_sys_rename (cce_location_t * L, const char * oldname, const char * newname)
{
  int	rv;
  errno = 0;
  rv = rename(oldname, newname);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

/* ------------------------------------------------------------------ */

void
cce_sys_chown (cce_location_t * L, const char * pathname, uid_t owner, gid_t group)
{
  int	rv;
  errno = 0;
  rv = chown(pathname, owner, group);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

void
cce_sys_fchown (cce_location_t * L, int filedes, uid_t owner, gid_t group)
{
  int	rv;
  errno = 0;
  rv = fchown(filedes, owner, group);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

void
cce_sys_lchown (cce_location_t * L, const char * pathname, uid_t owner, gid_t group)
{
  int	rv;
  errno = 0;
  rv = lchown(pathname, owner, group);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

void
cce_sys_fchownat (cce_location_t * L, int dirfd, const char * pathname, uid_t owner, gid_t group, int flags)
{
  int	rv;
  errno = 0;
  rv = fchownat(dirfd, pathname, owner, group, flags);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

/* ------------------------------------------------------------------ */

void
cce_sys_chmod (cce_location_t * L, const char * pathname, mode_t mode)
{
  int	rv;
  errno = 0;
  rv = chmod(pathname, mode);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

void
cce_sys_fchmod (cce_location_t * L, int filedes, mode_t mode)
{
  int	rv;
  errno = 0;
  rv = fchmod(filedes, mode);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

void
cce_sys_fchmodat (cce_location_t * L, int dirfd, const char * pathname, mode_t mode, int flags)
{
  int	rv;
  errno = 0;
  rv = fchmodat(dirfd, pathname, mode, flags);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

/* ------------------------------------------------------------------ */

int
cce_sys_access (cce_location_t * L, const char * pathname, int how)
{
  int	rv;
  errno = 0;
  rv = access(pathname, how);
  if (0 == rv) {
    return rv;
  } else if (errno) {
    cce_raise(L, cce_condition_make_errno_clear());
  } else {
    return rv;
  }
}

int
cce_sys_faccessat (cce_location_t * L, int dirfd, const char * pathname, int how, int flags)
{
  int	rv;
  errno = 0;
  rv = faccessat(dirfd, pathname, how, flags);
  if (0 == rv) {
    return rv;
  } else if (errno) {
    cce_raise(L, cce_condition_make_errno_clear());
  } else {
    return rv;
  }
}

/* ------------------------------------------------------------------ */

void
cce_sys_utime (cce_location_t * L, const char * pathname, const struct utimbuf * times)
{
  int	rv;
  errno = 0;
  rv = utime(pathname, times);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

void
cce_sys_utimes (cce_location_t * L, const char * pathname, const struct timeval TVP[2])
{
  int	rv;
  errno = 0;
  rv = utimes(pathname, TVP);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

void
cce_sys_lutimes (cce_location_t * L, const char * pathname, const struct timeval TVP[2])
{
  int	rv;
  errno = 0;
  rv = lutimes(pathname, TVP);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

void
cce_sys_futimes (cce_location_t * L, int filedes, const struct timeval TVP[2])
{
  int	rv;
  errno = 0;
  rv = futimes(filedes, TVP);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

/* ------------------------------------------------------------------ */

void
cce_sys_truncate (cce_location_t * L, const char * pathname, off_t length)
{
  int	rv;
  errno = 0;
  rv = truncate(pathname, length);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

void
cce_sys_ftruncate (cce_location_t * L, int filedes, off_t length)
{
  int	rv;
  errno = 0;
  rv = ftruncate(filedes, length);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
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
    cce_raise(L, cce_condition_make_errno_clear());
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
    cce_raise(L, cce_condition_make_errno_clear());
  }
#else
  cce_raise(L, cce_condition_unimplemented);
#endif
}


/** --------------------------------------------------------------------
 ** System call wrappers: sockets.
 ** ----------------------------------------------------------------- */

void
cce_sys_bind (cce_location_t * L, int socket, struct sockaddr * addr, socklen_t length)
{
  int	rv;
  errno = 0;
  rv = bind(socket, addr, length);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

void
cce_sys_getsockname (cce_location_t * L, int socket, struct sockaddr * addr, socklen_t * length_ptr)
{
  int	rv;
  errno = 0;
  rv = getsockname(socket, addr, length_ptr);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

/* ------------------------------------------------------------------ */

void
cce_sys_inet_aton (cce_location_t * L, const char * name, struct in_addr * addr)
{
  int	rv;
  errno = 0;
  rv = inet_aton(name, addr);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

in_addr_t
cce_sys_inet_network (cce_location_t * L, const char * name)
{
  in_addr_t	rv;
  errno = 0;
  rv = inet_network(name);
  if (((in_addr_t)-1) == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  } else {
    return rv;
  }
}

/* ------------------------------------------------------------------ */

struct hostent *
cce_sys_gethostbyname (cce_location_t * L, const char * name)
{
  struct hostent *	rv;
  h_errno = 0;
  rv = gethostbyname(name);
  if (rv) {
    return rv;
  } else {
    cce_raise(L, cce_condition_make_h_errno_clear());
  }
}

struct hostent *
cce_sys_gethostbyname2 (cce_location_t * L, const char * name, int af)
{
  struct hostent *	rv;
  h_errno = 0;
  rv = gethostbyname2(name, af);
  if (rv) {
    return rv;
  } else {
    cce_raise(L, cce_condition_make_h_errno_clear());
  }
}

struct hostent *
cce_sys_gethostbyaddr (cce_location_t * L, const void * addr, socklen_t length, int format)
{
  struct hostent *	rv;
  h_errno = 0;
  rv = gethostbyaddr(addr, length, format);
  if (rv) {
    return rv;
  } else {
    cce_raise(L, cce_condition_make_h_errno_clear());
  }
}

/* ------------------------------------------------------------------ */

int
cce_sys_socket (cce_location_t * L, int namespace, int style, int protocol)
{
  int	rv;
  errno = 0;
  rv = socket(namespace, style, protocol);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  } else {
    return rv;
  }
}

void
cce_sys_shutdown (cce_location_t * L, int socket, int how)
{
  int	rv;
  errno = 0;
  rv = shutdown(socket, how);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

void
cce_sys_socketpair (cce_location_t * L, int namespace, int style, int protocol, int filedes[2])
{
  int	rv;
  errno = 0;
  rv = socketpair(namespace, style, protocol, filedes);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

/* ------------------------------------------------------------------ */

void
cce_sys_connect (cce_location_t * L, int socket, struct sockaddr * addr, socklen_t length)
{
  int	rv;
  errno = 0;
  rv = connect(socket, addr, length);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

void
cce_sys_listen (cce_location_t * L, int socket, int N)
{
  int	rv;
  errno = 0;
  rv = listen(socket, N);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

int
cce_sys_accept (cce_location_t * L, int socket, struct sockaddr * addr, socklen_t * length_ptr)
{
  int	rv;
  errno = 0;
  rv = accept(socket, addr, length_ptr);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  } else {
    return rv;
  }
}

void
cce_sys_getpeername (cce_location_t * L, int socket, struct sockaddr * addr, socklen_t * length_ptr)
{
  int	rv;
  errno = 0;
  rv = getpeername(socket, addr, length_ptr);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

size_t
cce_sys_send (cce_location_t * L, int socket, const void * buffer, size_t size, int flags)
{
  ssize_t	rv;
  errno = 0;
  rv = send(socket, buffer, size, flags);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  } else {
    return (size_t)rv;
  }
}

size_t
cce_sys_recv (cce_location_t * L, int socket, void * buffer, size_t size, int flags)
{
  ssize_t	rv;
  errno = 0;
  rv = recv(socket, buffer, size, flags);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  } else {
    return (size_t)rv;
  }
}

/* ------------------------------------------------------------------ */

size_t
cce_sys_sendto (cce_location_t * L, int socket, const void * buffer, size_t size, int flags, struct sockaddr * addr, socklen_t length)
{
  ssize_t	rv;
  errno = 0;
  rv = sendto(socket, buffer, size, flags, addr, length);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  } else {
    return (size_t)rv;
  }
}

size_t
cce_sys_recvfrom (cce_location_t * L, int socket, void * buffer, size_t size, int flags, struct sockaddr * addr, socklen_t * length_ptr)
{
  ssize_t	rv;
  errno = 0;
  rv = recvfrom(socket, buffer, size, flags, addr, length_ptr);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  } else {
    return (size_t)rv;
  }
}

/* ------------------------------------------------------------------ */

void
cce_sys_getsockopt (cce_location_t * L, int socket, int level, int optname, void * optval, socklen_t * optlen_ptr)
{
  int	rv;
  errno = 0;
  rv = getsockopt(socket, level, optname, optval, optlen_ptr);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

void
cce_sys_setsockopt (cce_location_t * L, int socket, int level, int optname, const void * optval, socklen_t optlen)
{
  int	rv;
  errno = 0;
  rv = setsockopt(socket, level, optname, optval, optlen);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}


/** --------------------------------------------------------------------
 ** System wrappers: process handling.
 ** ----------------------------------------------------------------- */

int
cce_sys_system (cce_location_t * L, const char * command)
{
  int	rv;
  errno = 0;
  rv = system(command);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  } else {
    return rv;
  }
}

pid_t
cce_sys_fork (cce_location_t * L)
{
  pid_t	rv;
  errno = 0;
  rv = fork();
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  } else {
    return rv;
  }
}

/* ------------------------------------------------------------------ */

void
cce_sys_execv (cce_location_t * L, const char * filename, char * const argv [])
{
  int	rv;
  errno = 0;
  rv = execv(filename, argv);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

void
cce_sys_execve (cce_location_t * L, const char * filename, char * const argv [], char * const env [])
{
  int	rv;
  errno = 0;
  rv = execve(filename, argv, env);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

void
cce_sys_execvp (cce_location_t * L, const char * filename, char * const argv [])
{
  int	rv;
  errno = 0;
  rv = execvp(filename, argv);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

/* ------------------------------------------------------------------ */

void
cce_sys_waitpid (cce_location_t * L, pid_t pid, int * wstatus, int options)
{
  pid_t	rv;
  errno = 0;
  rv = waitpid(pid, wstatus, options);
  if (-1 == rv) {
    cce_raise(L, cce_condition_make_errno_clear());
  }
}

/* end of file */
