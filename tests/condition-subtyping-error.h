/*
  Part of: CCExceptions
  Contents: header definitions for subtyping of "error" conditions
  Date: Dec  3, 2017

  Abstract

	Header definitions for subtyping of "error" conditions

  Copyright (C) 2017, 2018, 2019 Marco Maggi <mrc.mgg@gmail.com>

  See the COPYING file.
*/

#ifndef ERROR_SUBTYPING_HEADER_H
#define ERROR_SUBTYPING_HEADER_H 1


/** --------------------------------------------------------------------
 ** Heaaders.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include <stdio.h>
#include <stdlib.h>


/** --------------------------------------------------------------------
 ** Module initialisation.
 ** ----------------------------------------------------------------- */

extern void error_subtyping_init_module (void);


/** --------------------------------------------------------------------
 ** Header definitions.
 ** ----------------------------------------------------------------- */

typedef struct my_descriptor_error_subtype_t	my_descriptor_error_subtype_t;
typedef struct my_condition_error_subtype_t	my_condition_error_subtype_t;

struct my_descriptor_error_subtype_t {
  cce_descriptor_t	descriptor;
};

struct my_condition_error_subtype_t {
  cce_condition_error_t		error;
  int *				data;
};

extern void cce_descriptor_set_parent_to(my_descriptor_error_subtype_t) (cce_descriptor_t * const D)
  __attribute__((__nonnull__(1)));

/* ------------------------------------------------------------------ */

extern void my_condition_init_error_subtype (cce_destination_t L, my_condition_error_subtype_t * C, int the_data)
  __attribute__((__nonnull__(1)));

extern cce_condition_t const * my_condition_new_error_subtype (cce_destination_t L, int the_data)
  __attribute__((__nonnull__(1)));

extern bool my_condition_is_error_subtype (cce_condition_t const * C)
  __attribute__((__pure__,__nonnull__(1)));


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#endif /* ERROR_SUBTYPING_HEADER_H */

/* end of file */
