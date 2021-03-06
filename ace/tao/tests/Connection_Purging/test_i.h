//
// test_i.h,v 1.1 2001/05/17 14:23:58 oci Exp
//

#ifndef TEST_I_H
#define TEST_I_H
#include "ace/pre.h"

#include "testS.h"

#if defined (_MSC_VER)
# if (_MSC_VER >= 1200)
#  pragma warning(push)
# endif /* _MSC_VER >= 1200 */
# pragma warning (disable:4250)
#endif /* _MSC_VER */


class test_i
  : public virtual POA_test
  , public virtual PortableServer::RefCountServantBase
{
public:
  // = The skeleton methods
  virtual void send_stuff (const char* string,
                           CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

private:
};

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma warning(pop)
#endif /* _MSC_VER */

#include "ace/post.h"
#endif /* TEST_I_H */
