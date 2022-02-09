
# MIT License

# Copyright (c) 2020-2021, Simon Byrne, Kevin Squire, Nikhil Mitra

# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

.PHONY: build clean dist instantiate install uninstall

# JULIA ?= julia-debug # julia # 
# NAME := scjulia

ROOT_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
BUILDER := $(ROOT_DIR)/builder

JULIA_DIR := $(shell $(JULIA) --startup-file=no -e 'print(dirname(Sys.BINDIR))')
DLEXT := $(shell $(JULIA) --startup-file=no -e 'using Libdl; print(Libdl.dlext)')
OS := $(shell uname)
DEPS := $(shell find . build src -maxdepth 1 -and \( -name \*.toml -or -name \*.jl -or -name Makefile \) -and -not -type l)

BIN_DIR := build/$(NAME)/bin
INCLUDE_DIR = build/$(NAME)/include
LIB_DIR := build/$(NAME)/lib
PREFIX ?= $${HOME}/.local

LIB_NAME := lib$(NAME).$(DLEXT)
INCLUDES = $(INCLUDE_DIR)/julia_init.h $(INCLUDE_DIR)/$(NAME).h
LIB_PATH := $(LIB_DIR)/$(LIB_NAME)

.DEFAULT_GOAL := build

$(LIB_PATH) $(INCLUDES): $(BUILDER)/build.jl $(DEPS)
	$(JULIA) --startup-file=no --project=. -e 'using Pkg; Pkg.instantiate()'
	$(JULIA) --startup-file=no --project=$(BUILDER) -e 'using Pkg; Pkg.instantiate()'
# $(JULIA) --startup-file=no --project=$(BUILDER) $< $(NAME)
# Replace the previous line with the line below to enable verbose debugging during package build
	JULIA_DEBUG=PackageCompiler $(JULIA) --startup-file=no --project=$(BUILDER) $< $(NAME)

build: $(LIB_PATH) $(INCLUDES) README.md

instantiate:
	$(JULIA) --startup-file=no --project=. -e "import Pkg; Pkg.instantiate()"
	$(JULIA) --startup-file=no --project=build -e "import Pkg; Pkg.instantiate()"

clean:
	$(RM) -Rf build