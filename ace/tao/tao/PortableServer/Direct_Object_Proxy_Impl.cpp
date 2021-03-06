// Direct_Object_Proxy_Impl.cpp,v 1.4 2001/03/30 16:44:29 parsons Exp

#include "Direct_Object_Proxy_Impl.h"
#include "Object_Adapter.h"
#include "tao/Object.h"

ACE_RCSID(tao, TAO_Direct_Object_Proxy_Impl, "Direct_Object_Proxy_Impl.cpp,v 1.4 2001/03/30 16:44:29 parsons Exp")

TAO_Direct_Object_Proxy_Impl::TAO_Direct_Object_Proxy_Impl (void)
{
  // No-op
}


TAO_Direct_Object_Proxy_Impl::~TAO_Direct_Object_Proxy_Impl (void)
{
  // No-op
}

CORBA::Boolean
TAO_Direct_Object_Proxy_Impl::_is_a (const CORBA::Object_ptr target,
                                     const CORBA::Char *logical_type_id,
                                     CORBA_Environment &ACE_TRY_ENV )
{

  return target->_servant ()->_is_a (logical_type_id,
                                     ACE_TRY_ENV);
}


#if (TAO_HAS_MINIMUM_CORBA == 0)

CORBA::Boolean
TAO_Direct_Object_Proxy_Impl::_non_existent (const CORBA::Object_ptr target,
                                             CORBA_Environment &ACE_TRY_ENV)
{
  CORBA::Boolean _tao_retval = 0;
  ACE_TRY
    {
      if (target->_servant () != 0)
        return target->_servant ()->_non_existent (ACE_TRY_ENV);

      // @@ Maybe we want to change this exception...
      ACE_THROW_RETURN (CORBA::INV_OBJREF (), 0);
    }
  ACE_CATCH (CORBA::OBJECT_NOT_EXIST, ex)
    {
      _tao_retval = 1;
    }
  ACE_CATCHANY
    {
      ACE_RE_THROW;
    }
  ACE_ENDTRY;

  return _tao_retval;
}

CORBA_InterfaceDef_ptr
TAO_Direct_Object_Proxy_Impl::_get_interface (const CORBA::Object_ptr target,
                                              CORBA_Environment &ACE_TRY_ENV)
{
  ACE_TRY
    {
      if (target->_servant () != 0)
        return target->_servant ()->_get_interface (ACE_TRY_ENV);

      // @@ Maybe we want to change this exception...
      ACE_THROW_RETURN (CORBA::INV_OBJREF (), 0);
    }
  ACE_CATCH (CORBA::OBJECT_NOT_EXIST, ex)
    {
    }
  ACE_CATCHANY
    {
      ACE_RE_THROW;
    }
  ACE_ENDTRY;

  return 0;
}

#endif /* TAO_HAS_MINIMUM_CORBA == 0 */
