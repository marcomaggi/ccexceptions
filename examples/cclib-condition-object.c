/*
  Part of: CCExceptions
  Contents: example of condition object type definition
  Date: Apr 16, 2020

  Abstract

	This is the body file of an example of condition object type definition.

	This file contains  body definitions for a new condition  object type derived
	from  "cce_condition_runtime_error_t".  No  inline  functions; new  condition
	objects  allocated by  a  constructor; use  of  the CCLibraries  preprocessor
	macros.

  Copyright (C) 2020 Marco Maggi <mrc.mgg@gmail.com>

  The author  hereby grant permission to  use, copy, modify, distribute,  and license
  this  software  and its  documentation  for  any  purpose, provided  that  existing
  copyright  notices are  retained in  all copies  and that  this notice  is included
  verbatim in  any distributions. No  written agreement,  license, or royalty  fee is
  required for  any of the  authorized uses.  Modifications  to this software  may be
  copyrighted by  their authors  and need  not follow  the licensing  terms described
  here, provided that the  new terms are clearly indicated on the  first page of each
  file where they apply.

  IN NO  EVENT SHALL THE AUTHOR  OR DISTRIBUTORS BE  LIABLE TO ANY PARTY  FOR DIRECT,
  INDIRECT, SPECIAL, INCIDENTAL,  OR CONSEQUENTIAL DAMAGES ARISING OUT OF  THE USE OF
  THIS SOFTWARE,  ITS DOCUMENTATION, OR ANY  DERIVATIVES THEREOF, EVEN IF  THE AUTHOR
  HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  THE AUTHOR  AND DISTRIBUTORS SPECIFICALLY  DISCLAIM ANY WARRANTIES,  INCLUDING, BUT
  NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
  PURPOSE, AND NON-INFRINGEMENT.  THIS SOFTWARE IS  PROVIDED ON AN "AS IS" BASIS, AND
  THE AUTHOR  AND DISTRIBUTORS  HAVE NO OBLIGATION  TO PROVIDE  MAINTENANCE, SUPPORT,
  UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
*/


/** --------------------------------------------------------------------
 ** Heaaders.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include "cclib-condition-object.h"
#include <stdio.h>
#include <stdlib.h>


/** --------------------------------------------------------------------
 ** Condition type descriptor definition.
 ** ----------------------------------------------------------------- */

static cce_condition_final_fun_t		cclib_method(cclib_exceptional_condition_descriptor_type(my_error_2), final);
static cce_condition_delete_fun_t		cclib_method(cclib_exceptional_condition_descriptor_type(my_error_2), delete);
static cce_condition_static_message_fun_t	cclib_method(cclib_exceptional_condition_descriptor_type(my_error_2), static_message);

static cclib_exceptional_condition_descriptor_type(my_error_2) cclib_exceptional_condition_descriptor(my_error_2) = {
  /* This "parent" field is set below by the module initialisation function. */
  .descriptor.parent		= NULL,
  .descriptor.final		= cclib_method(cclib_exceptional_condition_descriptor_type(my_error_2), final),
  .descriptor.delete		= cclib_method(cclib_exceptional_condition_descriptor_type(my_error_2), delete),
  .descriptor.static_message	= cclib_method(cclib_exceptional_condition_descriptor_type(my_error_2), static_message)
};

void
cclib_exceptional_condition_descriptor_set_parent_to(my_error_2) (cce_descriptor_t * const D)
{
  D->parent = cclib_exceptional_condition_descriptor_pointer(my_error_2);
}


/** --------------------------------------------------------------------
 ** Condition type descriptor: protocol functions.
 ** ----------------------------------------------------------------- */

void
cclib_method(cclib_exceptional_condition_descriptor_type(my_error_2), final) (cce_condition_t * _C)
/* Finalisation   functions    are   called    automatically   when    the   function
   "cce_condition_final()" is applied  to the argument C.  Here we  finalise only the
   fields of this type leaving untouched the fields of the parent type. */
{
  CCLIB_PC(cclib_exceptional_condition_object_type(my_error_2), C, _C);
  *(C->data) = 0;
  if (1) { fprintf(stderr, "%s: finalising %p\n", __func__, (void*)C); }
  free(C->data);
}

void
cclib_method(cclib_exceptional_condition_descriptor_type(my_error_2), delete) (cce_condition_t * _C)
/* The  delete  function  is  called  automatically  when  the  client  code  applies
   "cce_condition_delete()" to the argument C.   Here we release memory allocated for
   the condition object. */
{
  CCLIB_PC(cclib_exceptional_condition_object_type(my_error_2), C, _C);

  if (1) { fprintf(stderr, "%s: deleting %p\n", __func__, (void*)C); }
  free(C);
}

char const *
cclib_method(cclib_exceptional_condition_descriptor_type(my_error_2), static_message) (cce_condition_t const * C CCLIB_UNUSED)
{
  return "Error-1 exceptional condition";
}


/** --------------------------------------------------------------------
 ** Condition-object type: constructor functions.
 ** ----------------------------------------------------------------- */

void
cclib_init(cclib_exceptional_condition_object_type(my_error_2))
  (cce_destination_t L, cclib_exceptional_condition_object_type(my_error_2) * C, int the_data)
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
  cce_condition_init_runtime_error(&(C->runtime_error));
  C->data = cce_sys_malloc(L, sizeof(int));
  *(C->data) = the_data;
  if (1) { fprintf(stderr, "%s: initialised %p\n", __func__, (void*)C); }
}

cce_condition_t const *
cclib_new(cclib_exceptional_condition_object_type(my_error_2)) (cce_destination_t upper_L, int the_data)
/* This constructor function is the public  interface to the constructor of condition
 * objects of type "cclib_exceptional_condition_object_type(my_error_2)".
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
    cclib_exceptional_condition_object_type(my_error_2) * C =
      cce_sys_malloc_guarded(L, C_H, sizeof(cclib_exceptional_condition_object_type(my_error_2)));

    cce_condition_init((cce_condition_t *) C, cclib_exceptional_condition_descriptor_pointer(my_error_2));
    cclib_init(cclib_exceptional_condition_object_type(my_error_2))(L, C, the_data);

    cce_run_body_handlers(L);
    if (1) { fprintf(stderr, "%s: constructed %p\n", __func__, (void*)C); }
    return (cce_condition_t const *) C;
  }
}


/** --------------------------------------------------------------------
 ** Condition-object type: predicate function.
 ** ----------------------------------------------------------------- */

bool
cclib_exceptional_condition_object_is(my_error_2) (cce_condition_t const * C)
{
  return cce_condition_is(C, cclib_exceptional_condition_descriptor_pointer(my_error_2));
}


/** --------------------------------------------------------------------
 ** Module initialisation.
 ** ----------------------------------------------------------------- */

void
my_plain_init_module (void)
{
  cce_descriptor_set_parent_to(cce_descriptor_runtime_error_t)(cclib_exceptional_condition_descriptor_pointer(my_error_2));
}

/* end of file */
