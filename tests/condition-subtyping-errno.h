/*
  Part of: CCExceptions
  Contents: header definitions for subtyping of "errno" conditions
  Date: Apr 18, 2020

  Abstract

	Header definitions for subtyping of "errno" conditions.

  Copyright (C) 2020 Marco Maggi <mrc.mgg@gmail.com>

  See the COPYING file.
*/

#ifndef ERRNO_SUBTYPING_HEADER_H
#define ERRNO_SUBTYPING_HEADER_H 1


/** --------------------------------------------------------------------
 ** Heaaders.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include <stdio.h>
#include <stdlib.h>


/** --------------------------------------------------------------------
 ** Module initialisation.
 ** ----------------------------------------------------------------- */

extern void errno_subtyping_init_module (void);


/** --------------------------------------------------------------------
 ** Header definitions.
 ** ----------------------------------------------------------------- */

typedef struct my_descriptor_errno_subtype_t	my_descriptor_errno_subtype_t;
typedef struct my_condition_errno_subtype_t	my_condition_errno_subtype_t;

struct my_descriptor_errno_subtype_t {
  cce_descriptor_t	descriptor;
};

struct my_condition_errno_subtype_t {
  cce_condition_errno_t		parent;
  int *				data;
};

cclib_decl void cce_descriptor_set_parent_to(my_descriptor_errno_subtype_t) (cce_descriptor_t * const D)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1);

/* ------------------------------------------------------------------ */

cclib_decl void my_condition_init_errno_subtype (cce_destination_t L, my_condition_errno_subtype_t * C, int errnum, int the_data)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1);

cclib_decl cce_condition_t const * my_condition_new_errno_subtype (cce_destination_t L, int errnum, int the_data)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1);

cclib_decl bool my_condition_is_errno_subtype (cce_condition_t const * C)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
  CCLIB_FUNC_ATTRIBUTE_PURE;


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#endif /* ERRNO_SUBTYPING_HEADER_H */

/* end of file */
