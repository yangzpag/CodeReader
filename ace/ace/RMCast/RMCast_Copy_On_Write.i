// RMCast_Copy_On_Write.i,v 1.3 2000/10/04 19:28:28 coryan Exp

template<class COLLECTION, class ITERATOR> ACE_INLINE
ACE_RMCast_Copy_On_Write_Collection<COLLECTION,ITERATOR>::
    ACE_RMCast_Copy_On_Write_Collection (void)
      :  refcount_ (1)
{
}

// ****************************************************************

template<class COLLECTION, class ITERATOR> ACE_INLINE
ACE_RMCast_Copy_On_Write_Read_Guard<COLLECTION,ITERATOR>::
    ACE_RMCast_Copy_On_Write_Read_Guard (Container &container)
  : collection (0)
  , mutex_ (container.mutex_)
{
  ACE_GUARD (ACE_SYNCH_MUTEX, ace_mon, this->mutex_);
  this->collection = container.collection_;
  this->collection->_incr_refcnt ();
}

template<class COLLECTION, class ITERATOR> ACE_INLINE
ACE_RMCast_Copy_On_Write_Read_Guard<COLLECTION,ITERATOR>::
    ~ACE_RMCast_Copy_On_Write_Read_Guard (void)
{
  if (this->collection != 0)
    {
      ACE_GUARD (ACE_SYNCH_MUTEX, ace_mon, this->mutex_);
      this->collection->_decr_refcnt ();
    }
}

// ****************************************************************
