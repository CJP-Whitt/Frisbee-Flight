#	Name:		Makefile
#	Created:	11/29/2022
# 	Author:	    CWhitt
#
#	This is Carson's guarenteen perfection Makefile. It will provide all the necessary targets for
#	setting up and working on this codebase. Use it wisely.

SCRIPT_VERSION = v1.0
SCRIPT_AUTHOR = CWhitt

HELP_FUN = \
    %help; while(<>){push@{$$help{$$2//'options'}},[$$1,$$3] \
    if/^([\w-_]+)\s*:.*\#\#(?:@(\w+))?\s(.*)$$/}; \
    print"$$_:\n", map"  $$_->[0]".(" "x(20-length($$_->[0])))."$$_->[1]\n",\
    @{$$help{$$_}},"\n" for keys %help; \
	
.DEFAULT_GOAL := help
.PHONY: help

lint: ##@Tools Check source files for linting conflicts
	cpplint --linelength=100 --extensions=c,c++,cc,cpp,cu,cuh,cxx,h,h++,hh,hpp,hxx,ino --recursive \
		./app ./configs ./libraries/PWM_BDLC_Control ./tests ./utilities

hello: ##@Miscellaneous Example make target
	@echo "Hello, World!"

help: ##@Miscellaneous Show help message
	@echo "Usage: make [target] ...\n"
	@perl -e '$(HELP_FUN)' $(MAKEFILE_LIST)
	@echo "Written by $(SCRIPT_AUTHOR), version $(SCRIPT_VERSION)"