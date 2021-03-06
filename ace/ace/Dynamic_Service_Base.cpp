// Dynamic_Service_Base.cpp,v 4.2 2000/11/19 18:42:08 coryan Exp

#include "ace/Dynamic_Service_Base.h"
#include "ace/Service_Config.h"
#include "ace/Service_Repository.h"
#include "ace/Log_Msg.h"

ACE_RCSID(ace, Dynamic_Service_Base, "Dynamic_Service_Base.cpp,v 4.2 2000/11/19 18:42:08 coryan Exp")

void
ACE_Dynamic_Service_Base::dump (void) const
{
  ACE_TRACE ("ACE_Dynamic_Service_Base::dump");

  ACE_DEBUG ((LM_DEBUG, ACE_BEGIN_DUMP, this));
  ACE_DEBUG ((LM_DEBUG, ACE_LIB_TEXT ("\n")));
  ACE_DEBUG ((LM_DEBUG, ACE_END_DUMP));
}

// Get the instance using <name>.

void *
ACE_Dynamic_Service_Base::instance (const ACE_TCHAR *name)
{
  ACE_TRACE ("ACE_Dynamic_Service_Base::instance");
  const ACE_Service_Type *svc_rec;

  if (ACE_Service_Repository::instance ()->find (name,
                                                 &svc_rec) == -1)
    return 0;

  const ACE_Service_Type_Impl *type = svc_rec->type ();

  if (type == 0)
    return 0;

  void *obj = type->object ();
  return obj;
}
