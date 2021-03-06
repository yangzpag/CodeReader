// -*- C++ -*-

// ===================================================================
/**
 *  @file   GIOP_Message_Generator_Parser_11.h
 *
 *  GIOP_Message_Generator_Parser_11.h,v 1.2 2000/12/07 23:39:26 bala Exp
 *
 *  @author Balachandran Natarajan <bala@cs.wustl.edu>
 */
// ===================================================================

#ifndef TAO_GIOP_MESSAGE_GENERATOR_PARSER_11_H
#define TAO_GIOP_MESSAGE_GENERATOR_PARSER_11_H
#include "ace/pre.h"
#include "tao/GIOP_Message_Generator_Parser_10.h"


#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#if defined(_MSC_VER)
#if (_MSC_VER >= 1200)
#pragma warning(push)
#endif /* _MSC_VER >= 1200 */
#pragma warning(disable:4250)
#endif /* _MSC_VER */

/**
 * @class TAO_GIOP_Message_Generator_Parser_11
 *
 * @brief Implementation for GIOP v1.1
 *
 *  This just derives from v1.0 class. It uses most of the methods in
 *  the 1.0 class.
 *
 */

class TAO_Export TAO_GIOP_Message_Generator_Parser_11:
  public TAO_GIOP_Message_Generator_Parser_10
{
public:

  /// Our minor version
  virtual CORBA::Octet minor_version (void);

};


#if defined (__ACE_INLINE__)
# include "tao/GIOP_Message_Generator_Parser_11.inl"
#endif /* __ACE_INLINE__ */

#include "ace/post.h"
#endif /*TAO_GIOP_MESSAGE_GENERATOR_PARSER_11_H*/
