/* -*- C++ -*- */

//=============================================================================
/**
 *  @file    SV_Message_Queue.h
 *
 *  SV_Message_Queue.h,v 4.13 2001/06/25 05:05:33 schmidt Exp
 *
 *  @author Douglas C. Schmidt <schmidt@cs.wustl.edu>
 */
//=============================================================================

#ifndef ACE_SV_MESSAGE_QUEUE_H
#define ACE_SV_MESSAGE_QUEUE_H
#include "ace/pre.h"

#include "ace/ACE.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/SV_Message.h"

/**
 * @class ACE_SV_Message_Queue
 *
 * @brief Defines the header file for the C++ wrapper for System V IPC
 * message queues.
 */
class ACE_Export ACE_SV_Message_Queue
{
public:
  // = Useful symbolic constants.
  enum
  {
    ACE_CREATE = IPC_CREAT,
    ACE_OPEN   = 0,
    ACE_NOWAIT = IPC_NOWAIT
  };

  // = Initialization and termination methods.
   /// Open a message queue using the <external_id>.
  ACE_SV_Message_Queue (void);
  ACE_SV_Message_Queue (key_t external_id,
                        int create = ACE_SV_Message_Queue::ACE_OPEN,
                        int perms = ACE_DEFAULT_FILE_PERMS);
  int open (key_t external_id,
            int create = ACE_SV_Message_Queue::ACE_OPEN,
            int perms = ACE_DEFAULT_FILE_PERMS);

  ~ACE_SV_Message_Queue (void);

  /// Close down this instance of the message queue without removing it
  /// from the system.
  int close (void);

  /// Close down and remove the message queue from the system.
  int remove (void);


  // = Message transfer methods.
  int recv (ACE_SV_Message &mb,
            int length,
            long mtype = 0,
            int mflags = 0);

  int send (const ACE_SV_Message &mb,
            int length,
            int mflags = 0);

  /// Access the underlying control operations.
  int control (int option, void *arg = 0);

  // = Get/set the underly internal id.
  int get_id (void) const;
  void set_id (int);

  /// Dump the state of an object.
  void dump (void) const;

  /// Declare the dynamic allocation hooks.
  ACE_ALLOC_HOOK_DECLARE;

protected:
  /// Returned from the underlying <msgget> system call.
  int internal_id_;
};

#if !defined (ACE_LACKS_INLINE_FUNCTIONS)
#include "ace/SV_Message_Queue.i"
#endif

#include "ace/post.h"
#endif /* ACE_SV_MESSAGE_QUEUE_H */
