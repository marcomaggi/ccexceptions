/*
  Part of: CCExceptions
  Contents: body definitions of a subtype of "unimplemented"
  Date: Dec  3, 2017

  Abstract

	Body definitions of a subtype of "unimplemented".

  Copyright (C) 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

  See the COPYING file.
*/


/** --------------------------------------------------------------------
 ** Heaaders.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include "condition-subtyping-unimplemented-header.h"
#include <stdio.h>
#include <stdlib.h>


/** --------------------------------------------------------------------
 ** Condition type descriptor definition.
 ** ----------------------------------------------------------------- */

static cce_condition_delete_fun_t		my_condition_delete_unimplemented_subtype;
static cce_condition_final_fun_t		my_condition_final_unimplemented_subtype;
static cce_condition_static_message_fun_t	my_condition_static_message_unimplemented_subtype;

static my_descriptor_unimplemented_subtype_t my_descriptor_unimplemented_subtype_stru = {
  /* This  "parent" field  is  set below  by  the module  initialisation
     function. */
  .descriptor.parent		= NULL,
  .descriptor.delete		= my_condition_delete_unimplemented_subtype,
  .descriptor.final		= my_condition_final_unimplemented_subtype,
  .descriptor.static_message	= my_condition_static_message_unimplemented_subtype
};

my_descriptor_unimplemented_subtype_t const * const my_descriptor_unimplemented_subtype_ptr = &my_descriptor_unimplemented_subtype_stru;


/** --------------------------------------------------------------------
 ** Condition type descriptor: protocol functions.
 ** ----------------------------------------------------------------- */

void
my_condition_final_unimplemented_subtype (cce_condition_t * _C)
/* Finalisation  functions are  called automatically  when the  function
   "cce_condition_final()"  is  applied  to  the argument  C.   Here  we
   finalise only the fields of this type leaving untouched the fields of
   the parent type. */
{
  my_condition_unimplemented_subtype_t * C = (my_condition_unimplemented_subtype_t *) _C;
  *(C->data) = 0;
  free(C->data);
  if (1) { fprintf(stderr, "%s: finalised %p\n", __func__, (void*)C); }
}

void
my_condition_delete_unimplemented_subtype (cce_condition_t * _C)
/* The  delete  function  is  called  automatically  when  code  applies
   "cce_condition_delete()" to  the argument C.  Here  we release memory
   allocated for the condition object. */
{
  my_condition_unimplemented_subtype_t * C = (my_condition_unimplemented_subtype_t *) _C;

  free(C);
  if (1) { fprintf(stderr, "%s: deleted %p\n", __func__, (void*)C); }
}

char const *
my_condition_static_message_unimplemented_subtype (cce_condition_t const * C CCE_UNUSED)
{
  return "Unimplemented subtype exceptional condition";
}


/** --------------------------------------------------------------------
 ** Condition object type: constructor functions.
 ** ----------------------------------------------------------------- */

void
my_condition_init_unimplemented_subtype (cce_destination_t L, my_condition_unimplemented_subtype_t * C, int the_data)
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
  cce_condition_init_unimplemented(&(C->unimplemented));
  C->data = cce_sys_malloc(L, sizeof(int));
  *(C->data) = the_data;
  if (1) { fprintf(stderr, "%s: initialised %p\n", __func__, (void*)C); }
}

cce_condition_t const *
my_condition_new_unimplemented_subtype (cce_destination_t upper_L, int the_data)
/* This constructor function is the  public interface to the constructor
 * of condition objects of type "my_condition_unimplemented_subtype_t".
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
  cce_handler_t		C_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    my_condition_unimplemented_subtype_t * C = cce_sys_malloc(L, sizeof(my_condition_unimplemented_subtype_t));
    cce_error_handler_malloc_init(L, C_H, C);

    cce_condition_init((cce_condition_t *) C, &(my_descriptor_unimplemented_subtype_ptr->descriptor));
    my_condition_init_unimplemented_subtype(L, C, the_data);

    cce_run_cleanup_handlers(L);
    if (1) { fprintf(stderr, "%s: constructed %p\n", __func__, (void*)C); }
    return (cce_condition_t const *) C;
  }
}


void
unimplemented_subtyping_init_module (void)
{
  my_descriptor_unimplemented_subtype_stru.descriptor.parent = &(cce_descriptor_unimplemented_ptr->descriptor);
}

/* end of file */
