/*
  Part of: CCExceptions
  Contents: demo program for structs as values with no descriptor, header file
  Date: Apr 11, 2020

  Abstract

	This header file defines the struct  "my_coords_t" as value, using the common
	API.

  Copyright (C) 2019-2020 Marco Maggi <mrc.mgg@gmail.com>

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

#ifndef STRUCT_AS_VALUE_NO_DESCR_H
#define STRUCT_AS_VALUE_NO_DESCR_H

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
 ** Type definitions: data struct "my_coords_t".
 ** ----------------------------------------------------------------- */

typedef struct my_coords_t	my_coords_t;

struct my_coords_t {
  double	*X;
  double	*Y;
};


/** --------------------------------------------------------------------
 ** Data struct "my_coords_t": well known functions API.
 ** ----------------------------------------------------------------- */

/* Maker function.  This initialises from rectangular coordinates. */
cclib_decl my_coords_t cclib_make(my_coords_t, rec) (cce_destination_t L, double X, double Y);

/* Maker function.  This initialises from polar coordinates. */
cclib_decl my_coords_t cclib_make(my_coords_t, pol) (cce_destination_t L, double RHO, double THETA);

/* Destructor function. */
cclib_decl void cclib_unmake(my_coords_t) (my_coords_t S);

/* Destructor function. */
cclib_decl void cclib_final(my_coords_t) (my_coords_t * S);


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* define STRUCT_AS_VALUE_NO_DESCR_H */

/* end of file */
