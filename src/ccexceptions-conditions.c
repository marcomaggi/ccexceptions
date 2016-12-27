/*
  Part of: CCExceptions
  Contents: exceptional condition descriptor functions
  Date: Dec 26, 2016

  Abstract



  Copyright (C) 2016 Marco Maggi <marco.maggi-ipsu@poste.it>

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


#include "ccexceptions-internals.h"
#include <limits.h>	// for INT_MAX
#include <errno.h>
#include <string.h>	// for strerror()

void
cce_condition_free (void * _condition)
{
  cce_condition_t *	C = _condition;
  if (C->table->free) {
    C->table->free(C);
  }
}
const char *
cce_condition_static_message (void * _condition)
{
  cce_condition_t *	C = _condition;
  return C->table->static_message(C);
}


typedef struct cce_errno_condition_t {
  cce_condition_functions_table_t *	table;
  int					errnum;
  const char *				message;
} cce_errno_condition_t;

static const char * cce_condition_errno_static_message_fun (void * _condition) {
  cce_errno_condition_t	* C = _condition;
  return C->message;
}

static cce_condition_functions_table_t cce_condition_errno_table = {
  NULL, // cce_condition_free_fun_t *
  cce_condition_errno_static_message_fun
};

#define CCE_DECLARE_ERRNO_CONDITION(ERRNO,MESSAGE)	\
  							\
  {							\
    .table	= &cce_condition_errno_table,		\
    .errnum	= ERRNO,				\
    .message	= MESSAGE				\
  }

static const cce_errno_condition_t
cce_errno_conditions[] = {
  CCE_DECLARE_ERRNO_CONDITION(0,			"(errno=0) Success"),
  /* Whenever  an  errno  constant  is not  defined  by  the  underlying
     platform:  the  "configure"  script  defines it  as  -1.   Here  we
     intercept the -1 value so that  it is not mistaken for an undefined
     constant. */
  CCE_DECLARE_ERRNO_CONDITION(-1,			"Invalid errno value"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EPERM,		"(errno=EPERM)"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOENT,		"(errno=ENOENT) No such file or directory"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ESRCH,		"(errno=ESRCH) No such process"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EINTR,		"(errno=EINTR) Interrupted system call"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EIO,		"(errno=EIO) Input/output error"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENXIO,		"(errno=ENXIO) No such device or address"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_E2BIG,		"(errno=E2BIG) Argument list too long"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOEXEC,		"(errno=ENOEXEC) Exec format error"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EBADF,		"(errno=EBADF) Bad file descriptor"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ECHILD,		"(errno=ECHILD) No child processes"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EPROCLIM,		"(errno=EPROCLIM) Too many processes"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EAGAIN,		"(errno=EAGAIN) Resource temporarily unavailable"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOMEM,		"(errno=ENOMEM) Cannot allocate memory"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EACCES,		"(errno=EACCES) Access permission denied"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EFAULT,		"(errno=EFAULT) Bad address"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOTBLK,		"(errno=ENOTBLK) Block device required"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EBUSY,		"(errno=EBUSY) Device or resource busy"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EEXIST,		"(errno=EEXIST) File exists"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EXDEV,		"(errno=EXDEV) Invalid cross-device link"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENODEV,		"(errno=ENODEV) No such device"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOTDIR,		"(errno=ENOTDIR) Not a directory"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EISDIR,		"(errno=EISDIR) Is a directory"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EINVAL,		"(errno=EINVAL) Invalid argument"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENFILE,		"(errno=ENFILE) Too many open files in system"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EMFILE,		"(errno=EMFILE) Too many open files"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOTTY,		"(errno=ENOTTY) Inappropriate ioctl for device"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ETXTBSY,		"(errno=ETXTBSY) Text file busy"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EFBIG,		"(errno=EFBIG) File too large"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOSPC,		"(errno=ENOSPC) No space left on device"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ESPIPE,		"(errno=ESPIPE) Illegal seek"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EROFS,		"(errno=EROFS) Read-only file system"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EMLINK,		"(errno=EMLINK) Too many links"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EPIPE,		"(errno=EPIPE) Broken pipe"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EDOM,		"(errno=EDOM) Argument out of domain"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ERANGE,		"(errno=ERANGE) Result out of range"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EDEADLK,		"(errno=EDEADLK) Resource deadlock avoided"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENAMETOOLONG,	"(errno=ENAMETOOLONG) File name too long"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOLCK,		"(errno=ENOLCK) No locks available"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOSYS,		"(errno=ENOSYS) Operation not implemented"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOTEMPTY,	"(errno=ENOTEMPTY) Directory not empty"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ELOOP,		"(errno=ELOOP) Too many levels of symbolic links"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EWOULDBLOCK,	"(errno=EWOULDBLOCK) Operation would block"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOMSG,		"(errno=ENOMSG) No message of desired type"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EIDRM,		"(errno=EIDRM) Identifier removed"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ECHRNG,		"(errno=ECHRNG) Channel number out of range"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EL2NSYNC,		"(errno=EL2NSYNC) Level 2 not synchronized"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EL3HLT,		"(errno=EL3HLT) Level 3 halted"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EL3RST,		"(errno=EL3RST) Level 3 reset"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ELNRNG,		"(errno=ELNRNG) Link number out of range"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EUNATCH,		"(errno=EUNATCH) Protocol driver not attached"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOCSI,		"(errno=ENOCSI) No CSI structure available"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EL2HLT,		"(errno=EL2HLT) Level 2 halted"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EBADE,		"(errno=EBADE) Invalid exchange"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EBADR,		"(errno=EBADR) Invalid request descriptor"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EXFULL,		"(errno=EXFULL) Exchange full"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOANO,		"(errno=ENOANO) No anode"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EBADRQC,		"(errno=EBADRQC) Invalid request code"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EBADSLT,		"(errno=EBADSLT) Invalid slot"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EDEADLOCK,	"(errno=EDEADLOCK) File locking deadlock error"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EBFONT,		"(errno=EBFONT) Bad font file format"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOSTR,		"(errno=ENOSTR) Device not a stream"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENODATA,		"(errno=ENODATA) No data available"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ETIME,		"(errno=ETIME) Timer expired"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOSR,		"(errno=ENOSR) Out of streams resources"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENONET,		"(errno=ENONET) Machine is not on the network"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOPKG,		"(errno=ENOPKG) Package not installed"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EREMOTE,		"(errno=EREMOTE) Object is remote"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOLINK,		"(errno=ENOLINK)"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EADV,		"(errno=EADV) Advertise error"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ESRMNT,		"(errno=ESRMNT) Srmount error"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ECOMM,		"(errno=ECOMM) Communication error on send"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EPROTO,		"(errno=EPROTO) Protocol error"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EMULTIHOP,	"(errno=EMULTIHOP) Multihop attempted"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EDOTDOT,		"(errno=EDOTDOT) RFS specific error"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EBADMSG,		"(errno=EBADMSG) Bad message"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EOVERFLOW,	"(errno=EOVERFLOW) Value too large for defined data type"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOTUNIQ,		"(errno=ENOTUNIQ) Name not unique on network"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EBADFD,		"(errno=EBADFD) File descriptor in bad state"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EREMCHG,		"(errno=EREMCHG) Remote address changed"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ELIBACC,		"(errno=ELIBACC) Can not access a needed shared library"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ELIBBAD,		"(errno=ELIBBAD) Accessing a corrupted shared library"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ELIBSCN,		"(errno=ELIBSCN) .lib section in a.out corrupted"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ELIBMAX,		"(errno=ELIBMAX) Attempting to link in too many shared libraries"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ELIBEXEC,		"(errno=ELIBEXEC) Cannot exec a shared library directly"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EILSEQ,		"(errno=EILSEQ) Invalid or incomplete multibyte or wide character"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ERESTART,		"(errno=ERESTART) Interrupted system call should be restarted"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ESTRPIPE,		"(errno=ESTRPIPE) Streams pipe error"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EUSERS,		"(errno=EUSERS) Too many users"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOTSOCK,		"(errno=ENOTSOCK) Socket operation on non-socket"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EDESTADDRREQ,	"(errno=EDESTADDRREQ) Destination address required"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EMSGSIZE,		"(errno=EMSGSIZE) Message too long"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EPROTOTYPE,	"(errno=EPROTOTYPE) Protocol wrong type for socket"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOPROTOOPT,	"(errno=ENOPROTOOPT) Protocol not available"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EPROTONOSUPPORT,	"(errno=EPROTONOSUPPORT) Protocol not supported"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ESOCKTNOSUPPORT,	"(errno=ESOCKTNOSUPPORT) Socket type not supported"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EOPNOTSUPP,	"(errno=EOPNOTSUPP) Operation not supported"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EPFNOSUPPORT,	"(errno=EPFNOSUPPORT) Protocol family not supported"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EAFNOSUPPORT,	"(errno=EAFNOSUPPORT) Address family not supported by protocol"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EADDRINUSE,	"(errno=EADDRINUSE) Address already in use"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EADDRNOTAVAIL,	"(errno=EADDRNOTAVAIL) Cannot assign requested address"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENETDOWN,		"(errno=ENETDOWN) Network is down"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENETUNREACH,	"(errno=ENETUNREACH) Network is unreachable"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENETRESET,	"(errno=ENETRESET) Network dropped connection on reset"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ECONNABORTED,	"(errno=ECONNABORTED) Software caused connection abort"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ECONNRESET,	"(errno=ECONNRESET) Connection reset by peer"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOBUFS,		"(errno=ENOBUFS) No buffer space available"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EISCONN,		"(errno=EISCONN) Transport endpoint is already connected"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOTCONN,		"(errno=ENOTCONN) Transport endpoint is not connected"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ESHUTDOWN,	"(errno=ESHUTDOWN) Cannot send after transport endpoint shutdown"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ETOOMANYREFS,	"(errno=ETOOMANYREFS) Too many references: cannot splice"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ETIMEDOUT,	"(errno=ETIMEDOUT) Connection timed out"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ECONNREFUSED,	"(errno=ECONNREFUSED) Connection refused"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EHOSTDOWN,	"(errno=EHOSTDOWN) Host is down"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EHOSTUNREACH,	"(errno=EHOSTUNREACH) No route to host"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EALREADY,		"(errno=EALREADY) Operation already in progress"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EINPROGRESS,	"(errno=EINPROGRESS) Operation now in progress"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ESTALE,		"(errno=ESTALE) Stale NFS file handle"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EUCLEAN,		"(errno=EUCLEAN) Structure needs cleaning"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOTNAM,		"(errno=ENOTNAM) Not a XENIX named type file"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENAVAIL,		"(errno=ENAVAIL) No XENIX semaphores available"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EISNAM,		"(errno=EISNAM) Is a named type file"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EREMOTEIO,	"(errno=EREMOTEIO) Remote I/O error"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EDQUOT,		"(errno=EDQUOT) Disk quota exceeded"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOMEDIUM,	"(errno=ENOMEDIUM) No medium found"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EMEDIUMTYPE,	"(errno=EMEDIUMTYPE) Wrong medium type"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ECANCELED,	"(errno=ECANCELED) Operation canceled"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOKEY,		"(errno=ENOKEY) Required key not available"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EKEYEXPIRED,	"(errno=EKEYEXPIRED) Key has expired"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EKEYREVOKED,	"(errno=EKEYREVOKED) Key has been revoked"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EKEYREJECTED,	"(errno=EKEYREJECTED) Key was rejected by service"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EOWNERDEAD,	"(errno=EOWNERDEAD) Owner died"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOTRECOVERABLE,	"(errno=ENOTRECOVERABLE) State not recoverable"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EBADRPC,		"(errno=EBADRPC) RPC struct is bad"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ERPCMISMATCH,	"(errno=ERPCMISMATCH) RPC version wrong"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EPROGUNAVAIL,	"(errno=EPROGUNAVAIL) RPC program not available"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EPROGMISMATCH,	"(errno=EPROGMISMATCH) RPC program version wrong"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EPROCUNAVAIL,	"(errno=EPROCUNAVAIL) RPC bad procedure for program"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EFTYPE,		"(errno=EFTYPE) Inappropriate file type or format"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EAUTH,		"(errno=EAUTH) Authentication error"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENEEDAUTH,	"(errno=ENEEDAUTH) Need authenticator"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOTSUP,		"(errno=ENOTSUP) Not supported"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EBACKGROUND,	"(errno=EBACKGROUND) Inappropriate operation for background process"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EDIED,		"(errno=EDIED) Translator died"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOLINK,		"(errno=ENOLINK) Link has been severed"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ERFKILL,		"(errno=ERFKILL) Operation not possible due to RF-kill"),
  CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EHWPOISON,	"(errno=EHWPOISON) Memory page has hardware error"),
  CCE_DECLARE_ERRNO_CONDITION(INT_MAX,			"Unknown errno code")
};

static const cce_errno_condition_t cce_invalid_errno_condition = CCE_DECLARE_ERRNO_CONDITION(INT_MAX, "Unknown errno code");

cce_condition_t *
cce_condition_errno (int errnum)
{
  for (int i = 0; INT_MAX != cce_errno_conditions[i].errnum; ++i) {
    if (errnum == cce_errno_conditions[i].errnum) {
      return (cce_condition_t *) &(cce_errno_conditions[i]);
    }
  }
  /* If  we  are  here  ERRNUM  is an  invalid  "errno"  value  for  the
     underlying platform. */
  return (cce_condition_t *) &cce_invalid_errno_condition;
}

/* end of file */
