// -*- C++ -*-
// Time_Date_i.h,v 1.5 1999/06/16 23:01:12 schmidt Exp

// ============================================================================
//
// = LIBRARY
//    TAO/tests/Simple/time_date
//
// = FILENAME
//    Time_Date_i.h
//
// = DESCRIPTION
//    This class implements the Time_Date IDL interface.
//
// = AUTHOR
//    Douglas C. Schmidt <schmidt@cs.wustl.edu> and Michael Kircher.
//
// ============================================================================

#ifndef TIME_DATE_I_H
#define TIME_DATE_I_H

#include "Time_DateS.h"

class Time_Date_i: public POA_Time_Date
{
  // = TITLE
  //    Time_Date object implementation.
  //
  // = DESCRIPTION
  //    Time_Date object implementation
public:
  // = Initialization and termination methods.

  Time_Date_i (void);
  // Constructor

  ~Time_Date_i (void);
  // Destructor

  virtual void bin_date (CORBA::Long_out time_date,
                         CORBA::Environment &)
    ACE_THROW_SPEC ((CORBA::SystemException));

  // Obtain the time and date in binary format.

  virtual void str_date (CORBA::String_out time_date,
                         CORBA::Environment &)
    ACE_THROW_SPEC ((CORBA::SystemException));
  // Obtain the time and date in string format.

  void orb (CORBA::ORB_ptr orb_ptr);
  // ORB pointer.

private:
  CORBA::ORB_var orb_var_;
  // ORB pointer.
};

#endif /* TIME_DATE_I_H */
