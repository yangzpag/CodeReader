// EC_UDP_Admin.cpp,v 1.2 1999/06/12 23:43:58 coryan Exp

#include "orbsvcs/Event/EC_UDP_Admin.h"

ACE_RCSID(Event, EC_UDP_Admin, "EC_UDP_Admin.cpp,v 1.2 1999/06/12 23:43:58 coryan Exp")

TAO_EC_Simple_AddrServer::TAO_EC_Simple_AddrServer (CORBA::UShort port)
  : port_ (port)
{
}

TAO_EC_Simple_AddrServer::~TAO_EC_Simple_AddrServer (void)
{
}

void
TAO_EC_Simple_AddrServer::get_addr (const RtecEventComm::EventHeader& header,
                                    RtecUDPAdmin::UDP_Addr_out addr,
                                    CORBA::Environment&)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  addr.ipaddr = header.type;
  addr.port = this->port_;
}
