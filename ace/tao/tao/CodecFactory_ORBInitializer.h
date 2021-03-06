// -*- C++ -*-

//=============================================================================
/**
 *  @file CodecFactory_ORBInitializer.h
 *
 *  CodecFactory_ORBInitializer.h,v 1.2 2001/08/13 01:01:38 othman Exp
 *
 *  @author  Ossama Othman <ossama@uci.edu>
 */
//=============================================================================


#ifndef TAO_CODEC_FACTORY_ORB_INITIALIZER_H
#define TAO_CODEC_FACTORY_ORB_INITIALIZER_H

#include "ace/pre.h"

#include "TAO_Export.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "PortableInterceptorC.h"
#include "LocalObject.h"
#include "IOPC.h"

// This is to remove "inherits via dominance" warnings from MSVC.
// MSVC is being a little too paranoid.
#if defined(_MSC_VER)
#if (_MSC_VER >= 1200)
#pragma warning(push)
#endif /* _MSC_VER >= 1200 */
#pragma warning(disable:4250)
#endif /* _MSC_VER */


/**
 * @class TAO_CodecFactory_ORBInitializer
 *
 * @brief ORBInitializer for the CodecFactory support.
 *
 * This class simply registers the CodecFactory object with the ORB
 * resolve_initial_references() mechanism.
 */
class TAO_Export TAO_CodecFactory_ORBInitializer
  : public virtual PortableInterceptor::ORBInitializer,
    public virtual TAO_Local_RefCounted_Object
{
public:

  virtual void pre_init (PortableInterceptor::ORBInitInfo_ptr info
                         TAO_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException));

  virtual void post_init (PortableInterceptor::ORBInitInfo_ptr info
                          TAO_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException));

private:

  /// Instance of the IOP::CodecFactory.
  /**
   * The CodecFactory is stateless and reentrant, so share a single
   * instance between all ORBs.
   */
  IOP::CodecFactory_var codec_factory_;

};

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma warning(pop)
#endif /* _MSC_VER */

#include "ace/post.h"

#endif /* TAO_CODEC_FACTORY_ORB_INITIALIZER_H */
