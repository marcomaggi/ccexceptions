/*
  Part of: CCExceptions
  Contents: header definitions for subtyping of "math_underflow" conditions
  Date: Dec  3, 2017

  Abstract

	Header definitions for subtyping of "math_underflow" conditions.

  Copyright (C) 2017, 2018, 2019 Marco Maggi <marco.maggi-ipsu@poste.it>

  See the COPYING file.
*/

#ifndef MATH_UNDERFLOW_SUBTYPING_HEADER_H
#define MATH_UNDERFLOW_SUBTYPING_HEADER_H 1


/** --------------------------------------------------------------------
 ** Heaaders.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include <stdio.h>
#include <stdlib.h>


/** --------------------------------------------------------------------
 ** Module initialisation.
 ** ----------------------------------------------------------------- */

extern void math_underflow_subtyping_init_module (void);


/** --------------------------------------------------------------------
 ** Header definitions.
 ** ----------------------------------------------------------------- */

typedef struct my_descriptor_math_underflow_subtype_t	my_descriptor_math_underflow_subtype_t;
typedef struct my_condition_math_underflow_subtype_t	my_condition_math_underflow_subtype_t;

struct my_descriptor_math_underflow_subtype_t {
  cce_descriptor_t	descriptor;
};

struct my_condition_math_underflow_subtype_t {
  cce_condition_math_underflow_t		parent;
  int *				data;
};

extern void cce_descriptor_set_parent_to(my_descriptor_math_underflow_subtype_t) (cce_descriptor_t * const D)
  __attribute__((__nonnull__(1)));

/* ------------------------------------------------------------------ */

extern void my_condition_init_math_underflow_subtype (cce_destination_t L, my_condition_math_underflow_subtype_t * C, int the_data)
  __attribute__((__nonnull__(1)));

extern cce_condition_t const * my_condition_new_math_underflow_subtype (cce_destination_t L, int the_data)
  __attribute__((__nonnull__(1)));

extern bool my_condition_is_math_underflow_subtype (cce_condition_t const * C)
  __attribute__((__pure__,__nonnull__(1)));


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#endif /* MATH_UNDERFLOW_SUBTYPING_HEADER_H */

/* end of file */
