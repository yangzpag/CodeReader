//
// exception_ctor.cpp,v 1.11 2000/09/29 16:19:16 parsons Exp
//

// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    exception_ctor.cpp
//
// = DESCRIPTION
//    Visitor generating code for the special constructor for Exceptions
//
// = AUTHOR
//    Aniruddha Gokhale
//
// ============================================================================

#include	"idl.h"
#include	"idl_extern.h"
#include	"be.h"

#include "be_visitor_exception.h"

ACE_RCSID(be_visitor_exception, exception_ctor, "exception_ctor.cpp,v 1.11 2000/09/29 16:19:16 parsons Exp")


// ************************************************************************
//  code to generate the special ctor
// ************************************************************************

be_visitor_exception_ctor::be_visitor_exception_ctor
(be_visitor_context *ctx)
  : be_visitor_scope (ctx)
{
}

be_visitor_exception_ctor::~be_visitor_exception_ctor (void)
{
}

int
be_visitor_exception_ctor::post_process (be_decl *bd)
{
  TAO_OutStream *os = this->ctx_->stream (); // get output stream

  if (!this->last_node (bd))
    {
      *os << "," << be_nl;
    }

  return 0;
}

int be_visitor_exception_ctor::visit_exception (be_exception *node)
{
  TAO_OutStream *os = this->ctx_->stream ();
  this->ctx_->node (node);

  os->indent ();

  if (this->ctx_->state () == TAO_CodeGen::TAO_EXCEPTION_CTOR_CH)
    {
      *os << node->local_name ();
    }
  else
    {
      *os << node->name () << "::" << node->local_name ();
    }

  *os << " (" << be_idt << be_idt_nl;

  if (this->visit_scope (node) == -1)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "be_visitor_exception_ctor_assign::"
                         "visit_exception - "
                         "codegen for scope failed\n"),
                        -1);
    }

  if (this->ctx_->state () == TAO_CodeGen::TAO_EXCEPTION_CTOR_CH)
    {
      *os << be_uidt_nl << ");" << be_uidt_nl;
    }
  else
    {
      *os << be_uidt_nl << ")" << be_uidt_nl;
    }

  return 0;
}

int be_visitor_exception_ctor::visit_field (be_field *node)
{
  TAO_OutStream *os = this->ctx_->stream (); // get output stream

  // Retrieve the type.
  be_type *bt = be_type::narrow_from_decl (node->field_type ());

  if (!bt)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "be_visitor_exception_ctor::"
                         "visit_exception - "
                         "Bad field type\n"),
                        -1);
    }

  if (bt->accept (this) == -1)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "be_visitor_exception_ctor::"
                         "visit_field - "
                         "cannot accept visitor\n"),
                        -1);
    }

  *os << " _tao_" << node->local_name ();
  return 0;
}

int be_visitor_exception_ctor::visit_array (be_array *node)
{
  TAO_OutStream *os = this->ctx_->stream (); // get output stream

  // set the right type;
  be_type *bt;
  if (this->ctx_->alias ())
    bt = this->ctx_->alias ();
  else
    bt = node;

  *os << "const ";

  be_typedef *tdef = be_typedef::narrow_from_decl (bt);

  if (this->ctx_->state () != TAO_CodeGen::TAO_EXCEPTION_CTOR_CH
      && !tdef)
    *os << this->ctx_->scope ()->full_name () << "::";

  if (!tdef)
    *os << "_";

  *os << bt->nested_type_name (this->ctx_->scope ());

  return 0;
}

int be_visitor_exception_ctor::visit_enum (be_enum *node)
{
  TAO_OutStream *os = this->ctx_->stream (); // get output stream

  // set the right type;
  be_type *bt;
  if (this->ctx_->alias ())
    bt = this->ctx_->alias ();
  else
    bt = node;

  if (this->ctx_->state () == TAO_CodeGen::TAO_EXCEPTION_CTOR_CH)
    *os << bt->nested_type_name (this->ctx_->scope ());
  else
    *os << bt->name ();
  return 0;
}

int be_visitor_exception_ctor::visit_interface (be_interface *node)
{
  TAO_OutStream *os = this->ctx_->stream (); // get output stream

  // set the right type;
  be_type *bt;
  if (this->ctx_->alias ())
    bt = this->ctx_->alias ();
  else
    bt = node;

  if (this->ctx_->state () == TAO_CodeGen::TAO_EXCEPTION_CTOR_CH)
    *os << "const " << bt->nested_type_name (this->ctx_->scope (), "_ptr ");
  else
    *os << "const " << bt->name () << "_ptr ";
  return 0;
}

int be_visitor_exception_ctor::visit_interface_fwd (be_interface_fwd *node)
{
  TAO_OutStream *os = this->ctx_->stream (); // get output stream

  // set the right type;
  be_type *bt;
  if (this->ctx_->alias ())
    bt = this->ctx_->alias ();
  else
    bt = node;

  if (this->ctx_->state () == TAO_CodeGen::TAO_EXCEPTION_CTOR_CH)
    *os << "const " << bt->nested_type_name (this->ctx_->scope (), "_ptr ");
  else
    *os << "const " << bt->name () << "_ptr ";
  return 0;
}

int be_visitor_exception_ctor::visit_predefined_type (be_predefined_type *node)
{
  TAO_OutStream *os = this->ctx_->stream (); // get output stream

  // set the right type;
  be_type *bt;
  if (this->ctx_->alias ())
    bt = this->ctx_->alias ();
  else
    bt = node;

  // check if the type is an any
  if (node->pt () == AST_PredefinedType::PT_any)
    {
      if (this->ctx_->state () == TAO_CodeGen::TAO_EXCEPTION_CTOR_CH)
        *os << "const " << bt->nested_type_name (this->ctx_->scope ());
      else
        *os << "const " << bt->name ();
      *os << " &";
      return 0;
    } // end of if
  else if (node->pt () == AST_PredefinedType::PT_pseudo) // e.g., CORBA::Object
    {
      if (this->ctx_->state () == TAO_CodeGen::TAO_EXCEPTION_CTOR_CH)
        *os << "const " << bt->nested_type_name (this->ctx_->scope (), "_ptr ");
      else
        *os << "const " << bt->name () << "_ptr ";
    } // end else if
  else // simple predefined types
    {
      if (this->ctx_->state () == TAO_CodeGen::TAO_EXCEPTION_CTOR_CH)
        *os << bt->nested_type_name (this->ctx_->scope ());
      else
        *os << bt->name ();
    } // end of else

  return 0;
}

int be_visitor_exception_ctor::visit_sequence (be_sequence *node)
{
  TAO_OutStream *os = this->ctx_->stream (); // get output stream

  // set the right type;
  be_type *bt;
  if (this->ctx_->alias ())
    bt = this->ctx_->alias ();
  else
    bt = node;

  if (this->ctx_->state () == TAO_CodeGen::TAO_EXCEPTION_CTOR_CH)
    *os << "const " << bt->nested_type_name (this->ctx_->scope ());
  else
    *os << "const " << bt->name ();
  *os << " &";
  return 0;
}

int be_visitor_exception_ctor::visit_string (be_string *node)
{
  TAO_OutStream *os = this->ctx_->stream (); // get output stream
 
  if (node->width () == (long) sizeof (char))
    {
      *os << "const char *";
    }
  else
    {
      *os << "const CORBA::WChar *";
    }

  return 0;
}

int be_visitor_exception_ctor::visit_structure (be_structure *node)
{
  TAO_OutStream *os = this->ctx_->stream (); // get output stream

  // set the right type;
  be_type *bt;
  if (this->ctx_->alias ())
    bt = this->ctx_->alias ();
  else
    bt = node;

  if (this->ctx_->state () == TAO_CodeGen::TAO_EXCEPTION_CTOR_CH)
    *os << "const " << bt->nested_type_name (this->ctx_->scope ());
  else
    *os << "const " << bt->name ();
  *os << " &";
  return 0;
}

int be_visitor_exception_ctor::visit_union (be_union *node)
{
  TAO_OutStream *os = this->ctx_->stream (); // get output stream

  // set the right type;
  be_type *bt;
  if (this->ctx_->alias ())
    bt = this->ctx_->alias ();
  else
    bt = node;

  if (this->ctx_->state () == TAO_CodeGen::TAO_EXCEPTION_CTOR_CH)
    *os << "const " << bt->nested_type_name (this->ctx_->scope ());
  else
    *os << "const " << bt->name ();
  *os << " &";
  return 0;
}

int be_visitor_exception_ctor::visit_typedef (be_typedef *node)
{
  this->ctx_->alias (node);
  if (node->primitive_base_type ()->accept (this) == -1)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "be_visitor_exception_ctor::"
                         "visit_typedef - "
                         "accept on primitive type failed\n"),
                        -1);
    }
  this->ctx_->alias (0);
  return 0;
}
