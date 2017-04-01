# Copyright (c) 2017 The Authors taihejin.
# All rights reserved. Use of this source code should be governed
# by the author. See the AUTHORS file for names of authors.
# Author: zhanglong Email: taihejin@whu.edu.cn

# -------------------------------------------------
# Uncomment exactly one of the lines labelled (A), (B), and (C) below
# to switch between compilation modes.
#
# (A) Production use (optimized mode)
OPT ?= -O2 -DNDEBUG
# (B) Debug mode, w/ full line-level debugging symbols
# OPT ?= -g2
# (C) Profiling mode: opt, but w/debugging symbols
# OPT ?= -O2 -g2 -DNDEBUG
# -------------------------------------------------

# temporarily disable globbing so that our patterns aren't expanded
$(shell set -f)
SOURCE_DIR     := .
SOURCE_PATTERN := *.cc
PRUNE_TEST     := -name *test.cc -prune
PRUNE_BENCH    := -name *bench.cc -prune
SOURCES        := $(shell find $(SOURCE_DIR) $(PRUNE_TEST) -o $(PRUNE_BENCH) \
		  -o -name "$(SOURCE_PATTERN)" -print \
		  | sort | sed "s,^$(SOURCE_DIR)/,," | tr "\n" " ")
# re-enable globbing
$(shell set +f)

THIRD_PARTY  := ../third-party
GOOGLE_TEST  := $(THIRD_PARTY)/gtest
INCLUDE_PATH := -I$(GOOGLE_TEST)/include

LINK_LIB     := -lpthread 
LINK_LIB     += $(GOOGLE_TEST)/lib/libgtest.a

CXXFLAGS     += $(INCLUDE_PATH) $(OPT)
CFLAGS       += $(INCLUDE_PATH) $(OPT)

PROGRAMS     := $(SOURCES:.cc=)

%: %.cc
	$(CXX) $(CXXFLAGS) $< $(LINK_LIB) -o $@

all: $(PROGRAMS)

clean:
	rm -rf $(PROGRAMS) 

verify:
	@echo --sources: $(SOURCES)--
	@echo --programs: $(PROGRAMS)--
	@echo --link lib: $(LINK_LIB)--
	@echo --cflags: $(CFLAGS)--
