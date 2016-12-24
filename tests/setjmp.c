/*
  Part of: CCExceptions
  Contents: test for setjmp()
  Date: Dec 23, 2016

  Abstract

	Test  file for  "setjmp()"  and  "longjmp()" functions  standard
	behaviour.

  Copyright (C) 2016 Marco Maggi <marco.maggi-ipsu@poste.it>

  See the COPYING file.
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

#define JUMP_TO_ERROR		2
#define JUMP_TO_RETRY		3

int
main (int argc, const char *const argv[])
{
  /* No exception.  Call "setjmp()" but not "longjmp()". */
  {
    sigjmp_buf	L;
    int		flag = 0, code = 0;

    code = sigsetjmp(L, 0);
    if (code) {
      // error occurred
      flag = 2;
    } else {
      // the body
      flag = 1;
    }
    assert(0 == code);
    assert(1 == flag);
  }

  /* Exception  with  "if"  logic.    Call  "setjmp()"  and  "longjmp()"
     once. */
  {
    sigjmp_buf	L;
    int		code;
    int		flag = 0;

    code = sigsetjmp(L, 0);
    if (JUMP_TO_ERROR == code) {
      // error occurred
      flag = 2;
    } else {
      // the body
      siglongjmp(L, JUMP_TO_ERROR);
      flag = 1;
    }
    assert(JUMP_TO_ERROR == code);
    assert(2 == flag);
  }

  /* Exception  with "switch"  logic.  Call  "setjmp()" and  "longjmp()"
     once. */
  {
    sigjmp_buf	L;
    int		code;
    int		flag = 0;

    code = sigsetjmp(L, 0);
    switch (code) {
    case JUMP_TO_ERROR:
      // error occurred
      flag = 2;
      break;
    default:
      // the body
      siglongjmp(L, JUMP_TO_ERROR);
      flag = 1;
      break;
    }
    assert(JUMP_TO_ERROR == code);
    assert(2 == flag);
  }

  /* Exception  with "switch"  logic.   Retrying with  a handler.   Call
     "setjmp()" and "longjmp()" twice to retry. */
  {
    sigjmp_buf	L;
    int		code;
    int		flag = 0;

    code = sigsetjmp(L, 0);
    switch (code) {
    case JUMP_TO_ERROR:
      // error occurred
      siglongjmp(L, JUMP_TO_RETRY);
      flag = 2;
      break;
    case JUMP_TO_RETRY:
      // error occurred, retry
      flag = 3;
      break;
    default:
      // the body
      siglongjmp(L, JUMP_TO_ERROR);
      flag = 1;
      break;
    }
    assert(JUMP_TO_RETRY == code);
    assert(3 == flag);
  }

  /* Exception with "switch" logic.  Retrying the body.  Call "setjmp()"
     and "longjmp()" twice to retry. */
  {
    sigjmp_buf	L;
    int		code;
    int		flag = 0;

    code = sigsetjmp(L, 0);
    switch (code) {
    case JUMP_TO_ERROR:
      // error occurred
      siglongjmp(L, JUMP_TO_RETRY);
      flag = 2;
      break;
    default:
      if (JUMP_TO_RETRY == code) {
	// retrying
	flag = 3;
      } else {
	// the body
	siglongjmp(L, JUMP_TO_ERROR);
	flag = 1;
      }
      break;
    }
    assert(JUMP_TO_RETRY == code);
    assert(3 == flag);
  }

  /* Exception with  "switch" logic.  Retrying  the body 5  times.  Call
     "setjmp()" and "longjmp()" multiple times to retry. */
  {
    sigjmp_buf		L;
    volatile int	times = 0;
    int			code = 0;
    int			flag = 0;

    code = sigsetjmp(L, 0);
    switch (code) {
    case JUMP_TO_ERROR:
      // error occurred
      siglongjmp(L, JUMP_TO_RETRY);
      flag = 2;
      break;
    default:
      if ((JUMP_TO_RETRY == code) && (times < 5)) {
	// retrying
	++times;
	siglongjmp(L, JUMP_TO_ERROR);
      } else if (JUMP_TO_RETRY == code) {
	flag = 3;
      } else {
	// the body
	siglongjmp(L, JUMP_TO_ERROR);
	flag = 1;
      }
      break;
    }
    assert(JUMP_TO_RETRY == code);
    assert(3 == flag);
  }

  exit(EXIT_SUCCESS);
}

/* end of file */
