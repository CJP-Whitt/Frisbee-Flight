#	Name:		Makefile
#	Created:	11/29/2022
# 	Author:	    CWhitt
#
#	This is Carson's guarenteen perfection Makefile. It will provide all the necessary targets for
#	setting up and working on this codebase. Use it wisely.

export

# Variable definitions

# Miscillaneous
SCRIPT_VERSION = v1.0
SCRIPT_AUTHOR = CWhitt

# Locations of source files
SOURCE_FILES := ./src ./configs ./lib ./tests

# Help macros
HELP_FUN = \
    %help; while(<>){push@{$$help{$$2//'options'}},[$$1,$$3] \
    if/^([\w-_]+)\s*:.*\#\#(?:@(\w+))?\s(.*)$$/}; \
    print"$$_:\n", map"  $$_->[0]".(" "x(20-length($$_->[0])))."$$_->[1]\n",\
    @{$$help{$$_}},"\n" for keys %help; \

# Cpp lint flags
LINT_FLAGS := --linelength=120 --filter=-legal/copyright,-build/include_subdir \
	--extensions=c,c++,cc,cpp,cu,cuh,cxx,h,h++,hh,hpp,hxx,ino --recursive

.PHONY: hello help lint	
.DEFAULT_GOAL := help

# Rules
lint: ##@Formatting Check source files for linting conflicts. (Provide filenames to lint set of filenames)
ifeq ($(MAKECMDGOALS), lint)
	@cpplint $(LINT_FLAGS) $(SOURCE_FILES)
endif
	@cpplint $(LINT_FLAGS) $(filter-out $@, $(MAKECMDGOALS))

hello: ##@Miscellaneous Example make target
	@echo "Hello, World!"

help: ##@Miscellaneous Show help message
	@echo "Usage: make [target] ...\n"
	@perl -e '$(HELP_FUN)' $(MAKEFILE_LIST)
	@echo "Written by $(SCRIPT_AUTHOR), version $(SCRIPT_VERSION)"

clang: ##@Testing Static analysis with scan-build
	@clang --analyze --analyzer-output text $(IFLAGS) $(APP_SRC)
