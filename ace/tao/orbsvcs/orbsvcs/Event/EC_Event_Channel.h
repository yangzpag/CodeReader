/* -*- C++ -*- */
/**
 *  @file   EC_Event_Channel.h
 *
 *  EC_Event_Channel.h,v 1.34 2000/10/31 03:11:12 coryan Exp
 *
 *  @author Carlos O'Ryan (coryan@cs.wustl.edu)
 *
 * Based on previous work by Tim Harrison (harrison@cs.wustl.edu) and
 * other members of the DOC group. More details can be found in:
 *
 * http://doc.ece.uci.edu/~coryan/EC/index.html
 */

#ifndef TAO_EC_EVENT_CHANNEL_H
#define TAO_EC_EVENT_CHANNEL_H
#include "ace/pre.h"

#include "EC_Factory.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "EC_Defaults.h"
#include "orbsvcs/RtecEventChannelAdminS.h"

/**
 * @class TAO_EC_Event_Channel_Attributes
 *
 * @brief Defines the construction time attributes for the Event
 * Channel.
 *
 * The event channel implementation is controlled by two
 * mechanisms:
 * The EC_Factory that provides the strategies for the EC
 * implementation.
 * The EC attributes that define constants and values required
 * by the EC construction.
 * This class encapsulates those constants and values, providing
 * an easy mechanism to extend the attributes without requiring
 * changes in the EC constructor.
 */
class TAO_RTEvent_Export TAO_EC_Event_Channel_Attributes
{
public:
  /**
   * The basic constructor.
   * The attributes listed as arguments are *required* by the EC, and
   * no appropiate defaults are available for them.
   */
  TAO_EC_Event_Channel_Attributes (PortableServer::POA_ptr supplier_poa,
                                   PortableServer::POA_ptr consumer_poa);

  // Most fields are public, there is no need to protect them, in fact
  // the user should be able to set any values she wants.

  /// Can consumers or suppliers invoke connect_push_* multiple times?
  int consumer_reconnect;
  int supplier_reconnect;

  /**
   * It not zero the event channel will send disconnect callbacks when
   * a disconnect method is called on a Proxy.  In other words, if a
   * consumer calls disconnect_push_supplier() on its proxy the EC
   * will invoke disconnect_push_consumer() on the consumer.  A
   * similar thing is done for suppliers.
   * It is a matter of debate what the spec requires for the regular
   * event service.
   */
  int disconnect_callbacks;

  /// Flags for the Consumer Admin
  int busy_hwm;
  int max_write_delay;

  /**
   * The scheduling service that we will use with this event channel.
   * Notice that this is optional and will only take effect if the EC
   * is configured with the right filtering strategies.
   */
  CORBA::Object_ptr scheduler;

private:
  /// Only the EC can read the private fields.
  friend class TAO_EC_Event_Channel;

  /// The POAs
  PortableServer::POA_ptr supplier_poa;
  PortableServer::POA_ptr consumer_poa;
};

/**
 * @class TAO_EC_Event_Channel
 *
 * @brief The RtecEventChannelAdmin::EventChannel implementation.
 *
 * This class is the Mediator between all the classes in the EC
 * implementation, its main task is to redirect the messages to
 * the right components, to hold and manage the lifetime of the
 * long lived objects (Timer_Module, SupplierAdmin,
 * ConsumerAdmin and Dispatching) and to provide a simpler
 * interface to the EC_Factory.
 */
class TAO_RTEvent_Export TAO_EC_Event_Channel : public POA_RtecEventChannelAdmin::EventChannel
{
public:
  /**
   * constructor
   * If <own_factory> is not 0 it assumes ownership of the factory.
   * If the factory is <nil> it uses the Service_Configurator to load
   * the Factory, if not found it uses TAO_EC_Default_Resource_Factory
   */
  TAO_EC_Event_Channel (const TAO_EC_Event_Channel_Attributes& attributes,
                        TAO_EC_Factory* factory = 0,
                        int own_factory = 0);

  /// destructor
  virtual ~TAO_EC_Event_Channel (void);

  /// Start the internal threads (if any), etc.
  /// After this call the EC can be used.
  virtual void activate (CORBA::Environment &env = TAO_default_environment ());

  /// Shutdown any internal threads, cleanup all the internal
  /// structures, flush all the messages, etc.
  virtual void shutdown (CORBA::Environment &env = TAO_default_environment ());

  /// Access the dispatching module....
  TAO_EC_Dispatching* dispatching (void) const;

  /// Access the filter builder....
  TAO_EC_Filter_Builder* filter_builder (void) const;

  /// Access the filter builder....
  TAO_EC_Supplier_Filter_Builder* supplier_filter_builder (void) const;

  /// Access the consumer admin implementation, useful for controlling
  /// the activation...
  TAO_EC_ConsumerAdmin* consumer_admin (void) const;

  /// Access the supplier admin implementation, useful for controlling
  /// the activation...
  TAO_EC_SupplierAdmin* supplier_admin (void) const;

  /// Access the timer module...
  TAO_EC_Timeout_Generator* timeout_generator (void) const;

  /// Access the scheduling strategy
  TAO_EC_Scheduling_Strategy* scheduling_strategy (void) const;

  /// Access the client control strategies.
  TAO_EC_ConsumerControl *consumer_control (void) const;
  TAO_EC_SupplierControl *supplier_control (void) const;

  // = The factory methods, they delegate on the EC_Factory.
  /// Create and destroy a ProxyPushSupplier
  void create_proxy (TAO_EC_ProxyPushSupplier*&);
  void destroy_proxy (TAO_EC_ProxyPushSupplier*);

  /// Create and destroy a ProxyPushConsumer
  void create_proxy (TAO_EC_ProxyPushConsumer*&);
  void destroy_proxy (TAO_EC_ProxyPushConsumer*);


  /// Create and destroy a the collections used to store
  /// ProxyPushSuppliers
  void create_proxy_collection (TAO_EC_ProxyPushSupplier_Collection*&);
  void destroy_proxy_collection (TAO_EC_ProxyPushSupplier_Collection*);


  /// Create and destroy a the collections used to store
  /// ProxyPushConsumers
  void create_proxy_collection (TAO_EC_ProxyPushConsumer_Collection*&);
  void destroy_proxy_collection (TAO_EC_ProxyPushConsumer_Collection*);

  /// Access the supplier and consumer POAs from the factory.
  PortableServer::POA_ptr supplier_poa (void);
  PortableServer::POA_ptr consumer_poa (void);

  /// Locking strategies for the ProxyPushConsumer and
  /// ProxyPushSupplier objects
  ACE_Lock* create_consumer_lock (void);
  void destroy_consumer_lock (ACE_Lock*);
  ACE_Lock* create_supplier_lock (void);
  void destroy_supplier_lock (ACE_Lock*);

  /// Used to inform the EC that a Consumer has connected or
  /// disconnected from it.
  virtual void connected (TAO_EC_ProxyPushConsumer*,
                          CORBA::Environment&);
  virtual void reconnected (TAO_EC_ProxyPushConsumer*,
                            CORBA::Environment&);
  virtual void disconnected (TAO_EC_ProxyPushConsumer*,
                             CORBA::Environment&);

  /// Used to inform the EC that a Supplier has connected or
  /// disconnected from it.
  virtual void connected (TAO_EC_ProxyPushSupplier*,
                          CORBA::Environment&);
  virtual void reconnected (TAO_EC_ProxyPushSupplier*,
                            CORBA::Environment&);
  virtual void disconnected (TAO_EC_ProxyPushSupplier*,
                             CORBA::Environment&);

  // Simple flags to control the EC behavior, set by the application
  // at construction time.

  /// Can the consumers reconnect to the EC?
  int consumer_reconnect (void) const;

  /// Can the suppliers reconnect to the EC?
  int supplier_reconnect (void) const;

  /// Should we send callback disconnect messages when a proxy is
  /// disconnected by the client
  int disconnect_callbacks (void) const;

  /// Obtain the scheduler, the user must release
  CORBA::Object_ptr scheduler (void);

  /// Control the concurrency of the delayed connect/disconnect
  /// operations.
  int busy_hwm (void) const;
  int max_write_delay (void) const;

  // = The RtecEventChannelAdmin::EventChannel methods...
  /// The default implementation is:
  ///    this->consumer_admin ()->_this (env);
  virtual RtecEventChannelAdmin::ConsumerAdmin_ptr
      for_consumers (CORBA::Environment& env)
        ACE_THROW_SPEC ((CORBA::SystemException));

  /// The default implementation is:
  ///    this->supplier_admin ()->_this (env);
  virtual RtecEventChannelAdmin::SupplierAdmin_ptr
      for_suppliers (CORBA::Environment& env)
        ACE_THROW_SPEC ((CORBA::SystemException));

  /// Commit suicide.
  virtual void destroy (CORBA::Environment &env)
    ACE_THROW_SPEC ((CORBA::SystemException));

  virtual RtecEventChannelAdmin::Observer_Handle
      append_observer (RtecEventChannelAdmin::Observer_ptr,
                       CORBA::Environment &env)
      ACE_THROW_SPEC ((
          CORBA::SystemException,
          RtecEventChannelAdmin::EventChannel::SYNCHRONIZATION_ERROR,
          RtecEventChannelAdmin::EventChannel::CANT_APPEND_OBSERVER));
  virtual void
      remove_observer (RtecEventChannelAdmin::Observer_Handle,
                       CORBA::Environment &env)
      ACE_THROW_SPEC ((
          CORBA::SystemException,
          RtecEventChannelAdmin::EventChannel::SYNCHRONIZATION_ERROR,
          RtecEventChannelAdmin::EventChannel::CANT_REMOVE_OBSERVER));

private:
  /// The POAs used to activate "supplier-side" and "consumer-side"
  /// objects.
  PortableServer::POA_var supplier_poa_;
  PortableServer::POA_var consumer_poa_;

  /**
   * This is the abstract factory that creates all the objects that
   * compose an event channel, the event channel simply acts as a
   * Mediator among them.
   */
  TAO_EC_Factory *factory_;

  /// Flag that indicates if we own the factory.
  int own_factory_;

  /// The dispatching "module"
  TAO_EC_Dispatching *dispatching_;

  /// The filter builder
  TAO_EC_Filter_Builder *filter_builder_;

  /// The filter builder for suppliers
  TAO_EC_Supplier_Filter_Builder *supplier_filter_builder_;

  /// The ConsumerAdmin implementation
  TAO_EC_ConsumerAdmin *consumer_admin_;

  /// The SupplierAdmin implementation
  TAO_EC_SupplierAdmin *supplier_admin_;

  /// The timeout generator
  TAO_EC_Timeout_Generator *timeout_generator_;

  /// The observer strategy
  TAO_EC_ObserverStrategy *observer_strategy_;

  /// The scheduler (may be nil)
  CORBA::Object_var scheduler_;

  /// The scheduling strategy
  TAO_EC_Scheduling_Strategy *scheduling_strategy_;

  /// Consumer/Supplier reconnection flags
  int consumer_reconnect_;
  int supplier_reconnect_;

  /// If not zero we send callbacks when a proxy is disconnected
  int disconnect_callbacks_;

  /// Control the level of concurrency in the supplier sets with
  /// delayed operations
  int busy_hwm_;
  int max_write_delay_;

  /// Strategies to disconnect misbehaving or destroyed consumers and
  /// suppliers
  TAO_EC_ConsumerControl *consumer_control_;
  TAO_EC_SupplierControl *supplier_control_;
};

#if defined (__ACE_INLINE__)
#include "EC_Event_Channel.i"
#endif /* __ACE_INLINE__ */

#include "ace/post.h"
#endif /* TAO_EC_EVENT_CHANNEL_H */
