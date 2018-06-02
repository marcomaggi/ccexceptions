/*
  Part of: CCExceptions
  Contents: deprecated features
  Date: Sat Jun  2, 2018

  Abstract



  Copyright (C) 2018 Marco Maggi <marco.maggi-ipsu@poste.it>

  This is free software; you  can redistribute it and/or modify it under
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


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "ccexceptions-internals.h"


/** --------------------------------------------------------------------
 ** Predefined POSIX exception handler: malloc pointer.
 ** ----------------------------------------------------------------- */

__attribute__((__deprecated__))
void
cce_clean_handler_malloc_init (cce_location_t * L, cce_clean_handler_t * H, void * pointer)
{
  cce_init_clean_handler_malloc(L, H, pointer);
}

__attribute__((__deprecated__))
void
cce_error_handler_malloc_init (cce_location_t * L, cce_error_handler_t * H, void * pointer)
{
  cce_init_error_handler_malloc(L, H, pointer);
}


/** --------------------------------------------------------------------
 ** Locations API.
 ** ----------------------------------------------------------------- */

__attribute__((__deprecated__))
void
cce_run_clean_handlers (cce_location_t * L)
{
  cce_run_body_handlers(L);
}

__attribute__((__deprecated__))
void
cce_run_error_handlers (cce_location_t * L)
{
  cce_run_catch_handlers(L);
}

/* end of file */
