// This may look like C, but it's really -*- C++ -*-

//=============================================================================
/**
 *  @file     varbase.h
 *
 *  varbase.h,v 1.2 2000/12/15 20:06:51 coryan Exp
 *
 *   Contains a base class for the object _var classes.
 *
 *
 *  @author  Jeff Parsons.
 */
//=============================================================================


#ifndef TAO_VARBASE_H
#define TAO_VARBASE_H
#include "ace/pre.h"

/**
 * @class TAO_Base_var
 *
 * @brief TAO_Base_var
 *
 * Base class for object _var classes. Used to prevent the
 * _var class of a CORBA interface from accepting the _var
 * of a more derived interface in its copy constructor or
 * assignment operator.
 */
class TAO_Base_var
{
public:
  TAO_Base_var (void) {}
};

#include "ace/post.h"
#endif /* TAO_VARBASE_H */
