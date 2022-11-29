
include $(MAKE_INCLUDE_GEN)
IFLAGS               += -I$(BASEDIR)/component/common/network/libcoap/include

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/common/utilities
MATTER_APP_DIR = $(BASEDIR)/component/common/application/matter/application
MATTER_PROTOBUF_DIR = $(BASEDIR)/component/common/application/matter/protobuf

vpath %.c $(DIR)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC +=  \
	$(DIR)/tcptest.c \
	$(DIR)/ssl_client.c \
	$(DIR)/ssl_client_ext.c \
	$(DIR)/http_client.c \
	$(DIR)/xml.c \
	$(DIR)/cJSON.c \
	$(MATTER_APP_DIR)/matter_dcts.c \
	$(MATTER_APP_DIR)/matter_timers.c \
	$(MATTER_APP_DIR)/matter_utils.c \
	$(MATTER_APP_DIR)/matter_wifis.c \
	$(MATTER_PROTOBUF_DIR)/ameba_factory.pb.c \
	$(MATTER_PROTOBUF_DIR)/nanopb/pb_common.c \
	$(MATTER_PROTOBUF_DIR)/nanopb/pb_decode.c \
	$(MATTER_PROTOBUF_DIR)/nanopb/pb_encode.c \

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(CSRC:.c=.o)

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
