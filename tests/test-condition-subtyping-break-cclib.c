/*
  Part of: CCExceptions
  Contents: test for subtyping of break conditions
  Date: Apr 18, 2020

  Abstract

	Test file for subtyping of break conditions.

  Copyright (C) 2017, 2018, 2020 Marco Maggi <mrc.mgg@gmail.com>

  See the COPYING file.
*/


/** --------------------------------------------------------------------
 ** Heaaders.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include <stdio.h>
#include <stdlib.h>
#include "condition-subtyping-break-cclib.h"


int
main (void)
{
  break_cclib_subtyping_init_module();

  {
    cce_location_t	L[1];

    if (cce_location(L)) {
      fprintf(stderr, "%s: static message: %s\n", __func__, cce_condition_static_message(cce_condition(L)));

      if (cclib_is(cclib_exceptional_condition_object_type(my_break_subtype))(cce_condition(L))) {
	CCLIB_PC(cclib_exceptional_condition_object_type(my_break_subtype), C, cce_condition(L));

	fprintf(stderr, "%s: is break subtype, data=%d\n", __func__, *(C->data));
      } else {
	fprintf(stderr, "%s: wrong condition-object type\n", __func__);
	exit(EXIT_FAILURE);
      }

      if (cclib_is(cclib_exceptional_condition_object_type(cce_break))(cce_condition(L))) {
	fprintf(stderr, "%s: is break condition\n", __func__);
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
      cce_raise(L, cclib_new(cclib_exceptional_condition_object_type(my_break_subtype))(L, 123));
      cce_run_body_handlers(L);
    }
  }

  exit(EXIT_SUCCESS);
}

/* end of file */
