/*
  Part of: CCExceptions
  Contents: test for subtyping of logic error conditions
  Date: Dec  3, 2017

  Abstract

	Test file for subtyping of logic error conditions.

  Copyright (C) 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

  See the COPYING file.
*/


/** --------------------------------------------------------------------
 ** Heaaders.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include <stdio.h>
#include <stdlib.h>
#include "logic-error-subtyping-header.h"


int
main (void)
{
  logic_error_subtyping_init_module();

  {
    cce_location_t	L[1];

    if (cce_location(L)) {
      fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
      cce_run_error_handlers_final(L);
    } else {
      cce_raise(L, my_condition_new_logic_error_subtype(L, 123));
      cce_run_cleanup_handlers(L);
    }
  }

  exit(EXIT_SUCCESS);
}

/* end of file */
