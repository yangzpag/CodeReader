// This may look like C, but it's really -*- C++ -*-

//=============================================================================
/**
 *  @file    Exception.h
 *
 *  Exception.h,v 1.78 2001/05/15 23:20:21 coryan Exp
 *
 *   This file defines way in which CORBA exceptions are reported.
 *
 *
 *  @author  Copyright 1994-1995 by Sun Microsystems Inc.
 */
//=============================================================================


#ifndef TAO_EXCEPTION_H
#define TAO_EXCEPTION_H
#include "ace/pre.h"

#include "tao/corbafwd.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/SString.h"

// This is used in the implementation of the _raise methods
#if defined (TAO_HAS_EXCEPTIONS)
#define TAO_RAISE(EXCEPTION) throw EXCEPTION
#else
#define TAO_RAISE(EXCEPTION)
#endif /* TAO_HAS_EXCEPTIONS */

#include "ace/SString.h"

class CORBA_Any;
class TAO_OutputCDR;
class TAO_InputCDR;

/**
 * @class CORBA_Exception
 *
 * @brief CORBA_Exception
 *
 * CORBA2-specified exception hierarchy.  All exceptions have a
 * type (represented by a TypeCode) and a widely scoped type ID
 * (in the TypeCode) that generated by any OMG-IDL compiler and
 * available through the Interface Repositories.  Think of it as a
 * "globally scoped" name distinguishing each exception.
 */
class TAO_Export CORBA_Exception
{
public:
  // = Initialization and termination methods.

  /// Copy constructor.
  CORBA_Exception (const CORBA_Exception &src);

  /// Assignment operator.
  CORBA_Exception &operator = (const CORBA_Exception &src);

  /// Destructor.
  virtual ~CORBA_Exception (void);

  // = To throw the exception (when using the standard mapping).
  virtual void _raise (void) = 0;

  // = The static narrow operation.
  static CORBA_Exception *_downcast (CORBA_Exception *x);

  // = These are TAO-specific extensions.

  /// Return the repository ID of the Exception.
  const char *_id (void) const;

  /// Will be overridden in the concrete derived classes.
  virtual CORBA::TypeCode_ptr _type (void) const;

  // = To implement the narrow method.
  virtual int _is_a (const char* repository_id) const;

  /// Constructor from a respository id.
  CORBA_Exception (const char* repository_id);

  /// Print the exception <ex> to output determined by <f>.  This
  /// function is not CORBA compliant.
  void _tao_print_exception (const char *info,
                             FILE *f = stdout) const;

  /// Returns a string containing information about the exception. This
  /// function is not CORBA compliant.
  virtual ACE_CString _info (void) const = 0;

  virtual void _tao_encode (TAO_OutputCDR &cdr,
                            CORBA::Environment &) const = 0;
  virtual void _tao_decode (TAO_InputCDR &cdr,
                            CORBA::Environment &) = 0;

  /// Used in the non-copying Any insertion operator.
  static void _tao_any_destructor (void *);

  // = Methods required for memory management support.
  CORBA::ULong _incr_refcnt (void);
  CORBA::ULong _decr_refcnt (void);

protected:
  CORBA_Exception (void);
  // Default constructor is protected.

private:
  /// Storage of our repository id.
  char *id_;

  /// Reference count to avoid copying overhead.
  CORBA::ULong refcount_;

  /**
   * Mutex to protect the reference count; though in most cases this
   * class is used only in one thread adding a mutex here is *not*
   * expensive, because uses of this class should never be on the
   * critical path.
   */
  TAO_SYNCH_MUTEX refcount_lock_;
};

#if !defined (ACE_LACKS_IOSTREAM_TOTALLY)

// Convenient ostream operator.
TAO_Export ostream& operator<< (ostream &os,
                                const CORBA_Exception &e);

#endif /* (ACE_LACKS_IOSTREAM_TOTALLY) */

/**
 * @class CORBA_UserException
 *
 * @brief User exceptions are those defined by application developers
 * using OMG-IDL.
 */
class TAO_Export CORBA_UserException : public CORBA_Exception
{
public:
  // = Initialization and termination methods.

  /// Copy constructor.
  CORBA_UserException (const CORBA_UserException &src);

  /// Destructor.
  ~CORBA_UserException (void);

  /// Assignment operator.
  CORBA_UserException &operator= (const CORBA_UserException &src);

  /// The narrow operation.
  static CORBA_UserException *_downcast (CORBA_Exception *exception);

  // = TAO specific extension.

  /// Constructor from a repository id.
  CORBA_UserException (const char* repository_id);

  virtual int _is_a (const char *interface_id) const;

  // Used for narrowing

  /// Returns a string containing information about the exception. This
  /// function is not CORBA compliant.
  virtual ACE_CString _info (void) const;

  //protected:
  /// Default constructor.
  CORBA_UserException (void);
};

/**
 * @class CORBA_SystemException
 *
 * @brief CORBA_SystemException
 *
 * System exceptions are those defined in the CORBA spec; OMG-IDL
 * defines these.
 */
class TAO_Export CORBA_SystemException : public CORBA_Exception
{
public:
  // = Initialization and termination methods.

  /// Default constructtor
  CORBA_SystemException (void);

  /// Copy constructor.
  CORBA_SystemException (const CORBA_SystemException &src);

  /// Destructor.
  ~CORBA_SystemException (void);

  /// Assignment operator.
  CORBA_SystemException &operator= (const CORBA_SystemException &src);

  /// Get the minor status.
  CORBA::ULong minor (void) const;

  /// Set the minor status.
  void minor (CORBA::ULong m);

  /// Get the completion status.
  CORBA::CompletionStatus completed (void) const;

  /// Set the operation completion status.
  void completed (CORBA::CompletionStatus c);

  /// Narrow to a SystemException.
  static CORBA_SystemException *_downcast (CORBA_Exception *exception);

  // = TAO-specific extension.

  /// Helper for the _downcast operation.
  virtual int _is_a (const char *type_id) const;

  /// Print the system exception <ex> to output determined by f.  This
  /// function is not CORBA compliant.
  void _tao_print_system_exception (FILE *f = stdout) const;

  /// Returns a string containing information about the exception. This
  /// function is not CORBA compliant.
  virtual ACE_CString _info (void) const;

  virtual void _tao_encode (TAO_OutputCDR &cdr,
                            CORBA::Environment &) const;
  virtual void _tao_decode (TAO_InputCDR &cdr,
                            CORBA::Environment &);

  /// Helper to create a minor status value.
  static CORBA::ULong _tao_minor_code (u_int location,
                                       int errno_value);

  /// Helper to translate a platform-specific errno to a TAO errno
  /// value.
  static CORBA::ULong _tao_errno (int errno_value);

protected:

  /// Constructor using a repository id.
  CORBA_SystemException (const char *repository_id,
                         CORBA::ULong code,
                         CORBA::CompletionStatus completed);

  /// Return the exception description associated with the given OMG
  /// minor code.
  static const char *_tao_get_omg_exception_description (
    const CORBA::SystemException &exc,
    CORBA::ULong minor_code);

private:
  /// Minor code.
  CORBA::ULong minor_;

  /// Completion status.
  CORBA::CompletionStatus completed_;

};

// Declarations for all of the CORBA standard exceptions.
//
// @@ - shouldn't have a default minor code, at least for code that's
// inside the ORB.  All minor codes should be symbolically catalogued.

#define TAO_SYSTEM_EXCEPTION(name) \
class TAO_Export CORBA_ ## name : public CORBA_SystemException { \
public: \
  CORBA_ ## name (void); \
  CORBA_ ## name (CORBA::ULong code, \
                  CORBA::CompletionStatus completed) \
    : CORBA_SystemException ("IDL:omg.org/CORBA/" #name ":1.0", code, completed) \
    { } \
  static CORBA_##name * _downcast (CORBA_Exception* exception); \
  virtual int _is_a (const char* type_id) const; \
  virtual void _raise (void); \
  virtual CORBA::TypeCode_ptr _type (void) const; \
  static void _tao_any_destructor (void*); \
}; \
TAO_Export void operator<<= (CORBA::Any &, const CORBA_##name &); \
TAO_Export void operator<<= (CORBA::Any &, CORBA_##name *); \
TAO_Export CORBA::Boolean operator>>= (const CORBA::Any &, \
                                       const CORBA_##name *&)


TAO_SYSTEM_EXCEPTION(UNKNOWN);          // the unknown exception
TAO_SYSTEM_EXCEPTION(BAD_PARAM);        // an invalid parameter was passed
TAO_SYSTEM_EXCEPTION(NO_MEMORY);        // memory allocation failure
TAO_SYSTEM_EXCEPTION(IMP_LIMIT);        // violated implementation limit
TAO_SYSTEM_EXCEPTION(COMM_FAILURE);     // communication failure
TAO_SYSTEM_EXCEPTION(INV_OBJREF);       // invalid object reference
TAO_SYSTEM_EXCEPTION(OBJECT_NOT_EXIST); // no such object
TAO_SYSTEM_EXCEPTION(NO_PERMISSION);    // no permission for operation
TAO_SYSTEM_EXCEPTION(INTERNAL);         // ORB internal error
TAO_SYSTEM_EXCEPTION(MARSHAL);          // error marshaling param/result
TAO_SYSTEM_EXCEPTION(INITIALIZE);       // ORB initialization failure
TAO_SYSTEM_EXCEPTION(NO_IMPLEMENT);     // implementation unavailable
TAO_SYSTEM_EXCEPTION(BAD_TYPECODE);     // bad typecode
TAO_SYSTEM_EXCEPTION(BAD_OPERATION);    // invalid operation
TAO_SYSTEM_EXCEPTION(NO_RESOURCES);     // out of resources for request
TAO_SYSTEM_EXCEPTION(NO_RESPONSE);      // response not yet available
TAO_SYSTEM_EXCEPTION(PERSIST_STORE);    // persistent storage failure
TAO_SYSTEM_EXCEPTION(BAD_INV_ORDER);    // routine invocations out of order
TAO_SYSTEM_EXCEPTION(TRANSIENT);        // transient error, try again later
TAO_SYSTEM_EXCEPTION(FREE_MEM);         // cannot free memory
TAO_SYSTEM_EXCEPTION(INV_IDENT);        // invalid identifier syntax
TAO_SYSTEM_EXCEPTION(INV_FLAG);         // invalid flag was specified
TAO_SYSTEM_EXCEPTION(INTF_REPOS);       // interface repository unavailable
TAO_SYSTEM_EXCEPTION(BAD_CONTEXT);      // error processing context object
TAO_SYSTEM_EXCEPTION(OBJ_ADAPTER);      // object adapter failure
TAO_SYSTEM_EXCEPTION(DATA_CONVERSION);  // data conversion error
TAO_SYSTEM_EXCEPTION(INV_POLICY);       // invalid policies present
TAO_SYSTEM_EXCEPTION(REBIND);           // rebind needed
TAO_SYSTEM_EXCEPTION(TIMEOUT);          // operation timed out
TAO_SYSTEM_EXCEPTION(TRANSACTION_UNAVAILABLE); // no transaction
TAO_SYSTEM_EXCEPTION(TRANSACTION_MODE);        // invalid transaction mode
TAO_SYSTEM_EXCEPTION(TRANSACTION_REQUIRED);    // operation needs transaction
TAO_SYSTEM_EXCEPTION(TRANSACTION_ROLLEDBACK);  // operation was a no-op
TAO_SYSTEM_EXCEPTION(INVALID_TRANSACTION);     // invalid TP context passed
TAO_SYSTEM_EXCEPTION(CODESET_INCOMPATIBLE);    // incompatible code set
TAO_SYSTEM_EXCEPTION(BAD_QOS);          // bad quality of service

#undef TAO_SYSTEM_EXCEPTION

/**
 * @class TAO_Exceptions
 *
 * @brief This class is a namespace for exception-related static data and
 * methods.
 */
class TAO_Export TAO_Exceptions
{
public:
  /**
   * Make the TypeCode for a standard exception.  When used correctly,
   * initializing system exceptions is only an exercise in CPU time;
   * it allocates no new memory.
   */
  static void make_standard_typecode (CORBA::TypeCode_ptr &tcp,
                                      const char *name,
                                      char *buf,
                                      size_t buflen,
                                      CORBA_Environment &ACE_TRY_ENV =
                                        TAO_default_environment ());

  /// Make the TypeCode for the CORBA::UnknownUserException standard
  /// exception.
  static void make_unknown_user_typecode (CORBA::TypeCode_ptr &tcp,
                                          CORBA_Environment &ACE_TRY_ENV =
                                            TAO_default_environment ());

  /// Runtime initialization of all standard exception typecodes.
  /// Called from <CORBA::ORB_init>.
  static void init (CORBA_Environment &ACE_TRY_ENV =
                      TAO_default_environment ());

  /// Runtime finalization of all standard exception typecodes.
  static void fini (void);

  /// Create a CORBA::SystemException given the interface repository ID.
  static CORBA_SystemException *create_system_exception (
      const char *id,
      CORBA_Environment &ACE_TRY_ENV =
        TAO_default_environment ()
    );

  /**
   * This global allocator is used to initialize system exception
   * typecodes.  Since at the time, the ORB is mostly still not
   * available.  Using a separate allocator prevents CDR routines from
   * accessing the optimized allocators from the ORB.
   */
  static ACE_Allocator *global_allocator_;

private:
  /// Flag that denotes that the TAO's CORBA exceptions have been
  /// initialized.
  static int initialized_;
};

#if defined (TAO_DONT_CATCH_DOT_DOT_DOT)
/**
 * @class TAO_DONT_CATCH
 *
 * @brief This class is only used internally in TAO as an exception
 * that never gets thrown.  Never use this class anywhere.
 */
class TAO_Export TAO_DONT_CATCH
{
public:
  TAO_DONT_CATCH (void);
};
#endif /* TAO_DONT_CATCH_DOT_DOT_DOT */

#if defined (__ACE_INLINE__)
# include "tao/Exception.i"
#endif /* __ACE_INLINE__ */

#include "ace/post.h"
#endif /* TAO_EXCEPTION_H */
