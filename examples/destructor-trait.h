/*
  Part of: CCExceptions
  Contents: example definition of a destructor trait
  Date: Apr 12, 2020

  Abstract

	This  header  file  defines  the  trait  "my_destructor_T".   It  is  a  data
	structure, passed  as value, using the  common structs API, using  the struct
	descriptor API.   The purpose of  this trait is to  provide a unified  API to
	call the destructor of any resource.

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

#ifndef DESTRUCTOR_TRAIT_H
#define DESTRUCTOR_TRAIT_H

#ifdef __cplusplus
extern "C" {
#endif


/** --------------------------------------------------------------------
 ** Descrs.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include <stdio.h>
#include <stdlib.h>


/** --------------------------------------------------------------------
 ** Destructor trait.
 ** ----------------------------------------------------------------- */

CCLIB_DEFINE_TRAIT(my_destructor_T);

/* A typedef for every method. */
typedef void                            cclib_method_type(my_destructor_T, destroy) (my_destructor_T self);
typedef cce_resource_destructor_fun_t * cclib_method_type(my_destructor_T, retrieve_cce_resource_destructor) (my_destructor_T self);

/* The methods table declaration. */
struct cclib_methods_table_type(my_destructor_T) {
  cclib_method_type(my_destructor_T, destroy)				*destroy;
  cclib_method_type(my_destructor_T, retrieve_cce_resource_destructor)	*retrieve_cce_resource_destructor;
};


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* define DESTRUCTOR_TRAIT_H */

/* end of file */
