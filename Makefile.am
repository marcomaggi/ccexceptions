## Process this file with automake to produce Makefile.in

ACLOCAL_AMFLAGS		= -I meta/autotools
AUTOMAKE_OPTIONS	= foreign
EXTRA_DIST		= INSTALL			\
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
	src/ccexceptions-deprecated.c		\
	src/ccexceptions-version.c

#page
#### tests

check_PROGRAMS	= \
	tests/version					\
	tests/setjmp					\
	tests/no-exceptions				\
	tests/exception-no-handlers			\
	tests/exception-with-cleanup-handler		\
	tests/exception-with-error-handler		\
	tests/exception-with-handlers			\
	tests/handlers-routines				\
	tests/handlers-as-handlers			\
	tests/conditions-raising			\
	tests/conditions-hierarchy			\
	tests/conditions-example			\
	tests/conditions-tests				\
	tests/tracing					\
	tests/retry					\
	tests/system-memory				\
	tests/sizeof					\
	\
	tests/condition-subtyping-root			\
	tests/condition-subtyping-break			\
	tests/condition-subtyping-unimplemented		\
	tests/condition-subtyping-error			\
	tests/condition-subtyping-runtime-error		\
	tests/condition-subtyping-logic-error		\
	tests/condition-subtyping-invalid-arg		\
	tests/condition-subtyping-unreachable

if WANT_GCC
check_PROGRAMS	+= \
	tests/gcc-auto-cleanup			\
	tests/exception-with-gcc-auto-cleanup
endif

TESTS				= $(check_PROGRAMS)

ccexceptions_tests_cppflags	= -I$(srcdir)/src -I$(srcdir)/tests
ccexceptions_tests_ldadd	= libccexceptions.la

## --------------------------------------------------------------------

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

tests_handlers_as_handlers_CPPFLAGS		= $(ccexceptions_tests_cppflags)
tests_handlers_as_handlers_LDADD		= $(ccexceptions_tests_ldadd)

tests_conditions_raising_CPPFLAGS		= $(ccexceptions_tests_cppflags)
tests_conditions_raising_LDADD			= $(ccexceptions_tests_ldadd)

tests_conditions_hierarchy_CPPFLAGS		= $(ccexceptions_tests_cppflags)
tests_conditions_hierarchy_LDADD		= $(ccexceptions_tests_ldadd)

tests_conditions_example_CPPFLAGS		= $(ccexceptions_tests_cppflags)
tests_conditions_example_LDADD			= $(ccexceptions_tests_ldadd)

tests_conditions_tests_CPPFLAGS			= $(ccexceptions_tests_cppflags)
tests_conditions_tests_LDADD			= $(ccexceptions_tests_ldadd)

tests_tracing_CPPFLAGS				= $(ccexceptions_tests_cppflags)
tests_tracing_LDADD				= $(ccexceptions_tests_ldadd)

tests_retry_CPPFLAGS				= $(ccexceptions_tests_cppflags)
tests_retry_LDADD				= $(ccexceptions_tests_ldadd)

tests_system_memory_CPPFLAGS			= $(ccexceptions_tests_cppflags)
tests_system_memory_LDADD			= $(ccexceptions_tests_ldadd)

tests_sizeof_CPPFLAGS				= $(ccexceptions_tests_cppflags)
tests_sizeof_LDADD				= $(ccexceptions_tests_ldadd)

## --------------------------------------------------------------------

tests_condition_subtyping_root_CPPFLAGS		= $(ccexceptions_tests_cppflags)
tests_condition_subtyping_root_LDADD		= $(ccexceptions_tests_ldadd)
tests_condition_subtyping_root_SOURCES		= \
	tests/condition-subtyping-root.c	\
	tests/condition-subtyping-root-body.c	\
	tests/condition-subtyping-root-header.h

## --------------------------------------------------------------------

tests_condition_subtyping_break_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_condition_subtyping_break_LDADD		= $(ccexceptions_tests_ldadd)
tests_condition_subtyping_break_SOURCES		= \
	tests/condition-subtyping-break.c		\
	tests/condition-subtyping-break-body.c		\
	tests/condition-subtyping-break-header.h

## --------------------------------------------------------------------

tests_condition_subtyping_unimplemented_CPPFLAGS= $(ccexceptions_tests_cppflags)
tests_condition_subtyping_unimplemented_LDADD	= $(ccexceptions_tests_ldadd)
tests_condition_subtyping_unimplemented_SOURCES	= \
	tests/condition-subtyping-unimplemented.c	\
	tests/condition-subtyping-unimplemented-body.c	\
	tests/condition-subtyping-unimplemented-header.h

## --------------------------------------------------------------------

tests_condition_subtyping_error_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_condition_subtyping_error_LDADD		= $(ccexceptions_tests_ldadd)
tests_condition_subtyping_error_SOURCES		= \
	tests/condition-subtyping-error.c	\
	tests/condition-subtyping-error-body.c	\
	tests/condition-subtyping-error-header.h

## --------------------------------------------------------------------

tests_condition_subtyping_runtime_error_CPPFLAGS= $(ccexceptions_tests_cppflags)
tests_condition_subtyping_runtime_error_LDADD	= $(ccexceptions_tests_ldadd)
tests_condition_subtyping_runtime_error_SOURCES	= \
	tests/condition-subtyping-runtime-error.c	\
	tests/condition-subtyping-runtime-error-body.c	\
	tests/condition-subtyping-runtime-error-header.h

## --------------------------------------------------------------------

tests_condition_subtyping_logic_error_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_condition_subtyping_logic_error_LDADD	= $(ccexceptions_tests_ldadd)
tests_condition_subtyping_logic_error_SOURCES	= \
	tests/condition-subtyping-logic-error.c		\
	tests/condition-subtyping-logic-error-body.c	\
	tests/condition-subtyping-logic-error-header.h

## --------------------------------------------------------------------

tests_condition_subtyping_invalid_arg_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_condition_subtyping_invalid_arg_LDADD	= $(ccexceptions_tests_ldadd)
tests_condition_subtyping_invalid_arg_SOURCES	= \
	tests/condition-subtyping-invalid-arg.c		\
	tests/condition-subtyping-invalid-arg-body.c	\
	tests/condition-subtyping-invalid-arg-header.h

## --------------------------------------------------------------------

tests_condition_subtyping_unreachable_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_condition_subtyping_unreachable_LDADD	= $(ccexceptions_tests_ldadd)
tests_condition_subtyping_unreachable_SOURCES	= \
	tests/condition-subtyping-unreachable.c		\
	tests/condition-subtyping-unreachable-body.c	\
	tests/condition-subtyping-unreachable-header.h

## --------------------------------------------------------------------

installcheck-local: $(TESTS)
	@for f in $(TESTS); do $(builddir)/$$f; done

#page
### examples

noinst_PROGRAMS	= \
	examples/plain		\
	examples/inline

ccexceptions_examples_cppflags	= -I$(srcdir)/src -I$(srcdir)/examples
ccexceptions_examples_ldadd	= libccexceptions.la

.PHONY: examples

examples: $(noinst_PROGRAMS)
	-./examples/plain
	-./examples/inline

## --------------------------------------------------------------------

examples_plain_SOURCES		=	\
	examples/plain.c		\
	examples/plain-header.h		\
	examples/plain-body.c

examples_plain_CPPFLAGS		= $(ccexceptions_examples_cppflags)
examples_plain_LDADD		= $(ccexceptions_examples_ldadd)

## --------------------------------------------------------------------

examples_inline_SOURCES		=	\
	examples/inline.c		\
	examples/inline-header.h	\
	examples/inline-body.c

examples_inline_CPPFLAGS	= $(ccexceptions_examples_cppflags)
examples_inline_LDADD		= $(ccexceptions_examples_ldadd)

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
