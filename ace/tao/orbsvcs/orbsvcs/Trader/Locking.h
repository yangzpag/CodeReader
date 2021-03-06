/* -*- C++ -*- */

// =========================================================================
// Locking.h,v 1.6 2000/03/23 20:52:34 nanbor Exp
//
// = LIBRARY
//    Trading
//
// = FILENAME
//    Locking.h
//
// = AUTHOR
//    Marina Spivak <marina@cs.wustl.edu>
//    Seth Widoff <sbw1@cs.wustl.edu>
//    Irfan Pyarali <irfan@cs.wustl.edu>
//
// ==========================================================================
#ifndef TAO_LOCKING_H
#define TAO_LOCKING_H
#include "ace/pre.h"

#include "tao/corba.h"

// Macros for obtaining read/write locks that are
// automatically released at the end of scope.
// In case of failure, CORBA::SystemException is thrown.

#define TAO_WRITE_GUARD(MUTEX,OBJ,LOCK) \
ACE_Write_Guard<MUTEX> OBJ (LOCK); \
if (OBJ.locked () == 0) \
  TAO_THROW (CORBA::UNKNOWN (TAO_DEFAULT_MINOR_CODE, CORBA::COMPLETED_NO));

#define TAO_READ_GUARD(MUTEX,OBJ,LOCK) \
ACE_Read_Guard<MUTEX> OBJ (LOCK); \
if (OBJ.locked () == 0) \
  TAO_THROW (CORBA::UNKNOWN (TAO_DEFAULT_MINOR_CODE, CORBA::COMPLETED_NO));

#define TAO_WRITE_GUARD_RETURN(MUTEX,OBJ,LOCK,RETURN) \
ACE_Write_Guard<MUTEX> OBJ (LOCK); \
if (OBJ.locked () == 0) \
  TAO_THROW_RETURN (CORBA::UNKNOWN (TAO_DEFAULT_MINOR_CODE, CORBA::COMPLETED_NO), RETURN);

#define TAO_READ_GUARD_RETURN(MUTEX,OBJ,LOCK,RETURN) \
ACE_Read_Guard<MUTEX> OBJ (LOCK); \
if (OBJ.locked () == 0) \
  TAO_THROW_RETURN (CORBA::UNKNOWN (TAO_DEFAULT_MINOR_CODE, CORBA::COMPLETED_NO), RETURN);

#include "ace/post.h"
#endif /* TAO_LOCKING_H */
