// ast_enum_val.cpp,v 1.8 2000/10/14 22:21:53 parsons Exp

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

// AST_EnumVals denote IDL enumerator declarations
// AST_EnumVals are a subclass of AST_Constant
// AST_EnumVals have no additional fields.

#include "idl.h"
#include "idl_extern.h"

ACE_RCSID(ast, ast_enum_val, "ast_enum_val.cpp,v 1.8 2000/10/14 22:21:53 parsons Exp")

// Constructor(s) and destructor.
AST_EnumVal::AST_EnumVal (void)
{
}

AST_EnumVal::AST_EnumVal (unsigned long v, 
                          UTL_ScopedName *n, 
                          UTL_StrList *p)
  : AST_Constant  (AST_Expression::EV_ulong,
		               AST_Decl::NT_enum_val,
			             new AST_Expression (v), 
                   n, 
                   p),
	  AST_Decl (AST_Decl::NT_enum_val, 
              n, 
              p)
{
}

AST_EnumVal::~AST_EnumVal (void)
{
}

// Redefinition of inherited virtual operations.

// Dump this AST_EnumVal to the ostream o.
void
AST_EnumVal::dump (ostream &o)
{
  AST_Constant::dump (o);
}

int
AST_EnumVal::ast_accept (ast_visitor *visitor)
{
  return visitor->visit_enum_val (this);
}

// Narrowing methods.
IMPL_NARROW_METHODS1(AST_EnumVal, AST_Constant)
IMPL_NARROW_FROM_DECL(AST_EnumVal)
