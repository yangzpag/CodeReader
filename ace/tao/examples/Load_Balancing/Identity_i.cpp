/* -*- C++ -*- */
// Identity_i.cpp,v 1.4 2001/04/01 23:58:29 kitty Exp
// ============================================================================
//
// = FILENAME
//   Identity_i.cpp
//
// = DESCRIPTION
//    Implements the interface in Identity.idl.
//
// = AUTHOR
//    Marina Spivak <marina@cs.wustl.edu>
//
// ============================================================================
#include "Identity_i.h"

Identity_i::Identity_i (const char *name)
  : name_ (name)
{
}

Identity_i::~Identity_i (void)
{
}

void
Identity_i::get_name (CORBA::String_out name,
                      CORBA::Environment & )
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  name = this->name_.in ();
}
