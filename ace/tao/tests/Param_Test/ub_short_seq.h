// ub_short_seq.h,v 1.10 2000/03/21 20:04:48 coryan Exp

// ============================================================================
//
// = LIBRARY
//    TAO/tests/Param_Test
//
// = FILENAME
//    ub_short_seq.h
//
// = DESCRIPTION
//     Tests unbounded short sequence
//
// = AUTHORS
//      Aniruddha Gokhale
//
// ============================================================================

#ifndef PARAM_TEST_UNBOUNDED_SHORT_SEQUENCE_H
#define PARAM_TEST_UNBOUNDED_SHORT_SEQUENCE_H

#include "param_testCli.h"

// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
//           test sequences of shorts
// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*

class Test_Short_Sequence
{
public:
  Test_Short_Sequence (void);
  // ctor

  ~Test_Short_Sequence (void);
  // dtor

  int run_sii_test (Param_Test_ptr objref,
                    CORBA::Environment &env);
  // run the SII test

  const char *opname (void) const;
  // return operation name

  int init_parameters (Param_Test_ptr objref,
                       CORBA::Environment &env);
  // set values for parameters

  int reset_parameters (void);
  // reset values for CORBA

  CORBA::Boolean check_validity (void);
  // check if results are valid

  CORBA::Boolean check_validity (CORBA::Request_ptr req);
  // check if results are valid. This is used for DII results

  void print_values (void);
  // print all the values

  void dii_req_invoke (CORBA::Request *, CORBA::Environment &);
  // invoke DII request with appropriate exception handling.

private:
  char *opname_;
  // operation name

  Param_Test::Short_Seq_var in_;
  // in parameter

  Param_Test::Short_Seq_var inout_;
  // inout parameter

  Param_Test::Short_Seq_var out_;
  // out parameter

  Param_Test::Short_Seq_var ret_;
  // return value
};

#endif /* PARAM_TEST_UNBOUNDED_SHORT_SEQUENCE_H */
