// ub_wstring.cpp,v 1.5 2001/05/04 17:17:35 parsons Exp

// ============================================================================
//
// = LIBRARY
//    TAO/tests/Param_Test
//
// = FILENAME
//    ub_wstring.cpp
//
// = DESCRIPTION
//    tests unbounded wide strings
//
// = AUTHORS
//      Jeff Parsons <parsons@cs.wustl.edu>
//
// ============================================================================

#include "helper.h"
#include "ub_wstring.h"

ACE_RCSID(Param_Test, ub_wstring, "ub_wstring.cpp,v 1.5 2001/05/04 17:17:35 parsons Exp")

// ************************************************************************
//               Test_Unbounded_WString
// ************************************************************************

Test_Unbounded_WString::Test_Unbounded_WString (void)
  : opname_ (CORBA::string_dup ("test_unbounded_wstring")),
    in_ (0),
    inout_ (0),
    out_ (0),
    ret_ (0)
{
}

Test_Unbounded_WString::~Test_Unbounded_WString (void)
{
  CORBA::string_free (this->opname_);
  CORBA::wstring_free (this->in_);
  CORBA::wstring_free (this->inout_);
  CORBA::wstring_free (this->out_);
  CORBA::wstring_free (this->ret_);
  this->opname_ = 0;
  this->in_ = 0;
  this->inout_ = 0;
  this->out_ = 0;
  this->ret_ = 0;
}

const char *
Test_Unbounded_WString::opname (void) const
{
  return this->opname_;
}

void
Test_Unbounded_WString::dii_req_invoke (CORBA::Request *req,
                                        CORBA::Environment &ACE_TRY_ENV)
{
  req->add_in_arg ("s1") <<= this->in_;
  req->add_inout_arg ("s2") <<= this->inout_;
  req->add_out_arg ("s3") <<= this->out_;

  // The Any arg manages its memory but this class member does not.
  CORBA::wstring_free (this->inout_);

  req->set_return_type (CORBA::_tc_wstring);

  req->invoke (ACE_TRY_ENV);
  ACE_CHECK;

  const CORBA::WChar *tmp;
  req->return_value () >>= tmp;
  this->ret_ = CORBA::wstring_dup (tmp);

  CORBA::NamedValue_ptr o2 =
    req->arguments ()->item (1, ACE_TRY_ENV);
  ACE_CHECK;
  *o2->value () >>= tmp;
  this->inout_ = CORBA::wstring_dup (tmp);

  CORBA::NamedValue_ptr o3 =
    req->arguments ()->item (2, ACE_TRY_ENV);
  ACE_CHECK;
  *o3->value () >>= tmp;
  this->out_ = CORBA::wstring_dup (tmp);
}

int
Test_Unbounded_WString::init_parameters (Param_Test_ptr,
                                         CORBA::Environment &)
{
  Generator *gen = GENERATOR::instance (); // value generator

  // release any previously occupied values
  CORBA::wstring_free (this->in_);
  CORBA::wstring_free (this->inout_);
  CORBA::wstring_free (this->out_);
  CORBA::wstring_free (this->ret_);
  this->in_ = 0;
  this->inout_ = 0;
  this->out_ = 0;
  this->ret_ = 0;

  this->in_ = gen->gen_wstring ();
  this->inout_ = CORBA::wstring_dup (this->in_);
  return 0;
}

int
Test_Unbounded_WString::reset_parameters (void)
{
  // release any previously occupied values
  CORBA::wstring_free (this->inout_);
  CORBA::wstring_free (this->out_);
  CORBA::wstring_free (this->ret_);
  this->inout_ = 0;
  this->out_ = 0;
  this->ret_ = 0;

  this->inout_ = CORBA::wstring_dup (this->in_);
  return 0;
}

int
Test_Unbounded_WString::run_sii_test (Param_Test_ptr objref,
                                      CORBA::Environment &ACE_TRY_ENV)
{
  ACE_TRY
    {
      CORBA::WString_out str_out (this->out_);

      this->ret_ = objref->test_unbounded_wstring (this->in_,
                                                   this->inout_,
                                                   str_out,
                                                   ACE_TRY_ENV);
      ACE_TRY_CHECK;

      return 0;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
                           "Test_Unbounded_WString::run_sii_test\n");

    }
  ACE_ENDTRY;
  return -1;
}

CORBA::Boolean
Test_Unbounded_WString::check_validity (void)
{
  CORBA::ULong len = ACE_OS::wslen (this->in_);

  if (!ACE_OS::wscmp (this->in_, this->out_) &&
      !ACE_OS::wscmp (this->in_, this->ret_) &&
      ACE_OS::wslen (this->inout_) == 2*len &&
      !ACE_OS::wsncmp (this->in_, this->inout_, len) &&
      !ACE_OS::wsncmp (this->in_, &this->inout_[len], len))
    return 1;

  return 0; // otherwise
}

CORBA::Boolean
Test_Unbounded_WString::check_validity (CORBA::Request_ptr )
{
  // No need to retrieve anything because, for all the args and
  // the return, we provided the memory and we own it.
  return this->check_validity ();
}

void
Test_Unbounded_WString::print_values (void)
{
}
