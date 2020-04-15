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
AM_MAKEINFOHTMLFLAGS	= --split=node  -I $(srcdir)/examples -c WORDS_IN_PAGE=0 --css-ref=cclibraries.css \
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
	src/ccexceptions-conditions.h

lib_LTLIBRARIES			= libccexceptions.la
libccexceptions_la_LDFLAGS	= $(ccexceptions_LINKER_VERSION)
libccexceptions_la_SOURCES	= \
	src/cclibraries.h			\
	src/ccexceptions.h			\
	src/ccexceptions-handlers.h		\
	src/ccexceptions-conditions.h		\
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
	tests/version					\
	tests/setjmp					\
	tests/no-exceptions				\
	tests/exception-no-handlers			\
	tests/exception-with-clean-handler		\
	tests/exception-with-error-handler		\
	tests/exception-with-handlers			\
	tests/handlers-routines				\
	tests/handlers-as-handlers			\
	tests/conditions-raising			\
	tests/conditions-example			\
	tests/conditions-tests				\
	tests/tracing					\
	tests/retry					\
	tests/system-memory				\
	tests/destructors				\
	tests/test-cclibraries				\
	tests/sizeof					\
	\
	tests/condition-subtyping-root			\
	tests/condition-subtyping-break			\
	tests/condition-subtyping-unimplemented		\
	tests/condition-subtyping-error			\
	tests/condition-subtyping-runtime-error		\
	tests/condition-subtyping-logic-error		\
	tests/condition-subtyping-invalid-arg		\
	tests/condition-subtyping-unreachable		\
	tests/condition-subtyping-math-error		\
	tests/condition-subtyping-math-nan		\
	tests/condition-subtyping-math-infinity		\
	tests/condition-subtyping-math-overflow		\
	tests/condition-subtyping-math-underflow

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

tests_test_cclibraries_CPPFLAGS		= $(ccexceptions_tests_cppflags)
tests_test_cclibraries_LDADD			= $(ccexceptions_tests_ldadd)

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

tests_condition_subtyping_math_error_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_condition_subtyping_math_error_LDADD	= $(ccexceptions_tests_ldadd)
tests_condition_subtyping_math_error_SOURCES	= \
	tests/condition-subtyping-math-error.c		\
	tests/condition-subtyping-math-error-body.c	\
	tests/condition-subtyping-math-error-header.h

## --------------------------------------------------------------------

tests_condition_subtyping_math_nan_CPPFLAGS	= $(ccexceptions_tests_cppflags)
tests_condition_subtyping_math_nan_LDADD	= $(ccexceptions_tests_ldadd)
tests_condition_subtyping_math_nan_SOURCES	= \
	tests/condition-subtyping-math-nan.c		\
	tests/condition-subtyping-math-nan-body.c	\
	tests/condition-subtyping-math-nan-header.h

## --------------------------------------------------------------------

tests_condition_subtyping_math_infinity_CPPFLAGS= $(ccexceptions_tests_cppflags)
tests_condition_subtyping_math_infinity_LDADD	= $(ccexceptions_tests_ldadd)
tests_condition_subtyping_math_infinity_SOURCES	= \
	tests/condition-subtyping-math-infinity.c		\
	tests/condition-subtyping-math-infinity-body.c	\
	tests/condition-subtyping-math-infinity-header.h

## --------------------------------------------------------------------

tests_condition_subtyping_math_overflow_CPPFLAGS= $(ccexceptions_tests_cppflags)
tests_condition_subtyping_math_overflow_LDADD	= $(ccexceptions_tests_ldadd)
tests_condition_subtyping_math_overflow_SOURCES	= \
	tests/condition-subtyping-math-overflow.c		\
	tests/condition-subtyping-math-overflow-body.c	\
	tests/condition-subtyping-math-overflow-header.h

## --------------------------------------------------------------------

tests_condition_subtyping_math_underflow_CPPFLAGS= $(ccexceptions_tests_cppflags)
tests_condition_subtyping_math_underflow_LDADD	= $(ccexceptions_tests_ldadd)
tests_condition_subtyping_math_underflow_SOURCES	= \
	tests/condition-subtyping-math-underflow.c		\
	tests/condition-subtyping-math-underflow-body.c	\
	tests/condition-subtyping-math-underflow-header.h

## --------------------------------------------------------------------

installcheck-local: $(TESTS)
	@for f in $(TESTS); do $(builddir)/$$f; done


### examples

examplesdir		= $(docdir)/examples
dist_examples_DATA	=				\
	examples/struct-as-pointer-no-descr.texi	\
	examples/struct-no-descr.h			\
	examples/struct-no-descr.c			\
	examples/test-struct-no-descr.c			\
							\
	examples/struct-as-pointer-with-descr.texi	\
	examples/struct-with-descr.h			\
	examples/struct-with-descr.c			\
	examples/test-struct-with-descr.c		\
							\
	examples/struct-as-value-no-descr.h		\
	examples/struct-as-value-no-descr.c		\
	examples/test-struct-as-value-no-descr.c	\
	examples/struct-as-value-no-descr.texi		\
							\
	examples/struct-as-value-with-descr.texi	\
	examples/struct-as-value-with-descr.h		\
	examples/struct-as-value-with-descr.c		\
	examples/test-struct-as-value-with-descr.c	\
							\
	examples/destructor-trait.h			\
	examples/test-destructor-trait.c

noinst_PROGRAMS	=					\
	examples/plain					\
	examples/test-struct-no-descr			\
	examples/test-struct-with-descr			\
	examples/test-struct-as-value-no-descr		\
	examples/test-struct-as-value-with-descr	\
	examples/test-destructor-trait

ccexceptions_examples_cppflags		= $(AM_CPPFLAGS) -I$(srcdir)/examples
ccexceptions_examples_ldadd		= -lm -L$(builddir) libccexceptions.la

.PHONY: examples

examples: $(noinst_PROGRAMS)
	-./examples/plain
	-./examples/test-struct-no-descr
	-./examples/test-struct-with-descr
	-./examples/test-struct-as-value-no-descr
	-./examples/test-struct-as-value-with-descr
	-./examples/test-destructor-trait

## --------------------------------------------------------------------

examples_plain_SOURCES		=	\
	examples/plain.c		\
	examples/plain-header.h		\
	examples/plain-body.c

examples_plain_CPPFLAGS			= $(ccexceptions_examples_cppflags)
examples_plain_LDADD			= $(ccexceptions_examples_ldadd)

$(examples_plain_OBJECTS): libccexceptions.la

## --------------------------------------------------------------------

examples_test_struct_no_descr_SOURCES =	\
	examples/struct-no-descr.h		\
	examples/struct-no-descr.c		\
	examples/test-struct-no-descr.c

examples_test_struct_no_descr_CPPFLAGS	= $(ccexceptions_examples_cppflags)
examples_test_struct_no_descr_LDADD	= $(ccexceptions_examples_ldadd)

$(examples_test_struct_no_descr_OBJECTS): libccexceptions.la

## --------------------------------------------------------------------

examples_test_struct_with_descr_SOURCES =	\
	examples/struct-with-descr.h		\
	examples/struct-with-descr.c		\
	examples/test-struct-with-descr.c

examples_test_struct_with_descr_CPPFLAGS	= $(ccexceptions_examples_cppflags)
examples_test_struct_with_descr_LDADD		= $(ccexceptions_examples_ldadd)

$(examples_test_struct_with_descr_OBJECTS): libccexceptions.la

## --------------------------------------------------------------------

examples_test_struct_as_value_no_descr_SOURCES =	\
	examples/struct-as-value-no-descr.h		\
	examples/struct-as-value-no-descr.c		\
	examples/test-struct-as-value-no-descr.c

examples_test_struct_as_value_no_descr_CPPFLAGS	= $(ccexceptions_examples_cppflags)
examples_test_struct_as_value_no_descr_LDADD	= $(ccexceptions_examples_ldadd)

$(examples_test_struct_as_value_no_descr_OBJECTS): libccexceptions.la

## --------------------------------------------------------------------

examples_test_struct_as_value_with_descr_SOURCES =	\
	examples/struct-as-value-with-descr.h		\
	examples/struct-as-value-with-descr.c		\
	examples/test-struct-as-value-with-descr.c

examples_test_struct_as_value_with_descr_CPPFLAGS	= $(ccexceptions_examples_cppflags)
examples_test_struct_as_value_with_descr_LDADD		= $(ccexceptions_examples_ldadd)

$(examples_test_struct_as_value_with_descr_OBJECTS): libccexceptions.la

## --------------------------------------------------------------------

examples_test_destructor_trait_SOURCES =		\
	examples/destructor-trait.h			\
	examples/struct-as-value-with-descr.h		\
	examples/struct-as-value-with-descr.c		\
	examples/struct-with-descr.h			\
	examples/struct-with-descr.c			\
	examples/test-destructor-trait.c

examples_test_destructor_trait_CPPFLAGS		= $(ccexceptions_examples_cppflags)
examples_test_destructor_trait_LDADD		= $(ccexceptions_examples_ldadd)

$(examples_test_destructor_trait_OBJECTS): libccexceptions.la

## --------------------------------------------------------------------

EXTRA_DIST		+= $(top_srcdir)/doc/cclibraries-examples.texi
EXAMPLES_INFO_TARGETS	 = $(builddir)/doc/cclibraries-examples.info

info: $(EXAMPLES_INFO_TARGETS)

$(builddir)/doc/cclibraries-examples.info: \
		$(top_srcdir)/doc/cclibraries-examples.texi			\
		$(top_srcdir)/examples/struct-as-pointer-no-descr.texi		\
		$(top_srcdir)/examples/struct-as-pointer-with-descr.texi	\
		$(top_srcdir)/examples/struct-as-value-no-descr.texi		\
		$(top_srcdir)/examples/struct-as-value-with-descr.texi		\
		$(top_srcdir)/doc/macros.texi
	$(MAKEINFO) $(AM_MAKEINFOFLAGS) $(MAKEINFOFLAGS) -I $(top_srcdir)/examples -o $(@) $(<)


#### common rules

include $(top_srcdir)/meta/automake/mmux-makefile-rules

### end of file
