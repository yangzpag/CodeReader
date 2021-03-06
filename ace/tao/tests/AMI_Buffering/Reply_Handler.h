//
// Reply_Handler.h,v 1.2 2001/04/24 08:02:57 coryan Exp
//

#ifndef REPLY_HANDLER_H
#define REPLY_HANDLER_H
#include "ace/pre.h"

#include "TestS.h"

#if defined (_MSC_VER)
# if (_MSC_VER >= 1200)
#  pragma warning(push)
# endif /* _MSC_VER >= 1200 */
# pragma warning (disable:4250)
#endif /* _MSC_VER */

/// Implement the AMI_AMI_BufferingHandler interface
class Reply_Handler
  : public virtual POA_Test::AMI_AMI_BufferingHandler
  , public virtual PortableServer::RefCountServantBase
{
public:
  /// Constructor
  Reply_Handler (void);

  // = The skeleton methods
  virtual void receive_data (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));
  virtual void receive_data_excep (Test::AMI_AMI_BufferingExceptionHolder *holder,
                                   CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

  virtual void sync (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));
  virtual void sync_excep (Test::AMI_AMI_BufferingExceptionHolder *holder,
                           CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

  virtual void shutdown (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));
  virtual void shutdown_excep (Test::AMI_AMI_BufferingExceptionHolder *holder,
                               CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));
};

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma warning(pop)
#endif /* _MSC_VER */

#include "ace/post.h"
#endif /* REPLY_HANDLER_H */
