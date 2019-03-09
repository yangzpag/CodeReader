//
// Session_Control.cpp,v 1.2 2001/04/24 08:02:58 coryan Exp
//
#include "Session_Control.h"

ACE_RCSID(Big_Oneways, Session_Control, "Session_Control.cpp,v 1.2 2001/04/24 08:02:58 coryan Exp")

Session_Control::Session_Control (CORBA::ULong session_count)
  : session_count_ (session_count)
  , success_ (1)
{
}

int
Session_Control::all_sessions_finished (void) const
{
  return this->session_count_ == 0;
}

Session_Control::~Session_Control (void)
{
  if (this->session_count_ == 0 && this->success_)
    {
      ACE_DEBUG ((LM_DEBUG,
                  "(%P|%t) Session_Control::~Session_control, "
                  " good, all sessions did finish\n"));
    }
  else if (session_count_ != 0)
    {
      ACE_ERROR ((LM_ERROR,
                  "ERROR: (%P|%t) Session_Control::~Session_control, "
                  " %d sessions did not finish\n",
                  this->session_count_));
    }
  else
    {
      ACE_ERROR ((LM_ERROR,
                  "ERROR: (%P|%t) Session_Control::~Session_control, "
                  " some sessions failed\n"));
    }
}

void
Session_Control::session_finished (CORBA::Boolean success,
                                   CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  ACE_GUARD (ACE_SYNCH_MUTEX, ace_mon, this->mutex_);
  if (this->session_count_ == 0)
    {
      ACE_ERROR ((LM_ERROR,
                  "ERROR: (%P|%t) Session_Control::session_finished, "
                  "unexpected callback\n"));
    }
  if (success == 0)
    this->success_ = 0;

  this->session_count_--;
  ACE_DEBUG ((LM_DEBUG,
              "(%P|%t) Session_Control::session_finished, "
              "%d sessions to go\n",
              this->session_count_));
  if (session_count_ == 0)
    {
      PortableServer::POA_var poa =
        this->_default_POA (ACE_TRY_ENV);
      ACE_CHECK;
      PortableServer::ObjectId_var oid =
        poa->servant_to_id (this, ACE_TRY_ENV);
      ACE_CHECK;
      poa->deactivate_object (oid.in (), ACE_TRY_ENV);
      ACE_CHECK;
    }

}
