#----------------------------------------------------------------------------
#
# Makefile,v 1.23 2001/04/27 21:05:10 irfan Exp
#
# Makefile for the POA tests
#
#----------------------------------------------------------------------------

#----------------------------------------------------------------------------
#	Local macros
#----------------------------------------------------------------------------

DIRS  = POA_Destruction \
	wait_for_completion \
	Excessive_Object_Deactivations \
	Etherealization \
	Object_Reactivation \
	Non_Servant_Upcalls \
	Single_Threaded_POA \
	Identity 

# The following test hasn't been updated yet
# Demux_Test

#### Does not compile on UNIX:	Forwarding \

ifndef TAO_ROOT
  TAO_ROOT = $(ACE_ROOT)/TAO
endif

#----------------------------------------------------------------------------
#	Include macros and targets
#----------------------------------------------------------------------------

include	$(ACE_ROOT)/include/makeinclude/wrapper_macros.GNU
include	$(ACE_ROOT)/include/makeinclude/macros.GNU
include $(TAO_ROOT)/rules.tao.GNU
include	$(ACE_ROOT)/include/makeinclude/rules.common.GNU
include	$(ACE_ROOT)/include/makeinclude/rules.nested.GNU
include	$(ACE_ROOT)/include/makeinclude/rules.nolocal.GNU
