// ESF_Copy_On_Write.cpp,v 1.4 2000/10/31 03:11:12 coryan Exp

#ifndef TAO_ESF_COPY_ON_WRITE_CPP
#define TAO_ESF_COPY_ON_WRITE_CPP

#include "ESF_Copy_On_Write.h"

#if ! defined (__ACE_INLINE__)
#include "ESF_Copy_On_Write.i"
#endif /* __ACE_INLINE__ */

ACE_RCSID(ESF, ESF_Copy_On_Write, "ESF_Copy_On_Write.cpp,v 1.4 2000/10/31 03:11:12 coryan Exp")

template<class COLLECTION, class ITERATOR> CORBA::ULong
TAO_ESF_Copy_On_Write_Collection<COLLECTION,ITERATOR>::_incr_refcnt (void)
{
  // LOCKING: no locking is required, the caller grabs the mutex.
  return this->refcount_++;
}

template<class COLLECTION, class ITERATOR> CORBA::ULong
TAO_ESF_Copy_On_Write_Collection<COLLECTION,ITERATOR>::_decr_refcnt (void)
{
  // LOCKING: no locking is required, the caller grabs the mutex.
  {
    this->refcount_--;
    if (this->refcount_ != 0)
      return this->refcount_;
  }

  ITERATOR end = this->collection.end ();
  for (ITERATOR i = this->collection.begin (); i != end; ++i)
    {
      (*i)->_decr_refcnt ();
    }

  delete this;
  return 0;
}

// ****************************************************************

template<class PROXY, class COLLECTION, class ITERATOR, ACE_SYNCH_DECL>
TAO_ESF_Copy_On_Write<PROXY,COLLECTION,ITERATOR,ACE_SYNCH_USE>::
    TAO_ESF_Copy_On_Write (void)
      :  pending_writes_ (0),
         writing_ (0),
         cond_ (mutex_)
{
  ACE_NEW (this->collection_, Collection);
}

template<class PROXY, class COLLECTION, class ITERATOR, ACE_SYNCH_DECL>
TAO_ESF_Copy_On_Write<PROXY,COLLECTION,ITERATOR,ACE_SYNCH_USE>::
    ~TAO_ESF_Copy_On_Write (void)
{
  ACE_GUARD (ACE_SYNCH_MUTEX_T, ace_mon, this->mutex_);

  while (this->pending_writes_ != 0)
    this->cond_.wait ();

  this->collection_->_decr_refcnt ();
  this->collection_ = 0;
}

template<class PROXY, class COLLECTION, class ITERATOR, ACE_SYNCH_DECL> void
TAO_ESF_Copy_On_Write<PROXY,COLLECTION,ITERATOR,ACE_SYNCH_USE>::
    for_each (TAO_ESF_Worker<PROXY> *worker,
              CORBA::Environment &ACE_TRY_ENV)
{
  Read_Guard ace_mon (this->mutex_,
                      this->collection_);

  ITERATOR end = ace_mon.collection->collection.end ();
  for (ITERATOR i = ace_mon.collection->collection.begin (); i != end; ++i)
    {
      worker->work (*i, ACE_TRY_ENV);
      ACE_CHECK;
    }
}

template<class PROXY, class COLLECTION, class ITERATOR, ACE_SYNCH_DECL> void
TAO_ESF_Copy_On_Write<PROXY,COLLECTION,ITERATOR,ACE_SYNCH_USE>::
    connected (PROXY *proxy,
               CORBA::Environment &ACE_TRY_ENV)
{
  Write_Guard ace_mon (this->mutex_,
                       this->cond_,
                       this->pending_writes_,
                       this->writing_,
                       this->collection_);

  proxy->_incr_refcnt ();
  ace_mon.copy->collection.connected (proxy, ACE_TRY_ENV);
}

template<class PROXY, class COLLECTION, class ITERATOR, ACE_SYNCH_DECL> void
TAO_ESF_Copy_On_Write<PROXY,COLLECTION,ITERATOR,ACE_SYNCH_USE>::
    reconnected (PROXY *proxy,
                 CORBA::Environment &ACE_TRY_ENV)
{
  Write_Guard ace_mon (this->mutex_,
                       this->cond_,
                       this->pending_writes_,
                       this->writing_,
                       this->collection_);

  proxy->_incr_refcnt ();
  ace_mon.copy->collection.reconnected (proxy, ACE_TRY_ENV);
}

template<class PROXY, class COLLECTION, class ITERATOR, ACE_SYNCH_DECL> void
TAO_ESF_Copy_On_Write<PROXY,COLLECTION,ITERATOR,ACE_SYNCH_USE>::
    disconnected (PROXY *proxy,
                  CORBA::Environment &ACE_TRY_ENV)
{
  Write_Guard ace_mon (this->mutex_,
                       this->cond_,
                       this->pending_writes_,
                       this->writing_,
                       this->collection_);

  ace_mon.copy->collection.disconnected (proxy, ACE_TRY_ENV);
}

template<class PROXY, class COLLECTION, class ITERATOR, ACE_SYNCH_DECL> void
TAO_ESF_Copy_On_Write<PROXY,COLLECTION,ITERATOR,ACE_SYNCH_USE>::
    shutdown (CORBA::Environment &ACE_TRY_ENV)
{
  // We need to perform a copy to follow the protocol.
  Write_Guard ace_mon (this->mutex_,
                       this->cond_,
                       this->pending_writes_,
                       this->writing_,
                       this->collection_);

  ace_mon.copy->collection.shutdown (ACE_TRY_ENV);
}

template<class COLLECTION, class ITERATOR, ACE_SYNCH_DECL>
TAO_ESF_Copy_On_Write_Write_Guard<COLLECTION,ITERATOR,ACE_SYNCH_USE>::
    TAO_ESF_Copy_On_Write_Write_Guard (ACE_SYNCH_MUTEX_T &m,
                                       ACE_SYNCH_CONDITION_T &c,
                                       int &p,
                                       int &w,
                                       Collection*& cr)
      :  copy (0),
         mutex (m),
         cond (c),
         pending_writes (p),
         writing_flag (w),
         collection (cr)
{
  {
    ACE_GUARD (ACE_SYNCH_MUTEX_T, ace_mon, this->mutex);

    this->pending_writes++;

    while (this->writing_flag != 0)
      this->cond.wait ();

    this->writing_flag = 1;
  }

  // Copy outside the mutex, because it may take a long time.
  // Nobody can change it, because it is protected by the
  // writing_flag.

  // First initialize it (with the correct reference count
  ACE_NEW (this->copy, Collection);
  // Copy the contents
  this->copy->collection = this->collection->collection;

  // Increase the reference counts
  ITERATOR end = this->copy->collection.end ();
  for (ITERATOR i = this->copy->collection.begin (); i != end; ++i)
    {
      (*i)->_incr_refcnt ();
    }
}

template<class COLLECTION, class ITERATOR, ACE_SYNCH_DECL>
TAO_ESF_Copy_On_Write_Write_Guard<COLLECTION,ITERATOR,ACE_SYNCH_USE>::
    ~TAO_ESF_Copy_On_Write_Write_Guard (void)
{
  Collection *tmp = 0;
  {
    ACE_GUARD (ACE_SYNCH_MUTEX_T, ace_mon, this->mutex);

    tmp = this->collection;
    this->collection = this->copy;
    this->writing_flag = 0;
    this->pending_writes--;

    this->cond.signal ();
  }
  // Delete outside the mutex, because it may take a long time.
  tmp->_decr_refcnt ();
}

// ****************************************************************

#endif /* TAO_ESF_COPY_ON_WRITE_CPP */
