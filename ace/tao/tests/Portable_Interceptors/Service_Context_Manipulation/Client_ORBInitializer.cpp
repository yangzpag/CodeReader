// -*- C++ -*-
//
// Client_ORBInitializer.cpp,v 1.2 2001/01/28 03:57:27 othman Exp
//

#include "Client_ORBInitializer.h"
#include "interceptors.h"

ACE_RCSID (Service_Context_Manipulation, Client_ORBInitializer, "Client_ORBInitializer.cpp,v 1.2 2001/01/28 03:57:27 othman Exp")

Client_ORBInitializer::Client_ORBInitializer (void)
{
}

void
Client_ORBInitializer::pre_init (
    PortableInterceptor::ORBInitInfo_ptr
    TAO_ENV_ARG_DECL_NOT_USED)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
}

void
Client_ORBInitializer::post_init (
    PortableInterceptor::ORBInitInfo_ptr info
    TAO_ENV_ARG_DECL)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  TAO_ENV_ARG_DEFN;

  CORBA::String_var orb_id =
    info->orb_id (ACE_TRY_ENV);
  ACE_CHECK;

  PortableInterceptor::ClientRequestInterceptor_ptr interceptor =
    PortableInterceptor::ClientRequestInterceptor::_nil ();

  // Install the Echo client request interceptor
  ACE_NEW_THROW_EX (interceptor,
                    Echo_Client_Request_Interceptor (orb_id.in ()),
                    CORBA::NO_MEMORY ());
  ACE_CHECK;

  PortableInterceptor::ClientRequestInterceptor_var
    client_interceptor = interceptor;

  info->add_client_request_interceptor (client_interceptor.in (),
                                        ACE_TRY_ENV);
  ACE_CHECK;
}

