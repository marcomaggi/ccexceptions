### @configure_input@
#

AC_PREREQ([2.69])
MMUX_PKG_VERSIONS([0],[10],[0],[devel.5])
AC_INIT([CCExceptions],[MMUX_PACKAGE_VERSION],
  [mrc.mgg@gmail.com],
  [ccexceptions],[http://github.com/marcomaggi/ccexceptions/])
MMUX_INIT
MMUX_LIBTOOL_LIBRARY_VERSIONS([ccexceptions],10,0,0)
AC_REVISION([1.0])
AC_COPYRIGHT([Copyright (c) 2016-2020 Marco Maggi <mrc.mgg@gmail.com>

This program is free software: you  can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published by
the Free  Software Foundation, either version  3 of the License,  or (at
your option) any later version.

This program  is distributed  in the  hope that it  will be  useful, but
WITHOUT   ANY   WARRANTY;  without   even   the   implied  warranty   of
MERCHANTABILITY  or  FITNESS FOR  A  PARTICULAR  PURPOSE.  See  the  GNU
General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
])
AC_CONFIG_SRCDIR([src/])
AC_CONFIG_MACRO_DIR([meta/autotools])
AC_CONFIG_AUX_DIR([meta/autotools])
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE([1.16 foreign subdir-objects])
AM_MAINTAINER_MODE

AM_PROG_AR
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_MKDIR_P

LT_PREREQ([2.4])
LT_INIT


#### basic system inspection

MMUX_CHECK_TARGET_OS
AX_IS_RELEASE([git-directory])

AC_LANG([C])
MMUX_LANG_C11

AM_PROG_AS
AM_PROG_CC_C_O
AC_HEADER_STDC
AC_CHECK_HEADERS([assert.h stdint.h stdbool.h setjmp.h memory.h limits.h])
AC_HEADER_STDBOOL

dnl The  documentation of GNU  Autoconf states that AC_PROG_CC  sets the
dnl variable "GCC" to "yes" if the selected compiler is GCC.
AM_CONDITIONAL([WANT_GCC],[test "x$GCC" = xyes])

dnl This constant is redefined in the main header file.  We define it here so
dnl that it is there in the tests below.
AC_DEFINE([_POSIX_C_SOURCE],[200809L],[Request enabling latest POSIX features.])

CCLIB_CONFIG_SETUP()

AC_CACHE_SAVE


#### external libraries

PKG_PREREQ([0.29])
PKG_INSTALLDIR


#### errno values inspection

CCEXCEPTIONS_ERRNO_TESTS([E2BIG],[EACCES],[EADDRINUSE],[EADDRNOTAVAIL],
  [EADV],[EAFNOSUPPORT],[EAGAIN],[EALREADY],[EAUTH],[EBACKGROUND],[EBADE],
  [EBADFD],[EBADF],[EBADMSG],[EBADRPC],[EBADRQC],[EBADR],[EBADSLT],[EBFONT],
  [EBUSY],[ECANCELED],[ECHILD],[ECHRNG],[ECOMM],[ECONNABORTED],[ECONNREFUSED],
  [ECONNRESET],[EDEADLK],[EDEADLOCK],[EDESTADDRREQ],[EDIED],[EDOM],[EDOTDOT],
  [EDQUOT],[EEXIST],[EFAULT],[EFBIG],[EFTYPE],[EHOSTDOWN],[EHOSTUNREACH],
  [EHWPOISON],[EIDRM],[EILSEQ],[EINPROGRESS],[EINTR],[EINVAL],[EIO],[EISCONN],
  [EISDIR],[EISNAM],[EKEYEXPIRED],[EKEYREJECTED],[EKEYREVOKED],[EL2HLT],[EL2NSYNC],
  [EL3HLT],[EL3RST],[ELIBACC],[ELIBBAD],[ELIBEXEC],[ELIBMAX],[ELIBSCN],[ELNRNG],
  [ELOOP],[EMEDIUMTYPE],[EMFILE],[EMLINK],[EMSGSIZE],[EMULTIHOP],[ENAMETOOLONG],
  [ENAVAIL],[ENEEDAUTH],[ENETDOWN],[ENETRESET],[ENETUNREACH],[ENFILE],[ENOANO],
  [ENOBUFS],[ENOCSI],[ENODATA],[ENODEV],[ENOENT],[ENOEXEC],[ENOKEY],[ENOLCK],
  [ENOLINK],[ENOMEDIUM],[ENOMEM],[ENOMSG],[ENONET],[ENOPKG],[ENOPROTOOPT],
  [ENOSPC],[ENOSR],[ENOSTR],[ENOSYS],[ENOTBLK],[ENOTCONN],[ENOTDIR],[ENOTEMPTY],
  [ENOTNAM],[ENOTRECOVERABLE],[ENOTSOCK],[ENOTSUP],[ENOTTY],[ENOTUNIQ],[ENXIO],
  [EOPNOTSUPP],[EOVERFLOW],[EOWNERDEAD],[EPERM],[EPFNOSUPPORT],[EPIPE],[EPROCLIM],
  [EPROCUNAVAIL],[EPROGMISMATCH],[EPROGUNAVAIL],[EPROTONOSUPPORT],[EPROTOTYPE],
  [EPROTO],[ERANGE],[EREMCHG],[EREMOTEIO],[EREMOTE],[ERESTART],[ERFKILL],[EROFS],
  [ERPCMISMATCH],[ESHUTDOWN],[ESOCKTNOSUPPORT],[ESPIPE],[ESRCH],[ESRMNT],[ESTALE],
  [ESTRPIPE],[ETIMEDOUT],[ETIME],[ETOOMANYREFS],[ETXTBSY],[EUCLEAN],[EUNATCH],
  [EUSERS],[EWOULDBLOCK],[EXDEV],[EXFULL])


#### finish

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile]
  [meta/scripts/ccexceptions.pc]
  [meta/slackware/slack-desc])
MMUX_OUTPUT
AC_OUTPUT

### end of file
