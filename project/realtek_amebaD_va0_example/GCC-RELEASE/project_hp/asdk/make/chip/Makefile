include $(MAKE_INCLUDE_GEN)


.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
OBJS =

#*****************************************************************************#
#                               Include Dependency                            #
#*****************************************************************************#
-include $(OBJS:.o=.d)

# GLOBAL_CFLAGS += -I$(BASEDIR)/component/common/bluetooth/realtek/sdk/example/bt_matter_adapter

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
	make -C all_clusters_app clean
	make -C lighting_app clean

-include $(DEPS)
