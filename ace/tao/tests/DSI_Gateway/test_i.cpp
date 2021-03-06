// test_i.cpp,v 1.5 2001/05/21 20:46:26 kitty Exp

#include "test_i.h"
#include "tao/debug.h"

#if !defined(__ACE_INLINE__)
#include "test_i.i"
#endif /* __ACE_INLINE__ */

ACE_RCSID(DSI_Gateway, test_i, "test_i.cpp,v 1.5 2001/05/21 20:46:26 kitty Exp")

CORBA::Long
Simple_Server_i::test_method (CORBA::Long x,
                              const Structure& the_in_structure,
                              Structure_out the_out_structure,
                              char *&name,
                              CORBA::Environment&)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  Structure *tmp;
  ACE_NEW_RETURN (tmp, Structure (the_in_structure), -1);
  the_out_structure = tmp;

  if (TAO_debug_level > 0)
    {
      ACE_DEBUG ((LM_DEBUG,
                  "Simpler_Server_i ====\n"
                  "    x = %d\n"
                  "    i = %d\n"
                  "    length = %d\n"
                  "    name = <%s>\n",
                  x,
                  the_in_structure.i,
                  the_in_structure.seq.length (),
                  name));
    }

  return x;
}

void
Simple_Server_i::raise_user_exception (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     test_exception))
{
  ACE_THROW (test_exception (33,
                             "reactor meltdown",
                             "kaput"));
}

void
Simple_Server_i::raise_system_exception (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  ACE_THROW (CORBA::NO_PERMISSION ());
}

void
Simple_Server_i::shutdown (CORBA::Environment& ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  this->orb_->shutdown (0, ACE_TRY_ENV);
}
