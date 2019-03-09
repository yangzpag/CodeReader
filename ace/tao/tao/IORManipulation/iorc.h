// -*- C++ -*-
//
// IORC.h,v 1.8 2001/08/21 19:00:28 parsons Exp

// ****  Code generated by the The ACE ORB (TAO) IDL Compiler ****
// TAO and the TAO IDL Compiler have been developed by:
//       Center for Distributed Object Computing
//       Washington University
//       St. Louis, MO
//       USA
//       http://www.cs.wustl.edu/~schmidt/doc-center.html
// and
//       Distributed Object Computing Laboratory
//       University of California at Irvine
//       Irvine, CA
//       USA
//       http://doc.ece.uci.edu/
//
// Information about TAO is available at:
//     http://www.cs.wustl.edu/~schmidt/TAO.html

#ifndef _TAO_IDL_ORIG_IORC_H_
#define _TAO_IDL_ORIG_IORC_H_

#include "ace/pre.h"
#include "tao/corbafwd.h"

#ifndef TAO_IORMANIP_SAFE_INCLUDE
#error "You should not include IORC.h directly, use IORManip_Loader.h"
#endif /* !TAO_IORMANIP_SAFE_INCLUDE */

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ior_manip_export.h"
#include "tao/Exception.h"
#include "tao/Object.h"
#include "tao/Environment.h"
#include "tao/Sequence.h"
#include "tao/CDR.h"

#if defined (TAO_EXPORT_MACRO)
#undef TAO_EXPORT_MACRO
#endif
#define TAO_EXPORT_MACRO TAO_IORManip_Export

#if defined (TAO_EXPORT_NESTED_CLASSES)
#  if defined (TAO_EXPORT_NESTED_MACRO)
#    undef TAO_EXPORT_NESTED_MACRO
#  endif /* defined (TAO_EXPORT_NESTED_MACRO) */
#  define TAO_EXPORT_NESTED_MACRO TAO_IORManip_Export
#endif /* TAO_EXPORT_NESTED_CLASSES */

#if defined(_MSC_VER)
#if (_MSC_VER >= 1200)
#pragma warning(push)
#endif /* _MSC_VER >= 1200 */
#pragma warning(disable:4250)
#endif /* _MSC_VER */

#if defined (__BORLANDC__)
#pragma option push -w-rvl -w-rch -w-ccc -w-inl
#endif /* __BORLANDC__ */

TAO_NAMESPACE  TAO_IOP
{

#if !defined (_TAO_IOP_EMPTYPROFILELIST_CH_)
#define _TAO_IOP_EMPTYPROFILELIST_CH_

  class TAO_IORManip_Export EmptyProfileList : public CORBA::UserException
  {
  public:

    EmptyProfileList (void);
    // Default constructor.
    
    EmptyProfileList (const EmptyProfileList &);
    // Copy constructor.
    
    ~EmptyProfileList (void);
    // Destructor.
    
    static void _tao_any_destructor (void*);
    
    EmptyProfileList &operator= (const EmptyProfileList &);
    
    virtual void _raise (void);

    virtual void _tao_encode (
        TAO_OutputCDR &,
        CORBA::Environment &
      ) const;
    
    virtual void _tao_decode (
        TAO_InputCDR &,
        CORBA::Environment &
      );
    
    static EmptyProfileList *_downcast (CORBA::Exception *);


    // = TAO extension.
    static CORBA::Exception *_alloc (void);
    virtual CORBA::TypeCode_ptr _type (void) const;
  }; // Exception TAO_IOP::EmptyProfileList.

  TAO_NAMESPACE_STORAGE_CLASS CORBA::TypeCode_ptr _tc_EmptyProfileList;


#endif /* end #if !defined */


#if !defined (_TAO_IOP_NOTFOUND_CH_)
#define _TAO_IOP_NOTFOUND_CH_

  class TAO_IORManip_Export NotFound : public CORBA::UserException
  {
  public:

    NotFound (void);
    // Default constructor.
    
    NotFound (const NotFound &);
    // Copy constructor.
    
    ~NotFound (void);
    // Destructor.
    
    static void _tao_any_destructor (void*);
    
    NotFound &operator= (const NotFound &);
    
    virtual void _raise (void);

    virtual void _tao_encode (
        TAO_OutputCDR &,
        CORBA::Environment &
      ) const;
    
    virtual void _tao_decode (
        TAO_InputCDR &,
        CORBA::Environment &
      );
    
    static NotFound *_downcast (CORBA::Exception *);


    // = TAO extension.
    static CORBA::Exception *_alloc (void);
    virtual CORBA::TypeCode_ptr _type (void) const;
  }; // Exception TAO_IOP::NotFound.

  TAO_NAMESPACE_STORAGE_CLASS CORBA::TypeCode_ptr _tc_NotFound;


#endif /* end #if !defined */


#if !defined (_TAO_IOP_DUPLICATE_CH_)
#define _TAO_IOP_DUPLICATE_CH_

  class TAO_IORManip_Export Duplicate : public CORBA::UserException
  {
  public:

    Duplicate (void);
    // Default constructor.
    
    Duplicate (const Duplicate &);
    // Copy constructor.
    
    ~Duplicate (void);
    // Destructor.
    
    static void _tao_any_destructor (void*);
    
    Duplicate &operator= (const Duplicate &);
    
    virtual void _raise (void);

    virtual void _tao_encode (
        TAO_OutputCDR &,
        CORBA::Environment &
      ) const;
    
    virtual void _tao_decode (
        TAO_InputCDR &,
        CORBA::Environment &
      );
    
    static Duplicate *_downcast (CORBA::Exception *);


    // = TAO extension.
    static CORBA::Exception *_alloc (void);
    virtual CORBA::TypeCode_ptr _type (void) const;
  }; // Exception TAO_IOP::Duplicate.

  TAO_NAMESPACE_STORAGE_CLASS CORBA::TypeCode_ptr _tc_Duplicate;


#endif /* end #if !defined */


#if !defined (_TAO_IOP_INVALID_IOR_CH_)
#define _TAO_IOP_INVALID_IOR_CH_

  class TAO_IORManip_Export Invalid_IOR : public CORBA::UserException
  {
  public:

    Invalid_IOR (void);
    // Default constructor.
    
    Invalid_IOR (const Invalid_IOR &);
    // Copy constructor.
    
    ~Invalid_IOR (void);
    // Destructor.
    
    static void _tao_any_destructor (void*);
    
    Invalid_IOR &operator= (const Invalid_IOR &);
    
    virtual void _raise (void);

    virtual void _tao_encode (
        TAO_OutputCDR &,
        CORBA::Environment &
      ) const;
    
    virtual void _tao_decode (
        TAO_InputCDR &,
        CORBA::Environment &
      );
    
    static Invalid_IOR *_downcast (CORBA::Exception *);


    // = TAO extension.
    static CORBA::Exception *_alloc (void);
    virtual CORBA::TypeCode_ptr _type (void) const;
  }; // Exception TAO_IOP::Invalid_IOR.

  TAO_NAMESPACE_STORAGE_CLASS CORBA::TypeCode_ptr _tc_Invalid_IOR;


#endif /* end #if !defined */


#if !defined (_TAO_IOP_MULTIPROFILELIST_CH_)
#define _TAO_IOP_MULTIPROFILELIST_CH_

  class TAO_IORManip_Export MultiProfileList : public CORBA::UserException
  {
  public:

    MultiProfileList (void);
    // Default constructor.
    
    MultiProfileList (const MultiProfileList &);
    // Copy constructor.
    
    ~MultiProfileList (void);
    // Destructor.
    
    static void _tao_any_destructor (void*);
    
    MultiProfileList &operator= (const MultiProfileList &);
    
    virtual void _raise (void);

    virtual void _tao_encode (
        TAO_OutputCDR &,
        CORBA::Environment &
      ) const;
    
    virtual void _tao_decode (
        TAO_InputCDR &,
        CORBA::Environment &
      );
    
    static MultiProfileList *_downcast (CORBA::Exception *);


    // = TAO extension.
    static CORBA::Exception *_alloc (void);
    virtual CORBA::TypeCode_ptr _type (void) const;
  }; // Exception TAO_IOP::MultiProfileList.

  TAO_NAMESPACE_STORAGE_CLASS CORBA::TypeCode_ptr _tc_MultiProfileList;


#endif /* end #if !defined */


#if !defined (_TAO_IOP_TAO_IOR_PROPERTY___PTR_CH_)
#define _TAO_IOP_TAO_IOR_PROPERTY___PTR_CH_

  class TAO_IOR_Property;
  typedef TAO_IOR_Property *TAO_IOR_Property_ptr;
  
#endif /* end #if !defined */


#if !defined (_TAO_IOP_TAO_IOR_PROPERTY___VAR_CH_)
#define _TAO_IOP_TAO_IOR_PROPERTY___VAR_CH_

  class TAO_IORManip_Export TAO_IOR_Property_var : public TAO_Base_var
  {
  public:
    TAO_IOR_Property_var (void); // default constructor
    TAO_IOR_Property_var (TAO_IOR_Property_ptr p) : ptr_ (p) {} 
    TAO_IOR_Property_var (const TAO_IOR_Property_var &); // copy constructor
    ~TAO_IOR_Property_var (void); // destructor
    
    TAO_IOR_Property_var &operator= (TAO_IOR_Property_ptr);
    TAO_IOR_Property_var &operator= (const TAO_IOR_Property_var &);
    TAO_IOR_Property_ptr operator-> (void) const;
    
    operator const TAO_IOR_Property_ptr &() const;
    operator TAO_IOR_Property_ptr &();
    // in, inout, out, _retn 
    TAO_IOR_Property_ptr in (void) const;
    TAO_IOR_Property_ptr &inout (void);
    TAO_IOR_Property_ptr &out (void);
    TAO_IOR_Property_ptr _retn (void);
    TAO_IOR_Property_ptr ptr (void) const;
    
    // Hooks used by template sequence and object manager classes
    // for non-defined forward declared interfaces.
    static TAO_IOR_Property_ptr tao_duplicate (TAO_IOR_Property_ptr);
    static void tao_release (TAO_IOR_Property_ptr);
    static TAO_IOR_Property_ptr tao_nil (void);
    static TAO_IOR_Property_ptr tao_narrow (CORBA::Object *, CORBA::Environment &);
    static CORBA::Object * tao_upcast (void *);
  
  private:
    TAO_IOR_Property_ptr ptr_;
    // Unimplemented - prevents widening assignment.
    TAO_IOR_Property_var (const TAO_Base_var &rhs);
    TAO_IOR_Property_var &operator= (const TAO_Base_var &rhs);
  };


#endif /* end #if !defined */


#if !defined (_TAO_IOP_TAO_IOR_PROPERTY___OUT_CH_)
#define _TAO_IOP_TAO_IOR_PROPERTY___OUT_CH_

  class TAO_IORManip_Export TAO_IOR_Property_out
  {
  public:
    TAO_IOR_Property_out (TAO_IOR_Property_ptr &);
    TAO_IOR_Property_out (TAO_IOR_Property_var &);
    TAO_IOR_Property_out (const TAO_IOR_Property_out &);
    TAO_IOR_Property_out &operator= (const TAO_IOR_Property_out &);
    TAO_IOR_Property_out &operator= (const TAO_IOR_Property_var &);
    TAO_IOR_Property_out &operator= (TAO_IOR_Property_ptr);
    operator TAO_IOR_Property_ptr &();
    TAO_IOR_Property_ptr &ptr (void);
    TAO_IOR_Property_ptr operator-> (void);
  
  private:
    TAO_IOR_Property_ptr &ptr_;
  };


#endif /* end #if !defined */


#if !defined (_TAO_IOP_TAO_IOR_PROPERTY_CH_)
#define _TAO_IOP_TAO_IOR_PROPERTY_CH_

class TAO_IORManip_Export TAO_IOR_Property : public virtual CORBA_Object
  {
  public:
  #if !defined(__GNUC__) || !defined (ACE_HAS_GNUG_PRE_2_8)
    typedef TAO_IOR_Property_ptr _ptr_type;
    typedef TAO_IOR_Property_var _var_type;
  #endif /* ! __GNUC__ || g++ >= 2.8 */

  static int _tao_class_id;

    // the static operations
    static TAO_IOR_Property_ptr _duplicate (TAO_IOR_Property_ptr obj);
    static TAO_IOR_Property_ptr _narrow (
        CORBA::Object_ptr obj,
        CORBA::Environment &ACE_TRY_ENV = 
          TAO_default_environment ()
      );
    static TAO_IOR_Property_ptr _unchecked_narrow (
        CORBA::Object_ptr obj,
        CORBA::Environment &ACE_TRY_ENV = 
          TAO_default_environment ()
      );
    static TAO_IOR_Property_ptr _nil (void)
      {
        return (TAO_IOR_Property_ptr)0;
      }

    virtual CORBA::Boolean set_property (
        CORBA::Object_ptr ior,
        CORBA::Environment &ACE_TRY_ENV = 
          TAO_default_environment ()
      )
      ACE_THROW_SPEC ((
        CORBA::SystemException,
        TAO_IOP::Invalid_IOR
      )) = 0;

    virtual CORBA::Boolean set_primary (
        CORBA::Object_ptr ior1,
        CORBA::Object_ptr ior2,
        CORBA::Environment &ACE_TRY_ENV = 
          TAO_default_environment ()
      )
      ACE_THROW_SPEC ((
        CORBA::SystemException,
        TAO_IOP::Duplicate,
        TAO_IOP::NotFound
      )) = 0;

    virtual CORBA::Object_ptr get_primary (
        CORBA::Object_ptr ior,
        CORBA::Environment &ACE_TRY_ENV = 
          TAO_default_environment ()
      )
      ACE_THROW_SPEC ((
        CORBA::SystemException,
        TAO_IOP::NotFound
      )) = 0;

    virtual CORBA::Boolean is_primary_set (
        CORBA::Object_ptr ior,
        CORBA::Environment &ACE_TRY_ENV = 
          TAO_default_environment ()
      )
      ACE_THROW_SPEC ((
        CORBA::SystemException
      )) = 0;

    virtual void *_tao_QueryInterface (ptr_arith_t type);
    
    virtual const char* _interface_repository_id (void) const;

  protected:
    TAO_IOR_Property ();
    
    virtual ~TAO_IOR_Property (void);
  private:
    TAO_IOR_Property (const TAO_IOR_Property &);
    void operator= (const TAO_IOR_Property &);
  };


#endif /* end #if !defined */


#if !defined (_TAO_IOP_TAO_IOR_MANIPULATION___PTR_CH_)
#define _TAO_IOP_TAO_IOR_MANIPULATION___PTR_CH_

  class TAO_IOR_Manipulation;
  typedef TAO_IOR_Manipulation *TAO_IOR_Manipulation_ptr;
  
#endif /* end #if !defined */


#if !defined (_TAO_IOP_TAO_IOR_MANIPULATION___VAR_CH_)
#define _TAO_IOP_TAO_IOR_MANIPULATION___VAR_CH_

  class TAO_IORManip_Export TAO_IOR_Manipulation_var : public TAO_Base_var
  {
  public:
    TAO_IOR_Manipulation_var (void); // default constructor
    TAO_IOR_Manipulation_var (TAO_IOR_Manipulation_ptr p) : ptr_ (p) {} 
    TAO_IOR_Manipulation_var (const TAO_IOR_Manipulation_var &); // copy constructor
    ~TAO_IOR_Manipulation_var (void); // destructor
    
    TAO_IOR_Manipulation_var &operator= (TAO_IOR_Manipulation_ptr);
    TAO_IOR_Manipulation_var &operator= (const TAO_IOR_Manipulation_var &);
    TAO_IOR_Manipulation_ptr operator-> (void) const;
    
    operator const TAO_IOR_Manipulation_ptr &() const;
    operator TAO_IOR_Manipulation_ptr &();
    // in, inout, out, _retn 
    TAO_IOR_Manipulation_ptr in (void) const;
    TAO_IOR_Manipulation_ptr &inout (void);
    TAO_IOR_Manipulation_ptr &out (void);
    TAO_IOR_Manipulation_ptr _retn (void);
    TAO_IOR_Manipulation_ptr ptr (void) const;
    
    // Hooks used by template sequence and object manager classes
    // for non-defined forward declared interfaces.
    static TAO_IOR_Manipulation_ptr tao_duplicate (TAO_IOR_Manipulation_ptr);
    static void tao_release (TAO_IOR_Manipulation_ptr);
    static TAO_IOR_Manipulation_ptr tao_nil (void);
    static TAO_IOR_Manipulation_ptr tao_narrow (CORBA::Object *, CORBA::Environment &);
    static CORBA::Object * tao_upcast (void *);
  
  private:
    TAO_IOR_Manipulation_ptr ptr_;
    // Unimplemented - prevents widening assignment.
    TAO_IOR_Manipulation_var (const TAO_Base_var &rhs);
    TAO_IOR_Manipulation_var &operator= (const TAO_Base_var &rhs);
  };


#endif /* end #if !defined */


#if !defined (_TAO_IOP_TAO_IOR_MANIPULATION___OUT_CH_)
#define _TAO_IOP_TAO_IOR_MANIPULATION___OUT_CH_

  class TAO_IORManip_Export TAO_IOR_Manipulation_out
  {
  public:
    TAO_IOR_Manipulation_out (TAO_IOR_Manipulation_ptr &);
    TAO_IOR_Manipulation_out (TAO_IOR_Manipulation_var &);
    TAO_IOR_Manipulation_out (const TAO_IOR_Manipulation_out &);
    TAO_IOR_Manipulation_out &operator= (const TAO_IOR_Manipulation_out &);
    TAO_IOR_Manipulation_out &operator= (const TAO_IOR_Manipulation_var &);
    TAO_IOR_Manipulation_out &operator= (TAO_IOR_Manipulation_ptr);
    operator TAO_IOR_Manipulation_ptr &();
    TAO_IOR_Manipulation_ptr &ptr (void);
    TAO_IOR_Manipulation_ptr operator-> (void);
  
  private:
    TAO_IOR_Manipulation_ptr &ptr_;
  };


#endif /* end #if !defined */


#if !defined (_TAO_IOP_TAO_IOR_MANIPULATION_CH_)
#define _TAO_IOP_TAO_IOR_MANIPULATION_CH_

class TAO_IORManip_Export TAO_IOR_Manipulation : public virtual CORBA_Object
  {
  public:
  #if !defined(__GNUC__) || !defined (ACE_HAS_GNUG_PRE_2_8)
    typedef TAO_IOR_Manipulation_ptr _ptr_type;
    typedef TAO_IOR_Manipulation_var _var_type;
  #endif /* ! __GNUC__ || g++ >= 2.8 */

  static int _tao_class_id;

    // the static operations
    static TAO_IOR_Manipulation_ptr _duplicate (TAO_IOR_Manipulation_ptr obj);
    static TAO_IOR_Manipulation_ptr _narrow (
        CORBA::Object_ptr obj,
        CORBA::Environment &ACE_TRY_ENV = 
          TAO_default_environment ()
      );
    static TAO_IOR_Manipulation_ptr _unchecked_narrow (
        CORBA::Object_ptr obj,
        CORBA::Environment &ACE_TRY_ENV = 
          TAO_default_environment ()
      );
    static TAO_IOR_Manipulation_ptr _nil (void)
      {
        return (TAO_IOR_Manipulation_ptr)0;
      }


#if !defined (TAO_USE_SEQUENCE_TEMPLATES)
      
#if !defined (__TAO_UNBOUNDED_OBJECT_SEQUENCE_TAO_IOP_TAO_IOR_MANIPULATION_IORLIST_CH_)
#define __TAO_UNBOUNDED_OBJECT_SEQUENCE_TAO_IOP_TAO_IOR_MANIPULATION_IORLIST_CH_

      class TAO_EXPORT_MACRO _TAO_Unbounded_Object_Sequence_TAO_IOP_TAO_IOR_Manipulation_IORList : public TAO_Unbounded_Base_Sequence
      {
      public:
        // = Initialization and termination methods.
        
        _TAO_Unbounded_Object_Sequence_TAO_IOP_TAO_IOR_Manipulation_IORList (void);
        _TAO_Unbounded_Object_Sequence_TAO_IOP_TAO_IOR_Manipulation_IORList (CORBA::ULong maximum);
        _TAO_Unbounded_Object_Sequence_TAO_IOP_TAO_IOR_Manipulation_IORList (CORBA::ULong maximum,
          CORBA::ULong length,
          CORBA::Object* *value,
          CORBA::Boolean release = 0);
        _TAO_Unbounded_Object_Sequence_TAO_IOP_TAO_IOR_Manipulation_IORList(const _TAO_Unbounded_Object_Sequence_TAO_IOP_TAO_IOR_Manipulation_IORList &rhs);
        virtual ~_TAO_Unbounded_Object_Sequence_TAO_IOP_TAO_IOR_Manipulation_IORList (void);
        _TAO_Unbounded_Object_Sequence_TAO_IOP_TAO_IOR_Manipulation_IORList &operator= (const _TAO_Unbounded_Object_Sequence_TAO_IOP_TAO_IOR_Manipulation_IORList &rhs);
        TAO_Object_Manager<CORBA::Object,CORBA::Object_var> operator[] (CORBA::ULong index) const;
        static CORBA::Object **allocbuf (CORBA::ULong nelems);
        static void freebuf (CORBA::Object **buffer);
        // The Base_Sequence functions, please see tao/Sequence.h
        virtual void _allocate_buffer (CORBA::ULong length);
        virtual void _deallocate_buffer (void);
        CORBA::Object* *get_buffer (CORBA::Boolean orphan = 0);
        const CORBA::Object* *get_buffer (void) const;
        virtual void _shrink_buffer (CORBA::ULong nl, CORBA::ULong ol);
        virtual void _downcast (
            void* target,
            CORBA_Object *src,
            CORBA_Environment &ACE_TRY_ENV = 
              TAO_default_environment ()
          );
        virtual CORBA_Object* _upcast (void *src) const;
        
      };

#endif /* end #if !defined */


#endif /* !TAO_USE_SEQUENCE_TEMPLATES */ 
    
#if !defined (_TAO_IOP_TAO_IOR_MANIPULATION_IORLIST_CH_)
#define _TAO_IOP_TAO_IOR_MANIPULATION_IORLIST_CH_

    class IORList;
    class IORList_var;
    
    // *************************************************************
    // IORList
    // *************************************************************
    
    class TAO_IORManip_Export IORList : public 
#if !defined (TAO_USE_SEQUENCE_TEMPLATES)
      _TAO_Unbounded_Object_Sequence_TAO_IOP_TAO_IOR_Manipulation_IORList
#else /* TAO_USE_SEQUENCE_TEMPLATES */
      TAO_Unbounded_Object_Sequence<CORBA::Object,CORBA::Object_var>
#endif /* !TAO_USE_SEQUENCE_TEMPLATES */ 
    {
    public:
      IORList (void); // default ctor
      IORList (CORBA::ULong max); // uses max size
      IORList (
        CORBA::ULong max, 
        CORBA::ULong length, 
        CORBA::Object_ptr *buffer, 
        CORBA::Boolean release = 0
      );
      IORList (const IORList &); // copy ctor
      ~IORList (void);
      static void _tao_any_destructor (void*);

#if !defined(__GNUC__) || !defined (ACE_HAS_GNUG_PRE_2_8)
      typedef IORList_var _var_type;
#endif /* ! __GNUC__ || g++ >= 2.8 */

    };
    
#endif /* end #if !defined */


#if !defined (_TAO_IOP_TAO_IOR_MANIPULATION_IORLIST___VAR_CH_)
#define _TAO_IOP_TAO_IOR_MANIPULATION_IORLIST___VAR_CH_

    // *************************************************************
    // class TAO_IOP::TAO_IOR_Manipulation::IORList_var
    // *************************************************************

    class TAO_IORManip_Export IORList_var
    {
    public:
      IORList_var (void); // default constructor
      IORList_var (IORList *);
      IORList_var (const IORList_var &); // copy constructor
      ~IORList_var (void); // destructor
      
      IORList_var &operator= (IORList *);
      IORList_var &operator= (const IORList_var &);
      IORList *operator-> (void);
      const IORList *operator-> (void) const;
      
      operator const IORList &() const;
      operator IORList &();
      operator IORList &() const;
      operator IORList *&(); // variable-size base types only
      
      TAO_Object_Manager<CORBA::Object,CORBA::Object_var> operator[] (CORBA::ULong index);
      
      // in, inout, out, _retn 
      const IORList &in (void) const;
      IORList &inout (void);
      IORList *&out (void);
      IORList *_retn (void);
      IORList *ptr (void) const;

    private:
      IORList *ptr_;
    };


#endif /* end #if !defined */


#if !defined (_TAO_IOP_TAO_IOR_MANIPULATION_IORLIST___OUT_CH_)
#define _TAO_IOP_TAO_IOR_MANIPULATION_IORLIST___OUT_CH_

    class TAO_IORManip_Export IORList_out
    {
    public:
      IORList_out (IORList *&);
      IORList_out (IORList_var &);
      IORList_out (const IORList_out &);
      IORList_out &operator= (const IORList_out &);
      IORList_out &operator= (IORList *);
      operator IORList *&();
      IORList *&ptr (void);
      IORList *operator-> (void);
      TAO_Object_Manager<CORBA::Object,CORBA::Object_var> operator[] (CORBA::ULong index);
      
    private:
      IORList *&ptr_;
      // assignment from T_var not allowed
      void operator= (const IORList_var &);
    };


#endif /* end #if !defined */

    virtual CORBA::Object_ptr merge_iors (
        const TAO_IOP::TAO_IOR_Manipulation::IORList & iors,
        CORBA::Environment &ACE_TRY_ENV = 
          TAO_default_environment ()
      )
      ACE_THROW_SPEC ((
        CORBA::SystemException,
        TAO_IOP::EmptyProfileList,
        TAO_IOP::Duplicate,
        TAO_IOP::Invalid_IOR
      )) = 0;

    virtual CORBA::Object_ptr add_profiles (
        CORBA::Object_ptr ior1,
        CORBA::Object_ptr ior2,
        CORBA::Environment &ACE_TRY_ENV = 
          TAO_default_environment ()
      )
      ACE_THROW_SPEC ((
        CORBA::SystemException,
        TAO_IOP::EmptyProfileList,
        TAO_IOP::Duplicate,
        TAO_IOP::Invalid_IOR
      )) = 0;

    virtual CORBA::Object_ptr remove_profiles (
        CORBA::Object_ptr ior1,
        CORBA::Object_ptr ior2,
        CORBA::Environment &ACE_TRY_ENV = 
          TAO_default_environment ()
      )
      ACE_THROW_SPEC ((
        CORBA::SystemException,
        TAO_IOP::Invalid_IOR,
        TAO_IOP::EmptyProfileList,
        TAO_IOP::NotFound
      )) = 0;

    virtual CORBA::Boolean set_property (
        TAO_IOP::TAO_IOR_Property_ptr prop,
        CORBA::Object_ptr ior,
        CORBA::Environment &ACE_TRY_ENV = 
          TAO_default_environment ()
      )
      ACE_THROW_SPEC ((
        CORBA::SystemException,
        TAO_IOP::Invalid_IOR,
        TAO_IOP::Duplicate
      )) = 0;

    virtual CORBA::Boolean set_primary (
        TAO_IOP::TAO_IOR_Property_ptr prop,
        CORBA::Object_ptr ior1,
        CORBA::Object_ptr ior2,
        CORBA::Environment &ACE_TRY_ENV = 
          TAO_default_environment ()
      )
      ACE_THROW_SPEC ((
        CORBA::SystemException,
        TAO_IOP::Invalid_IOR,
        TAO_IOP::Duplicate,
        TAO_IOP::MultiProfileList,
        TAO_IOP::NotFound
      )) = 0;

    virtual CORBA::Object_ptr get_primary (
        TAO_IOP::TAO_IOR_Property_ptr prop,
        CORBA::Object_ptr ior,
        CORBA::Environment &ACE_TRY_ENV = 
          TAO_default_environment ()
      )
      ACE_THROW_SPEC ((
        CORBA::SystemException,
        TAO_IOP::NotFound
      )) = 0;

    virtual CORBA::Boolean is_primary_set (
        TAO_IOP::TAO_IOR_Property_ptr prop,
        CORBA::Object_ptr ior,
        CORBA::Environment &ACE_TRY_ENV = 
          TAO_default_environment ()
      )
      ACE_THROW_SPEC ((
        CORBA::SystemException
      )) = 0;

    virtual CORBA::ULong is_in_ior (
        CORBA::Object_ptr ior1,
        CORBA::Object_ptr ior2,
        CORBA::Environment &ACE_TRY_ENV = 
          TAO_default_environment ()
      )
      ACE_THROW_SPEC ((
        CORBA::SystemException,
        TAO_IOP::NotFound
      )) = 0;

    virtual CORBA::ULong get_profile_count (
        CORBA::Object_ptr ior,
        CORBA::Environment &ACE_TRY_ENV = 
          TAO_default_environment ()
      )
      ACE_THROW_SPEC ((
        CORBA::SystemException,
        TAO_IOP::EmptyProfileList
      )) = 0;

    virtual void *_tao_QueryInterface (ptr_arith_t type);
    
    virtual const char* _interface_repository_id (void) const;

  protected:
    TAO_IOR_Manipulation ();
    
    virtual ~TAO_IOR_Manipulation (void);
  private:
    TAO_IOR_Manipulation (const TAO_IOR_Manipulation &);
    void operator= (const TAO_IOR_Manipulation &);
  };


#endif /* end #if !defined */


}
TAO_NAMESPACE_CLOSE // module TAO_IOP

TAO_IORManip_Export void operator<<= (CORBA::Any &, const TAO_IOP::EmptyProfileList &); // copying version
TAO_IORManip_Export void operator<<= (CORBA::Any &, TAO_IOP::EmptyProfileList*); // noncopying version
TAO_IORManip_Export CORBA::Boolean operator>>= (const CORBA::Any &, TAO_IOP::EmptyProfileList *&); // deprecated
TAO_IORManip_Export CORBA::Boolean operator>>= (const CORBA::Any &, const TAO_IOP::EmptyProfileList *&);
TAO_IORManip_Export void operator<<= (CORBA::Any &, const TAO_IOP::NotFound &); // copying version
TAO_IORManip_Export void operator<<= (CORBA::Any &, TAO_IOP::NotFound*); // noncopying version
TAO_IORManip_Export CORBA::Boolean operator>>= (const CORBA::Any &, TAO_IOP::NotFound *&); // deprecated
TAO_IORManip_Export CORBA::Boolean operator>>= (const CORBA::Any &, const TAO_IOP::NotFound *&);
TAO_IORManip_Export void operator<<= (CORBA::Any &, const TAO_IOP::Duplicate &); // copying version
TAO_IORManip_Export void operator<<= (CORBA::Any &, TAO_IOP::Duplicate*); // noncopying version
TAO_IORManip_Export CORBA::Boolean operator>>= (const CORBA::Any &, TAO_IOP::Duplicate *&); // deprecated
TAO_IORManip_Export CORBA::Boolean operator>>= (const CORBA::Any &, const TAO_IOP::Duplicate *&);
TAO_IORManip_Export void operator<<= (CORBA::Any &, const TAO_IOP::Invalid_IOR &); // copying version
TAO_IORManip_Export void operator<<= (CORBA::Any &, TAO_IOP::Invalid_IOR*); // noncopying version
TAO_IORManip_Export CORBA::Boolean operator>>= (const CORBA::Any &, TAO_IOP::Invalid_IOR *&); // deprecated
TAO_IORManip_Export CORBA::Boolean operator>>= (const CORBA::Any &, const TAO_IOP::Invalid_IOR *&);
TAO_IORManip_Export void operator<<= (CORBA::Any &, const TAO_IOP::MultiProfileList &); // copying version
TAO_IORManip_Export void operator<<= (CORBA::Any &, TAO_IOP::MultiProfileList*); // noncopying version
TAO_IORManip_Export CORBA::Boolean operator>>= (const CORBA::Any &, TAO_IOP::MultiProfileList *&); // deprecated
TAO_IORManip_Export CORBA::Boolean operator>>= (const CORBA::Any &, const TAO_IOP::MultiProfileList *&);

#ifndef __ACE_INLINE__

TAO_IORManip_Export CORBA::Boolean operator<< (TAO_OutputCDR &, const TAO_IOP::EmptyProfileList &);
TAO_IORManip_Export CORBA::Boolean operator>> (TAO_InputCDR &, TAO_IOP::EmptyProfileList &);

TAO_IORManip_Export CORBA::Boolean operator<< (TAO_OutputCDR &, const TAO_IOP::NotFound &);
TAO_IORManip_Export CORBA::Boolean operator>> (TAO_InputCDR &, TAO_IOP::NotFound &);

TAO_IORManip_Export CORBA::Boolean operator<< (TAO_OutputCDR &, const TAO_IOP::Duplicate &);
TAO_IORManip_Export CORBA::Boolean operator>> (TAO_InputCDR &, TAO_IOP::Duplicate &);

TAO_IORManip_Export CORBA::Boolean operator<< (TAO_OutputCDR &, const TAO_IOP::Invalid_IOR &);
TAO_IORManip_Export CORBA::Boolean operator>> (TAO_InputCDR &, TAO_IOP::Invalid_IOR &);

TAO_IORManip_Export CORBA::Boolean operator<< (TAO_OutputCDR &, const TAO_IOP::MultiProfileList &);
TAO_IORManip_Export CORBA::Boolean operator>> (TAO_InputCDR &, TAO_IOP::MultiProfileList &);


#endif /* __ACE_INLINE__ */


#if defined (__ACE_INLINE__)
#include "IORC.i"
#endif /* defined INLINE */

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma warning(pop)
#endif /* _MSC_VER */

#if defined (__BORLANDC__)
#pragma option pop
#endif /* __BORLANDC__ */

#include "ace/post.h"
#endif /* ifndef */
