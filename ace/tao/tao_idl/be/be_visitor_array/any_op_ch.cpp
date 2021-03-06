//
// any_op_ch.cpp,v 1.6 2000/08/23 16:58:46 parsons Exp
//

// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    any_op_ch.cpp
//
// = DESCRIPTION
//    Visitor for code generation of Arrays for the Any operators in the client
//    header.
//
// = AUTHOR
//    Aniruddha Gokhale
//
// ============================================================================

#include	"idl.h"
#include	"idl_extern.h"
#include	"be.h"

#include "be_visitor_array.h"

ACE_RCSID(be_visitor_array, any_op_ch, "any_op_ch.cpp,v 1.6 2000/08/23 16:58:46 parsons Exp")


// ***************************************************************************
// Array visitor for generating Any operator declarations in the client header
// ***************************************************************************

be_visitor_array_any_op_ch::be_visitor_array_any_op_ch
(be_visitor_context *ctx)
  : be_visitor_decl (ctx)
{
}

be_visitor_array_any_op_ch::~be_visitor_array_any_op_ch (void)
{
}

int
be_visitor_array_any_op_ch::visit_array (be_array *node)
{
  if (node->cli_hdr_any_op_gen () || node->imported ())
    return 0;

  TAO_OutStream *os = this->ctx_->stream ();

  // generate the Any <<= and >>= operator declarations
  os->indent ();
  *os << be_global->stub_export_macro () << " void"
      << " operator<<= (CORBA::Any &, const " << node->name ()
      << "_forany &);" << be_nl;
  *os << be_global->stub_export_macro () << " CORBA::Boolean"
      << " operator>>= (const CORBA::Any &, "
      << node->name () << "_forany &);\n";

  node->cli_hdr_any_op_gen (1);
  return 0;
}
