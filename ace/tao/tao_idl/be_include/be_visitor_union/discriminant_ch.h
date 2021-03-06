/* -*- c++ -*- */
//
// discriminant_ch.h,v 1.2 1998/10/20 02:32:36 levine Exp
//

// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    discriminant_ch.h
//
// = DESCRIPTION
//     Visitor for the Union class.
//     This one generates code for the discriminant of the Union in the client
//     header.
//
// = AUTHOR
//    Aniruddha Gokhale
//
// ============================================================================

#ifndef _BE_VISITOR_UNION_DISCRIMINANT_CH_H_
#define _BE_VISITOR_UNION_DISCRIMINANT_CH_H_

class be_visitor_union_discriminant_ch : public be_visitor_decl
{
  //
  // = TITLE
  //   be_visitor_union_discriminant_ch
  //
  // = DESCRIPTION
  //   This is a concrete visitor to generate the client header for union
  //   discriminant
  //
  //
public:
  be_visitor_union_discriminant_ch (be_visitor_context *ctx);
  // constructor

  ~be_visitor_union_discriminant_ch (void);
  // destructor

  virtual int visit_enum (be_enum *node);
  // visit an enum

  virtual int visit_predefined_type (be_predefined_type *node);
  // visit a predefined type

  virtual int visit_typedef (be_typedef *node);
  // visit a typedef node
};

#endif /* _BE_VISITOR_UNION_DISCRIMINANT_CH_H_ */
