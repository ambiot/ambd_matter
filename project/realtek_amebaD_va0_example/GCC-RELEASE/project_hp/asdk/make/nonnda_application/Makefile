
include $(MAKE_INCLUDE_GEN)

.PHONY: lib clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR_RAM_HP = $(BASEDIR)/component/soc/realtek/amebad/fwlib/ram_hp
DIR_MISC = $(BASEDIR)/component/soc/realtek/amebad/misc
DIR_RAM_COMMON = $(BASEDIR)/component/soc/realtek/amebad/fwlib/ram_common


vpath %.c $(DIR_RAM_HP) $(DIR_MISC) $(DIR_RAM_COMMON) 

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC =	$(DIR_RAM_HP)/rtl8721dhp_pmc.c \
	$(DIR_RAM_HP)/rtl8721dhp_pmc_ram.c \
	$(DIR_MISC)/rtl8721d_freertos_pmu.c \
	$(DIR_RAM_HP)/rtl8721dhp_psram.c \
	$(DIR_RAM_COMMON)/rtl8721d_rand2.c \


#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

lib: CORE_TARGETS COPY_RAM_OBJS
	$(AR) rvs lib_application_hp.a $(OBJS)
	$(MOVE) -f lib_application_hp.a $(ROOTDIR)/lib/application
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
