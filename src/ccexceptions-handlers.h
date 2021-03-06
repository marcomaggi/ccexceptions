/*
  Part of: CCExceptions
  Contents: public header file, exceptional-condition objects
  Date: Apr 19, 2019

  Abstract

	This is a  subordinate header file: it is sourced  by "ccexceptions.h" and it
	must not be included by itself.

  Copyright (C) 2016-2020 Marco Maggi <mrc.mgg@gmail.com>

  This program is free  software: you can redistribute it and/or  modify it under the
  terms of the  GNU Lesser General Public  License as published by  the Free Software
  Foundation, either version 3 of the License, or (at your option) any later version.

  This program  is distributed in the  hope that it  will be useful, but  WITHOUT ANY
  WARRANTY; without  even the implied  warranty of  MERCHANTABILITY or FITNESS  FOR A
  PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License along with
  this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CCEXCEPTIONS_HANDLERS_H
#define CCEXCEPTIONS_HANDLERS_H		1


/** --------------------------------------------------------------------
 ** Exception handlers: type definitions.
 ** ----------------------------------------------------------------- */

typedef void cce_handler_fun_t       (cce_condition_t const * C, cce_handler_t       const * H);
typedef void cce_clean_handler_fun_t (cce_condition_t const * C, cce_clean_handler_t const * H);
typedef void cce_error_handler_fun_t (cce_condition_t const * C, cce_error_handler_t const * H);
typedef cclib_resource_data_t	cce_resource_data_t;
typedef void cce_resource_destructor_fun_t (cce_resource_data_t * pointer);

#define cce_resource_pointer(EXPR)	cclib_resource_pointer(EXPR)
#define cce_resource_destructor(FUN)	((cce_resource_destructor_fun_t *)(FUN))

struct cce_handler_t {
  cce_handler_t			*next_handler;
  cce_handler_fun_t		*handler_function;
  cce_resource_data_t		*resource_pointer;
  cce_resource_destructor_fun_t	*resource_destructor;
};

struct cce_clean_handler_t {
  cce_handler_t		handler;
};

struct cce_error_handler_t {
  cce_handler_t		handler;
};


/** --------------------------------------------------------------------
 ** Exception handlers: core handler accessors.
 ** ----------------------------------------------------------------- */

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_PURE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL
static inline cce_handler_t *
cce_clean_handler_handler (cce_clean_handler_t * const H)
{
  return &(H->handler);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_PURE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL
static inline cce_handler_t *
cce_error_handler_handler (cce_error_handler_t * const H)
{
  return &(H->handler);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_PURE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL
static inline cce_handler_t const *
cce_clean_handler_const_handler (cce_clean_handler_t const * const H)
{
  return &(H->handler);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_PURE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL
static inline cce_handler_t const *
cce_error_handler_const_handler (cce_error_handler_t const * const H)
{
  return &(H->handler);
}

#define cce_handler_handler(H)						\
  _Generic((H),								\
	   cce_clean_handler_t *: cce_clean_handler_handler,		\
	   cce_error_handler_t *: cce_error_handler_handler,		\
	   cce_clean_handler_t const *: cce_clean_handler_const_handler, \
	   cce_error_handler_t const *: cce_error_handler_const_handler)(H)


/** --------------------------------------------------------------------
 ** Exception handlers: resource pointer accessors.
 ** ----------------------------------------------------------------- */

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_PURE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL
static inline void *
cce_clean_handler_resource_pointer (cce_clean_handler_t const * const H)
{
  return H->handler.resource_pointer;
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_PURE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL
static inline void *
cce_error_handler_resource_pointer (cce_error_handler_t const * const H)
{
  return H->handler.resource_pointer;
}

#define cce_handler_resource_pointer(H)					\
  _Generic((H),								\
	   cce_clean_handler_t       *: cce_clean_handler_resource_pointer, \
	   cce_error_handler_t       *: cce_error_handler_resource_pointer, \
	   cce_clean_handler_t const *: cce_clean_handler_resource_pointer, \
	   cce_error_handler_t const *: cce_error_handler_resource_pointer)(H)


/** --------------------------------------------------------------------
 ** Exception handlers: resource destructor accessors.
 ** ----------------------------------------------------------------- */

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_PURE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline cce_resource_destructor_fun_t *
cce_clean_handler_resource_destructor (cce_clean_handler_t const * const H)
{
  return H->handler.resource_destructor;
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_PURE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline cce_resource_destructor_fun_t *
cce_error_handler_resource_destructor (cce_error_handler_t const * const H)
{
  return H->handler.resource_destructor;
}

#define cce_handler_resource_destructor(H)				\
  _Generic((H),								\
	   cce_clean_handler_t       *: cce_clean_handler_resource_destructor, \
	   cce_error_handler_t       *: cce_error_handler_resource_destructor, \
	   cce_clean_handler_t const *: cce_clean_handler_resource_destructor, \
	   cce_error_handler_t const *: cce_error_handler_resource_destructor)(H)


/** --------------------------------------------------------------------
 ** Exception handlers: default handler functions.
 ** ----------------------------------------------------------------- */

cclib_decl void cce_default_clean_handler_function (cce_condition_t const * C, cce_clean_handler_t const * H)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2);

cclib_decl void cce_default_error_handler_function (cce_condition_t const * C, cce_error_handler_t const * H)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2);


/** --------------------------------------------------------------------
 ** Exception handlers: initialisation only.
 ** ----------------------------------------------------------------- */

cclib_decl void cce_init_clean_handler_3 (cce_clean_handler_t * H, cce_clean_handler_fun_t * handler_function,
					  cce_resource_data_t * resource_pointer)
  CCLIB_FUNC_ATTRIBUTE_LEAF
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2);

cclib_decl void cce_init_clean_handler_4 (cce_clean_handler_t * H, cce_clean_handler_fun_t * handler_function,
					  cce_resource_data_t * resource_pointer, cce_resource_destructor_fun_t * resource_destructor)
  CCLIB_FUNC_ATTRIBUTE_LEAF
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2);

/* ------------------------------------------------------------------ */

cclib_decl void cce_init_error_handler_3 (cce_error_handler_t * H, cce_error_handler_fun_t * handler_function,
					  cce_resource_data_t * resource_pointer)
  CCLIB_FUNC_ATTRIBUTE_LEAF
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2);

cclib_decl void cce_init_error_handler_4 (cce_error_handler_t * H, cce_error_handler_fun_t * handler_function,
					  cce_resource_data_t * resource_pointer, cce_resource_destructor_fun_t * resource_destructor)
  CCLIB_FUNC_ATTRIBUTE_LEAF
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2);

/* ------------------------------------------------------------------ */

#define cce_init_handler_3(HANDLER_STRUCT,HANDLER_FUNCTION,RESOURCE_POINTER) \
  _Generic((HANDLER_STRUCT),						\
	   cce_clean_handler_t	*:	cce_init_clean_handler_3,	\
	   cce_error_handler_t	*:	cce_init_error_handler_3)	\
  (HANDLER_STRUCT,HANDLER_FUNCTION,RESOURCE_POINTER)

#define cce_init_handler_4(HANDLER_STRUCT,HANDLER_FUNCTION,RESOURCE_POINTER,RESOURCE_DESTRUCTOR) \
  _Generic((HANDLER_STRUCT),						\
	   cce_clean_handler_t	*:	cce_init_clean_handler_4,	\
	   cce_error_handler_t	*:	cce_init_error_handler_4)	\
  (HANDLER_STRUCT,HANDLER_FUNCTION,RESOURCE_POINTER,RESOURCE_DESTRUCTOR)

#define cce_init_handler(...)	CCLIB_VNAME(cce_init_handler,__VA_ARGS__)


/** --------------------------------------------------------------------
 ** Exception handlers: registration.
 ** ----------------------------------------------------------------- */

cclib_decl void cce_register_clean_handler (cce_destination_t L, cce_clean_handler_t * H)
  CCLIB_FUNC_ATTRIBUTE_LEAF
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2);

cclib_decl void cce_register_error_handler (cce_destination_t L, cce_error_handler_t * H)
  CCLIB_FUNC_ATTRIBUTE_LEAF
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2);

#define cce_register_handler(L,H)					\
  _Generic((H),								\
	   cce_clean_handler_t *: cce_register_clean_handler,		\
	   cce_error_handler_t *: cce_register_error_handler)(L,H)

/* ------------------------------------------------------------------ */

cclib_decl void cce_forget_clean_handler (cce_destination_t L, cce_clean_handler_t * H)
  CCLIB_FUNC_ATTRIBUTE_LEAF
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2);

cclib_decl void cce_forget_error_handler (cce_destination_t L, cce_error_handler_t * H)
  CCLIB_FUNC_ATTRIBUTE_LEAF
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2);

#define cce_forget_handler(L,H)						\
  _Generic((H),								\
	   cce_clean_handler_t *: cce_forget_clean_handler,		\
	   cce_error_handler_t *: cce_forget_error_handler)(L,H)


/** --------------------------------------------------------------------
 ** Exception handlers: initialisation and registration.
 ** ----------------------------------------------------------------- */

cclib_decl void cce_init_and_register_clean_handler_4 (cce_destination_t L,
						     cce_clean_handler_t * H, cce_clean_handler_fun_t * handler_function,
						     cce_resource_data_t * resource_pointer)
  CCLIB_FUNC_ATTRIBUTE_LEAF
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3);

cclib_decl void cce_init_and_register_clean_handler_5 (cce_destination_t L,
						     cce_clean_handler_t * H, cce_clean_handler_fun_t * handler_function,
						     cce_resource_data_t * resource_pointer, cce_resource_destructor_fun_t * resource_destructor)
  CCLIB_FUNC_ATTRIBUTE_LEAF
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3);

/* ------------------------------------------------------------------ */

cclib_decl void cce_init_and_register_error_handler_4 (cce_destination_t L,
						     cce_error_handler_t * H, cce_error_handler_fun_t * handler_function,
						     cce_resource_data_t * resource_pointer)
  CCLIB_FUNC_ATTRIBUTE_LEAF
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3);

cclib_decl void cce_init_and_register_error_handler_5 (cce_destination_t L,
						     cce_error_handler_t * H, cce_error_handler_fun_t * handler_function,
						     cce_resource_data_t * resource_pointer, cce_resource_destructor_fun_t * resource_destructor)
  CCLIB_FUNC_ATTRIBUTE_LEAF
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3);

/* ------------------------------------------------------------------ */

#define cce_init_and_register_handler_4(LOCATION,HANDLER_STRUCT,HANDLER_FUNCTION,RESOURCE_POINTER) \
  _Generic((HANDLER_STRUCT),						\
	   cce_clean_handler_t	*:	cce_init_and_register_clean_handler_4, \
	   cce_error_handler_t	*:	cce_init_and_register_error_handler_4) \
  (LOCATION, HANDLER_STRUCT,HANDLER_FUNCTION,RESOURCE_POINTER)

#define cce_init_and_register_handler_5(LOCATION,HANDLER_STRUCT,HANDLER_FUNCTION,RESOURCE_POINTER,RESOURCE_DESTRUCTOR) \
  _Generic((HANDLER_STRUCT),						\
	   cce_clean_handler_t *: cce_init_and_register_clean_handler_5, \
	   cce_error_handler_t *: cce_init_and_register_error_handler_5) \
  (LOCATION, HANDLER_STRUCT,HANDLER_FUNCTION,RESOURCE_POINTER,RESOURCE_DESTRUCTOR)

#define cce_init_and_register_handler(...)	CCLIB_VNAME(cce_init_and_register_handler,__VA_ARGS__)


/** --------------------------------------------------------------------
 ** Exception handlers: execution.
 ** ----------------------------------------------------------------- */

/* We do *not* set the "leaf" attribute for this function, because the clean handlers
   might modify data in the current compilation unit. */
cclib_decl void cce_run_body_handlers (cce_destination_t L)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1);

/* We do *not* set the "leaf" attribute for this function, because the error handlers
   might modify data in the current compilation unit. */
cclib_decl void cce_run_catch_handlers (cce_destination_t L)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1);


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#endif /* CCEXCEPTIONS_HANDLERS_H */

/* end of file */
