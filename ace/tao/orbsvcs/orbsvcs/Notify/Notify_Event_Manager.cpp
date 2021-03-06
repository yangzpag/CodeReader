// Notify_Event_Manager.cpp,v 1.10 2001/02/26 07:48:09 pradeep Exp

#include "orbsvcs/ESF/ESF_Proxy_Collection.h"
#include "Notify_Event_Manager.h"
#include "Notify_Factory.h"
#include "Notify_Worker_Task.h"
#include "Notify_Event_Manager_Objects_Factory.h"
#include "Notify_Update_Dispatch_Command.h"
#include "Notify_AdminProperties.h"

#if ! defined (__ACE_INLINE__)
#include "Notify_Event_Manager.i"
#endif /* __ACE_INLINE__ */

ACE_RCSID(Notify, Notify_Event_Manager, "Notify_Event_Manager.cpp,v 1.10 2001/02/26 07:48:09 pradeep Exp")

TAO_Notify_Event_Manager::TAO_Notify_Event_Manager (TAO_Notify_EventChannel_i* event_channel, TAO_Notify_EMO_Factory* emo_factory)
  :event_channel_ (event_channel),
   event_map_ (0),
   event_processor_ (0),
   updates_dispatching_task_ (0),
   emo_factory_ (emo_factory),
   admin_properties_ (0)
{
}

TAO_Notify_Event_Manager::~TAO_Notify_Event_Manager ()
{
  delete this->event_map_;
  delete this->event_processor_;
  delete this->lock_;
  delete this->admin_properties_;

  emo_factory_->destroy_updates_task (this->updates_dispatching_task_);
}

void
TAO_Notify_Event_Manager::init (CORBA::Environment &ACE_TRY_ENV)
{
  ACE_NEW_THROW_EX (this->lock_,
                    ACE_Lock_Adapter<TAO_SYNCH_MUTEX> (),
                    CORBA::NO_MEMORY ());

  // Create members.

  this->admin_properties_ = new TAO_Notify_AdminProperties ();

  this->event_map_ =
    this->emo_factory_->create_event_map (ACE_TRY_ENV);
  ACE_CHECK;

  this->event_processor_ =
    this->emo_factory_->create_event_processor (this, ACE_TRY_ENV);
  ACE_CHECK;

  this->updates_dispatching_task_ =
    this->emo_factory_->create_updates_task (ACE_TRY_ENV);
  ACE_CHECK;

  // Init the objects
  this->event_map_->init (ACE_TRY_ENV);
  ACE_CHECK;

  this->event_processor_->init (ACE_TRY_ENV);
  ACE_CHECK;

  // @@ check return value
  this->updates_dispatching_task_->init_task (this->admin_properties_);
  // The updates task doesn't really use admin properties but this makes it future proof.
}

void
TAO_Notify_Event_Manager::shutdown (CORBA::Environment &ACE_TRY_ENV)
{
  ACE_GUARD_THROW_EX (ACE_Lock, ace_mon, *this->lock_,
                      CORBA::INTERNAL ());
  ACE_CHECK;

  this->event_processor_->shutdown (ACE_TRY_ENV);
  ACE_CHECK;

  this->event_map_->shutdown (ACE_TRY_ENV);
  ACE_CHECK;

  this->updates_dispatching_task_->shutdown (ACE_TRY_ENV);
}

void
TAO_Notify_Event_Manager::subscribe_for_events (TAO_Notify_EventListener* event_listener, const CosNotification::EventTypeSeq & added, const CosNotification::EventTypeSeq & removed, CORBA::Environment &ACE_TRY_ENV)
{
  TAO_Notify_EventType_List added_update, removed_update;

  this->event_map_->subscribe_for_events (event_listener, added_update,
                                         added, ACE_TRY_ENV);
  ACE_CHECK;

  this->event_map_->unsubscribe_from_events (event_listener, removed_update,
                                              removed, ACE_TRY_ENV);
  ACE_CHECK;

  // if either of the lists are *not* empty, send updates
  if (added_update.is_empty () == 0 || removed_update.is_empty () == 0)
    this->dispatch_updates_i (this->event_map_->subscription_change_listeners (),
                              added_update, removed_update, ACE_TRY_ENV);
}

void
TAO_Notify_Event_Manager::update_publication_list (const CosNotification::EventTypeSeq & added, const CosNotification::EventTypeSeq & removed, CORBA::Environment &ACE_TRY_ENV)
{
  TAO_Notify_EventType_List added_list;
  TAO_Notify_EventType_List removed_list;

  this->event_map_->update_publication_list (added, removed,
                                            added_list, removed_list, ACE_TRY_ENV);
  ACE_CHECK;

  // if either of the lists are *not* empty, send updates
  if (added_list.is_empty () == 0 || removed_list.is_empty () == 0)
    this->dispatch_updates_i (this->event_map_->publication_change_listeners (),
                              added_list, removed_list, ACE_TRY_ENV);
}

void
TAO_Notify_Event_Manager::dispatch_updates_i (TAO_Notify_UpdateListener_List* update_listener_list, TAO_Notify_EventType_List& added, TAO_Notify_EventType_List& removed, CORBA::Environment &ACE_TRY_ENV)
{
  ACE_GUARD_THROW_EX (ACE_Lock, ace_mon, *this->lock_,
                      CORBA::INTERNAL ());

  TAO_Notify_Update_Worker update_worker (this->updates_dispatching_task_,
                                          added, removed);

  update_listener_list->for_each (&update_worker, ACE_TRY_ENV);
}

/********************************************************************/

TAO_Notify_Update_Worker::TAO_Notify_Update_Worker (TAO_Notify_Worker_Task * updates_dispatching_task, TAO_Notify_EventType_List& added, TAO_Notify_EventType_List& removed)
  : added_ (added),
    removed_ (removed),
    updates_dispatching_task_ (updates_dispatching_task)
{
}

void
TAO_Notify_Update_Worker::work (TAO_Notify_UpdateListener* listener, CORBA::Environment &ACE_TRY_ENV)
{
  TAO_Notify_Update_Dispatch_Command* mb =
    new TAO_Notify_Update_Dispatch_Command (listener, this->added_,
                                            this->removed_);

  this->updates_dispatching_task_->process_event (mb, ACE_TRY_ENV);
}

/********************************************************************/
#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)

template class ACE_Hash_Map_Entry<TAO_Notify_EventType, TAO_Notify_EventListener_List *>;
template class ACE_Hash_Map_Manager<TAO_Notify_EventType, TAO_Notify_EventListener_List *,TAO_SYNCH_MUTEX>;
template class ACE_Hash_Map_Manager_Ex<TAO_Notify_EventType, TAO_Notify_EventListener_List *,ACE_Hash<TAO_Notify_EventType>, ACE_Equal_To<TAO_Notify_EventType>,TAO_SYNCH_MUTEX>;
template class ACE_Hash_Map_Iterator<TAO_Notify_EventType, TAO_Notify_EventListener_List *,TAO_SYNCH_MUTEX>;
template class ACE_Hash_Map_Iterator_Ex<TAO_Notify_EventType, TAO_Notify_EventListener_List *,ACE_Hash<TAO_Notify_EventType>, ACE_Equal_To<TAO_Notify_EventType>,TAO_SYNCH_MUTEX>;
template class ACE_Hash_Map_Iterator_Base_Ex<TAO_Notify_EventType, TAO_Notify_EventListener_List *,ACE_Hash<TAO_Notify_EventType>, ACE_Equal_To<TAO_Notify_EventType>,TAO_SYNCH_MUTEX>;
template class ACE_Hash_Map_Reverse_Iterator<TAO_Notify_EventType, TAO_Notify_EventListener_List *,TAO_SYNCH_MUTEX>;
template class ACE_Hash_Map_Reverse_Iterator_Ex<TAO_Notify_EventType, TAO_Notify_EventListener_List *,ACE_Hash<TAO_Notify_EventType>, ACE_Equal_To<TAO_Notify_EventType>,TAO_SYNCH_MUTEX>;
template class ACE_Hash<TAO_Notify_EventType>;
template class ACE_Equal_To<TAO_Notify_EventType>;
#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)

#pragma instantiate ACE_Hash_Map_Entry<TAO_Notify_EventType, TAO_Notify_EventListener_List *>
#pragma instantiate ACE_Hash_Map_Manager<TAO_Notify_EventType, TAO_Notify_EventListener_List *,TAO_SYNCH_MUTEX>
#pragma instantiate ACE_Hash_Map_Manager_Ex<TAO_Notify_EventType, TAO_Notify_EventListener_List *,ACE_Hash<TAO_Notify_EventType>, ACE_Equal_To<TAO_Notify_EventType>,TAO_SYNCH_MUTEX>
#pragma instantiate ACE_Hash_Map_Iterator<TAO_Notify_EventType, TAO_Notify_EventListener_List *,TAO_SYNCH_MUTEX>
#pragma instantiate ACE_Hash_Map_Iterator_Ex<TAO_Notify_EventType, TAO_Notify_EventListener_List *,ACE_Hash<TAO_Notify_EventType>, ACE_Equal_To<TAO_Notify_EventType>,TAO_SYNCH_MUTEX>
#pragma instantiate ACE_Hash_Map_Iterator_Base_Ex<TAO_Notify_EventType, TAO_Notify_EventListener_List *,ACE_Hash<TAO_Notify_EventType>, ACE_Equal_To<TAO_Notify_EventType>,TAO_SYNCH_MUTEX>
#pragma instantiate ACE_Hash_Map_Reverse_Iterator<TAO_Notify_EventType, TAO_Notify_EventListener_List *,TAO_SYNCH_MUTEX>
#pragma instantiate ACE_Hash_Map_Reverse_Iterator_Ex<TAO_Notify_EventType, TAO_Notify_EventListener_List *,ACE_Hash<TAO_Notify_EventType>, ACE_Equal_To<TAO_Notify_EventType>,TAO_SYNCH_MUTEX>
#pragma instantiate template ACE_Hash<TAO_Notify_EventType>
#pragma instantiate template ACE_Equal_To<TAO_Notify_EventType>
#endif /*ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */
