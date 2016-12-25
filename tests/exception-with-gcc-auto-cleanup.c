/*
  Part of: CCExceptions
  Contents: test for GCC automatic variable cleanup
  Date: Dec 24, 2016

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
#include <ccexceptions.h>

int
main (int argc CCE_UNUSED, const char *const CCE_UNUSED argv[])
{
  /* no exception */
  {
    bool	out_flag1 = false;
    bool	out_flag2 = false;
    {
      void handler1 (bool * flagp)
      {
	out_flag1 = *flagp;
      }
      void handler2 (bool * flagp)
      {
	out_flag2 = *flagp;
      }

      cce_location_t	L;
      bool		flag1 __attribute__((cleanup(handler1))) = false;
      bool		flag2 __attribute__((cleanup(handler2))) = false;

      switch (cce_location(L)) {
      case CCE_ERROR:
	flag1 = false;
	flag2 = false;
	cce_run_error_handlers(L);
	break;

      default:
	flag1 = true;
	flag2 = true;
	cce_run_cleanup_handlers(L);
      }
      assert(NULL == L->condition);
      assert(true == flag1);
      assert(true == flag2);
    }
    assert(true == out_flag1);
    assert(true == out_flag2);
  }

  /* with error */
  {
    bool	out_flag1 = false;
    bool	out_flag2 = false;
    {
      void handler1 (bool * flagp)
      {
	out_flag1 = *flagp;
      }
      void handler2 (bool * flagp)
      {
	out_flag2 = *flagp;
      }

      cce_location_t	L;
      bool		flag1 __attribute__((cleanup(handler1))) = false;
      bool		flag2 __attribute__((cleanup(handler2))) = false;

      switch (cce_location(L)) {
      case CCE_ERROR:
	flag1 = false;
	flag2 = false;
	cce_run_error_handlers(L);
	break;

      default:
	flag1 = true;
	flag2 = true;
	cce_raise(L, NULL);
	cce_run_cleanup_handlers(L);
      }
      assert(NULL == L->condition);
      assert(false == flag1);
      assert(false == flag2);
    }
    assert(false == out_flag1);
    assert(false == out_flag2);
  }

  /* with retry */
  {
    bool	out_flag1 = false;
    bool	out_flag2 = false;
    {
      void handler1 (bool * flagp)
      {
	out_flag1 = *flagp;
      }
      void handler2 (bool * flagp)
      {
	out_flag2 = *flagp;
      }

      cce_location_t	L;
      bool		flag1 __attribute__((cleanup(handler1))) = false;
      bool		flag2 __attribute__((cleanup(handler2))) = false;

      switch (cce_location(L)) {
      case CCE_ERROR:
	flag1 = false;
	flag2 = false;
	cce_run_error_handlers(L);
	break;

      case CCE_SUCCESS:
	flag1 = true;
	flag2 = true;
	if (1) {
	  cce_retry(L);
	}
	// else fall through

      default:
	cce_run_cleanup_handlers(L);
      }
      assert(NULL == L->condition);
      assert(true == flag1);
      assert(true == flag2);
    }
    assert(true == out_flag1);
    assert(true == out_flag2);
  }

  exit(EXIT_SUCCESS);
}

/* end of file */
