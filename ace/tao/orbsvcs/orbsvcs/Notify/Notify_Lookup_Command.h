/* -*- C++ -*- */
// Notify_Lookup_Command.h,v 1.2 2000/08/30 01:29:00 pradeep Exp
//
// ============================================================================
//
// = LIBRARY
//   ORBSVCS Notification
//
// = FILENAME
//   Notify_Lookup_Command.h
//
// = DESCRIPTION
//   Command object for looking up subscriptions for a given event.
//
// = AUTHOR
//   Pradeep Gore <pradeep@cs.wustl.edu>
//
// ============================================================================

#ifndef TAO_NOTIFY_LOOKUP_COMMAND_H
#define TAO_NOTIFY_LOOKUP_COMMAND_H

#include "ace/pre.h"
#include "orbsvcs/ESF/ESF_Worker.h"
#include "Notify_Command.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

class TAO_Notify_Event;
class TAO_Notify_EventListener;
class TAO_Notify_Event_Map;

class TAO_Notify_Export TAO_Notify_Lookup_Command : public TAO_Notify_Command, public TAO_ESF_Worker<TAO_Notify_EventListener>
{
  // = TITLE
  //   TAO_Notify_Lookup_Command
  //
  // = DESCRIPTION
  //   Command object for event subscription lookup in the event map.
  //
 public:
  // = Initialization and termination code
  TAO_Notify_Lookup_Command (TAO_Notify_Event_Processor* event_processor, TAO_Notify_Event* event, TAO_Notify_Event_Map* event_map);

  ~TAO_Notify_Lookup_Command ();

  virtual int execute (CORBA::Environment&);
  // Command callback

  // = TAO_ESF_Worker method
  void work (TAO_Notify_EventListener* listener, CORBA::Environment &ACE_TRY_ENV);
 protected:
  // = Data member
  TAO_Notify_Event_Map* event_map_;
  // The event map to lookup in.
};

#include "ace/post.h"
#endif /* TAO_NOTIFY_LOOKUP_COMMAND_H */
