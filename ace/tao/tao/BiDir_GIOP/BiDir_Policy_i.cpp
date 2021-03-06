// BiDir_Policy_i.cpp,v 1.2 2001/03/30 19:52:13 bala Exp

#include "BiDir_Policy_i.h"
#include "tao/Stub.h"
#include "tao/debug.h"

ACE_RCSID(TAO, BiDir_Policy_i, "BiDir_Policy_i.cpp,v 1.2 2001/03/30 19:52:13 bala Exp")



#if ! defined (__ACE_INLINE__)
#include "BiDir_Policy_i.inl"
#endif /* __ACE_INLINE__ */

TAO_BidirectionalPolicy::TAO_BidirectionalPolicy (
    const BiDirPolicy::BidirectionalPolicyValue  val)
  : value_ (val)
{
}

TAO_BidirectionalPolicy::TAO_BidirectionalPolicy (const TAO_BidirectionalPolicy &rhs)
  : BiDirPolicy::BidirectionalPolicy (),
    TAO_Local_RefCounted_Object (),
    value_ (rhs.value_)
{
}



CORBA::PolicyType
TAO_BidirectionalPolicy::policy_type (CORBA_Environment &)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  // Future policy implementors: notice how this minimizes the
  // footprint of the class.
  return BiDirPolicy::BIDIRECTIONAL_POLICY_TYPE;
}


TAO_BidirectionalPolicy *
TAO_BidirectionalPolicy::clone (void) const
{
  TAO_BidirectionalPolicy *copy = 0;
  ACE_NEW_RETURN (copy,
                  TAO_BidirectionalPolicy (*this),
                  0);
  return copy;
}

CORBA::Policy_ptr
TAO_BidirectionalPolicy::copy (CORBA_Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  // Future policy implementors: notice how the following code is
  // exception safe!

  TAO_BidirectionalPolicy* tmp;
  ACE_NEW_THROW_EX (tmp, TAO_BidirectionalPolicy (*this),
                    CORBA::NO_MEMORY (TAO_DEFAULT_MINOR_CODE,
                                      CORBA::COMPLETED_NO));
  ACE_CHECK_RETURN (CORBA::Policy::_nil ());

  return tmp;
}

void
TAO_BidirectionalPolicy::destroy (CORBA_Environment &)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
}


BiDirPolicy::BidirectionalPolicyValue
TAO_BidirectionalPolicy::value (
    CORBA::Environment &)
  ACE_THROW_SPEC ((
      CORBA::SystemException))
{
  return this->value_;
}
