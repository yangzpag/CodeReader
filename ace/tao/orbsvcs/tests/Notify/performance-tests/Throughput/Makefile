#----------------------------------------------------------------------------
#
# Makefile,v 1.8 2001/09/18 20:14:39 coryan Exp
#
#----------------------------------------------------------------------------

#----------------------------------------------------------------------------
#       Local macros
#----------------------------------------------------------------------------

ifndef TAO_ROOT
  TAO_ROOT = $(ACE_ROOT)/TAO
endif # ! TAO_ROOT

BIN2 =  Throughput

#### If the orbsvcs library wasn't built with all components, don't
#### try to build certain tests.
TAO_ORBSVCS := $(shell sh $(ACE_ROOT)/bin/ace_components --orbsvcs)
ifeq (Notify,$(findstring Notify,$(TAO_ORBSVCS)))
  ifeq (Naming,$(findstring Naming,$(TAO_ORBSVCS)))
  BIN = $(BIN2)
endif # Naming
endif # Notify

PSRC=$(addsuffix .cpp,$(BIN))
LDLIBS += -lNotifyTests -lTAO_CosNotification -lTAO_CosNaming -lTAO_Svc_Utils -lTAO_IORTable -lTAO_DynamicAny -lTAO_PortableServer -lTAO
CPPFLAGS += -I../../lib -I$(TAO_ROOT) -I$(TAO_ROOT)/orbsvcs \
        $(foreach svc, $(TAO_ORBSVCS), -DTAO_ORBSVCS_HAS_$(svc))

#----------------------------------------------------------------------------
#       Include macros and targets
#----------------------------------------------------------------------------

include $(ACE_ROOT)/include/makeinclude/wrapper_macros.GNU
include $(ACE_ROOT)/include/makeinclude/macros.GNU
include $(TAO_ROOT)/rules.tao.GNU
include $(ACE_ROOT)/include/makeinclude/rules.common.GNU
include $(ACE_ROOT)/include/makeinclude/rules.nonested.GNU
include $(ACE_ROOT)/include/makeinclude/rules.bin.GNU
include $(ACE_ROOT)/include/makeinclude/rules.local.GNU

# To build multiple executables in the same directory on AIX, it works
# best to wipe out any previously-created tempinc directory.
# The compiler/linker isn't too smart about instantiating templates...
ifdef TEMPINCDIR
COMPILE.cc := $(RM) -rf tempinc; $(COMPILE.cc)
endif

#----------------------------------------------------------------------------
#       Local targets
#----------------------------------------------------------------------------

ifeq (Notify,$(findstring Notify,$(TAO_ORBSVCS)))

all: Throughput

# Throughput: $(addprefix $(VDIR),Throughput.o)
#	$(LINK.cc) $(LDFLAGS) -o $@ $^ -lTAO_CosNotification -lTAO_CosNaming $(VLDLIBS) $(POS# TLINK)

endif # Notify

#----------------------------------------------------------------------------
#       Dependencies
#----------------------------------------------------------------------------
# DO NOT DELETE THIS LINE -- g++dep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.



# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
