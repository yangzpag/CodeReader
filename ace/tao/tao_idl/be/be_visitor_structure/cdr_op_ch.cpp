//
// cdr_op_ch.cpp,v 1.7 2000/08/23 16:58:47 parsons Exp
//

// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    cdr_op_ch.cpp
//
// = DESCRIPTION
//    Visitor generating code for CDR operators for structures. This uses
//    compiled marshaling.
//
// = AUTHOR
//    Aniruddha Gokhale
//
// ============================================================================

#include        "idl.h"
#include        "idl_extern.h"
#include        "be.h"

#include "be_visitor_structure.h"

ACE_RCSID(be_visitor_structure, cdr_op_ch, "cdr_op_ch.cpp,v 1.7 2000/08/23 16:58:47 parsons Exp")

// ***************************************************************************
// Structure visitor for generating CDR operator declarations in the client header
// ***************************************************************************

be_visitor_structure_cdr_op_ch::be_visitor_structure_cdr_op_ch
(be_visitor_context *ctx)
  : be_visitor_structure (ctx)
{
}

be_visitor_structure_cdr_op_ch::~be_visitor_structure_cdr_op_ch (void)
{
}

int
be_visitor_structure_cdr_op_ch::visit_structure (be_structure *node)
{
  if (node->cli_hdr_cdr_op_gen () ||
      node->imported () ||
      node->is_local ())
    return 0;

  TAO_OutStream *os = this->ctx_->stream ();

  // generate the CDR << and >> operator declarations
  os->indent ();
  *os << be_global->stub_export_macro () << " CORBA::Boolean"
      << " operator<< (TAO_OutputCDR &, const " << node->name ()
      << " &);" << be_nl;
  *os << be_global->stub_export_macro () << " CORBA::Boolean"
      << " operator>> (TAO_InputCDR &, "
      << node->name () << " &);\n";


  // set the substate as generating code for the types defined in our scope
  this->ctx_->sub_state(TAO_CodeGen::TAO_CDR_SCOPE);
  // all we have to do is to visit the scope and generate code
  if (this->visit_scope (node) == -1)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "(%N:%l) be_visitor_structure_cdr_op_ch::"
                         "visit_structure - "
                         "codegen for scope failed\n"), -1);
    }


  node->cli_hdr_cdr_op_gen (1);
  return 0;
}
