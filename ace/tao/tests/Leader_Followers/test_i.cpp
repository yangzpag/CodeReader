// test_i.cpp,v 1.4 2001/05/20 15:46:57 bala Exp

#include "test_i.h"

ACE_RCSID(Leader_Followers, test_i, "test_i.cpp,v 1.4 2001/05/20 15:46:57 bala Exp")

test_i::test_i (CORBA::ORB_ptr orb)
  : orb_ (CORBA::ORB::_duplicate (orb))
{
}

void
test_i::shutdown (CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  this->orb_->shutdown (0,
                        ACE_TRY_ENV);
}

CORBA::ULong
test_i::method (CORBA::ULong work,
                CORBA::Environment &)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  ACE_DEBUG ((LM_DEBUG,
              "Server: Working for %d milli seconds @ %T\n",
              work));

  // Time required to process this request. <work> is time units in
  // milli seconds.
  ACE_Time_Value work_time (0,
                            work * 1000);

  ACE_OS::sleep (work_time);

  return work;
}
