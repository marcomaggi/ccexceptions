/*
  Part of: CCExceptions
  Contents: list directory contents
  Date: Mon Mar 13, 2017

  Abstract



  Copyright (C) 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

  The author  hereby grant permission to use,  copy, modify, distribute,
  and  license this  software  and its  documentation  for any  purpose,
  provided that  existing copyright notices  are retained in  all copies
  and that  this notice  is included verbatim  in any  distributions. No
  written agreement, license, or royalty  fee is required for any of the
  authorized uses.  Modifications to this software may be copyrighted by
  their authors and need not  follow the licensing terms described here,
  provided that the new terms are clearly indicated on the first page of
  each file where they apply.

  IN NO  EVENT SHALL THE AUTHOR  OR DISTRIBUTORS BE LIABLE  TO ANY PARTY
  FOR  DIRECT, INDIRECT, SPECIAL,  INCIDENTAL, OR  CONSEQUENTIAL DAMAGES
  ARISING OUT  OF THE  USE OF THIS  SOFTWARE, ITS DOCUMENTATION,  OR ANY
  DERIVATIVES  THEREOF, EVEN  IF THE  AUTHOR  HAVE BEEN  ADVISED OF  THE
  POSSIBILITY OF SUCH DAMAGE.

  THE  AUTHOR  AND DISTRIBUTORS  SPECIFICALLY  DISCLAIM ANY  WARRANTIES,
  INCLUDING,   BUT   NOT  LIMITED   TO,   THE   IMPLIED  WARRANTIES   OF
  MERCHANTABILITY,    FITNESS   FOR    A    PARTICULAR   PURPOSE,    AND
  NON-INFRINGEMENT.  THIS  SOFTWARE IS PROVIDED  ON AN "AS  IS" BASIS,
  AND  THE  AUTHOR  AND  DISTRIBUTORS  HAVE  NO  OBLIGATION  TO  PROVIDE
  MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
*/

#include "ccexceptions.h"

int
main (int argc, const char *const argv[])
{
  cce_location_t		L[1];
  cce_handler_dirstream_t	dirstream_H[1];
  const char *			pathname;

  if (2 == argc) {
    pathname = argv[1];
  } else {
    pathname = "./";
  }

  if (cce_location(L)) {
    cce_run_error_handlers(L);
    cce_condition_free(cce_condition(L));
    exit(EXIT_FAILURE);
  } else {
    DIR *		dirstream;
    struct dirent *	direntry;

    dirstream = cce_sys_opendir(L, pathname);
    cce_cleanup_handler_dirstream_init(L, dirstream_H, dirstream);
    for (direntry = cce_sys_readdir(L, dirstream);
	 direntry;
	 direntry = cce_sys_readdir(L, dirstream)) {
      printf("%s\n", direntry->d_name);
      fflush(stdout);
    }
    cce_run_cleanup_handlers(L);
    exit(EXIT_SUCCESS);
  }
}

/* end of file */
