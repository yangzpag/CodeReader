//
// AMI_Buffering_Admin.h,v 1.3 2001/05/22 20:44:00 sharath Exp
//

#ifndef AMI_BUFFERING_ADMIN_H
#define AMI_BUFFERING_ADMIN_H
#include "ace/pre.h"

#include "TestS.h"

#if defined (_MSC_VER)
# if (_MSC_VER >= 1200)
#  pragma warning(push)
# endif /* _MSC_VER >= 1200 */
# pragma warning (disable:4250)
#endif /* _MSC_VER */

/// Implement the Test::AMI_Buffering_Admin interface
class AMI_Buffering_Admin
  : public virtual POA_Test::AMI_Buffering_Admin
  , public virtual PortableServer::RefCountServantBase
{
public:
  /// Constructor
  AMI_Buffering_Admin (CORBA::ORB_ptr orb);

  // = The skeleton methods
  virtual CORBA::ULong request_count (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

  virtual CORBA::ULong bytes_received_count (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

  virtual void request_received (CORBA::ULong payload_length,
                                 CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

  virtual void flush (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

  virtual void shutdown (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

private:
  /// Use an ORB reference to shutdown the application.
  CORBA::ORB_var orb_;

  /// Keep track of the number of requests received
  CORBA::ULong request_count_;

  /// Keep track of the number of requests received
  CORBA::ULong bytes_received_count_;
};

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma warning(pop)
#endif /* _MSC_VER */

#include "ace/post.h"
#endif /* AMI_BUFFERING_H */
