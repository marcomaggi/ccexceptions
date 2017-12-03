/*
  Part of: CCExceptions
  Contents: body definitions of a subtype of "error"
  Date: Dec  3, 2017

  Abstract

	Body definitions of a subtype of "error".

  Copyright (C) 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

  See the COPYING file.
*/


/** --------------------------------------------------------------------
 ** Heaaders.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include "error-subtyping-header.h"
#include <stdio.h>
#include <stdlib.h>


/** --------------------------------------------------------------------
 ** Code definitions.
 ** ----------------------------------------------------------------- */

static void
my_condition_final_error_subtype (cce_condition_t * _C)
/* Here we finalise  only the fields of this type  leaving untouched the
   fields of the parent type. */
{
  my_condition_error_subtype_t * C = (my_condition_error_subtype_t *) _C;
  *(C->data) = 0;
  if (1) { fprintf(stderr, "%s: finalised %p\n", __func__, (void*)C); }
}

static void
my_condition_delete_error_subtype (cce_condition_t * _C)
{
  my_condition_error_subtype_t * C = (my_condition_error_subtype_t *) _C;

  free(C->data);
  free(C);
  if (1) { fprintf(stderr, "%s: deleted %p\n", __func__, (void*)C); }
}

static char const *
my_condition_static_message_error_subtype (cce_condition_t const * C CCE_UNUSED)
{
  return "Error subtype exceptional condition";
}

static my_descriptor_error_subtype_t my_descriptor_error_subtype_stru = {
  /* This field is set below by the module initialisation function. */
  .descriptor.parent		= NULL,
  .descriptor.delete		= my_condition_delete_error_subtype,
  .descriptor.final		= my_condition_final_error_subtype,
  .descriptor.static_message	= my_condition_static_message_error_subtype
};

my_descriptor_error_subtype_t const * const my_descriptor_error_subtype_ptr = &my_descriptor_error_subtype_stru;

void
my_condition_init_error_subtype (my_condition_error_subtype_t * C, int the_data)
/* Here we call the parent's initialisation function; then we initialise
   the fields of this type. */
{
  cce_condition_init_error(&(C->parent));
  *(C->data) = the_data;
}

cce_condition_t const *
my_condition_new_error_subtype (cce_destination_t L, int the_data)
/* Here  we  allocate  the  asynchronous resources  and  initialise  the
   descriptor field; then we call the initialisation function. */
{
  my_condition_error_subtype_t * C = cce_sys_malloc(L, sizeof(my_condition_error_subtype_t));
  C->data = cce_sys_malloc(L, sizeof(int));
  cce_condition_init((cce_condition_t *) C, &(my_descriptor_error_subtype_ptr->descriptor));
  my_condition_init_error_subtype(C, the_data);
  return (cce_condition_t const *) C;
}


void
error_subtyping_init_module (void)
{
  my_descriptor_error_subtype_stru.descriptor.parent = &(cce_descriptor_error_ptr->descriptor);
}

/* end of file */
