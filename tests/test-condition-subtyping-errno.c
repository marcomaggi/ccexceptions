/*
  Part of: CCExceptions
  Contents: test for subtyping of errno conditions
  Date: Apr 18, 2020

  Abstract

	Test file for subtyping of errno conditions.

  Copyright (C) 2020 Marco Maggi <mrc.mgg@gmail.com>

  See the COPYING file.
*/


/** --------------------------------------------------------------------
 ** Heaaders.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "condition-subtyping-errno.h"


int
main (void)
{
  errno_subtyping_init_module();

  {
    cce_location_t	L[1];

    if (cce_location(L)) {
      fprintf(stderr, "%s: static message: %s\n", __func__, cce_condition_static_message(cce_condition(L)));

      if (my_condition_is_errno_subtype(cce_condition(L))) {
	CCLIB_PC(my_condition_errno_subtype_t, C, cce_condition(L));
	fprintf(stderr, "%s: is errno subtype, errno=%d, message=%s, data=%d\n", __func__,
		C->parent.errnum, C->parent.message, *(C->data));
      } else {
	fprintf(stderr, "%s: wrong condition-object type\n", __func__);
	exit(EXIT_FAILURE);
      }

      if (cce_condition_is_errno(cce_condition(L))) {
	fprintf(stderr, "%s: is errno condition\n", __func__);
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
      cce_raise(L, my_condition_new_errno_subtype(L, ENOMEM, 123));
      cce_run_body_handlers(L);
    }
  }

  exit(EXIT_SUCCESS);
}

/* end of file */
