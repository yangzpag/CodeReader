// @(#) BiDir_Adapter.cpp,v 1.5 2001/04/11 23:16:57 bala Exp

#include "tao/BiDir_Adapter.h"
#include "ace/Dynamic_Service.h"

ACE_RCSID(tao, BiDir_Adapter, "BiDir_Adapter.cpp,v 1.5 2001/04/11 23:16:57 bala Exp")


TAO_BiDir_Adapter::~TAO_BiDir_Adapter (void)
{
}

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)

template class ACE_Dynamic_Service<TAO_BiDir_Adapter>;

#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)

#pragma instantiate ACE_Dynamic_Service<TAO_BiDir_Adapter>

#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */


