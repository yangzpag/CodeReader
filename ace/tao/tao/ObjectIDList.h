/* -*- C++ -*- */
// ObjectIDList.h,v 1.17 2000/03/23 20:52:40 nanbor Exp
// ******  Code generated by the The ACE ORB (TAO) IDL Compiler *******
// TAO and the TAO IDL Compiler have been developed by the Center for
// Distributed Object Computing at Washington University, St. Louis.
//
// Information about TAO is available at:
//                 http://www.cs.wustl.edu/~schmidt/TAO.html
//
//  Hand Modified by Vishal Kachroo <vishal@cs.wustl.edu>
//

#ifndef OBJECTIDLIST_H_
#define OBJECTIDLIST_H_
#include "ace/pre.h"

#include "tao/corbafwd.h"
#include "tao/Sequence.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */


#if defined (TAO_EXPORT_MACRO)
#undef TAO_EXPORT_MACRO
#endif
#define TAO_EXPORT_MACRO
#if defined(_MSC_VER)
#if (_MSC_VER >= 1200)
#pragma warning(push)
#endif /* _MSC_VER >= 1200 */
#pragma warning(disable:4250)
#endif /* _MSC_VER */


#if !defined (_CORBA_ORB_OBJECTIDLIST_CH_)
#define _CORBA_ORB_OBJECTIDLIST_CH_

// *************************************************************
// ObjectIdList
// *************************************************************

class TAO_Export CORBA_ORB_ObjectIdList : public
#if !defined (TAO_USE_SEQUENCE_TEMPLATES)
TAO_Unbounded_String_Sequence
#else /* TAO_USE_SEQUENCE_TEMPLATES */
TAO_Unbounded_String_Sequence
#endif /* !TAO_USE_SEQUENCE_TEMPLATES */
{
public:
 CORBA_ORB_ObjectIdList (void); // default ctor
 CORBA_ORB_ObjectIdList (CORBA::ULong max); // uses max size
 CORBA_ORB_ObjectIdList (
               CORBA::ULong max,
               CORBA::ULong length,
               char * *buffer,
               CORBA::Boolean release=0
               );
 CORBA_ORB_ObjectIdList (const CORBA_ORB_ObjectIdList &); // copy ctor
 ~CORBA_ORB_ObjectIdList (void); // dtor

  static void _tao_any_destructor (void*);
};

typedef CORBA_ORB_ObjectIdList *CORBA_ORB_ObjectIdList_ptr;

#endif /* end #if !defined */

#if !defined (_CORBA_ORB_OBJECTIDLIST___VAR_CH_)
#define _CORBA_ORB_OBJECTIDLIST___VAR_CH_

// *************************************************************
// class CORBA::ORB::ObjectIdList_var
// *************************************************************

class TAO_Export CORBA_ORB_ObjectIdList_var
{
public:
  CORBA_ORB_ObjectIdList_var (void); // default constructor
  CORBA_ORB_ObjectIdList_var (CORBA_ORB_ObjectIdList *);
  CORBA_ORB_ObjectIdList_var (const CORBA_ORB_ObjectIdList_var &); // copy constructor
  ~CORBA_ORB_ObjectIdList_var (void); // destructor

  CORBA_ORB_ObjectIdList_var &operator= (CORBA_ORB_ObjectIdList *);
  CORBA_ORB_ObjectIdList_var &operator= (const CORBA_ORB_ObjectIdList_var &);
  CORBA_ORB_ObjectIdList *operator-> (void);
  const CORBA_ORB_ObjectIdList *operator-> (void) const;

  operator const CORBA_ORB_ObjectIdList &() const;
  operator CORBA_ORB_ObjectIdList &();
  operator CORBA_ORB_ObjectIdList &() const;
  TAO_SeqElem_String_Manager operator[] (CORBA::ULong slot);
  // in, inout, out, _retn
  const CORBA_ORB_ObjectIdList &in (void) const;
  CORBA_ORB_ObjectIdList &inout (void);
  CORBA_ORB_ObjectIdList *&out (void);
  CORBA_ORB_ObjectIdList *_retn (void);
  CORBA_ORB_ObjectIdList *ptr (void) const;

private:
  CORBA_ORB_ObjectIdList *ptr_;
};

#endif /* end #if !defined */


#if !defined (_CORBA_ORB_OBJECTIDLIST___OUT_CH_)
#define _CORBA_ORB_OBJECTIDLIST___OUT_CH_

class TAO_Export CORBA_ORB_ObjectIdList_out
{
public:
  CORBA_ORB_ObjectIdList_out (CORBA_ORB_ObjectIdList *&);
  CORBA_ORB_ObjectIdList_out (CORBA_ORB_ObjectIdList_var &);
  CORBA_ORB_ObjectIdList_out (const CORBA_ORB_ObjectIdList_out &);
  CORBA_ORB_ObjectIdList_out &operator= (const CORBA_ORB_ObjectIdList_out &);
  CORBA_ORB_ObjectIdList_out &operator= (CORBA_ORB_ObjectIdList *);
  operator CORBA_ORB_ObjectIdList *&();
  CORBA_ORB_ObjectIdList *&ptr (void);
  CORBA_ORB_ObjectIdList *operator-> (void);
  TAO_SeqElem_String_Manager operator[] (CORBA::ULong slot);

private:
  CORBA_ORB_ObjectIdList *&ptr_;
  // assignment from T_var not allowed
  void operator= (const CORBA_ORB_ObjectIdList_var &);
};

#endif /* end #if !defined */

TAO_Export CORBA::Boolean operator<< (TAO_OutputCDR &, const CORBA_ORB_ObjectIdList &); //
TAO_Export CORBA::Boolean operator>> (TAO_InputCDR &, CORBA_ORB_ObjectIdList &);

#if defined (__ACE_INLINE__)
#include "tao/ObjectIDList.i"
#endif /* defined INLINE */

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma warning(pop)
#endif /* _MSC_VER */

#include "ace/post.h"
#endif /* ifndef */
