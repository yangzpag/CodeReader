//
// interface_ss.h,v 1.3 2001/05/17 10:49:55 brunsch Exp
//
/* -*- c++ -*- */
// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    interface_ss.h
//
// = DESCRIPTION
//    Concrete visitor for the Interface node.
//    This provides for code generation in the server skeleton
//
// = AUTHOR
//    Aniruddha Gokhale
//
// ============================================================================

#ifndef _BE_INTERFACE_INTERFACE_SS_H_
#define _BE_INTERFACE_INTERFACE_SS_H_

class be_visitor_interface_ss : public be_visitor_interface
{
  //
  // = TITLE
  //   be_visitor_interface_ss
  //
  // = DESCRIPTION
  //   This is a concrete visitor to generate the server skeletons for interface
  //
  //
public:
  be_visitor_interface_ss (be_visitor_context *ctx);
  // constructor

  ~be_visitor_interface_ss (void);
  // destructor

  virtual int visit_interface (be_interface *node);
  // set the right context and make a visitor

protected:
  virtual void this_method (be_interface *node);
  virtual void dispatch_method (be_interface *node);
};

#endif /* _BE_INTERFACE_INTERFACE_SS_H_ */
