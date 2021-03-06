// main.cpp,v 1.1 1999/11/22 23:24:03 kirthika Exp

#include "ace/streams.h"
#include "ace/Get_Opt.h"
#include "Coll_Tester.h"

ACE_RCSID(Collocation, main, "main.cpp,v 1.1 1999/11/22 23:24:03 kirthika Exp")

int main (int argc, char *argv[])
{
  Collocation_Test coll_test;

  ACE_TRY_NEW_ENV
    {
      coll_test.init (argc, argv, ACE_TRY_ENV);
      ACE_TRY_CHECK;

      coll_test.run (ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Uncaught exception: ");
    }
  ACE_ENDTRY;

  return 0;
}
