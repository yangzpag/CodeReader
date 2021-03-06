// timeout_i.h,v 1.3 2001/03/14 20:50:02 mk1 Exp

// ============================================================================
//
// = LIBRARY
//    TAO/tests/AMI_Timeouts
//
// = FILENAME
//    timeout_i.h
//
// = DESCRIPTION
//    Implements the CORBA object.
//
// = AUTHOR
//    Michael Kircher <Michael.Kircher@mchp.siemens.de>
//
// ============================================================================

#ifndef TIMEOUT_I_H
#define TIMEOUT_I_H

#include "ace/High_Res_Timer.h"
#include "tao/corba.h"

#include "timeoutS.h"

class Timeout_i
: public POA_TimeoutObj
{
public:
  Timeout_i (CORBA::ORB_ptr orb);

  ~Timeout_i ();

  virtual void sendTimeToWait (CORBA::Long msec,
                               CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

  virtual void shutdown (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

private:

  CORBA::ORB_var orb_;
};

class TimeoutHandler_i
: public POA_AMI_TimeoutObjHandler
{
public:
  TimeoutHandler_i ();

  ~TimeoutHandler_i ();

  virtual void sendTimeToWait (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

  virtual void sendTimeToWait_excep (
      AMI_TimeoutObjExceptionHolder * excep_holder,
      CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

  void reset_reply_counter ();

  void reset_reply_excep_counter ();

  unsigned short reply_counter ();

  unsigned short reply_excep_counter ();

  /// Start the time measurement
  void start ();

  /// Return the elapsed time
  ACE_Time_Value &elapsed_time ();

private:
  unsigned short reply_counter_;

  unsigned short reply_excep_counter_;

  ACE_High_Res_Timer timer_;

  ACE_Time_Value elapsed_time_;
};

#endif /* TIMEOUT_I_H */
