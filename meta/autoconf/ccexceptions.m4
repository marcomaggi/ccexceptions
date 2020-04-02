#
# Part of: CCExceptions
# Contents: macros for library configuration
# Date: Apr  2, 2020
#
# Abstract
#
#       Macros used in "configure.ac" by CCExceptions.
#
#       Some of these  macros are reused from the  infrastructure of the
#       the package Vicare Scheme.
#
# Copyright (C) 2020 Marco Maggi <mrc.mgg@gmail.com>
#
# This program is  free software: you can redistribute  it and/or modify
# it  under the  terms  of  the GNU  Lesser  General  Public License  as
# published by  the Free  Software Foundation, either  version 3  of the
# License, or (at your option) any later version.
#
# This program  is distributed in the  hope that it will  be useful, but
# WITHOUT   ANY  WARRANTY;   without  even   the  implied   warranty  of
# MERCHANTABILITY  or FITNESS  FOR A  PARTICULAR PURPOSE.   See the  GNU
# General Public License for more details.
#
# You should  have received  a copy  of the  GNU General  Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

AC_DEFUN([CCEXCEPTIONS_ERRNO_TEST],
  [AC_REQUIRE([CCLIB_VALUEOF_TEST])
   CCLIB_VALUEOF_TEST([$1],[$1],[#include <errno.h>
])])

AC_DEFUN([CCEXCEPTIONS_ERRNO_TESTS],
  [m4_map([CCEXCEPTIONS_ERRNO_TEST],[$@])])

# end of file
# Local Variables:
# mode: autoconf
# End:
