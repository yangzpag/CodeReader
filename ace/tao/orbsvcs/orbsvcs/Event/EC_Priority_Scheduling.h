/* -*- C++ -*- */
/**
 *  @file   EC_Priority_Scheduling.h
 *
 *  EC_Priority_Scheduling.h,v 1.7 2000/10/31 03:11:12 coryan Exp
 *
 *  @author Carlos O'Ryan (coryan@cs.wustl.edu)
 *
 * Based on previous work by Tim Harrison (harrison@cs.wustl.edu) and
 * other members of the DOC group. More details can be found in:
 *
 * http://doc.ece.uci.edu/~coryan/EC/index.html
 */

#ifndef TAO_EC_PRIORITY_SCHEDULING_H
#define TAO_EC_PRIORITY_SCHEDULING_H
#include "ace/pre.h"

#include "EC_Scheduling_Strategy.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "orbsvcs/RtecSchedulerC.h"
#include "sched_event_export.h"

/**
 * @class TAO_EC_Priority_Scheduling
 *
 * @brief A scheduling strategy that uses TAO's real-time scheduler
 *
 * This implementation of the Scheduling_Strategy uses TAO's
 * real-time scheduler.
 */
class TAO_RTSchedEvent_Export TAO_EC_Priority_Scheduling : public TAO_EC_Scheduling_Strategy
{
public:
  /// Constructor.
  TAO_EC_Priority_Scheduling (RtecScheduler::Scheduler_ptr scheduler);

  /// Destructor
  virtual ~TAO_EC_Priority_Scheduling (void);

  /// Add all the dependencies between <supplier> and <consumer>
  virtual void add_proxy_supplier_dependencies (
      TAO_EC_ProxyPushSupplier *supplier,
      TAO_EC_ProxyPushConsumer *consumer,
      CORBA::Environment &ACE_TRY_ENV);

  /// Initializes <qos_info> based on the QoS information for
  /// <consumer> and the event header.
  virtual void init_event_qos (
      const RtecEventComm::EventHeader& header,
      TAO_EC_ProxyPushConsumer *consumer,
      TAO_EC_QOS_Info& qos_info,
      CORBA::Environment &ACE_TRY_ENV);

private:
  ACE_UNIMPLEMENTED_FUNC (TAO_EC_Priority_Scheduling
                              (const TAO_EC_Priority_Scheduling&))
  ACE_UNIMPLEMENTED_FUNC (TAO_EC_Priority_Scheduling& operator=
                              (const TAO_EC_Priority_Scheduling&))

  /// Initialize our RT_Info handle and dependencies
  void init_rt_info (CORBA::Environment& env);

private:
  /// The scheduler we are going to use
  RtecScheduler::Scheduler_var scheduler_;
};

#if defined (__ACE_INLINE__)
#include "EC_Priority_Scheduling.i"
#endif /* __ACE_INLINE__ */

#include "ace/post.h"
#endif /* TAO_EC_PRIORITY_SCHEDULING_H */
