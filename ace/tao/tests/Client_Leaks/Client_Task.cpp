//
// Client_Task.cpp,v 1.3 2001/03/29 15:50:18 coryan Exp
//

#include "Client_Task.h"

ACE_RCSID(Client_Leaks, Client_Task, "Client_Task.cpp,v 1.3 2001/03/29 15:50:18 coryan Exp")

Client_Task::Client_Task (Test::Process_Factory_ptr process_factory,
                          int iterations)
  : process_factory_ (Test::Process_Factory::_duplicate (process_factory))
  , iterations_ (iterations)
  , successful_calls_ (0)
{
}

int
Client_Task::successful_calls (void) const
{
  return this->successful_calls_;
}

int
Client_Task::svc (void)
{
  ACE_DEBUG ((LM_DEBUG, "(%P|%t) Starting client task\n"));
  ACE_DECLARE_NEW_CORBA_ENV;

  int successful_calls = 0;

  ACE_TRY
    {
      this->validate_connection (ACE_TRY_ENV);
      ACE_TRY_CHECK;

      for (int i = 0; i != this->iterations_; ++i)
        {
          int retval = this->one_iteration (ACE_TRY_ENV);
          ACE_TRY_CHECK;

          if (retval != 0)
            successful_calls++;

          if (i % 10 == 0)
            {
              ACE_DEBUG ((LM_DEBUG,
                          "(%P|%t) - Client_Task::svc %d / %d iterations\n",
                          i, this->iterations_));
            }
        }
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
                           "Exception caught:");
      return -1;
    }
  ACE_ENDTRY;
  ACE_DEBUG ((LM_DEBUG, "(%P|%t) Client task finished\n"));

  ACE_GUARD_RETURN (TAO_SYNCH_MUTEX, ace_mon, this->mutex_, -1);
  this->successful_calls_ += successful_calls;

  return 0;
}

void
Client_Task::validate_connection (CORBA::Environment &ACE_TRY_ENV)
{
  ACE_TRY
    {
      for (int i = 0; i != 100; ++i)
        {
          (void) this->process_factory_->noop (ACE_TRY_ENV);
          ACE_TRY_CHECK;
        }
    }
  ACE_CATCH (CORBA::TRANSIENT, ex)
    {
      // Ignore transient exceptions
    }
  ACE_ENDTRY;
  ACE_CHECK;
}

int
Client_Task::one_iteration (CORBA::Environment &ACE_TRY_ENV)
{
  ACE_TRY
    {
      Test::Process_var process =
        this->process_factory_->create_new_process (ACE_TRY_ENV);
      ACE_TRY_CHECK;

      (void) process->get_process_id (ACE_TRY_ENV);
      ACE_TRY_CHECK;

      process->shutdown (ACE_TRY_ENV);
      ACE_TRY_CHECK;

      return 1;
    }
  ACE_CATCH(Test::Spawn_Failed, ignored)
    {
      // Ignore this exception, it is usually caused by a transient
      // condition
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
                           "Exception caught:");
    }
  ACE_ENDTRY;

  return 0;
}
