// CPP-memclient.cpp,v 4.6 2001/05/24 20:36:07 nanbor Exp

// This tests the features of the <ACE_MEM_Connector> and
// <ACE_MEM_Stream> classes.  In addition, it can be used to test the
// oneway and twoway latency and throughput at the socket-level.  This
// is useful as a baseline to compare against ORB-level performance
// for the same types of data.

#include "ace/MEM_Connector.h"
#include "ace/INET_Addr.h"
#include "ace/Thread_Manager.h"
#include "ace/Singleton.h"
#include "ace/Get_Opt.h"
#include "ace/High_Res_Timer.h"
#include "ace/Synch.h"


ACE_RCSID(SOCK_SAP, CPP_inclient, "CPP-memclient.cpp,v 4.6 2001/05/24 20:36:07 nanbor Exp")

static int
run_client (void)
{
  ACE_MEM_Connector connector;
  ACE_MEM_Stream stream;
  ACE_MEM_Addr server_addr (ACE_DEFAULT_SERVER_PORT);

  if (connector.connect (stream, server_addr.get_remote_addr ()) == -1)
    ACE_ERROR_RETURN ((LM_ERROR, "%p\n", "connect"), -1);

  char buf [MAXPATHLEN];
  while (fgets (buf, MAXPATHLEN, stdin) >0)
    {
      stream.send (buf, ACE_OS::strlen (buf)+1);
      stream.recv (buf, MAXPATHLEN);
      ACE_DEBUG ((LM_DEBUG, "Echo: %s\n", buf));
    }

  return 0;
}

int
main (int argc, char *argv[])
{
  ACE_UNUSED_ARG(argc);
  // Initialize the logger.
  ACE_LOG_MSG->open (argv[0]);

  // Run the client
  run_client ();

  return 0;
}

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)
#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)
#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */
