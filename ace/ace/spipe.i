/* -*- C++ -*- */
// SPIPE.i,v 4.4 1998/04/30 23:25:51 nanbor Exp

// SPIPE.i

ASYS_INLINE int
ACE_SPIPE::disable (int signum) const
{
#if defined (ACE_WIN32)
  ACE_UNUSED_ARG (signum) ;
  return 0 ;
#else  /* ACE_WIN32 */
  return ACE_IPC_SAP::disable (signum) ;
#endif /* ACE_WIN32 */
}

