/*
  Part of: CCExceptions
  Contents: body definitions of a subtype of "break"
  Date: Dec  3, 2017

  Abstract

	Body definitions of a subtype of "break".

  Copyright (C) 2017, 2018, 2019, 2020 Marco Maggi <mrc.mgg@gmail.com>

  See the COPYING file.
*/


/** --------------------------------------------------------------------
 ** Heaaders.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include "condition-subtyping-break.h"
#include <stdio.h>
#include <stdlib.h>


/** --------------------------------------------------------------------
 ** Condition type descriptor definition.
 ** ----------------------------------------------------------------- */

static cce_condition_delete_fun_t		my_condition_delete_break_subtype;
static cce_condition_final_fun_t		my_condition_final_break_subtype;
static cce_condition_static_message_fun_t	my_condition_static_message_break_subtype;

static my_descriptor_break_subtype_t my_descriptor_break_subtype = {
  /* This  "parent" field  is  set below  by  the module  initialisation
     function. */
  .descriptor.parent		= NULL,
  .descriptor.delete		= my_condition_delete_break_subtype,
  .descriptor.final		= my_condition_final_break_subtype,
  .descriptor.static_message	= my_condition_static_message_break_subtype
};

void
cce_descriptor_set_parent_to(my_descriptor_break_subtype_t) (cce_descriptor_t * const D)
{
  D->parent = cce_descriptor_pointer(my_descriptor_break_subtype);
}


/** --------------------------------------------------------------------
 ** Condition type descriptor: protocol functions.
 ** ----------------------------------------------------------------- */

void
my_condition_final_break_subtype (cce_condition_t * _C)
/* Finalisation  functions are  called automatically  when the  function
   "cce_condition_final()"  is  applied  to  the argument  C.   Here  we
   finalise only the fields of this type leaving untouched the fields of
   the parent type. */
{
  my_condition_break_subtype_t * C = (my_condition_break_subtype_t *) _C;
  *(C->data) = 0;
  free(C->data);
  if (1) { fprintf(stderr, "%s: finalised %p\n", __func__, (void*)C); }
}

void
my_condition_delete_break_subtype (cce_condition_t * _C)
/* The  delete function  is called  automatically when  the client  code
   applies "cce_condition_delete()" to the  argument C.  Here we release
   memory allocated for the condition object. */
{
  my_condition_break_subtype_t * C = (my_condition_break_subtype_t *) _C;

  free(C);
  if (1) { fprintf(stderr, "%s: deleted %p\n", __func__, (void*)C); }
}

char const *
my_condition_static_message_break_subtype (cce_condition_t const * C CCLIB_UNUSED)
{
  return "Break subtype exceptional condition";
}


/** --------------------------------------------------------------------
 ** Condition object type: constructor functions.
 ** ----------------------------------------------------------------- */

void
my_condition_init_break_subtype (cce_destination_t L, my_condition_break_subtype_t * C, int the_data)
/* This initialisation function must be called both by:
 *
 * - The constructor function of this object type.
 *
 * - The  initialisation functions  of  object types  derived from  this
 *   type.
 *
 * Here we call the parent's initialisation function; then we initialise
 * the fields of this type.
 */
{
  cce_condition_init_break(&(C->parent));
  C->data = cce_sys_malloc(L, sizeof(int));
  *(C->data) = the_data;
  if (1) { fprintf(stderr, "%s: initialised %p\n", __func__, (void*)C); }
}

cce_condition_t const *
my_condition_new_break_subtype (cce_destination_t upper_L, int the_data)
/* This constructor function is the  public interface to the constructor
 * of condition objects of type "my_condition_break_subtype_t".
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
    my_condition_break_subtype_t * C = cce_sys_malloc_guarded(L, C_H, sizeof(my_condition_break_subtype_t));

    cce_condition_init((cce_condition_t *) C, cce_descriptor_pointer(my_descriptor_break_subtype));
    my_condition_init_break_subtype(L, C, the_data);

    cce_run_body_handlers(L);
    if (1) { fprintf(stderr, "%s: constructed %p\n", __func__, (void*)C); }
    return (cce_condition_t const *) C;
  }
}

bool
my_condition_is_break_subtype (cce_condition_t const * C)
{
  return cce_condition_is(C, cce_descriptor_pointer(my_descriptor_break_subtype));
}


void
break_subtyping_init_module (void)
{
  cce_descriptor_set_parent_to(cce_descriptor_break_t)(cce_descriptor_pointer(my_descriptor_break_subtype));
}

/* end of file */
