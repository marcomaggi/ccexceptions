/*
  Part of: CCExceptions
  Contents: example of condition object type definition
  Date: Dec  5, 2017

  Abstract

	This is the body  file of an example of condition  object type definition; it
	goes along with the files "plain.c" and "plain-header.h".

	This file contains  body definitions for a new condition  object type derived
	from  "ccname_type(cce_condition_t,  runtime_error)".   The definition  is  a
	"plain"  one: no  inline  functions;  new condition  objects  allocated by  a
	constructor.

  Copyright (C) 2017, 2018, 2019 Marco Maggi <marco.maggi-ipsu@poste.it>

  See the COPYING file.
*/


/** --------------------------------------------------------------------
 ** Heaaders.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include "plain-header.h"
#include <stdio.h>
#include <stdlib.h>


/** --------------------------------------------------------------------
 ** Condition type descriptor definition.
 ** ----------------------------------------------------------------- */

static ccname_method_type(cce_condition_t, release)		my_condition_release_error_1;
static ccname_method_type(cce_condition_t, final)		my_condition_final_error_1;
static ccname_method_type(cce_condition_t, static_message)	my_condition_static_message_error_1;

static my_descriptor_error_1_t my_descriptor_error_1_stru = {
  /* This  "parent" field  is  set below  by  the module  initialisation
     function. */
  .descriptor.parent		= NULL,
  .descriptor.release		= my_condition_release_error_1,
  .descriptor.final		= my_condition_final_error_1,
  .descriptor.static_message	= my_condition_static_message_error_1
};

my_descriptor_error_1_t const * const my_descriptor_error_1_ptr = &my_descriptor_error_1_stru;


/** --------------------------------------------------------------------
 ** Condition type descriptor: protocol functions.
 ** ----------------------------------------------------------------- */

void
my_condition_final_error_1 (cce_condition_t * _C)
/* Finalisation  functions are  called automatically  when the  function
   "ccname_final(cce_condition_t)()"  is  applied  to  the argument  C.   Here  we
   finalise only the fields of this type leaving untouched the fields of
   the parent type. */
{
  my_condition_error_1_t * C = (my_condition_error_1_t *) _C;
  *(C->data) = 0;
  if (1) { fprintf(stderr, "%s: finalising %p\n", __func__, (void*)C); }
  free(C->data);
}

void
my_condition_release_error_1 (cce_condition_t * _C)
/* The  release  function  is  called  automatically when  the  client  code  applies
   "ccname_delete(cce_condition_t)()" to the argument C.   Here we release memory allocated for
   the condition object. */
{
  my_condition_error_1_t * C = (my_condition_error_1_t *) _C;

  if (1) { fprintf(stderr, "%s: released %p\n", __func__, (void*)C); }
  free(C);
}

char const *
my_condition_static_message_error_1 (cce_condition_t const * C CCE_UNUSED)
{
  return "Error-1 exceptional condition";
}


/** --------------------------------------------------------------------
 ** Condition-object type: constructor functions.
 ** ----------------------------------------------------------------- */

void
my_condition_init_error_1 (cce_destination_t L, my_condition_error_1_t * C, int the_data)
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
my_condition_new_error_1 (cce_destination_t upper_L, int the_data)
/* This constructor function is the  public interface to the constructor
 * of condition objects of type "my_condition_error_1_t".
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
    my_condition_error_1_t * C = cce_sys_malloc_guarded(L, C_H, sizeof(my_condition_error_1_t));

    ccname_init(cce_condition_t)((cce_condition_t *) C, &(my_descriptor_error_1_ptr->descriptor));
    my_condition_init_error_1(L, C, the_data);

    cce_run_body_handlers(L);
    if (1) { fprintf(stderr, "%s: constructed %p\n", __func__, (void*)C); }
    return (cce_condition_t const *) C;
  }
}


/** --------------------------------------------------------------------
 ** Condition-object type: predicate function.
 ** ----------------------------------------------------------------- */

bool
my_condition_is_error_1 (cce_condition_t const * C)
{
  return ccname_is(cce_condition_t)(C, &(my_descriptor_error_1_ptr->descriptor));
}


/** --------------------------------------------------------------------
 ** Module initialisation.
 ** ----------------------------------------------------------------- */

void
plain_init_module (void)
{
  my_descriptor_error_1_stru.descriptor.parent = &(cce_descriptor_runtime_error_ptr->descriptor);
}

/* end of file */
