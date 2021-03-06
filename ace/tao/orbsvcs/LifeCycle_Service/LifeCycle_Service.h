// LifeCycle_Service.h,v 1.4 2000/09/01 05:05:45 coryan Exp

// ============================================================================
//
// = FILENAME
//    LifeCycle_Service.h
//
// = DESCRIPTION
//    A creation service for objects using the CosLifeCycle GenericFactory.
//
// = AUTHOR
//    Michael Kircher (mk1@cs.wustl.edu)
//
// ============================================================================

#include "ace/Get_Opt.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "tao/PortableServer/ORB_Manager.h"
#include "LifeCycle_Service_i.h"

#ifndef LIFECYCLE_SERVICE_H
#define LIFECYCLE_SERVICE_H

class Life_Cycle_Service_Server
{
  // = TILE
  //   Server object for the LifeCycle Service

public:
  Life_Cycle_Service_Server (void);
  // Default constructor

  ~Life_Cycle_Service_Server (void);
  // Destructor

  int init (int argc,
            char *argv[],
            CORBA::Environment& ACE_TRY_ENV);
  // Initialize the Server state - parsing arguments and ...

  int run (CORBA::Environment& ACE_TRY_ENV);
  // Run the orb.

  u_int parse_args (void);
  // Parse the passed parameters.

private:
  TAO_ORB_Manager orb_manager_;
  // instance of the ORB Manager

  Life_Cycle_Service_i *life_Cycle_Service_i_ptr_;
  // Instance of the creation service

  CosNaming::NamingContext_var namingContext_var_;
  // reference to the naming service

  int argc_;
  // Number of commandline arguments.

  char **argv_;
  // commandline arguments.

  int debug_level_;
  // debug level (0 = quiet, 1 = default, informative, 2+ = noisy);
};

#endif /* LIFECYCLE_SERVICE_H */
