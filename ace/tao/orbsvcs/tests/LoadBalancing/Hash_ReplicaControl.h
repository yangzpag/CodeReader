// -*- C++ -*-

// Hash_ReplicaControl.h,v 1.2 2000/06/08 22:14:05 othman Exp

#ifndef TAO_HASH_REPLICACONTROL_H
#define TAO_HASH_REPLICACONTROL_H

#include "Hash_Replica_i.h"
#include "orbsvcs/LoadBalancingS.h"

class Hash_ReplicaControl;

// @@ Ossama: notice how i integrated the reactor into the control
// loop, to periodically send the load...
class Timeout_Adapter : public ACE_Event_Handler
{
public:
  Timeout_Adapter (Hash_ReplicaControl *adaptee);

  // Receive the timeout event
  virtual int handle_timeout (const ACE_Time_Value &current_time,
                              const void *arg);

private:
  Hash_ReplicaControl *adaptee_;
};

// @@ Ossama: remember that we want to implement load balancing using
// interceptors.
class Hash_ReplicaControl : public virtual POA_LoadBalancing::ReplicaControl
{
public:
  Hash_ReplicaControl (void);
  // Constructor.

  void init (CORBA::ORB_ptr the_orb,
             LoadBalancing::LoadBalancer_ptr balancer,
             CORBA::Environment &ACE_TRY_ENV);

  int handle_timeout (const ACE_Time_Value &current_time,
                      const void *arg);
  // Handle a timeout event

  void request_received (void);
  // A request has been received

  void request_rejected (CORBA::Environment &ACE_TRY_ENV);
  // A request has been rejected, take appropriate action

  virtual void high_load_advisory (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

  virtual void nominal_load_advisory (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

  CORBA::Object_ptr replica (void);
  // Return a reference to the replica being load balanced.

private:
  Timeout_Adapter adapter_;
  // Adapter

  Hash_Replica_Impl replica_;
  // Replica being load balanced.

  LoadBalancing::ReplicaProxy_var proxy_;
  // The proxy

  CORBA::Object_var group_;
  // The group identity

  ACE_Time_Value interval_start_;
  // The start of the current measurement interval

  CORBA::ULong request_count_;
  // The number of requests in the current interval

  CORBA::Float current_load_;
  // The current load
};

#endif  /* TAO_HASH_REPLICACONTROL_H */
