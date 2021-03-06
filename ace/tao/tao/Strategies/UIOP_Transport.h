// This may look like C, but it's really -*- C++ -*-

// ===================================================================
/**
 *  @file   UIOP_Transport.h
 *
 *  UIOP_Transport.h,v 1.11 2001/07/06 04:39:24 bala Exp
 *
 *  @author Originally by Fred Kuhns <fredk@cs.wustl.edu>
 *  @author Ossama Othman <ossama@ece.uci.edu>
 *  @author Modified by Balachandran Natarajan <bala@cs.wustl.edu>
 */
// ===================================================================

#ifndef TAO_UIOP_TRANSPORT_H
#define TAO_UIOP_TRANSPORT_H
#include "ace/pre.h"

#include "tao/Transport.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "strategies_export.h"

# if TAO_HAS_UIOP == 1
#include "ace/LSOCK_Acceptor.h"
#include "ace/Synch.h"
#include "ace/Svc_Handler.h"

// Forward decls.

class TAO_ORB_Core;
class TAO_UIOP_Connection_Handler;
class TAO_Pluggable_Messaging;

typedef ACE_Svc_Handler<ACE_LSOCK_STREAM, ACE_NULL_SYNCH>
        TAO_UIOP_SVC_HANDLER;

/**
 * @class TAO_UIOP_Transport
 *
 * @brief Specialization of the base TAO_Transport class to handle the
 *  UIOP protocol.
 *
 *
 *
 */

class TAO_Strategies_Export TAO_UIOP_Transport : public TAO_Transport
{
public:

  /// Constructor.
  TAO_UIOP_Transport (TAO_UIOP_Connection_Handler *handler,
                      TAO_ORB_Core *orb_core,
                      CORBA::Boolean flag);

  /// Default destructor.
  ~TAO_UIOP_Transport (void);

protected:
  /** @name Overridden Template Methods
   *
   * These are implementations of template methods declared by TAO_Transport.
   */
  //@{

  virtual ACE_Event_Handler *event_handler_i (void);

  virtual TAO_Pluggable_Messaging *messaging_object (void);

  /// Write the complete Message_Block chain to the connection.
  virtual ssize_t send_i (iovec *iov, int iovcnt,
                          size_t &bytes_transferred,
                          const ACE_Time_Value *timeout = 0);

  /// Read len bytes from into buf.
  virtual ssize_t recv_i (char *buf,
                          size_t len,
                          const ACE_Time_Value *s = 0);

  virtual int register_handler_i (void);

  /// Method to do whatever it needs to do when the connection
  /// handler is being closed and destroyed.
  virtual void transition_handler_state_i (void);

public:
  /// @@TODO: These methods IMHO should have more meaningful
  /// names. The names seem to indicate nothing.
  virtual int send_request (TAO_Stub *stub,
                            TAO_ORB_Core *orb_core,
                            TAO_OutputCDR &stream,
                            int twoway,
                            ACE_Time_Value *max_wait_time);

  virtual int send_message (TAO_OutputCDR &stream,
                            TAO_Stub *stub = 0,
                            int twoway = 1,
                            ACE_Time_Value *max_time_wait = 0);

  /// Initialising the messaging object
  virtual int messaging_init (CORBA::Octet major,
                              CORBA::Octet minor);

  //@}

private:

  /// The connection service handler used for accessing lower layer
  /// communication protocols.
  TAO_UIOP_Connection_Handler *connection_handler_;

  /// Our messaging object.
  TAO_Pluggable_Messaging *messaging_object_;
};



#if defined (__ACE_INLINE__)
#include "UIOP_Transport.i"
#endif /* __ACE_INLINE__ */

# endif  /* TAO_HAS_UIOP == 1 */

#include "ace/post.h"
#endif  /* TAO_UIOP_TRANSPORT_H */
