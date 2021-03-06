// @(#) Default_Servant_Dispatcher.cpp,v 1.3 2001/06/12 18:58:20 fhunleth Exp

#include "Default_Servant_Dispatcher.h"
#include "POA.h"

ACE_RCSID(tao, Default_Acceptor_Filter, "Default_Servant_Dispatcher.cpp,v 1.3 2001/06/12 18:58:20 fhunleth Exp")

TAO_Default_Servant_Dispatcher::~TAO_Default_Servant_Dispatcher (void)
{
}

void
TAO_Default_Servant_Dispatcher::dispatch (
  TAO_Object_Adapter::Servant_Upcall &servant_upcall,
  TAO_ServerRequest &req,
  CORBA::Environment &ACE_TRY_ENV)
{
  servant_upcall.servant ()->_dispatch (req,
                                        &servant_upcall,
                                        ACE_TRY_ENV);
}

TAO_POA *
TAO_Default_Servant_Dispatcher::create_POA (const ACE_CString &name,
                                            TAO_POA_Manager &poa_manager,
                                            const TAO_POA_Policy_Set &policies,
                                            TAO_POA *parent,
                                            ACE_Lock &lock,
                                            TAO_SYNCH_MUTEX &thread_lock,
                                            TAO_ORB_Core &orb_core,
                                            TAO_Object_Adapter *object_adapter,
                                            CORBA_Environment &ACE_TRY_ENV)
{
  TAO_POA *poa;

  ACE_NEW_THROW_EX (poa,
                    TAO_POA (name,
                             poa_manager,
                             policies,
                             parent,
                             lock,
                             thread_lock,
                             orb_core,
                             object_adapter,
                             ACE_TRY_ENV),
                    CORBA::NO_MEMORY ());
  ACE_CHECK_RETURN (0);

  return poa;
}
