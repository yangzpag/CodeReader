// -*- c++ -*-
// test_dynunion.cpp,v 1.17 2001/06/13 14:12:49 parsons Exp
// ============================================================================
//
// = LIBRARY
//    TAO/tests/DynAny_Test
//
// = FILENAME
//    test_dynunion.cpp
//
// = DESCRIPTION
//    Implementation of the simple DynUnion test
//
// = AUTHOR
//    Jeff Parsons <parsons@cs.wustl.edu>
//
// ============================================================================

#include "test_dynunion.h"
#include "da_testsC.h"
#include "data.h"
#include "tao/DynamicAny/DynamicAny.h"

Test_DynUnion::Test_DynUnion (CORBA::ORB_var orb)
  : orb_ (orb),
    test_name_ (CORBA::string_dup ("test_dynunion")),
    error_count_ (0)
{
}

Test_DynUnion::~Test_DynUnion (void)
{
  CORBA::string_free (this->test_name_);
  this->test_name_ = 0;
}

const char*
Test_DynUnion::test_name (void) const
{
  return this->test_name_;
}

int
Test_DynUnion::run_test (void)
{
  Data data (this->orb_);

  DynAnyTests::test_union tu;

  ACE_TRY_NEW_ENV
    {
      ACE_DEBUG ((LM_DEBUG,
                 "\t*=*=*=*= %s =*=*=*=*\n",
                 data.labels[12]));

      ACE_DEBUG ((LM_DEBUG,
                 "testing: constructor(Any)/insert/get\n"));

      CORBA::Object_var factory_obj =
        this->orb_->resolve_initial_references ("DynAnyFactory",
                                                ACE_TRY_ENV);
      ACE_TRY_CHECK;

      DynamicAny::DynAnyFactory_var dynany_factory =
        DynamicAny::DynAnyFactory::_narrow (factory_obj.in (),
                                            ACE_TRY_ENV);
      ACE_TRY_CHECK;

      if (CORBA::is_nil (dynany_factory.in ()))
        {
          ACE_ERROR_RETURN ((LM_ERROR,
                             "Nil dynamic any factory after narrow\n"),
                            -1);
        }

      tu._d (DynAnyTests::TE_SECOND);
      tu.tc (data.m_typecode2);
      CORBA_Any in_any1;
      in_any1 <<= tu;
      DynamicAny::DynAny_var dp1 =
        dynany_factory->create_dyn_any (in_any1,
                                        ACE_TRY_ENV);
      ACE_TRY_CHECK;
      DynamicAny::DynUnion_var fa1 =
        DynamicAny::DynUnion::_narrow (dp1.in (),
                                       ACE_TRY_ENV);
      ACE_TRY_CHECK;
      fa1->seek (1,
                 ACE_TRY_ENV);
      ACE_TRY_CHECK;
      fa1->insert_typecode (data.m_typecode1,
                            ACE_TRY_ENV);
      ACE_TRY_CHECK;
      CORBA::TypeCode_var s_out1 = fa1->get_typecode (ACE_TRY_ENV);
      ACE_TRY_CHECK;

      if (s_out1.in ()->equal (data.m_typecode1))
        {
          ACE_DEBUG ((LM_DEBUG,
                     "++ OK ++\n"));
        }
      else
        {
          ++this->error_count_;
        }

      ACE_DEBUG ((LM_DEBUG,
                 "testing: constructor(TypeCode)/from_any/to_any\n"));

      CORBA_Any_var out_any1 = fa1->to_any (ACE_TRY_ENV);
      ACE_TRY_CHECK;
      DynamicAny::DynAny_var ftc1_base =
        dynany_factory->create_dyn_any_from_type_code (DynAnyTests::_tc_test_union,
                                                       ACE_TRY_ENV);
      ACE_TRY_CHECK;

      DynamicAny::DynUnion_var ftc1 =
        DynamicAny::DynUnion::_narrow (ftc1_base.in (),
                                          ACE_TRY_ENV);
      ACE_TRY_CHECK;

      if (CORBA::is_nil (ftc1.in ()))
        {
          ACE_ERROR_RETURN ((LM_ERROR,
                             "DynUnion::_narrow() returned nil\n"),
                            -1);
        }

      ftc1->from_any (out_any1.in (),
                      ACE_TRY_ENV);
      ACE_TRY_CHECK;
      ftc1->seek (1,
                 ACE_TRY_ENV);
      ACE_TRY_CHECK;
      CORBA::TypeCode_var s_out2 = ftc1->get_typecode (ACE_TRY_ENV);
      ACE_TRY_CHECK;

      if (s_out2.in ()->equal (data.m_typecode1))
        {
          ACE_DEBUG ((LM_DEBUG,
                     "++ OK ++\n"));
        }
      else
        {
          ++this->error_count_;
        }

      ACE_DEBUG ((LM_DEBUG,
                 "testing:discriminator/discriminator_kind\n"));

      DynamicAny::DynAny_var dp2 = ftc1->get_discriminator (ACE_TRY_ENV);
      ACE_TRY_CHECK;

      CORBA::TypeCode_var tc2 = dp2->type (ACE_TRY_ENV);
      ACE_TRY_CHECK;

      CORBA::TCKind tc1kind = ftc1->discriminator_kind (ACE_TRY_ENV);
      ACE_TRY_CHECK;
      CORBA::TCKind tc2kind = tc2->kind (ACE_TRY_ENV);
      ACE_TRY_CHECK;

      if (tc2kind == tc1kind)
        {
          ACE_DEBUG ((LM_DEBUG,
                     "++ OK ++\n"));
        }
      else
        {
          ++this->error_count_;
        }

      ACE_DEBUG ((LM_DEBUG,
                 "testing:member/member_kind/member_name\n"));

      DynamicAny::DynAny_var dp3 = ftc1->member (ACE_TRY_ENV);
      ACE_TRY_CHECK;
      CORBA::String_var m_nm = ftc1->member_name (ACE_TRY_ENV);
      ACE_TRY_CHECK;
      CORBA::TCKind tk = ftc1->member_kind (ACE_TRY_ENV);
      ACE_TRY_CHECK;
      CORBA::TypeCode_var tc3 = dp3->get_typecode (ACE_TRY_ENV);
      ACE_TRY_CHECK;

      if (!ACE_OS::strcmp (m_nm.in (), "tc")
          && tk == CORBA::tk_TypeCode
          && data.m_typecode1->equal (tc3.in ()))
        {
          ACE_DEBUG ((LM_DEBUG,
                     "++ OK ++\n"));
        }
      else
        {
          ++this->error_count_;
        }

      ACE_TRY_CHECK;

      ACE_DEBUG ((LM_DEBUG,
                 "testing: set_to_default_member\n"));

      ftc1->set_to_default_member (ACE_TRY_ENV);
      ACE_TRY_CHECK;
      ftc1->seek (1,
                  ACE_TRY_ENV);
      ACE_TRY_CHECK;
      ftc1->insert_short (data.m_short1,
                          ACE_TRY_ENV);
      ACE_TRY_CHECK;
      DynamicAny::DynAny_var mem = ftc1->member (ACE_TRY_ENV);
      ACE_TRY_CHECK;
      CORBA::Short out_s = mem->get_short (ACE_TRY_ENV);
      ACE_TRY_CHECK;

      if (out_s == data.m_short1)
        {
          ACE_DEBUG ((LM_DEBUG,
                      "++ OK ++\n"));
        }
      else
        {
          ++this->error_count_;
        }

      fa1->destroy (ACE_TRY_ENV);
      ACE_TRY_CHECK;
      ftc1->destroy (ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
                           "test_dynunion::run_test");
      return -1;
    }
  ACE_ENDTRY;

  ACE_DEBUG ((LM_DEBUG,
              "\n%d errors\n",
              this->error_count_));

  return 0;
}
