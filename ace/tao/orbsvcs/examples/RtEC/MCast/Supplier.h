/* -*- C++ -*- */
// Supplier.h,v 1.1 2000/04/24 22:28:54 coryan Exp
//
// ============================================================================
//
// = LIBRARY
//   ORBSVCS Real-time Event Channel examples
//
// = FILENAME
//   Supplier
//
// = AUTHOR
//   Carlos O'Ryan (coryan@cs.wustl.edu)
//
// ============================================================================

#ifndef SUPPLIER_H
#define SUPPLIER_H

#include "orbsvcs/RtecEventCommS.h"
#include "orbsvcs/RtecEventChannelAdminC.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

class Supplier : public POA_RtecEventComm::PushSupplier
{
  // = TITLE
  //   Simple supplier object
  //
  // = DESCRIPTION
  //   This class is a supplier of events.
  //   It simply publishes one event type, when the perform_push()
  //   method is invoked it pushes the event through the event service
  //
public:
  Supplier (void);
  // Constructor

  void connect (RtecEventChannelAdmin::SupplierAdmin_ptr supplier_admin,
                CORBA::Environment &ACE_TRY_ENV);
  // Connect to the event channel

  void disconnect (CORBA::Environment &ACE_TRY_ENV);
  // Disconnect from the event channel

  void perform_push (CORBA::Environment &ACE_TRY_ENV);
  // Push a single event

  // = The RtecEventComm::PushSupplier methods

  virtual void disconnect_push_supplier (CORBA::Environment &)
    ACE_THROW_SPEC ((CORBA::SystemException));
  // The skeleton methods.

private:
  RtecEventChannelAdmin::ProxyPushConsumer_var proxy_;
  // The proxy
};

#endif /* SUPPLIER_H */
