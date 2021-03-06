// -*- C++ -*-
// client.cpp,v 1.1 2001/01/02 22:53:08 parsons Exp

#include "ifr_dii_client.h"

ACE_RCSID(Application_Test, client, "client.cpp,v 1.1 2001/01/02 22:53:08 parsons Exp")

int
main (int argc, char *argv[])
{
  IFR_DII_Client client;

  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {
      if (client.init (argc, 
                       argv, 
                       ACE_TRY_ENV) 
           == -1)
        {
          return 1;
        }
      else
        {
          client.run (ACE_TRY_ENV);
          ACE_TRY_CHECK;
        }
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, 
                           "Client Exception");
      return -1;
    }
  ACE_ENDTRY;

  return 0;
}

