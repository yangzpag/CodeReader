//
// Client_Task.cpp,v 1.7 2001/05/10 15:49:59 coryan Exp
//

#include "Client_Task.h"
#include "tao/TimeBaseC.h"
#include "tao/MessagingC.h"


ACE_RCSID(MT_Timeout, Client_Task, "Client_Task.cpp,v 1.7 2001/05/10 15:49:59 coryan Exp")

Client_Task::Client_Task (CORBA::ORB_ptr orb,
                          Test::Sleep_Service_ptr sleep_service,
                          int iterations,
                          CORBA::ULong sleep_time,
                          CORBA::ULong timeout)
  : orb_ (CORBA::ORB::_duplicate (orb))
  , sleep_service_ (Test::Sleep_Service::_duplicate (sleep_service))
  , iterations_ (iterations)
  , sleep_time_ (sleep_time)
  , timeout_ (timeout)
  , successful_calls_ (0)
  , timed_out_calls_ (0)
  , too_big_difference_ (0)
{
}

int
Client_Task::successful_calls (void) const
{
  return this->successful_calls_;
}

int
Client_Task::timed_out_calls (void) const
{
  return this->timed_out_calls_;
}

int
Client_Task::too_big_difference_calls (void) const
{
  return this->too_big_difference_;
}

int
Client_Task::svc (void)
{
  ACE_DECLARE_NEW_CORBA_ENV;

  int successful_calls = 0;
  int timed_out_calls = 0;

  ACE_TRY
    {
      this->validate_connection (ACE_TRY_ENV);
      ACE_TRY_CHECK;

      CORBA::Object_var object =
        this->orb_->resolve_initial_references ("PolicyCurrent",
                                                ACE_TRY_ENV);
      ACE_TRY_CHECK;
      CORBA::PolicyCurrent_var policy_current =
        CORBA::PolicyCurrent::_narrow (object.in (), ACE_TRY_ENV);
      ACE_TRY_CHECK;

      TimeBase::TimeT timeout_period = 10 * this->timeout_;

      CORBA::Any timeout_as_any;
      timeout_as_any <<= timeout_period;

      CORBA::PolicyList policy_list (1);
      policy_list.length (1);
      policy_list[0] =
        this->orb_->create_policy (Messaging::RELATIVE_RT_TIMEOUT_POLICY_TYPE,
                                   timeout_as_any,
                                   ACE_TRY_ENV);
      ACE_TRY_CHECK;

      policy_current->set_policy_overrides (policy_list,
                                            CORBA::ADD_OVERRIDE,
                                            ACE_TRY_ENV);
      ACE_TRY_CHECK;

      for (int i = 0; i != this->iterations_; ++i)
        {
          int retval = this->one_iteration (ACE_TRY_ENV);
          ACE_TRY_CHECK;

          if (retval == 1)
            successful_calls++;
          else if (retval == 0)
            timed_out_calls++;

#if 0
          if (i % 50 == 0)
            {
              ACE_DEBUG ((LM_DEBUG,
                          "(%P|%t) - Client_Task::svc %d / %d iterations\n",
                          i, this->iterations_));
            }
#endif /* 0 */
        }
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
                           "Exception caught:");
      return -1;
    }
  ACE_ENDTRY;

  ACE_GUARD_RETURN (TAO_SYNCH_MUTEX, ace_mon, this->mutex_, -1);
  this->successful_calls_ += successful_calls;
  this->timed_out_calls_  += timed_out_calls;

  return 0;
}

void
Client_Task::validate_connection (CORBA::Environment &ACE_TRY_ENV)
{
  ACE_TRY
    {
      for (int i = 0; i != 100; ++i)
        {
          (void) this->sleep_service_->go_to_sleep (0, ACE_TRY_ENV);
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
      ACE_Time_Value start = ACE_OS::gettimeofday ();

      this->sleep_service_->go_to_sleep (this->sleep_time_,
                                         ACE_TRY_ENV);
      ACE_TRY_CHECK;

      ACE_Time_Value end = ACE_OS::gettimeofday ();

      if (this->sleep_time_ > this->timeout_)
        {
          // If we don't sleep then the next request will also
          // timeout:
          // The server is already sleeping, the client sends a new
          // request, but the server cannot process it until the
          // previous sleep completes. The sleep times for multiple
          // requests accumulate, and the client always fails.
          CORBA::ULong remainder =
            this->sleep_time_ - this->timeout_;
          ACE_Time_Value tv (0, remainder);
          ACE_OS::sleep (tv);
        }

      if (this->timeout_ > 0)
        {
          CORBA::ULong max_milliseconds = this->timeout_ / 1000;

          ACE_Time_Value elapsed = end - start;
          CORBA::ULong elapsed_milliseconds = elapsed.msec ();

          if (elapsed_milliseconds > max_milliseconds)
            {
              CORBA::ULong difference =
                elapsed_milliseconds - max_milliseconds;

              // If the different is more than 10 milliseconds we are
              // *way* off, this is an error.
              if (difference > 10)
                {
		  this->too_big_difference_++;
                  ACE_ERROR ((LM_ERROR,
                              "(%P|%t) Elapsed time = %d, expected %d\n",
                              elapsed_milliseconds, max_milliseconds));
                }
            }
        }

      return 1;
    }
  ACE_CATCH(CORBA::TIMEOUT, to_exp)
    {
      // Ignore this exception, it is usually caused by a transient
      // condition
      return 0;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
                           "Exception caught:");
    }
  ACE_ENDTRY;

  return -1;
}
