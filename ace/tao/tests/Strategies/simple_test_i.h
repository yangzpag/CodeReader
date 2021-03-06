// simple_test_i.h,v 1.1 2000/12/07 20:07:21 doccvs Exp

// ============================================================================
//
// = LIBRARY
//   TAO/tao/Strategies/tests/
//
// = FILENAME
//   simple_test_i.h
//
// = AUTHOR
//     Priyanka Gontla <pgontla@ece.uci.edu>
//
// ============================================================================

#ifndef TAO_STRATEGIES_TEST_I_H
#define TAO_STRATEGIES_TEST_I_H

#include "simple_testS.h"

class Simple_Server_i : public POA_Simple_Server
{
  // = TITLE
  //   Simpler Server implementation
  //
  // = DESCRIPTION
  //   Implements the Simple_Server interface in test.idl
  //
public:
  Simple_Server_i (CORBA::ORB_ptr orb);
  // ctor

  // = The Simple_Server methods.
  CORBA::Boolean print_status (CORBA::Environment&)
    ACE_THROW_SPEC ((CORBA::SystemException));

  void shutdown (CORBA::Environment&)
    ACE_THROW_SPEC ((CORBA::SystemException));

private:
  CORBA::ORB_var orb_;
};

#if defined(__ACE_INLINE__)
#include "simple_test_i.i"
#endif /* __ACE_INLINE__ */

#endif /* TAO_STRATEGIES_I_H */
