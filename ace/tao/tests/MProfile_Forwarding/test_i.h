// test_i.h,v 1.2 2000/04/20 16:34:11 coryan Exp

// ============================================================================
//
// = LIBRARY
//
// = FILENAME
//   test_i.h
//
// = AUTHOR
//   Balachandran Natarajan
//
// ============================================================================

#ifndef MPROFILE_FORWARDING_TEST_I_H
#define MPROFILE_FORWARDING_TEST_I_H

#include "testS.h"

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

  Simple_Server_i (void);
  // ctor

  // = The Simple_Server methods.
  void remote_call (CORBA::Environment &)
    ACE_THROW_SPEC ((CORBA::SystemException));

  void shutdown (CORBA::Environment&)
    ACE_THROW_SPEC ((CORBA::SystemException));

 private:
  CORBA::ORB_var orb_;

};

#if defined(__ACE_INLINE__)
#include "test_i.i"
#endif /* __ACE_INLINE__ */

#endif /* TAO_MT_CLIENT_TEST_I_H */
