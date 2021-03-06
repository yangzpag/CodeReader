// server.cpp,v 1.12 2001/03/26 21:16:52 coryan Exp
// ============================================================================
//
// = FILENAME
//    Quoter_Server.cpp
//
// = DESCRIPTION
//    The Server for the Quoter Factory
//
// = AUTHOR
//    Darrell Brunsch (brunsch@cs.wustl.edu)
//    Michael Kircher (mk1@cs.wustl.edu)
//
// ============================================================================

#include "server.h"
#include "tao/ORB_Core.h"

ACE_RCSID(Quoter, server, "server.cpp,v 1.12 2001/03/26 21:16:52 coryan Exp")

Quoter_Server::Quoter_Server (void)
  : num_of_objs_ (1),
    quoter_Factory_i_ptr_ (0),
    debug_level_ (1)
{
}

int
Quoter_Server::parse_args (void)
{
  ACE_Get_Opt get_opts (argc_, argv_, "d:n:");
  int c;

  while ((c = get_opts ()) != -1)
    switch (c)
      {
      case 'd':  // debug flag.
        this->debug_level_ = ACE_OS::atoi (get_opts.optarg);
        break;
      case 'n': // number of Quoter objects we export
        this->num_of_objs_ = ACE_OS::atoi (get_opts.optarg);
        break;
      case '?':
      default:
        ACE_ERROR_RETURN ((LM_ERROR,
                           "usage:  %s"
                           " [-d] <debug level>"
                           " [-n] <num of Quoter objects>"
                           "\n",
                           argv_ [0]),
                          1);
      }


  // Indicates successful parsing of command line.
  return 0;
}


//Initialize the Quoter Server

int
Quoter_Server::init (int argc,
                    char* argv[],
                    CORBA::Environment &ACE_TRY_ENV)
{
  const char *exception_message = "Null Message";
  ACE_TRY
    {
      exception_message = "While ORB Manager init";
      int result = this->orb_manager_.init (argc, argv, ACE_TRY_ENV);
      ACE_TRY_CHECK;

      if (result == -1)
        ACE_ERROR_RETURN ((LM_ERROR,
                           "%p\n",
                           "init"),
                          -1);

      // Copy them, because parse_args expects them there.
      this->argc_ = argc;
      int i;

      // Make a copy of argv since ORB_init will change it.
      this->argv_ = new char *[argc];

      for (i = 0; i < argc; i++)
        this->argv_[i] = argv[i];

      this->parse_args ();

      // Obtain the RootPOA.
      CORBA::Object_var obj =
        this->orb_manager_.orb()->resolve_initial_references ("RootPOA", ACE_TRY_ENV);
      ACE_TRY_CHECK;

      // Get the POA_var object from Object_var.
      exception_message = "While narrowing the root pos";
      PortableServer::POA_var root_poa =
        PortableServer::POA::_narrow (obj.in (), ACE_TRY_ENV);
      ACE_TRY_CHECK;

      // Get the POAManager of the RootPOA.
      exception_message = "While getting the POA Manager";
      PortableServer::POAManager_var poa_manager =
        root_poa->the_POAManager (ACE_TRY_ENV);
      ACE_TRY_CHECK;

      ACE_NEW_RETURN (quoter_Factory_i_ptr_,
                      Quoter_Factory_i(this->num_of_objs_,
                                       root_poa.in()),
                      0);

      exception_message = "While initing the quoter factory";
      quoter_Factory_i_ptr_->init (ACE_TRY_ENV);
      ACE_TRY_CHECK;

      PortableServer::ObjectId_var quoter_Factory_oid =
        PortableServer::string_to_ObjectId ("Quoter_Factory");

      exception_message = "While activating quoter factory";
      root_poa->activate_object_with_id (quoter_Factory_oid.in (),
                                         quoter_Factory_i_ptr_,
                                         ACE_TRY_ENV);
      ACE_TRY_CHECK;

      // Get Object reference for first_foo_impl object.
      exception_message = "While quoter_Factor::_this";
      Stock::Quoter_Factory_var quoter_Factory_var = quoter_Factory_i_ptr_->_this (ACE_TRY_ENV);
      ACE_TRY_CHECK;

      // Stringify the object reference and print it out.
      exception_message = "While object_to_string";
      CORBA::String_var quoter_Factory_ior =
        this->orb_manager_.orb()->object_to_string (quoter_Factory_var.in (), ACE_TRY_ENV);
      ACE_TRY_CHECK;

      exception_message = "While activating the POA Manager";
      poa_manager->activate (ACE_TRY_ENV);
      ACE_TRY_CHECK;

      // Print the IOR.
      if (this->debug_level_ >= 2)
        ACE_DEBUG ((LM_DEBUG, "Quoter Server: IOR is: <%s>\n", quoter_Factory_ior.in ()));
    }
  ACE_CATCHANY
    {
      ACE_ERROR ((LM_ERROR, "Quote_Server::init - %s\n", exception_message));
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Exception");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;

  return this->init_naming_service (ACE_TRY_ENV);
}


// Initialization of Naming Service and register IDL_Quoter Context
// and Quoter_factory object.

int
Quoter_Server::init_naming_service (CORBA::Environment &ACE_TRY_ENV)
{
  const char *exception_message = "Null Message";
  ACE_TRY
    {
      CORBA::ORB_ptr orb_ptr = TAO_ORB_Core_instance()->orb();

      CORBA::Object_var naming_obj =
        orb_ptr->resolve_initial_references ("NameService", ACE_TRY_ENV);
      ACE_TRY_CHECK;

      if (CORBA::is_nil (naming_obj.in ()))
        ACE_ERROR_RETURN ((LM_ERROR,
                                       " (%P|%t) Unable to resolve the Name Service.\n"),
                          -1);

      exception_message = "While narrowing naming context";
      namingContext_var_ =
        CosNaming::NamingContext::_narrow (naming_obj.in (), ACE_TRY_ENV);
      ACE_TRY_CHECK;

      CosNaming::Name quoterContextName (1);
      quoterContextName.length (1);
      quoterContextName[0].id = CORBA::string_dup ("IDL_Quoter");

      exception_message = "While binding a new context";
      CosNaming::NamingContext_var quoterNameContext =
        namingContext_var_->bind_new_context (quoterContextName, ACE_TRY_ENV);
      ACE_TRY_CHECK;

      //Register the quoter_factory name with the IDL_quoter Naming
      //Context...
      CosNaming::Name quoterFactoryContextName (1);
      quoterFactoryContextName.length (1);
      quoterFactoryContextName[0].id = CORBA::string_dup ("Quoter_Factory");

      exception_message = "While using factory _this";
      Stock::Quoter_Factory_var quoter_factory_var = quoter_Factory_i_ptr_->_this (ACE_TRY_ENV);
      ACE_TRY_CHECK;

      exception_message = "While binding factory";
      quoterNameContext->bind (quoterFactoryContextName,
                               quoter_factory_var.in (),
                               ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      ACE_ERROR ((LM_ERROR, "Quote_Server::init_naming_service - %s", exception_message));
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Exception");
      return -1;
    }
  ACE_ENDTRY;

  return 0;
}

int
Quoter_Server::run (CORBA::Environment &ACE_TRY_ENV)
{
  if (this->debug_level_ >= 1)
    ACE_DEBUG ((LM_DEBUG,
                "\nQuoter Example: Quoter_Server is running\n"));

  orb_manager_.orb()->run (ACE_TRY_ENV);
  ACE_CHECK_RETURN (-1);

  return 0;
}

Quoter_Server::~Quoter_Server (void)
{
  ACE_TRY_NEW_ENV
    {
      // Unbind quoter factory context and name.
      CosNaming::Name factory_name (2);
      factory_name.length (2);
      factory_name[0].id = CORBA::string_dup ("IDL_Quoter");
      factory_name[1].id = CORBA::string_dup ("Quoter_Factory");
      if (this->namingContext_var_.ptr () != 0)
        this->namingContext_var_->unbind (factory_name, ACE_TRY_ENV);
      ACE_TRY_CHECK;

      factory_name.length (1);
      if (this->namingContext_var_.ptr () != 0)
        this->namingContext_var_->unbind (factory_name, ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      ACE_ERROR ((LM_ERROR,
                  "Could not unbind Quoter Server from the Name Service\n"));
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "~Quoter_Server");
    }
  ACE_ENDTRY;

  delete [] this->argv_;
}

int
main (int argc, char *argv[])
{
  Quoter_Server quoter_server;

  ACE_TRY_NEW_ENV
    {
      int result = quoter_server.init (argc, argv, ACE_TRY_ENV);
      ACE_TRY_CHECK;

      if (result == -1)
        return 1;

      quoter_server.run (ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, "System Exception");
      return -1;
    }
  ACE_CATCH (CORBA::UserException, userex)
    {
      ACE_PRINT_EXCEPTION (userex, "User Exception");
      return -1;
    }
  ACE_ENDTRY;
  return 0;
}
