/*
  Part of: CCExceptions
  Contents: header definitions for subtyping of "test unreachable" conditions
  Date: Dec 13, 2017

  Abstract

	Header definitions for subtyping of "test unreachable" conditions.

  Copyright (C) 2017, 2018, 2019 Marco Maggi <marco.maggi-ipsu@poste.it>

  See the COPYING file.
*/

#ifndef CONDITION_UNREACHABLE_SUBTYPING_HEADER_H
#define CONDITION_UNREACHABLE_SUBTYPING_HEADER_H 1


/** --------------------------------------------------------------------
 ** Heaaders.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include <stdio.h>
#include <stdlib.h>


/** --------------------------------------------------------------------
 ** Header definitions.
 ** ----------------------------------------------------------------- */

typedef struct my_descriptor_unreachable_subtype_t	my_descriptor_unreachable_subtype_t;
typedef struct my_condition_unreachable_subtype_t	my_condition_unreachable_subtype_t;

struct my_descriptor_unreachable_subtype_t {
  cce_descriptor_t	descriptor;
};

struct my_condition_unreachable_subtype_t {
  ccname_type(cce_condition_t, unreachable)	unreachable;
  int *				data;
};

cce_decl my_descriptor_unreachable_subtype_t const * const	my_descriptor_unreachable_subtype_ptr;

cce_decl void my_condition_init_unreachable_subtype (cce_destination_t L, my_condition_unreachable_subtype_t * C,
							 char const * const filename,
							 char const * const funcname,
							 int const linenum,
							 int the_data)
  __attribute__((__nonnull__(1,2,3,4)));

cce_decl cce_condition_t const * my_condition_new_unreachable_subtype (cce_destination_t L,
									   char const * const filename,
									   char const * const funcname,
									   int const linenum,
									   int the_data)
  __attribute__((__nonnull__(1,2,3),__returns_nonnull__));

__attribute__((__pure__,__nonnull__(1),__always_inline__))
static inline bool
my_condition_is_unreachable_subtype (cce_condition_t const * C)
{
  return ccname_is(cce_condition_t)(C, &(my_descriptor_unreachable_subtype_ptr->descriptor));
}

cce_decl void condition_unreachable_subtyping_init_module (void);


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#endif /* CONDITION_UNREACHABLE_SUBTYPING_HEADER_H */

/* end of file */
