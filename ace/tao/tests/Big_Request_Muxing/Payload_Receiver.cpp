//
// Payload_Receiver.cpp,v 1.2 2001/04/24 08:02:57 coryan Exp
//
#include "Payload_Receiver.h"

ACE_RCSID(Big_Request_Muxing, Payload_Receiver, "Payload_Receiver.cpp,v 1.2 2001/04/24 08:02:57 coryan Exp")

Payload_Receiver::Payload_Receiver (void)
  :  message_count_ (0)
  ,  byte_count_ (0)
{
}

void
Payload_Receiver::more_data (const Test::Payload &payload,
                             CORBA::Environment &)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  this->message_count_++;
  this->byte_count_ += payload.length ();
}

CORBA::Long
Payload_Receiver::get_message_count (CORBA::Environment &)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  return this->message_count_;
}
