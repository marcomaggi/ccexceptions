## Process this file with automake to produce Makefile.in

ACLOCAL_AMFLAGS		= -I meta/autotools
AUTOMAKE_OPTIONS	= foreign
EXTRA_DIST		= INSTALL			\
			  meta/slackware/slack-desc.in
dist_doc_DATA		= README COPYING
AM_CFLAGS		= $(MMUX_CFLAGS)
AM_CPPFLAGS		= -I$(srcdir)/src -I$(builddir)/src
CLEANFILES		=

## --------------------------------------------------------------------

nodist_pkgconfig_DATA	= meta/scripts/ccexceptions.pc


#### documentation

EXTRA_DIST		+= doc/cclibraries.style.css
CLEANFILES		+= doc/cclibraries.css

AM_MAKEINFOFLAGS	= --no-split
AM_MAKEINFOHTMLFLAGS	= --split=node -I $(srcdir)/examples -c WORDS_IN_PAGE=0 --css-ref=cclibraries.css \
	-c PRE_BODY_CLOSE="<p>This document describes version <tt>$(PACKAGE_VERSION)</tt> of <em>$(PACKAGE_NAME)</em>.</p>"

info_TEXINFOS		= doc/ccexceptions.texi
doc_ccexceptions_TEXINFOS	= \
	doc/macros.texi			\
	doc/ccexceptions-macros.texi	\
	doc/overview-linking.texi	\
	doc/lgpl-3.0.texi		\
	doc/fdl-1.3.texi		\
	\
	doc/condition-example-plain.texi

## --------------------------------------------------------------------

doc/ccexceptions.html/$(am__dirstamp): doc/$(am__dirstamp)
	@$(MKDIR_P) doc/ccexceptions.html/
	@: > doc/ccexceptions.html/$(am__dirstamp)

doc/ccexceptions.html/cclibraries.css: doc/cclibraries.style.css doc/ccexceptions.html/$(am__dirstamp)
	$(INSTALL) -m 0444 "$(top_srcdir)/doc/cclibraries.style.css" "$(builddir)/doc/ccexceptions.html/cclibraries.css"

## --------------------------------------------------------------------

html-local: doc/ccexceptions.html/cclibraries.css

install-html-local:
	$(MKDIR_P) "$(DESTDIR)$(htmldir)/ccexceptions.html/"
	$(INSTALL) -m 0444 $(builddir)/doc/ccexceptions.html/cclibraries.css "$(DESTDIR)$(htmldir)/ccexceptions.html/"


#### libraries

ccexceptions_CURRENT		= @ccexceptions_VERSION_INTERFACE_CURRENT@
ccexceptions_REVISION		= @ccexceptions_VERSION_INTERFACE_REVISION@
ccexceptions_AGE		= @ccexceptions_VERSION_INTERFACE_AGE@
ccexceptions_LINKER_VERSION	= -version-info $(ccexceptions_CURRENT):$(ccexceptions_REVISION):$(ccexceptions_AGE)

include_HEADERS			= \
	src/cclibraries.h			\
	src/ccexceptions.h			\
	src/ccexceptions-handlers.h		\
	src/ccexceptions-conditions.h		\
	src/ccexceptions-cclib-conditions.h

lib_LTLIBRARIES			= libccexceptions.la
libccexceptions_la_LDFLAGS	= $(ccexceptions_LINKER_VERSION)
libccexceptions_la_SOURCES	= \
	src/cclibraries.h			\
	src/ccexceptions.h			\
	src/ccexceptions-handlers.h		\
	src/ccexceptions-conditions.h		\
	src/ccexceptions-cclib-conditions.h	\
	src/ccexceptions-internals.h		\
	src/ccexceptions-locations.c		\
	src/ccexceptions-conditions.c		\
	src/ccexceptions-system.c		\
	src/ccexceptions-deprecated.c		\
	src/ccexceptions-version.c

.PHONY: library

library: libccexceptions.la


#### tests

check_PROGRAMS	= \
	tests/version						\
	tests/setjmp						\
	tests/no-exceptions					\
	tests/exception-no-handlers				\
	tests/exception-with-clean-handler			\
	tests/exception-with-error-handler			\
	tests/exception-with-handlers				\
	tests/handlers-routines					\
	tests/handlers-as-handlers				\
	tests/conditions-raising				\
	tests/conditions-example				\
	tests/conditions-tests					\
	tests/tracing						\
	tests/retry						\
	tests/system-memory					\
	tests/destructors					\
	tests/test-cclibraries					\
	tests/sizeof						\
								\
	tests/test-condition-subtyping-root			\
	tests/test-condition-subtyping-break			\
	tests/test-condition-subtyping-unimplemented		\
	tests/test-condition-subtyping-error			\
	tests/test-condition-subtyping-runtime-error		\
	tests/test-condition-subtyping-logic-error		\
	tests/test-condition-subtyping-invalid-arg		\
	tests/test-condition-subtyping-unreachable		\
	tests/test-condition-subtyping-math-error		\
	tests/test-condition-subtyping-math-nan			\
	tests/test-condition-subtyping-math-infinity		\
	tests/test-condition-subtyping-math-overflow		\
	tests/test-condition-subtyping-math-underflow		\
	tests/test-condition-subtyping-errno			\
								\
	tests/test-condition-subtyping-root-cclib		\
	tests/test-condition-subtyping-break-cclib		\
	tests/test-condition-subtyping-unimplemented-cclib	\
	tests/test-condition-subtyping-error-cclib		\
	tests/test-condition-subtyping-runtime-error-cclib	\
	tests/test-condition-subtyping-logic-error-cclib	\
	tests/test-condition-subtyping-invalid-arg-cclib	\
	tests/test-condition-subtyping-unreachable-cclib	\
	tests/test-condition-subtyping-math-error-cclib		\
	tests/test-condition-subtyping-math-nan-cclib		\
	tests/test-condition-subtyping-math-infinity-cclib	\
	tests/test-condition-subtyping-math-overflow-cclib	\
	tests/test-condition-subtyping-math-underflow-cclib	\
	tests/test-condition-subtyping-errno-cclib

if WANT_GCC
check_PROGRAMS	+= \
	tests/gcc-auto-cleanup			\
	tests/exception-with-gcc-auto-cleanup
endif

TESTS				= $(check_PROGRAMS)

ccexceptions_tests_cppflags	= $(AM_CPPFLAGS) -I$(srcdir)/tests
ccexceptions_tests_ldadd	= $(AM_LDFLAGS) libccexceptions.la

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

tests_exception_with_clean_handler_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_exception_with_clean_handler_LDADD	= $(ccexceptions_tests_ldadd)

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

tests_conditions_example_CPPFLAGS		= $(ccexceptions_tests_cppflags)
tests_conditions_example_LDADD			= $(ccexceptions_tests_ldadd)

tests_conditions_tests_CPPFLAGS			= $(ccexceptions_tests_cppflags)
tests_conditions_tests_LDADD			= $(ccexceptions_tests_ldadd)

tests_tracing_CPPFLAGS				= $(ccexceptions_tests_cppflags)
tests_tracing_LDADD				= $(ccexceptions_tests_ldadd)

tests_retry_CPPFLAGS				= $(ccexceptions_tests_cppflags)
tests_retry_LDADD				= $(ccexceptions_tests_ldadd)

tests_destructors_CPPFLAGS			= $(ccexceptions_tests_cppflags)
tests_destructors_LDADD				= $(ccexceptions_tests_ldadd)

tests_system_memory_CPPFLAGS			= $(ccexceptions_tests_cppflags)
tests_system_memory_LDADD			= $(ccexceptions_tests_ldadd)

tests_test_cclibraries_CPPFLAGS			= $(ccexceptions_tests_cppflags)
tests_test_cclibraries_LDADD			= $(ccexceptions_tests_ldadd)

tests_sizeof_CPPFLAGS				= $(ccexceptions_tests_cppflags)
tests_sizeof_LDADD				= $(ccexceptions_tests_ldadd)

## --------------------------------------------------------------------

tests_test_condition_subtyping_root_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_test_condition_subtyping_root_LDADD	= $(ccexceptions_tests_ldadd)
tests_test_condition_subtyping_root_SOURCES	=	\
	tests/test-condition-subtyping-root.c		\
	tests/condition-subtyping-root.c		\
	tests/condition-subtyping-root.h

tests_test_condition_subtyping_root_cclib_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_test_condition_subtyping_root_cclib_LDADD		= $(ccexceptions_tests_ldadd)
tests_test_condition_subtyping_root_cclib_SOURCES	=	\
	tests/test-condition-subtyping-root-cclib.c		\
	tests/condition-subtyping-root-cclib.c			\
	tests/condition-subtyping-root-cclib.h

## --------------------------------------------------------------------

tests_test_condition_subtyping_break_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_test_condition_subtyping_break_LDADD	= $(ccexceptions_tests_ldadd)
tests_test_condition_subtyping_break_SOURCES	=	\
	tests/test-condition-subtyping-break.c		\
	tests/condition-subtyping-break.c		\
	tests/condition-subtyping-break.h

tests_test_condition_subtyping_break_cclib_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_test_condition_subtyping_break_cclib_LDADD	= $(ccexceptions_tests_ldadd)
tests_test_condition_subtyping_break_cclib_SOURCES	=	\
	tests/test-condition-subtyping-break-cclib.c		\
	tests/condition-subtyping-break-cclib.c			\
	tests/condition-subtyping-break-cclib.h

## --------------------------------------------------------------------

tests_test_condition_subtyping_unimplemented_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_test_condition_subtyping_unimplemented_LDADD	= $(ccexceptions_tests_ldadd)
tests_test_condition_subtyping_unimplemented_SOURCES	=	\
	tests/test-condition-subtyping-unimplemented.c		\
	tests/condition-subtyping-unimplemented.c		\
	tests/condition-subtyping-unimplemented.h

tests_test_condition_subtyping_unimplemented_cclib_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_test_condition_subtyping_unimplemented_cclib_LDADD	= $(ccexceptions_tests_ldadd)
tests_test_condition_subtyping_unimplemented_cclib_SOURCES	=	\
	tests/test-condition-subtyping-unimplemented-cclib.c		\
	tests/condition-subtyping-unimplemented-cclib.c			\
	tests/condition-subtyping-unimplemented-cclib.h

## --------------------------------------------------------------------

tests_test_condition_subtyping_error_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_test_condition_subtyping_error_LDADD	= $(ccexceptions_tests_ldadd)
tests_test_condition_subtyping_error_SOURCES	=	\
	tests/test-condition-subtyping-error.c		\
	tests/condition-subtyping-error.c		\
	tests/condition-subtyping-error.h

tests_test_condition_subtyping_error_cclib_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_test_condition_subtyping_error_cclib_LDADD	= $(ccexceptions_tests_ldadd)
tests_test_condition_subtyping_error_cclib_SOURCES	=	\
	tests/test-condition-subtyping-error-cclib.c		\
	tests/condition-subtyping-error-cclib.c			\
	tests/condition-subtyping-error-cclib.h

## --------------------------------------------------------------------

tests_test_condition_subtyping_runtime_error_CPPFLAGS= $(ccexceptions_tests_cppflags)
tests_test_condition_subtyping_runtime_error_LDADD	= $(ccexceptions_tests_ldadd)
tests_test_condition_subtyping_runtime_error_SOURCES	=	\
	tests/test-condition-subtyping-runtime-error.c		\
	tests/condition-subtyping-runtime-error.c		\
	tests/condition-subtyping-runtime-error.h

tests_test_condition_subtyping_runtime_error_cclib_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_test_condition_subtyping_runtime_error_cclib_LDADD	= $(ccexceptions_tests_ldadd)
tests_test_condition_subtyping_runtime_error_cclib_SOURCES	=	\
	tests/test-condition-subtyping-runtime-error-cclib.c		\
	tests/condition-subtyping-runtime-error-cclib.c			\
	tests/condition-subtyping-runtime-error-cclib.h

## --------------------------------------------------------------------

tests_test_condition_subtyping_logic_error_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_test_condition_subtyping_logic_error_LDADD	= $(ccexceptions_tests_ldadd)
tests_test_condition_subtyping_logic_error_SOURCES	=	\
	tests/test-condition-subtyping-logic-error.c		\
	tests/condition-subtyping-logic-error.c			\
	tests/condition-subtyping-logic-error.h

tests_test_condition_subtyping_logic_error_cclib_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_test_condition_subtyping_logic_error_cclib_LDADD		= $(ccexceptions_tests_ldadd)
tests_test_condition_subtyping_logic_error_cclib_SOURCES	=	\
	tests/test-condition-subtyping-logic-error-cclib.c		\
	tests/condition-subtyping-logic-error-cclib.c			\
	tests/condition-subtyping-logic-error-cclib.h

## --------------------------------------------------------------------

tests_test_condition_subtyping_invalid_arg_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_test_condition_subtyping_invalid_arg_LDADD	= $(ccexceptions_tests_ldadd)
tests_test_condition_subtyping_invalid_arg_SOURCES	=	\
	tests/test-condition-subtyping-invalid-arg.c		\
	tests/condition-subtyping-invalid-arg.c			\
	tests/condition-subtyping-invalid-arg.h

tests_test_condition_subtyping_invalid_arg_cclib_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_test_condition_subtyping_invalid_arg_cclib_LDADD		= $(ccexceptions_tests_ldadd)
tests_test_condition_subtyping_invalid_arg_cclib_SOURCES	=	\
	tests/test-condition-subtyping-invalid-arg-cclib.c		\
	tests/condition-subtyping-invalid-arg-cclib.c			\
	tests/condition-subtyping-invalid-arg-cclib.h

## --------------------------------------------------------------------

tests_test_condition_subtyping_unreachable_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_test_condition_subtyping_unreachable_LDADD	= $(ccexceptions_tests_ldadd)
tests_test_condition_subtyping_unreachable_SOURCES	=	\
	tests/test-condition-subtyping-unreachable.c		\
	tests/condition-subtyping-unreachable.c			\
	tests/condition-subtyping-unreachable.h

tests_test_condition_subtyping_unreachable_cclib_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_test_condition_subtyping_unreachable_cclib_LDADD		= $(ccexceptions_tests_ldadd)
tests_test_condition_subtyping_unreachable_cclib_SOURCES	=	\
	tests/test-condition-subtyping-unreachable-cclib.c		\
	tests/condition-subtyping-unreachable-cclib.c			\
	tests/condition-subtyping-unreachable-cclib.h

## --------------------------------------------------------------------

tests_test_condition_subtyping_math_error_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_test_condition_subtyping_math_error_LDADD		= $(ccexceptions_tests_ldadd)
tests_test_condition_subtyping_math_error_SOURCES	=	\
	tests/test-condition-subtyping-math-error.c		\
	tests/condition-subtyping-math-error.c			\
	tests/condition-subtyping-math-error.h

tests_test_condition_subtyping_math_error_cclib_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_test_condition_subtyping_math_error_cclib_LDADD		= $(ccexceptions_tests_ldadd)
tests_test_condition_subtyping_math_error_cclib_SOURCES		=	\
	tests/test-condition-subtyping-math-error-cclib.c		\
	tests/condition-subtyping-math-error-cclib.c			\
	tests/condition-subtyping-math-error-cclib.h

## --------------------------------------------------------------------

tests_test_condition_subtyping_math_nan_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_test_condition_subtyping_math_nan_LDADD		= $(ccexceptions_tests_ldadd)
tests_test_condition_subtyping_math_nan_SOURCES		=	\
	tests/test-condition-subtyping-math-nan.c		\
	tests/condition-subtyping-math-nan.c			\
	tests/condition-subtyping-math-nan.h

tests_test_condition_subtyping_math_nan_cclib_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_test_condition_subtyping_math_nan_cclib_LDADD	= $(ccexceptions_tests_ldadd)
tests_test_condition_subtyping_math_nan_cclib_SOURCES	=	\
	tests/test-condition-subtyping-math-nan-cclib.c		\
	tests/condition-subtyping-math-nan-cclib.c		\
	tests/condition-subtyping-math-nan-cclib.h

## --------------------------------------------------------------------

tests_test_condition_subtyping_math_infinity_CPPFLAGS= $(ccexceptions_tests_cppflags)
tests_test_condition_subtyping_math_infinity_LDADD	= $(ccexceptions_tests_ldadd)
tests_test_condition_subtyping_math_infinity_SOURCES	=	\
	tests/test-condition-subtyping-math-infinity.c		\
	tests/condition-subtyping-math-infinity.c		\
	tests/condition-subtyping-math-infinity.h

tests_test_condition_subtyping_math_infinity_cclib_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_test_condition_subtyping_math_infinity_cclib_LDADD	= $(ccexceptions_tests_ldadd)
tests_test_condition_subtyping_math_infinity_cclib_SOURCES	=	\
	tests/test-condition-subtyping-math-infinity-cclib.c		\
	tests/condition-subtyping-math-infinity-cclib.c			\
	tests/condition-subtyping-math-infinity-cclib.h

## --------------------------------------------------------------------

tests_test_condition_subtyping_math_overflow_CPPFLAGS= $(ccexceptions_tests_cppflags)
tests_test_condition_subtyping_math_overflow_LDADD	= $(ccexceptions_tests_ldadd)
tests_test_condition_subtyping_math_overflow_SOURCES	=	\
	tests/test-condition-subtyping-math-overflow.c		\
	tests/condition-subtyping-math-overflow.c		\
	tests/condition-subtyping-math-overflow.h

tests_test_condition_subtyping_math_overflow_cclib_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_test_condition_subtyping_math_overflow_cclib_LDADD	= $(ccexceptions_tests_ldadd)
tests_test_condition_subtyping_math_overflow_cclib_SOURCES	=	\
	tests/test-condition-subtyping-math-overflow-cclib.c		\
	tests/condition-subtyping-math-overflow-cclib.c			\
	tests/condition-subtyping-math-overflow-cclib.h

## --------------------------------------------------------------------

tests_test_condition_subtyping_math_underflow_CPPFLAGS= $(ccexceptions_tests_cppflags)
tests_test_condition_subtyping_math_underflow_LDADD	= $(ccexceptions_tests_ldadd)
tests_test_condition_subtyping_math_underflow_SOURCES	=	\
	tests/test-condition-subtyping-math-underflow.c		\
	tests/condition-subtyping-math-underflow.c		\
	tests/condition-subtyping-math-underflow.h

tests_test_condition_subtyping_math_underflow_cclib_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_test_condition_subtyping_math_underflow_cclib_LDADD	= $(ccexceptions_tests_ldadd)
tests_test_condition_subtyping_math_underflow_cclib_SOURCES	=	\
	tests/test-condition-subtyping-math-underflow-cclib.c		\
	tests/condition-subtyping-math-underflow-cclib.c		\
	tests/condition-subtyping-math-underflow-cclib.h

## --------------------------------------------------------------------

tests_test_condition_subtyping_errno_CPPFLAGS		= $(ccexceptions_tests_cppflags)
tests_test_condition_subtyping_errno_LDADD		= $(ccexceptions_tests_ldadd)
tests_test_condition_subtyping_errno_SOURCES		=	\
	tests/test-condition-subtyping-errno.c			\
	tests/condition-subtyping-errno.c			\
	tests/condition-subtyping-errno.h

tests_test_condition_subtyping_errno_cclib_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_test_condition_subtyping_errno_cclib_LDADD	= $(ccexceptions_tests_ldadd)
tests_test_condition_subtyping_errno_cclib_SOURCES	=	\
	tests/test-condition-subtyping-errno-cclib.c		\
	tests/condition-subtyping-errno-cclib.c			\
	tests/condition-subtyping-errno-cclib.h

## --------------------------------------------------------------------

installcheck-local: $(TESTS)
	@for f in $(TESTS); do $(builddir)/$$f; done


### examples

examplesdir		= $(docdir)/examples
dist_examples_DATA	=				\
	examples/plain-condition-object.h		\
	examples/plain-condition-object.c		\
	examples/test-plain-condition-object.c		\
							\
	examples/cclib-condition-object.texi		\
	examples/cclib-condition-object.h		\
	examples/cclib-condition-object.c		\
	examples/test-cclib-condition-object.c		\
							\
	examples/cclib-condition-object-alias.texi	\
	examples/cclib-condition-object-alias.h		\
	examples/cclib-condition-object-alias.c		\
	examples/test-cclib-condition-object-alias.c	\
							\
	examples/struct-by-ptr-no-descr.texi		\
	examples/struct-by-ptr-no-descr.h		\
	examples/struct-by-ptr-no-descr.c		\
	examples/test-struct-by-ptr-no-descr.c		\
							\
	examples/struct-by-ptr-with-descr.texi		\
	examples/struct-by-ptr-with-descr.h		\
	examples/struct-by-ptr-with-descr.c		\
	examples/test-struct-by-ptr-with-descr.c	\
							\
	examples/struct-by-val-no-descr.texi		\
	examples/struct-by-val-no-descr.h		\
	examples/struct-by-val-no-descr.c		\
	examples/test-struct-by-val-no-descr.c		\
							\
	examples/struct-by-val-with-descr.texi		\
	examples/struct-by-val-with-descr.h		\
	examples/struct-by-val-with-descr.c		\
	examples/test-struct-by-val-with-descr.c	\
							\
	examples/destructor-trait.h			\
	examples/test-destructor-trait.c

noinst_PROGRAMS	=					\
	examples/test-plain-condition-object		\
	examples/test-cclib-condition-object		\
	examples/test-cclib-condition-object-alias	\
	examples/test-struct-by-ptr-no-descr		\
	examples/test-struct-by-ptr-with-descr		\
	examples/test-struct-by-val-no-descr		\
	examples/test-struct-by-val-with-descr		\
	examples/test-destructor-trait

ccexceptions_examples_cppflags		= $(AM_CPPFLAGS) -I$(srcdir)/examples
ccexceptions_examples_ldadd		= -lm -L$(builddir) libccexceptions.la

.PHONY: examples

examples: $(noinst_PROGRAMS)
	-./examples/test-plain-condition-object
	-./examples/test-cclib-condition-object
	-./examples/test-struct-by-ptr-no-descr
	-./examples/test-struct-by-ptr-with-descr
	-./examples/test-struct-by-val-no-descr
	-./examples/test-struct-by-val-with-descr
	-./examples/test-destructor-trait

## --------------------------------------------------------------------

examples_test_plain_condition_object_SOURCES =		\
	examples/plain-condition-object.h		\
	examples/plain-condition-object.c		\
	examples/test-plain-condition-object.c

examples_test_plain_condition_object_CPPFLAGS	= $(ccexceptions_examples_cppflags)
examples_test_plain_condition_object_LDADD	= $(ccexceptions_examples_ldadd)

$(examples_test_plain_condition_object_OBJECTS): libccexceptions.la

## --------------------------------------------------------------------

examples_test_cclib_condition_object_SOURCES =		\
	examples/cclib-condition-object.h		\
	examples/cclib-condition-object.c		\
	examples/test-cclib-condition-object.c

examples_test_cclib_condition_object_CPPFLAGS	= $(ccexceptions_examples_cppflags)
examples_test_cclib_condition_object_LDADD	= $(ccexceptions_examples_ldadd)

$(examples_test_cclib_condition_object_OBJECTS): libccexceptions.la

## --------------------------------------------------------------------

examples_test_cclib_condition_object_alias_SOURCES =	\
	examples/cclib-condition-object-alias.h		\
	examples/cclib-condition-object-alias.c		\
	examples/test-cclib-condition-object-alias.c

examples_test_cclib_condition_object_alias_CPPFLAGS	= $(ccexceptions_examples_cppflags)
examples_test_cclib_condition_object_alias_LDADD	= $(ccexceptions_examples_ldadd)

$(examples_test_cclib_condition_object_alias_OBJECTS): libccexceptions.la

## --------------------------------------------------------------------

examples_test_struct_by_ptr_no_descr_SOURCES =		\
	examples/struct-by-ptr-no-descr.h		\
	examples/struct-by-ptr-no-descr.c		\
	examples/test-struct-by-ptr-no-descr.c

examples_test_struct_by_ptr_no_descr_CPPFLAGS	= $(ccexceptions_examples_cppflags)
examples_test_struct_by_ptr_no_descr_LDADD	= $(ccexceptions_examples_ldadd)

$(examples_test_struct_by_ptr_no_descr_OBJECTS): libccexceptions.la

## --------------------------------------------------------------------

examples_test_struct_by_ptr_with_descr_SOURCES =	\
	examples/struct-by-ptr-with-descr.h		\
	examples/struct-by-ptr-with-descr.c		\
	examples/test-struct-by-ptr-with-descr.c

examples_test_struct_by_ptr_with_descr_CPPFLAGS	= $(ccexceptions_examples_cppflags)
examples_test_struct_by_ptr_with_descr_LDADD	= $(ccexceptions_examples_ldadd)

$(examples_test_struct_by_ptr_with_descr_OBJECTS): libccexceptions.la

## --------------------------------------------------------------------

examples_test_struct_by_val_no_descr_SOURCES =		\
	examples/struct-by-val-no-descr.h		\
	examples/struct-by-val-no-descr.c		\
	examples/test-struct-by-val-no-descr.c

examples_test_struct_by_val_no_descr_CPPFLAGS	= $(ccexceptions_examples_cppflags)
examples_test_struct_by_val_no_descr_LDADD	= $(ccexceptions_examples_ldadd)

$(examples_test_struct_by_val_no_descr_OBJECTS): libccexceptions.la

## --------------------------------------------------------------------

examples_test_struct_by_val_with_descr_SOURCES =	\
	examples/struct-by-val-with-descr.h		\
	examples/struct-by-val-with-descr.c		\
	examples/test-struct-by-val-with-descr.c

examples_test_struct_by_val_with_descr_CPPFLAGS	= $(ccexceptions_examples_cppflags)
examples_test_struct_by_val_with_descr_LDADD	= $(ccexceptions_examples_ldadd)

$(examples_test_struct_by_val_with_descr_OBJECTS): libccexceptions.la

## --------------------------------------------------------------------

examples_test_destructor_trait_SOURCES =		\
	examples/destructor-trait.h			\
	examples/struct-by-val-with-descr.h		\
	examples/struct-by-val-with-descr.c		\
	examples/struct-by-ptr-with-descr.h		\
	examples/struct-by-ptr-with-descr.c		\
	examples/test-destructor-trait.c

examples_test_destructor_trait_CPPFLAGS		= $(ccexceptions_examples_cppflags)
examples_test_destructor_trait_LDADD		= $(ccexceptions_examples_ldadd)

$(examples_test_destructor_trait_OBJECTS): libccexceptions.la

## --------------------------------------------------------------------

EXTRA_DIST		+= $(top_srcdir)/doc/cclibraries-examples.texi
EXAMPLES_INFO_TARGETS	 = $(builddir)/doc/cclibraries-examples.info
CLEANFILES		+= $(EXAMPLES_INFO_TARGETS)

info-local: $(EXAMPLES_INFO_TARGETS)

$(builddir)/doc/cclibraries-examples.info:					\
		$(top_srcdir)/doc/cclibraries-examples.texi			\
		$(top_srcdir)/examples/struct-by-ptr-no-descr.texi		\
		$(top_srcdir)/examples/struct-by-ptr-with-descr.texi		\
		$(top_srcdir)/examples/struct-by-val-no-descr.texi		\
		$(top_srcdir)/examples/struct-by-val-with-descr.texi		\
		$(top_srcdir)/examples/cclib-condition-object.texi		\
		$(top_srcdir)/examples/cclib-condition-object-alias.texi	\
		$(top_srcdir)/doc/macros.texi
	$(MAKEINFO) $(AM_MAKEINFOFLAGS) $(MAKEINFOFLAGS) -I $(top_srcdir)/examples -o $(@) $(<)


#### common rules

include $(top_srcdir)/meta/automake/mmux-makefile-rules

### end of file
