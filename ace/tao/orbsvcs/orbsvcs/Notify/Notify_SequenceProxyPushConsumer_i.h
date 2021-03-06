/* -*- C++ -*- */
// Notify_SequenceProxyPushConsumer_i.h,v 1.6 2000/07/19 02:40:06 pradeep Exp
// ==========================================================================
//
// = LIBRARY
//   orbsvcs
//
// = FILENAME
//   TAO_Notify_SequenceProxyPushConsumer_i.h
//
// = DESCRIPTION
//   Implements the CosNotifyChannelAdmin::SequenceProxyPushConsumer
//   interface.
//
// = AUTHOR
//    Pradeep Gore <pradeep@cs.wustl.edu>
//
// ==========================================================================

#ifndef TAO_NOTIFY_SEQUENCEPROXYPUSHCONSUMER_I_H
#define TAO_NOTIFY_SEQUENCEPROXYPUSHCONSUMER_I_H
#include "ace/pre.h"

#include "Notify_ProxyConsumer_T.h"
#include "orbsvcs/CosNotifyChannelAdminS.h"

class TAO_Notify_SupplierAdmin_i;

#if defined(_MSC_VER)
#if (_MSC_VER >= 1200)
#pragma warning(push)
#endif /* _MSC_VER >= 1200 */
#pragma warning(disable:4250)
#endif /* _MSC_VER */

class TAO_Notify_Export TAO_Notify_SequenceProxyPushConsumer_i : public TAO_Notify_ProxyConsumer <POA_CosNotifyChannelAdmin::SequenceProxyPushConsumer>
{
  // = TITLE
  //   TAO_Notify_SequenceProxyPushConsumer_i
  //
  // = DESCRIPTION
  //   Implements CosNotifyChannelAdmin::SequenceProxyPushConsumer
  //

public:
  TAO_Notify_SequenceProxyPushConsumer_i (TAO_Notify_SupplierAdmin_i* supplier_admin);
  // Constructor

  virtual ~TAO_Notify_SequenceProxyPushConsumer_i (void);
  // Destructor

  // = interface methods
  virtual void connect_sequence_push_supplier (
    CosNotifyComm::SequencePushSupplier_ptr push_supplier,
    CORBA::Environment &ACE_TRY_ENV
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException,
    CosEventChannelAdmin::AlreadyConnected
  ));

  virtual void push_structured_events (
    const CosNotification::EventBatch & notifications,
    CORBA::Environment &ACE_TRY_ENV
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException,
    CosEventComm::Disconnected
  ));

  virtual void disconnect_sequence_push_consumer (
    CORBA::Environment &ACE_TRY_ENV
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ));

protected:
  // = Helper methods
 virtual void dispatch_update_i (CosNotification::EventTypeSeq added, CosNotification::EventTypeSeq removed, CORBA::Environment &ACE_TRY_ENV);
  // Sends updates to the supplier.

  // = Data members
  CosNotifyComm::SequencePushSupplier_ptr push_supplier_;
  // The supplier that we're connected to.

private:
  typedef TAO_Notify_ProxyConsumer <POA_CosNotifyChannelAdmin::SequenceProxyPushConsumer> proxy_inherited;
};

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma warning(pop)
#endif /* _MSC_VER */

#include "ace/post.h"
#endif /* TAO_NOTIFY_SEQUENCEPROXYPUSHCONSUMER_I_H */
