// ub_wstring.h,v 1.2 2000/03/21 20:04:48 coryan Exp

// ============================================================================
//
// = LIBRARY
//    TAO/tests/Param_Test
//
// = FILENAME
//    ub_wstring.h
//
// = DESCRIPTION
//     Tests unbounded wide string
//
// = AUTHORS
//      Jeff Parsons <parsons@cs.wustl.edu>
//
// ============================================================================

#ifndef PARAM_TEST_UNBOUNDED_WSTRING_H
#define PARAM_TEST_UNBOUNDED_WSTRING_H

#include "param_testCli.h"

// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
//                        test unbounded wide strings
// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
class Test_Unbounded_WString
{
public:
  Test_Unbounded_WString (void);
  // ctor

  ~Test_Unbounded_WString (void);
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

  void dii_req_invoke (CORBA::Request *,
                       CORBA::Environment &);
  // invoke DII request with appropriate exception handling.

private:
  char *opname_;
  // operation name

  CORBA::WChar *in_;
  // in parameter

  CORBA::WChar *inout_;
  // inout parameter

  CORBA::WChar *out_;
  // out parameter

  CORBA::WChar *ret_;
  // return value
};

#endif /* PARAM_TEST_UNBOUNDED_WSTRING_H */
