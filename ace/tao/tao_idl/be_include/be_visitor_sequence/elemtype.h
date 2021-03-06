/* -*- c++ -*- */
//
// elemtype.h,v 1.2 1998/10/20 02:32:33 levine Exp
//

// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    elemtype.h
//
// = DESCRIPTION
//    Concrete visitor for the Sequence class
//    This one provides code generation for the element type returned by the []
//    operators for the Sequence node.
//
// = AUTHOR
//    Aniruddha Gokhale
//
// ============================================================================

#ifndef _BE_VISITOR_SEQUENCE_ELEMTYPE_H_
#define _BE_VISITOR_SEQUENCE_ELEMTYPE_H_

class be_visitor_sequence_elemtype : public be_visitor_decl
{
  //
  // = TITLE
  //    be_visitor_sequence_elemtype
  //
  // = DESCRIPTION
  //   This is a concrete visitor to generate the return type for the
  //   [] operators
  //
  // = NOTES
  //    This class may eventually go away when the _var and _out classes are
  //    generated using templates
public:
  be_visitor_sequence_elemtype (be_visitor_context *ctx);
  // Constructor

  ~be_visitor_sequence_elemtype (void);
  // destructor

  // = Visitors
  virtual int visit_predefined_type (be_predefined_type *node);
  virtual int visit_interface (be_interface *node);
  virtual int visit_interface_fwd (be_interface_fwd *node);
  virtual int visit_structure (be_structure *node);
  virtual int visit_enum (be_enum *node);
  virtual int visit_exception (be_exception *node);
  virtual int visit_union (be_union *node);
  virtual int visit_array (be_array *node);
  virtual int visit_sequence (be_sequence *node);
  virtual int visit_typedef (be_typedef *node);
  virtual int visit_string (be_string *node);

protected:
  int visit_node (be_type *);
  // helper that does the common job

};

#endif /* _BE_VISITOR_SEQUENCE_ELEMTYPE_H_ */
