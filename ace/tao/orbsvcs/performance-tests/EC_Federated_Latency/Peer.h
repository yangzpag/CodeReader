/**
 * @file Peer.h
 *
 * Peer.h,v 1.1 2001/08/24 21:46:48 coryan Exp
 *
 */

#ifndef ECFL_PEER_H
#define ECFL_PEER_H

#include "ControlS.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

/**
 * @class ECFL_Peer
 *
 * @brief Implement the Control::Peer interface
 *
 */
class ECFL_Peer
 : public virtual POA_Control::Peer
 , public virtual PortableServer::RefCountServantBase
{
public:
  /// Constructor
  ECFL_Peer (CORBA::ORB_ptr orb);

  /// Destructor
  virtual ~ECFL_Peer (void);

  /// Initialize the peer
  void init (PortableServer::POA_ptr poa,
             CORBA::Environment &ACE_TRY_ENV);

  //@{
  /** @name The Control::Peer methods
   */
  virtual RtecEventChannelAdmin::EventChannel_ptr
      channel (CORBA::Environment&)
        ACE_THROW_SPEC ((CORBA::SystemException));

  virtual void connect (RtecEventChannelAdmin::EventChannel_ptr remote_ec,
                        CORBA::Environment&)
    ACE_THROW_SPEC ((CORBA::SystemException));

  Control::Loopback_ptr setup_loopback (CORBA::Long experiment_id,
                                        CORBA::Environment &)
    ACE_THROW_SPEC ((CORBA::SystemException));

  virtual Control::Samples* run_experiment (CORBA::Long experiment_id,
                                            CORBA::Long iterations,
                                            CORBA::Environment &)
    ACE_THROW_SPEC ((CORBA::SystemException));

  virtual void shutdown (CORBA::Environment&)
    ACE_THROW_SPEC ((CORBA::SystemException));
  //@}

private:
  /// Synchronize access to the internal data
  TAO_SYNCH_MUTEX mutex_;

  /// Keep a reference to the ORB, used in shutdown
  CORBA::ORB_var orb_;

  /// Event Channel references
  RtecEventChannelAdmin::EventChannel_var event_channel_;
};

#endif /* ECFL_PEER_H */
