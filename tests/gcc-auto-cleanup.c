/*
  Part of: CCExceptions
  Contents: test for GCC automatic variables cleanup
  Date: Dec 23, 2016

  Abstract



  Copyright (C) 2016, 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

  See the COPYING file.
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <setjmp.h>

#define JUMP_TO_ERROR		2
#define JUMP_TO_RETRY		3

bool	flag = false;

static void
func1 (void)
{
  void handler (bool * flagp) {
    flag = *flagp;
  }
  bool flag1 __attribute__((cleanup(handler))) = true;
  return;
}

static void
func2 (jmp_buf bufferp)
{
  void handler (bool * flagp) {
    flag = *flagp;
  }
  bool flag1 __attribute__((cleanup(handler))) = true;
  /* By long-jumping we exclude the cleanup. */
  longjmp(bufferp, 2);
}

int
main (int argc __attribute__((unused)), const char *const argv[] __attribute__((unused)))
{
  /* Simple cleanup. */
  {
    flag = false;
    func1();
    assert(true == flag);
  }

  /* Cleanup with "longjmp()" . */
  {
    jmp_buf	buffer;

    flag = false;
    if (setjmp(buffer)) {
      assert(false == flag);
    } else {
      func2(buffer);
    }
    assert(false == flag);
  }
  exit(EXIT_SUCCESS);
}

/* end of file */
