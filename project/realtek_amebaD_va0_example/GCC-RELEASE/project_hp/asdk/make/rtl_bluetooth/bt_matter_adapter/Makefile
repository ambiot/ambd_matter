
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

include ../amebad_bsp/Makefile

MATTER_BT_DIR = $(BASEDIR)/component/common/application/matter/common/bluetooth/bt_matter_adapter
# board-specific
MODULE_IFLAGS += \
   -I$(MATTER_BT_DIR)

CSRC += \
    $(MATTER_BT_DIR)/bt_matter_adapter_app_main.c \
    $(MATTER_BT_DIR)/bt_matter_adapter_app_task.c \
    $(MATTER_BT_DIR)/bt_matter_adapter_peripheral_app.c \
    $(MATTER_BT_DIR)/bt_matter_adapter_service.c \
    $(MATTER_BT_DIR)/bt_matter_adapter_wifi.c

OBJS = $(CSRC:.c=.o)
TOBJS = $(notdir $(OBJS))
LOBJS = $(addprefix objs/,$(TOBJS))

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# LIBBLUETOOTH_OBJS_PATH = $(shell pwd)/objs
# Define the Rules to build the core targets
all: CORE_TARGETS COPY_RAM_OBJS
	# mkdir -p $(LIBBLUETOOTH_OBJS_PATH)
	# for i in $(OBJS); do \
	# 	 $(COPY)  $$i $(LIBBLUETOOTH_OBJS_PATH) -f;\
	# 	done
	# $(REMOVE) *.i
	# $(REMOVE) *.s
	# $(REMOVE) *.d

#*****************************************************************************#
#              GENERATE OBJECT FILE
#*****************************************************************************#
CORE_TARGETS: $(OBJS)

#*****************************************************************************#
#                        RULES TO CLEAN TARGETS                               #
#*****************************************************************************#
clean: CLEAN_OBJS
	$(REMOVE) *.o
	$(REMOVE) *.i
	$(REMOVE) *.s
	$(REMOVE) *.d

-include $(DEPS)
