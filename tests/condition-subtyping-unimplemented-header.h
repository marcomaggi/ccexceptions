/*
  Part of: CCExceptions
  Contents: header definitions for subtyping of "unimplemented" conditions
  Date: Dec  3, 2017

  Abstract

	Header definitions for subtyping of "unimplemented" conditions.

  Copyright (C) 2017, 2018, 2019 Marco Maggi <marco.maggi-ipsu@poste.it>

  See the COPYING file.
*/

#ifndef UNIMPLEMENTED_SUBTYPING_HEADER_H
#define UNIMPLEMENTED_SUBTYPING_HEADER_H 1


/** --------------------------------------------------------------------
 ** Heaaders.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include <stdio.h>
#include <stdlib.h>


/** --------------------------------------------------------------------
 ** Header definitions.
 ** ----------------------------------------------------------------- */

typedef struct my_descriptor_unimplemented_subtype_t	my_descriptor_unimplemented_subtype_t;
typedef struct my_condition_unimplemented_subtype_t	my_condition_unimplemented_subtype_t;

struct my_descriptor_unimplemented_subtype_t {
  cce_descriptor_t	descriptor;
};

struct my_condition_unimplemented_subtype_t {
  ccname_type(cce_condition_t, unimplemented)	unimplemented;
  int *				data;
};

extern my_descriptor_unimplemented_subtype_t const * const	my_descriptor_unimplemented_subtype_ptr;

extern void my_condition_init_unimplemented_subtype (cce_destination_t L, my_condition_unimplemented_subtype_t * C, int the_data)
  __attribute__((__nonnull__(1)));

extern cce_condition_t const * my_condition_new_unimplemented_subtype (cce_destination_t L, int the_data)
  __attribute__((__nonnull__(1)));

__attribute__((__pure__,__nonnull__(1),__always_inline__))
static inline bool
my_condition_is_unimplemented_subtype (cce_condition_t const * C)
{
  return ccname_is(cce_condition_t)(C, &(my_descriptor_unimplemented_subtype_ptr->descriptor));
}

extern void unimplemented_subtyping_init_module (void);


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#endif /* UNIMPLEMENTED_SUBTYPING_HEADER_H */

/* end of file */
