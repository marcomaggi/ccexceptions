/*
  Part of: CCExceptions
  Contents: example of condition descriptors hierarchy
  Date: Dec 28, 2016

  Abstract



  Copyright (C) 2016 Marco Maggi <marco.maggi-ipsu@poste.it>

  This is free software; you can  redistribute it and/or modify it under
  the terms of the GNU Lesser General Public License as published by the
  Free Software  Foundation; either version  3.0 of the License,  or (at
  your option) any later version.

  This library  is distributed in the  hope that it will  be useful, but
  WITHOUT   ANY  WARRANTY;   without  even   the  implied   warranty  of
  MERCHANTABILITY  or FITNESS  FOR A  PARTICULAR PURPOSE.   See  the GNU
  Lesser General Public License for more details.

  You  should have  received a  copy of  the GNU  Lesser  General Public
  License along  with this library; if  not, write to  the Free Software
  Foundation, Inc.,  59 Temple Place,  Suite 330, Boston,  MA 02111-1307
  USA.

*/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <ccexceptions.h>


/* Exceptional condition A. */

typedef struct A_condition_descriptor_t {
  cce_condition_descriptor_t	core;
} A_condition_descriptor_t;

typedef struct A_condition_object_t {
  cce_condition_t	core;
  int			alpha;
} A_condition_object_t;

cce_condition_t *	A_condition_init  (A_condition_object_t * cnd, int alpha);
void			A_condition_final (A_condition_object_t * cnd);
cce_condition_t *	A_condition_constructor (int code);
static void		A_condition_destructor  (void * cnd);
static const char *	A_condition_static_message (void * cnd CCE_UNUSED);

static A_condition_descriptor_t A_condition_descriptor_stru = {
  .core.parent		= NULL,
  .core.free		= A_condition_destructor,
  .core.static_message	= A_condition_static_message
};

const cce_condition_descriptor_t * A_condition_descriptor =
  (const cce_condition_descriptor_t *)&A_condition_descriptor_stru;

cce_condition_t *
A_condition_init (A_condition_object_t * cnd, int alpha)
{
  cnd->core.descriptor	= A_condition_descriptor;
  cnd->alpha		= alpha;
  return (cce_condition_t *)cnd;
}

void
A_condition_final (A_condition_object_t * cnd CCE_UNUSED)
{
  return;
}

cce_condition_t *
A_condition_constructor (int alpha)
{
  A_condition_object_t *	cnd;
  cnd = malloc(sizeof(A_condition_object_t));
  assert(cnd);
  return A_condition_init(cnd, alpha);
}

static void
A_condition_destructor (void * cnd)
{
  A_condition_final(cnd);
  free(cnd);
}

static const char *
A_condition_static_message (void * cnd CCE_UNUSED)
{
  return "exceptional condition A";
}


/* Exceptional condition B. */

typedef struct B_condition_descriptor_t {
  A_condition_descriptor_t	A_descr;
} B_condition_descriptor_t;

typedef struct B_condition_object_t {
  A_condition_object_t	A;
  int			beta;
} B_condition_object_t;

cce_condition_t *	B_condition_init  (B_condition_object_t * cnd, int alpha, int beta);
void			B_condition_final (B_condition_object_t * cnd);
cce_condition_t *	B_condition_constructor (int alpha, int beta);
static void		B_condition_destructor  (void * cnd);
static const char *	B_condition_static_message (void * cnd CCE_UNUSED);

static B_condition_descriptor_t B_condition_descriptor_stru;

const cce_condition_descriptor_t * B_condition_descriptor =
  (const cce_condition_descriptor_t *)&B_condition_descriptor_stru;


cce_condition_t *
B_condition_init (B_condition_object_t * cnd, int alpha, int beta)
{
  A_condition_init((A_condition_object_t *)cnd, alpha);
  cnd->A.core.descriptor	= B_condition_descriptor;
  cnd->beta			= beta;
  return (cce_condition_t *)cnd;
}

void
B_condition_final (B_condition_object_t * cnd)
{
  A_condition_final((A_condition_object_t *)cnd);
}

cce_condition_t *
B_condition_constructor (int alpha, int beta)
{
  B_condition_object_t *	cnd;

  cnd = malloc(sizeof(B_condition_object_t));
  assert(cnd);
  return B_condition_init(cnd, alpha, beta);
}

static void
B_condition_destructor (void * cnd)
{
  B_condition_final(cnd);
  free(cnd);
}

static const char *
B_condition_static_message (void * cnd CCE_UNUSED)
{
  return "exceptional condition B";
}


/* Exceptional condition C. */
#if 0
typedef struct C_condition_descriptor_t {
  cce_condition_descriptor_t	core;
} C_condition_descriptor_t;

typedef struct C_condition_object_t {
  B_condition_object_t  B;
  int			code;
} C_condition_object_t;

static const char *
C_condition_static_message (void * cnd CCE_UNUSED)
{
  return "exceptional condition C";
}

static void
C_condition_destructor (void * cnd)
{
  free(cnd);
}

static C_condition_descriptor_t C_condition_descriptor_stru = {
  .core.parent		= (const cce_condition_descriptor_t *)&B_condition_descriptor,
  .core.free		= C_condition_destructor,
  .core.static_message	= C_condition_static_message
};

const cce_condition_descriptor_t * C_condition_descriptor =
  (const cce_condition_descriptor_t *)&C_condition_descriptor_stru;

cce_condition_t *
C_condition_constructor (int code)
{
  C_condition_object_t *	cnd;

  cnd = malloc(sizeof(C_condition_object_t));
  assert(cnd);
  cnd->B.A.core.descriptor	= C_condition_descriptor;
  cnd->B.A.alpha		= code;
  cnd->B.code			= code;
  cnd->code			= code;
  return (cce_condition_t *)cnd;
}
#endif


int
main (int argc CCE_UNUSED, const char *const argv[])
{
  /* Dynamic initialisation. */
  A_condition_descriptor_stru.core.parent	= cce_root_condition_descriptor;
  B_condition_descriptor_stru.A_descr		= A_condition_descriptor_stru;
  B_condition_descriptor_stru.A_descr.core.parent= A_condition_descriptor;

  /* Branching upon condition types with "cce_condition_is_a()". */
  {
    cce_location_t	L;
    int			flag;

    if (cce_location(L)) {
      void *	cnd = cce_location_condition(L);

      if (cce_condition_is_a(cnd, B_condition_descriptor)) {
	B_condition_object_t *	B = cnd;
	flag = B->beta;
      } else if (cce_condition_is_a(cnd, A_condition_descriptor)) {
	A_condition_object_t *	A = cnd;
	flag = A->alpha;
      } else {
	flag = 0;
      }
      cce_condition_free(cnd);
      cce_run_error_handlers(L);
    } else {
      cce_raise(L, B_condition_constructor(1, 2));
      cce_run_cleanup_handlers(L);
    }
    assert(2 == flag);
  }

  exit(EXIT_SUCCESS);
}

/* end of file */
