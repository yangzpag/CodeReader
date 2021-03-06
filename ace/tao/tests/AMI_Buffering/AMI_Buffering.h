//
// AMI_Buffering.h,v 1.2 2001/04/24 08:02:56 coryan Exp
//

#ifndef AMI_BUFFERING_H
#define AMI_BUFFERING_H
#include "ace/pre.h"

#include "TestS.h"

#if defined (_MSC_VER)
# if (_MSC_VER >= 1200)
#  pragma warning(push)
# endif /* _MSC_VER >= 1200 */
# pragma warning (disable:4250)
#endif /* _MSC_VER */

/// Implement the Test::AMI_Buffering interface
class AMI_Buffering
  : public virtual POA_Test::AMI_Buffering
  , public virtual PortableServer::RefCountServantBase
{
public:
  /// Constructor
  AMI_Buffering (CORBA::ORB_ptr orb,
                 Test::AMI_Buffering_Admin_ptr admin);

  // = The skeleton methods
  virtual void receive_data (const Test::Payload &the_payload,
                             CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

  virtual void flush (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

  virtual void sync (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

  virtual void shutdown (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

private:
  /// Use an ORB reference to shutdown the application.
  CORBA::ORB_var orb_;

  /// Report request progress to this interface
  Test::AMI_Buffering_Admin_var admin_;
};

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma warning(pop)
#endif /* _MSC_VER */

#include "ace/post.h"
#endif /* AMI_BUFFERING_H */
