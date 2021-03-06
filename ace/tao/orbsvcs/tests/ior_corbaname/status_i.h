//
// status_i.h,v 1.3 2000/11/21 23:39:44 doccvs Exp
//

#ifndef STATUS_I_H
#define STATUS_I_H

#include "corbanameS.h"

class corbaname_Status_i : public POA_corbaname::Status {
public:
  corbaname_Status_i (CORBA::Environment & =
                     TAO_default_environment());

  CORBA::Boolean print_status (CORBA::Environment & = TAO_default_environment())
    ACE_THROW_SPEC ((CORBA::SystemException));

};

#endif /* STATUS_I_H */
