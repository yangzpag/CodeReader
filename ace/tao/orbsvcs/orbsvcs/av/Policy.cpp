// Policy.cpp,v 5.6 2001/03/26 21:17:02 coryan Exp

#include "Policy.h"
#include "FlowSpec_Entry.h"
#include "tao/debug.h"

#if !defined(__ACE_INLINE__)
#include "Policy.i"
#endif /* __ACE_INLINE__ */

TAO_AV_Policy::TAO_AV_Policy (CORBA::ULong type)
  :type_ (type)
{
}


TAO_AV_SSRC_Policy::TAO_AV_SSRC_Policy (CORBA::ULong ssrc)
  :TAO_AV_Policy (TAO_AV_SSRC_POLICY),
   ssrc_ (ssrc)
{
}


TAO_AV_Payload_Type_Policy::TAO_AV_Payload_Type_Policy (int payload_type)
  :TAO_AV_Policy (TAO_AV_PAYLOAD_TYPE_POLICY),
   payload_type_ (payload_type)
{
}

// TAO_AV_RTP_Sdes_Policy
TAO_AV_RTCP_Sdes_Policy::TAO_AV_RTCP_Sdes_Policy (void)
  :TAO_AV_Policy (TAO_AV_RTCP_SDES_POLICY)
{
}

TAO_AV_SFP_Credit_Policy::TAO_AV_SFP_Credit_Policy (void)
  :TAO_AV_Policy (TAO_AV_SFP_CREDIT_POLICY)
{
}

// TAO_AV_Callback
TAO_AV_Callback::TAO_AV_Callback (void)
   :protocol_object_ (0)
{
}

TAO_AV_Callback::~TAO_AV_Callback (void)
{
}

int
TAO_AV_Callback::open (TAO_AV_Protocol_Object *object,
                       TAO_AV_Flow_Handler *handler)
{
  this->protocol_object_ = object;
  this->handler_ = handler;
  handler->callback (this);
  return 0;
}

int
TAO_AV_Callback::handle_start (void)
{
  if (TAO_debug_level > 0) ACE_DEBUG ((LM_DEBUG,"TAO_AV_Callback::handle_start\n"));
  return -1;
}

int
TAO_AV_Callback::handle_stop (void)
{
  if (TAO_debug_level > 0) ACE_DEBUG ((LM_DEBUG,"TAO_AV_Callback::handle_stop\n"));
  return -1;
}

int
TAO_AV_Callback::receive_frame (ACE_Message_Block * /*frame*/,
                                TAO_AV_frame_info *,
                                const ACE_Addr &)
{
  if (TAO_debug_level > 0) ACE_DEBUG ((LM_DEBUG,"TAO_AV_Callback::receive_frame\n"));
  return -1;
}

int
TAO_AV_Callback::receive_control_frame (ACE_Message_Block *,
                                        const ACE_Addr& )
{
  return 0;
}

int
TAO_AV_Callback::handle_destroy (void)
{
  if (TAO_debug_level > 0) ACE_DEBUG ((LM_DEBUG,"TAO_AV_Callback::handle_end_stream\n"));
  return -1;
}

void
TAO_AV_Callback::get_timeout (ACE_Time_Value *& /*tv*/,
                              void *& /*arg*/)
{
  if (TAO_debug_level > 0) ACE_DEBUG ((LM_DEBUG,"TAO_AV_Callback::get_timeout\n"));
}

int
TAO_AV_Callback::handle_timeout (void * /*arg*/)
{
  if (TAO_debug_level > 0) ACE_DEBUG ((LM_DEBUG,"TAO_AV_Callback::handle_timeout\n"));
  return 0;
}

TAO_AV_PolicyList
TAO_AV_Callback::get_policies (void)
{
  TAO_AV_PolicyList list;
  return list;
}

// TAO_AV_Transport*
// TAO_AV_Callback::transport (void)
// {
//   return this->transport_;
// }

// void
// TAO_AV_Callback::transport (TAO_AV_Transport *transport)
// {
//   this->transport_ = transport;
// }

TAO_AV_Protocol_Object*
TAO_AV_Callback::protocol_object (void)
{
  return this->protocol_object_;
}

// void
// TAO_AV_Callback::protocol_object (TAO_AV_Protocol_Object *object)
// {
//   this->protocol_object_ = object;
// }

int
TAO_AV_Callback::schedule_timer (void)
{
  return this->handler_->schedule_timer ();
}

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)

template class TAO_Unbounded_Sequence<TAO_AV_Policy*>;

#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)

#pragma instantiate TAO_Unbounded_Sequence<TAO_AV_Policy*>

#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */
