#
#    Copyright (c) 2020 Project CHIP Authors
#    All rights reserved.
#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#        http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.

#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#

DIR = $(SRCDIR)
DIR += $(CHIPDIR)/src/app
DIR += $(CHIPDIR)/src/app/server
DIR += $(CHIPDIR)/examples/ota-requestor-app/ota-requestor-common
DIR += $(CHIPDIR)/examples/ota-requestor-app/ameba/main
DIR += $(CHIPDIR)/examples/platform/ameba/ota
DIR += $(CHIPDIR)/examples/providers
DIR += $(CHIPDIR)/zzz_generated/ota-requestor-app/zap-generated
DIR += $(CHIPDIR)/zzz_generated/app-common/app-common/zap-generated
DIR += $(CHIPDIR)/zzz_generated/app-common/app-common/zap-generated/attributes

vpath %.cpp $(DIR) $(shell find $(DIR) -type d)
vpath %.c $(DIR) $(shell find $(DIR) -type d)
#*****************************************************************************#
#                               CFLAGS                                        #
#*****************************************************************************#

GLOBAL_CFLAGS += -DCHIP_PROJECT=1
GLOBAL_CFLAGS += -DCHIP_ADDRESS_RESOLVE_IMPL_INCLUDE_HEADER=\"lib/address_resolve/AddressResolve_DefaultImpl.h\"

#*****************************************************************************#
#                               Include FILE LIST                             #
#*****************************************************************************#

#IFLAGS = -I$(DIR)./
IFLAGS += -I$(CHIPDIR)/component/soc/realtek/amebad/fwlib/include
IFLAGS += -I$(CHIPDIR)/examples/ota-requestor-app/ameba/main/include
IFLAGS += -I$(CHIPDIR)/examples/ota-requestor-app/ameba/build/chip/gen/include
IFLAGS += -I$(CHIPDIR)/examples/ota-requestor-app/ota-requestor-common
IFLAGS += -I$(CHIPDIR)/examples/ota-requestor-app/ota-requestor-common/include
IFLAGS += -I$(CHIPDIR)/examples/platform/ameba
IFLAGS += -I$(CHIPDIR)/examples/providers
IFLAGS += -I$(CHIPDIR)/src/
IFLAGS += -I$(CHIPDIR)/src/app/
IFLAGS += -I$(CHIPDIR)/src/app/clusters/ota-requestor
IFLAGS += -I$(CHIPDIR)/src/app/util/
IFLAGS += -I$(CHIPDIR)/src/app/server/
IFLAGS += -I$(CHIPDIR)/src/controller/data_model
IFLAGS += -I$(CHIPDIR)/src/include/
IFLAGS += -I$(CHIPDIR)/src/lib/
IFLAGS += -I$(CHIPDIR)/third_party/nlassert/repo/include/
IFLAGS += -I$(CHIPDIR)/third_party/nlio/repo/include/
IFLAGS += -I$(CHIPDIR)/third_party/nlunit-test/repo/src
IFLAGS += -I$(CHIPDIR)/zzz_generated/app-common
IFLAGS += -I$(CHIPDIR)/zzz_generated/ota-requestor-app
IFLAGS += -I$(CHIPDIR)/zzz_generated/ota-requestor-app/zap-generated

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#

CPPSRC += $(CHIPDIR)/src/app/server/Server.cpp
CPPSRC += $(CHIPDIR)/src/app/server/Dnssd.cpp
CPPSRC += $(CHIPDIR)/src/app/server/EchoHandler.cpp
CPPSRC += $(CHIPDIR)/src/app/server/OnboardingCodesUtil.cpp
CPPSRC += $(CHIPDIR)/src/app/server/CommissioningWindowManager.cpp

CPPSRC += $(CHIPDIR)/src/app/util/af-event.cpp
#CPPSRC += $(CHIPDIR)/src/app/util/af-main-common.cpp
CPPSRC += $(CHIPDIR)/src/app/util/attribute-storage.cpp
CPPSRC += $(CHIPDIR)/src/app/util/attribute-table.cpp
CPPSRC += $(CHIPDIR)/src/app/util/attribute-size-util.cpp
CPPSRC += $(CHIPDIR)/src/app/util/binding-table.cpp
#CPPSRC += $(CHIPDIR)/src/app/util/CHIPDeviceCallbacksMgr.cpp
#CPPSRC += $(CHIPDIR)/src/app/util/chip-message-send.cpp
CPPSRC += $(CHIPDIR)/src/app/util/DataModelHandler.cpp
CPPSRC += $(CHIPDIR)/src/app/util/ember-compatibility-functions.cpp
CPPSRC += $(CHIPDIR)/src/app/util/ember-global-attribute-access-interface.cpp
CPPSRC += $(CHIPDIR)/src/app/util/ember-io-storage.cpp
CPPSRC += $(CHIPDIR)/src/app/util/ember-print.cpp
CPPSRC += $(CHIPDIR)/src/app/util/message.cpp
CPPSRC += $(CHIPDIR)/src/app/util/util.cpp
CPPSRC += $(CHIPDIR)/src/app/util/error-mapping.cpp
CPPSRC += $(CHIPDIR)/src/app/util/privilege-storage.cpp
#CPPSRC += $(CHIPDIR)/src/app/util/im-client-callbacks.cpp

CPPSRC += $(CHIPDIR)/src/app/clusters/administrator-commissioning-server/administrator-commissioning-server.cpp
CPPSRC += $(CHIPDIR)/src/app/clusters/groups-server/groups-server.cpp
CPPSRC += $(CHIPDIR)/src/app/clusters/basic/basic.cpp
CPPSRC += $(CHIPDIR)/src/app/clusters/bindings/bindings.cpp
CPPSRC += $(CHIPDIR)/src/app/clusters/descriptor/descriptor.cpp
CPPSRC += $(CHIPDIR)/src/app/clusters/diagnostic-logs-server/diagnostic-logs-server.cpp
CPPSRC += $(CHIPDIR)/src/app/clusters/ethernet-network-diagnostics-server/ethernet-network-diagnostics-server.cpp
CPPSRC += $(CHIPDIR)/src/app/clusters/fixed-label-server/fixed-label-server.cpp
CPPSRC += $(CHIPDIR)/src/app/clusters/user-label-server/user-label-server.cpp
CPPSRC += $(CHIPDIR)/src/app/clusters/thread-network-diagnostics-server/thread-network-diagnostics-server.cpp
CPPSRC += $(CHIPDIR)/src/app/clusters/wifi-network-diagnostics-server/wifi-network-diagnostics-server.cpp
CPPSRC += $(CHIPDIR)/src/app/clusters/software-diagnostics-server/software-diagnostics-server.cpp
CPPSRC += $(CHIPDIR)/src/app/clusters/switch-server/switch-server.cpp
CPPSRC += $(CHIPDIR)/src/app/clusters/general-diagnostics-server/general-diagnostics-server.cpp
CPPSRC += $(CHIPDIR)/src/app/clusters/group-key-mgmt-server/group-key-mgmt-server.cpp
CPPSRC += $(CHIPDIR)/src/app/clusters/general-commissioning-server/general-commissioning-server.cpp
CPPSRC += $(CHIPDIR)/src/app/clusters/operational-credentials-server/operational-credentials-server.cpp
CPPSRC += $(CHIPDIR)/src/app/clusters/localization-configuration-server/localization-configuration-server.cpp
CPPSRC += $(CHIPDIR)/src/app/clusters/time-format-localization-server/time-format-localization-server.cpp
CPPSRC += $(CHIPDIR)/src/app/clusters/access-control-server/access-control-server.cpp
CPPSRC += $(CHIPDIR)/src/app/clusters/ota-requestor/BDXDownloader.cpp
CPPSRC += $(CHIPDIR)/src/app/clusters/ota-requestor/DefaultOTARequestor.cpp
CPPSRC += $(CHIPDIR)/src/app/clusters/ota-requestor/DefaultOTARequestorDriver.cpp
CPPSRC += $(CHIPDIR)/src/app/clusters/ota-requestor/ExtendedOTARequestorDriver.cpp
CPPSRC += $(CHIPDIR)/src/app/clusters/ota-requestor/DefaultOTARequestorStorage.cpp
CPPSRC += $(CHIPDIR)/src/app/clusters/ota-requestor/ota-requestor-server.cpp
CPPSRC += $(CHIPDIR)/src/app/clusters/network-commissioning/network-commissioning.cpp
CPPSRC += $(CHIPDIR)/src/app/clusters/fan-control-server/fan-control-server.cpp

CPPSRC += $(CHIPDIR)/src/app/reporting/Engine.cpp

CPPSRC += $(CHIPDIR)/zzz_generated/app-common/app-common/zap-generated/attributes/Accessors.cpp
CPPSRC += $(CHIPDIR)/zzz_generated/app-common/app-common/zap-generated/cluster-objects.cpp

CPPSRC += $(CHIPDIR)/zzz_generated/ota-requestor-app/zap-generated/callback-stub.cpp
CPPSRC += $(CHIPDIR)/zzz_generated/ota-requestor-app/zap-generated/IMClusterCommandHandler.cpp
#CPPSRC += $(CHIPDIR)/zzz_generated/ota-requestor-app/zap-generated/CHIPClusters.cpp
#CPPSRC += $(CHIPDIR)/zzz_generated/ota-requestor-app/zap-generated/CHIPClientCallbacks.cpp

CPPSRC += $(CHIPDIR)/examples/ota-requestor-app/ameba/main/chipinterface.cpp
CPPSRC += $(CHIPDIR)/examples/ota-requestor-app/ameba/main/Globals.cpp
CPPSRC += $(CHIPDIR)/examples/ota-requestor-app/ameba/main/LEDWidget.cpp
CPPSRC += $(CHIPDIR)/examples/ota-requestor-app/ameba/main/CHIPDeviceManager.cpp
CPPSRC += $(CHIPDIR)/examples/ota-requestor-app/ameba/main/DeviceCallbacks.cpp

CPPSRC += $(CHIPDIR)/examples/platform/ameba/ota/OTAInitializer.cpp
CPPSRC += $(CHIPDIR)/examples/providers/DeviceInfoProviderImpl.cpp

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
CPPOBJS = $(notdir $(CPPSRC:.cpp=.o))
COBJS = $(notdir $(CSRC:.c=.o))
OBJS = $(CPPOBJS)
OBJS += $(COBJS)
STATIC_LIB = lib_main.a

#*****************************************************************************#
#                               Include Dependency                            #
#*****************************************************************************#
-include $(OBJS:.o=.d)


#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
all: CORE_TARGETS

#*****************************************************************************#
#              GENERATE OBJECT FILE
#*****************************************************************************#
#CORE_TARGETS:	$(CPPOBJS) $(COBJS)
CORE_TARGETS:	$(OBJS) $(STATIC_LIB)
$(STATIC_LIB):$(OBJS)
	$(AR) rvs $@ $^
	$(MOVE) -f $@ $(ROOTDIR)/lib/application

#*****************************************************************************#
#              CLEAN GENERATED FILES                                          #
#*****************************************************************************#
clean:
	rm -f $(ROOTDIR)/make/chip_main/ota_requestor_app/*.o
	rm -f $(ROOTDIR)/make/chip_main/ota_requestor_app/*.i
	rm -f $(ROOTDIR)/make/chip_main/ota_requestor_app/*.s
	rm -f $(ROOTDIR)/make/chip_main/ota_requestor_app/*.d
	rm -f $(ROOTDIR)/make/chip_main/ota_requestor_app/*.ii
	rm -f $(ROOTDIR)/make/chip_main/ota_requestor_app/*.su

-include $(DEPS)
