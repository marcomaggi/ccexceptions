/*
  Part of: CCExceptions
  Contents: test for subtyping of root conditions
  Date: Dec  4, 2017

  Abstract

	Test file for subtyping of root conditions.

  Copyright (C) 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

  See the COPYING file.
*/


/** --------------------------------------------------------------------
 ** Heaaders.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include <stdio.h>
#include <stdlib.h>
#include "root-subtyping-header.h"


int
main (void)
{
  root_subtyping_init_module();

  {
    cce_location_t	L[1];

    if (cce_location(L)) {
      fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
      if (! my_condition_is_root_subtype(cce_condition(L))) {
	exit(EXIT_FAILURE);
      }
      if (! cce_condition_is_root(cce_condition(L))) {
	exit(EXIT_FAILURE);
      }
      cce_run_error_handlers_final(L);
    } else {
      cce_raise(L, my_condition_new_root_subtype(L, 123));
      cce_run_cleanup_handlers(L);
    }
  }

  exit(EXIT_SUCCESS);
}

/* end of file */
