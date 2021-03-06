/* -*- C++ -*- */
// Receiver_i.h,v 1.5 1999/06/28 22:35:15 pradeep Exp

// ===========================================================
//
// = LIBRARY
//    TAO/tests/Simple/chat
//
// = FILENAME
//    Receiver_i.h
//
// = DESCRIPTION
//    Defines the implementation header for the Receiver interface.
//
// = AUTHOR
//    Pradeep Gore <pradeep@cs.wustl.edu>
//
// ===========================================================

#ifndef RECEIVER_I_H
#define RECEIVER_I_H

#include "ReceiverS.h"

class Receiver_i : public POA_Receiver
{
  // = TITLE
  //    Receiver object implementation
  //
  // = DESCRIPTION
  //    This class has methods that are called by the chat server.
public:
  // = Initialization and termination methods.
  Receiver_i (void);
  // Constructor.

  ~Receiver_i (void);
  // Destructor.

  virtual void message (const char *msg,
                        CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((
      CORBA::SystemException
    ));
  // Receives a message string.

  virtual void shutdown (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((
      CORBA::SystemException
    ));
  // Called when the chat server is going away.  The client
  // implementation should shutdown the chat client in response to
  // this.

  void orb (CORBA::ORB_ptr o);
  // Set the ORB pointer.

private:
  CORBA::ORB_var orb_;
  // ORB pointer.
};

#endif /* RECEIVER_I_H  */
