/* -*- C++ -*- */

//=============================================================================
/**
 *  @file   UDP.h
 *
 *  UDP.h,v 5.9 2001/07/03 18:55:09 crodrigu Exp
 *
 *  @author Nagarajan Surendran <naga@cs.wustl.edu>
 */
//=============================================================================


#ifndef TAO_AV_UDP_H
#define TAO_AV_UDP_H
#include "ace/pre.h"

#include "ace/OS.h"
#include "Protocol_Factory.h"

/**
 * @class TAO_AV_UDP_Factory
 * @brief
 */
class TAO_AV_Export TAO_AV_UDP_Factory : public TAO_AV_Transport_Factory
{
public:
  /// Initialization hook.
  TAO_AV_UDP_Factory (void);
  virtual ~TAO_AV_UDP_Factory (void);
  virtual int init (int argc, char *argv[]);
  virtual int match_protocol (const char *protocol_string);
  virtual TAO_AV_Acceptor *make_acceptor (void);
  virtual TAO_AV_Connector *make_connector (void);
};

class TAO_AV_UDP_Flow_Handler;

/**
 * @class TAO_AV_UDP_Transport
 * @brief A transport abstraction for udp sockets. 
 *        Uses the ACE_SOCK_Dgram to send the data.
 */
class TAO_AV_Export TAO_AV_UDP_Transport
  :public TAO_AV_Transport
{

public:
  TAO_AV_UDP_Transport (void);

  TAO_AV_UDP_Transport (TAO_AV_UDP_Flow_Handler *handler);

  virtual  ~TAO_AV_UDP_Transport (void);
  virtual int open (ACE_Addr *addr);

  virtual int close (void);

  virtual int mtu (void);

  virtual ACE_Addr *get_peer_addr (void);

  virtual int set_remote_address (const ACE_INET_Addr &address);

  /// Write the complete Message_Block chain to the connection.
  virtual ssize_t send (const ACE_Message_Block *mblk,
                        ACE_Time_Value *s = 0);

  /// Write the contents of the buffer of length len to the connection.
  virtual ssize_t send (const char *buf,
                        size_t len,
                        ACE_Time_Value *s = 0);

  /// Write the contents of iovcnt iovec's to the connection.
  virtual ssize_t send (const iovec *iov,
                        int iovcnt,
                        ACE_Time_Value *s = 0);

  /// Read len bytes from into buf.
  virtual ssize_t recv (char *buf,
                        size_t len,
                        ACE_Time_Value *s = 0);

  /// Read len bytes from into buf using flags.
  virtual ssize_t recv (char *buf,
                        size_t len,
                        int flags,
                        ACE_Time_Value *s = 0);

  ///  Read received data into the iovec buffers.
  virtual ssize_t recv (iovec *iov,
                        int iovcnt,
                        ACE_Time_Value *s = 0);
protected:
  TAO_AV_UDP_Flow_Handler *handler_;
  ACE_Addr *addr_;
  ACE_INET_Addr peer_addr_;
};

/**
 * @class TAO_AV_UDP_Flow_Handler
 * @brief Flow Handler for UDP flows. 
 */
class TAO_AV_Export TAO_AV_UDP_Flow_Handler
  :public virtual TAO_AV_Flow_Handler,
   public virtual ACE_Event_Handler
{
public:
  ///Ctor
  /// Dtor
  TAO_AV_UDP_Flow_Handler (void);
  ~TAO_AV_UDP_Flow_Handler (void);
  int open (ACE_Addr &address);
  virtual TAO_AV_Transport *transport (void);
  virtual int set_remote_address (ACE_Addr *address);
  virtual ACE_HANDLE get_handle (void) const;
  virtual int handle_input (ACE_HANDLE fd);
  virtual int handle_timeout (const ACE_Time_Value &tv, const void *arg = 0);
  const ACE_SOCK_Dgram *get_socket (void) const;
  virtual ACE_Event_Handler* event_handler (void){ return this; }
protected:
  TAO_AV_Core *av_core_;
  ACE_INET_Addr peer_addr_;
  ACE_SOCK_Dgram sock_dgram_;
};

/**
 * @class TAO_AV_UDP_Acceptor
 * @brief 
 */
class TAO_AV_Export TAO_AV_UDP_Acceptor
  :public TAO_AV_Acceptor
{
public:
  TAO_AV_UDP_Acceptor (void);
  virtual ~TAO_AV_UDP_Acceptor (void);
  virtual int open (TAO_Base_StreamEndPoint *endpoint,
                    TAO_AV_Core *av_core,
                    TAO_FlowSpec_Entry *entry,
                    TAO_AV_Flow_Protocol_Factory *factory);

  virtual int open_default (TAO_Base_StreamEndPoint *endpoint,
                            TAO_AV_Core *av_core,
                            TAO_FlowSpec_Entry *entry,
                            TAO_AV_Flow_Protocol_Factory *factory);

  virtual int open_i (ACE_INET_Addr *address);

  virtual int close (void);
  virtual int activate_svc_handler (TAO_AV_Flow_Handler *handler);
protected:
  TAO_Base_StreamEndPoint *endpoint_;
  TAO_FlowSpec_Entry *entry_;
  TAO_AV_Flow_Protocol_Factory *flow_protocol_factory_;
};

/**
 * @class TAO_AV_UDP_Connector
 * @brief 
 */
class TAO_AV_Export TAO_AV_UDP_Connector
  :public TAO_AV_Connector
{
public:
  TAO_AV_UDP_Connector (void);
  ~TAO_AV_UDP_Connector (void);
  virtual int open (TAO_Base_StreamEndPoint *endpoint,
                    TAO_AV_Core *av_core,
                    TAO_AV_Flow_Protocol_Factory *factory);

  virtual int connect (TAO_FlowSpec_Entry *entry,
                       TAO_AV_Transport *&transport);
  virtual int activate_svc_handler (TAO_AV_Flow_Handler *handler);
  virtual int close (void);
protected:
  TAO_Base_StreamEndPoint *endpoint_;
  TAO_AV_Core *av_core_;
  TAO_FlowSpec_Entry *entry_;
  TAO_AV_Flow_Protocol_Factory *flow_protocol_factory_;
};

/**
 * @class TAO_AV_UDP_Object
 * @brief TAO_AV_Protocol_Object for the User Datagram Protocol (UDP)
 */
class TAO_AV_Export TAO_AV_UDP_Object  : public TAO_AV_Protocol_Object
{
public:
  TAO_AV_UDP_Object (TAO_AV_Callback *callback,
                     TAO_AV_Transport *transport = 0);

  /// Dtor
  virtual ~TAO_AV_UDP_Object (void);

  virtual int handle_input (void);

  /// send a data frame.
  virtual int send_frame (ACE_Message_Block *frame,
                          TAO_AV_frame_info *frame_info = 0);

  virtual int send_frame (const iovec *iov,
                          int iovcnt,
                          TAO_AV_frame_info *frame_info = 0);

  virtual int send_frame (const char*buf,
                          size_t len);
  
  /// end the stream.
  virtual int destroy (void);

private:
  /// Pre-allocated memory to receive the data...
  ACE_Message_Block frame_;
};

/**
 * @class TAO_AV_UDP_Flow_Factory
 * @brief 
 */
class TAO_AV_Export TAO_AV_UDP_Flow_Factory : public TAO_AV_Flow_Protocol_Factory
{
public:
  /// Initialization hook.
  TAO_AV_UDP_Flow_Factory (void);
  virtual ~TAO_AV_UDP_Flow_Factory (void);
  virtual int init (int argc, char *argv[]);
  virtual int match_protocol (const char *flow_string);
  TAO_AV_Protocol_Object* make_protocol_object (TAO_FlowSpec_Entry *entry,
                                                TAO_Base_StreamEndPoint *endpoint,
                                                TAO_AV_Flow_Handler *handler,
                                                TAO_AV_Transport *transport);
};

ACE_STATIC_SVC_DECLARE (TAO_AV_UDP_Flow_Factory)
ACE_FACTORY_DECLARE (TAO_AV, TAO_AV_UDP_Flow_Factory)

ACE_STATIC_SVC_DECLARE (TAO_AV_UDP_Factory)
ACE_FACTORY_DECLARE (TAO_AV, TAO_AV_UDP_Factory)


#if defined(__ACE_INLINE__)
#include "UDP.i"
#endif /* __ACE_INLINE__ */

#include "ace/post.h"
#endif /* TAO_AV_UDP_H */
