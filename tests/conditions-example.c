/*
  Part of: CCExceptions
  Contents: example of condition descriptors hierarchy
  Date: Dec 28, 2016

  Abstract



  Copyright (C) 2016, 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

  This is free software; you can  redistribute it and/or modify it under
  the terms of the GNU Lesser General Public License as published by the
  Free Software  Foundation; either version  3.0 of the License,  or (at
  your option) any later version.

  This library  is distributed in the  hope that it will  be useful, but
  WITHOUT   ANY  WARRANTY;   without  even   the  implied   warranty  of
  MERCHANTABILITY  or FITNESS  FOR A  PARTICULAR PURPOSE.   See  the GNU
  Lesser General Public License for more details.

  You  should have  received a  copy of  the GNU  Lesser General  Public
  License along  with this library; if  not, write to the  Free Software
  Foundation, Inc.,  59 Temple Place,  Suite 330, Boston,  MA 02111-1307
  USA.
*/


#include <stdlib.h>
#include <assert.h>
#include <ccexceptions.h>


/*** Exceptional condition A. ***/

/* Exceptional condition descriptor type.  The  field "core" can be seen
   as  a  table  of  virtual   methods,  which  are  overridden  by  the
   subtypes. */
typedef struct A_condition_descriptor_t {
  cce_condition_descriptor_t;
} A_condition_descriptor_t;

/* Exceptional condition object type. */
typedef struct A_condition_object_t {
  cce_condition_t;
  int			alpha;
} A_condition_object_t;

cce_condition_t *	A_condition_init  (A_condition_object_t * cnd, int alpha);
void			A_condition_final (A_condition_object_t * cnd);
cce_condition_t *	A_condition_constructor (int code);
static void		A_condition_destructor  (cce_condition_t * cnd);
static const char *	A_condition_static_message (const cce_condition_t * cnd);

/* Instance of condition descriptor.   The "parent" field is initialised
   to  NULL here  and  reinitialised to  "cce_root_condition_descriptor"
   later by an initialisation function. */
static A_condition_descriptor_t A_condition_descriptor = {
  .parent		= NULL,
  .free			= A_condition_destructor,
  .static_message	= A_condition_static_message
};

cce_condition_t *
A_condition_init (A_condition_object_t * cnd, int alpha)
/* Initialise an already allocated condition object. */
{
  cce_condition_init(cnd, &A_condition_descriptor);
  cnd->alpha = alpha;
  return cnd;
}

void
A_condition_final (A_condition_object_t * cnd CCE_UNUSED)
/* Finalise a condition object; do not release memory. */
{
  return;
}

cce_condition_t *
A_condition_constructor (int alpha)
/* Allocate and initialise an instance of condition object. */
{
  A_condition_object_t *	cnd;
  cnd = malloc(sizeof(A_condition_object_t));
  assert(cnd);
  return A_condition_init(cnd, alpha);
}

static void
A_condition_destructor (cce_condition_t * cnd)
/* Finalise and release memory of an instance of condition object. */
{
  A_condition_final((A_condition_object_t *)cnd);
  free(cnd);
}

static const char *
A_condition_static_message (const cce_condition_t * cnd CCE_UNUSED)
{
  return "exceptional condition A";
}

bool
A_condition_is (void * condition)
{
  return cce_condition_is_a(condition, (const cce_condition_descriptor_t *)&A_condition_descriptor);
}


/*** Exceptional condition B. ***/

/* Exceptional condition descriptor type.  The  field "core" can be seen
   as  a  table  of  virtual   methods,  which  are  overridden  by  the
   subtypes. */
typedef struct B_condition_descriptor_t {
  cce_condition_descriptor_t;
} B_condition_descriptor_t;

/* Exceptional condition object type. */
typedef struct B_condition_object_t {
  A_condition_object_t;
  int			beta;
} B_condition_object_t;

cce_condition_t *	B_condition_init  (B_condition_object_t * cnd, int alpha, int beta);
void			B_condition_final (B_condition_object_t * cnd);
cce_condition_t *	B_condition_constructor (int alpha, int beta);
static void		B_condition_destructor  (cce_condition_t * cnd);
static const char *	B_condition_static_message (const cce_condition_t * cnd);

/* Instance of condition descriptor. */
static B_condition_descriptor_t B_condition_descriptor = {
  .parent		= (const cce_condition_descriptor_t *)&A_condition_descriptor,
  .free			= B_condition_destructor,
  .static_message	= B_condition_static_message
};

cce_condition_t *
B_condition_init (B_condition_object_t * cnd, int alpha, int beta)
/* Initialise an already allocated condition object. */
{
  A_condition_init(cnd, alpha);
  cce_condition_init(cnd, &B_condition_descriptor);
  cnd->beta = beta;
  return cnd;
}

void
B_condition_final (B_condition_object_t * cnd)
/* Finalise a condition object; do not release memory. */
{
  A_condition_final((A_condition_object_t *)cnd);
}

cce_condition_t *
B_condition_constructor (int alpha, int beta)
/* Allocate and initialise an instance of condition object. */
{
  B_condition_object_t *	cnd;

  cnd = malloc(sizeof(B_condition_object_t));
  assert(cnd);
  return B_condition_init(cnd, alpha, beta);
}

static void
B_condition_destructor (cce_condition_t * cnd)
/* Finalise and release memory of an instance of condition object. */
{
  B_condition_final((B_condition_object_t *)cnd);
  free(cnd);
}

static const char *
B_condition_static_message (const cce_condition_t * cnd CCE_UNUSED)
{
  return "exceptional condition B";
}

bool
B_condition_is (void * condition)
{
  return cce_condition_is_a(condition, (const cce_condition_descriptor_t *)&B_condition_descriptor);
}


/*** Exceptional condition C. ***/

/* Exceptional condition descriptor type.  The  field "core" can be seen
   as  a  table  of  virtual   methods,  which  are  overridden  by  the
   subtypes. */
typedef struct C_condition_descriptor_t {
  cce_condition_descriptor_t;
} C_condition_descriptor_t;

/* Exceptional condition object type. */
typedef struct C_condition_object_t {
  B_condition_object_t;
  int			gamma;
} C_condition_object_t;

cce_condition_t *	C_condition_init  (C_condition_object_t * cnd, int alpha, int beta, int gamma);
void			C_condition_final (C_condition_object_t * cnd);
cce_condition_t *	C_condition_constructor (int alpha, int beta, int gamma);
static void		C_condition_destructor  (cce_condition_t * cnd);
static const char *	C_condition_static_message (const cce_condition_t * cnd);

/* Instance of condition descriptor. */
static C_condition_descriptor_t C_condition_descriptor = {
  .parent		= (cce_condition_descriptor_t *)&B_condition_descriptor,
  .free			= C_condition_destructor,
  .static_message	= C_condition_static_message
};

cce_condition_t *
C_condition_init (C_condition_object_t * cnd, int alpha, int beta, int gamma)
/* Initialise an already allocated condition object. */
{
  B_condition_init(cnd, alpha, beta);
  cce_condition_init(cnd, &C_condition_descriptor);
  cnd->gamma = gamma;
  return cnd;
}

void
C_condition_final (C_condition_object_t * cnd)
/* Finalise a condition object; do not release memory. */
{
  B_condition_final((B_condition_object_t *)cnd);
}

cce_condition_t *
C_condition_constructor (int alpha, int beta, int gamma)
/* Allocate and initialise an instance of condition object. */
{
  C_condition_object_t *	cnd;

  cnd = malloc(sizeof(C_condition_object_t));
  assert(cnd);
  return C_condition_init(cnd, alpha, beta, gamma);
}

static void
C_condition_destructor (cce_condition_t * cnd)
/* Finalise and release memory of an instance of condition object. */
{
  C_condition_final((C_condition_object_t *)cnd);
  free(cnd);
}

static const char *
C_condition_static_message (const cce_condition_t * cnd CCE_UNUSED)
{
  return "exceptional condition C";
}

bool
C_condition_is (void * condition)
{
  return cce_condition_is_a(condition, (const cce_condition_descriptor_t *)&C_condition_descriptor);
}


int
main (int argc CCE_UNUSED, const char *const argv[] CCE_UNUSED)
{
  /* Dynamic initialisation. */
  A_condition_descriptor.parent	= cce_root_condition_descriptor;

  /* Raising condition object of type C. */
  {
    cce_location_t	L[1];
    int			flag;

    if (cce_location(L)) {
      void *	cnd = cce_location_condition(L);

      if        (C_condition_is(cnd)) {
	C_condition_object_t *	C = cnd;
	flag = C->gamma;
      } else if (B_condition_is(cnd)) {
	B_condition_object_t *	B = cnd;
	flag = B->beta;
      } else if (A_condition_is(cnd)) {
	A_condition_object_t *	A = cnd;
	flag = A->alpha;
      } else {
	flag = 0;
      }
      cce_run_error_handlers(L);
      cce_condition_free(cnd);
    } else {
      cce_raise(L, C_condition_constructor(1, 2, 3));
      cce_run_cleanup_handlers(L);
    }
    assert(3 == flag);
  }

  /* Raising condition object of type B. */
  {
    cce_location_t	L[1];
    int			flag;

    if (cce_location(L)) {
      void *	cnd = cce_location_condition(L);

      if        (C_condition_is(cnd)) {
	C_condition_object_t *	C = cnd;
	flag = C->gamma;
      } else if (B_condition_is(cnd)) {
	B_condition_object_t *	B = cnd;
	flag = B->beta;
      } else if (A_condition_is(cnd)) {
	A_condition_object_t *	A = cnd;
	flag = A->alpha;
      } else {
	flag = 0;
      }
      cce_run_error_handlers(L);
      cce_condition_free(cnd);
    } else {
      cce_raise(L, B_condition_constructor(1, 2));
      cce_run_cleanup_handlers(L);
    }
    assert(2 == flag);
  }

  /* Raising condition object of type A. */
  {
    cce_location_t	L[1];
    int			flag;

    if (cce_location(L)) {
      void *	cnd = cce_location_condition(L);

      if        (B_condition_is(cnd)) {
	C_condition_object_t *	C = cnd;
	flag = C->gamma;
      } else if (B_condition_is(cnd)) {
	B_condition_object_t *	B = cnd;
	flag = B->beta;
      } else if (A_condition_is(cnd)) {
	A_condition_object_t *	A = cnd;
	flag = A->alpha;
      } else {
	flag = 0;
      }
      cce_run_error_handlers(L);
      cce_condition_free(cnd);
    } else {
      cce_raise(L, A_condition_constructor(1));
      cce_run_cleanup_handlers(L);
    }
    assert(1 == flag);
  }

  exit(EXIT_SUCCESS);
}

/* end of file */
