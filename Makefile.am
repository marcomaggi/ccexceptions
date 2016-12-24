## Process this file with automake to produce Makefile.in

ACLOCAL_AMFLAGS		= -I meta/autotools
AUTOMAKE_OPTIONS	= foreign
EXTRA_DIST		= INSTALL configure.sh
dist_doc_DATA		= README COPYING
AM_CFLAGS		= -Wall

## --------------------------------------------------------------------

EXTRA_DIST		+= meta/scripts/ccexceptions.pc.in
pkgconfigdir		= $(libdir)/pkgconfig
nodist_pkgconfig_DATA	= meta/scripts/ccexceptions.pc

## --------------------------------------------------------------------

AM_MAKEINFOFLAGS	= --no-split

info_TEXINFOS		= doc/ccexceptions.texi
doc_ccexceptions_TEXINFOS	= \
	doc/macros.texi		\
	doc/lgpl-3.0.texi	\
	doc/fdl-1.3.texi

#page
#### libraries

ccexceptions_CURRENT	= @ccexceptions_VERSION_INTERFACE_CURRENT@
ccexceptions_REVISION	= @ccexceptions_VERSION_INTERFACE_REVISION@
ccexceptions_AGE	= @ccexceptions_VERSION_INTERFACE_AGE@

include_HEADERS		= src/ccexceptions.h

lib_LTLIBRARIES		= libccexceptions.la
libccexceptions_la_LDFLAGS= -version-info $(ccexceptions_CURRENT):$(ccexceptions_REVISION):$(ccexceptions_AGE)
libccexceptions_la_SOURCES= \
	src/ccexceptions.h		\
	src/ccexceptions-internals.h	\
	src/ccexceptions-locations.c	\
	src/ccexceptions-version.c

#page
#### tests

check_PROGRAMS	= \
	tests/version				\
	tests/setjmp				\
	tests/no-exceptions			\
	tests/exception-no-handlers		\
	tests/exception-with-cleanup-handler	\
	tests/exception-with-error-handler	\
	tests/exception-with-handlers		\
	tests/exception-with-gcc-auto-cleanup

TESTS				= $(check_PROGRAMS)

ccexceptions_tests_cppflags	= -I$(srcdir)/src
ccexceptions_tests_ldadd	= libccexceptions.la

tests_version_CPPFLAGS				= $(ccexceptions_tests_cppflags)
tests_version_LDADD				= $(ccexceptions_tests_ldadd)

tests_setjmp_CPPFLAGS				= $(ccexceptions_tests_cppflags)
tests_setjmp_LDADD				= $(ccexceptions_tests_ldadd)

tests_no_exceptions_CPPFLAGS			= $(ccexceptions_tests_cppflags)
tests_no_exceptions_LDADD			= $(ccexceptions_tests_ldadd)

tests_exception_no_handlers_CPPFLAGS		= $(ccexceptions_tests_cppflags)
tests_exception_no_handlers_LDADD		= $(ccexceptions_tests_ldadd)

tests_exception_with_cleanup_handler_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_exception_with_cleanup_handler_LDADD	= $(ccexceptions_tests_ldadd)

tests_exception_with_error_handler_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_exception_with_error_handler_LDADD	= $(ccexceptions_tests_ldadd)

tests_exception_with_handlers_CPPFLAGS		= $(ccexceptions_tests_cppflags)
tests_exception_with_handlers_LDADD		= $(ccexceptions_tests_ldadd)

tests_exception_with_gcc_auto_cleanup_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_exception_with_gcc_auto_cleanup_LDADD	= $(ccexceptions_tests_ldadd)

installcheck-local: $(TESTS)
	@for f in $(TESTS); do $(builddir)/$$f; done

### end of file
