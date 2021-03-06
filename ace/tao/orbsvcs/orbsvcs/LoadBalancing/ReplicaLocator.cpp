// -*- C++ -*-

// ReplicaLocator.cpp,v 1.7 2001/01/12 22:54:46 othman Exp

#include "ReplicaLocator.h"
#include "LoadBalancer_i.h"

ACE_RCSID(orbsvcs, ReplicaLocator, "ReplicaLocator.cpp,v 1.7 2001/01/12 22:54:46 othman Exp")

TAO_LB_ReplicaLocator::TAO_LB_ReplicaLocator (TAO_LB_LoadBalancer *lb)
  : load_balancer_ (lb) // This pointer shouldn't be zero!
{
  // Nothing else
}

PortableServer::Servant
TAO_LB_ReplicaLocator::preinvoke (
      const PortableServer::ObjectId & /* oid */,
      PortableServer::POA_ptr /* adapter */,
      const char * /* operation */,
      PortableServer::ServantLocator::Cookie & /* the_cookie */
      TAO_ENV_ARG_DECL)
  ACE_THROW_SPEC ((CORBA::SystemException,
                   PortableServer::ForwardRequest))
{
  TAO_ENV_ARG_DEFN;

  if (this->load_balancer_ == 0)
    ACE_THROW_RETURN (CORBA::INTERNAL (), 0);

  CORBA::Object_var replica =
    this->load_balancer_->replica (ACE_TRY_ENV);
  ACE_CHECK_RETURN (0);

  // Throw a forward exception to force the client to redirect its
  // requests to the Replica chosen by the LoadBalancer.
  ACE_THROW_RETURN (PortableServer::ForwardRequest (
                      replica.in ()),
                    0);
}

void
TAO_LB_ReplicaLocator::postinvoke (
    const PortableServer::ObjectId & /* oid */,
    PortableServer::POA_ptr /* adapter */,
    const char * /* operation */,
    PortableServer::ServantLocator::Cookie /* the_cookie */,
    PortableServer::Servant /* the_servant */
    TAO_ENV_ARG_DECL_NOT_USED)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  // No-op
}
