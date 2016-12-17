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
	src/ccexceptions-version.c

#page
#### tests

check_PROGRAMS	= \
	tests/version

TESTS				= $(check_PROGRAMS)

ccexceptions_tests_cppflags	= -I$(srcdir)/src
ccexceptions_tests_ldadd	= libccexceptions.la

tests_version_CPPFLAGS		= $(ccexceptions_tests_cppflags)
tests_version_LDADD		= $(ccexceptions_tests_ldadd)

installcheck-local: $(TESTS)
	@for f in $(TESTS); do $(builddir)/$$f; done

### end of file
