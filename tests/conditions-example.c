/*
  Part of: CCExceptions
  Contents: example of condition descriptors hierarchy
  Date: Dec 28, 2016

  Abstract

	This example is copied in the documentation.

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


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include <stdlib.h>
#include <assert.h>


/** --------------------------------------------------------------------
 ** Exceptional condition alpha: headers.
 ** ----------------------------------------------------------------- */

/* Exceptional condition  descriptor type.   The anonymous field  can be
   seen  as a  table of  virtual methods,  which are  overridden by  the
   subtypes. */
typedef struct alpha_D_t {
  cce_condition_D_t	condition_D[1];
} alpha_D_t;

/* Exceptional condition object type. */
typedef struct alpha_C_t {
  cce_condition_C_t	condition_C[1];
  int			alpha;
} alpha_C_t;

cce_condition_C_t *	alpha_C_init  (alpha_C_t * cnd, int alpha);
void			alpha_C_final (alpha_C_t * cnd);
cce_condition_C_t *	alpha_C_constructor (int code);
static void		alpha_C_destructor  (cce_condition_C_t * cnd);
static const char *	alpha_C_static_message (const cce_condition_C_t * cnd);
bool                    alpha_C_is_a (const cce_condition_C_t * condition);

/* ------------------------------------------------------------------ */

__attribute__((const,always_inline))
static inline alpha_D_t *
my_cast_to_alpha_D_from_alpha_D (const alpha_D_t * src)
{
  return (alpha_D_t *)src;
}

__attribute__((const,always_inline))
static inline alpha_C_t *
my_cast_to_alpha_C_from_alpha_C (const alpha_C_t * src)
{
  return (alpha_C_t *)src;
}

/* ------------------------------------------------------------------ */

__attribute__((const,always_inline))
static inline cce_condition_D_t *
my_cast_to_condition_D_from_alpha_D (const alpha_D_t * src)
{
  return (cce_condition_D_t *)(src->condition_D);
}

__attribute__((const,always_inline))
static inline alpha_D_t *
my_cast_to_alpha_D_from_condition_D (const cce_condition_D_t * src)
{
  return (alpha_D_t *)(((uint8_t *)src) - (ptrdiff_t)offsetof(alpha_D_t, condition_D));
}

/* ------------------------------------------------------------------ */

__attribute__((const,always_inline))
static inline cce_condition_C_t *
my_cast_to_condition_C_from_alpha_C (const alpha_C_t * src)
{
  return (cce_condition_C_t *)(src->condition_C);
}

__attribute__((const,always_inline))
static inline alpha_C_t *
my_cast_to_alpha_C_from_condition_C (const cce_condition_C_t * src)
{
  return (alpha_C_t *)(((uint8_t *)src) - (ptrdiff_t)offsetof(alpha_C_t, condition_C));
}


/** --------------------------------------------------------------------
 ** Exceptional condition beta: headers.
 ** ----------------------------------------------------------------- */

/* Exceptional condition  descriptor type.   The anonymous field  can be
   seen  as a  table of  virtual methods,  which are  overridden by  the
   subtypes. */
typedef struct beta_D_t {
  cce_condition_D_t	condition_D[1];
} beta_D_t;

/* Exceptional condition object type. */
typedef struct beta_C_t {
  alpha_C_t		condition_C[1];
  int			beta;
} beta_C_t;

cce_condition_C_t *	beta_C_init  (beta_C_t * cnd, int alpha, int beta);
void			beta_C_final (beta_C_t * cnd);
cce_condition_C_t *	beta_C_constructor (int alpha, int beta);
static void		beta_C_destructor  (cce_condition_C_t * cnd);
static const char *	beta_C_static_message (const cce_condition_C_t * cnd);
bool			beta_C_is_a (const cce_condition_C_t * condition);

/* ------------------------------------------------------------------ */

__attribute__((const,always_inline))
static inline beta_D_t *
my_cast_to_beta_D_from_beta_D (const beta_D_t * src)
{
  return (beta_D_t *)src;
}

__attribute__((const,always_inline))
static inline beta_C_t *
my_cast_to_beta_C_from_beta_C (const beta_C_t * src)
{
  return (beta_C_t *)src;
}

/* ------------------------------------------------------------------ */

__attribute__((const,always_inline))
static inline cce_condition_D_t *
my_cast_to_condition_D_from_beta_D (const beta_D_t * src)
{
  return (cce_condition_D_t *)(src->condition_D);
}

__attribute__((const,always_inline))
static inline beta_D_t *
my_cast_to_beta_D_from_condition_D (const cce_condition_D_t * src)
{
  return (beta_D_t *)(((uint8_t *)src) - (ptrdiff_t)offsetof(beta_D_t, condition_D));
}

/* ------------------------------------------------------------------ */

__attribute__((const,always_inline))
static inline cce_condition_C_t *
my_cast_to_condition_C_from_beta_C (const beta_C_t * src)
{
  return (cce_condition_C_t *)(src->condition_C[0].condition_C);
}

__attribute__((const,always_inline))
static inline beta_C_t *
my_cast_to_beta_C_from_condition_C (const cce_condition_C_t * src)
{
  return (beta_C_t *)(((uint8_t *)src) - (ptrdiff_t)offsetof(beta_C_t, condition_C));
}

/* ------------------------------------------------------------------ */

__attribute__((const,always_inline))
static inline alpha_C_t *
my_cast_to_alpha_C_from_beta_C (const beta_C_t * src)
{
  return (alpha_C_t *)(src->condition_C);
}

__attribute__((const,always_inline))
static inline beta_C_t *
my_cast_to_beta_C_from_alpha_C (const alpha_C_t * src)
{
  return (beta_C_t *)(((uint8_t *)src) - (ptrdiff_t)offsetof(beta_C_t, condition_C));
}


/** --------------------------------------------------------------------
 ** Exceptional condition gamma: headers.
 ** ----------------------------------------------------------------- */

/* Exceptional condition  descriptor type.   The anonymous field  can be
   seen  as a  table of  virtual methods,  which are  overridden by  the
   subtypes. */
typedef struct gamma_D_t {
  cce_condition_D_t	condition_D[1];
} gamma_D_t;

/* Exceptional condition object type. */
typedef struct gamma_C_t {
  beta_C_t		condition_C[1];
  int			gamma;
} gamma_C_t;

cce_condition_C_t *	gamma_C_init  (gamma_C_t * cnd, int alpha, int beta, int gamma);
void			gamma_C_final (gamma_C_t * cnd);
cce_condition_C_t *	gamma_C_constructor (int alpha, int beta, int gamma);
static void		gamma_C_destructor  (cce_condition_C_t * cnd);
static const char *	gamma_C_static_message (const cce_condition_C_t * cnd);
bool			gamma_C_is_a (const cce_condition_C_t * condition);

/* ------------------------------------------------------------------ */

__attribute__((const,always_inline))
static inline gamma_D_t *
my_cast_to_gamma_D_from_gamma_D (const gamma_D_t * src)
{
  return (gamma_D_t *)src;
}

__attribute__((const,always_inline))
static inline gamma_C_t *
my_cast_to_gamma_C_from_gamma_C (const gamma_C_t * src)
{
  return (gamma_C_t *)src;
}

/* ------------------------------------------------------------------ */

__attribute__((const,always_inline))
static inline cce_condition_D_t *
my_cast_to_condition_D_from_gamma_D (const gamma_D_t * src)
{
  return (cce_condition_D_t *)(src->condition_D);
}

__attribute__((const,always_inline))
static inline gamma_D_t *
my_cast_to_gamma_D_from_condition_D (const cce_condition_D_t * src)
{
  return (gamma_D_t *)(((uint8_t *)src) - (ptrdiff_t)offsetof(gamma_D_t, condition_D));
}

/* ------------------------------------------------------------------ */

__attribute__((const,always_inline))
static inline cce_condition_C_t *
my_cast_to_condition_C_from_gamma_C (const gamma_C_t * src)
{
  return (cce_condition_C_t *)(src->condition_C);
}

__attribute__((const,always_inline))
static inline gamma_C_t *
my_cast_to_gamma_C_from_condition_C (const cce_condition_C_t * src)
{
  return (gamma_C_t *)(((uint8_t *)src) - (ptrdiff_t)offsetof(gamma_C_t, condition_C));
}

/* ------------------------------------------------------------------ */

__attribute__((const,always_inline))
static inline beta_C_t *
my_cast_to_beta_C_from_gamma_C (const gamma_C_t * src)
{
  return (beta_C_t *)(src->condition_C);
}

__attribute__((const,always_inline))
static inline gamma_C_t *
my_cast_to_gamma_C_from_beta_C (const beta_C_t * src)
{
  return (gamma_C_t *)(((uint8_t *)src) - (ptrdiff_t)offsetof(gamma_C_t, condition_C));
}


/** --------------------------------------------------------------------
 ** Cast functions.
 ** ----------------------------------------------------------------- */

#define my_condition_D(STRUCT_PTR)					\
  _Generic((STRUCT_PTR),						\
	   alpha_D_t		*: (cce_condition_D_t *)(STRUCT_PTR),		\
	   beta_D_t		*: (cce_condition_D_t *)(STRUCT_PTR),		\
	   gamma_D_t		*: (cce_condition_D_t *)(STRUCT_PTR),		\
	   const alpha_D_t	*: (cce_condition_D_t *)(STRUCT_PTR),		\
	   const beta_D_t	*: (cce_condition_D_t *)(STRUCT_PTR),		\
	   const gamma_D_t	*: (cce_condition_D_t *)(STRUCT_PTR))
//	   default:		cce_condition_D(STRUCT_PTR)

#define my_condition_C(STRUCT_PTR)					\
  _Generic((STRUCT_PTR),						\
	   alpha_C_t		*: (cce_condition_C_t *)(STRUCT_PTR),		\
	   beta_C_t		*: (cce_condition_C_t *)(STRUCT_PTR),		\
	   gamma_C_t		*: (cce_condition_C_t *)(STRUCT_PTR),		\
	   const alpha_C_t	*: (cce_condition_C_t *)(STRUCT_PTR),		\
	   const beta_C_t	*: (cce_condition_C_t *)(STRUCT_PTR),		\
	   const gamma_C_t	*: (cce_condition_C_t *)(STRUCT_PTR))
//	   default:		cce_condition_C(STRUCT_PTR))(STRUCT_PTR)

/* ------------------------------------------------------------------ */

#define my_alpha_D(STRUCT_PTR)						\
  _Generic((STRUCT_PTR),						\
	   alpha_D_t		*: (alpha_D_t *)(STRUCT_PTR),			\
	   beta_D_t		*: (alpha_D_t *)(STRUCT_PTR),			\
	   gamma_D_t		*: (alpha_D_t *)(STRUCT_PTR),			\
	   const alpha_D_t	*: (alpha_D_t *)(STRUCT_PTR),			\
	   const beta_D_t	*: (alpha_D_t *)(STRUCT_PTR),			\
	   const gamma_D_t	*: (alpha_D_t *)(STRUCT_PTR))

#define my_alpha_C(STRUCT_PTR)						\
  _Generic((STRUCT_PTR),						\
	   alpha_C_t		*: (alpha_C_t *)(STRUCT_PTR),			\
	   beta_C_t		*: (alpha_C_t *)(STRUCT_PTR),			\
	   gamma_C_t		*: (alpha_C_t *)(STRUCT_PTR),			\
	   const alpha_C_t	*: (alpha_C_t *)(STRUCT_PTR),			\
	   const beta_C_t	*: (alpha_C_t *)(STRUCT_PTR),			\
	   const gamma_C_t	*: (alpha_C_t *)(STRUCT_PTR))

/* ------------------------------------------------------------------ */

#define my_beta_D(STRUCT_PTR)						\
  _Generic((STRUCT_PTR),						\
	   alpha_D_t		*: (beta_D_t *)(STRUCT_PTR),			\
	   beta_D_t		*: (beta_D_t *)(STRUCT_PTR),			\
	   gamma_D_t		*: (beta_D_t *)(STRUCT_PTR),			\
	   const alpha_D_t	*: (beta_D_t *)(STRUCT_PTR),			\
	   const beta_D_t	*: (beta_D_t *)(STRUCT_PTR),			\
	   const gamma_D_t	*: (beta_D_t *)(STRUCT_PTR))

#define my_beta_C(STRUCT_PTR)						\
  _Generic((STRUCT_PTR),						\
	   alpha_C_t		*: (beta_C_t *)(STRUCT_PTR),			\
	   beta_C_t		*: (beta_C_t *)(STRUCT_PTR),			\
	   gamma_C_t		*: (beta_C_t *)(STRUCT_PTR),			\
	   const alpha_C_t	*: (beta_C_t *)(STRUCT_PTR),			\
	   const beta_C_t	*: (beta_C_t *)(STRUCT_PTR),			\
	   const gamma_C_t	*: (beta_C_t *)(STRUCT_PTR))

/* ------------------------------------------------------------------ */

#define my_gamma_D(STRUCT_PTR)						\
  _Generic((STRUCT_PTR),						\
	   alpha_D_t		*: (gamma_D_t *)(STRUCT_PTR),			\
	   beta_D_t		*: (gamma_D_t *)(STRUCT_PTR),			\
	   gamma_D_t		*: (gamma_D_t *)(STRUCT_PTR),			\
	   const alpha_D_t	*: (gamma_D_t *)(STRUCT_PTR),			\
	   const beta_D_t	*: (gamma_D_t *)(STRUCT_PTR),			\
	   const gamma_D_t	*: (gamma_D_t *)(STRUCT_PTR))

#define my_gamma_C(STRUCT_PTR)						\
  _Generic((STRUCT_PTR),						\
	   beta_C_t		*: (gamma_C_t *)(STRUCT_PTR),			\
	   beta_C_t		*: (gamma_C_t *)(STRUCT_PTR),			\
	   gamma_C_t		*: (gamma_C_t *)(STRUCT_PTR),			\
	   const alpha_C_t	*: (gamma_C_t *)(STRUCT_PTR),			\
	   const beta_C_t	*: (gamma_C_t *)(STRUCT_PTR),			\
	   const gamma_C_t	*: (gamma_C_t *)(STRUCT_PTR))

/* ------------------------------------------------------------------ */

#if 0
#define my_condition_D(STRUCT_PTR)					\
  _Generic((STRUCT_PTR),						\
	   alpha_D_t		*: (cce_condition_t *), \
	   beta_D_t		*: my_cast_to_condition_D_from_beta_D,	\
	   gamma_D_t		*: my_cast_to_condition_D_from_gamma_D, \
	   const alpha_D_t	*: my_cast_to_condition_D_from_alpha_D, \
	   const beta_D_t	*: my_cast_to_condition_D_from_beta_D,	\
	   const gamma_D_t	*: my_cast_to_condition_D_from_gamma_D)(STRUCT_PTR)

//	   default:		cce_condition_D(STRUCT_PTR)

#define my_condition_C(STRUCT_PTR)					\
  _Generic((STRUCT_PTR),						\
	   alpha_C_t		*: my_cast_to_condition_C_from_alpha_C, \
	   beta_C_t		*: my_cast_to_condition_C_from_beta_C,	\
	   gamma_C_t		*: my_cast_to_condition_C_from_gamma_C, \
	   const alpha_C_t	*: my_cast_to_condition_C_from_alpha_C, \
	   const beta_C_t	*: my_cast_to_condition_C_from_beta_C,	\
	   const gamma_C_t	*: my_cast_to_condition_C_from_gamma_C)(STRUCT_PTR)

//	   default:		cce_condition_C(STRUCT_PTR))(STRUCT_PTR)

/* ------------------------------------------------------------------ */

#define my_alpha_D(STRUCT_PTR)						\
  _Generic((STRUCT_PTR),						\
	   alpha_D_t		*: my_cast_to_alpha_D_from_alpha_D,	\
	   beta_D_t		*: my_cast_to_alpha_D_from_beta_D,	\
	   gamma_D_t		*: my_cast_to_alpha_D_from_gamma_D,	\
	   const alpha_D_t	*: my_cast_to_alpha_D_from_alpha_D,	\
	   const beta_D_t	*: my_cast_to_alpha_D_from_beta_D,	\
	   const gamma_D_t	*: my_cast_to_alpha_D_from_gamma_D)(STRUCT_PTR)

#define my_alpha_C(STRUCT_PTR)						\
  _Generic((STRUCT_PTR),						\
	   alpha_C_t		*: my_cast_to_alpha_C_from_alpha_C,	\
	   beta_C_t		*: my_cast_to_alpha_C_from_beta_C,	\
	   gamma_C_t		*: my_cast_to_alpha_C_from_gamma_C,	\
	   const alpha_C_t	*: my_cast_to_alpha_C_from_alpha_C,	\
	   const beta_C_t	*: my_cast_to_alpha_C_from_beta_C,	\
	   const gamma_C_t	*: my_cast_to_alpha_C_from_gamma_C)(STRUCT_PTR)

/* ------------------------------------------------------------------ */

#define my_beta_D(STRUCT_PTR)						\
  _Generic((STRUCT_PTR),						\
	   alpha_D_t		*: my_cast_to_beta_D_from_alpha_D,	\
	   beta_D_t		*: my_cast_to_beta_D_from_beta_D,	\
	   gamma_D_t		*: my_cast_to_beta_D_from_gamma_D,	\
	   const alpha_D_t	*: my_cast_to_beta_D_from_alpha_D,	\
	   const beta_D_t	*: my_cast_to_beta_D_from_beta_D,	\
	   const gamma_D_t	*: my_cast_to_beta_D_from_gamma_D)(STRUCT_PTR)

#define my_beta_C(STRUCT_PTR)						\
  _Generic((STRUCT_PTR),						\
	   alpha_C_t		*: my_cast_to_beta_C_from_alpha_C,	\
	   beta_C_t		*: my_cast_to_beta_C_from_beta_C,	\
	   gamma_C_t		*: my_cast_to_beta_C_from_gamma_C,	\
	   const alpha_C_t	*: my_cast_to_beta_C_from_alpha_C,	\
	   const beta_C_t	*: my_cast_to_beta_C_from_beta_C,	\
	   const gamma_C_t	*: my_cast_to_beta_C_from_gamma_C)(STRUCT_PTR)

/* ------------------------------------------------------------------ */

#define my_gamma_D(STRUCT_PTR)						\
  _Generic((STRUCT_PTR),						\
	   alpha_D_t		*: my_cast_to_gamma_D_from_alpha_D,	\
	   beta_D_t		*: my_cast_to_gamma_D_from_beta_D,	\
	   gamma_D_t		*: my_cast_to_gamma_D_from_gamma_D,	\
	   const alpha_D_t	*: my_cast_to_gamma_D_from_alpha_D,	\
	   const beta_D_t	*: my_cast_to_gamma_D_from_beta_D,	\
	   const gamma_D_t	*: my_cast_to_gamma_D_from_gamma_D)(STRUCT_PTR)

#define my_gamma_C(STRUCT_PTR)						\
  _Generic((STRUCT_PTR),						\
	   alpha_C_t		*: my_cast_to_gamma_C_from_alpha_C,	\
	   beta_C_t		*: my_cast_to_gamma_C_from_beta_C,	\
	   gamma_C_t		*: my_cast_to_gamma_C_from_gamma_C,	\
	   const alpha_C_t	*: my_cast_to_gamma_C_from_alpha_C,	\
	   const beta_C_t	*: my_cast_to_gamma_C_from_beta_C,	\
	   const gamma_C_t	*: my_cast_to_gamma_C_from_gamma_C)(STRUCT_PTR)

#endif


/** --------------------------------------------------------------------
 ** Exceptional condition alpha: code.
 ** ----------------------------------------------------------------- */

/* Instance of condition descriptor.   The "parent" field is initialised
   to  NULL  here   and  reinitialised  to  "cce_root_D"   later  by  an
   initialisation function. */
static alpha_D_t alpha_D = {
  .condition_D[0] = {
    .parent		= NULL,
    .final		= alpha_C_destructor,
    .static_message	= alpha_C_static_message
  }
};

cce_condition_C_t *
alpha_C_init (alpha_C_t * cnd, int alpha)
/* Initialise an already allocated condition object. */
{
  cce_condition_C_init(my_condition_C(cnd), my_condition_D(&alpha_D));
  cnd->alpha = alpha;
  return my_condition_C(cnd);
}

void
alpha_C_final (alpha_C_t * cnd CCE_UNUSED)
/* Finalise a condition object; do not release memory. */
{
  return;
}

cce_condition_C_t *
alpha_C_constructor (int alpha)
/* Allocate and initialise an instance of condition object. */
{
  alpha_C_t *	cnd;
  cnd = malloc(sizeof(alpha_C_t));
  assert(cnd);
  return alpha_C_init(cnd, alpha);
}

static void
alpha_C_destructor (cce_condition_C_t * cnd)
/* Finalise and release memory of an instance of condition object. */
{
  alpha_C_final((alpha_C_t *)cnd);
  free(cnd);
}

static const char *
alpha_C_static_message (const cce_condition_C_t * cnd CCE_UNUSED)
{
  return "exceptional condition A";
}

bool
alpha_C_is_a (const cce_condition_C_t * condition)
{
  return cce_is_condition_C(condition, my_condition_D(&alpha_D));
}


/** --------------------------------------------------------------------
 ** Exceptional condition beta: code.
 ** ----------------------------------------------------------------- */

/* Instance of condition descriptor. */
static beta_D_t beta_D = {
  .condition_D[0] = {
    .parent		= alpha_D.condition_D,
    .final		= beta_C_destructor,
    .static_message	= beta_C_static_message
  }
};

cce_condition_C_t *
beta_C_init (beta_C_t * cnd, int alpha, int beta)
/* Initialise an already allocated condition object. */
{
  alpha_C_init(my_alpha_C(cnd), alpha);
  cce_condition_C_init(my_condition_C(cnd), my_condition_D(&beta_D));
  cnd->beta = beta;
  return my_condition_C(cnd);
}

void
beta_C_final (beta_C_t * cnd)
/* Finalise a condition object; do not release memory. */
{
  alpha_C_final((alpha_C_t *)cnd);
}

cce_condition_C_t *
beta_C_constructor (int alpha, int beta)
/* Allocate and initialise an instance of condition object. */
{
  beta_C_t *	cnd;

  cnd = malloc(sizeof(beta_C_t));
  assert(cnd);
  return beta_C_init(cnd, alpha, beta);
}

static void
beta_C_destructor (cce_condition_C_t * cnd)
/* Finalise and release memory of an instance of condition object. */
{
  beta_C_final((beta_C_t *)cnd);
  free(cnd);
}

static const char *
beta_C_static_message (const cce_condition_C_t * cnd CCE_UNUSED)
{
  return "exceptional condition B";
}

bool
beta_C_is_a (const cce_condition_C_t * condition)
{
  return cce_is_condition_C(condition, my_condition_D(&beta_D));
}


/** --------------------------------------------------------------------
 ** Exceptional condition gamma: code.
 ** ----------------------------------------------------------------- */

/* Instance of condition descriptor. */
static gamma_D_t gamma_D = {
  .condition_D[0] = {
    .parent		= beta_D.condition_D,
    .final		= gamma_C_destructor,
    .static_message	= gamma_C_static_message
  }
};

cce_condition_C_t *
gamma_C_init (gamma_C_t * cnd, int alpha, int beta, int gamma)
/* Initialise an already allocated condition object. */
{
  beta_C_init(my_beta_C(cnd), alpha, beta);
  cce_condition_C_init(my_condition_C(cnd), my_condition_D(&gamma_D));
  cnd->gamma = gamma;
  return my_condition_C(cnd);
}

void
gamma_C_final (gamma_C_t * cnd)
/* Finalise a condition object; do not release memory. */
{
  beta_C_final((beta_C_t *)cnd);
}

cce_condition_C_t *
gamma_C_constructor (int alpha, int beta, int gamma)
/* Allocate and initialise an instance of condition object. */
{
  gamma_C_t *	cnd;

  cnd = malloc(sizeof(gamma_C_t));
  assert(cnd);
  return gamma_C_init(cnd, alpha, beta, gamma);
}

static void
gamma_C_destructor (cce_condition_C_t * cnd)
/* Finalise and release memory of an instance of condition object. */
{
  gamma_C_final((gamma_C_t *)cnd);
  free(cnd);
}

static const char *
gamma_C_static_message (const cce_condition_C_t * cnd CCE_UNUSED)
{
  return "exceptional condition C";
}

bool
gamma_C_is_a (const cce_condition_C_t * condition)
{
  return cce_is_condition_C(condition, my_condition_D(&gamma_D));
}


int
main (int argc CCE_UNUSED, const char *const argv[] CCE_UNUSED)
{
  /* Dynamic initialisation. */
  cce_condition_D_set_root_parent(alpha_D.condition_D);

  /* Raising condition object of type C. */
  {
    cce_location_t	L[1];
    int			flag;

    if (cce_location(L)) {
      cce_condition_C_t *	C = cce_condition_C(L);

      if (gamma_C_is_a(C)) {
	gamma_C_t *	K = (gamma_C_t *)C;
	flag = K->gamma;
      } else if (beta_C_is_a(C)) {
	beta_C_t *	K = (beta_C_t *)C;
	flag = K->beta;
      } else if (alpha_C_is_a(C)) {
	alpha_C_t *	K = (alpha_C_t *)C;
	flag = K->alpha;
      } else {
	flag = 0;
      }
      cce_run_error_handlers(L);
      cce_condition_C_final(C);
    } else {
      cce_raise(L, gamma_C_constructor(1, 2, 3));
      cce_run_cleanup_handlers(L);
    }
    assert(3 == flag);
  }

  /* Raising condition object of type B. */
  {
    cce_location_t	L[1];
    int			flag;

    if (cce_location(L)) {
      cce_condition_C_t *	C = cce_condition_C(L);

      if (gamma_C_is_a(C)) {
	gamma_C_t *	K = (gamma_C_t *)C;
	flag = K->gamma;
      } else if (beta_C_is_a(C)) {
	beta_C_t *	K = (beta_C_t *)C;
	flag = K->beta;
      } else if (alpha_C_is_a(C)) {
	alpha_C_t *	K = (alpha_C_t *)C;
	flag = K->alpha;
      } else {
	flag = 0;
      }
      cce_run_error_handlers(L);
      cce_condition_C_final(C);
    } else {
      cce_raise(L, beta_C_constructor(1, 2));
      cce_run_cleanup_handlers(L);
    }
    assert(2 == flag);
  }

  /* Raising condition object of type A. */
  {
    cce_location_t	L[1];
    int			flag;

    if (cce_location(L)) {
      cce_condition_C_t *	C = cce_condition_C(L);

      if (gamma_C_is_a(C)) {
	gamma_C_t *	K = (gamma_C_t *)C;
	flag = K->gamma;
      } else if (beta_C_is_a(C)) {
	beta_C_t *	K = (beta_C_t *)C;
	flag = K->beta;
      } else if (alpha_C_is_a(C)) {
	alpha_C_t *	K = (alpha_C_t *)C;
	flag = K->alpha;
      } else {
	flag = 0;
      }
      cce_run_error_handlers(L);
      cce_condition_C_final(C);
    } else {
      cce_raise(L, alpha_C_constructor(1));
      cce_run_cleanup_handlers(L);
    }
    assert(1 == flag);
  }

  exit(EXIT_SUCCESS);
}

/* end of file */
