#! /usr/bin/make

# NOTE: this file addapts to the contents of the directory it is in 
#       and provides a path to generate and compile a murphi model for each of the three
#       model-checkers (romp, cmurphi, rumur).
#       PLEASE update the paths to each model checker for your computer

# ====================
#  config model runs
# ====================
# max memory used by hash tables in MB (rumur & cmurphi)
# MEM_LIMIT := 2048
# MEM_LIMIT := 1024


# =====================
#  config model builds
# =====================
# this makefile presumes that you have the romp, rumur, & CMurphi repos all in the same directory
#  and that you have built them all using the normal build patterns for their respective repos.
CC := gcc
CXX := g++
ROMP := ../../build/romp/romp
CMURPHI := ../../../cmurphi/src/mu
RUMUR := ../../../rumur/build/rumur/rumur

RM := rm -rf 
RMDIR := rm -rf 
MKDIR := mkdir -p
CP := cp -rf

CFLAGS := -std=c11 -O3 -pthread -march=native
CXXFLAGS := -std=c++17 -O3 -pthread
ROMP_FLAGS := -s --do-measure --simple-trace-rep
CMURPHI_FLAGS := -c
CMURPHI_INCLUDE_DIR := ../../../cmurphi/include
RUMUR_FLAGS := --smt-path z3 --smt-arg=-smt2 --smt-arg=-in --smt-arg=-t:5000


# =====================
#  parameter producers
# =====================
ALL_MODELS := $(wildcard *.m)
ROMP_MODELS := $(wildcard *.m)
CMURPHI_MODELS := $(wildcard *.m)
RUMUR_MODELS := $(filter-out MESI%,$(ALL_MODELS))
# RUMUR_MODELS := $(wildcard ru*.m)

ROMP_MODEL_SOURCES := $(foreach model,$(ROMP_MODELS),$(model:%.m=%.romp.cpp))
CMURPHI_MODEL_SOURCES := $(foreach model,$(CMURPHI_MODELS),$(model:%.m=%.cpp))
RUMUR_MODEL_SOURCES := $(foreach model,$(RUMUR_MODELS),$(model:%.m=%.ru.c))

ROMP_MODEL_EXE := $(foreach model,$(ROMP_MODELS),$(model:%.m=%.sym.romp)) $(foreach model,$(ROMP_MODELS),$(model:%.m=%.nsym.romp)) $(foreach model,$(ROMP_MODELS),$(model:%.m=%.romp))
CMURPHI_MODEL_EXE := $(foreach model,$(CMURPHI_MODELS),$(model:%.m=%.cm))
RUMUR_MODEL_EXE := $(foreach model,$(RUMUR_MODELS),$(model:%.m=%.ru))
ALL_MODEL_EXE := $(ROMP_MODEL_EXE) $(CMURPHI_MODEL_EXE) $(RUMUR_MODEL_EXE)
# $(info $(CMURPHI_MODEL_EXE))

# ======================
#  directive generation
# ======================
#generate romp directives
define __generate_romp_model_directive
$(1).romp.cpp: $(1).m
	@printf "Generating $$@ with romp ...\n"
	@printf "  $$(ROMP) $$(ROMP_FLAGS) -o $$@ $(1).m\n"
	@$$(ROMP) $$(ROMP_FLAGS) -o $$@ $(1).m
	@printf "Finished Generating: $$@\n"
$(1).sym.romp: $(1).romp.cpp
	@printf "Building $$@ ...\n"
	@printf "  $$(CXX) $$(CXXFLAGS) -D__romp__ENABLE_symmetry -o $$@ $(1).romp.cpp\n"
	@$$(CXX) $$(CXXFLAGS) -D__romp__ENABLE_symmetry -o $$@ $(1).romp.cpp
	@printf "Finished Building: $$@\n"
$(1).nsym.romp: $(1).romp.cpp
	@printf "Building $$@ ...\n"
	@printf "  $$(CXX) $$(CXXFLAGS) -o $$@ $(1).romp.cpp\n"
	@$$(CXX) $$(CXXFLAGS) -o $$@ $(1).romp.cpp
	@printf "Finished Building: $$@\n"
$(1).romp: $(1).sym.romp
	@printf "``Making'' $$@ with `cp` ...\n"
	@printf "  $$(CP) $(1).sym.romp $(1).romp\n"
	@$$(CP) $(1).sym.romp $(1).romp
	@printf "Finished ``Making'': $$@\n"
endef
$(foreach model,$(ROMP_MODELS),$(eval $(call __generate_romp_model_directive,$(model:%.m=%))))
#generate cmurphi directives
define __generate_cmurphi_model_directive
$(1).cm.cpp: $(1).m
	@printf "Generating $$@ with cmurphi ...\n"
	@printf " $$(CMURPHI) $$(CMURPHI_FLAGS) $(1).m\n"
	@$$(CMURPHI) $$(CMURPHI_FLAGS) $(1).m
	@printf "Finished Generating: $$@\n"
$(1).cm: $(1).cpp
	@printf "Building $$@ ...\n"
	@printf "  $$(CXX) $$(CXXFLAGS) -I$$(CMURPHI_INCLUDE_DIR) -o $$@ $(1).cpp\n"
	@$$(CXX) $$(CXXFLAGS) -I$$(CMURPHI_INCLUDE_DIR) -o $$@ $(1).cpp
	@printf "Finished Building: $$@\n"
endef
$(foreach model,$(CMURPHI_MODELS),$(eval $(call __generate_cmurphi_model_directive,$(model:%.m=%))))
#generate rumur directives
define __generate_rumur_model_directive
$(1).ru.c: $(1).m
	@printf "Generating $$@ with rumur ...\n"
	@printf "  $$(RUMUR) $$(RUMUR_FLAGS) -o $$@ $(1).m\n"
	@$$(RUMUR) $$(RUMUR_FLAGS) -o $$@ $(1).m
	@printf "Finished Generating: $$@\n"
$(1).ru: $(1).ru.c
	@printf "Building $$@ ...\n"
	@printf "  $$(CC) $$(CFLAGS) -o $$@ $(1).ru.c\n"
	@$$(CC) $(CFLAGS) -o $$@ $(1).ru.c
	@printf "Finished Building: $$@\n"
endef
$(foreach model,$(CMURPHI_MODELS),$(eval $(call __generate_rumur_model_directive,$(model:%.m=%))))
#generate per model directives
# define __genrate_per_model_directive
# $(1): $(2)
# 	@printf "\nFinished Building all `$@` model checkers!\n\n"
# endef
# $(foreach model,$(ALL_MODELS),$(eval $(call __generate_per_model_directive,$(model:%.m=%),$(if $(filter $(model:%.m=%).m,$(ROMP_MODELS)),$(model:%.m=%).sym.romp $(model:%.m=%).nsym.romp )$(if $(filter $(model:%.m=%).m,$(CMURPHI_MODELS)),$(model:%.m=%).cm )$(if $(filter $(model:%.m=%).m,$(RUMUR_MODELS)),$(model:%.m=%).ru))))
# $(info $(foreach model,$(ALL_MODELS),$(model:%.m=%): $(ifeq $(filter $(1),$(ROMP_MODELS)),$(1),$(1).sym.romp $(1).nsym.romp) $(ifeq $(filter $(model:%.m=%),$(CMURPHI_MODELS)),$(model:%.m=%),$(model:%.m=%).cm) $(ifeq $(filter $(model:%.m=%),$(RUMUR_MODELS)),$(model:%.m=%),$(model:%.m=%).ru)))
# $(foreach model,$(ALL_MODELS),$(info $(model:%.m=%): $(if $(filter $(model:%.m=%).m,$(ROMP_MODELS)),$(model:%.m=%).sym.romp $(model:%.m=%).nsym.romp )$(if $(filter $(model:%.m=%).m,$(CMURPHI_MODELS)),$(model:%.m=%).cm )$(if $(filter $(model:%.m=%).m,$(RUMUR_MODELS)),$(model:%.m=%).ru)))



# ================= 
#  make directives
# ================= 
all: $(ALL_MODEL_EXE)
	@printf "Finished Building all model checkers in directory\n"

romp_models: $(ROMP_MODEL_EXE)
cmurphi_models: $(CMURPHI_MODEL_EXE)
rumur_models: $(RUMUR_MODEL_EXE)

.PHONY: all clean clean-inter romp_models cmurphi_models rumur_models $(patsubst %.m,%,$(ALL_MODELS))
.DEFAULT_GOAL := all

# =================
#  clean directive
# =================

# clean:
#	$(RM) $(ROMP_MODEL_SOURCES) $(CMURPHI_MODEL_SOURCES) $(RUMUR_MODEL_SOURCES)
#	$(RM) $(ROMP_MODEL_EXE) $(CMURPHI_MODEL_EXE) $(RUMUR_MODEL_EXE)
clean-inter:
	@$(RM) ./*.cpp
	@$(RM) ./*.c
	@printf "Cleaning of intermedairies Finished !!\n"

clean:
	@$(RM) ./*.cpp
	@$(RM) ./*.c
	@$(RM) ./*.romp
	@$(RM) ./*.cm
	@$(RM) ./*.ru
	@$(RM) ./*.test
	@printf "Cleaning Finished !!\n"