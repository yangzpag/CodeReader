// server.cpp,v 1.6 1999/07/22 19:04:58 levine Exp

#include "PP_Test_Server.h"
#include "tao/Timeprobe.h"

ACE_RCSID(IDL_Cubit, server, "server.cpp,v 1.6 1999/07/22 19:04:58 levine Exp")

// This runs the server test.

int
main (int argc, char *argv[])
{
  PP_Test_Server pp_test_server;

  ACE_DEBUG ((LM_DEBUG,
              "\n\tPluggable_Test: server\n\n"));

  ACE_DECLARE_NEW_CORBA_ENV;

  ACE_TRY
    {
      int status = pp_test_server.init (argc,
                                        argv,
                                        ACE_TRY_ENV);
      ACE_TRY_CHECK;

      if (status == -1)
        {
          ACE_ERROR_RETURN ((LM_ERROR,
                             "Initialization Error\n"),
                            -1);
        }
      else
        {
          pp_test_server.run (ACE_TRY_ENV);
          ACE_TRY_CHECK;
        }
    }
  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_UNUSED_ARG (sysex);
      ACE_PRINT_EXCEPTION (sysex,
                           "System Exception");
      return -1;
    }
  ACE_CATCH (CORBA::UserException, userex)
    {
      ACE_UNUSED_ARG (userex);
      ACE_PRINT_EXCEPTION (userex,
                           "User Exception");
      return -1;
    }
  ACE_ENDTRY;
  ACE_TIMEPROBE_PRINT;

  return 0;
}
