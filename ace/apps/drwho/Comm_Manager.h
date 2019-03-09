/* -*- C++ -*- */
// Comm_Manager.h,v 1.4 1998/10/20 02:34:37 levine Exp

// ============================================================================
//
// = LIBRARY
//    drwho
//
// = FILENAME
//    Comm_Manager.h
//
// = AUTHOR
//    Douglas C. Schmidt
//
// ============================================================================

#ifndef _COMM_MANAGER_H
#define _COMM_MANAGER_H

#include "global.h"

class Comm_Manager
{
  // = TITLE
  //   Provides a virtual communcations layer for the drwho program.
protected:
  char recv_packet_[UDP_PACKET_SIZE];
  char send_packet_[UDP_PACKET_SIZE];
  sockaddr_in sin_;
  int sokfd_;

  virtual int mux (char *packet, int &packet_length)   = 0;
  virtual int demux (char *packet, int &packet_length) = 0;
  virtual int open (short port_number) = 0;
  virtual int receive (int timeout = 0) = 0;
  virtual int send (void) = 0;
};

#endif /* _COMM_MANAGER_H */
