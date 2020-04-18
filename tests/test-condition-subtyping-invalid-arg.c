/*
  Part of: CCExceptions
  Contents: test for subtyping of "invalid argument" conditions
  Date: Dec  5, 2017

  Abstract

	Test file for subtyping of "invalid argument" conditions.

  Copyright (C) 2017, 2018, 2020 Marco Maggi <mrc.mgg@gmail.com>

  See the COPYING file.
*/


/** --------------------------------------------------------------------
 ** Heaaders.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include <stdio.h>
#include <stdlib.h>
#include "condition-subtyping-invalid-arg.h"


int
main (void)
{
  invalid_argument_subtyping_init_module();

  {
    cce_location_t	L[1];

    if (cce_location(L)) {
      fprintf(stderr, "%s: static message: %s\n", __func__, cce_condition_static_message(cce_condition(L)));

      if (my_condition_is_invalid_argument_subtype(cce_condition(L))) {
	CCLIB_PC(my_condition_invalid_argument_subtype_t, C, cce_condition(L));
	fprintf(stderr, "%s: is invalid argument subtype, funcname=%s, index=%u, data=%d\n",
		__func__, C->invalid_argument.funcname, C->invalid_argument.index, *(C->data));
      } else {
	fprintf(stderr, "%s: wrong condition-object type\n", __func__);
	exit(EXIT_FAILURE);
      }

      if (cce_condition_is_invalid_argument(cce_condition(L))) {
	fprintf(stderr, "%s: is invalid argument condition\n", __func__);
      } else {
	fprintf(stderr, "%s: wrong condition-object type\n", __func__);
	exit(EXIT_FAILURE);
      }

      if (cce_condition_is_logic_error(cce_condition(L))) {
	fprintf(stderr, "%s: is logic error condition\n", __func__);
      } else {
	fprintf(stderr, "%s: wrong condition-object type\n", __func__);
	exit(EXIT_FAILURE);
      }

      if (cce_condition_is_error(cce_condition(L))) {
	fprintf(stderr, "%s: is error condition\n", __func__);
      } else {
	fprintf(stderr, "%s: wrong condition-object type\n", __func__);
	exit(EXIT_FAILURE);
      }

      if (cce_condition_is_root(cce_condition(L))) {
	fprintf(stderr, "%s: is root condition\n", __func__);
      } else {
	fprintf(stderr, "%s: wrong condition-object type\n", __func__);
	exit(EXIT_FAILURE);
      }

      cce_run_catch_handlers_final(L);
    } else {
      cce_raise(L, my_condition_new_invalid_argument_subtype(L, "do_something", 1, 123));
      cce_run_body_handlers(L);
    }
  }

  exit(EXIT_SUCCESS);
}

/* end of file */
