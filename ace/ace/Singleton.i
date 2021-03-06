/* -*- C++ -*- */
// Singleton.i,v 4.5 1999/07/14 15:25:12 levine Exp

// Default constructors.
//
// Note: don't explicitly initialize "instance_", because TYPE may not
// have a default constructor.  Let the compiler figure it out . . .

template <class TYPE, class ACE_LOCK> ACE_INLINE
ACE_Singleton<TYPE, ACE_LOCK>::ACE_Singleton (void)
{
}

template <class TYPE, class ACE_LOCK> ACE_INLINE
ACE_Unmanaged_Singleton<TYPE, ACE_LOCK>::ACE_Unmanaged_Singleton (void)
{
}

template <class TYPE, class ACE_LOCK> ACE_INLINE
ACE_TSS_Singleton<TYPE, ACE_LOCK>::ACE_TSS_Singleton (void)
{
}

template <class TYPE, class ACE_LOCK> ACE_INLINE
ACE_Unmanaged_TSS_Singleton<TYPE, ACE_LOCK>::ACE_Unmanaged_TSS_Singleton (void)
{
}
