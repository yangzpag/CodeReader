//remote_proxy_impl_ch.h,v 1.1 2000/11/20 02:15:10 corsaro Exp
//
// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    remote_proxy_impl_ch.h
//
// = DESCRIPTION
//     Concrete visitor for the Interface node. This
//     visitor handle the generation of the proxy
//     implementations remote clas.
//
// = AUTHOR
//     Angelo Corsaro <corsaro@cs.wustl.edu>
//
// ============================================================================

#ifndef BE_REMOTE_PROXY_IMPL_CH_H_
#define BE_REMOTE_PROXY_IMPL_CH_H_

class be_visitor_interface_remote_proxy_impl_ch : public be_visitor_interface
{
  // = TITLE
  //   Generates the declaration for the remote proxy
  //   implementation classes.

public:
  // -- Ctor/Dtor Decl. --
  be_visitor_interface_remote_proxy_impl_ch (be_visitor_context *ctx);

  virtual ~be_visitor_interface_remote_proxy_impl_ch (void);

  virtual int visit_interface (be_interface *node);
  // visit an interface

};

#endif /* BE_REMOTE_PROXY_IMPL_CH_H_ */
