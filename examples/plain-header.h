/*
  Part of: CCExceptions
  Contents: example of condition object type definition
  Date: Dec  5, 2017

  Abstract

	This is the header file of an example of condition object type definition; it
	goes along with the files "plain.c" and "plain-body.c".

	This file contains header definitions for a new condition object type derived
	from  "ccname_type(cce_condition_t,  runtime_error)".   The definition  is  a
	"plain"  one: no  inline  functions;  new condition  objects  allocated by  a
	constructor.

  Copyright (C) 2017, 2019 Marco Maggi <marco.maggi-ipsu@poste.it>

  See the COPYING file.
*/

#ifndef PLAIN_HEADER_H
#define PLAIN_HEADER_H 1


/** --------------------------------------------------------------------
 ** Heaaders.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include <stdio.h>
#include <stdlib.h>


/** --------------------------------------------------------------------
 ** Header definitions.
 ** ----------------------------------------------------------------- */

typedef struct my_descriptor_error_1_t	my_descriptor_error_1_t;
typedef struct my_condition_error_1_t	my_condition_error_1_t;

struct my_descriptor_error_1_t {
  cce_descriptor_t	descriptor;
};

struct my_condition_error_1_t {
  ccname_type(cce_condition_t, runtime_error)	runtime_error;
  int *				data;
};

extern my_descriptor_error_1_t const * const	my_descriptor_error_1_ptr;

extern void my_condition_init_error_1 (cce_destination_t L, my_condition_error_1_t * C, int the_data)
  __attribute__((__nonnull__(1)));

extern cce_condition_t const * my_condition_new_error_1 (cce_destination_t L, int the_data)
  __attribute__((__nonnull__(1)));

extern bool my_condition_is_error_1 (cce_condition_t const * C)
  __attribute__((__pure__,__nonnull__(1)));

extern void plain_init_module (void);


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#endif /* PLAIN_HEADER_H */

/* end of file */
