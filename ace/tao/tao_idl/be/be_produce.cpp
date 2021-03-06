// be_produce.cpp,v 1.17 2001/05/17 10:49:55 brunsch Exp

/*

COPYRIGHT

Copyright 1992, 1993, 1994 Sun Microsystems, Inc.  Printed in the United
States of America.  All Rights Reserved.

This product is protected by copyright and distributed under the following
license restricting its use.

The Interface Definition Language Compiler Front End (CFE) is made
available for your use provided that you include this license and copyright
notice on all media and documentation and the software program in which
this product is incorporated in whole or part. You may copy and extend
functionality (but may not remove functionality) of the Interface
Definition Language CFE without charge, but you are not authorized to
license or distribute it to anyone else except as part of a product or
program developed by you or with the express written consent of Sun
Microsystems, Inc. ("Sun").

The names of Sun Microsystems, Inc. and any of its subsidiaries or
affiliates may not be used in advertising or publicity pertaining to
distribution of Interface Definition Language CFE as permitted herein.

This license is effective until terminated by Sun for failure to comply
with this license.  Upon termination, you shall destroy or return all code
and documentation for the Interface Definition Language CFE.

INTERFACE DEFINITION LANGUAGE CFE IS PROVIDED AS IS WITH NO WARRANTIES OF
ANY KIND INCLUDING THE WARRANTIES OF DESIGN, MERCHANTIBILITY AND FITNESS
FOR A PARTICULAR PURPOSE, NONINFRINGEMENT, OR ARISING FROM A COURSE OF
DEALING, USAGE OR TRADE PRACTICE.

INTERFACE DEFINITION LANGUAGE CFE IS PROVIDED WITH NO SUPPORT AND WITHOUT
ANY OBLIGATION ON THE PART OF Sun OR ANY OF ITS SUBSIDIARIES OR AFFILIATES
TO ASSIST IN ITS USE, CORRECTION, MODIFICATION OR ENHANCEMENT.

SUN OR ANY OF ITS SUBSIDIARIES OR AFFILIATES SHALL HAVE NO LIABILITY WITH
RESPECT TO THE INFRINGEMENT OF COPYRIGHTS, TRADE SECRETS OR ANY PATENTS BY
INTERFACE DEFINITION LANGUAGE CFE OR ANY PART THEREOF.

IN NO EVENT WILL SUN OR ANY OF ITS SUBSIDIARIES OR AFFILIATES BE LIABLE FOR
ANY LOST REVENUE OR PROFITS OR OTHER SPECIAL, INDIRECT AND CONSEQUENTIAL
DAMAGES, EVEN IF SUN HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

Use, duplication, or disclosure by the government is subject to
restrictions as set forth in subparagraph (c)(1)(ii) of the Rights in
Technical Data and Computer Software clause at DFARS 252.227-7013 and FAR
52.227-19.

Sun, Sun Microsystems and the Sun logo are trademarks or registered
trademarks of Sun Microsystems, Inc.

SunSoft, Inc.
2550 Garcia Avenue
Mountain View, California  94043

NOTE:

SunOS, SunSoft, Sun, Solaris, Sun Microsystems or the Sun logo are
trademarks or registered trademarks of Sun Microsystems, Inc.

 */

// BE_produce.cc - Produce the work of the BE - does nothing in the
//		   dummy BE

#include "idl.h"
#include "idl_extern.h"
#include "be.h"
#include "be_visitor_root.h"
#include "TAO_IDL_BE_Export.h"

ACE_RCSID(be, be_produce, "be_produce.cpp,v 1.17 2001/05/17 10:49:55 brunsch Exp")

// Clean up before exit, whether successful or not.
TAO_IDL_BE_Export void
BE_cleanup (void)
{
  AST_Decl *d = idl_global->root ();
  be_root *root = be_root::narrow_from_decl (d);

  root->destroy ();
  delete root;
  root = 0;

  idl_global->destroy ();
  delete idl_global;
  idl_global = 0;
}

// Abort this run of the BE.
TAO_IDL_BE_Export void
BE_abort (void)
{
  ACE_ERROR ((LM_ERROR,
              "Fatal Error - Aborting\n"));

  BE_cleanup ();

  ACE_OS::exit (1);
}
 
// Do the work of this BE. This is the starting point for code generation.
TAO_IDL_BE_Export void
BE_produce (void)
{
  // Root of the AST made up of BE nodes.
  be_root *root = 0;

  // Visitor for root.
  be_visitor *visitor = 0;

  // Context information for the visitor root.
  be_visitor_context ctx;

  // Configure the CodeGen object with the strategy to generate the visitors
  // that can produce interpretive or compiled marshaling stubs and skeletons.
  tao_cg->config_visitor_factory ();

  // Get the root node and narrow it down to be the back-end root node.
  AST_Decl *d = idl_global->root ();
  root = be_root::narrow_from_decl (d);

  if (root == 0)
    {
      ACE_ERROR ((LM_ERROR,
                  "(%N:%l) be_produce - "
                  "No Root\n"));
      BE_abort ();
    }

  if (be_global->ami_call_back () == I_TRUE)
    {
      // Make a first pass over the AST and introduce
      // AMI specific interfaces, methods and valuetypes.
      be_visitor_context *local_ctx = 0;
      ACE_NEW (local_ctx,
               be_visitor_context (ctx));

      ACE_NEW (visitor,
               be_visitor_ami_pre_proc (local_ctx));
      
      if (root->accept (visitor) == -1)
        {
          ACE_ERROR ((LM_ERROR,
                      "(%N:%l) be_produce - "
                      "client header for Root failed\n"));
          BE_abort ();
        }

      delete visitor;
    }

  if (be_global->gen_amh_classes () == I_TRUE)
    {
      // Make a first pass over the AST and introduce
      // AMH specific code
      be_visitor_context *local_ctx = 0;
      ACE_NEW (local_ctx,
               be_visitor_context (ctx));

      ACE_NEW (visitor,
               be_visitor_amh_pre_proc (local_ctx));
      
      if (root->accept (visitor) == -1)
        {
          ACE_ERROR ((LM_ERROR,
                      "(%N:%l) be_produce - "
                      "client header for Root failed\n"));
          BE_abort ();
        }

      delete visitor;
    }

  // Code generation involves six steps because of the six files that we
  // generate.

  // (1) Generate client header,
  // instantiate a visitor context, and set the codegen state
  ctx.state (TAO_CodeGen::TAO_ROOT_CH);

  // Get a root visitor.
  visitor = tao_cg->make_visitor (&ctx);

  // Generate code for the client header
  if (root->accept (visitor) == -1)
    {
      ACE_ERROR ((LM_ERROR,
                  "(%N:%l) be_produce - "
                  "client header for Root failed\n"));
      BE_abort ();
    }

  delete visitor;

  // (2) Generate client inline and
  // set the context information.
  ctx.reset ();
  ctx.state (TAO_CodeGen::TAO_ROOT_CI);

  // Create a visitor.
  visitor = tao_cg->make_visitor (&ctx);

  // Generate code for the client inline file.
  if (root->accept (visitor) == -1)
    {
      ACE_ERROR ((LM_ERROR,
                  "(%N:%l) be_produce - "
                  "client inline for Root failed\n"));
      BE_abort ();
    }

  delete visitor;


  // (3) Generate client stubs.
  ctx.reset ();
  ctx.state (TAO_CodeGen::TAO_ROOT_CS);

  // Create a visitor.
  visitor = tao_cg->make_visitor (&ctx);

  // Generate code for the client stubs.
  if (root->accept (visitor) == -1)
    {
      ACE_ERROR ((LM_ERROR,
                  "(%N:%l) be_produce - "
                  "client stubs for Root failed\n"));
      BE_abort ();
    }

  delete visitor;

  // (4) Generate server header.
  ctx.reset ();
  ctx.state (TAO_CodeGen::TAO_ROOT_SH);

  // Create a visitor.
  visitor = tao_cg->make_visitor (&ctx);

  // Generate code for the server header file.
  if (root->accept (visitor) == -1)
    {
      ACE_ERROR ((LM_ERROR,
                  "(%N:%l) be_produce - "
                  "server header for Root failed\n"));
      BE_abort ();
    }

  delete visitor;

  // (5) Generate server inline.
  ctx.reset ();
  ctx.state (TAO_CodeGen::TAO_ROOT_SI);

  // Create a visitor.
  visitor = tao_cg->make_visitor (&ctx);

  // Generate code for the server inline file.
  if (root->accept (visitor) == -1)
    {
      ACE_ERROR ((LM_ERROR,
                  "(%N:%l) be_produce - "
                  "server inline for Root failed\n"));
      BE_abort ();
    }

  delete visitor;

  // (6) Generate server skeletons
  ctx.reset ();
  ctx.state (TAO_CodeGen::TAO_ROOT_SS);

  // Create a visitor.
  visitor = tao_cg->make_visitor (&ctx);

  // Generate code for the server skeletons.
  if (root->accept (visitor) == -1)
    {
      ACE_ERROR ((LM_ERROR,
                  "(%N:%l) be_produce - "
                  "server skeletons for Root failed\n"));
      BE_abort ();
    }

  delete visitor;

  // (7) Generated server template header.
  if (be_global->gen_tie_classes ())
    {
      ctx.reset ();
      ctx.state (TAO_CodeGen::TAO_ROOT_TIE_SH);

      // Create a visitor.
      be_visitor_root_sth sth_visitor (&ctx);

      // Generate code for the implementation header.
      if (root->accept (&sth_visitor) == -1)
        {
          ACE_ERROR ((LM_ERROR,
                      "(%N:%l) be_produce - "
                      "server template header for Root failed\n"));
          BE_abort ();
        }
    }

  // Check if the flags are set for generating the 
  // the implementation header and skeleton files.
  if (be_global->gen_impl_files ())
    {
      // (8) generate implementation header.      
      ctx.reset ();
      ctx.state (TAO_CodeGen::TAO_ROOT_IH);

      // Create a visitor.
      visitor = tao_cg->make_visitor (&ctx);

      // Generate code for the implementation header.
      if (root->accept (visitor) == -1)
        {
          ACE_ERROR ((LM_ERROR,
                      "(%N:%l) be_produce - "
                      "implementation skeletons for Root failed\n"));
          BE_abort ();
        }
      
      delete visitor;
      
      // (9) Generate implementation source.      
      ctx.reset ();
      ctx.state (TAO_CodeGen::TAO_ROOT_IS);

      // Create a visitor.
      visitor = tao_cg->make_visitor (&ctx);
      
      // Generate code for the implementation source.
      if (root->accept (visitor) == -1)
        {
          ACE_ERROR ((LM_ERROR,
                      "(%N:%l) be_produce - "
                      "implementation skeletons for Root failed\n"));
          BE_abort ();
        }
      
      delete visitor;
    }

  // Clean up.
  BE_cleanup ();
}

