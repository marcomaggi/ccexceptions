dnl @configure_input@
dnl

AC_PREREQ([2.69])
AC_INIT([CCExceptions],[0.6.2-devel.1],
  [marco.maggi-ipsu@poste.it],
  [ccexceptions],[http://github.com/marcomaggi/ccexceptions/])
dnl This is the revision number of this configure.ac
AC_REVISION([0.1])
AC_COPYRIGHT([Copyright (c) 2016, 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

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
AM_INIT_AUTOMAKE([foreign dist-xz no-dist-gzip subdir-objects])
AM_MAINTAINER_MODE

AM_PROG_AR
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_MKDIR_P

LT_PREREQ([2.4])
LT_INIT

dnl page
#### configuration

dnl case "$target_os" in
dnl   *linux*)
dnl     ccexceptions_OS_LINUX=yes
dnl     AC_MSG_NOTICE([detected OS: linux])
dnl     ;;
dnl   *bsd*)
dnl     ccexceptions_OS_BSD=yes
dnl     AC_MSG_NOTICE([detected OS: BSD])
dnl     ;;
dnl   *cygwin*)
dnl     ccexceptions_OS_CYGWIN=yes
dnl     AC_MSG_NOTICE([detected OS: CYGWIN])
dnl     ;;
dnl   *darwin*)
dnl     ccexceptions_OS_DARWIN=yes
dnl     AC_MSG_NOTICE([detected OS: DARWIN])
dnl     ;;
dnl esac
dnl AM_CONDITIONAL([ON_LINUX], [test "x$ccexceptions_OS_LINUX"  = xyes])
dnl AM_CONDITIONAL([ON_BSD],   [test "x$ccexceptions_OS_BSD"    = xyes])
dnl AM_CONDITIONAL([ON_CYGWIN],[test "x$ccexceptions_OS_CYGWIN" = xyes])
dnl AM_CONDITIONAL([ON_DARWIN],[test "x$ccexceptions_OS_DARWIN" = xyes])

dnl page
#### libraries interface version

AS_VAR_SET([SLACKSTUFF_PACKAGE_VERSION],[0.6d2.1])
AC_SUBST([SLACKSTUFF_PACKAGE_VERSION])

dnl This is the version stored in the pkg-config data file.
AC_SUBST([CCEXCEPTIONS_PKG_CONFIG_VERSION],[0.6.2])

MM_LIBTOOL_LIBRARY_VERSIONS([ccexceptions],6,2,0)

dnl page
#### basic system inspection

AC_LANG([C])
AC_PROG_CC_C99

AX_CHECK_COMPILE_FLAG([-std=c11],[],[AC_MSG_ERROR([*** Compiler does not support -std=c11])],[-pedantic])

AS_VAR_SET(AX_CFLAGS,[-std=c11])
AS_VAR_APPEND(AX_CFLAGS,[" -Wall -Wextra"])
AX_GCC_VERSION
AS_IF([test "x$GCC" = "xyes"],
  [AS_CASE("$GCC_VERSION",
     [7.*],[AS_VAR_APPEND(AX_CFLAGS,[" -pedantic -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wrestrict -Wnull-dereference -Wjump-misses-init -Wdouble-promotion -Wshadow -Wformat=2 -Wmisleading-indentation"])])])
AC_SUBST(AX_CFLAGS)

AM_PROG_AS
AC_PROG_CC
AM_PROG_CC_C_O
AC_HEADER_STDC
AC_CHECK_HEADERS([assert.h stdint.h stdbool.h setjmp.h memory.h limits.h])
AC_HEADER_STDBOOL

dnl The  documentation of GNU  Autoconf states that AC_PROG_CC  sets the
dnl variable "GCC" to "yes" if the selected compiler is GCC.
AM_CONDITIONAL([WANT_GCC],[test "x$GCC" = xyes])

AC_CACHE_SAVE

dnl page
#### checks for library functions

dnl This constant is redefined in the main header file.  We define it here so
dnl that it is there in the tests below.
AC_DEFINE([_POSIX_C_SOURCE],[200809L],[Request enabling latest POSIX features.])

AC_CACHE_SAVE

dnl page
#### errno values inspection

dnl Wrapper for AC_COMPUTE_INT which computes  and caches the value of a
dnl C language constant.  For example, to compute the value of the
dnl "errno" constant EPERM we do:
dnl
dnl    CCE_VALUEOF_TEST([EPERM],[EPERM])
dnl
dnl this macro expansion: defines  the shell variable "VALUEOF_EPERM" to
dnl the    value    of    EPERM;     defines    the    shell    variable
dnl "cce_cv_valueof_EPERM" to cache the value; defines an Autoconf
dnl substitution for the symbol "VALUEOF_EPERM".
dnl
dnl $1 - the stem  to use  to define  shell variables  representing the
dnl      result of this test
dnl $2 - the name of a C language constant whose value is an integer
dnl
AC_DEFUN([CCE_VALUEOF_TEST],
  [VALUEOF_$1="-1"
   AC_CACHE_CHECK([the value of '$2'],
     [cce_cv_valueof_$1],
     [AC_COMPUTE_INT([cce_cv_valueof_$1],
        [$2],
        [#include <errno.h>
],
        [cce_cv_valueof_$1="-1"])])
    VALUEOF_$1="$cce_cv_valueof_$1"
    AC_DEFINE_UNQUOTED([VALUEOF_$1],$VALUEOF_$1,[value of constant $1])])

AC_DEFUN([CCE_ERRNO_TEST],[CCE_VALUEOF_TEST([$1],[$1])])

CCE_ERRNO_TEST([EPERM])
CCE_ERRNO_TEST([ENOENT])
CCE_ERRNO_TEST([ESRCH])
CCE_ERRNO_TEST([EINTR])
CCE_ERRNO_TEST([EIO])
CCE_ERRNO_TEST([ENXIO])
CCE_ERRNO_TEST([E2BIG])
CCE_ERRNO_TEST([ENOEXEC])
CCE_ERRNO_TEST([EBADF])
CCE_ERRNO_TEST([ECHILD])
CCE_ERRNO_TEST([EPROCLIM])
CCE_ERRNO_TEST([EAGAIN])
CCE_ERRNO_TEST([ENOMEM])
CCE_ERRNO_TEST([EACCES])
CCE_ERRNO_TEST([EFAULT])
CCE_ERRNO_TEST([ENOTBLK])
CCE_ERRNO_TEST([EBUSY])
CCE_ERRNO_TEST([EEXIST])
CCE_ERRNO_TEST([EXDEV])
CCE_ERRNO_TEST([ENODEV])
CCE_ERRNO_TEST([ENOTDIR])
CCE_ERRNO_TEST([EISDIR])
CCE_ERRNO_TEST([EINVAL])
CCE_ERRNO_TEST([ENFILE])
CCE_ERRNO_TEST([EMFILE])
CCE_ERRNO_TEST([ENOTTY])
CCE_ERRNO_TEST([ETXTBSY])
CCE_ERRNO_TEST([EFBIG])
CCE_ERRNO_TEST([ENOSPC])
CCE_ERRNO_TEST([ESPIPE])
CCE_ERRNO_TEST([EROFS])
CCE_ERRNO_TEST([EMLINK])
CCE_ERRNO_TEST([EPIPE])
CCE_ERRNO_TEST([EDOM])
CCE_ERRNO_TEST([ERANGE])
CCE_ERRNO_TEST([EDEADLK])
CCE_ERRNO_TEST([ENAMETOOLONG])
CCE_ERRNO_TEST([ENOLCK])
CCE_ERRNO_TEST([ENOSYS])
CCE_ERRNO_TEST([ENOTEMPTY])
CCE_ERRNO_TEST([ELOOP])
CCE_ERRNO_TEST([EWOULDBLOCK])
CCE_ERRNO_TEST([ENOMSG])
CCE_ERRNO_TEST([EIDRM])
CCE_ERRNO_TEST([ECHRNG])
CCE_ERRNO_TEST([EL2NSYNC])
CCE_ERRNO_TEST([EL3HLT])
CCE_ERRNO_TEST([EL3RST])
CCE_ERRNO_TEST([ELNRNG])
CCE_ERRNO_TEST([EUNATCH])
CCE_ERRNO_TEST([ENOCSI])
CCE_ERRNO_TEST([EL2HLT])
CCE_ERRNO_TEST([EBADE])
CCE_ERRNO_TEST([EBADR])
CCE_ERRNO_TEST([EXFULL])
CCE_ERRNO_TEST([ENOANO])
CCE_ERRNO_TEST([EBADRQC])
CCE_ERRNO_TEST([EBADSLT])
CCE_ERRNO_TEST([EDEADLOCK])
CCE_ERRNO_TEST([EBFONT])
CCE_ERRNO_TEST([ENOSTR])
CCE_ERRNO_TEST([ENODATA])
CCE_ERRNO_TEST([ETIME])
CCE_ERRNO_TEST([ENOSR])
CCE_ERRNO_TEST([ENONET])
CCE_ERRNO_TEST([ENOPKG])
CCE_ERRNO_TEST([EREMOTE])
CCE_ERRNO_TEST([ENOLINK])
CCE_ERRNO_TEST([EADV])
CCE_ERRNO_TEST([ESRMNT])
CCE_ERRNO_TEST([ECOMM])
CCE_ERRNO_TEST([EPROTO])
CCE_ERRNO_TEST([EMULTIHOP])
CCE_ERRNO_TEST([EDOTDOT])
CCE_ERRNO_TEST([EBADMSG])
CCE_ERRNO_TEST([EOVERFLOW])
CCE_ERRNO_TEST([ENOTUNIQ])
CCE_ERRNO_TEST([EBADFD])
CCE_ERRNO_TEST([EREMCHG])
CCE_ERRNO_TEST([ELIBACC])
CCE_ERRNO_TEST([ELIBBAD])
CCE_ERRNO_TEST([ELIBSCN])
CCE_ERRNO_TEST([ELIBMAX])
CCE_ERRNO_TEST([ELIBEXEC])
CCE_ERRNO_TEST([EILSEQ])
CCE_ERRNO_TEST([ERESTART])
CCE_ERRNO_TEST([ESTRPIPE])
CCE_ERRNO_TEST([EUSERS])
CCE_ERRNO_TEST([ENOTSOCK])
CCE_ERRNO_TEST([EDESTADDRREQ])
CCE_ERRNO_TEST([EMSGSIZE])
CCE_ERRNO_TEST([EPROTOTYPE])
CCE_ERRNO_TEST([ENOPROTOOPT])
CCE_ERRNO_TEST([EPROTONOSUPPORT])
CCE_ERRNO_TEST([ESOCKTNOSUPPORT])
CCE_ERRNO_TEST([EOPNOTSUPP])
CCE_ERRNO_TEST([EPFNOSUPPORT])
CCE_ERRNO_TEST([EAFNOSUPPORT])
CCE_ERRNO_TEST([EADDRINUSE])
CCE_ERRNO_TEST([EADDRNOTAVAIL])
CCE_ERRNO_TEST([ENETDOWN])
CCE_ERRNO_TEST([ENETUNREACH])
CCE_ERRNO_TEST([ENETRESET])
CCE_ERRNO_TEST([ECONNABORTED])
CCE_ERRNO_TEST([ECONNRESET])
CCE_ERRNO_TEST([ENOBUFS])
CCE_ERRNO_TEST([EISCONN])
CCE_ERRNO_TEST([ENOTCONN])
CCE_ERRNO_TEST([ESHUTDOWN])
CCE_ERRNO_TEST([ETOOMANYREFS])
CCE_ERRNO_TEST([ETIMEDOUT])
CCE_ERRNO_TEST([ECONNREFUSED])
CCE_ERRNO_TEST([EHOSTDOWN])
CCE_ERRNO_TEST([EHOSTUNREACH])
CCE_ERRNO_TEST([EALREADY])
CCE_ERRNO_TEST([EINPROGRESS])
CCE_ERRNO_TEST([ESTALE])
CCE_ERRNO_TEST([EUCLEAN])
CCE_ERRNO_TEST([ENOTNAM])
CCE_ERRNO_TEST([ENAVAIL])
CCE_ERRNO_TEST([EISNAM])
CCE_ERRNO_TEST([EREMOTEIO])
CCE_ERRNO_TEST([EDQUOT])
CCE_ERRNO_TEST([ENOMEDIUM])
CCE_ERRNO_TEST([EMEDIUMTYPE])
CCE_ERRNO_TEST([ECANCELED])
CCE_ERRNO_TEST([ENOKEY])
CCE_ERRNO_TEST([EKEYEXPIRED])
CCE_ERRNO_TEST([EKEYREVOKED])
CCE_ERRNO_TEST([EKEYREJECTED])
CCE_ERRNO_TEST([EOWNERDEAD])
CCE_ERRNO_TEST([ENOTRECOVERABLE])
CCE_ERRNO_TEST([EBADRPC])
CCE_ERRNO_TEST([ERPCMISMATCH])
CCE_ERRNO_TEST([EPROGUNAVAIL])
CCE_ERRNO_TEST([EPROGMISMATCH])
CCE_ERRNO_TEST([EPROCUNAVAIL])
CCE_ERRNO_TEST([EFTYPE])
CCE_ERRNO_TEST([EAUTH])
CCE_ERRNO_TEST([ENEEDAUTH])
CCE_ERRNO_TEST([ENOTSUP])
CCE_ERRNO_TEST([EBACKGROUND])
CCE_ERRNO_TEST([EDIED])
CCE_ERRNO_TEST([ENOLINK])
CCE_ERRNO_TEST([ERFKILL])
CCE_ERRNO_TEST([EHWPOISON])

dnl page
#### finish

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile]
   [meta/scripts/ccexceptions.pc]
   [meta/slackstuff/config]
   [meta/slackware/slack-desc])
AC_OUTPUT

### end of file
# Local Variables:
# mode: autoconf
# page-delimiter: "^dnl page"
# End:
