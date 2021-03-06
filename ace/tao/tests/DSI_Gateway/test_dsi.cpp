// test_dsi.cpp,v 1.10 2001/05/09 19:17:09 parsons Exp

#include "test_dsi.h"
#include "tao/DynamicInterface/Request.h"
#include "tao/DynamicInterface/Unknown_User_Exception.h"

#if !defined(__ACE_INLINE__)
#include "test_dsi.i"
#endif /* __ACE_INLINE__ */

ACE_RCSID(DSI_Gateway, test_dsi, "test_dsi.cpp,v 1.10 2001/05/09 19:17:09 parsons Exp")

void
DSI_Simple_Server::invoke (CORBA::ServerRequest_ptr request,
                           CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  if (ACE_OS::strcmp ("shutdown", request->operation ()) == 0)
    {
      this->orb_->shutdown (0, ACE_TRY_ENV);
      ACE_CHECK;
    }

  CORBA::NVList_ptr list;
  this->orb_->create_list (0, list, ACE_TRY_ENV);
  ACE_CHECK;

  request->arguments (list, ACE_TRY_ENV);
  ACE_CHECK;

  CORBA::Request_var target_request;

  this->target_->_create_request (0, // ctx
                                  request->operation (),
                                  list,
                                  0, // result
                                  0, // exception_list,
                                  0, // context_list,
                                  target_request.inout (),
                                  0,
                                  ACE_TRY_ENV);
  ACE_CHECK;

  target_request->_tao_lazy_evaluation (1);

  // Outgoing request must have the same byte order as the incoming one.
  target_request->_tao_byte_order (request->_tao_incoming_byte_order ());

  ACE_TRY
    {
      // Updates the byte order state, if necessary.
      target_request->invoke (ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCH (CORBA::UNKNOWN, ex)
    {
      ACE_UNUSED_ARG (ex);

      // Outgoing reply must have the same byte order as the incoming one.
      request->_tao_reply_byte_order (target_request->_tao_byte_order ());

      request->gateway_exception_reply (target_request->raw_user_exception ());

      return;
    }
  ACE_ENDTRY;

  // Outgoing reply must have the same byte order as the incoming one.
  request->_tao_reply_byte_order (target_request->_tao_byte_order ());
}

CORBA::RepositoryId
DSI_Simple_Server::_primary_interface (const PortableServer::ObjectId &,
                                       PortableServer::POA_ptr,
                                       CORBA::Environment &)
    ACE_THROW_SPEC (())
{
  return CORBA::string_dup ("IDL:Simple_Server:1.0");
}

PortableServer::POA_ptr
DSI_Simple_Server::_default_POA (CORBA::Environment &)
{
  return PortableServer::POA::_duplicate (this->poa_.in ());
}
