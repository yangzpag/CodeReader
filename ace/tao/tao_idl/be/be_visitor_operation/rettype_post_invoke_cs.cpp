//
// rettype_post_invoke_cs.cpp,v 1.2 2000/03/21 20:03:55 coryan Exp
//

// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    rettype_post_invoke_cs.cpp
//
// = DESCRIPTION
//    Visitor generating code for return type post processing following a
//    do_static_call.
//
// = AUTHOR
//    Aniruddha Gokhale
//
// ============================================================================

#include        "idl.h"
#include        "idl_extern.h"
#include        "be.h"

#include "be_visitor_operation.h"

ACE_RCSID(be_visitor_operation, rettype_post_invoke_cs, "rettype_post_invoke_cs.cpp,v 1.2 2000/03/21 20:03:55 coryan Exp")


// *******************************************************************************
//    be_visitor_operation_rettype_post_invoke_cs
// ********************************************************************************

be_visitor_operation_rettype_post_invoke_cs::
    be_visitor_operation_rettype_post_invoke_cs (be_visitor_context *ctx)
      : be_visitor_decl (ctx)
{
}

int
be_visitor_operation_rettype_post_invoke_cs::visit_array (be_array *node)
{
  TAO_OutStream *os = this->ctx_->stream (); // grab the out stream
  be_type *bt = node;

  if (this->ctx_->alias ()) // a typedefed return type
    bt = this->ctx_->alias ();

  *os << bt->name () << "_forany _tao_retval_forany ("
      << be_idt << be_idt_nl
      << "_tao_safe_retval.inout ()" << be_uidt_nl
      << ");\n" << be_uidt;
  return 0;
}

int
be_visitor_operation_rettype_post_invoke_cs::visit_typedef (be_typedef *node)
{
  this->ctx_->alias (node); // set the alias node
  if (node->primitive_base_type ()->accept (this) == -1)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "be_visitor_operation_rettype_post_docall::"
                         "visit_typedef - "
                         "accept on primitive type failed\n"),
                        -1);
    }
  this->ctx_->alias (0);
  return 0;
}
