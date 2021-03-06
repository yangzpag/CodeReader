// Interpreter_Utils_T.cpp,v 1.3 2000/08/28 00:15:15 coryan Exp

#ifndef TAO_INTERPRETER_UTILS_CPP
#define TAO_INTERPRETER_UTILS_CPP

#include "orbsvcs/orbsvcs/Trader/Interpreter_Utils_T.h"
#include "orbsvcs/orbsvcs/Trader/Constraint_Visitors.h"
#include "tao/DynamicAny/DynSequence_i.h"

template <class OPERAND_TYPE> CORBA::Boolean
TAO_find (const CORBA::Any& sequence, const OPERAND_TYPE& element)
{
  CORBA::Boolean return_value = 0;
  TAO_Element_Equal<OPERAND_TYPE> functor;
  TAO_DynSequence_i dyn_seq;

  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {
      dyn_seq.init (sequence, ACE_TRY_ENV);
      ACE_TRY_CHECK;

      CORBA::ULong length =
        dyn_seq.get_length (ACE_TRY_ENV);
      ACE_TRY_CHECK;

      for (CORBA::ULong i = 0; i < length && ! return_value; i++)
        if (functor (dyn_seq, element))
          return_value = 1;
    }
  ACE_CATCHANY
    {
      return 0;
    }
  ACE_ENDTRY;


  return return_value;
}

#endif /* TAO_INTERPRETER_UTILS_CPP */
