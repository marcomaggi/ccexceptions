/*
  Part of: CCExceptions
  Contents: header definitions for subtyping of "errno" conditions
  Date: Apr 18, 2020

  Abstract

	Header definitions for subtyping of "errno" conditions.

  Copyright (C) 2017, 2018, 2019, 2020 Marco Maggi <mrc.mgg@gmail.com>

  See the COPYING file.
*/

#ifndef CONDITION_SUBTYPING_ERRNO_CCLIB_H
#define CONDITION_SUBTYPING_ERRNO_CCLIB_H 1


/** --------------------------------------------------------------------
 ** Heaaders.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include <stdio.h>
#include <stdlib.h>


/** --------------------------------------------------------------------
 ** Module initialisation.
 ** ----------------------------------------------------------------- */

extern void errno_cclib_subtyping_init_module (void);


/** --------------------------------------------------------------------
 ** Header definitions.
 ** ----------------------------------------------------------------- */

CCLIB_STRUCT_TYPEDEF(cclib_exceptional_condition_descriptor_type(my_errno_subtype));
CCLIB_STRUCT_TYPEDEF(cclib_exceptional_condition_object_type(my_errno_subtype));

struct cclib_exceptional_condition_descriptor_type(my_errno_subtype) {
  cce_descriptor_t	descriptor;
};

struct cclib_exceptional_condition_object_type(my_errno_subtype) {
  cclib_exceptional_condition_object_type(cce_errno)	parent;
  int *		data;
};

cclib_decl void cclib_exceptional_condition_descriptor_set_parent_to(my_errno_subtype) (cce_descriptor_t * const D)
  __attribute__((__nonnull__(1)));

/* ------------------------------------------------------------------ */

cclib_decl void cclib_init(cclib_exceptional_condition_object_type(my_errno_subtype))
  (cce_destination_t L, cclib_exceptional_condition_object_type(my_errno_subtype) * C, int errnum, int the_data)
  __attribute__((__nonnull__(1)));

cclib_decl cce_condition_t const * cclib_new(cclib_exceptional_condition_object_type(my_errno_subtype))
  (cce_destination_t L, int errnum, int the_data)
  __attribute__((__nonnull__(1)));

cclib_decl bool cclib_is(cclib_exceptional_condition_object_type(my_errno_subtype)) (cce_condition_t const * C)
  __attribute__((__pure__,__nonnull__(1)));


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#endif /* CONDITION_SUBTYPING_ERRNO_CCLIB_H */

/* end of file */
