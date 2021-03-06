//
// Manager.cpp,v 1.1 2000/06/16 20:15:25 coryan Exp
//

#include "Manager.h"

ACE_RCSID(LongUpcalls, Manager, "Manager.cpp,v 1.1 2000/06/16 20:15:25 coryan Exp")

Manager::Manager (CORBA::ORB_ptr orb)
  : orb_ (CORBA::ORB::_duplicate (orb))
{
}

void
Manager::start_workers (CORBA::Short worker_count,
                        CORBA::Long milliseconds,
                        Test::Controller_ptr controller,
                        CORBA::Environment &)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  ACE_Thread_Manager thread_manager;

  // ACE_DEBUG ((LM_DEBUG, "Starting %d workers\n", worker_count));
  Worker worker (&thread_manager,
                 controller, milliseconds);

  worker.activate (THR_NEW_LWP | THR_JOINABLE, worker_count);

  thread_manager.wait ();
}

void
Manager::shutdown (CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  this->orb_->shutdown (0, ACE_TRY_ENV);
}


// ****************************************************************

Worker::Worker (ACE_Thread_Manager *thr_mgr,
                Test::Controller_ptr controller,
                CORBA::Long milliseconds)
  :  ACE_Task_Base (thr_mgr)
  ,  controller_ (Test::Controller::_duplicate (controller))
  ,  milliseconds_ (milliseconds)
{
}

int
Worker::svc (void)
{
  // ACE_DEBUG ((LM_DEBUG, "Worker starts\n"));
  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {
      this->controller_->worker_started (ACE_TRY_ENV);
      ACE_TRY_CHECK;

      // ACE_DEBUG ((LM_DEBUG, "Worker start reported\n"));

      ACE_Time_Value tv (0, 1000 * this->milliseconds_);
      ACE_OS::sleep (tv);

      this->controller_->worker_finished (ACE_TRY_ENV);
      ACE_TRY_CHECK;

      // ACE_DEBUG ((LM_DEBUG, "Worker completion reported\n"));
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
                           "Exception in svc() method\n");
    }
  ACE_ENDTRY;
  return 0;
}
