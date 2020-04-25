/*
  Part of: CCExceptions
  Contents: example of condition object type definition, cclib API
  Date: Apr 16, 2020

  Abstract

	This is the header file of an example of condition object type definition.

	This file contains header definitions for a new condition object type derived
	from  "cce_condition_runtime_error_t".  No  inline  functions; new  condition
	objects allocated by a constructor; use of the CCLibraries macros.

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

#ifndef CCLIB_CONDITION_OBJECT_ALIAS_H
#define CCLIB_CONDITION_OBJECT_ALIAS_H 1


/** --------------------------------------------------------------------
 ** Heaaders.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include <stdio.h>
#include <stdlib.h>


/** --------------------------------------------------------------------
 ** Module initialisation.
 ** ----------------------------------------------------------------- */

extern void my_plain_init_module (void);


/** --------------------------------------------------------------------
 ** Header definitions.
 ** ----------------------------------------------------------------- */

CCLIB_STRUCT_TYPEDEF(cclib_exceptional_condition_descriptor_t(my_error_3));
CCLIB_STRUCT_TYPEDEF(cclib_exceptional_condition_object_t(my_error_3));

struct cclib_exceptional_condition_descriptor_t(my_error_3) {
  cce_descriptor_t	descriptor;
};

struct cclib_exceptional_condition_object_t(my_error_3) {
  cce_condition_runtime_error_t	runtime_error;
  int *				data;
};

cclib_decl void cclib_exceptional_condition_descriptor_set_parent_to(my_error_3) (cce_descriptor_t * D)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1);

/* ------------------------------------------------------------------ */

cclib_decl void cclib_init(cclib_exceptional_condition_object_t(my_error_3))
  (cce_destination_t L, cclib_exceptional_condition_object_t(my_error_3) * C, int the_data)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2);

cclib_decl cce_condition_t const * cclib_new(cclib_exceptional_condition_object_t(my_error_3)) (cce_destination_t L, int the_data)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL;

cclib_decl bool cclib_is(cclib_exceptional_condition_object_t(my_error_3)) (cce_condition_t const * C)
  CCLIB_FUNC_ATTRIBUTE_PURE
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1);


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#endif /* CCLIB_CONDITION_OBJECT_ALIAS_H */

/* end of file */
