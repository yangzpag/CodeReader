/* -*- C++ -*- */
// Notify_StructuredProxyPushConsumer_i.h,v 1.11 2000/07/19 02:40:06 pradeep Exp
// ==========================================================================
//
// = LIBRARY
//   orbsvcs
//
// = FILENAME
//   TAO_Notify_StructuredProxyPushConsumer_i.h
//
// = DESCRIPTION
//   Implements the CosNotifyChannelAdmin::StructuredProxyPushConsumer
//   interface.
//
// = AUTHOR
//    Pradeep Gore <pradeep@cs.wustl.edu>
//
// ==========================================================================

#ifndef TAO_NOTIFY_STRUCTUREDPROXYPUSHCONSUMER_I_H
#define TAO_NOTIFY_STRUCTUREDPROXYPUSHCONSUMER_I_H

#include "ace/pre.h"
#include "orbsvcs/CosNotifyChannelAdminS.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "Notify_ProxyConsumer_T.h"
#include "notify_export.h"

class TAO_Notify_SupplierAdmin_i;

#if defined(_MSC_VER)
#if (_MSC_VER >= 1200)
#pragma warning(push)
#endif /* _MSC_VER >= 1200 */
#pragma warning(disable:4250)
#endif /* _MSC_VER */

class TAO_Notify_Export TAO_Notify_StructuredProxyPushConsumer_i : public TAO_Notify_ProxyConsumer <POA_CosNotifyChannelAdmin::StructuredProxyPushConsumer>
{
  // = TITLE
  //   TAO_Notify_StructuredProxyPushConsumer_i
  //
  // = DESCRIPTION
  //   Implements CosNotifyChannelAdmin::StructuredProxyPushConsumer
  //

public:
  TAO_Notify_StructuredProxyPushConsumer_i (TAO_Notify_SupplierAdmin_i* supplier_admin);
  // Constructor

  virtual ~TAO_Notify_StructuredProxyPushConsumer_i (void);
  // Destructor

  // = interface methods
  virtual void connect_structured_push_supplier (
    CosNotifyComm::StructuredPushSupplier_ptr push_supplier,
    CORBA::Environment &ACE_TRY_ENV
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException,
    CosEventChannelAdmin::AlreadyConnected
  ));

virtual void push_structured_event (
    const CosNotification::StructuredEvent & notification,
    CORBA::Environment &ACE_TRY_ENV
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException,
    CosEventComm::Disconnected
  ));

  virtual void disconnect_structured_push_consumer (
    CORBA::Environment &ACE_TRY_ENV
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ));

protected:
  // = Helper methods
 virtual void dispatch_update_i (CosNotification::EventTypeSeq added, CosNotification::EventTypeSeq removed, CORBA::Environment &ACE_TRY_ENV);
  // dispatch updates to the supplier.

  // = Data members
  CosNotifyComm::StructuredPushSupplier_var push_supplier_;
  // The supplier that we're connected to.

private:
  typedef TAO_Notify_ProxyConsumer <POA_CosNotifyChannelAdmin::StructuredProxyPushConsumer>
  proxy_inherited;
};

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma warning(pop)
#endif /* _MSC_VER */

#include "ace/post.h"
#endif /* TAO_NOTIFY_STRUCTUREDPROXYPUSHCONSUMER_I_H */
