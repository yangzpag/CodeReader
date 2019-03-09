//
// enum_ch.cpp,v 1.10 2001/05/15 15:48:35 parsons Exp
//

// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    enum_ch.cpp
//
// = DESCRIPTION
//    Visitor generating code for Enums in the client header
//
// = AUTHOR
//    Aniruddha Gokhale
//
// ============================================================================

#include	"idl.h"
#include	"idl_extern.h"
#include	"be.h"

#include "be_visitor_enum.h"

ACE_RCSID(be_visitor_enum, enum_ch, "enum_ch.cpp,v 1.10 2001/05/15 15:48:35 parsons Exp")


// ********************************************************************
// Visitor implementation for the Enum type
// This one for the client header file
// ********************************************************************

be_visitor_enum_ch::be_visitor_enum_ch (be_visitor_context *ctx)
  : be_visitor_scope (ctx)
{
}

be_visitor_enum_ch::~be_visitor_enum_ch (void)
{
}

// Visit the enum_ch node and its scope.
int
be_visitor_enum_ch::visit_enum (be_enum *node)
{
  TAO_OutStream *os = this->ctx_->stream ();

  // Comma to be generated by the scope visitor.
  this->ctx_->comma (1); 

  if (!node->cli_hdr_gen () && !node->imported ())
    {
      *os << "enum " << node->local_name () << be_nl;
      *os << "{" << be_idt_nl;

       if (this->visit_scope (node) == 1)
         {
           ACE_ERROR_RETURN ((LM_ERROR,
                              "(%N:%l) be_visitor_enum_ch::"
                              "visit_enum - "
                              "scope generation failed\n"
                              ), 
                             -1);
         }

      *os << be_uidt_nl;
      *os << "};" << be_nl << be_nl;

      // As per the ORBOS spec, we need the following typedef
      *os << "typedef " << node->local_name () << " &" << node->local_name ()
          << "_out;" << be_nl;

      if (!node->is_local ())
        {
          // By using a visitor to declare and define the TypeCode, we have
          // the added advantage to conditionally not generate any code. This
          // will be based on the command line options. This is still TO-DO.
          be_visitor_context ctx (*this->ctx_);
          ctx.state (TAO_CodeGen::TAO_TYPECODE_DECL);
          be_visitor *visitor = tao_cg->make_visitor (&ctx);

          if (!visitor || (node->accept (visitor) == -1))
            {
              ACE_ERROR_RETURN ((LM_ERROR,
                                 "(%N:%l) be_visitor_enum_ch::"
                                 "visit_enum - "
                                 "TypeCode declaration failed\n"
                                 ), 
                                -1);
            }
        }

      node->cli_hdr_gen (I_TRUE);
    }

  return 0;
}

int
be_visitor_enum_ch::post_process (be_decl *bd)
{
  TAO_OutStream *os = this->ctx_->stream ();

  // Am I the last one?
  if (!this->last_node (bd))
    {
      *os << "," << be_nl;
    }

  return 0;
}

int
be_visitor_enum_ch::visit_enum_val (be_enum_val *node)
{
  TAO_OutStream *os = this->ctx_->stream ();

  *os << node->local_name ();

  return 0;
}
