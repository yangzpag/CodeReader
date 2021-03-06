/* -*- C++ -*- */
// LSOCK_Stream.i,v 4.2 1998/05/25 18:15:44 irfan Exp

// LSOCK_Stream.i

// Sets both the file descriptors... Overrides handle from the base
// classes.

ASYS_INLINE void
ACE_LSOCK_Stream::set_handle (ACE_HANDLE fd)
{
  ACE_TRACE ("ACE_LSOCK_Stream::set_handle");
  this->ACE_SOCK_Stream::set_handle (fd);
  this->ACE_LSOCK::set_handle (fd);
}

ASYS_INLINE ACE_HANDLE
ACE_LSOCK_Stream::get_handle (void) const
{
  ACE_TRACE ("ACE_LSOCK_Stream::get_handle");
  return this->ACE_SOCK_Stream::get_handle ();
}



