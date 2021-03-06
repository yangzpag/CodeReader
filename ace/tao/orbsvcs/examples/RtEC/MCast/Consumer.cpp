// Consumer.cpp,v 1.2 2000/04/25 17:38:13 coryan Exp

#include "Consumer.h"
#include "orbsvcs/RtecEventChannelAdminS.h"
#include "orbsvcs/Event_Service_Constants.h"

ACE_RCSID(EC_Examples, Consumer, "Consumer.cpp,v 1.2 2000/04/25 17:38:13 coryan Exp")

Consumer::Consumer (void)
  : event_count_ (0)
{
}

void
Consumer::connect (RtecEventChannelAdmin::ConsumerAdmin_ptr consumer_admin,
                   CORBA::Environment &ACE_TRY_ENV)
{
  this->proxy_ =
    consumer_admin->obtain_push_supplier (ACE_TRY_ENV);
  ACE_CHECK;

  RtecEventComm::PushConsumer_var me =
    this->_this (ACE_TRY_ENV);
  ACE_CHECK;

  // Simple subscription, but usually the helper classes in
  // $TAO_ROOT/orbsvcs/Event_Utils.h are a better way to do this.
  RtecEventChannelAdmin::ConsumerQOS qos;
  qos.is_gateway = 0;

  qos.dependencies.length (2);
  RtecEventComm::EventHeader& h0 =
    qos.dependencies[0].event.header;
  h0.type   = ACE_ES_DISJUNCTION_DESIGNATOR;
  h0.source = 1; // The disjunction has one element

  RtecEventComm::EventHeader& h1 =
    qos.dependencies[1].event.header;
  h1.type   = ACE_ES_EVENT_UNDEFINED;  // first free event type
  h1.source = ACE_ES_EVENT_SOURCE_ANY; // Any source is OK

  this->proxy_->connect_push_consumer (me.in (), qos,
                                       ACE_TRY_ENV);
  ACE_CHECK;
}

void
Consumer::disconnect (CORBA::Environment &ACE_TRY_ENV)
{
  ACE_TRY
    {
      // Disconnect from the proxy
      this->proxy_->disconnect_push_supplier (ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      // Ignore exceptions
    }
  ACE_ENDTRY;
  this->proxy_ = RtecEventChannelAdmin::ProxyPushSupplier::_nil ();

  // Deactivate this object
  PortableServer::POA_var poa =
    this->_default_POA (ACE_TRY_ENV);
  ACE_CHECK;
  // Get the Object Id used for the servant..
  PortableServer::ObjectId_var oid =
    poa->servant_to_id (this, ACE_TRY_ENV);
  ACE_CHECK;
  // Deactivate the object
  poa->deactivate_object (oid.in (), ACE_TRY_ENV);
  ACE_CHECK;
}

void
Consumer::push (const RtecEventComm::EventSet& events,
                CORBA::Environment &)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  if (events.length () == 0)
    {
      ACE_DEBUG ((LM_DEBUG,
                  "Consumer (%P|%t) no events\n"));
      return;
    }

  this->event_count_ += events.length ();
  if (this->event_count_ % 100 == 0)
    {
      ACE_DEBUG ((LM_DEBUG,
                  "Consumer (%P|%t): %d events received\n",
                  this->event_count_));
    }
}

void
Consumer::disconnect_push_consumer (CORBA::Environment &)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
}

// ****************************************************************

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)
#elif defined(ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)
#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */
