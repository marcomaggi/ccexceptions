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


#include <ccexceptions.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

static const char *
default_static_message (const cce_condition_C_t * C CCE_UNUSED)
{
  return "default message";
}

/* ------------------------------------------------------------------ */

static cce_condition_D_t alpha_D = {
  /* This field is initialised later. */
  .parent		= NULL,
  .final		= NULL,
  .static_message	= default_static_message
};

static const cce_condition_D_t beta_D = {
  .parent		= &alpha_D,
  .final		= NULL,
  .static_message	= default_static_message
};

static const cce_condition_D_t gamma_D = {
  .parent		= &beta_D,
  .final		= NULL,
  .static_message	= default_static_message
};

/* ------------------------------------------------------------------ */

static const cce_condition_C_t alpha_C = {
  .condition_D		= &alpha_D
};

static const cce_condition_C_t beta_C = {
  .condition_D		= &beta_D
};

static const cce_condition_C_t gamma_C = {
  .condition_D		= &gamma_D
};


int
main (int argc CCE_UNUSED, const char *const argv[] CCE_UNUSED)
{
  /* Dynamic initialisation. */
  cce_condition_D_set_root_parent(&alpha_D);

  assert(true  == cce_is_root_C(cce_condition_C(cce_make_unknown_C())));
  assert(true  == cce_is_root_C(cce_condition_C(cce_make_errno_C(EINVAL))));
  assert(true  == cce_is_root_C(&alpha_C));
  assert(true  == cce_is_root_C(&beta_C));
  assert(true  == cce_is_root_C(&gamma_C));

  assert(true  == cce_is_condition_C(cce_condition_C(cce_make_unknown_C()),     cce_condition_D(cce_unknown_D_ptr)));
  assert(false == cce_is_condition_C(cce_condition_C(cce_make_errno_C(EINVAL)),	cce_condition_D(cce_unknown_D_ptr)));
  assert(false == cce_is_condition_C(&alpha_C, cce_condition_D(cce_unknown_D_ptr)));
  assert(false == cce_is_condition_C(&beta_C,  cce_condition_D(cce_unknown_D_ptr)));
  assert(false == cce_is_condition_C(&gamma_C, cce_condition_D(cce_unknown_D_ptr)));

  assert(false == cce_is_condition_C(cce_condition_C(cce_make_unknown_C()),     cce_condition_D(cce_errno_D_ptr)));
  assert(true  == cce_is_condition_C(cce_condition_C(cce_make_errno_C(EINVAL)),	cce_condition_D(cce_errno_D_ptr)));
  assert(false == cce_is_condition_C(&alpha_C, cce_condition_D(cce_errno_D_ptr)));
  assert(false == cce_is_condition_C(&beta_C,  cce_condition_D(cce_errno_D_ptr)));
  assert(false == cce_is_condition_C(&gamma_C, cce_condition_D(cce_errno_D_ptr)));

  assert(false == cce_is_condition_C(cce_condition_C(cce_make_unknown_C()),     &alpha_D));
  assert(false == cce_is_condition_C(cce_condition_C(cce_make_errno_C(EINVAL)),	&alpha_D));
  assert(true  == cce_is_condition_C(&alpha_C, &alpha_D));
  assert(true  == cce_is_condition_C(&beta_C,  &alpha_D));
  assert(true  == cce_is_condition_C(&gamma_C, &alpha_D));

  assert(false == cce_is_condition_C(cce_condition_C(cce_make_unknown_C()),     &beta_D));
  assert(false == cce_is_condition_C(cce_condition_C(cce_make_errno_C(EINVAL)), &beta_D));
  assert(false == cce_is_condition_C(&alpha_C, &beta_D));
  assert(true  == cce_is_condition_C(&beta_C,  &beta_D));
  assert(true  == cce_is_condition_C(&gamma_C, &beta_D));

  assert(false == cce_is_condition_C(cce_condition_C(cce_make_unknown_C()),     &gamma_D));
  assert(false == cce_is_condition_C(cce_condition_C(cce_make_errno_C(EINVAL)), &gamma_D));
  assert(false == cce_is_condition_C(&alpha_C, &gamma_D));
  assert(false == cce_is_condition_C(&beta_C,  &gamma_D));
  assert(true  == cce_is_condition_C(&gamma_C, &gamma_D));

  /* Branching upon condition types with "cce_is_condition_C()". */
  {
    cce_location_t	L[1];
    bool		flag = false;

    if (cce_location(L)) {
      cce_condition_C_t *	C = cce_condition_C(L);

      if (cce_is_condition_C(C, cce_condition_D(cce_unknown_D_ptr)))
	{
	  flag = false;
	}
      else if (cce_is_condition_C(C, cce_condition_D(cce_errno_D_ptr)))
	{
	  flag = true;
	}
      else
	{
	  flag = false;
	}
      cce_run_error_handlers(L);
      cce_condition_C_final(C);
    } else {
      cce_raise(L, cce_condition_C(cce_make_errno_C(EINVAL)));
      cce_run_cleanup_handlers(L);
    }
    assert(true == flag);
  }

  /* Branching upon condition types with "cce_descriptor_child_and_parent()". */
  {
    cce_location_t	L[1];
    bool		flag = false;

    if (cce_location(L)) {
      cce_condition_C_t *	C  = cce_condition_C(L);
      const cce_condition_D_t *	CD = cce_condition_D(C);

      if (cce_condition_D_child_and_parent(CD, cce_condition_D(cce_unknown_D_ptr)))
	{
	  flag = false;
	}
      else if (cce_condition_D_child_and_parent(CD, cce_condition_D(cce_errno_D_ptr)))
	{
	  flag = true;
	}
      else
	{
	  flag = false;
	}
      cce_run_error_handlers(L);
      cce_condition_C_final(C);
    } else {
      cce_raise(L, cce_condition_C(cce_make_errno_C(EINVAL)));
      cce_run_cleanup_handlers(L);
    }
    assert(true == flag);
  }

  exit(EXIT_SUCCESS);
}

/* end of file */
