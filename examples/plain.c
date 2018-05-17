/*
  Part of: CCExceptions
  Contents: example of condition object type definition
  Date: Dec  5, 2017

  Abstract

	This is the main program of  an example of condition-object type
	definition; it  goes along  with the files  "plain-header.h" and
	"plain-body.c".

	The other files define a  new condition-object type derived from
	"cce_condition_runtime_error_t" and  this program uses  it.  The
	definition is a "plain" one:  no inline functions; new condition
	objects allocated by a constructor.

  Copyright (C) 2017, 2018 Marco Maggi <marco.maggi-ipsu@poste.it>

  See the COPYING file.
*/


/** --------------------------------------------------------------------
 ** Heaaders.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include <stdio.h>
#include <stdlib.h>
#include "plain-header.h"


int
main (void)
{
  plain_init_module();

  {
    cce_location_t	L[1];

    if (cce_location(L)) {
      fprintf(stderr, "%s: static message: %s\n", __func__, cce_condition_static_message(cce_condition(L)));

      if (my_condition_is_error_1(cce_condition(L))) {
	CCE_PC(my_condition_error_1_t, C, cce_condition(L));
	fprintf(stderr, "%s: is error-1 condition, data=%d\n", __func__, *(C->data));
      } else {
	fprintf(stderr, "%s: wrong condition-object type\n", __func__);
	exit(EXIT_FAILURE);
      }

      if (cce_condition_is_runtime_error(cce_condition(L))) {
	fprintf(stderr, "%s: is runtime error condition\n", __func__);
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

      cce_run_error_handlers_final(L);
    } else {
      cce_raise(L, my_condition_new_error_1(L, 123));
      cce_run_clean_handlers(L);
    }
  }

  exit(EXIT_SUCCESS);
}

/* end of file */
