/*
  Part of: CCExceptions
  Contents: body definitions of a subtype of "math_error"
  Date: Apr 18, 2020

  Abstract

	Body definitions of a subtype of "math_error".

  Copyright (C) 2017, 2018, 2019, 2020 Marco Maggi <mrc.mgg@gmail.com>

  See the COPYING file.
*/


/** --------------------------------------------------------------------
 ** Heaaders.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include "condition-subtyping-math-error-cclib.h"
#include <stdio.h>
#include <stdlib.h>


/** --------------------------------------------------------------------
 ** Condition type descriptor definition.
 ** ----------------------------------------------------------------- */

static cce_condition_final_fun_t		cclib_method(cclib_exceptional_condition_descriptor_type(my_math_error_subtype), final);
static cce_condition_delete_fun_t		cclib_method(cclib_exceptional_condition_descriptor_type(my_math_error_subtype), delete);
static cce_condition_static_message_fun_t	cclib_method(cclib_exceptional_condition_descriptor_type(my_math_error_subtype), static_message);

static cclib_exceptional_condition_descriptor_type(my_math_error_subtype)
  cclib_exceptional_condition_descriptor(my_math_error_subtype) = {
  /* This "parent" field is set below by the module initialisation function. */
  .descriptor.parent		= NULL,
  .descriptor.final		= cclib_method(cclib_exceptional_condition_descriptor_type(my_math_error_subtype), final),
  .descriptor.delete		= cclib_method(cclib_exceptional_condition_descriptor_type(my_math_error_subtype), delete),
  .descriptor.static_message	= cclib_method(cclib_exceptional_condition_descriptor_type(my_math_error_subtype), static_message)
};

void
cclib_exceptional_condition_descriptor_set_parent_to(my_math_error_subtype) (cce_descriptor_t * const D)
{
  D->parent = cclib_exceptional_condition_descriptor_pointer(my_math_error_subtype);
}


/** --------------------------------------------------------------------
 ** Condition type descriptor: protocol functions.
 ** ----------------------------------------------------------------- */

void
cclib_method(cclib_exceptional_condition_descriptor_type(my_math_error_subtype), final) (cce_condition_t * _C)
/* Finalisation   functions    are   called    automatically   when    the   function
   "cce_condition_final()" is applied  to the argument C.  Here we  finalise only the
   fields of this type leaving untouched the fields of the parent type. */
{
  CCLIB_PC(cclib_exceptional_condition_object_type(my_math_error_subtype), C, _C);

  *(C->data) = 0;
  free(C->data);
  if (1) { fprintf(stderr, "%s: finalised %p\n", __func__, (void*)C); }
}

void
cclib_method(cclib_exceptional_condition_descriptor_type(my_math_error_subtype), delete) (cce_condition_t * _C)
/* The  delete  function  is  called  automatically  when  the  client  code  applies
   "cce_condition_delete()" to the argument C.   Here we release memory allocated for
   the condition object. */
{
  CCLIB_PC(cclib_exceptional_condition_object_type(my_math_error_subtype), C, _C);

  free(C);
  if (1) { fprintf(stderr, "%s: deleted %p\n", __func__, (void*)C); }
}

char const *
cclib_method(cclib_exceptional_condition_descriptor_type(my_math_error_subtype), static_message) (cce_condition_t const * C CCLIB_UNUSED)
{
  return "Math_Error subtype exceptional condition";
}


/** --------------------------------------------------------------------
 ** Condition object type: constructor functions.
 ** ----------------------------------------------------------------- */

void
cclib_init(cclib_exceptional_condition_object_type(my_math_error_subtype))
  (cce_destination_t L, cclib_exceptional_condition_object_type(my_math_error_subtype) * C, int the_data)
/* This initialisation function must be called both by:
 *
 * - The constructor function of this object type.
 *
 * - The initialisation functions of object types derived from this type.
 *
 * Here we call  the parent's initialisation function; then we  initialise the fields
 * of this type.
 */
{
  cclib_init(cclib_exceptional_condition_object_type(cce_math_error))(&(C->parent));
  C->data = cce_sys_malloc(L, sizeof(int));
  *(C->data) = the_data;
  if (1) { fprintf(stderr, "%s: initialised %p\n", __func__, (void*)C); }
}

cce_condition_t const *
cclib_new(cclib_exceptional_condition_object_type(my_math_error_subtype)) (cce_destination_t upper_L, int the_data)
/* This constructor function is the public  interface to the constructor of condition
 * objects of type "my_condition_math_error_subtype_t".
 *
 * Here we:
 *
 * 1. Allocate memory for the condition object itself.
 *
 * 2. Initialise the descriptor field by calling "cce_condition_init()".
 *
 * 3. Call the initialisation function for this type.
 */
{
  cce_location_t	L[1];
  cce_error_handler_t	C_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    cclib_exceptional_condition_object_type(my_math_error_subtype) * C =
      cce_sys_malloc_guarded(L, C_H, sizeof(cclib_exceptional_condition_object_type(my_math_error_subtype)));

    cce_condition_init((cce_condition_t *) C, cclib_exceptional_condition_descriptor_pointer(my_math_error_subtype));
    cclib_init(cclib_exceptional_condition_object_type(my_math_error_subtype))(L, C, the_data);

    cce_run_body_handlers(L);
    if (1) { fprintf(stderr, "%s: constructed %p\n", __func__, (void*)C); }
    return (cce_condition_t const *) C;
  }
}

bool
cclib_is(cclib_exceptional_condition_object_type(my_math_error_subtype)) (cce_condition_t const * C)
{
  return cce_condition_is(C, cclib_exceptional_condition_descriptor_pointer(my_math_error_subtype));
}


/** --------------------------------------------------------------------
 ** Module initialisation.
 ** ----------------------------------------------------------------- */

void
math_error_cclib_subtyping_init_module (void)
{
  cclib_exceptional_condition_descriptor_set_parent_to(cce_math_error)(cclib_exceptional_condition_descriptor_pointer(my_math_error_subtype));
}

/* end of file */
