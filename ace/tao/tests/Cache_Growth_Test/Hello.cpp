//
// Hello.cpp,v 1.2 2001/09/18 21:39:33 irfan Exp
//
#include "Hello.h"
#include "tao/ORB_Core.h"
#include "tao/Transport_Cache_Manager.h"
#include "tao/Thread_Lane_Resources.h"

ACE_RCSID(Hello, Hello, "Hello.cpp,v 1.2 2001/09/18 21:39:33 irfan Exp")

Hello::Hello (CORBA::ORB_ptr orb)
  : orb_ (CORBA::ORB::_duplicate (orb))
{
}

char *
Hello::get_string (CORBA::Environment &)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  if (this->orb_->orb_core ()->lane_resources ().transport_cache ().current_size () > 1)
    {
      ACE_ERROR ((LM_ERROR,
                  "(%P|%t) The size is growing \n"));
    }

  return CORBA::string_dup ("Hello there!");
}

void
Hello::shutdown (CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  this->orb_->shutdown (0, ACE_TRY_ENV);
}
