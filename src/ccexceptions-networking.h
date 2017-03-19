/*
  Part of: CCExceptions
  Contents: system calls for networking
  Date: Sun Mar 19, 2017

  Abstract



  Copyright (C) 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

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

#ifndef CCEXCEPTIONS_NETWORKING_H
#define CCEXCEPTIONS_NETWORKING_H 1

#ifdef __cplusplus
extern "C" {
#endif


/** --------------------------------------------------------------------
 ** Header files.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
//#include <net/if.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>


/** --------------------------------------------------------------------
 ** System call wrappers: sockets.
 ** ----------------------------------------------------------------- */

cce_decl void cce_sys_bind (cce_location_t * L, int socket, struct sockaddr * addr, socklen_t length)
  __attribute__((nonnull(1,3)));

cce_decl void cce_sys_getsockname (cce_location_t * L, int socket, struct sockaddr * addr, socklen_t * length_ptr)
  __attribute__((nonnull(1,3,4)));

cce_decl void cce_sys_inet_aton (cce_location_t * L, const char * name, struct in_addr * addr)
  __attribute__((nonnull(1,2,3)));

cce_decl in_addr_t cce_sys_inet_network (cce_location_t * L, const char * name)
  __attribute__((nonnull(1,2)));

cce_decl struct hostent * cce_sys_gethostbyname (cce_location_t * L, const char * name)
  __attribute__((nonnull(1,2),returns_nonnull));

cce_decl struct hostent * cce_sys_gethostbyname2 (cce_location_t * L, const char * name, int af)
  __attribute__((nonnull(1,2),returns_nonnull));

cce_decl struct hostent * cce_sys_gethostbyaddr (cce_location_t * L, const void * addr, socklen_t length, int format)
  __attribute__((nonnull(1,2),returns_nonnull));

cce_decl int cce_sys_socket (cce_location_t * L, int namespace, int style, int protocol)
  __attribute__((nonnull(1)));

cce_decl void cce_sys_shutdown (cce_location_t * L, int socket, int how)
  __attribute__((nonnull(1)));

cce_decl void cce_sys_socketpair (cce_location_t * L, int namespace, int style, int protocol, int filedes[2])
  __attribute__((nonnull(1,5)));

/* ------------------------------------------------------------------ */

cce_decl void cce_sys_connect (cce_location_t * L, int socket, struct sockaddr * addr, socklen_t length)
  __attribute__((nonnull(1)));

cce_decl void cce_sys_listen (cce_location_t * L, int socket, int N)
  __attribute__((nonnull(1)));

cce_decl int cce_sys_accept (cce_location_t * L, int socket, struct sockaddr * addr, socklen_t * length_ptr)
  __attribute__((nonnull(1,3,4)));

cce_decl void cce_sys_getpeername (cce_location_t * L, int socket, struct sockaddr * addr, socklen_t * length_ptr)
  __attribute__((nonnull(1,3,4)));

cce_decl size_t cce_sys_send (cce_location_t * L, int socket, const void * buffer, size_t size, int flags)
  __attribute__((nonnull(1,3)));

cce_decl size_t cce_sys_recv (cce_location_t * L, int socket, void * buffer, size_t size, int flags)
  __attribute__((nonnull(1,3)));

cce_decl size_t cce_sys_sendto (cce_location_t * L, int socket, const void * buffer, size_t size, int flags,
				struct sockaddr * addr, socklen_t length)
  __attribute__((nonnull(1,3,6)));

cce_decl size_t cce_sys_recvfrom (cce_location_t * L, int socket, void * buffer, size_t size, int flags,
				  struct sockaddr * addr, socklen_t * length_ptr)
  __attribute__((nonnull(1,3,6,7)));

cce_decl void cce_sys_getsockopt (cce_location_t * L, int socket, int level, int optname, void * optval, socklen_t * optlen_ptr)
  __attribute__((nonnull(1,5,6)));

cce_decl void cce_sys_setsockopt (cce_location_t * L, int socket, int level, int optname, const void * optval, socklen_t optlen)
  __attribute__((nonnull(1,5)));


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* CCEXCEPTIONS_NETWORKING_H */

/* end of file */
