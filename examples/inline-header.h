/*
  Part of: CCExceptions
  Contents: example of condition object type definition
  Date: Dec  5, 2017

  Abstract

	This is the  header file of an example of  condition object type
	definition;  it  goes  along   with  the  files  "inline.c"  and
	"inline-body.c".

	This file contains header definitions for a new condition object
	type   derived    from   "cce_condition_runtime_error_t".    The
	definition is a "inline" one: as much as possible it uses inline
	functions; new condition objects allocated by a constructor.

  Copyright (C) 2017, 2018 Marco Maggi <marco.maggi-ipsu@poste.it>

  See the COPYING file.
*/

#ifndef INLINE_HEADER_H
#define INLINE_HEADER_H 1


/** --------------------------------------------------------------------
 ** Heaaders.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include <stdio.h>
#include <stdlib.h>


/** --------------------------------------------------------------------
 ** Header definitions.
 ** ----------------------------------------------------------------- */

typedef struct my_descriptor_error_2_t	my_descriptor_error_2_t;
typedef struct my_condition_error_2_t	my_condition_error_2_t;

struct my_descriptor_error_2_t {
  cce_descriptor_t	descriptor;
};

struct my_condition_error_2_t {
  cce_condition_runtime_error_t	runtime_error;
  int *				data;
};

extern my_descriptor_error_2_t const * const	my_descriptor_error_2_ptr;

extern void my_condition_init_error_2 (cce_destination_t L, my_condition_error_2_t * C, int the_data)
  __attribute__((__nonnull__(1)));

extern cce_condition_t const * my_condition_new_error_2 (cce_destination_t L, int the_data)
  __attribute__((__nonnull__(1)));

__attribute__((__pure__,__nonnull__(1),__always_inline__))
static inline bool
my_condition_is_error_2 (cce_condition_t const * C)
{
  return cce_condition_is(C, &(my_descriptor_error_2_ptr->descriptor));
}

extern void inline_init_module (void);


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#endif /* INLINE_HEADER_H */

/* end of file */
