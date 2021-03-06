//
// rettype_vardecl_cs.cpp,v 1.17 2001/06/28 20:05:36 parsons Exp
//

// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    rettype_vardecl_cs.cpp
//
// = DESCRIPTION
//    Visitor generating code for return type variable declaration in the stubs.
//
// = AUTHOR
//    Aniruddha Gokhale
//
// ============================================================================

#include        "idl.h"
#include        "idl_extern.h"
#include        "be.h"

#include "be_visitor_operation.h"

ACE_RCSID(be_visitor_operation, rettype_vardecl_cs, "rettype_vardecl_cs.cpp,v 1.17 2001/06/28 20:05:36 parsons Exp")


// ************************************************************
//    be_visitor_operation_rettype_vardecl_cs
//    This visitor generates code for variable declaration and initialization
//    of the return type.
// ************************************************************

be_visitor_operation_rettype_vardecl_cs::
be_visitor_operation_rettype_vardecl_cs (be_visitor_context *ctx)
  : be_visitor_decl (ctx)
{
}

be_visitor_operation_rettype_vardecl_cs::
~be_visitor_operation_rettype_vardecl_cs (void)
{
}

int
be_visitor_operation_rettype_vardecl_cs::visit_array (be_array *node)
{
  TAO_OutStream *os = this->ctx_->stream (); // grab the out stream
  be_type *bt; // return type

  if (this->ctx_->alias ()) // a typedefed return type
    bt = this->ctx_->alias ();
  else
    bt = node;

  os->indent ();

  *os << bt->name () << "_slice *_tao_retval = 0;";

  *os << be_nl;

  return 0;
}

int
be_visitor_operation_rettype_vardecl_cs::visit_enum (be_enum *node)
{
  TAO_OutStream *os = this->ctx_->stream (); // grab the out stream
  be_type *bt; // return type

  if (this->ctx_->alias ()) // a typedefed return type
    bt = this->ctx_->alias ();
  else
    bt = node;

  os->indent ();

  *os << bt->name () << " _tao_retval = (" << bt->name () << ")0;";

  *os << be_nl << be_nl;

  return 0;
}

int
be_visitor_operation_rettype_vardecl_cs::visit_interface (be_interface *node)
{
  TAO_OutStream *os = this->ctx_->stream (); // grab the out stream
  be_type *bt; // return type

  if (this->ctx_->alias ()) // a typedefed return type
    bt = this->ctx_->alias ();
  else
    bt = node;

  os->indent ();

  if (node->is_defined ())
    {
      *os << bt->name () << "_ptr _tao_retval = "
          << bt->name () << "::_nil ();" << be_nl;
    }
  else
    {
      *os << bt->name () << "_ptr _tao_retval = tao_" 
          << node->flat_name () << "_nil ();" << be_nl;
    }

  *os << bt->name () << "_var _tao_safe_retval (_tao_retval);";

  *os << be_nl << be_nl;

  return 0;
}

int
be_visitor_operation_rettype_vardecl_cs::visit_interface_fwd (
    be_interface_fwd *node
  )
{
  TAO_OutStream *os = this->ctx_->stream (); // grab the out stream
  be_type *bt; // return type

  if (this->ctx_->alias ()) // a typedefed return type
    bt = this->ctx_->alias ();
  else
    bt = node;

  os->indent ();

  if (node->full_definition ()->is_defined ())
    {
      *os << bt->name () << "_ptr _tao_retval = "
          << bt->name () << "::_nil ();" << be_nl;
    }
  else
    {
      *os << bt->name () << "_ptr _tao_retval = tao_" 
          << node->flat_name () << "_nil ();" << be_nl;
    }

  *os << bt->name () << "_var _tao_safe_retval (_tao_retval);";

  *os << be_nl << be_nl;

  return 0;
}

#ifdef IDL_HAS_VALUETYPE

int
be_visitor_operation_rettype_vardecl_cs::visit_valuetype (be_valuetype *node)
{
  TAO_OutStream *os = this->ctx_->stream (); // grab the out stream
  be_type *bt; // return type

  if (this->ctx_->alias ()) // a typedefed return type
    bt = this->ctx_->alias ();
  else
    bt = node;

  os->indent ();

  *os << bt->name () << "_ptr _tao_retval = 0;" << be_nl;
  *os << bt->name () << "_var _tao_safe_retval (_tao_retval);";

  *os << be_nl << be_nl;

  return 0;
}

int
be_visitor_operation_rettype_vardecl_cs::visit_valuetype_fwd (be_valuetype_fwd *node)
{
  TAO_OutStream *os = this->ctx_->stream (); // grab the out stream
  be_type *bt; // return type

  if (this->ctx_->alias ()) // a typedefed return type
    bt = this->ctx_->alias ();
  else
    bt = node;

  os->indent ();
  *os << bt->name () << "_ptr _tao_retval = 0;" << be_nl;
  *os << bt->name () << "_var _tao_safe_retval (_tao_retval);";

  *os << be_nl << be_nl;

  return 0;
}

#endif /* IDL_HAS_VALUETYPE */

int
be_visitor_operation_rettype_vardecl_cs::visit_predefined_type (be_predefined_type *node)
{
  TAO_OutStream *os = this->ctx_->stream ();
  be_type *bt;

  if (this->ctx_->alias ())
    {
      bt = this->ctx_->alias ();
    }
  else
    {
      bt = node;
    }

  os->indent ();

  switch (node->pt ())
    {
    case AST_PredefinedType::PT_pseudo:
      *os << bt->name () << "_ptr _tao_retval = " 
          << bt->name () << "::_nil ();" << be_nl;
      *os << bt->name () << "_var _tao_safe_retval (_tao_retval);";
      break;
    case AST_PredefinedType::PT_any:
      *os << bt->name () << " *_tao_retval = 0;";
      break;
    case AST_PredefinedType::PT_void:
      break;
    case AST_PredefinedType::PT_longdouble:
      *os << bt->name () 
          << " _tao_retval = ACE_CDR_LONG_DOUBLE_INITIALIZER;";
      break;
    case AST_PredefinedType::PT_longlong:
      *os << bt->name () 
          << " _tao_retval = ACE_CDR_LONGLONG_INITIALIZER;";
      break;
    default:
      *os << bt->name () << " _tao_retval = 0;";
      break;
    }

  *os << be_nl << be_nl;

  return 0;
}

int
be_visitor_operation_rettype_vardecl_cs::visit_sequence (be_sequence *node)
{
  // we should never directly be here because anonymous sequence return types
  // are not allowed
  TAO_OutStream *os = this->ctx_->stream (); // grab the out stream
  be_type *bt; // return type

  if (this->ctx_->alias ()) // a typedefed return type
    bt = this->ctx_->alias ();
  else
    bt = node;

  os->indent ();
  *os << bt->name () << " *_tao_retval = 0;";

  *os << be_nl << be_nl;
  return 0;
}

int
be_visitor_operation_rettype_vardecl_cs::visit_string (be_string *node)
{
  TAO_OutStream *os = this->ctx_->stream (); // grab the out stream

  os->indent ();

  if (node->width () == (long) sizeof (char))
    {
      *os << "CORBA::String_var _tao_safe_retval;";
    }
  else
    {
      *os << "CORBA::WString_var _tao_safe_retval;";
    }

  *os << be_nl << be_nl;
  return 0;
}

int
be_visitor_operation_rettype_vardecl_cs::visit_structure (be_structure *node)
{
  TAO_OutStream *os = this->ctx_->stream (); // grab the out stream
  be_type *bt; // return type

  if (this->ctx_->alias ()) // a typedefed return type
    bt = this->ctx_->alias ();
  else
    bt = node;

  os->indent ();

  // based on whether we are variable or not, we return a pointer or the
  // aggregate type
  if (node->size_type () == be_decl::VARIABLE)
	  {
	    *os << bt->name () << " *_tao_retval = 0;" << be_nl;
	  }
  else
	  {
	    *os << bt->name () << " _tao_retval;" << be_nl;
	    *os << "ACE_OS::memset (&_tao_retval, 0, sizeof (" << bt->name () << "));"
	        << be_nl;
	  }

  return 0;
}

int
be_visitor_operation_rettype_vardecl_cs::visit_typedef (be_typedef *node)
{
  this->ctx_->alias (node); // set the alias node
  if (node->primitive_base_type ()->accept (this) == -1)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "be_visitor_operation_rettype_vardecl_cs::"
                         "visit_typedef - "
                         "accept on primitive type failed\n"),
                        -1);
    }
  this->ctx_->alias (0);
  return 0;
}

int
be_visitor_operation_rettype_vardecl_cs::visit_union (be_union *node)
{
  TAO_OutStream *os = this->ctx_->stream (); // grab the out stream
  be_type *bt; // return type

  if (this->ctx_->alias ()) // a typedefed return type
    bt = this->ctx_->alias ();
  else
    bt = node;

  os->indent ();

  // based on whether we are variable or not, we return a pointer or the
  // aggregate type
  if (node->size_type () == be_decl::VARIABLE)
    {
      *os << bt->name () << " *_tao_retval = 0;";
    }
  else
    {
      *os << bt->name () << " _tao_retval;";
    }

  *os << be_nl;
  return 0;
}
