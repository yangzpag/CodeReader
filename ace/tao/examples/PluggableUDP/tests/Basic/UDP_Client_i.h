// -*- C++ -*-
// UDP_Client_i.h,v 1.1 2001/04/09 21:39:27 mk1 Exp

// ============================================================================
//
// = LIBRARY
//    TAO/examples/Simple/UDP
//
// = FILENAME
//    UDP_Client_i.h
//
// = DESCRIPTION
//    This class implements the client functionality of the UDP test.
//
// = AUTHOR
//    Michael Kircher <Michael.Kircher@mchp.siemens.de>
//
// ============================================================================

#ifndef UDP_CLIENT_I_H
#define UDP_CLIENT_I_H

#include "ace/Task.h"
#include "tao/corba.h"

#include "UDPC.h"

class UDP_Client_i
: public ACE_Task_Base
{
  // = TITLE
  //    UDP Client interface subclass.
  //
  // = DESCRIPTION
  //    This class wrapps the client functionality into one class
  //
public:
  // = Initialization and termination methods.
  UDP_Client_i (CORBA::ORB_ptr orb,
                UDP_ptr udp,
                UDP_ptr udpHandler,
                ACE_UINT32 msec,
                ACE_UINT32 iterations);
  // Constructor

  virtual ~UDP_Client_i (void);
  // Destructor

private:
  // Runs in a separate thread.
  virtual int svc (void );

private:
  CORBA::ORB_var orb_;

  UDP_var udp_;

  UDP_var udpHandler_;

  ACE_UINT32 delay_;

  ACE_UINT32 iterations_;
};


#endif /* UDP_CLIENT_I_H */
