//
// Sleep_Service.h,v 1.1 2001/03/31 03:58:21 coryan Exp
//

#ifndef SLEEP_SERVICE_H
#define SLEEP_SERVICE_H
#include "ace/pre.h"

#include "TestS.h"

#if defined (_MSC_VER)
# if (_MSC_VER >= 1200)
#  pragma warning(push)
# endif /* _MSC_VER >= 1200 */
# pragma warning (disable:4250)
#endif /* _MSC_VER */

/// Implement the Test::Sleep_Service interface
class Sleep_Service
  : public virtual POA_Test::Sleep_Service
  , public virtual PortableServer::RefCountServantBase
{
public:
  /// Constructor
  Sleep_Service (CORBA::ORB_ptr orb);

  // = The skeleton methods
  virtual void go_to_sleep (CORBA::ULong microseconds,
                            CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

  virtual void shutdown (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

private:
  /// Use an ORB reference to conver strings to objects and shutdown
  /// the application.
  CORBA::ORB_var orb_;
};

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma warning(pop)
#endif /* _MSC_VER */

#include "ace/post.h"
#endif /* SLEEP_SERVICE_H */
