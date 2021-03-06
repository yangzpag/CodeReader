// Naming_Loader.cpp,v 1.9 2001/05/02 00:02:53 bala Exp

// ================================================================
// LIBRARY
//   libTAO_CosNaming.so
//
// DESCRIPTION
//   This class allows for dynamically loading
//   the Naming Service.
//
// AUTHORS
//   Priyanka Gontla <pgontla@ece.uci.edu>
//   Carlos O'Ryan <coryan@uci.edu>
// ================================================================

#include "Naming_Loader.h"
#include "ace/Dynamic_Service.h"

ACE_RCSID (Naming, Naming_Loader, "Naming_Loader.cpp,v 1.9 2001/05/02 00:02:53 bala Exp")

TAO_Naming_Loader::TAO_Naming_Loader (void)
{
  // Constructor
}

TAO_Naming_Loader::~TAO_Naming_Loader (void)
{
  // Destructor
}

int
TAO_Naming_Loader::init (int argc, char *argv[])
{
  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {
      // Initialize the ORB
      CORBA::ORB_var orb =
        CORBA::ORB_init (argc, argv, 0, ACE_TRY_ENV);
      ACE_TRY_CHECK;

      // This function call initializes the Naming Service
      CORBA::Object_var object =
        this->create_object (orb.in (), argc, argv, ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      // @@ Should we log this???
      return -1;
    }
  ACE_ENDTRY;
  return 0;
}

int
TAO_Naming_Loader::fini (void)
{
  // Remove the Naming Service.
  return this->naming_server_.fini ();
}

CORBA::Object_ptr
TAO_Naming_Loader::create_object (CORBA::ORB_ptr orb,
                                  int argc, char *argv[],
                                  CORBA::Environment &)
   ACE_THROW_SPEC ((CORBA::SystemException))
{
  int result;

  // Initializes the Naming Service. Returns -1
  // on an error.
  result = this->naming_server_.init_with_orb (argc,
                                               argv,
                                               orb);
  if (result == -1)
    return CORBA::Object::_nil ();

  return 0;
}

ACE_FACTORY_DEFINE (TAO_Naming, TAO_Naming_Loader)

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)
template class ACE_Dynamic_Service<TAO_Naming_Loader>;
#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)
#pragma instantiate ACE_Dynamic_Service<TAO_Naming_Loader>
#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */
