DIR_COMMON = ../_common/
DIR_PC     = ../pc/
DIR_LINUX  = ./
DIR_3RD    = ../../3rd/



include $(DIR_3RD)3rd-linux.mk
include $(DIR_COMMON)common.mk
include $(DIR_PC)pc.mk
include $(DIR_LINUX)linux.mk


all: buildPaths Bizarre3rd Bizarre

buildPaths:
	mkdir -p $(BUILDIDIRS_3RD)

Bizarre3rd:
	cd $(DIR_3RD)pc/bullet/ && $(MAKE)
	cd $(DIR_3RD)pc/zlib/ && $(MAKE)
	cd $(DIR_3RD)pc/libpng/ && $(MAKE)
	cd $(DIR_3RD)pc/npk/ && $(MAKE)
	cd $(DIR_3RD)pc/tinyxml/ && $(MAKE)


CC = gcc
CXX = g++
CXXFLAGS = -O3
LDFLAGS = $(LIBS_3RD) $(LIBS_LINUX)
LIBDIRS = $(LIBDIRS_3RD)
INCDIRS = $(INCS_COMMON) $(INCS_3RD) $(INCS_LINUX) $(INCS_PC)


src =$(OBJS_PC) \
	 $(OBJS_COMMON) \
	 $(OBJS_LINUX) \
	 $(OBJS_3RD)


obj = $(src:.cpp=.o)
INC_PARAMS=$(foreach d, $(INCDIRS), -I$d)
CXXFLAGS += $(INC_PARAMS)

INCLIBS_PARAMS=$(foreach d, $(LIBDIRS), -L$d)
LDFLAGS += $(INCLIBS_PARAMS)


Bizarre: $(obj)
	cd . && $(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) 



.PHONY: clean cleanAll

cleanAll:
	cd $(DIR_3RD)pc/bullet/ && $(MAKE) clean
	cd $(DIR_3RD)pc/zlib/ && $(MAKE) clean
	cd $(DIR_3RD)pc/libpng/ && $(MAKE) clean
	cd $(DIR_3RD)pc/npk/ && $(MAKE) clean
	cd $(DIR_3RD)pc/tinyxml/ && $(MAKE) clean
	cd $(DIR_3RD)pc/glee/ && $(MAKE) clean
	rm -f $(src) Bizarre
	rmdir $(BUILDIDIRS_3RD)

clean:
	rm -f $(src) Bizarre
	

