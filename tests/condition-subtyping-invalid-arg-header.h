/*
  Part of: CCExceptions
  Contents: header definitions for subtyping of "invalid argument" conditions
  Date: Dec  5, 2017

  Abstract

	Header definitions for subtyping of "invalid argument" conditions.

  Copyright (C) 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

  See the COPYING file.
*/

#ifndef INVALID_ARGUMENT_SUBTYPING_HEADER_H
#define INVALID_ARGUMENT_SUBTYPING_HEADER_H 1


/** --------------------------------------------------------------------
 ** Heaaders.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include <stdio.h>
#include <stdlib.h>


/** --------------------------------------------------------------------
 ** Header definitions.
 ** ----------------------------------------------------------------- */

typedef struct my_descriptor_invalid_argument_subtype_t	my_descriptor_invalid_argument_subtype_t;
typedef struct my_condition_invalid_argument_subtype_t	my_condition_invalid_argument_subtype_t;

struct my_descriptor_invalid_argument_subtype_t {
  cce_descriptor_t	descriptor;
};

struct my_condition_invalid_argument_subtype_t {
  cce_condition_invalid_argument_t	invalid_argument;
  int *					data;
};

extern my_descriptor_invalid_argument_subtype_t const * const	my_descriptor_invalid_argument_subtype_ptr;

extern void my_condition_init_invalid_argument_subtype (cce_destination_t L, my_condition_invalid_argument_subtype_t * C,
							char const * func, unsigned index, int the_data)
  __attribute__((__nonnull__(1)));

extern cce_condition_t const * my_condition_new_invalid_argument_subtype (cce_destination_t L, char const * func, unsigned index, int the_data)
  __attribute__((__nonnull__(1)));

__attribute__((__pure__,__nonnull__(1),__always_inline__))
static inline bool
my_condition_is_invalid_argument_subtype (cce_condition_t const * C)
{
  return cce_is_condition(C, &(my_descriptor_invalid_argument_subtype_ptr->descriptor));
}

extern void invalid_argument_subtyping_init_module (void);


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#endif /* INVALID_ARGUMENT_SUBTYPING_HEADER_H */

/* end of file */