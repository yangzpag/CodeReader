//
// Server_Task.cpp,v 1.1 2001/03/21 01:07:53 coryan Exp
//

#include "Server_Task.h"

ACE_RCSID(Client_Leaks, Server_Task, "Server_Task.cpp,v 1.1 2001/03/21 01:07:53 coryan Exp")

Server_Task::Server_Task (CORBA::ORB_ptr orb,
                          ACE_Thread_Manager *thr_mgr)
  : ACE_Task_Base (thr_mgr)
  , orb_ (CORBA::ORB::_duplicate (orb))
{
}

int
Server_Task::svc (void)
{
  ACE_DEBUG ((LM_DEBUG, "(%P|%t) Starting server task\n"));
  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {
      // run the test for at most 120 seconds...
      // ACE_Time_Value tv (120, 0);
      this->orb_->run ( /* tv, */ ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      return -1;
    }
  ACE_ENDTRY;
  ACE_DEBUG ((LM_DEBUG, "(%P|%t) Server task finished\n"));
  return 0;
}
