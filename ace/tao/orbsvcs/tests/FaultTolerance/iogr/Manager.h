//Manager.h,v 1.3 2001/03/10 19:49:11 coryan Exp
// -*- C++ -*-
// Manager.h,v 1.3 2001/03/10 19:49:11 coryan Exp

// ============================================================================
//
// = LIBRARY
//   test
//
// = FILENAME
//    Manager.h
//
// = DESCRIPTION
//    A manager class that merger IORS and designates primary
//
// = AUTHOR
//     Bala Natarajan <bala@cs.wustl.edu>
//
// ============================================================================
#ifndef TEST_FT_IOGR_MANAGER_H
#define TEST_FT_IOGR_MANAGER_H

#include "tao/ORB.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "tao/Object.h"

#if defined(_MSC_VER)
#if (_MSC_VER >= 1200)
#pragma warning(push)
#endif /* _MSC_VER >= 1200 */
#pragma warning(disable:4250)
#endif /* _MSC_VER */

class Manager
{
public:

  Manager (void);
  // Ctor

  void init (int argc,
             char *argv[],
             CORBA::Environment & ACE_TRY_ENV);

  // Initialize the ORB, POA etc.

  int make_merged_iors (CORBA::Environment &);
  // Merges the different IORS

  int set_properties (CORBA::Environment &);
  // Sets the properties for the profiles

  int run (CORBA::Environment &ACE_TRY_ENV);
  // Run the  ORB event loop..

  int write_to_file (void);
  // Write the merged IOR to a file

  CORBA::ORB_ptr orb (void);
  // Return the pointer to the copy of our ORB
private:
  CORBA::ORB_var orb_;
  // Our ORB

  CORBA::Object_var merged_set_;
  // The merged IOR set
};
#endif /*TEST_FT_IOGR_MANAGER_H */
