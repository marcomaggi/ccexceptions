/*
  Part of: CCExceptions
  Contents: tests for exceptional condition descriptors hierarchy
  Date: Dec 28, 2016

  Abstract



  Copyright (C) 2016, 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

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
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <ccexceptions.h>

static const char *
default_static_message (const cce_condition_t * C CCE_UNUSED)
{
  return "default message";
}

/* ------------------------------------------------------------------ */

static cce_condition_descriptor_t A_condition_descriptor = {
  /* This field is initialised later. */
  .parent		= NULL,
  .free			= NULL,
  .static_message	= default_static_message
};

static const cce_condition_descriptor_t B_condition_descriptor = {
  .parent		= &A_condition_descriptor,
  .free			= NULL,
  .static_message	= default_static_message
};

static const cce_condition_descriptor_t C_condition_descriptor = {
  .parent		= &B_condition_descriptor,
  .free			= NULL,
  .static_message	= default_static_message
};

/* ------------------------------------------------------------------ */

static const cce_condition_t A_condition = {
  .descriptor		= &A_condition_descriptor
};

static const cce_condition_t B_condition = {
  .descriptor		= &B_condition_descriptor
};

static const cce_condition_t C_condition = {
  .descriptor		= &C_condition_descriptor
};


int
main (int argc CCE_UNUSED, const char *const argv[] CCE_UNUSED)
{
  /* Dynamic initialisation. */
  A_condition_descriptor.parent = cce_root_condition_descriptor;

  assert(true  == cce_condition_is_a(cce_unknown_condition,       cce_root_condition_descriptor));
  assert(true  == cce_condition_is_a(cce_errno_condition(EINVAL), cce_root_condition_descriptor));
  assert(true  == cce_condition_is_a(&A_condition,                cce_root_condition_descriptor));
  assert(true  == cce_condition_is_a(&B_condition,                cce_root_condition_descriptor));
  assert(true  == cce_condition_is_a(&C_condition,                cce_root_condition_descriptor));

  assert(true  == cce_condition_is_a(cce_unknown_condition,       cce_unknown_condition_descriptor));
  assert(false == cce_condition_is_a(cce_errno_condition(EINVAL), cce_unknown_condition_descriptor));
  assert(false == cce_condition_is_a(&A_condition,                cce_unknown_condition_descriptor));
  assert(false == cce_condition_is_a(&B_condition,                cce_unknown_condition_descriptor));
  assert(false == cce_condition_is_a(&C_condition,                cce_unknown_condition_descriptor));

  assert(false == cce_condition_is_a(cce_unknown_condition,       cce_errno_condition_descriptor));
  assert(true  == cce_condition_is_a(cce_errno_condition(EINVAL), cce_errno_condition_descriptor));
  assert(false == cce_condition_is_a(&A_condition,                cce_errno_condition_descriptor));
  assert(false == cce_condition_is_a(&B_condition,                cce_errno_condition_descriptor));
  assert(false == cce_condition_is_a(&C_condition,                cce_errno_condition_descriptor));

  assert(false == cce_condition_is_a(cce_unknown_condition,       &A_condition_descriptor));
  assert(false == cce_condition_is_a(cce_errno_condition(EINVAL), &A_condition_descriptor));
  assert(true  == cce_condition_is_a(&A_condition,                &A_condition_descriptor));
  assert(true  == cce_condition_is_a(&B_condition,                &A_condition_descriptor));
  assert(true  == cce_condition_is_a(&C_condition,                &A_condition_descriptor));

  assert(false == cce_condition_is_a(cce_unknown_condition,       &B_condition_descriptor));
  assert(false == cce_condition_is_a(cce_errno_condition(EINVAL), &B_condition_descriptor));
  assert(false == cce_condition_is_a(&A_condition,                &B_condition_descriptor));
  assert(true  == cce_condition_is_a(&B_condition,                &B_condition_descriptor));
  assert(true  == cce_condition_is_a(&C_condition,                &B_condition_descriptor));

  assert(false == cce_condition_is_a(cce_unknown_condition,       &C_condition_descriptor));
  assert(false == cce_condition_is_a(cce_errno_condition(EINVAL), &C_condition_descriptor));
  assert(false == cce_condition_is_a(&A_condition,                &C_condition_descriptor));
  assert(false == cce_condition_is_a(&B_condition,                &C_condition_descriptor));
  assert(true  == cce_condition_is_a(&C_condition,                &C_condition_descriptor));

  /* Branching upon condition types with "cce_condition_is_a()". */
  {
    cce_location_t	L[1];
    bool		flag = false;

    if (cce_location(L)) {
      cce_condition_t *	C = cce_condition(L);

      if (cce_condition_is_a(C, cce_unknown_condition_descriptor))
	{
	  flag = false;
	}
      else if (cce_condition_is_a(C, cce_errno_condition_descriptor))
	{
	  flag = true;
	}
      else
	{
	  flag = false;
	}
      cce_run_error_handlers(L);
      cce_condition_free(C);
    } else {
      cce_raise(L, cce_errno_condition(EINVAL));
      cce_run_cleanup_handlers(L);
    }
    assert(true == flag);
  }

  /* Branching upon condition types with "cce_descriptor_child_and_parent()". */
  {
    cce_location_t	L[1];
    bool		flag = false;

    if (cce_location(L)) {
      cce_condition_t *			C  = cce_condition(L);
      const cce_condition_descriptor_t *CD = cce_condition_descriptor(C);

      if (cce_condition_descriptor_child_and_parent(CD, cce_unknown_condition_descriptor))
	{
	  flag = false;
	}
      else if (cce_condition_descriptor_child_and_parent(CD, cce_errno_condition_descriptor))
	{
	  flag = true;
	}
      else
	{
	  flag = false;
	}
      cce_run_error_handlers(L);
      cce_condition_free(C);
    } else {
      cce_raise(L, cce_errno_condition(EINVAL));
      cce_run_cleanup_handlers(L);
    }
    assert(true == flag);
  }

  exit(EXIT_SUCCESS);
}

/* end of file */
