/* -*- C++ -*- */
// Scheduler_Utilities.h,v 1.10 2000/03/23 20:52:17 nanbor Exp

// ============================================================================
//
// = LIBRARY
//    orbsvcs
//
// = FILENAME
//    Scheduler_Utilities.h
//
// = AUTHOR
//     Chris Gill <cdgill@cs.wustl.edu>
//
// ============================================================================

#ifndef ACE_SCHEDULER_UTILITIES_H
#define ACE_SCHEDULER_UTILITIES_H
#include "ace/pre.h"

#include "ace/OS.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "orbsvcs/RtecSchedulerC.h"
#include "orbsvcs/Sched/sched_export.h"

class TAO_RTSched_Export ACE_RT_Info : public RtecScheduler::RT_Info
{
  // = TITLE
  //   Offers a convenient C++ interface to the IDL RT_Info structure.
  //
  // = DESCRIPTION
  //   For performance reasons the RT_Info data is represented as an
  //   IDL structure, this permits sending complete RT_Info's from the
  //   client to the server.  Unfortunately this precludes the usage
  //   of member functions and constructors, this class serves as a
  //   helper to implement those without loosing the performance on
  //   IDL.
public:

  ACE_RT_Info (const char* entry_point,
               RtecScheduler::Time worst_time,
               RtecScheduler::Time typical_time,
               RtecScheduler::Time cached_time,
               RtecScheduler::Period_t period,
               RtecScheduler::Importance_t importance,
               RtecScheduler::Quantum_t quantum,
               CORBA::Long threads);
  // Construct a helper class instance from values for
  // the fields of the IDL struct it wraps.

  ACE_RT_Info (const RtecScheduler::RT_Info& rt_info);
  // Construct a helper class instance from the IDL struct it wraps.

  int add_dependency(RtecScheduler::handle_t dep,
                     int number_of_calls = 1);
  // Add a dependency of one RT_Info upon another.

};

#if defined (__ACE_INLINE__)
#include "orbsvcs/Scheduler_Utilities.i"
#endif /* __ACE_INLINE__ */

#include "ace/post.h"
#endif /* ACE_SCHEDULER_UTILITIES_H */
