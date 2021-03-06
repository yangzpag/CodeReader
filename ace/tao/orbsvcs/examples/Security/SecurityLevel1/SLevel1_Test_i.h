// SLevel1_Test_i.h,v 1.1 2001/01/19 21:59:03 doccvs Exp

// ============================================================================
//
// = LIBRARY
//   orbsvcs/examples/Security/SecurityLevel1
//
// = FILENAME
//   SLevel1_Test_i.h
//
// = AUTHOR
//   Priyanka Gontla <gontla_p@ociweb.com>
//
// ============================================================================

#ifndef TAO_SLEVEL1_TEST_I_H
#define TAO_SLEVEL1_TEST_I_H

#include "SLevel1_TestS.h"

class SLevel1_Server_i : public POA_SLevel1_Server
{
 public:
  /// Constructor
  SLevel1_Server_i ();

  ///
  CORBA::Boolean authorize_level1 (CORBA::Environment &)
    ACE_THROW_SPEC ((CORBA::SystemException));

  CORBA::Boolean authorize_level2 (CORBA::Environment &)
    ACE_THROW_SPEC ((CORBA::SystemException));

  static int authorized_1;
  static int authorized_2;

};

#endif /* TAO_SLEVEL1_TEST_I_H */
