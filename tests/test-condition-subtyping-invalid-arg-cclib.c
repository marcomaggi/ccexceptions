/*
  Part of: CCExceptions
  Contents: test for subtyping of invalid_arg conditions
  Date: Apr 18, 2020

  Abstract

	Test file for subtyping of invalid_arg conditions.

  Copyright (C) 2017, 2018, 2020 Marco Maggi <mrc.mgg@gmail.com>

  See the COPYING file.
*/


/** --------------------------------------------------------------------
 ** Heaaders.
 ** ----------------------------------------------------------------- */

#include "condition-subtyping-invalid-arg-cclib.h"
#include <stdio.h>
#include <stdlib.h>


int
main (void)
{
  invalid_arg_cclib_subtyping_init_module();

  {
    cce_location_t	L[1];

    if (cce_location(L)) {
      fprintf(stderr, "%s: static message: %s\n", __func__, cce_condition_static_message(cce_condition(L)));

      if (cclib_is(cclib_exceptional_condition_object_type(my_invalid_arg_subtype))(cce_condition(L))) {
	CCLIB_PC(cclib_exceptional_condition_object_type(my_invalid_arg_subtype), C, cce_condition(L));

	fprintf(stderr, "%s: is invalid argument subtype, funcname=%s, index=%u, data=%d\n",
		__func__, C->parent.funcname, C->parent.index, *(C->data));
      } else {
	fprintf(stderr, "%s: wrong condition-object type\n", __func__);
	exit(EXIT_FAILURE);
      }

      if (cclib_is(cclib_exceptional_condition_object_type(cce_invalid_argument))(cce_condition(L))) {
	fprintf(stderr, "%s: is invalid_arg condition\n", __func__);
      } else {
	fprintf(stderr, "%s: wrong condition-object type\n", __func__);
	exit(EXIT_FAILURE);
      }

      if (cclib_is(cclib_exceptional_condition_object_type(cce_root))(cce_condition(L))) {
	fprintf(stderr, "%s: is root condition\n", __func__);
      } else {
	fprintf(stderr, "%s: wrong condition-object type\n", __func__);
	exit(EXIT_FAILURE);
      }

      cce_run_catch_handlers_final(L);
    } else {
      cce_raise(L, cclib_new(cclib_exceptional_condition_object_type(my_invalid_arg_subtype))(L, __func__, 2, 123));
      cce_run_body_handlers(L);
    }
  }

  exit(EXIT_SUCCESS);
}

/* end of file */
