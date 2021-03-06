// test_i.cpp,v 1.2 2001/05/20 17:38:49 fhunleth Exp

#include "test_i.h"
#include "tao/debug.h"
#include "ace/ACE.h"

#if !defined(__ACE_INLINE__)
#include "test_i.i"
#endif /* __ACE_INLINE__ */

ACE_RCSID(Latency, test_i, "test_i.cpp,v 1.2 2001/05/20 17:38:49 fhunleth Exp")

void
Test_i::test_method (CORBA::Long id,
                     CORBA::Environment&)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  if (TAO_debug_level > 0)
    ACE_DEBUG ((LM_DEBUG,
                "Receiving request from thread <%d> in <%t>\n",
                id));
}

void
Test_i::shutdown (const char *orb_id,
                  CORBA::Environment& ACE_TRY_ENV)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  int argc = 0;
  CORBA::ORB_var orb = CORBA::ORB_init (argc,
                                        0,
                                        orb_id,
                                        ACE_TRY_ENV);
  ACE_CHECK;

  orb->shutdown (0, ACE_TRY_ENV);
  ACE_CHECK;
}
