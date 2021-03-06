// This may look like C, but it's really -*- C++ -*-
// ast_structure.h,v 1.13 2001/03/26 21:16:52 coryan Exp
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

#ifndef _AST_STRUCTURE_AST_STRUCTURE_HH
#define _AST_STRUCTURE_AST_STRUCTURE_HH

#include "ace/Unbounded_Queue.h"

// Representation of structure:
//
// NOTE: add (AST_ConcreteType *) is defined here because a structure
// can contain locally defined types in addition to fields.
//
// NOTE: add (AST_EnumValue *) is defined here because enums can
// be defined manifest locally; the constants defined in these
// enums are inserted in the enclosing scope. It is unlikely that
// a BE writer will need to overload this function in AST_Structure.

class TAO_IDL_FE_Export AST_Structure : public virtual AST_ConcreteType,
                                        public virtual UTL_Scope
{
public:
  // Operations.

  // Constructor(s).
  AST_Structure (void);

  AST_Structure (UTL_ScopedName *n,
                 UTL_StrList *p,
                 idl_bool local,
                 idl_bool abstract);

  AST_Structure (AST_Decl::NodeType nt,
                 UTL_ScopedName *n,
                 UTL_StrList *p,
                 idl_bool local,
                 idl_bool abstract);

  // Destructor.
  virtual ~AST_Structure (void);

  // Narrowing.
  DEF_NARROW_METHODS2(AST_Structure, AST_ConcreteType, UTL_Scope);
  DEF_NARROW_FROM_DECL(AST_Structure);
  DEF_NARROW_FROM_SCOPE(AST_Structure);

  virtual int member_count (void);
  // Return the count of members.

  virtual size_t nfields (void) const;
  // Return the count of actual fields.

  virtual int field (AST_Field **&result,
                     size_t slot) const;
  // Get an individual field node.

  virtual idl_bool is_local (void);
  // Overwrite the is_local method.

  virtual idl_bool in_recursion (AST_Type *node = 0);
  // Are we or the node represented by node involved in recursion.

  // AST Dumping.
  virtual void dump (ostream &o);

  // Cleanup function.
  virtual void destroy (void);

  // Visiting.
  virtual int ast_accept (ast_visitor *visitor);

protected:
  ACE_Unbounded_Queue<AST_Field *> fields_;
  // Container for this struct's field nodes. Excludes nodes included
  // in member_count, i.e., enum values of an enum declared inside
  // the struct.

private:
  friend int tao_yyparse (void);
  // Scope Management Protocol.

  virtual AST_Union *fe_add_union (AST_Union *u);

  virtual AST_Structure *fe_add_structure (AST_Structure *s);

  virtual AST_Field *fe_add_field (AST_Field *f);

  virtual AST_Enum *fe_add_enum (AST_Enum *e);

  virtual AST_EnumVal *fe_add_enum_val (AST_EnumVal *v);

  int compute_member_count (void);
  // Count the number of members.

  int member_count_;
  // Number of members.

  idl_bool local_struct_;
  // We also need to determine whether we contain any local type.
};

#endif           // _AST_STRUCTURE_AST_STRUCTURE_HH
