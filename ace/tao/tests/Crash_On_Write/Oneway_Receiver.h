//
// Oneway_Receiver.h,v 1.1 2001/04/08 03:58:43 coryan Exp
//

#ifndef ONEWAY_RECEIVER_H
#define ONEWAY_RECEIVER_H
#include "ace/pre.h"

#include "TestS.h"

#if defined (_MSC_VER)
# if (_MSC_VER >= 1200)
#  pragma warning(push)
# endif /* _MSC_VER >= 1200 */
# pragma warning (disable:4250)
#endif /* _MSC_VER */

/// Implement the Test::Oneway_Receiver interface
class Oneway_Receiver
  : public virtual POA_Test::Oneway_Receiver
  , public virtual PortableServer::RefCountServantBase
{
public:
  /// Constructor
  Oneway_Receiver (void);

  // = The skeleton methods
  virtual void receive_oneway (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));
};

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma warning(pop)
#endif /* _MSC_VER */

#include "ace/post.h"
#endif /* ONEWAY_RECEIVER_H */
