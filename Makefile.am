## Process this file with automake to produce Makefile.in

ACLOCAL_AMFLAGS		= -I meta/autotools
AUTOMAKE_OPTIONS	= foreign
EXTRA_DIST		= INSTALL configure.sh		\
			  meta/slackstuff/config.in	\
			  meta/slackware/slack-desc.in
dist_doc_DATA		= README COPYING
AM_CFLAGS		= -I$(srcdir)/src -Wall $(AX_CFLAGS)

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
	src/ccexceptions.h			\
	src/ccexceptions-internals.h		\
	src/ccexceptions-locations.c		\
	src/ccexceptions-conditions.c		\
	src/ccexceptions-system.c		\
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
	tests/handlers-routines			\
	tests/conditions-raising		\
	tests/conditions-hierarchy		\
	tests/conditions-example		\
	tests/conditions-tests			\
	tests/sizeof				\
	\
	tests/break-subtyping			\
	tests/unimplemented-subtyping		\
	tests/error-subtyping			\
	tests/runtime-error-subtyping

if WANT_GCC
check_PROGRAMS	+= \
	tests/gcc-auto-cleanup			\
	tests/exception-with-gcc-auto-cleanup
endif

TESTS				= $(check_PROGRAMS)

ccexceptions_tests_cppflags	= -I$(srcdir)/src
ccexceptions_tests_ldadd	= libccexceptions.la

tests_version_CPPFLAGS				= $(ccexceptions_tests_cppflags)
tests_version_LDADD				= $(ccexceptions_tests_ldadd)

tests_setjmp_CPPFLAGS				= $(ccexceptions_tests_cppflags)
tests_setjmp_LDADD				= $(ccexceptions_tests_ldadd)

tests_gcc_auto_cleanup_CPPFLAGS			= $(ccexceptions_tests_cppflags)
tests_gcc_auto_cleanup_LDADD			= $(ccexceptions_tests_ldadd)

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

tests_handlers_routines_CPPFLAGS		= $(ccexceptions_tests_cppflags)
tests_handlers_routines_LDADD			= $(ccexceptions_tests_ldadd)

tests_conditions_raising_CPPFLAGS		= $(ccexceptions_tests_cppflags)
tests_conditions_raising_LDADD			= $(ccexceptions_tests_ldadd)

tests_conditions_hierarchy_CPPFLAGS		= $(ccexceptions_tests_cppflags)
tests_conditions_hierarchy_LDADD		= $(ccexceptions_tests_ldadd)

tests_conditions_example_CPPFLAGS		= $(ccexceptions_tests_cppflags)
tests_conditions_example_LDADD			= $(ccexceptions_tests_ldadd)

tests_conditions_tests_CPPFLAGS			= $(ccexceptions_tests_cppflags)
tests_conditions_tests_LDADD			= $(ccexceptions_tests_ldadd)

tests_sizeof_CPPFLAGS				= $(ccexceptions_tests_cppflags)
tests_sizeof_LDADD				= $(ccexceptions_tests_ldadd)

## --------------------------------------------------------------------

tests_break_subtyping_CPPFLAGS			= $(ccexceptions_tests_cppflags)
tests_break_subtyping_LDADD			= $(ccexceptions_tests_ldadd)
tests_break_subtyping_SOURCES			= \
	tests/break-subtyping.c		\
	tests/break-subtyping-body.c	\
	tests/break-subtyping-header.h

## --------------------------------------------------------------------

tests_unimplemented_subtyping_CPPFLAGS		= $(ccexceptions_tests_cppflags)
tests_unimplemented_subtyping_LDADD		= $(ccexceptions_tests_ldadd)
tests_unimplemented_subtyping_SOURCES		= \
	tests/unimplemented-subtyping.c		\
	tests/unimplemented-subtyping-body.c	\
	tests/unimplemented-subtyping-header.h

## --------------------------------------------------------------------

tests_error_subtyping_CPPFLAGS			= $(ccexceptions_tests_cppflags)
tests_error_subtyping_LDADD			= $(ccexceptions_tests_ldadd)
tests_error_subtyping_SOURCES			= \
	tests/error-subtyping.c		\
	tests/error-subtyping-body.c	\
	tests/error-subtyping-header.h

## --------------------------------------------------------------------

tests_runtime_error_subtyping_CPPFLAGS		= $(ccexceptions_tests_cppflags)
tests_runtime_error_subtyping_LDADD		= $(ccexceptions_tests_ldadd)
tests_runtime_error_subtyping_SOURCES		= \
	tests/runtime-error-subtyping.c		\
	tests/runtime-error-subtyping-body.c	\
	tests/runtime-error-subtyping-header.h

## --------------------------------------------------------------------

installcheck-local: $(TESTS)
	@for f in $(TESTS); do $(builddir)/$$f; done

#page
#### Coverity support
#
# First run  "make clean",  then run "make  coverity" to  generate the
# report.  Remember  to put  in the  PATH the  directory in  which the
# Coverity tools are installed.
#
# The tool  will use  a temporary directory  "$(builddir)/cov-int"; we
# must *not* change this pathname.
#
# To generate and submit a report we must do:
#
#    $ make clean
#    $ make coverity-scan
#    $ make coverity-archive
#    $ make coverity-upload
#
# after "make  coverity-scan" we should  check that the last  lines of
# the file "cov-int/build-log.txt" report a successful build.
#
# Notice that if your Linux kernel is  at version 4.8 or above we have
# to first issue the command:
#
#    $ sudo /sbin/sysctl vsyscall=emulate
#
# to make the Coverity tools work.
#

CCEXCEPTIONS_COVERITY_TOKEN_FILE = /home/unsafe-users/marco-devel/.coverity-ccexceptions-token

.PHONY: coverity-scan coverity-archive coverity-upload

coverity-scan:
	cov-build --dir cov-int make -j 4

coverity-archive:
	tar caf ccexceptions.xz cov-int

coverity-upload:
	curl --form token=$$(<$(CCEXCEPTIONS_COVERITY_TOKEN_FILE)) \
	     --form email='marco.maggi-ipsu@poste.it' \
	     --form file='@ccexceptions.xz' \
	     --form version="$(VERSION)" \
	     --form description="A build description" \
	     'https://scan.coverity.com/builds?project=marcomaggi%2Fccexceptions'

#page
#### Static analysis with Clang's Static Analyzer
#
# See the documentation for the command line tool at:
#
#    <http://clang-analyzer.llvm.org/scan-build.html>
#
# To run the tool we must do:
#
#    $ make clean
#    $ make clang-static-analysis
#
# The  program  "scan-build"  works  by  overriding  the  CC  and  CXX
# environment variables.  Automake defines CXX as:
#
#    CXX = g++ -std=c++11
#
# so we override CXXFLAGS to include the language specification.
#

.PHONY: clang-static-analysis

clang-static-analysis:
	scan-build make CXXFLAGS='-std=c++11'

### end of file
