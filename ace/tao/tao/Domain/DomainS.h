// -*- C++ -*-
//
// DomainS.h,v 1.6 2001/05/31 15:44:26 othman Exp

// ****  Code generated by the The ACE ORB (TAO) IDL Compiler ****
// TAO and the TAO IDL Compiler have been developed by:
//       Center for Distributed Object Computing
//       Washington University
//       St. Louis, MO
//       USA
//       http://www.cs.wustl.edu/~schmidt/doc-center.html
// and
//       Distributed Object Computing Laboratory
//       University of California at Irvine
//       Irvine, CA
//       USA
//       http://doc.ece.uci.edu/
//
// Information about TAO is available at:
//     http://www.cs.wustl.edu/~schmidt/TAO.html

#ifndef _TAO_IDL_DOMAINS_H_
#define _TAO_IDL_DOMAINS_H_

#include "ace/pre.h"

#include "domain_export.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "tao/DomainC.h"
#include "tao/PortableServer/PolicyS.h"

#include "tao/PortableServer/PortableServer.h"
#include "tao/PortableServer/Servant_Base.h"
#include "tao/PortableServer/Collocated_Object.h"
#include "tao/PortableServer/ThruPOA_Object_Proxy_Impl.h"
#include "tao/PortableServer/Direct_Object_Proxy_Impl.h"
#if defined(_MSC_VER)
#if (_MSC_VER >= 1200)
#pragma warning(push)
#endif /* _MSC_VER >= 1200 */
#pragma warning(disable:4250)
#endif /* _MSC_VER */

#if defined (__BORLANDC__)
#pragma option push -w-rvl -w-rch -w-ccc -w-inl
#endif /* __BORLANDC__ */

  class POA_CORBA_DomainManager;
  typedef POA_CORBA_DomainManager *POA_CORBA_DomainManager_ptr;
  // Forward Classes Declaration
  class _TAO_DomainManager_ThruPOA_Proxy_Impl;
  class _TAO_DomainManager_Strategized_Proxy_Broker;

  class TAO_Domain_Export POA_CORBA_DomainManager :  public virtual PortableServer::ServantBase
  {
  protected:
    POA_CORBA_DomainManager (void);

  public:
    POA_CORBA_DomainManager (const POA_CORBA_DomainManager& rhs);
    virtual ~POA_CORBA_DomainManager (void);


    virtual CORBA::Boolean _is_a (
        const char* logical_type_id,
        CORBA::Environment &ACE_TRY_ENV =
          TAO_default_environment ()
      );

    virtual void* _downcast (
        const char* logical_type_id
      );

    static void _is_a_skel (
        TAO_ServerRequest &req,
        void *obj,
        void *servant_upcall,
        CORBA::Environment &ACE_TRY_ENV
      );

    static void _non_existent_skel (
        TAO_ServerRequest &req,
        void *obj,
        void *servant_upcall,
        CORBA::Environment &ACE_TRY_ENV
      );

    static void _interface_skel (
        TAO_ServerRequest &req,
        void *obj,
        void *servant_upcall,
        CORBA::Environment &ACE_TRY_ENV
      );

    virtual void _dispatch (
        TAO_ServerRequest &req,
        void *_servant_upcall,
        CORBA::Environment &ACE_TRY_ENV
      );

    ::CORBA::DomainManager *_this (
        CORBA::Environment &ACE_TRY_ENV =
          TAO_default_environment ()
      );

    virtual const char* _interface_repository_id (void) const;

    virtual CORBA::Policy_ptr get_domain_policy (
        CORBA::PolicyType policy_type,
        CORBA::Environment &ACE_TRY_ENV =
          TAO_default_environment ()
      )
      ACE_THROW_SPEC ((
        CORBA::SystemException
      )) = 0;

    static void get_domain_policy_skel (
        TAO_ServerRequest &_tao_req,
        void *_tao_obj,
        void *_tao_servant_upcall,
        CORBA::Environment &ACE_TRY_ENV
      );


  };


  ///////////////////////////////////////////////////////////////////////
  //               Strategized Proxy Broker Declaration
  //

  class TAO_Domain_Export _TAO_DomainManager_Strategized_Proxy_Broker : public virtual _TAO_CORBA_DomainManager_Proxy_Broker
  {
  public:
    _TAO_DomainManager_Strategized_Proxy_Broker (void);

    virtual ~_TAO_DomainManager_Strategized_Proxy_Broker (void);

    virtual _TAO_CORBA_DomainManager_Proxy_Impl &select_proxy (
      ::CORBA::DomainManager *object,
      CORBA_Environment &ACE_TRY_ENV
    );

  private:
    // Helper methods that takes care to create the proxy
    // as soon as their use is necessary.
    void create_proxy (
      int collocation_strategy,
      CORBA::Environment &ACE_TRY_ENV
    );

    // Caches the proxy implementations. The proxy implementation
    // are totally stateless, and those can be shared by all the
    // instances of a given IDL interface type.
    _TAO_CORBA_DomainManager_Proxy_Impl
    *proxy_cache_[TAO_Collocation_Strategies::CS_LAST];

    TAO_SYNCH_MUTEX mutex_;
    // This funxtion is used to get an handle to the unique instance
    // of the Strategized Proxy Broker that is available for a given
    // interface.

  public:
    static _TAO_DomainManager_Strategized_Proxy_Broker *the_TAO_DomainManager_Strategized_Proxy_Broker (void);
  };


  //
  //            End Strategized Proxy Broker Declaration
  ///////////////////////////////////////////////////////////////////////


  ///////////////////////////////////////////////////////////////////////
  //                    ThruPOA  Impl. Declaration
  //

  class TAO_Domain_Export _TAO_DomainManager_ThruPOA_Proxy_Impl :
    public virtual _TAO_CORBA_DomainManager_Proxy_Impl,
    public virtual TAO_ThruPOA_Object_Proxy_Impl
  {
  public:
    _TAO_DomainManager_ThruPOA_Proxy_Impl (void);

    virtual ~_TAO_DomainManager_ThruPOA_Proxy_Impl (void) { }

    virtual CORBA::Policy_ptr get_domain_policy (
        CORBA::Object_ptr _collocated_tao_target_,
        CORBA::PolicyType policy_type,
        CORBA::Environment &ACE_TRY_ENV
      )
      ACE_THROW_SPEC ((
        CORBA::SystemException
      ));


  };

  //
  //                ThruPOA  Proxy Impl. Declaration
  ///////////////////////////////////////////////////////////////////////


  class POA_CORBA_ConstructionPolicy;
  typedef POA_CORBA_ConstructionPolicy *POA_CORBA_ConstructionPolicy_ptr;
  // Forward Classes Declaration
  class _TAO_ConstructionPolicy_ThruPOA_Proxy_Impl;
  class _TAO_ConstructionPolicy_Strategized_Proxy_Broker;

  class TAO_Domain_Export POA_CORBA_ConstructionPolicy : public virtual POA_CORBA_Policy
  {
  protected:
    POA_CORBA_ConstructionPolicy (void);

  public:
    POA_CORBA_ConstructionPolicy (const POA_CORBA_ConstructionPolicy& rhs);
    virtual ~POA_CORBA_ConstructionPolicy (void);


    virtual CORBA::Boolean _is_a (
        const char* logical_type_id,
        CORBA::Environment &ACE_TRY_ENV =
          TAO_default_environment ()
      );

    virtual void* _downcast (
        const char* logical_type_id
      );

    static void _is_a_skel (
        TAO_ServerRequest &req,
        void *obj,
        void *servant_upcall,
        CORBA::Environment &ACE_TRY_ENV
      );

    static void _non_existent_skel (
        TAO_ServerRequest &req,
        void *obj,
        void *servant_upcall,
        CORBA::Environment &ACE_TRY_ENV
      );

    static void _interface_skel (
        TAO_ServerRequest &req,
        void *obj,
        void *servant_upcall,
        CORBA::Environment &ACE_TRY_ENV
      );

    virtual void _dispatch (
        TAO_ServerRequest &req,
        void *_servant_upcall,
        CORBA::Environment &ACE_TRY_ENV
      );

    CORBA_ConstructionPolicy *_this (
        CORBA::Environment &ACE_TRY_ENV =
          TAO_default_environment ()
      );

    virtual const char* _interface_repository_id (void) const;

    virtual void make_domain_manager (
        CORBA::InterfaceDef_ptr object_type,
        CORBA::Boolean constr_policy,
        CORBA::Environment &ACE_TRY_ENV =
          TAO_default_environment ()
      )
      ACE_THROW_SPEC ((
        CORBA::SystemException
      )) = 0;

    static void make_domain_manager_skel (
        TAO_ServerRequest &_tao_req,
        void *_tao_obj,
        void *_tao_servant_upcall,
        CORBA::Environment &ACE_TRY_ENV
      );

    static void _get_policy_type_skel (
        TAO_ServerRequest &req,
        void *obj,
        void *context,
        CORBA::Environment &ACE_TRY_ENV =
          TAO_default_environment ()
      );

    static void copy_skel (
        TAO_ServerRequest &req,
        void *obj,
        void *context,
        CORBA::Environment &ACE_TRY_ENV =
          TAO_default_environment ()
      );

    static void destroy_skel (
        TAO_ServerRequest &req,
        void *obj,
        void *context,
        CORBA::Environment &ACE_TRY_ENV =
          TAO_default_environment ()
      );


  };


  ///////////////////////////////////////////////////////////////////////
  //               Strategized Proxy Broker Declaration
  //

  class TAO_Domain_Export _TAO_ConstructionPolicy_Strategized_Proxy_Broker : public virtual _TAO_CORBA_ConstructionPolicy_Proxy_Broker
  {
  public:
    _TAO_ConstructionPolicy_Strategized_Proxy_Broker (void);

    virtual ~_TAO_ConstructionPolicy_Strategized_Proxy_Broker (void);

    virtual _TAO_CORBA_ConstructionPolicy_Proxy_Impl &select_proxy (
      CORBA_ConstructionPolicy *object,
      CORBA_Environment &ACE_TRY_ENV
    );

  private:
    // Helper methods that takes care to create the proxy
    // as soon as their use is necessary.
    void create_proxy (
      int collocation_strategy,
      CORBA::Environment &ACE_TRY_ENV
    );

    // Caches the proxy implementations. The proxy implementation
    // are totally stateless, and those can be shared by all the
    // instances of a given IDL interface type.
    _TAO_CORBA_ConstructionPolicy_Proxy_Impl
    *proxy_cache_[TAO_Collocation_Strategies::CS_LAST];

    TAO_SYNCH_MUTEX mutex_;
    // This funxtion is used to get an handle to the unique instance
    // of the Strategized Proxy Broker that is available for a given
    // interface.

  public:
    static _TAO_ConstructionPolicy_Strategized_Proxy_Broker *the_TAO_ConstructionPolicy_Strategized_Proxy_Broker (void);
  };


  //
  //            End Strategized Proxy Broker Declaration
  ///////////////////////////////////////////////////////////////////////


  ///////////////////////////////////////////////////////////////////////
  //                    ThruPOA  Impl. Declaration
  //

  class TAO_Domain_Export _TAO_ConstructionPolicy_ThruPOA_Proxy_Impl :
    public virtual _TAO_CORBA_ConstructionPolicy_Proxy_Impl,
    public virtual TAO_ThruPOA_Object_Proxy_Impl,
    public virtual POA_CORBA_TAO_Policy_ThruPOA_Proxy_Impl

  {
  public:
    _TAO_ConstructionPolicy_ThruPOA_Proxy_Impl (void);

    virtual ~_TAO_ConstructionPolicy_ThruPOA_Proxy_Impl (void) { }

    virtual void make_domain_manager (
        CORBA::Object_ptr _collocated_tao_target_,
        CORBA::InterfaceDef_ptr object_type,
        CORBA::Boolean constr_policy,
        CORBA::Environment &ACE_TRY_ENV
      )
      ACE_THROW_SPEC ((
        CORBA::SystemException
      ));


  };

  //
  //                ThruPOA  Proxy Impl. Declaration
  ///////////////////////////////////////////////////////////////////////


#include "DomainS_T.h"

#if defined (__ACE_INLINE__)
#include "DomainS.i"
#endif /* defined INLINE */

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma warning(pop)
#endif /* _MSC_VER */

#if defined (__BORLANDC__)
#pragma option pop
#endif /* __BORLANDC__ */

#include "ace/post.h"
#endif /* ifndef */
