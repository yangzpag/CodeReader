//Transport_Descriptor_Interface.cpp,v 1.1 2001/03/17 00:53:36 oci Exp

#include "tao/Transport_Descriptor_Interface.h"



#if !defined (__ACE_INLINE__)
# include "tao/Transport_Descriptor_Interface.inl"
#endif /* __ACE_INLINE__ */

ACE_RCSID(tao, Transport_Descriptor_Interface, "Transport_Descriptor_Interface.cpp,v 1.1 2001/03/17 00:53:36 oci Exp")


TAO_Transport_Descriptor_Interface::
    ~TAO_Transport_Descriptor_Interface (void)
{
  if (this->endpoint_from_heap_)
    delete this->endpoint_;
}
