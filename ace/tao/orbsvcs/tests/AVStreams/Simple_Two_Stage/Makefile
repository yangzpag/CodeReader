#----------------------------------------------------------------------------
#	Makefile,v 1.14 2001/09/18 20:14:32 coryan Exp
#
#	Top-level Makefile for Pluggable testing of AVStreams of TAO.
#
#----------------------------------------------------------------------------

#----------------------------------------------------------------------------
#	Local macros
#----------------------------------------------------------------------------

LDLIBS     = -lTAO_AV -lTAO_CosProperty -lTAO_CosNaming -lTAO_Svc_Utils -lTAO_IORTable -lTAO_PortableServer -lTAO

RECEIVER_OBJS = receiver.o
SENDER_OBJS = sender.o

VLDLIBS = $(LDLIBS:%=%$(VAR))

ifndef TAO_ROOT
TAO_ROOT = $(ACE_ROOT)/TAO
endif

FILES = sender receiver
DEFS    = $(addsuffix .h,$(FILES))
LSRC	= $(addsuffix .cpp,$(FILES))

BIN2 = receiver sender

#### If the TAO orbsvcs library wasn't built with sufficient components,
#### don't try to build here.
TAO_ORBSVCS := $(shell $(ACE_ROOT)/bin/ace_components --orbsvcs)
ifeq (AV,$(findstring AV,$(TAO_ORBSVCS)))
  BIN = $(BIN2)
endif # AV

#----------------------------------------------------------------------------
#	Include macros and targets
#----------------------------------------------------------------------------

include $(ACE_ROOT)/include/makeinclude/wrapper_macros.GNU
include $(ACE_ROOT)/include/makeinclude/macros.GNU
include $(TAO_ROOT)/rules.tao.GNU
include $(ACE_ROOT)/include/makeinclude/rules.common.GNU
include $(ACE_ROOT)/include/makeinclude/rules.nonested.GNU
include $(ACE_ROOT)/include/makeinclude/rules.bin.GNU
include $(ACE_ROOT)/include/makeinclude/rules.local.GNU

ifeq ($(rapi),1)
  LDLIBS += -lACE_QoS
endif # rapi

#DCFLAGS = -g
LDFLAGS += -L$(TAO_ROOT)/orbsvcs/orbsvcs -L$(TAO_ROOT)/tao
CPPFLAGS += -I$(TAO_ROOT)/orbsvcs -I$(TAO_ROOT)/orbsvcs/orbsvcs/AV \
            -I$(TAO_ROOT)

# DO NOT DELETE THIS LINE -- g++dep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.


.obj/sender.o .obj/sender.so .shobj/sender.o .shobj/sender.so: sender.cpp sender.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/Naming/Naming_Utils.h \
 $(ACE_ROOT)/ace/pre.h \
 $(TAO_ROOT)/tao/corba.h \
 $(ACE_ROOT)/ace/post.h \
 $(ACE_ROOT)/ace/ACE_export.h \
 $(ACE_ROOT)/ace/svc_export.h \
 $(ACE_ROOT)/ace/ace_wchar.h \
 $(ACE_ROOT)/ace/ace_wchar.inl \
 $(ACE_ROOT)/ace/OS_Errno.h \
 $(ACE_ROOT)/ace/OS_Export.h \
 $(ACE_ROOT)/ace/OS_Errno.inl \
 $(TAO_ROOT)/tao/corbafwd.h \
 $(ACE_ROOT)/ace/CDR_Base.h \
 $(ACE_ROOT)/ace/Basic_Types.h \
 $(ACE_ROOT)/ace/Basic_Types.i \
 $(ACE_ROOT)/ace/Message_Block.h \
 $(ACE_ROOT)/ace/ACE.h \
 $(ACE_ROOT)/ace/OS.h \
 $(ACE_ROOT)/ace/OS_Dirent.h \
 $(ACE_ROOT)/ace/OS_Dirent.inl \
 $(ACE_ROOT)/ace/OS_String.h \
 $(ACE_ROOT)/ace/OS_String.inl \
 $(ACE_ROOT)/ace/OS_Memory.h \
 $(ACE_ROOT)/ace/OS_Memory.inl \
 $(ACE_ROOT)/ace/OS_TLI.h \
 $(ACE_ROOT)/ace/OS_TLI.inl \
 $(ACE_ROOT)/ace/Min_Max.h \
 $(ACE_ROOT)/ace/streams.h \
 $(ACE_ROOT)/ace/Trace.h \
 $(ACE_ROOT)/ace/OS.i \
 $(ACE_ROOT)/ace/Flag_Manip.h \
 $(ACE_ROOT)/ace/Flag_Manip.i \
 $(ACE_ROOT)/ace/Handle_Ops.h \
 $(ACE_ROOT)/ace/Handle_Ops.i \
 $(ACE_ROOT)/ace/Lib_Find.h \
 $(ACE_ROOT)/ace/Lib_Find.i \
 $(ACE_ROOT)/ace/Init_ACE.h \
 $(ACE_ROOT)/ace/Init_ACE.i \
 $(ACE_ROOT)/ace/Sock_Connect.h \
 $(ACE_ROOT)/ace/Sock_Connect.i \
 $(ACE_ROOT)/ace/ACE.i \
 $(ACE_ROOT)/ace/Malloc.h \
 $(ACE_ROOT)/ace/Log_Msg.h \
 $(ACE_ROOT)/ace/Log_Record.h \
 $(ACE_ROOT)/ace/Log_Priority.h \
 $(ACE_ROOT)/ace/Log_Record.i \
 $(ACE_ROOT)/ace/OS_Log_Msg_Attributes.h \
 $(ACE_ROOT)/ace/OS_Log_Msg_Attributes.inl \
 $(ACE_ROOT)/ace/Malloc.i \
 $(ACE_ROOT)/ace/Malloc_T.h \
 $(ACE_ROOT)/ace/Synch.h \
 $(ACE_ROOT)/ace/Synch.i \
 $(ACE_ROOT)/ace/Synch_T.h \
 $(ACE_ROOT)/ace/Synch_T.i \
 $(ACE_ROOT)/ace/Thread.h \
 $(ACE_ROOT)/ace/Thread_Adapter.h \
 $(ACE_ROOT)/ace/Base_Thread_Adapter.h \
 $(ACE_ROOT)/ace/Base_Thread_Adapter.inl \
 $(ACE_ROOT)/ace/Thread_Adapter.inl \
 $(ACE_ROOT)/ace/Thread.i \
 $(ACE_ROOT)/ace/Atomic_Op.i \
 $(ACE_ROOT)/ace/Synch_T.cpp \
 $(ACE_ROOT)/ace/Malloc_Allocator.h \
 $(ACE_ROOT)/ace/Malloc_Base.h \
 $(ACE_ROOT)/ace/Malloc_Allocator.i \
 $(ACE_ROOT)/ace/Free_List.h \
 $(ACE_ROOT)/ace/Free_List.i \
 $(ACE_ROOT)/ace/Free_List.cpp \
 $(ACE_ROOT)/ace/Malloc_T.i \
 $(ACE_ROOT)/ace/Malloc_T.cpp \
 $(ACE_ROOT)/ace/Memory_Pool.h \
 $(ACE_ROOT)/ace/Event_Handler.h \
 $(ACE_ROOT)/ace/Event_Handler.i \
 $(ACE_ROOT)/ace/Signal.h \
 $(ACE_ROOT)/ace/Signal.i \
 $(ACE_ROOT)/ace/Mem_Map.h \
 $(ACE_ROOT)/ace/Mem_Map.i \
 $(ACE_ROOT)/ace/SV_Semaphore_Complex.h \
 $(ACE_ROOT)/ace/SV_Semaphore_Simple.h \
 $(ACE_ROOT)/ace/SV_Semaphore_Simple.i \
 $(ACE_ROOT)/ace/SV_Semaphore_Complex.i \
 $(ACE_ROOT)/ace/Unbounded_Set.h \
 $(ACE_ROOT)/ace/Node.h \
 $(ACE_ROOT)/ace/Node.cpp \
 $(ACE_ROOT)/ace/Unbounded_Set.inl \
 $(ACE_ROOT)/ace/Unbounded_Set.cpp \
 $(ACE_ROOT)/ace/Memory_Pool.i \
 $(ACE_ROOT)/ace/Message_Block.i \
 $(ACE_ROOT)/ace/Message_Block_T.h \
 $(ACE_ROOT)/ace/Message_Block_T.i \
 $(ACE_ROOT)/ace/Message_Block_T.cpp \
 $(ACE_ROOT)/ace/CDR_Base.inl \
 $(TAO_ROOT)/tao/try_macros.h \
 $(TAO_ROOT)/tao/orbconf.h \
 $(ACE_ROOT)/ace/CORBA_macros.h \
 $(TAO_ROOT)/tao/varbase.h \
 $(TAO_ROOT)/tao/TAO_Export.h \
 $(TAO_ROOT)/tao/corbafwd.i \
 $(TAO_ROOT)/tao/Typecode.h \
 $(TAO_ROOT)/tao/Exception.h \
 $(ACE_ROOT)/ace/SString.h \
 $(ACE_ROOT)/ace/SString.i \
 $(TAO_ROOT)/tao/Exception.i \
 $(TAO_ROOT)/tao/Typecode.i \
 $(TAO_ROOT)/tao/Any.h \
 $(TAO_ROOT)/tao/CDR.h \
 $(ACE_ROOT)/ace/CDR_Stream.h \
 $(ACE_ROOT)/ace/CDR_Stream.i \
 $(TAO_ROOT)/tao/CDR.i \
 $(TAO_ROOT)/tao/Environment.h \
 $(TAO_ROOT)/tao/Environment.i \
 $(TAO_ROOT)/tao/Object.h \
 $(TAO_ROOT)/tao/Object_Proxy_Broker.h \
 $(TAO_ROOT)/tao/Object_Proxy_Impl.h \
 $(TAO_ROOT)/tao/Object.i \
 $(TAO_ROOT)/tao/Any.i \
 $(TAO_ROOT)/tao/NVList.h \
 $(ACE_ROOT)/ace/Unbounded_Queue.h \
 $(ACE_ROOT)/ace/Unbounded_Queue.inl \
 $(ACE_ROOT)/ace/Unbounded_Queue.cpp \
 $(TAO_ROOT)/tao/NVList.i \
 $(TAO_ROOT)/tao/LocalObject.h \
 $(TAO_ROOT)/tao/LocalObject.i \
 $(TAO_ROOT)/tao/Principal.h \
 $(TAO_ROOT)/tao/OctetSeqC.h \
 $(TAO_ROOT)/tao/Sequence.h \
 $(TAO_ROOT)/tao/Managed_Types.h \
 $(TAO_ROOT)/tao/Managed_Types.i \
 $(TAO_ROOT)/tao/Sequence.i \
 $(TAO_ROOT)/tao/Sequence_T.h \
 $(TAO_ROOT)/tao/Sequence_T.i \
 $(TAO_ROOT)/tao/Sequence_T.cpp \
 $(TAO_ROOT)/tao/OctetSeqC.i \
 $(TAO_ROOT)/tao/Principal.i \
 $(TAO_ROOT)/tao/ORB.h \
 $(TAO_ROOT)/tao/Services.h \
 $(TAO_ROOT)/tao/Services.i \
 $(TAO_ROOT)/tao/CORBA_String.h \
 $(TAO_ROOT)/tao/CORBA_String.inl \
 $(TAO_ROOT)/tao/PolicyC.h \
 $(TAO_ROOT)/tao/Encodable.h \
 $(TAO_ROOT)/tao/Remote_Object_Proxy_Impl.h \
 $(TAO_ROOT)/tao/CurrentC.h \
 $(TAO_ROOT)/tao/CurrentC.i \
 $(TAO_ROOT)/tao/PolicyC.i \
 $(TAO_ROOT)/tao/ORB.i \
 $(TAO_ROOT)/tao/BoundsC.h \
 $(TAO_ROOT)/tao/BoundsC.i \
 $(TAO_ROOT)/tao/ValueBase.h \
 $(TAO_ROOT)/tao/ValueBase.i \
 $(TAO_ROOT)/tao/ValueFactory.h \
 $(TAO_ROOT)/tao/ValueFactory.i \
 $(TAO_ROOT)/tao/DomainC.h \
 $(TAO_ROOT)/tao/DomainC.i \
 $(TAO_ROOT)/tao/WrongTransactionC.h \
 $(TAO_ROOT)/tao/Object_KeyC.h \
 $(TAO_ROOT)/tao/Object_KeyC.i \
 $(TAO_ROOT)/tao/ObjectIDList.h \
 $(TAO_ROOT)/tao/ObjectIDList.i \
 $(TAO_ROOT)/tao/StringSeqC.h \
 $(TAO_ROOT)/tao/StringSeqC.i \
 $(TAO_ROOT)/tao/PortableInterceptorC.h \
 $(TAO_ROOT)/tao/DynamicC.h \
 $(TAO_ROOT)/tao/DynamicC.i \
 $(TAO_ROOT)/tao/MessagingC.h \
 $(TAO_ROOT)/tao/TimeBaseC.h \
 $(TAO_ROOT)/tao/SmartProxies/Smart_Proxies.h \
 $(TAO_ROOT)/tao/SmartProxies/smartproxies_export.h \
 $(TAO_ROOT)/tao/TAO_Singleton.h \
 $(TAO_ROOT)/tao/TAO_Singleton.inl \
 $(TAO_ROOT)/tao/TAO_Singleton.cpp \
 $(ACE_ROOT)/ace/Object_Manager.h \
 $(ACE_ROOT)/ace/Object_Manager.i \
 $(ACE_ROOT)/ace/Managed_Object.h \
 $(ACE_ROOT)/ace/Managed_Object.i \
 $(ACE_ROOT)/ace/Managed_Object.cpp \
 $(TAO_ROOT)/tao/TAO_Singleton_Manager.h \
 $(TAO_ROOT)/tao/TAO_Singleton_Manager.inl \
 $(TAO_ROOT)/tao/SmartProxies/Smart_Proxies.inl \
 $(TAO_ROOT)/tao/TimeBaseC.i \
 $(TAO_ROOT)/tao/IOPC.h \
 $(TAO_ROOT)/tao/IOPC.i \
 $(TAO_ROOT)/tao/PollableC.h \
 $(TAO_ROOT)/tao/PollableC.i \
 $(TAO_ROOT)/tao/MessagingC.i \
 $(TAO_ROOT)/tao/PortableInterceptorC.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosNamingC.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/Naming/naming_export.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosNamingC.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/IOR_Multicast.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/svc_utils_export.h \
 $(ACE_ROOT)/ace/INET_Addr.h \
 $(ACE_ROOT)/ace/Addr.h \
 $(ACE_ROOT)/ace/Addr.i \
 $(ACE_ROOT)/ace/INET_Addr.i \
 $(ACE_ROOT)/ace/SOCK_Dgram_Mcast.h \
 $(ACE_ROOT)/ace/SOCK_Dgram.h \
 $(ACE_ROOT)/ace/SOCK.h \
 $(ACE_ROOT)/ace/IPC_SAP.h \
 $(ACE_ROOT)/ace/IPC_SAP.i \
 $(ACE_ROOT)/ace/SOCK.i \
 $(ACE_ROOT)/ace/SOCK_Dgram.i \
 $(ACE_ROOT)/ace/SOCK_Dgram_Mcast.i \
 $(ACE_ROOT)/ace/Reactor.h \
 $(ACE_ROOT)/ace/Handle_Set.h \
 $(ACE_ROOT)/ace/Handle_Set.i \
 $(ACE_ROOT)/ace/Timer_Queue.h \
 $(ACE_ROOT)/ace/Timer_Queue_T.h \
 $(ACE_ROOT)/ace/Test_and_Set.h \
 $(ACE_ROOT)/ace/Test_and_Set.i \
 $(ACE_ROOT)/ace/Test_and_Set.cpp \
 $(ACE_ROOT)/ace/Timer_Queue_T.i \
 $(ACE_ROOT)/ace/Timer_Queue_T.cpp \
 $(ACE_ROOT)/ace/Reactor.i \
 $(ACE_ROOT)/ace/Reactor_Impl.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/Naming/Naming_Context_Interface.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosNamingS.h \
 $(TAO_ROOT)/tao/PortableServer/PortableServer.h \
 $(TAO_ROOT)/tao/PortableServer/portableserver_export.h \
 $(TAO_ROOT)/tao/PortableServer/PortableServerC.h \
 $(TAO_ROOT)/tao/PortableServer/PortableServerC.i \
 $(TAO_ROOT)/tao/PortableServer/Servant_Base.h \
 $(TAO_ROOT)/tao/Abstract_Servant_Base.h \
 $(TAO_ROOT)/tao/PortableServer/Servant_Base.i \
 $(TAO_ROOT)/tao/PortableServer/Collocated_Object.h \
 $(TAO_ROOT)/tao/PortableServer/Collocated_Object.i \
 $(TAO_ROOT)/tao/PortableServer/ThruPOA_Object_Proxy_Impl.h \
 $(TAO_ROOT)/tao/PortableServer/Direct_Object_Proxy_Impl.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosNamingS_T.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosNamingS_T.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosNamingS_T.cpp \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosNamingS.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AV/AVStreams_i.h \
 $(ACE_ROOT)/ace/ATM_Addr.h \
 $(ACE_ROOT)/ace/ATM_Addr.i \
 $(ACE_ROOT)/ace/Containers_T.h \
 $(ACE_ROOT)/ace/Containers.h \
 $(ACE_ROOT)/ace/Containers.i \
 $(ACE_ROOT)/ace/Array_Base.h \
 $(ACE_ROOT)/ace/Array_Base.inl \
 $(ACE_ROOT)/ace/Array_Base.cpp \
 $(ACE_ROOT)/ace/Containers_T.i \
 $(ACE_ROOT)/ace/Containers_T.cpp \
 $(ACE_ROOT)/ace/Process.h \
 $(ACE_ROOT)/ace/Process.i \
 $(ACE_ROOT)/ace/SOCK_CODgram.h \
 $(ACE_ROOT)/ace/SOCK_IO.h \
 $(ACE_ROOT)/ace/SOCK_IO.i \
 $(ACE_ROOT)/ace/SOCK_CODgram.i \
 $(ACE_ROOT)/ace/SOCK_Connector.h \
 $(ACE_ROOT)/ace/SOCK_Stream.h \
 $(ACE_ROOT)/ace/SOCK_Stream.i \
 $(ACE_ROOT)/ace/Time_Value.h \
 $(ACE_ROOT)/ace/SOCK_Connector.i \
 $(ACE_ROOT)/ace/Connector.h \
 $(ACE_ROOT)/ace/Service_Config.h \
 $(ACE_ROOT)/ace/Service_Object.h \
 $(ACE_ROOT)/ace/Shared_Object.h \
 $(ACE_ROOT)/ace/Shared_Object.i \
 $(ACE_ROOT)/ace/Service_Object.i \
 $(ACE_ROOT)/ace/Service_Config.i \
 $(ACE_ROOT)/ace/Svc_Conf_Tokens.h \
 $(ACE_ROOT)/ace/Map_Manager.h \
 $(ACE_ROOT)/ace/Map_Manager.i \
 $(ACE_ROOT)/ace/Map_Manager.cpp \
 $(ACE_ROOT)/ace/Svc_Handler.h \
 $(ACE_ROOT)/ace/Synch_Options.h \
 $(ACE_ROOT)/ace/Synch_Options.i \
 $(ACE_ROOT)/ace/Task.h \
 $(ACE_ROOT)/ace/Thread_Manager.h \
 $(ACE_ROOT)/ace/Singleton.h \
 $(ACE_ROOT)/ace/Singleton.i \
 $(ACE_ROOT)/ace/Singleton.cpp \
 $(ACE_ROOT)/ace/Thread_Manager.i \
 $(ACE_ROOT)/ace/Task.i \
 $(ACE_ROOT)/ace/Task_T.h \
 $(ACE_ROOT)/ace/Message_Queue.h \
 $(ACE_ROOT)/ace/IO_Cntl_Msg.h \
 $(ACE_ROOT)/ace/Message_Queue_T.h \
 $(ACE_ROOT)/ace/Message_Queue_T.i \
 $(ACE_ROOT)/ace/Message_Queue_T.cpp \
 $(ACE_ROOT)/ace/Strategies.h \
 $(ACE_ROOT)/ace/Strategies_T.h \
 $(ACE_ROOT)/ace/Hash_Map_Manager.h \
 $(ACE_ROOT)/ace/Functor.h \
 $(ACE_ROOT)/ace/Functor.i \
 $(ACE_ROOT)/ace/Functor_T.h \
 $(ACE_ROOT)/ace/Functor_T.i \
 $(ACE_ROOT)/ace/Functor_T.cpp \
 $(ACE_ROOT)/ace/Hash_Map_Manager_T.h \
 $(ACE_ROOT)/ace/Hash_Map_Manager_T.i \
 $(ACE_ROOT)/ace/Hash_Map_Manager_T.cpp \
 $(ACE_ROOT)/ace/Strategies_T.i \
 $(ACE_ROOT)/ace/Strategies_T.cpp \
 $(ACE_ROOT)/ace/Service_Repository.h \
 $(ACE_ROOT)/ace/Service_Types.h \
 $(ACE_ROOT)/ace/Service_Types.i \
 $(ACE_ROOT)/ace/Service_Repository.i \
 $(ACE_ROOT)/ace/WFMO_Reactor.h \
 $(ACE_ROOT)/ace/Process_Mutex.h \
 $(ACE_ROOT)/ace/Process_Mutex.inl \
 $(ACE_ROOT)/ace/WFMO_Reactor.i \
 $(ACE_ROOT)/ace/Strategies.i \
 $(ACE_ROOT)/ace/Message_Queue.i \
 $(ACE_ROOT)/ace/Task_T.i \
 $(ACE_ROOT)/ace/Task_T.cpp \
 $(ACE_ROOT)/ace/Module.h \
 $(ACE_ROOT)/ace/Module.i \
 $(ACE_ROOT)/ace/Module.cpp \
 $(ACE_ROOT)/ace/Stream_Modules.h \
 $(ACE_ROOT)/ace/Stream_Modules.cpp \
 $(ACE_ROOT)/ace/Svc_Handler.cpp \
 $(ACE_ROOT)/ace/Dynamic.h \
 $(ACE_ROOT)/ace/Dynamic.i \
 $(ACE_ROOT)/ace/Connector.cpp \
 $(ACE_ROOT)/ace/Acceptor.h \
 $(ACE_ROOT)/ace/Acceptor.cpp \
 $(ACE_ROOT)/ace/SOCK_Acceptor.h \
 $(ACE_ROOT)/ace/SOCK_Acceptor.i \
 $(TAO_ROOT)/tao/PortableServer/ORB_Manager.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AV/AV_export.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosPropertyServiceS.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosPropertyServiceC.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/Property/property_export.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosPropertyServiceC.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosPropertyServiceS_T.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosPropertyServiceS_T.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosPropertyServiceS_T.cpp \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosPropertyServiceS.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AVStreamsS.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AVStreamsC.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AVStreamsC.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AVStreamsS_T.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AVStreamsS_T.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AVStreamsS_T.cpp \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AVStreamsS.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/Property/CosPropertyService_i.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AV/AV_Core.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AV/Endpoint_Strategy.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AV/Endpoint_Strategy_T.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AV/Endpoint_Strategy_T.cpp \
 $(TAO_ROOT)/tao/debug.h \
 $(ACE_ROOT)/ace/Process_Semaphore.h \
 $(ACE_ROOT)/ace/Process_Semaphore.inl \
 $(TAO_ROOT)/orbsvcs/orbsvcs/Null_MediaCtrlS.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/Null_MediaCtrlC.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/Null_MediaCtrlC.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/Null_MediaCtrlS_T.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/Null_MediaCtrlS_T.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/Null_MediaCtrlS_T.cpp \
 $(TAO_ROOT)/orbsvcs/orbsvcs/Null_MediaCtrlS.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AV/FlowSpec_Entry.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AV/Transport.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AV/Transport.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AV/FlowSpec_Entry.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AV/AVStreams_i.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AV/Flows_T.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AV/Flows_T.cpp \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AV/Protocol_Factory.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AV/Policy.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AV/Policy.i \
 $(ACE_ROOT)/ace/Get_Opt.h \
 $(ACE_ROOT)/ace/Get_Opt.i \
 $(ACE_ROOT)/ace/High_Res_Timer.h \
 $(ACE_ROOT)/ace/High_Res_Timer.i

.obj/receiver.o .obj/receiver.so .shobj/receiver.o .shobj/receiver.so: receiver.cpp receiver.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/Naming/Naming_Utils.h \
 $(ACE_ROOT)/ace/pre.h \
 $(TAO_ROOT)/tao/corba.h \
 $(ACE_ROOT)/ace/post.h \
 $(ACE_ROOT)/ace/ACE_export.h \
 $(ACE_ROOT)/ace/svc_export.h \
 $(ACE_ROOT)/ace/ace_wchar.h \
 $(ACE_ROOT)/ace/ace_wchar.inl \
 $(ACE_ROOT)/ace/OS_Errno.h \
 $(ACE_ROOT)/ace/OS_Export.h \
 $(ACE_ROOT)/ace/OS_Errno.inl \
 $(TAO_ROOT)/tao/corbafwd.h \
 $(ACE_ROOT)/ace/CDR_Base.h \
 $(ACE_ROOT)/ace/Basic_Types.h \
 $(ACE_ROOT)/ace/Basic_Types.i \
 $(ACE_ROOT)/ace/Message_Block.h \
 $(ACE_ROOT)/ace/ACE.h \
 $(ACE_ROOT)/ace/OS.h \
 $(ACE_ROOT)/ace/OS_Dirent.h \
 $(ACE_ROOT)/ace/OS_Dirent.inl \
 $(ACE_ROOT)/ace/OS_String.h \
 $(ACE_ROOT)/ace/OS_String.inl \
 $(ACE_ROOT)/ace/OS_Memory.h \
 $(ACE_ROOT)/ace/OS_Memory.inl \
 $(ACE_ROOT)/ace/OS_TLI.h \
 $(ACE_ROOT)/ace/OS_TLI.inl \
 $(ACE_ROOT)/ace/Min_Max.h \
 $(ACE_ROOT)/ace/streams.h \
 $(ACE_ROOT)/ace/Trace.h \
 $(ACE_ROOT)/ace/OS.i \
 $(ACE_ROOT)/ace/Flag_Manip.h \
 $(ACE_ROOT)/ace/Flag_Manip.i \
 $(ACE_ROOT)/ace/Handle_Ops.h \
 $(ACE_ROOT)/ace/Handle_Ops.i \
 $(ACE_ROOT)/ace/Lib_Find.h \
 $(ACE_ROOT)/ace/Lib_Find.i \
 $(ACE_ROOT)/ace/Init_ACE.h \
 $(ACE_ROOT)/ace/Init_ACE.i \
 $(ACE_ROOT)/ace/Sock_Connect.h \
 $(ACE_ROOT)/ace/Sock_Connect.i \
 $(ACE_ROOT)/ace/ACE.i \
 $(ACE_ROOT)/ace/Malloc.h \
 $(ACE_ROOT)/ace/Log_Msg.h \
 $(ACE_ROOT)/ace/Log_Record.h \
 $(ACE_ROOT)/ace/Log_Priority.h \
 $(ACE_ROOT)/ace/Log_Record.i \
 $(ACE_ROOT)/ace/OS_Log_Msg_Attributes.h \
 $(ACE_ROOT)/ace/OS_Log_Msg_Attributes.inl \
 $(ACE_ROOT)/ace/Malloc.i \
 $(ACE_ROOT)/ace/Malloc_T.h \
 $(ACE_ROOT)/ace/Synch.h \
 $(ACE_ROOT)/ace/Synch.i \
 $(ACE_ROOT)/ace/Synch_T.h \
 $(ACE_ROOT)/ace/Synch_T.i \
 $(ACE_ROOT)/ace/Thread.h \
 $(ACE_ROOT)/ace/Thread_Adapter.h \
 $(ACE_ROOT)/ace/Base_Thread_Adapter.h \
 $(ACE_ROOT)/ace/Base_Thread_Adapter.inl \
 $(ACE_ROOT)/ace/Thread_Adapter.inl \
 $(ACE_ROOT)/ace/Thread.i \
 $(ACE_ROOT)/ace/Atomic_Op.i \
 $(ACE_ROOT)/ace/Synch_T.cpp \
 $(ACE_ROOT)/ace/Malloc_Allocator.h \
 $(ACE_ROOT)/ace/Malloc_Base.h \
 $(ACE_ROOT)/ace/Malloc_Allocator.i \
 $(ACE_ROOT)/ace/Free_List.h \
 $(ACE_ROOT)/ace/Free_List.i \
 $(ACE_ROOT)/ace/Free_List.cpp \
 $(ACE_ROOT)/ace/Malloc_T.i \
 $(ACE_ROOT)/ace/Malloc_T.cpp \
 $(ACE_ROOT)/ace/Memory_Pool.h \
 $(ACE_ROOT)/ace/Event_Handler.h \
 $(ACE_ROOT)/ace/Event_Handler.i \
 $(ACE_ROOT)/ace/Signal.h \
 $(ACE_ROOT)/ace/Signal.i \
 $(ACE_ROOT)/ace/Mem_Map.h \
 $(ACE_ROOT)/ace/Mem_Map.i \
 $(ACE_ROOT)/ace/SV_Semaphore_Complex.h \
 $(ACE_ROOT)/ace/SV_Semaphore_Simple.h \
 $(ACE_ROOT)/ace/SV_Semaphore_Simple.i \
 $(ACE_ROOT)/ace/SV_Semaphore_Complex.i \
 $(ACE_ROOT)/ace/Unbounded_Set.h \
 $(ACE_ROOT)/ace/Node.h \
 $(ACE_ROOT)/ace/Node.cpp \
 $(ACE_ROOT)/ace/Unbounded_Set.inl \
 $(ACE_ROOT)/ace/Unbounded_Set.cpp \
 $(ACE_ROOT)/ace/Memory_Pool.i \
 $(ACE_ROOT)/ace/Message_Block.i \
 $(ACE_ROOT)/ace/Message_Block_T.h \
 $(ACE_ROOT)/ace/Message_Block_T.i \
 $(ACE_ROOT)/ace/Message_Block_T.cpp \
 $(ACE_ROOT)/ace/CDR_Base.inl \
 $(TAO_ROOT)/tao/try_macros.h \
 $(TAO_ROOT)/tao/orbconf.h \
 $(ACE_ROOT)/ace/CORBA_macros.h \
 $(TAO_ROOT)/tao/varbase.h \
 $(TAO_ROOT)/tao/TAO_Export.h \
 $(TAO_ROOT)/tao/corbafwd.i \
 $(TAO_ROOT)/tao/Typecode.h \
 $(TAO_ROOT)/tao/Exception.h \
 $(ACE_ROOT)/ace/SString.h \
 $(ACE_ROOT)/ace/SString.i \
 $(TAO_ROOT)/tao/Exception.i \
 $(TAO_ROOT)/tao/Typecode.i \
 $(TAO_ROOT)/tao/Any.h \
 $(TAO_ROOT)/tao/CDR.h \
 $(ACE_ROOT)/ace/CDR_Stream.h \
 $(ACE_ROOT)/ace/CDR_Stream.i \
 $(TAO_ROOT)/tao/CDR.i \
 $(TAO_ROOT)/tao/Environment.h \
 $(TAO_ROOT)/tao/Environment.i \
 $(TAO_ROOT)/tao/Object.h \
 $(TAO_ROOT)/tao/Object_Proxy_Broker.h \
 $(TAO_ROOT)/tao/Object_Proxy_Impl.h \
 $(TAO_ROOT)/tao/Object.i \
 $(TAO_ROOT)/tao/Any.i \
 $(TAO_ROOT)/tao/NVList.h \
 $(ACE_ROOT)/ace/Unbounded_Queue.h \
 $(ACE_ROOT)/ace/Unbounded_Queue.inl \
 $(ACE_ROOT)/ace/Unbounded_Queue.cpp \
 $(TAO_ROOT)/tao/NVList.i \
 $(TAO_ROOT)/tao/LocalObject.h \
 $(TAO_ROOT)/tao/LocalObject.i \
 $(TAO_ROOT)/tao/Principal.h \
 $(TAO_ROOT)/tao/OctetSeqC.h \
 $(TAO_ROOT)/tao/Sequence.h \
 $(TAO_ROOT)/tao/Managed_Types.h \
 $(TAO_ROOT)/tao/Managed_Types.i \
 $(TAO_ROOT)/tao/Sequence.i \
 $(TAO_ROOT)/tao/Sequence_T.h \
 $(TAO_ROOT)/tao/Sequence_T.i \
 $(TAO_ROOT)/tao/Sequence_T.cpp \
 $(TAO_ROOT)/tao/OctetSeqC.i \
 $(TAO_ROOT)/tao/Principal.i \
 $(TAO_ROOT)/tao/ORB.h \
 $(TAO_ROOT)/tao/Services.h \
 $(TAO_ROOT)/tao/Services.i \
 $(TAO_ROOT)/tao/CORBA_String.h \
 $(TAO_ROOT)/tao/CORBA_String.inl \
 $(TAO_ROOT)/tao/PolicyC.h \
 $(TAO_ROOT)/tao/Encodable.h \
 $(TAO_ROOT)/tao/Remote_Object_Proxy_Impl.h \
 $(TAO_ROOT)/tao/CurrentC.h \
 $(TAO_ROOT)/tao/CurrentC.i \
 $(TAO_ROOT)/tao/PolicyC.i \
 $(TAO_ROOT)/tao/ORB.i \
 $(TAO_ROOT)/tao/BoundsC.h \
 $(TAO_ROOT)/tao/BoundsC.i \
 $(TAO_ROOT)/tao/ValueBase.h \
 $(TAO_ROOT)/tao/ValueBase.i \
 $(TAO_ROOT)/tao/ValueFactory.h \
 $(TAO_ROOT)/tao/ValueFactory.i \
 $(TAO_ROOT)/tao/DomainC.h \
 $(TAO_ROOT)/tao/DomainC.i \
 $(TAO_ROOT)/tao/WrongTransactionC.h \
 $(TAO_ROOT)/tao/Object_KeyC.h \
 $(TAO_ROOT)/tao/Object_KeyC.i \
 $(TAO_ROOT)/tao/ObjectIDList.h \
 $(TAO_ROOT)/tao/ObjectIDList.i \
 $(TAO_ROOT)/tao/StringSeqC.h \
 $(TAO_ROOT)/tao/StringSeqC.i \
 $(TAO_ROOT)/tao/PortableInterceptorC.h \
 $(TAO_ROOT)/tao/DynamicC.h \
 $(TAO_ROOT)/tao/DynamicC.i \
 $(TAO_ROOT)/tao/MessagingC.h \
 $(TAO_ROOT)/tao/TimeBaseC.h \
 $(TAO_ROOT)/tao/SmartProxies/Smart_Proxies.h \
 $(TAO_ROOT)/tao/SmartProxies/smartproxies_export.h \
 $(TAO_ROOT)/tao/TAO_Singleton.h \
 $(TAO_ROOT)/tao/TAO_Singleton.inl \
 $(TAO_ROOT)/tao/TAO_Singleton.cpp \
 $(ACE_ROOT)/ace/Object_Manager.h \
 $(ACE_ROOT)/ace/Object_Manager.i \
 $(ACE_ROOT)/ace/Managed_Object.h \
 $(ACE_ROOT)/ace/Managed_Object.i \
 $(ACE_ROOT)/ace/Managed_Object.cpp \
 $(TAO_ROOT)/tao/TAO_Singleton_Manager.h \
 $(TAO_ROOT)/tao/TAO_Singleton_Manager.inl \
 $(TAO_ROOT)/tao/SmartProxies/Smart_Proxies.inl \
 $(TAO_ROOT)/tao/TimeBaseC.i \
 $(TAO_ROOT)/tao/IOPC.h \
 $(TAO_ROOT)/tao/IOPC.i \
 $(TAO_ROOT)/tao/PollableC.h \
 $(TAO_ROOT)/tao/PollableC.i \
 $(TAO_ROOT)/tao/MessagingC.i \
 $(TAO_ROOT)/tao/PortableInterceptorC.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosNamingC.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/Naming/naming_export.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosNamingC.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/IOR_Multicast.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/svc_utils_export.h \
 $(ACE_ROOT)/ace/INET_Addr.h \
 $(ACE_ROOT)/ace/Addr.h \
 $(ACE_ROOT)/ace/Addr.i \
 $(ACE_ROOT)/ace/INET_Addr.i \
 $(ACE_ROOT)/ace/SOCK_Dgram_Mcast.h \
 $(ACE_ROOT)/ace/SOCK_Dgram.h \
 $(ACE_ROOT)/ace/SOCK.h \
 $(ACE_ROOT)/ace/IPC_SAP.h \
 $(ACE_ROOT)/ace/IPC_SAP.i \
 $(ACE_ROOT)/ace/SOCK.i \
 $(ACE_ROOT)/ace/SOCK_Dgram.i \
 $(ACE_ROOT)/ace/SOCK_Dgram_Mcast.i \
 $(ACE_ROOT)/ace/Reactor.h \
 $(ACE_ROOT)/ace/Handle_Set.h \
 $(ACE_ROOT)/ace/Handle_Set.i \
 $(ACE_ROOT)/ace/Timer_Queue.h \
 $(ACE_ROOT)/ace/Timer_Queue_T.h \
 $(ACE_ROOT)/ace/Test_and_Set.h \
 $(ACE_ROOT)/ace/Test_and_Set.i \
 $(ACE_ROOT)/ace/Test_and_Set.cpp \
 $(ACE_ROOT)/ace/Timer_Queue_T.i \
 $(ACE_ROOT)/ace/Timer_Queue_T.cpp \
 $(ACE_ROOT)/ace/Reactor.i \
 $(ACE_ROOT)/ace/Reactor_Impl.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/Naming/Naming_Context_Interface.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosNamingS.h \
 $(TAO_ROOT)/tao/PortableServer/PortableServer.h \
 $(TAO_ROOT)/tao/PortableServer/portableserver_export.h \
 $(TAO_ROOT)/tao/PortableServer/PortableServerC.h \
 $(TAO_ROOT)/tao/PortableServer/PortableServerC.i \
 $(TAO_ROOT)/tao/PortableServer/Servant_Base.h \
 $(TAO_ROOT)/tao/Abstract_Servant_Base.h \
 $(TAO_ROOT)/tao/PortableServer/Servant_Base.i \
 $(TAO_ROOT)/tao/PortableServer/Collocated_Object.h \
 $(TAO_ROOT)/tao/PortableServer/Collocated_Object.i \
 $(TAO_ROOT)/tao/PortableServer/ThruPOA_Object_Proxy_Impl.h \
 $(TAO_ROOT)/tao/PortableServer/Direct_Object_Proxy_Impl.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosNamingS_T.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosNamingS_T.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosNamingS_T.cpp \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosNamingS.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AV/AVStreams_i.h \
 $(ACE_ROOT)/ace/ATM_Addr.h \
 $(ACE_ROOT)/ace/ATM_Addr.i \
 $(ACE_ROOT)/ace/Containers_T.h \
 $(ACE_ROOT)/ace/Containers.h \
 $(ACE_ROOT)/ace/Containers.i \
 $(ACE_ROOT)/ace/Array_Base.h \
 $(ACE_ROOT)/ace/Array_Base.inl \
 $(ACE_ROOT)/ace/Array_Base.cpp \
 $(ACE_ROOT)/ace/Containers_T.i \
 $(ACE_ROOT)/ace/Containers_T.cpp \
 $(ACE_ROOT)/ace/Process.h \
 $(ACE_ROOT)/ace/Process.i \
 $(ACE_ROOT)/ace/SOCK_CODgram.h \
 $(ACE_ROOT)/ace/SOCK_IO.h \
 $(ACE_ROOT)/ace/SOCK_IO.i \
 $(ACE_ROOT)/ace/SOCK_CODgram.i \
 $(ACE_ROOT)/ace/SOCK_Connector.h \
 $(ACE_ROOT)/ace/SOCK_Stream.h \
 $(ACE_ROOT)/ace/SOCK_Stream.i \
 $(ACE_ROOT)/ace/Time_Value.h \
 $(ACE_ROOT)/ace/SOCK_Connector.i \
 $(ACE_ROOT)/ace/Connector.h \
 $(ACE_ROOT)/ace/Service_Config.h \
 $(ACE_ROOT)/ace/Service_Object.h \
 $(ACE_ROOT)/ace/Shared_Object.h \
 $(ACE_ROOT)/ace/Shared_Object.i \
 $(ACE_ROOT)/ace/Service_Object.i \
 $(ACE_ROOT)/ace/Service_Config.i \
 $(ACE_ROOT)/ace/Svc_Conf_Tokens.h \
 $(ACE_ROOT)/ace/Map_Manager.h \
 $(ACE_ROOT)/ace/Map_Manager.i \
 $(ACE_ROOT)/ace/Map_Manager.cpp \
 $(ACE_ROOT)/ace/Svc_Handler.h \
 $(ACE_ROOT)/ace/Synch_Options.h \
 $(ACE_ROOT)/ace/Synch_Options.i \
 $(ACE_ROOT)/ace/Task.h \
 $(ACE_ROOT)/ace/Thread_Manager.h \
 $(ACE_ROOT)/ace/Singleton.h \
 $(ACE_ROOT)/ace/Singleton.i \
 $(ACE_ROOT)/ace/Singleton.cpp \
 $(ACE_ROOT)/ace/Thread_Manager.i \
 $(ACE_ROOT)/ace/Task.i \
 $(ACE_ROOT)/ace/Task_T.h \
 $(ACE_ROOT)/ace/Message_Queue.h \
 $(ACE_ROOT)/ace/IO_Cntl_Msg.h \
 $(ACE_ROOT)/ace/Message_Queue_T.h \
 $(ACE_ROOT)/ace/Message_Queue_T.i \
 $(ACE_ROOT)/ace/Message_Queue_T.cpp \
 $(ACE_ROOT)/ace/Strategies.h \
 $(ACE_ROOT)/ace/Strategies_T.h \
 $(ACE_ROOT)/ace/Hash_Map_Manager.h \
 $(ACE_ROOT)/ace/Functor.h \
 $(ACE_ROOT)/ace/Functor.i \
 $(ACE_ROOT)/ace/Functor_T.h \
 $(ACE_ROOT)/ace/Functor_T.i \
 $(ACE_ROOT)/ace/Functor_T.cpp \
 $(ACE_ROOT)/ace/Hash_Map_Manager_T.h \
 $(ACE_ROOT)/ace/Hash_Map_Manager_T.i \
 $(ACE_ROOT)/ace/Hash_Map_Manager_T.cpp \
 $(ACE_ROOT)/ace/Strategies_T.i \
 $(ACE_ROOT)/ace/Strategies_T.cpp \
 $(ACE_ROOT)/ace/Service_Repository.h \
 $(ACE_ROOT)/ace/Service_Types.h \
 $(ACE_ROOT)/ace/Service_Types.i \
 $(ACE_ROOT)/ace/Service_Repository.i \
 $(ACE_ROOT)/ace/WFMO_Reactor.h \
 $(ACE_ROOT)/ace/Process_Mutex.h \
 $(ACE_ROOT)/ace/Process_Mutex.inl \
 $(ACE_ROOT)/ace/WFMO_Reactor.i \
 $(ACE_ROOT)/ace/Strategies.i \
 $(ACE_ROOT)/ace/Message_Queue.i \
 $(ACE_ROOT)/ace/Task_T.i \
 $(ACE_ROOT)/ace/Task_T.cpp \
 $(ACE_ROOT)/ace/Module.h \
 $(ACE_ROOT)/ace/Module.i \
 $(ACE_ROOT)/ace/Module.cpp \
 $(ACE_ROOT)/ace/Stream_Modules.h \
 $(ACE_ROOT)/ace/Stream_Modules.cpp \
 $(ACE_ROOT)/ace/Svc_Handler.cpp \
 $(ACE_ROOT)/ace/Dynamic.h \
 $(ACE_ROOT)/ace/Dynamic.i \
 $(ACE_ROOT)/ace/Connector.cpp \
 $(ACE_ROOT)/ace/Acceptor.h \
 $(ACE_ROOT)/ace/Acceptor.cpp \
 $(ACE_ROOT)/ace/SOCK_Acceptor.h \
 $(ACE_ROOT)/ace/SOCK_Acceptor.i \
 $(TAO_ROOT)/tao/PortableServer/ORB_Manager.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AV/AV_export.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosPropertyServiceS.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosPropertyServiceC.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/Property/property_export.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosPropertyServiceC.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosPropertyServiceS_T.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosPropertyServiceS_T.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosPropertyServiceS_T.cpp \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosPropertyServiceS.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AVStreamsS.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AVStreamsC.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AVStreamsC.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AVStreamsS_T.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AVStreamsS_T.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AVStreamsS_T.cpp \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AVStreamsS.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/Property/CosPropertyService_i.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AV/AV_Core.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AV/Endpoint_Strategy.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AV/Endpoint_Strategy_T.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AV/Endpoint_Strategy_T.cpp \
 $(TAO_ROOT)/tao/debug.h \
 $(ACE_ROOT)/ace/Process_Semaphore.h \
 $(ACE_ROOT)/ace/Process_Semaphore.inl \
 $(TAO_ROOT)/orbsvcs/orbsvcs/Null_MediaCtrlS.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/Null_MediaCtrlC.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/Null_MediaCtrlC.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/Null_MediaCtrlS_T.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/Null_MediaCtrlS_T.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/Null_MediaCtrlS_T.cpp \
 $(TAO_ROOT)/orbsvcs/orbsvcs/Null_MediaCtrlS.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AV/FlowSpec_Entry.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AV/Transport.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AV/Transport.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AV/FlowSpec_Entry.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AV/AVStreams_i.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AV/Flows_T.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AV/Flows_T.cpp \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AV/Policy.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/AV/Policy.i \
 $(ACE_ROOT)/ace/Get_Opt.h \
 $(ACE_ROOT)/ace/Get_Opt.i

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
