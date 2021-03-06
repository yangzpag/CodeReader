// test_i.cpp,v 1.4 2001/07/17 19:12:00 bala Exp

#include "test_i.h"

ACE_RCSID(Single_Read, test_i, "test_i.cpp,v 1.4 2001/07/17 19:12:00 bala Exp")

test_i::test_i (CORBA::ORB_ptr orb)
  : orb_ (CORBA::ORB::_duplicate (orb))
{
}

void
test_i::method (CORBA::ULong request_number,
                const test::data &,
                CORBA::Environment &)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("server: Iteration %d @ %T\n"),
              request_number));

  // Time required to process this request.
  ACE_Time_Value work_time (0,
                            3000 * 1000);

  ACE_OS::sleep (work_time);
}

void
test_i::shutdown (CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  ACE_DEBUG ((LM_DEBUG,
              "(%P|%t) About to invoke shudown... "));
  this->orb_->shutdown (0,
                        ACE_TRY_ENV);
}
