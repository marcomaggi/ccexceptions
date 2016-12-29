/*
  Part of: CCExceptions
  Contents: tests for exceptional condition descriptors
  Date: Tue Dec 27, 2016

  Abstract



  Copyright (C) 2016 Marco Maggi <marco.maggi-ipsu@poste.it>

  This is free software; you can  redistribute it and/or modify it under
  the terms of the GNU Lesser General Public License as published by the
  Free Software  Foundation; either version  3.0 of the License,  or (at
  your option) any later version.

  This library  is distributed in the  hope that it will  be useful, but
  WITHOUT   ANY  WARRANTY;   without  even   the  implied   warranty  of
  MERCHANTABILITY  or FITNESS  FOR A  PARTICULAR PURPOSE.   See  the GNU
  Lesser General Public License for more details.

  You  should have  received a  copy of  the GNU  Lesser  General Public
  License along  with this library; if  not, write to  the Free Software
  Foundation, Inc.,  59 Temple Place,  Suite 330, Boston,  MA 02111-1307
  USA.

*/


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>	// for INT_MAX
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <ccexceptions.h>

int
main (int argc CCE_UNUSED, const char *const argv[])
{
  /* Raising a no-error error. */
  {
    cce_location_t	L;
    bool		flag = false;

    if (cce_location(L)) {
      {
	cce_condition_t *	C = cce_location_condition(L);
	fprintf(stderr, "log: %s\n", cce_condition_static_message(C));
	cce_condition_free(C);
      }
      flag = false;
      cce_run_error_handlers(L);
    } else {
      flag = true;
      cce_raise(L, cce_errno_condition(0));
      cce_run_cleanup_handlers(L);
    }
    assert(cce_errno_condition(0) == cce_location_condition(L));
    assert(false == flag);
  }

  /* Raising an EINVAL error. */
  {
    cce_location_t	L;
    bool		flag = false;

    if (cce_location(L)) {
      {
	cce_condition_t *	C = cce_location_condition(L);
	fprintf(stderr, "log: %s\n", cce_condition_static_message(C));
	cce_condition_free(C);
      }
      flag = false;
      cce_run_error_handlers(L);
    } else {
      flag = true;
      cce_raise(L, cce_errno_condition(EINVAL));
      cce_run_cleanup_handlers(L);
    }
    assert(cce_errno_condition(EINVAL) == cce_location_condition(L));
    assert(false == flag);
  }

  /* Raising an errno condition with invalid errno code: INT_MAX. */
  {
    cce_location_t	L;
    bool		flag = false;

    if (cce_location(L)) {
      {
	cce_condition_t *	C = cce_location_condition(L);
	fprintf(stderr, "log: %s\n", cce_condition_static_message(C));
	cce_condition_free(C);
      }
      flag = false;
      cce_run_error_handlers(L);
    } else {
      flag = true;
      cce_raise(L, cce_errno_condition(INT_MAX));
      cce_run_cleanup_handlers(L);
    }
    assert(cce_errno_condition(INT_MAX) == cce_location_condition(L));
    assert(false == flag);
  }

  /* Raising an errno condition with invalid errno code: -1. */
  {
    cce_location_t	L;
    bool		flag = false;

    if (cce_location(L)) {
      {
	cce_condition_t *	C = cce_location_condition(L);
	fprintf(stderr, "log: %s\n", cce_condition_static_message(C));
	cce_condition_free(C);
      }
      flag = false;
      cce_run_error_handlers(L);
    } else {
      flag = true;
      cce_raise(L, cce_errno_condition(-1));
      cce_run_cleanup_handlers(L);
    }
    assert(cce_errno_condition(-1) == cce_location_condition(L));
    assert(false == flag);
  }

  exit(EXIT_SUCCESS);
}

/* end of file */
