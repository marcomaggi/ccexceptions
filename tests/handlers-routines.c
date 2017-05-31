/*
  Part of: CCExceptions
  Contents: tests with error and cleanup handlers
  Date: Dec 26, 2016

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

  You  should have  received a  copy of  the GNU  Lesser  General Public
  License along  with this library; if  not, write to  the Free Software
  Foundation, Inc.,  59 Temple Place,  Suite 330, Boston,  MA 02111-1307
  USA.

*/


#include <ccexceptions.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int
main (int argc CCE_UNUSED, const char *const argv[] CCE_UNUSED)
{
  /* Just run cleanup handlers. */
  {
    bool	flag1 = false;
    bool	flag2 = false;
    bool	flag3 = false;

    void handler1 (const cce_condition_t * C CCE_UNUSED, cce_handler_t * H CCE_UNUSED) {
      flag1 = true;
    }
    void handler2 (const cce_condition_t * C CCE_UNUSED, cce_handler_t * H CCE_UNUSED) {
      flag2 = true;
    }
    void handler3 (const cce_condition_t * C CCE_UNUSED, cce_handler_t * H CCE_UNUSED) {
      flag3 = true;
    }

    cce_location_t	L[1];
    cce_handler_t	H1 = { .function = handler1 };
    cce_handler_t	H2 = { .function = handler2 };
    cce_handler_t	H3 = { .function = handler3 };

    cce_location_init(L);
    cce_register_cleanup_handler(L, &H1);
    cce_register_cleanup_handler(L, &H2);
    cce_register_cleanup_handler(L, &H3);
    cce_run_cleanup_handlers(L);

    assert(true == flag1);
    assert(true == flag2);
    assert(true == flag3);
  }

    /* Just run cleanup handlers. */
  {
    bool	flag1 = false;
    bool	flag2 = false;
    bool	flag3 = false;

    void handler1 (const cce_condition_t * C CCE_UNUSED, cce_handler_t * H CCE_UNUSED) {
      flag1 = true;
    }
    void handler2 (const cce_condition_t * C CCE_UNUSED, cce_handler_t * H CCE_UNUSED) {
      flag2 = true;
    }
    void handler3 (const cce_condition_t * C CCE_UNUSED, cce_handler_t * H CCE_UNUSED) {
      flag3 = true;
    }

    cce_location_t	L[1];
    cce_handler_t	H1 = { .function = handler1 };
    cce_handler_t	H2 = { .function = handler2 };
    cce_handler_t	H3 = { .function = handler3 };

    cce_location_init(L);
    cce_register_error_handler(L, &H1);
    cce_register_error_handler(L, &H2);
    cce_register_error_handler(L, &H3);
    cce_run_error_handlers(L);

    assert(true == flag1);
    assert(true == flag2);
    assert(true == flag3);
  }

  /* Allocating memory: success execution path. */
  {
    cce_location_t	L[1];
    cce_handler_t	H[1];
    void *		P;
    bool		flag = false;

    void P_handler (const cce_condition_t * C CCE_UNUSED, cce_handler_t * H CCE_UNUSED) {
      free(P);
      flag = true;
    }
    H->function = P_handler;

    switch (cce_location(L)) {
    case CCE_ERROR:
      cce_run_error_handlers(L);
      break;

    default:
      P = malloc(4096);
      if (P) {
	cce_register_cleanup_handler(L, H);
      } else {
	cce_raise(L, NULL);
      }
      // do something here
      cce_run_cleanup_handlers(L);
    }
    assert(true == flag);
  }

  /* Allocating memory: exceptional execution path. */
  {
    cce_location_t	L[1];
    cce_handler_t	H;
    void *		P;
    bool		flag = false;

    void P_handler (const cce_condition_t * C CCE_UNUSED, cce_handler_t * H CCE_UNUSED) {
      free(P);
      flag = true;
    }
    H.function = P_handler;

    switch (cce_location(L)) {
    case CCE_ERROR:
      cce_run_error_handlers(L);
      break;

    default:
      P = malloc(4096);
      if (P) {
	cce_register_cleanup_handler(L, &H);
      } else {
	cce_raise(L, NULL);
      }
      // do something here
      if (1) {
	cce_raise(L, NULL);
      }
      cce_run_cleanup_handlers(L);
    }
    assert(true == flag);
  }

  /* Constructor scheme: success path. */
  {
    void * constructor (cce_location_t * upper_L)
    {
      cce_location_t	L[1];
      cce_handler_t	H[1];
      void *		P;

      void P_handler (const cce_condition_t * C CCE_UNUSED, cce_handler_t * H CCE_UNUSED) {
	free(P);
      }
      H->function = P_handler;

      switch (cce_location(L)) {
      case CCE_ERROR:
	cce_run_error_handlers(L);
	cce_raise(upper_L, NULL);
	break;

      default:
	P = malloc(4096);
	if (P) {
	  cce_register_error_handler(L, H);
	} else {
	  cce_raise(L, NULL);
	}
	// do something here
	if (0) {
	  cce_raise(L, NULL);
	}
	cce_run_cleanup_handlers(L);
      }
      return P;
    }

    void caller (void)
    {
      cce_location_t	L[1];
      cce_handler_t	H[1];
      void *		P;
      bool		flag = false;

      void P_handler (const cce_condition_t * C CCE_UNUSED, cce_handler_t * H CCE_UNUSED) {
	free(P);
	flag = true;
      }
      H->function = P_handler;

      switch (cce_location(L)) {
      case CCE_ERROR:
	cce_run_error_handlers(L);
	break;

      default:
	P = constructor(L);
	assert(NULL != P);
	cce_register_cleanup_handler(L, H);
	// do_something_with(P);
	cce_run_cleanup_handlers(L);
      }
      assert(true == flag);
    }

    caller();
  }

  /* Constructor scheme: exceptional path. */
  {
    void * constructor (cce_location_t * upper_L)
    {
      cce_location_t	L[1];
      cce_handler_t	H[1];
      void *		P;

      void P_handler (const cce_condition_t * C CCE_UNUSED, cce_handler_t * H CCE_UNUSED) {
	free(P);
      }
      H->function = P_handler;

      switch (cce_location(L)) {
      case CCE_ERROR:
	cce_run_error_handlers(L);
	cce_raise(upper_L, NULL);
	break;

      default:
	P = malloc(4096);
	if (P) {
	  cce_register_error_handler(L, H);
	} else {
	  cce_raise(L, NULL);
	}
	// do something here
	if (1) {
	  cce_raise(L, NULL);
	}
	cce_run_cleanup_handlers(L);
      }
      return P;
    }

    void caller (void)
    {
      cce_location_t	L[1];
      cce_handler_t	H[1];
      void *		P;
      bool		flag = false;

      void P_handler (const cce_condition_t * C CCE_UNUSED, cce_handler_t * H CCE_UNUSED) {
	free(P);
      }
      H->function = P_handler;

      switch (cce_location(L)) {
      case CCE_ERROR:
	cce_run_error_handlers(L);
	flag = true;
	break;

      default:
	P = constructor(L);
	assert(NULL != P);
	cce_register_cleanup_handler(L, H);
	// do_something_with(P);
	cce_run_cleanup_handlers(L);
      }
      assert(true == flag);
    }

    caller();
  }

  exit(EXIT_SUCCESS);
}

/* end of file */
