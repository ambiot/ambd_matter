include $(MAKE_INCLUDE_GEN)

# Include folder list
# -------------------------------------------------------------------

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/common/application/matter
ATCMDDIR = $(BASEDIR)/component/common/application/matter/common/atcmd
BTDIR = $(BASEDIR)/component/common/application/matter/bluetooth/bt_matter_adapter
MBEDDIR = $(BASEDIR)/component/common/application/matter/mbedtls
PORTDIR = $(BASEDIR)/component/common/application/matter/port
PROTOBUFDIR = $(BASEDIR)/component/common/application/matter/protobuf
NANOPBDIR = $(BASEDIR)/component/common/application/matter/protobuf/nanopb
CHIPTESTDIR = $(BASEDIR)/component/common/application/matter/example/chiptest

vpath %.c $(DIR) $(shell find $(DIR) -type d)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#



# Source file list
# -------------------------------------------------------------------
CSRC += $(ATCMDDIR)/atcmd_matter.c
CSRC += $(BTDIR)/bt_matter_adapter_app_main.c
CSRC += $(BTDIR)/bt_matter_adapter_app_task.c
CSRC += $(BTDIR)/bt_matter_adapter_peripheral_app.c
CSRC += $(BTDIR)/bt_matter_adapter_service.c
CSRC += $(BTDIR)/bt_matter_adapter_wifi.c
CSRC += $(MBEDDIR)/net_sockets.c
CSRC += $(PORTDIR)/matter_dcts.c
CSRC += $(PORTDIR)/matter_ota.c
CSRC += $(PORTDIR)/matter_timers.c
CSRC += $(PORTDIR)/matter_utils.c
CSRC += $(PORTDIR)/matter_wifis.c
CSRC += $(PORTDIR)/matter_freertos.c
CSRC += $(PROTOBUFDIR)/ameba_factory.pb.c
CSRC += $(NANOPBDIR)/pb_common.c
CSRC += $(NANOPBDIR)/pb_decode.c
CSRC += $(NANOPBDIR)/pb_encode.c
CSRC += $(CHIPTESTDIR)/example_matter.c

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))

#*****************************************************************************#
#                               Include Dependency                            #
#*****************************************************************************#
-include $(OBJS:.o=.d)


#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#
all: CORE_TARGETS COPY_RAM_OBJS

#*****************************************************************************#
#              GENERATE OBJECT FILE 
#*****************************************************************************#
CORE_TARGETS: $(OBJS)

#*****************************************************************************#
#              CLEAN GENERATED FILES                                          #
#*****************************************************************************#
clean: CLEAN_OBJS 
	$(REMOVE) *.o
	$(REMOVE) *.i
	$(REMOVE) *.s
	$(REMOVE) *.d

-include $(DEPS)

