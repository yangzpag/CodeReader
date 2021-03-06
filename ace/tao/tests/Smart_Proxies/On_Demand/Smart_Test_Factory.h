// Smart_Test_Factory.h,v 1.2 2001/03/26 21:17:13 coryan Exp

#include "Smart_Proxy_Impl.h"
#include "ace/Service_Object.h"

class ACE_Svc_Export Smart_Test_Factory
  : public virtual TAO_Test_Default_Proxy_Factory,
    public ACE_Service_Object

{
public:

  Smart_Test_Factory (void);

  virtual Test_ptr create_proxy (Test_ptr proxy,
                                 CORBA::Environment &env =
                                 TAO_default_environment ());
  // This method will create the smart_proxy.
};

// The following Factory is used by the <ACE_Service_Config> to
// dynamically initialize the state of the Smart_Proxy_Factory
ACE_SVC_FACTORY_DECLARE (Smart_Test_Factory)
