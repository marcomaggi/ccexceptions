/*
  Part of: CCExceptions
  Contents: test for subtyping of errno conditions
  Date: Apr 18, 2020

  Abstract

	Test file for subtyping of errno conditions.

  Copyright (C) 2017, 2018, 2020 Marco Maggi <mrc.mgg@gmail.com>

  See the COPYING file.
*/


/** --------------------------------------------------------------------
 ** Heaaders.
 ** ----------------------------------------------------------------- */

#include "condition-subtyping-errno-cclib.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


int
main (void)
{
  errno_cclib_subtyping_init_module();

  {
    cce_location_t	L[1];

    if (cce_location(L)) {
      fprintf(stderr, "%s: static message: %s\n", __func__, cce_condition_static_message(cce_condition(L)));

      if (cclib_is(cclib_exceptional_condition_object_type(my_errno_subtype))(cce_condition(L))) {
	CCLIB_PC(cclib_exceptional_condition_object_type(my_errno_subtype) const, C, cce_condition(L));
	CCLIB_PC(cce_condition_t const, K, &(C->parent));

	fprintf(stderr, "%s: is errno subtype, errno=%d, message=%s, data=%d\n", __func__,
		cce_condition_ref_errno_errnum(K),
		cce_condition_ref_errno_message(K),
		*(C->data));
      } else {
	fprintf(stderr, "%s: wrong condition-object type\n", __func__);
	exit(EXIT_FAILURE);
      }

      if (cclib_is(cclib_exceptional_condition_object_type(cce_errno))(cce_condition(L))) {
	fprintf(stderr, "%s: is errno condition\n", __func__);
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
      cce_raise(L, cclib_new(cclib_exceptional_condition_object_type(my_errno_subtype))(L, ENOMEM, 123));
      cce_run_body_handlers(L);
    }
  }

  exit(EXIT_SUCCESS);
}

/* end of file */
