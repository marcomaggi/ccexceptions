/*
  Part of: CCExceptions
  Contents: exceptional condition descriptor functions
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


#include "ccexceptions-internals.h"
#include <limits.h>	// for INT_MAX
#include <errno.h>

void
cce_condition_init (cce_condition_t * C, const cce_condition_descriptor_t * D)
{
  C->descriptor = D;
}
const cce_condition_descriptor_t *
cce_condition_descriptor (const cce_condition_t * C)
{
  return C->descriptor;
}
void
cce_condition_free (cce_condition_t * C)
{
  if (C->descriptor->free) {
    C->descriptor->free(C);
  }
}
const char *
cce_condition_static_message (cce_condition_t * C)
{
  return C->descriptor->static_message(C);
}
bool
cce_condition_is_a (const cce_condition_t * C, const cce_condition_descriptor_t * descriptor)
{
  return cce_condition_descriptor_child_and_parent(C->descriptor, descriptor);
}
bool
cce_condition_descriptor_child_and_parent (const cce_condition_descriptor_t * child, const cce_condition_descriptor_t * parent)
{
  for (; child; child = child->parent) {
    if (child == parent) {
      return true;
    }
  }
  return false;
}


static const char *
cce_root_condition_static_message_fun (const cce_condition_t * C CCE_UNUSED)
{
  return "Unknown exceptional condition";
}

/* This  condition descriptor  is  the  root of  the  tree of  condition
   descriptors. */
static const cce_condition_descriptor_t cce_root_condition_descriptor_stru = {
  .parent		= NULL,
  .free			= NULL,
  .static_message	= cce_root_condition_static_message_fun
};

const cce_condition_descriptor_t * cce_root_condition_descriptor = &cce_root_condition_descriptor_stru;

/* ------------------------------------------------------------------ */

/* This   condition  descriptor   represents   an  unknown   exceptional
   condition.   This   descriptor  has  only  one   instance  statically
   allocated below: "cce_unknown_condition". */
static const cce_condition_descriptor_t cce_unknown_condition_descriptor_stru = {
  .parent		= &cce_root_condition_descriptor_stru,
  .free			= NULL,
  .static_message	= cce_root_condition_static_message_fun
};

const cce_condition_descriptor_t * cce_unknown_condition_descriptor = &cce_unknown_condition_descriptor_stru;

/* This is the single instance  of unknown exceptional condition.  It is
   used by "cce_raise()" and "cce_retry()". */
static const cce_condition_t cce_unknown_condition_stru = {
  .descriptor = &cce_unknown_condition_descriptor_stru
};

const cce_condition_t * cce_unknown_condition		= &cce_unknown_condition_stru;

/* ------------------------------------------------------------------ */

static const char *
cce_errno_condition_static_message_fun (const cce_condition_t * C)
{
  const cce_errno_condition_t *	EC = (const cce_errno_condition_t *)C;
  return EC->message;
}

/* This condition descriptor  represents "errno" exceptional conditions.
   It is a child of the root descriptor. */
const cce_errno_condition_descriptor_t cce_errno_condition_descriptor_stru = {
  .parent		= &cce_root_condition_descriptor_stru,
  .free			= NULL,
  .static_message	= cce_errno_condition_static_message_fun
};

const cce_condition_descriptor_t * cce_errno_condition_descriptor = \
  (const cce_condition_descriptor_t *) &cce_errno_condition_descriptor_stru;


#define CCE_DECLARE_ERRNO_CONDITION(ERRNO,MESSAGE)	\
  							\
  {							\
    .descriptor	= &cce_errno_condition_descriptor_stru,	\
    .errnum	= ERRNO,				\
    .message	= MESSAGE				\
  }

#define ERRNO_CONDITIONS_NUM		149
#define LAST_ERRNO_CONDITION		148

static const cce_errno_condition_t
cce_errno_conditions[ERRNO_CONDITIONS_NUM] = {
  /* 000 */ CCE_DECLARE_ERRNO_CONDITION(0,			"(errno=0) Success"),
  /* Whenever  an  errno  constant  is not  defined  by  the  underlying
     platform: the "configure" script  defines the associated "VALUEOF_"
     constant as  -1.  Here  we intercept  the -1  value so  that, while
     performing a  linear search,  it is not  mistaken for  an undefined
     constant. */
  /* 001 */ CCE_DECLARE_ERRNO_CONDITION(-1,			"Invalid errno value"),
  /* 002 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EPERM,		"(errno=EPERM) Permission denied"),
  /* 003 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOENT,		"(errno=ENOENT) No such file or directory"),
  /* 004 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ESRCH,		"(errno=ESRCH) No such process"),
  /* 005 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EINTR,		"(errno=EINTR) Interrupted system call"),
  /* 006 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EIO,		"(errno=EIO) Input/output error"),
  /* 007 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENXIO,		"(errno=ENXIO) No such device or address"),
  /* 008 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_E2BIG,		"(errno=E2BIG) Argument list too long"),
  /* 009 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOEXEC,	"(errno=ENOEXEC) Exec format error"),
  /* 010 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EBADF,		"(errno=EBADF) Bad file descriptor"),
  /* 011 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ECHILD,		"(errno=ECHILD) No child processes"),
  /* 012 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EPROCLIM,	"(errno=EPROCLIM) Too many processes"),
  /* 013 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EAGAIN,		"(errno=EAGAIN) Resource temporarily unavailable"),
  /* 014 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOMEM,		"(errno=ENOMEM) Cannot allocate memory"),
  /* 015 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EACCES,		"(errno=EACCES) Access permission denied"),
  /* 016 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EFAULT,		"(errno=EFAULT) Bad address"),
  /* 017 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOTBLK,	"(errno=ENOTBLK) Block device required"),
  /* 018 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EBUSY,		"(errno=EBUSY) Device or resource busy"),
  /* 019 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EEXIST,		"(errno=EEXIST) File exists"),
  /* 020 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EXDEV,		"(errno=EXDEV) Invalid cross-device link"),
  /* 021 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENODEV,		"(errno=ENODEV) No such device"),
  /* 022 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOTDIR,	"(errno=ENOTDIR) Not a directory"),
  /* 023 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EISDIR,		"(errno=EISDIR) Is a directory"),
  /* 024 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EINVAL,		"(errno=EINVAL) Invalid argument"),
  /* 025 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENFILE,		"(errno=ENFILE) Too many open files in system"),
  /* 026 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EMFILE,		"(errno=EMFILE) Too many open files"),
  /* 027 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOTTY,		"(errno=ENOTTY) Inappropriate ioctl for device"),
  /* 028 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ETXTBSY,	"(errno=ETXTBSY) Text file busy"),
  /* 029 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EFBIG,		"(errno=EFBIG) File too large"),
  /* 030 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOSPC,		"(errno=ENOSPC) No space left on device"),
  /* 031 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ESPIPE,		"(errno=ESPIPE) Illegal seek"),
  /* 032 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EROFS,		"(errno=EROFS) Read-only file system"),
  /* 033 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EMLINK,		"(errno=EMLINK) Too many links"),
  /* 034 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EPIPE,		"(errno=EPIPE) Broken pipe"),
  /* 035 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EDOM,		"(errno=EDOM) Argument out of domain"),
  /* 036 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ERANGE,		"(errno=ERANGE) Result out of range"),
  /* 037 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EDEADLK,	"(errno=EDEADLK) Resource deadlock avoided"),
  /* 038 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENAMETOOLONG,	"(errno=ENAMETOOLONG) File name too long"),
  /* 039 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOLCK,		"(errno=ENOLCK) No locks available"),
  /* 040 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOSYS,		"(errno=ENOSYS) Operation not implemented"),
  /* 041 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOTEMPTY,	"(errno=ENOTEMPTY) Directory not empty"),
  /* 042 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ELOOP,		"(errno=ELOOP) Too many levels of symbolic links"),
  /* 043 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EWOULDBLOCK,	"(errno=EWOULDBLOCK) Operation would block"),
  /* 044 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOMSG,		"(errno=ENOMSG) No message of desired type"),
  /* 045 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EIDRM,		"(errno=EIDRM) Identifier removed"),
  /* 046 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ECHRNG,		"(errno=ECHRNG) Channel number out of range"),
  /* 047 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EL2NSYNC,	"(errno=EL2NSYNC) Level 2 not synchronized"),
  /* 048 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EL3HLT,		"(errno=EL3HLT) Level 3 halted"),
  /* 049 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EL3RST,		"(errno=EL3RST) Level 3 reset"),
  /* 050 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ELNRNG,		"(errno=ELNRNG) Link number out of range"),
  /* 051 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EUNATCH,	"(errno=EUNATCH) Protocol driver not attached"),
  /* 052 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOCSI,		"(errno=ENOCSI) No CSI structure available"),
  /* 053 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EL2HLT,		"(errno=EL2HLT) Level 2 halted"),
  /* 054 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EBADE,		"(errno=EBADE) Invalid exchange"),
  /* 055 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EBADR,		"(errno=EBADR) Invalid request descriptor"),
  /* 056 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EXFULL,		"(errno=EXFULL) Exchange full"),
  /* 057 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOANO,		"(errno=ENOANO) No anode"),
  /* 058 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EBADRQC,	"(errno=EBADRQC) Invalid request code"),
  /* 059 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EBADSLT,	"(errno=EBADSLT) Invalid slot"),
  /* 060 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EDEADLOCK,	"(errno=EDEADLOCK) File locking deadlock error"),
  /* 061 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EBFONT,		"(errno=EBFONT) Bad font file format"),
  /* 062 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOSTR,		"(errno=ENOSTR) Device not a stream"),
  /* 063 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENODATA,	"(errno=ENODATA) No data available"),
  /* 064 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ETIME,		"(errno=ETIME) Timer expired"),
  /* 065 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOSR,		"(errno=ENOSR) Out of streams resources"),
  /* 066 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENONET,		"(errno=ENONET) Machine is not on the network"),
  /* 067 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOPKG,		"(errno=ENOPKG) Package not installed"),
  /* 068 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EREMOTE,	"(errno=EREMOTE) Object is remote"),
  /* 069 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOLINK,	"(errno=ENOLINK)"),
  /* 070 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EADV,		"(errno=EADV) Advertise error"),
  /* 071 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ESRMNT,		"(errno=ESRMNT) Srmount error"),
  /* 072 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ECOMM,		"(errno=ECOMM) Communication error on send"),
  /* 073 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EPROTO,		"(errno=EPROTO) Protocol error"),
  /* 074 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EMULTIHOP,	"(errno=EMULTIHOP) Multihop attempted"),
  /* 075 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EDOTDOT,	"(errno=EDOTDOT) RFS specific error"),
  /* 076 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EBADMSG,	"(errno=EBADMSG) Bad message"),
  /* 077 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EOVERFLOW,	"(errno=EOVERFLOW) Value too large for defined data type"),
  /* 078 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOTUNIQ,	"(errno=ENOTUNIQ) Name not unique on network"),
  /* 079 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EBADFD,		"(errno=EBADFD) File descriptor in bad state"),
  /* 080 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EREMCHG,	"(errno=EREMCHG) Remote address changed"),
  /* 081 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ELIBACC,	"(errno=ELIBACC) Can not access a needed shared library"),
  /* 082 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ELIBBAD,	"(errno=ELIBBAD) Accessing a corrupted shared library"),
  /* 083 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ELIBSCN,	"(errno=ELIBSCN) .lib section in a.out corrupted"),
  /* 084 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ELIBMAX,	"(errno=ELIBMAX) Attempting to link in too many shared libraries"),
  /* 085 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ELIBEXEC,	"(errno=ELIBEXEC) Cannot exec a shared library directly"),
  /* 086 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EILSEQ,		"(errno=EILSEQ) Invalid or incomplete multibyte or wide character"),
  /* 087 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ERESTART,	"(errno=ERESTART) Interrupted system call should be restarted"),
  /* 088 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ESTRPIPE,	"(errno=ESTRPIPE) Streams pipe error"),
  /* 089 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EUSERS,		"(errno=EUSERS) Too many users"),
  /* 090 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOTSOCK,	"(errno=ENOTSOCK) Socket operation on non-socket"),
  /* 091 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EDESTADDRREQ,	"(errno=EDESTADDRREQ) Destination address required"),
  /* 092 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EMSGSIZE,	"(errno=EMSGSIZE) Message too long"),
  /* 093 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EPROTOTYPE,	"(errno=EPROTOTYPE) Protocol wrong type for socket"),
  /* 094 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOPROTOOPT,	"(errno=ENOPROTOOPT) Protocol not available"),
  /* 095 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EPROTONOSUPPORT,"(errno=EPROTONOSUPPORT) Protocol not supported"),
  /* 096 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ESOCKTNOSUPPORT,"(errno=ESOCKTNOSUPPORT) Socket type not supported"),
  /* 097 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EOPNOTSUPP,	"(errno=EOPNOTSUPP) Operation not supported"),
  /* 098 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EPFNOSUPPORT,	"(errno=EPFNOSUPPORT) Protocol family not supported"),
  /* 099 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EAFNOSUPPORT,	"(errno=EAFNOSUPPORT) Address family not supported by protocol"),
  /* 100 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EADDRINUSE,	"(errno=EADDRINUSE) Address already in use"),
  /* 101 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EADDRNOTAVAIL,	"(errno=EADDRNOTAVAIL) Cannot assign requested address"),
  /* 102 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENETDOWN,	"(errno=ENETDOWN) Network is down"),
  /* 103 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENETUNREACH,	"(errno=ENETUNREACH) Network is unreachable"),
  /* 104 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENETRESET,	"(errno=ENETRESET) Network dropped connection on reset"),
  /* 105 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ECONNABORTED,	"(errno=ECONNABORTED) Software caused connection abort"),
  /* 106 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ECONNRESET,	"(errno=ECONNRESET) Connection reset by peer"),
  /* 107 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOBUFS,	"(errno=ENOBUFS) No buffer space available"),
  /* 108 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EISCONN,	"(errno=EISCONN) Transport endpoint is already connected"),
  /* 109 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOTCONN,	"(errno=ENOTCONN) Transport endpoint is not connected"),
  /* 110 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ESHUTDOWN,	"(errno=ESHUTDOWN) Cannot send after transport endpoint shutdown"),
  /* 111 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ETOOMANYREFS,	"(errno=ETOOMANYREFS) Too many references: cannot splice"),
  /* 112 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ETIMEDOUT,	"(errno=ETIMEDOUT) Connection timed out"),
  /* 113 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ECONNREFUSED,	"(errno=ECONNREFUSED) Connection refused"),
  /* 114 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EHOSTDOWN,	"(errno=EHOSTDOWN) Host is down"),
  /* 115 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EHOSTUNREACH,	"(errno=EHOSTUNREACH) No route to host"),
  /* 116 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EALREADY,	"(errno=EALREADY) Operation already in progress"),
  /* 117 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EINPROGRESS,	"(errno=EINPROGRESS) Operation now in progress"),
  /* 118 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ESTALE,		"(errno=ESTALE) Stale NFS file handle"),
  /* 119 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EUCLEAN,	"(errno=EUCLEAN) Structure needs cleaning"),
  /* 120 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOTNAM,	"(errno=ENOTNAM) Not a XENIX named type file"),
  /* 121 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENAVAIL,	"(errno=ENAVAIL) No XENIX semaphores available"),
  /* 122 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EISNAM,		"(errno=EISNAM) Is a named type file"),
  /* 123 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EREMOTEIO,	"(errno=EREMOTEIO) Remote I/O error"),
  /* 124 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EDQUOT,		"(errno=EDQUOT) Disk quota exceeded"),
  /* 125 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOMEDIUM,	"(errno=ENOMEDIUM) No medium found"),
  /* 126 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EMEDIUMTYPE,	"(errno=EMEDIUMTYPE) Wrong medium type"),
  /* 127 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ECANCELED,	"(errno=ECANCELED) Operation canceled"),
  /* 128 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOKEY,		"(errno=ENOKEY) Required key not available"),
  /* 129 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EKEYEXPIRED,	"(errno=EKEYEXPIRED) Key has expired"),
  /* 130 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EKEYREVOKED,	"(errno=EKEYREVOKED) Key has been revoked"),
  /* 131 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EKEYREJECTED,	"(errno=EKEYREJECTED) Key was rejected by service"),
  /* 132 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EOWNERDEAD,	"(errno=EOWNERDEAD) Owner died"),
  /* 133 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOTRECOVERABLE,"(errno=ENOTRECOVERABLE) State not recoverable"),
  /* 134 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EBADRPC,	"(errno=EBADRPC) RPC struct is bad"),
  /* 135 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ERPCMISMATCH,	"(errno=ERPCMISMATCH) RPC version wrong"),
  /* 136 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EPROGUNAVAIL,	"(errno=EPROGUNAVAIL) RPC program not available"),
  /* 137 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EPROGMISMATCH,	"(errno=EPROGMISMATCH) RPC program version wrong"),
  /* 138 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EPROCUNAVAIL,	"(errno=EPROCUNAVAIL) RPC bad procedure for program"),
  /* 139 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EFTYPE,		"(errno=EFTYPE) Inappropriate file type or format"),
  /* 140 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EAUTH,		"(errno=EAUTH) Authentication error"),
  /* 141 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENEEDAUTH,	"(errno=ENEEDAUTH) Need authenticator"),
  /* 142 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOTSUP,	"(errno=ENOTSUP) Not supported"),
  /* 143 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EBACKGROUND,	"(errno=EBACKGROUND) Inappropriate operation for background process"),
  /* 144 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EDIED,		"(errno=EDIED) Translator died"),
  /* 145 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ENOLINK,	"(errno=ENOLINK) Link has been severed"),
  /* 146 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_ERFKILL,	"(errno=ERFKILL) Operation not possible due to RF-kill"),
  /* 147 */ CCE_DECLARE_ERRNO_CONDITION(VALUEOF_EHWPOISON,	"(errno=EHWPOISON) Memory page has hardware error"),
  /* 148 */ CCE_DECLARE_ERRNO_CONDITION(INT_MAX,		"Unknown errno code")
};

cce_condition_t *
cce_errno_condition (int errnum)
{
  for (int i = 0; i < ERRNO_CONDITIONS_NUM; ++i) {
    if (errnum == cce_errno_conditions[i].errnum) {
      return (cce_condition_t *)&(cce_errno_conditions[i]);
    }
  }
  /* If  we  are  here  ERRNUM  is an  invalid  "errno"  value  for  the
     underlying platform. */
  return (cce_condition_t *)&(cce_errno_conditions[LAST_ERRNO_CONDITION]);
}

/* end of file */