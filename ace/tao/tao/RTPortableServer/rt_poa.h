// -*- C++ -*-
// RT_POA.h,v 1.2 2001/09/18 00:05:55 irfan Exp

// ============================================================================
//
// = LIBRARY
//    PortableServer
//
// = FILENAME
//    RT_POA.h
//
// = DESCRIPTION
//     RT_POA
//
// = AUTHOR
//     Irfan Pyarali
//
// ============================================================================

#ifndef TAO_RT_POA_H
#define TAO_RT_POA_H
#include "ace/pre.h"

#include "rtportableserver_export.h"
#include "tao/PortableServer/POA.h"

#define TAO_RT_PORTABLESERVER_SAFE_INCLUDE
#include "RTPortableServerC.h"
#undef TAO_RT_PORTABLESERVER_SAFE_INCLUDE

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

// This is to remove "inherits via dominance" warnings from MSVC.
// MSVC is being a little too paranoid.
#if defined(_MSC_VER)
#if (_MSC_VER >= 1200)
#pragma warning(push)
#endif /* _MSC_VER >= 1200 */
#pragma warning(disable:4250)
#endif /* _MSC_VER */

class TAO_Thread_Pool;
class TAO_Thread_Lane;
class TAO_PriorityBandedConnectionPolicy;

class TAO_RTPortableServer_Export TAO_RT_POA :
  public virtual RTPortableServer::POA,
  public virtual TAO_POA
{
public:

  // RTCORBA specific methods
  CORBA::Object_ptr create_reference_with_priority (const char * intf,
                                                    RTCORBA::Priority priority,
                                                    CORBA::Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableServer::POA::WrongPolicy));

  CORBA::Object_ptr create_reference_with_id_and_priority (const PortableServer::ObjectId & oid,
                                                           const char * intf,
                                                           RTCORBA::Priority priority,
                                                           CORBA::Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableServer::POA::WrongPolicy));

  PortableServer::ObjectId * activate_object_with_priority (PortableServer::Servant p_servant,
                                                            RTCORBA::Priority priority,
                                                            CORBA::Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableServer::POA::ServantAlreadyActive,
                     PortableServer::POA::WrongPolicy));

  void activate_object_with_id_and_priority (const PortableServer::ObjectId & oid,
                                             PortableServer::Servant p_servant,
                                             RTCORBA::Priority priority,
                                             CORBA::Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableServer::POA::ServantAlreadyActive,
                     PortableServer::POA::ObjectAlreadyActive,
                     PortableServer::POA::WrongPolicy));
  // End RTCORBA specific methods

  // Standard POA interface methods
  PortableServer::POA_ptr create_POA (const char *adapter_name,
                                      PortableServer::POAManager_ptr poa_manager,
                                      const CORBA::PolicyList &policies,
                                      CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableServer::POA::AdapterAlreadyExists,
                     PortableServer::POA::InvalidPolicy));

  PortableServer::POA_ptr find_POA (const char *adapter_name,
                                    CORBA::Boolean activate_it,
                                    CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableServer::POA::AdapterNonExistent));

  void destroy (CORBA::Boolean etherealize_objects,
                CORBA::Boolean wait_for_completion,
                CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

#if (TAO_HAS_MINIMUM_POA == 0)

  PortableServer::ThreadPolicy_ptr create_thread_policy (PortableServer::ThreadPolicyValue value,
                                                         CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

#endif /* TAO_HAS_MINIMUM_POA == 0 */

  PortableServer::LifespanPolicy_ptr create_lifespan_policy (PortableServer::LifespanPolicyValue value,
                                                             CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

  PortableServer::IdUniquenessPolicy_ptr create_id_uniqueness_policy (PortableServer::IdUniquenessPolicyValue value,
                                                                      CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

  PortableServer::IdAssignmentPolicy_ptr create_id_assignment_policy (PortableServer::IdAssignmentPolicyValue value,
                                                                      CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

#if (TAO_HAS_MINIMUM_POA == 0)

  PortableServer::ImplicitActivationPolicy_ptr create_implicit_activation_policy (PortableServer::ImplicitActivationPolicyValue value,
                                                                                  CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

  PortableServer::ServantRetentionPolicy_ptr create_servant_retention_policy (PortableServer::ServantRetentionPolicyValue value,
                                                                              CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

  PortableServer::RequestProcessingPolicy_ptr create_request_processing_policy (PortableServer::RequestProcessingPolicyValue value,
                                                                                CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

#endif /* TAO_HAS_MINIMUM_POA == 0 */

  char * the_name (CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

  PortableServer::POA_ptr the_parent (CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

  PortableServer::POAList *the_children (CORBA::Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

  PortableServer::POAManager_ptr the_POAManager (CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

#if (TAO_HAS_MINIMUM_POA == 0)

  PortableServer::AdapterActivator_ptr the_activator (CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

  void the_activator (PortableServer::AdapterActivator_ptr adapter_activator,
                      CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

  PortableServer::ServantManager_ptr get_servant_manager (CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableServer::POA::WrongPolicy));

  void set_servant_manager (PortableServer::ServantManager_ptr imgr,
                            CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableServer::POA::WrongPolicy));

  PortableServer::Servant get_servant (CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableServer::POA::NoServant,
                     PortableServer::POA::WrongPolicy));

  void set_servant (PortableServer::Servant servant,
                    CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableServer::POA::WrongPolicy));

#endif /* TAO_HAS_MINIMUM_POA == 0 */

  PortableServer::ObjectId *activate_object (PortableServer::Servant p_servant,
                                             CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableServer::POA::ServantAlreadyActive,
                     PortableServer::POA::WrongPolicy));

  void activate_object_with_id (const PortableServer::ObjectId &id,
                                PortableServer::Servant p_servant,
                                CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableServer::POA::ServantAlreadyActive,
                     PortableServer::POA::ObjectAlreadyActive,
                     PortableServer::POA::WrongPolicy));

  void deactivate_object (const PortableServer::ObjectId &oid,
                          CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableServer::POA::ObjectNotActive,
                     PortableServer::POA::WrongPolicy));

  CORBA::Object_ptr create_reference (const char *intf,
                                      CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableServer::POA::WrongPolicy));

  CORBA::Object_ptr create_reference_with_id (const PortableServer::ObjectId &oid,
                                              const char *intf,
                                              CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableServer::POA::WrongPolicy));

  PortableServer::ObjectId *servant_to_id (PortableServer::Servant p_servant,
                                           CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableServer::POA::ServantNotActive,
                     PortableServer::POA::WrongPolicy));

  CORBA::Object_ptr servant_to_reference (PortableServer::Servant p_servant,
                                          CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableServer::POA::ServantNotActive,
                     PortableServer::POA::WrongPolicy));

  PortableServer::Servant reference_to_servant (CORBA::Object_ptr reference,
                                                CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableServer::POA::ObjectNotActive,
                     PortableServer::POA::WrongAdapter,
                     PortableServer::POA::WrongPolicy));

  PortableServer::ObjectId *reference_to_id (CORBA::Object_ptr reference,
                                             CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableServer::POA::WrongAdapter,
                     PortableServer::POA::WrongPolicy));

  PortableServer::Servant id_to_servant (const PortableServer::ObjectId &oid,
                                         CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableServer::POA::ObjectNotActive,
                     PortableServer::POA::WrongPolicy));

  CORBA::Object_ptr id_to_reference (const PortableServer::ObjectId &oid,
                                     CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableServer::POA::ObjectNotActive,
                     PortableServer::POA::WrongPolicy));

  CORBA::OctetSeq *id (CORBA::Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

  // End standard POA interface methods.

  virtual CORBA::PolicyList *client_exposed_policies (CORBA::Short object_priority,
                                                      CORBA_Environment &ACE_TRY_ENV);

  TAO_RT_POA (const String &name,
              TAO_POA_Manager &poa_manager,
              const TAO_POA_Policy_Set &policies,
              TAO_POA *parent,
              ACE_Lock &lock,
              TAO_SYNCH_MUTEX &thread_lock,
              TAO_ORB_Core &orb_core,
              TAO_Object_Adapter *object_adapter,
              CORBA_Environment &ACE_TRY_ENV);

  virtual ~TAO_RT_POA (void);

  void *thread_pool (void) const;

protected:

  /// Template method for creating new POA's of this type.
  virtual TAO_POA *new_POA (const String &name,
                            TAO_POA_Manager &poa_manager,
                            const TAO_POA_Policy_Set &policies,
                            TAO_POA *parent,
                            ACE_Lock &lock,
                            TAO_SYNCH_MUTEX &thread_lock,
                            TAO_ORB_Core &orb_core,
                            TAO_Object_Adapter *object_adapter,
                            CORBA_Environment &ACE_TRY_ENV);

  virtual TAO_Stub *key_to_stub_i (const TAO_ObjectKey &key,
                                   const char *type_id,
                                   CORBA::Short priority,
                                   CORBA_Environment &ACE_TRY_ENV);

  void validate_priority (RTCORBA::Priority priority,
                          CORBA_Environment &ACE_TRY_ENV);

  void validate_policies (CORBA::Environment &ACE_TRY_ENV);

  // Parse the policy list for RT policies and update our
  // cached policy instance.
  void parse_rt_policies (TAO_POA_Policy_Set &policies,
                          CORBA::Environment &ACE_TRY_ENV);

  size_t endpoint_count (void);

  TAO_Stub *create_stub_object (const TAO_ObjectKey &object_key,
                                const char *type_id,
                                CORBA::PolicyList *policy_list,
                                TAO_Acceptor_Filter *filter,
                                TAO_PriorityBandedConnectionPolicy *priority_bands,
                                CORBA::Environment &ACE_TRY_ENV);

  int lane_required (TAO_Thread_Lane *lane,
                     TAO_PriorityBandedConnectionPolicy *priority_bands);

  TAO_Thread_Pool *thread_pool_;

};

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma warning(pop)
#endif /* _MSC_VER */

#if defined (__ACE_INLINE__)
# include "RT_POA.i"
#endif /* __ACE_INLINE__ */

#include "ace/post.h"
#endif /* TAO_POA_H */
