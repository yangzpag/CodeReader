/* -*- C++ -*- Notify_Filter_i.cpp,v 1.21 2001/04/02 19:44:25 pradeep Exp */

#include "Notify_Filter_i.h"
#include "Notify_Constraint_Visitors.h"

#include "tao/debug.h"

#include "ace/Auto_Ptr.h"

ACE_RCSID(Notify, Notify_Filter_i, "Notify_Filter_i.cpp,v 1.21 2001/04/02 19:44:25 pradeep Exp")

// Implementation skeleton constructor
TAO_Notify_Filter_i::TAO_Notify_Filter_i (void)
{
}

// Implementation skeleton destructor
TAO_Notify_Filter_i::~TAO_Notify_Filter_i (void)
{
  ACE_DECLARE_NEW_CORBA_ENV;
  this->remove_all_constraints (ACE_TRY_ENV);
  ACE_CHECK;

  if (TAO_debug_level > 0)
    ACE_DEBUG ((LM_DEBUG, "Filter Destroyed\n"));
}

CosNotifyFilter::Filter_ptr
TAO_Notify_Filter_i::get_ref (CORBA::Environment &ACE_TRY_ENV)
{
  PortableServer::POA_var my_POA = _default_POA ();

  PortableServer::ServantBase_var filter_var (this);

  PortableServer::ObjectId_var oid =
    my_POA->activate_object (this, ACE_TRY_ENV);
  ACE_CHECK_RETURN (CosNotifyFilter::Filter::_nil ());

  CORBA::Object_var obj =
    my_POA->id_to_reference (oid.in (), ACE_TRY_ENV);
  ACE_CHECK_RETURN (CosNotifyFilter::Filter::_nil ());

  return CosNotifyFilter::Filter::_narrow (obj.in (), ACE_TRY_ENV);
}

char*
TAO_Notify_Filter_i::constraint_grammar (
    CORBA::Environment & /* ACE_TRY_ENV */
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return CORBA::string_dup ("TCL");
  // @@pradeep: change this when we support ExTCL.
}

void
TAO_Notify_Filter_i::add_constraints_i (
    const CosNotifyFilter::ConstraintInfoSeq& constraint_info_seq,
    CORBA::Environment &ACE_TRY_ENV
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException,
    CosNotifyFilter::InvalidConstraint
  ))
{
  for (CORBA::ULong index = 0;
       index < constraint_info_seq.length ();
       ++index)
    {
      Notify_Constraint_Expr* notify_constr_expr;

      ACE_TRY
        {
          ACE_NEW_THROW_EX (notify_constr_expr,
                            Notify_Constraint_Expr (),
                            CORBA::NO_MEMORY ());

          const CosNotifyFilter::ConstraintExp& expr =
            constraint_info_seq[index].constraint_expression;

          notify_constr_expr->interpreter.
            build_tree (expr.constraint_expr.in (),
                        ACE_TRY_ENV);
          ACE_TRY_CHECK;

          notify_constr_expr->constr_expr = expr;

          CosNotifyFilter::ConstraintID cnstr_id = constraint_expr_ids_.get ();

          if (constraint_expr_list_.
              bind (cnstr_id, notify_constr_expr) == -1)
            ACE_THROW (CORBA::NO_RESOURCES ());

          constraint_expr_ids_.next (); // commit this id.

        }
      ACE_CATCHANY
        {
          delete notify_constr_expr; // delete the one that failed us.
          ACE_RE_THROW;
        }
      ACE_ENDTRY;
      ACE_CHECK;
    } // for
}

CosNotifyFilter::ConstraintInfoSeq*
TAO_Notify_Filter_i::add_constraints (
    const CosNotifyFilter::ConstraintExpSeq& constraint_list,
    CORBA::Environment &ACE_TRY_ENV
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException,
    CosNotifyFilter::InvalidConstraint
  ))
{
  CORBA::ULong constraint_length = constraint_list.length ();
  if (TAO_debug_level > 0)
    ACE_DEBUG ((LM_DEBUG, "constraint_length = %d\n", constraint_length));
  // create the list that goes out.
  CosNotifyFilter::ConstraintInfoSeq* infoseq;
  ACE_NEW_THROW_EX (infoseq,
                    CosNotifyFilter::ConstraintInfoSeq (constraint_length),
                    CORBA::NO_MEMORY ());
  ACE_CHECK_RETURN (0);

  infoseq->length (constraint_length);

  auto_ptr<CosNotifyFilter::ConstraintInfoSeq> auto_infoseq (infoseq);

  // populate infoseq
  for (CORBA::ULong pop_index = 0;
       pop_index < constraint_length;
       ++pop_index)
    {
      (*infoseq)[pop_index].constraint_expression =
        constraint_list [pop_index];

      if (TAO_debug_level > 0)
        ACE_DEBUG ((LM_DEBUG, "adding constraint %d, %s",
                    pop_index, constraint_list [pop_index].
                    constraint_expr.in ()));
    }

  this->add_constraints_i (*infoseq,
                           ACE_TRY_ENV);
  ACE_CHECK_RETURN (0);

  auto_infoseq.release ();

  return infoseq;
}

void
TAO_Notify_Filter_i::modify_constraints (
    const CosNotifyFilter::ConstraintIDSeq & del_list,
    const CosNotifyFilter::ConstraintInfoSeq & modify_list,
    CORBA::Environment &ACE_TRY_ENV
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException,
    CosNotifyFilter::InvalidConstraint,
    CosNotifyFilter::ConstraintNotFound
  ))
{
  // first check if all the ids are valid.
  u_int index;
  for (index = 0; index < del_list.length (); ++index)
    {
      if (constraint_expr_list_.find (del_list [index]) == -1)
        ACE_THROW (CosNotifyFilter::ConstraintNotFound (del_list [index]));
    }

  for (index = 0; index < modify_list.length (); ++index)
    {
      if (constraint_expr_list_.find (modify_list [index].constraint_id)
          == -1)
        ACE_THROW (CosNotifyFilter::ConstraintNotFound (modify_list [index].constraint_id));
    }

  // remove previous entries and save them in case we need to reinstate them.
  ACE_Array<Notify_Constraint_Expr*> constr_saved (modify_list.length ());
  Notify_Constraint_Expr* constr_expr = 0;

  for (index = 0; index < modify_list.length (); ++index)
    {
      CosNotifyFilter::ConstraintID cnstr_id = modify_list [index].constraint_id;

      if (constraint_expr_list_.unbind (cnstr_id, constr_expr) != -1)
        constr_saved[index] = constr_expr;

      constraint_expr_ids_.put (cnstr_id);
    }

  // now add the new entries.
  // keep a list of ids generated in this session.

  ACE_TRY
    {
      this->add_constraints_i (modify_list,
                               ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      // restore
      for (index = 0; index < modify_list.length (); ++index)
        {
          CosNotifyFilter::ConstraintID cnstr_id = constraint_expr_ids_.get ();

          if (constraint_expr_list_.bind (cnstr_id,
                                          constr_saved[index]) == -1)
            ACE_THROW (CORBA::NO_RESOURCES ());

          constraint_expr_ids_.next (); // commit this id.
        }
      ACE_RE_THROW;
    }
  ACE_ENDTRY;
  ACE_CHECK;

  // now go around deleting...
  // for the del_list
  for (index = 0; index < del_list.length (); ++index)
    {
      if (constraint_expr_list_.unbind (del_list [index],
                                        constr_expr) != -1)
        {
          delete constr_expr;
        }
    }
  // delete the old constraints.
  for (index = 0; index < constr_saved.max_size (); ++index)
    {
      delete constr_saved[index];
    }
}

CosNotifyFilter::ConstraintInfoSeq*
TAO_Notify_Filter_i::get_constraints (const CosNotifyFilter::ConstraintIDSeq & id_list,
                                      CORBA::Environment &ACE_TRY_ENV
                                      )
  ACE_THROW_SPEC ((
                   CORBA::SystemException,
                   CosNotifyFilter::ConstraintNotFound
                   ))
{
  // create the list that goes out.
  CosNotifyFilter::ConstraintInfoSeq* infoseq;
  ACE_NEW_THROW_EX (infoseq,
                    CosNotifyFilter::ConstraintInfoSeq (id_list.length ()),
                    CORBA::NO_MEMORY ());
  ACE_CHECK_RETURN (0);

  auto_ptr<CosNotifyFilter::ConstraintInfoSeq> auto_infoseq (infoseq);

  Notify_Constraint_Expr *notify_constr_expr = 0;
  for (u_int index = 0; index < id_list.length (); ++index)
    {
      if (constraint_expr_list_.find (id_list[index],
                                      notify_constr_expr) == -1)
        ACE_THROW_RETURN (CosNotifyFilter::ConstraintNotFound (id_list[index]),
                          0);

      (*infoseq)[index].constraint_expression =
        notify_constr_expr->constr_expr;

      // Get an id.
      (*infoseq)[index].constraint_id = id_list[index];
    }

  auto_infoseq.release ();
  return infoseq;
}

CosNotifyFilter::ConstraintInfoSeq*
TAO_Notify_Filter_i::get_all_constraints (CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((
                   CORBA::SystemException
                   ))
{
  // create the list that goes out.
  CosNotifyFilter::ConstraintInfoSeq* infoseq;
  ACE_NEW_THROW_EX (infoseq,
                    CosNotifyFilter::ConstraintInfoSeq
                    (constraint_expr_list_.current_size()),
                    CORBA::NO_MEMORY ());
  ACE_CHECK_RETURN (0);

  infoseq->length (constraint_expr_list_.current_size());
  CONSTRAINT_EXPR_LIST_ITER iter (constraint_expr_list_);
  CONSTRAINT_EXPR_ENTRY *entry;

  for (u_int index = 0; iter.done () == 0; iter.advance (), ++index)
    {
      if (iter.next (entry) != 0)
        {
          (*infoseq)[index].constraint_expression =
            ACE_static_cast (const CosNotifyFilter::ConstraintExp,
                             entry->int_id_->constr_expr);

          /*
            Why do we cast to a const object?
            We want to force the TAO_String_Manager to make a copy of the string.
            It wouldn't unless we coax it to use the correct assignment operator.
           */

          (*infoseq)[index].constraint_id = entry->ext_id_;
        }
    }

  return infoseq;
}

void
TAO_Notify_Filter_i::remove_all_constraints (CORBA::Environment &/*ACE_TRY_ENV*/)
  ACE_THROW_SPEC ((
                   CORBA::SystemException
                   ))
{
  CONSTRAINT_EXPR_LIST_ITER iter (constraint_expr_list_);
  CONSTRAINT_EXPR_ENTRY *entry;

  u_int index;
  for (index = 0; iter.done () == 0; iter.advance (), ++index)
    {
      if (iter.next (entry) != 0)
        {
          delete entry->int_id_;
        }
    }

  constraint_expr_list_.unbind_all ();
}

void
TAO_Notify_Filter_i::destroy (CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((
                   CORBA::SystemException
                   ))
{
  this->remove_all_constraints (ACE_TRY_ENV);
  ACE_CHECK;

  PortableServer::POA_var my_POA = _default_POA ();

  PortableServer::ObjectId_var refTemp =
    my_POA->servant_to_id(this);

  my_POA->deactivate_object(refTemp.in());
}

CORBA::Boolean
TAO_Notify_Filter_i::match (const CORBA::Any & /*filterable_data */,
                                           CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((
                   CORBA::SystemException,
                   CosNotifyFilter::UnsupportedFilterableData
                   ))
{
  ACE_THROW_RETURN (CORBA::NO_IMPLEMENT (), 0);
}

CORBA::Boolean
TAO_Notify_Filter_i::match_structured (const CosNotification::StructuredEvent & filterable_data, CORBA::Environment & //ACE_TRY_ENV
                                       )
  ACE_THROW_SPEC ((
                   CORBA::SystemException,
                   CosNotifyFilter::UnsupportedFilterableData
                   ))
{
  // We want to return true if atleast one constraint matches.
  CONSTRAINT_EXPR_LIST_ITER iter (constraint_expr_list_);
  CONSTRAINT_EXPR_ENTRY *entry;

  TAO_Notify_Constraint_Evaluator eval (filterable_data);

  for (; iter.done () == 0; iter.advance ())
    {
      if (iter.next (entry) != 0)
        {
          if (entry->int_id_->interpreter.evaluate (eval) == 1)
            return 1;
        }
    }

  return 0;
}

CORBA::Boolean
TAO_Notify_Filter_i::match_typed (const CosNotification::PropertySeq & /*filterable_data */,CORBA::Environment & ACE_TRY_ENV)
  ACE_THROW_SPEC ((
                   CORBA::SystemException,
                   CosNotifyFilter::UnsupportedFilterableData
                   ))
{
  ACE_THROW_RETURN (CORBA::NO_IMPLEMENT (), 0);
}

CosNotifyFilter::CallbackID
TAO_Notify_Filter_i::attach_callback (CosNotifyComm::NotifySubscribe_ptr /*callback */, CORBA::Environment & ACE_TRY_ENV
                                      )
  ACE_THROW_SPEC ((
                   CORBA::SystemException
                   ))
{
  ACE_THROW_RETURN (CORBA::NO_IMPLEMENT (), 0);
}

void
TAO_Notify_Filter_i::detach_callback (CosNotifyFilter::CallbackID /*callback*/,
                                      CORBA::Environment & ACE_TRY_ENV)
  ACE_THROW_SPEC ((
                   CORBA::SystemException,
                   CosNotifyFilter::CallbackNotFound
                   ))
{
  ACE_THROW (CORBA::NO_IMPLEMENT ());
}

CosNotifyFilter::CallbackIDSeq*
TAO_Notify_Filter_i::get_callbacks (CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((
                   CORBA::SystemException
                   ))
{
  ACE_THROW_RETURN (CORBA::NO_IMPLEMENT (), 0);
}

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)
template class ACE_Hash_Map_Entry<CosNotifyFilter::ConstraintID,TAO_Notify_Filter_i::Notify_Constraint_Expr *>;
template class ACE_Hash_Map_Manager<CosNotifyFilter::ConstraintID,TAO_Notify_Filter_i::Notify_Constraint_Expr*,TAO_SYNCH_MUTEX>;
template class ACE_Hash_Map_Manager_Ex<CosNotifyFilter::ConstraintID,TAO_Notify_Filter_i::Notify_Constraint_Expr*,ACE_Hash<CosNotifyFilter::ConstraintID>, ACE_Equal_To<CosNotifyFilter::ConstraintID>,TAO_SYNCH_MUTEX>;
template class ACE_Hash_Map_Iterator<CosNotifyFilter::ConstraintID,TAO_Notify_Filter_i::Notify_Constraint_Expr*,TAO_SYNCH_MUTEX>;
template class ACE_Hash_Map_Iterator_Ex<CosNotifyFilter::ConstraintID,TAO_Notify_Filter_i::Notify_Constraint_Expr*,ACE_Hash<CosNotifyFilter::ConstraintID>, ACE_Equal_To<CosNotifyFilter::ConstraintID>,TAO_SYNCH_MUTEX>;
template class ACE_Hash_Map_Iterator_Base_Ex<CosNotifyFilter::ConstraintID,TAO_Notify_Filter_i::Notify_Constraint_Expr*,ACE_Hash<CosNotifyFilter::ConstraintID>, ACE_Equal_To<CosNotifyFilter::ConstraintID>,TAO_SYNCH_MUTEX>;
template class ACE_Hash_Map_Reverse_Iterator<CosNotifyFilter::ConstraintID,TAO_Notify_Filter_i::Notify_Constraint_Expr*,TAO_SYNCH_MUTEX>;
template class ACE_Hash_Map_Reverse_Iterator_Ex<CosNotifyFilter::ConstraintID,TAO_Notify_Filter_i::Notify_Constraint_Expr*,ACE_Hash<CosNotifyFilter::ConstraintID>, ACE_Equal_To<CosNotifyFilter::ConstraintID>,TAO_SYNCH_MUTEX>;


template class ACE_Equal_To<CosNotifyFilter::ConstraintID>;

template class ACE_Array<TAO_Notify_Filter_i::Notify_Constraint_Expr*>;
template class ACE_Array_Base<TAO_Notify_Filter_i::Notify_Constraint_Expr*>;

template class auto_ptr<CosNotifyFilter::ConstraintInfoSeq>;
template class ACE_Auto_Basic_Ptr<CosNotifyFilter::ConstraintInfoSeq>;

#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)

#pragma instantiate ACE_Hash_Map_Entry<CosNotifyFilter::ConstraintID,TAO_Notify_Filter_i::Notify_Constraint_Expr*>
#pragma instantiate ACE_Hash_Map_Manager<CosNotifyFilter::ConstraintID,TAO_Notify_Filter_i::Notify_Constraint_Expr*,TAO_SYNCH_MUTEX>
#pragma instantiate ACE_Hash_Map_Manager_Ex<CosNotifyFilter::ConstraintID,TAO_Notify_Filter_i::Notify_Constraint_Expr*,ACE_Hash<CosNotifyFilter::ConstraintID>, ACE_Equal_To<CosNotifyFilter::ConstraintID>,TAO_SYNCH_MUTEX>
#pragma instantiate ACE_Hash_Map_Iterator<CosNotifyFilter::ConstraintID,TAO_Notify_Filter_i::Notify_Constraint_Expr*,TAO_SYNCH_MUTEX>
#pragma instantiate ACE_Hash_Map_Iterator_Ex<CosNotifyFilter::ConstraintID,TAO_Notify_Filter_i::Notify_Constraint_Expr*,ACE_Hash<CosNotifyFilter::ConstraintID>, ACE_Equal_To<CosNotifyFilter::ConstraintID>,TAO_SYNCH_MUTEX>
#pragma instantiate ACE_Hash_Map_Iterator_Base_Ex<CosNotifyFilter::ConstraintID,TAO_Notify_Filter_i::Notify_Constraint_Expr*,ACE_Hash<CosNotifyFilter::ConstraintID>, ACE_Equal_To<CosNotifyFilter::ConstraintID>,TAO_SYNCH_MUTEX>
#pragma instantiate ACE_Hash_Map_Reverse_Iterator<CosNotifyFilter::ConstraintID,TAO_Notify_Filter_i::Notify_Constraint_Expr*,TAO_SYNCH_MUTEX>
#pragma instantiate ACE_Hash_Map_Reverse_Iterator_Ex<CosNotifyFilter::ConstraintID,TAO_Notify_Filter_i::Notify_Constraint_Expr*,ACE_Hash<CosNotifyFilter::ConstraintID>, ACE_Equal_To<CosNotifyFilter::ConstraintID>,TAO_SYNCH_MUTEX>

#pragma instantiate ACE_Array<TAO_Notify_Filter_i::Notify_Constraint_Expr*>
#pragma instantiate ACE_Array_Base<TAO_Notify_Filter_i::Notify_Constraint_Expr*>

#pragma instantiate auto_ptr<CosNotifyFilter::ConstraintInfoSeq>
#pragma instantiate ACE_Auto_Basic_Ptr<CosNotifyFilter::ConstraintInfoSeq>

#endif /*ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */
