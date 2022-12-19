
include $(MAKE_INCLUDE_GEN)

.PHONY: lib clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR_BOOTLOADER = $(BASEDIR)/component/soc/realtek/amebad/bootloader


vpath %.c $(DIR_BOOTLOADER) 

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC =	$(DIR_BOOTLOADER)/boot_ram_hp.c \
	$(DIR_BOOTLOADER)/boot_flash_hp.c \
	$(DIR_BOOTLOADER)/boot_trustzone_hp.c \


#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

lib: CORE_TARGETS RENAME_LOADER_OBJS COPY_RAM_OBJS
	$(AR) rvs lib_bootloader_hp.a $(OBJS)
	$(MOVE) -f lib_bootloader_hp.a $(ROOTDIR)/lib/application
CORE_TARGETS: $(OBJS)

#*****************************************************************************#
#                        RULES TO CLEAN TARGETS                               #
#*****************************************************************************#
clean: CLEAN_OBJS 
	$(REMOVE) *.o
	$(REMOVE) *.i
	$(REMOVE) *.s
	$(REMOVE) *.d
	$(REMOVE) *.su

-include $(DEPS)
