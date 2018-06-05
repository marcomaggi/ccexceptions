/*
  Part of: CCExceptions
  Contents: header definitions for subtyping of "logic error" conditions
  Date: Dec  3, 2017

  Abstract

	Header definitions for subtyping of "logic error" conditions

  Copyright (C) 2017, 2018 Marco Maggi <marco.maggi-ipsu@poste.it>

  See the COPYING file.
*/

#ifndef LOGIC_ERROR_SUBTYPING_HEADER_H
#define LOGIC_ERROR_SUBTYPING_HEADER_H 1


/** --------------------------------------------------------------------
 ** Heaaders.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include <stdio.h>
#include <stdlib.h>


/** --------------------------------------------------------------------
 ** Header definitions.
 ** ----------------------------------------------------------------- */

typedef struct my_descriptor_logic_error_subtype_t	my_descriptor_logic_error_subtype_t;
typedef struct my_condition_logic_error_subtype_t	my_condition_logic_error_subtype_t;

struct my_descriptor_logic_error_subtype_t {
  cce_descriptor_t	descriptor;
};

struct my_condition_logic_error_subtype_t {
  cce_condition_logic_error_t	logic_error;
  int *				data;
};

extern my_descriptor_logic_error_subtype_t const * const	my_descriptor_logic_error_subtype_ptr;

extern void my_condition_init_logic_error_subtype (cce_destination_t L, my_condition_logic_error_subtype_t * C, int the_data)
  __attribute__((__nonnull__(1)));

extern cce_condition_t const * my_condition_new_logic_error_subtype (cce_destination_t L, int the_data)
  __attribute__((__nonnull__(1)));

__attribute__((__pure__,__nonnull__(1),__always_inline__))
static inline bool
my_condition_is_logic_error_subtype (cce_condition_t const * C)
{
  return cce_condition_is(C, &(my_descriptor_logic_error_subtype_ptr->descriptor));
}

extern void logic_error_subtyping_init_module (void);


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#endif /* LOGIC_ERROR_SUBTYPING_HEADER_H */

/* end of file */
