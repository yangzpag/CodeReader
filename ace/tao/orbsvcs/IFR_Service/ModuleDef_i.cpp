/* -*- C++ -*- */
// ModuleDef_i.cpp,v 1.5 2001/03/30 16:43:23 parsons Exp

#include "ModuleDef_i.h"
#include "Repository_i.h"

ACE_RCSID(IFR_Service, ModuleDef_i, "ModuleDef_i.cpp,v 1.5 2001/03/30 16:43:23 parsons Exp")

TAO_ModuleDef_i::TAO_ModuleDef_i (TAO_Repository_i *repo,
                                  ACE_Configuration_Section_Key section_key)
  : TAO_IRObject_i (repo, section_key),
    TAO_Container_i (repo, section_key),
    TAO_Contained_i (repo, section_key)
{
}

TAO_ModuleDef_i::~TAO_ModuleDef_i (void)
{
}

CORBA::DefinitionKind
TAO_ModuleDef_i::def_kind (CORBA::Environment &)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  return CORBA::dk_Module;
}

void 
TAO_ModuleDef_i::destroy (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  TAO_IFR_WRITE_GUARD;

  this->destroy_i (ACE_TRY_ENV);
}

void 
TAO_ModuleDef_i::destroy_i (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  // Destroy our members.
  TAO_Container_i::destroy_i (ACE_TRY_ENV);
  ACE_CHECK;
    
  // Destroy ourself.
  TAO_Contained_i::destroy_i (ACE_TRY_ENV);
  ACE_CHECK;
}

CORBA_Contained::Description *
TAO_ModuleDef_i::describe (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  TAO_IFR_READ_GUARD_RETURN (0);

  return this->describe_i (ACE_TRY_ENV);
}

CORBA_Contained::Description *
TAO_ModuleDef_i::describe_i (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  CORBA_Contained::Description *desc_ptr = 0;
  ACE_NEW_THROW_EX (desc_ptr,
                    CORBA_Contained::Description,
                    CORBA::NO_MEMORY ());
  ACE_CHECK_RETURN (0);

  CORBA_Contained::Description_var retval = desc_ptr;

  retval->kind = this->def_kind (ACE_TRY_ENV);
  ACE_CHECK_RETURN (0);

  CORBA_ModuleDescription md;

  md.name = this->name_i (ACE_TRY_ENV);
  ACE_CHECK_RETURN (0);

  md.id = this->id_i (ACE_TRY_ENV);
  ACE_CHECK_RETURN (0);

  ACE_TString container_id;

  this->repo_->config ()->get_string_value (this->section_key_,
                                            "container_id",
                                            container_id);

  md.defined_in = container_id.c_str ();

  md.version = this->version_i (ACE_TRY_ENV);
  ACE_CHECK_RETURN (0);

  retval->value <<= md;

  return retval._retn ();
}

