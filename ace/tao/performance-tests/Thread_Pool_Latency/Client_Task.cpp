//
// Client_Task.cpp,v 1.1 2001/05/09 22:38:26 coryan Exp
//
#include "Client_Task.h"

ACE_RCSID(Thread_Pool_Latency, Client_Task, "Client_Task.cpp,v 1.1 2001/05/09 22:38:26 coryan Exp")

Client_Task::Client_Task (Test::Roundtrip_ptr roundtrip,
                          int niterations)
  : roundtrip_ (Test::Roundtrip::_duplicate (roundtrip))
  , niterations_ (niterations)
{
}

int
Client_Task::svc (void)
{
  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {
      this->validate_connection (ACE_TRY_ENV);
      ACE_TRY_CHECK;

      for (int i = 0; i != this->niterations_; ++i)
        {
          CORBA::ULongLong start = ACE_OS::gethrtime ();

          (void) this->roundtrip_->test_method (start, ACE_TRY_ENV);
          ACE_TRY_CHECK;

          ACE_hrtime_t now = ACE_OS::gethrtime ();
          this->latency_.sample (now - start);
        }
    }
  ACE_CATCHANY
    {
      return 0;
    }
  ACE_ENDTRY;
  return 0;
}

void
Client_Task::accumulate_and_dump (ACE_Basic_Stats &totals,
                                  const char *msg,
                                  ACE_UINT32 gsf)
{
  totals.accumulate (this->latency_);
  this->latency_.dump_results (msg, gsf);
}

void
Client_Task::validate_connection (CORBA::Environment &ACE_TRY_ENV)
{
  CORBA::ULongLong dummy = 0;
  for (int i = 0; i != 100; ++i)
    {
      ACE_TRY
        {
          (void) this->roundtrip_->test_method (dummy, ACE_TRY_ENV);
          ACE_TRY_CHECK;
        }
      ACE_CATCHANY {} ACE_ENDTRY;
    }
}
