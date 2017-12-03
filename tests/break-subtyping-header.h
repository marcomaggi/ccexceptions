/*
  Part of: CCExceptions
  Contents: header definitions for subtyping of "break" conditions
  Date: Dec  3, 2017

  Abstract

	Header definitions for subtyping of "break" conditions

  Copyright (C) 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

  See the COPYING file.
*/

#ifndef BREAK_SUBTYPING_HEADER_H
#define BREAK_SUBTYPING_HEADER_H 1


/** --------------------------------------------------------------------
 ** Heaaders.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include <stdio.h>
#include <stdlib.h>


/** --------------------------------------------------------------------
 ** Header definitions.
 ** ----------------------------------------------------------------- */

typedef struct my_descriptor_break_subtype_t	my_descriptor_break_subtype_t;
typedef struct my_condition_break_subtype_t	my_condition_break_subtype_t;

struct my_descriptor_break_subtype_t {
  cce_descriptor_t	descriptor;
};

struct my_condition_break_subtype_t {
  cce_condition_break_t	parent;
  int *			data;
};

extern my_descriptor_break_subtype_t const * const	my_descriptor_break_subtype_ptr;

extern void my_condition_break_subtype_init  (my_condition_break_subtype_t * C, int the_data)
  __attribute__((__nonnull__(1)));

extern cce_condition_t const * my_condition_break_subtype_new (cce_destination_t L, int the_data)
  __attribute__((__nonnull__(1)));

__attribute__((__pure__,__nonnull__(1),__always_inline__))
static inline bool
my_condition_is_break_subtype (cce_condition_t const * C)
{
  return cce_is_condition(C, &(my_descriptor_break_subtype_ptr->descriptor));
}

extern void break_subtyping_init_module (void);


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#endif /* BREAK_SUBTYPING_HEADER_H */

/* end of file */
