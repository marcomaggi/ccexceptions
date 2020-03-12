/*
  Part of: CCExceptions
  Contents: version functions
  Date: Sat Dec 17, 2016

  Abstract



  Copyright (C) 2016, 2017 Marco Maggi <mrc.mgg@gmail.com>

  This program is  free software: you can redistribute  it and/or modify
  it  under the  terms  of  the GNU  Lesser  General  Public License  as
  published by  the Free  Software Foundation, either  version 3  of the
  License, or (at your option) any later version.

  This program  is distributed in the  hope that it will  be useful, but
  WITHOUT   ANY  WARRANTY;   without  even   the  implied   warranty  of
  MERCHANTABILITY  or FITNESS  FOR A  PARTICULAR PURPOSE.   See  the GNU
  General Public License for more details.

  You should  have received  a copy  of the  GNU >lesser  General Public
  License     along    with     this    program.      If    not,     see
  <http://www.gnu.org/licenses/>.
*/


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "ccexceptions-internals.h"


char const *
cce_version_string (void)
{
  return ccexceptions_VERSION_INTERFACE_STRING;
}
int
cce_version_interface_current (void)
{
  return ccexceptions_VERSION_INTERFACE_CURRENT;
}
int
cce_version_interface_revision (void)
{
  return ccexceptions_VERSION_INTERFACE_REVISION;
}
int
cce_version_interface_age (void)
{
  return ccexceptions_VERSION_INTERFACE_AGE;
}

/* end of file */
