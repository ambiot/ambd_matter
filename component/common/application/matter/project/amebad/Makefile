
#*****************************************************************************#
#                            Basic Configurations                             #
#*****************************************************************************#

CURRENT_DIR = $(shell pwd)
ABS_ROOTDIR = $(shell pwd)/../../../../../../project/realtek_amebaD_va0_example/GCC-RELEASE/project_hp/asdk
MATTER_DIR 		= $(ABS_ROOTDIR)/../../../../../component/common/application/matter
MAKE_INCLUDE_GEN = $(ABS_ROOTDIR)/Makefile.include.gen

CONFIG_SHELL := $(shell if [ -x "$$BASH" ]; then echo $$BASH; \
          else if [ -x /bin/bash ]; then echo /bin/bash; \
          else echo sh; fi ; fi)

include $(MAKE_INCLUDE_GEN)
include $(CURRENT_DIR)/Makefile.include.matter.hp.gen

#*****************************************************************************#
#                            MATTER ZAP files                                 #
#*****************************************************************************#
ALL_CLUSTERS_FILE = $(CHIPDIR)/examples/all-clusters-app/ameba/build/chip/codegen/cluster-file.txt
ALL_CLUSTERS_ZAP = $(CHIPDIR)/examples/all-clusters-app/all-clusters-common/all-clusters-app.zap
LIGHTING_FILE = $(CHIPDIR)/examples/lighting-app/ameba/build/chip/codegen/cluster-file.txt
LIGHTING_ZAP = $(CHIPDIR)/examples/lighting-app/lighting-common/lighting-app.zap
LIGHT_SWITCH_FILE = $(CHIPDIR)/examples/light-switch-app/ameba/build/chip/codegen/cluster-file.txt
LIGHT_SWITCH_ZAP = $(CHIPDIR)/examples/light-switch-app/light-switch-common/light-switch-app.zap
THERMOSTAT_PORT_FILE = $(CHIPDIR)/examples/thermostat/ameba/build/chip/codegen/cluster-file.txt
THERMOSTAT_PORT_ZAP = $(CHIPDIR)/examples/thermostat/thermostat-common/thermostat.zap
BRIDGE_PORT_FILE = $(CHIPDIR)/examples/bridge-app/ameba/build/chip/codegen/cluster-file.txt
BRIDGE_PORT_ZAP = $(CHIPDIR)/examples/bridge-app/bridge-common/bridge-app.zap
BRIDGE_DM_FILE = $(BASEDIR)/component/common/application/matter/example/bridge_dm/build/chip/codegen/cluster-file.txt
BRIDGE_DM_ZAP = $(BASEDIR)/component/common/application/matter/example/bridge_dm/bridge-app.zap
REFRIGERATOR_PORT_FILE = $(CHIPDIR)/examples/refrigerator-app/ameba/build/chip/codegen/cluster-file.txt
REFRIGERATOR_PORT_ZAP = $(BASEDIR)/component/common/application/matter/example/refrigerator/refrigerator-app.zap
AIR_PURIFIER_FILE = $(CHIPDIR)/examples/air-purifier-app/ameba/build/chip/codegen/cluster-file.txt
AIR_PURIFIER_ZAP = $(CHIPDIR)/examples/air-purifier-app/air-purifier-common/air-purifier-app.zap
AIRCON_PORT_FILE = $(BASEDIR)/component/common/application/matter/example/aircon/build/chip/codegen/cluster-file.txt
AIRCON_PORT_ZAP = $(BASEDIR)/component/common/application/matter/example/aircon/aircon-app.zap
DISHWASHER_PORT_FILE = $(BASEDIR)/component/common/application/matter/example/dishwasher/build/chip/codegen/cluster-file.txt
DISHWASHER_PORT_ZAP = $(BASEDIR)/component/common/application/matter/example/dishwasher/dishwasher-app.zap
LAUNDRYWASHER_PORT_FILE = $(BASEDIR)/component/common/application/matter/example/laundrywasher/build/chip/codegen/cluster-file.txt
LAUNDRYWASHER_PORT_ZAP = $(BASEDIR)/component/common/application/matter/example/laundrywasher/laundrywasher-app.zap

#*****************************************************************************#
#                         MATTER MAKE DEFINES                                 #
#*****************************************************************************#
all_clusters: $(ALL_CLUSTERS_FILE)
	make -C make/chip/all_clusters_app all
	make -C make/chip_main/all_clusters_app all

aircon_port: $(AIRCON_PORT_FILE)
	make -C make/chip/aircon_app all
	make -C make/chip_main/aircon_port all

air_purifier: $(AIR_PURIFIER_FILE)
	make -C make/chip/air_purifier_app all
	make -C make/chip_main/air_purifier_app all

bridge_port: $(BRIDGE_PORT_FILE)
	make -C make/chip/bridge_app all
	make -C make/chip_main/bridge_port all

bridge_dm: $(BRIDGE_DM_FILE) copy_gen_files_bridge_dm
	make -C make/chip/bridge_app all
	make -C make/chip_main/bridge_dm_app all

dishwasher_port: $(DISHWASHER_PORT_FILE)
	make -C make/chip/dishwasher_app all
	make -C make/chip_main/dishwasher_port all

laundrywasher_port: $(LAUNDRYWASHER_PORT_FILE)
	make -C make/chip/laundrywasher_app all
	make -C make/chip_main/laundrywasher_port all

light: $(LIGHTING_FILE)
	make -C make/chip/lighting_app all
	make -C make/chip_main/lighting_app all

light_port: $(LIGHTING_FILE)
	make -C make/chip/lighting_app all
	make -C make/chip_main/lighting_port all

light_dm:    $(LIGHTING_FILE) copy_gen_files_light_dm 
	make -C make/chip/lighting_app all
	make -C make/chip_main/lighting_dm_app all

light_switch: $(LIGHT_SWITCH_FILE)
	make -C make/chip/light_switch_app all
	make -C make/chip_main/light_switch_app all

refrigerator_port: $(REFRIGERATOR_PORT_FILE)
	make -C make/chip/refrigerator_app all
	make -C make/chip_main/refrigerator_port all

thermostat_port: $(THERMOSTAT_PORT_FILE)
	make -C make/chip/thermostat_app all
	make -C make/chip_main/thermostat_port all

#*****************************************************************************#
#                      RULES TO MAKE MATTER DIRS                              #
#*****************************************************************************#
$(ALL_CLUSTERS_FILE): $(ALL_CLUSTERS_ZAP)
	@cp $(MATTER_DIR)/example/chiptest/all-clusters-app.zap $(ALL_CLUSTERS_ZAP)
	@ rm -f $(RAM_OBJS_LIST)
	mkdir -p $(CHIPDIR)/examples/all-clusters-app/ameba/build/chip/codegen/zap-generated
	python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/matter-idl-server.json --output-dir examples/all-clusters-app/ameba/build/chip/codegen/zap-generated $^
	python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/app-templates.json --output-dir examples/all-clusters-app/ameba/build/chip/codegen/zap-generated $^
	python3 $(CHIPDIR)/scripts/codegen.py --generator cpp-app --output-dir $(CHIPDIR)/examples/all-clusters-app/ameba/build/chip/codegen --expected-outputs $(MATTER_TOOLDIR)/codegen_helpers/expected.outputs $(CHIPDIR)/examples/all-clusters-app/all-clusters-common/all-clusters-app.matter
	python3 $(CHIPDIR)/src/app/zap_cluster_list.py --zap_file $(CHIPDIR)/examples/all-clusters-app/all-clusters-common/all-clusters-app.zap > $(CHIPDIR)/examples/all-clusters-app/ameba/build/chip/codegen/cluster-file.txt
	python3 $(MATTER_TOOLDIR)/codegen_helpers/parse_clusters.py --cluster_file $(CHIPDIR)/examples/all-clusters-app/ameba/build/chip/codegen/cluster-file.txt --chip_path $(CHIPDIR)

$(BRIDGE_PORT_FILE): $(BRIDGE_PORT_ZAP)
	@ rm -f $(RAM_OBJS_LIST)
	mkdir -p $(CHIPDIR)/examples/bridge-app/ameba/build/chip/codegen/zap-generated
	python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/matter-idl-server.json --output-dir examples/bridge-app/ameba/build/chip/codegen/zap-generated $^
	python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/app-templates.json --output-dir examples/bridge-app/ameba/build/chip/codegen/zap-generated $^
	python3 $(CHIPDIR)/scripts/codegen.py --generator cpp-app --output-dir $(CHIPDIR)/examples/bridge-app/ameba/build/chip/codegen --expected-outputs $(MATTER_TOOLDIR)/codegen_helpers/expected.outputs $(CHIPDIR)/examples/bridge-app/bridge-common/bridge-app.matter
	python3 $(CHIPDIR)/src/app/zap_cluster_list.py --zap_file $(CHIPDIR)/examples/bridge-app/bridge-common/bridge-app.zap > $(CHIPDIR)/examples/bridge-app/ameba/build/chip/codegen/cluster-file.txt
	python3 $(MATTER_TOOLDIR)/codegen_helpers/parse_clusters.py --cluster_file $(CHIPDIR)/examples/bridge-app/ameba/build/chip/codegen/cluster-file.txt --chip_path $(CHIPDIR)

$(BRIDGE_DM_FILE): $(BRIDGE_DM_ZAP)
	@ rm -f $(RAM_OBJS_LIST)
	mkdir -p $(CHIPDIR)/examples/bridge-app/ameba/build/chip/codegen/zap-generated
	python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/matter-idl-server.json --output-dir examples/bridge-app/ameba/build/chip/codegen/zap-generated $^
	python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/app-templates.json --output-dir examples/bridge-app/ameba/build/chip/codegen/zap-generated $^
	python3 $(CHIPDIR)/scripts/codegen.py --generator cpp-app --output-dir $(CHIPDIR)/examples/bridge-app/ameba/build/chip/codegen --expected-outputs $(MATTER_TOOLDIR)/codegen_helpers/expected.outputs $(BASEDIR)/component/common/application/matter/example/bridge_dm/bridge-app.matter
	python3 $(CHIPDIR)/src/app/zap_cluster_list.py --zap_file $(BASEDIR)/component/common/application/matter/example/bridge_dm/bridge-app.zap > $(CHIPDIR)/examples/bridge-app/ameba/build/chip/codegen/cluster-file.txt
	python3 $(MATTER_TOOLDIR)/codegen_helpers/parse_clusters.py --cluster_file $(CHIPDIR)/examples/bridge-app/ameba/build/chip/codegen/cluster-file.txt --chip_path $(CHIPDIR)

$(LIGHTING_FILE): $(LIGHTING_ZAP)
	@ rm -f $(RAM_OBJS_LIST)
	mkdir -p $(CHIPDIR)/examples/lighting-app/ameba/build/chip/codegen/zap-generated
	python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/matter-idl-server.json --output-dir examples/lighting-app/ameba/build/chip/codegen/zap-generated $^
	python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/app-templates.json --output-dir examples/lighting-app/ameba/build/chip/codegen/zap-generated $^
	python3 $(CHIPDIR)/scripts/codegen.py --generator cpp-app --output-dir $(CHIPDIR)/examples/lighting-app/ameba/build/chip/codegen --expected-outputs $(MATTER_TOOLDIR)/codegen_helpers/expected.outputs $(CHIPDIR)/examples/lighting-app/lighting-common/lighting-app.matter
	python3 $(CHIPDIR)/src/app/zap_cluster_list.py --zap_file $(CHIPDIR)/examples/lighting-app/lighting-common/lighting-app.zap > $(CHIPDIR)/examples/lighting-app/ameba/build/chip/codegen/cluster-file.txt
	python3 $(MATTER_TOOLDIR)/codegen_helpers/parse_clusters.py --cluster_file $(CHIPDIR)/examples/lighting-app/ameba/build/chip/codegen/cluster-file.txt --chip_path $(CHIPDIR)

$(LIGHT_SWITCH_FILE): $(LIGHT_SWITCH_ZAP)
	@mkdir -p $(CHIPDIR)/examples/light-switch-app/ameba/build/chip/codegen/zap-generated
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/matter-idl-server.json --output-dir examples/light-switch-app/ameba/build/chip/codegen/zap-generated  $^
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/app-templates.json --output-dir examples/light-switch-app/ameba/build/chip/codegen/zap-generated $^
	@python3 $(CHIPDIR)/scripts/codegen.py --generator cpp-app --output-dir $(CHIPDIR)/examples/light-switch-app/ameba/build/chip/codegen --expected-outputs $(MATTER_TOOLDIR)/codegen_helpers/expected.outputs $(CHIPDIR)/examples/light-switch-app/light-switch-common/light-switch-app.matter
	@python3 $(CHIPDIR)/src/app/zap_cluster_list.py --zap_file $^ > $(CHIPDIR)/examples/light-switch-app/ameba/build/chip/codegen/cluster-file.txt
	@python3 $(MATTER_TOOLDIR)/codegen_helpers/parse_clusters.py --cluster_file $@ --chip_path $(CHIPDIR)

$(REFRIGERATOR_PORT_FILE): $(REFRIGERATOR_PORT_ZAP)
	@ rm -f $(RAM_OBJS_LIST)
	mkdir -p $(CHIPDIR)/examples/refrigerator-app/ameba/build/chip/codegen/zap-generated
	python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/matter-idl-server.json --output-dir examples/refrigerator-app/ameba/build/chip/codegen/zap-generated $^
	python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/app-templates.json --output-dir examples/refrigerator-app/ameba/build/chip/codegen/zap-generated $^
	python3 $(CHIPDIR)/scripts/codegen.py --generator cpp-app --output-dir $(CHIPDIR)/examples/refrigerator-app/ameba/build/chip/codegen --expected-outputs $(MATTER_TOOLDIR)/codegen_helpers/expected.outputs $(BASEDIR)/component/common/application/matter/example/refrigerator/refrigerator-app.matter
	python3 $(CHIPDIR)/src/app/zap_cluster_list.py --zap_file $(BASEDIR)/component/common/application/matter/example/refrigerator/refrigerator-app.zap > $(CHIPDIR)/examples/refrigerator-app/ameba/build/chip/codegen/cluster-file.txt
	python3 $(MATTER_TOOLDIR)/codegen_helpers/parse_clusters.py --cluster_file $(CHIPDIR)/examples/refrigerator-app/ameba/build/chip/codegen/cluster-file.txt --chip_path $(CHIPDIR)

$(THERMOSTAT_PORT_FILE): $(THERMOSTAT_PORT_ZAP)
	@ rm -f $(RAM_OBJS_LIST)
	mkdir -p $(CHIPDIR)/examples/thermostat/ameba/build/chip/codegen/zap-generated
	python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/matter-idl-server.json --output-dir examples/thermostat/ameba/build/chip/codegen/zap-generated $^
	python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/app-templates.json --output-dir examples/thermostat/ameba/build/chip/codegen/zap-generated $^
	python3 $(CHIPDIR)/scripts/codegen.py --generator cpp-app --output-dir $(CHIPDIR)/examples/thermostat/ameba/build/chip/codegen --expected-outputs $(MATTER_TOOLDIR)/codegen_helpers/expected.outputs $(CHIPDIR)/examples/thermostat/thermostat-common/thermostat.matter
	python3 $(CHIPDIR)/src/app/zap_cluster_list.py --zap_file $(CHIPDIR)/examples/thermostat/thermostat-common/thermostat.zap > $(CHIPDIR)/examples/thermostat/ameba/build/chip/codegen/cluster-file.txt
	python3 $(MATTER_TOOLDIR)/codegen_helpers/parse_clusters.py --cluster_file $(CHIPDIR)/examples/thermostat/ameba/build/chip/codegen/cluster-file.txt --chip_path $(CHIPDIR)

$(AIR_PURIFIER_FILE): $(AIR_PURIFIER_ZAP)
	@ rm -f $(RAM_OBJS_LIST)
	mkdir -p $(CHIPDIR)/examples/air-purifier-app/ameba/build/chip/codegen/zap-generated
	python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/matter-idl-server.json --output-dir examples/air-purifier-app/ameba/build/chip/codegen/zap-generated $^
	python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/app-templates.json --output-dir examples/air-purifier-app/ameba/build/chip/codegen/zap-generated $^
	python3 $(CHIPDIR)/scripts/codegen.py --generator cpp-app --output-dir $(CHIPDIR)/examples/air-purifier-app/ameba/build/chip/codegen --expected-outputs $(MATTER_TOOLDIR)/codegen_helpers/expected.outputs $(CHIPDIR)/examples/air-purifier-app/air-purifier-common/air-purifier-app.matter
	python3 $(CHIPDIR)/src/app/zap_cluster_list.py --zap_file $(CHIPDIR)/examples/air-purifier-app/air-purifier-common/air-purifier-app.zap > $(CHIPDIR)/examples/air-purifier-app/ameba/build/chip/codegen/cluster-file.txt
	python3 $(MATTER_TOOLDIR)/codegen_helpers/parse_clusters.py --cluster_file $(CHIPDIR)/examples/air-purifier-app/ameba/build/chip/codegen/cluster-file.txt --chip_path $(CHIPDIR)

$(AIRCON_PORT_FILE): $(AIRCON_PORT_ZAP)
	@ rm -f $(RAM_OBJS_LIST)
	mkdir -p $(BASEDIR)/component/common/application/matter/example/aircon/build/chip/codegen/zap-generated
	python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/matter-idl-server.json --output-dir $(BASEDIR)/component/common/application/matter/example/aircon/build/chip/codegen/zap-generated $^
	python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/app-templates.json --output-dir $(BASEDIR)/component/common/application/matter/example/aircon/build/chip/codegen/zap-generated $^
	python3 $(CHIPDIR)/scripts/codegen.py --generator cpp-app --output-dir $(BASEDIR)/component/common/application/matter/example/aircon/build/chip/codegen --expected-outputs $(MATTER_TOOLDIR)/codegen_helpers/expected.outputs $(BASEDIR)/component/common/application/matter/example/aircon/aircon-app.matter
	python3 $(CHIPDIR)/src/app/zap_cluster_list.py --zap_file $(BASEDIR)/component/common/application/matter/example/aircon/aircon-app.zap > $(BASEDIR)/component/common/application/matter/example/aircon/build/chip/codegen/cluster-file.txt
	python3 $(MATTER_TOOLDIR)/codegen_helpers/parse_clusters.py --cluster_file $(BASEDIR)/component/common/application/matter/example/aircon/build/chip/codegen/cluster-file.txt --chip_path $(CHIPDIR)

$(DISHWASHER_PORT_FILE): $(DISHWASHER_PORT_ZAP)
	@ rm -f $(RAM_OBJS_LIST)
	mkdir -p $(BASEDIR)/component/common/application/matter/example/dishwasher/build/chip/codegen/zap-generated
	python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/matter-idl-server.json --output-dir $(BASEDIR)/component/common/application/matter/example/dishwasher/build/chip/codegen/zap-generated $^
	python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/app-templates.json --output-dir $(BASEDIR)/component/common/application/matter/example/dishwasher/build/chip/codegen/zap-generated $^
	python3 $(CHIPDIR)/scripts/codegen.py --generator cpp-app --output-dir $(BASEDIR)/component/common/application/matter/example/dishwasher/build/chip/codegen --expected-outputs $(MATTER_TOOLDIR)/codegen_helpers/expected.outputs $(BASEDIR)/component/common/application/matter/example/dishwasher/dishwasher-app.matter
	python3 $(CHIPDIR)/src/app/zap_cluster_list.py --zap_file $(BASEDIR)/component/common/application/matter/example/dishwasher/dishwasher-app.zap > $(BASEDIR)/component/common/application/matter/example/dishwasher/build/chip/codegen/cluster-file.txt
	python3 $(MATTER_TOOLDIR)/codegen_helpers/parse_clusters.py --cluster_file $(BASEDIR)/component/common/application/matter/example/dishwasher/build/chip/codegen/cluster-file.txt --chip_path $(CHIPDIR)

$(LAUNDRYWASHER_PORT_FILE): $(LAUNDRYWASHER_PORT_ZAP)
	@ rm -f $(RAM_OBJS_LIST)
	mkdir -p $(BASEDIR)/component/common/application/matter/example/laundrywasher/build/chip/codegen/zap-generated
	python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/matter-idl-server.json --output-dir $(BASEDIR)/component/common/application/matter/example/laundrywasher/build/chip/codegen/zap-generated $^
	python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/app-templates.json --output-dir $(BASEDIR)/component/common/application/matter/example/laundrywasher/build/chip/codegen/zap-generated $^
	python3 $(CHIPDIR)/scripts/codegen.py --generator cpp-app --output-dir $(BASEDIR)/component/common/application/matter/example/laundrywasher/build/chip/codegen --expected-outputs $(MATTER_TOOLDIR)/codegen_helpers/expected.outputs $(BASEDIR)/component/common/application/matter/example/laundrywasher/laundrywasher-app.matter
	python3 $(CHIPDIR)/src/app/zap_cluster_list.py --zap_file $(BASEDIR)/component/common/application/matter/example/laundrywasher/laundrywasher-app.zap > $(BASEDIR)/component/common/application/matter/example/laundrywasher/build/chip/codegen/cluster-file.txt
	python3 $(MATTER_TOOLDIR)/codegen_helpers/parse_clusters.py --cluster_file $(BASEDIR)/component/common/application/matter/example/laundrywasher/build/chip/codegen/cluster-file.txt --chip_path $(CHIPDIR)

copy_gen_files_light_dm:
	cp $(BASEDIR)/component/common/application/matter/example/light_dm/endpoint_config.h $(CHIPDIR)/examples/lighting-app/ameba/build/chip/codegen/zap-generated
	cp $(BASEDIR)/component/common/application/matter/example/light_dm/gen_config.h $(CHIPDIR)/examples/lighting-app/ameba/build/chip/codegen/zap-generated

copy_gen_files_bridge_dm:
	cp $(BASEDIR)/component/common/application/matter/example/bridge_dm/endpoint_config.h $(CHIPDIR)/examples/bridge-app/ameba/build/chip/codegen/zap-generated
	cp $(BASEDIR)/component/common/application/matter/example/bridge_dm/gen_config.h $(CHIPDIR)/examples/bridge-app/ameba/build/chip/codegen/zap-generated
