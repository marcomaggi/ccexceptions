/*
  Part of: CCExceptions
  Contents: body definitions of a subtype of "runtime error"
  Date: Dec  3, 2017

  Abstract

	Body definitions of a subtype of "runtime error".

  Copyright (C) 2017, 2018, 2019 Marco Maggi <marco.maggi-ipsu@poste.it>

  See the COPYING file.
*/


/** --------------------------------------------------------------------
 ** Heaaders.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include "condition-subtyping-runtime-error-header.h"
#include <stdio.h>
#include <stdlib.h>


/** --------------------------------------------------------------------
 ** Condition type descriptor definition.
 ** ----------------------------------------------------------------- */

static ccname_method_type(cce_condition_t, release)		my_condition_release_runtime_error_subtype;
static ccname_method_type(cce_condition_t, final)		my_condition_final_runtime_error_subtype;
static ccname_method_type(cce_condition_t, static_message)	my_condition_static_message_runtime_error_subtype;

static my_descriptor_runtime_error_subtype_t my_descriptor_runtime_error_subtype_stru = {
  /* This  "parent" field  is  set below  by  the module  initialisation
     function. */
  .descriptor.parent		= NULL,
  .descriptor.release		= my_condition_release_runtime_error_subtype,
  .descriptor.final		= my_condition_final_runtime_error_subtype,
  .descriptor.static_message	= my_condition_static_message_runtime_error_subtype
};

my_descriptor_runtime_error_subtype_t const * const my_descriptor_runtime_error_subtype_ptr = &my_descriptor_runtime_error_subtype_stru;


/** --------------------------------------------------------------------
 ** Condition type descriptor: protocol functions.
 ** ----------------------------------------------------------------- */

void
my_condition_final_runtime_error_subtype (cce_condition_t * _C)
/* Finalisation  functions are  called automatically  when the  function
   "ccname_final(cce_condition_t)()"  is  applied  to  the argument  C.   Here  we
   finalise only the fields of this type leaving untouched the fields of
   the parent type. */
{
  my_condition_runtime_error_subtype_t * C = (my_condition_runtime_error_subtype_t *) _C;
  *(C->data) = 0;
  free(C->data);
  if (1) { fprintf(stderr, "%s: finalised %p\n", __func__, (void*)C); }
}

void
my_condition_release_runtime_error_subtype (cce_condition_t * _C)
/* The  release function  is called  automatically when  the client  code
   applies "ccname_delete(cce_condition_t)()" to the  argument C.  Here we release
   memory allocated for the condition object. */
{
  my_condition_runtime_error_subtype_t * C = (my_condition_runtime_error_subtype_t *) _C;

  free(C);
  if (1) { fprintf(stderr, "%s: released %p\n", __func__, (void*)C); }
}

char const *
my_condition_static_message_runtime_error_subtype (cce_condition_t const * C CCE_UNUSED)
{
  return "Runtime error subtype exceptional condition";
}


/** --------------------------------------------------------------------
 ** Condition object type: constructor functions.
 ** ----------------------------------------------------------------- */

void
my_condition_init_runtime_error_subtype (cce_destination_t L, my_condition_runtime_error_subtype_t * C, int the_data)
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
  ccname_init(cce_condition_t, runtime_error)(&(C->runtime_error));
  C->data = cce_sys_malloc(L, sizeof(int));
  *(C->data) = the_data;
  if (1) { fprintf(stderr, "%s: initialised %p\n", __func__, (void*)C); }
}

cce_condition_t const *
my_condition_new_runtime_error_subtype (cce_destination_t upper_L, int the_data)
/* This constructor function is the  public interface to the constructor
 * of condition objects of type "my_condition_runtime_error_subtype_t".
 *
 * Here we:
 *
 * 1. Allocate memory for the condition object itself.
 *
 * 2. Initialise the descriptor field by calling "ccname_init(cce_condition_t)()".
 *
 * 3. Call the initialisation function for this type.
 */
{
  cce_location_t	L[1];
  cce_error_handler_t	C_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    my_condition_runtime_error_subtype_t * C = cce_sys_malloc_guarded(L, C_H, sizeof(my_condition_runtime_error_subtype_t));

    ccname_init(cce_condition_t)((cce_condition_t *) C, &(my_descriptor_runtime_error_subtype_ptr->descriptor));
    my_condition_init_runtime_error_subtype(L, C, the_data);

    cce_run_body_handlers(L);
    if (1) { fprintf(stderr, "%s: constructed %p\n", __func__, (void*)C); }
    return (cce_condition_t const *) C;
  }
}


void
runtime_error_subtyping_init_module (void)
{
  my_descriptor_runtime_error_subtype_stru.descriptor.parent = &(cce_descriptor_runtime_error_ptr->descriptor);
}

/* end of file */
