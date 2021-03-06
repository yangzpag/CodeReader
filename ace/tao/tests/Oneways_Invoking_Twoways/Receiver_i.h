// This may look like C, but it's really -*- C++ -*-
// ===================================================================
/**
 *  @file   Receiver_i.h
 *
 *  Receiver_i.h,v 1.1 2001/06/24 13:54:49 bala Exp
 *
 *  @author Balachandran Natarajan <bala@cs.wustl.edu>
 **/
// ===================================================================

#ifndef TAO_TESTS_ONEWAYS_INVOKING_TWOWAYS_RECEIVER_I_H
#define TAO_TESTS_ONEWAYS_INVOKING_TWOWAYS_RECEIVER_I_H
#include "ace/pre.h"

#include "TestS.h"

#if defined (_MSC_VER)
# if (_MSC_VER >= 1200)
#  pragma warning(push)
# endif /* _MSC_VER >= 1200 */
# pragma warning (disable:4250)
#endif /* _MSC_VER */

/// Implement the Test::Receiver interface
/**
 * Skeleton implementation..
 */

class Receiver_i
  : public virtual POA_Test::Receiver
  , public virtual PortableServer::RefCountServantBase
{
public:
  /// Constructor
  Receiver_i (CORBA::ORB_ptr orb,
              Test::Sender_ptr sender,
              CORBA::ULong iter);

  ///Destructor
  virtual ~Receiver_i (void);

  // = The skeleton methods
  virtual CORBA::Long receive_call (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

  /// Retun the number of calls that every thread would make...
  virtual CORBA::Long get_call_count (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

private:
  /// Our Orb...
  CORBA::ORB_var orb_;

  /// THe sender..
  Test::Sender_var sender_;

  /// Number of invocations to be made on the sender..
  CORBA::ULong iteration_;

  /// Number of calls processed so far..
  CORBA::ULong no_calls_;
};

#include "ace/post.h"
#endif /*TAO_TESTS_ONEWAYS_INVOKING_TWOWAYS_RECEIVER_I_H*/
