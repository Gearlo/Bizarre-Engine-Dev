DIR_COMMON = ../_common/
DIR_PC     = ../pc/
DIR_WINDOWS  = ./
DIR_3RD = ../../3rd/

CC = gcc
CXX = g++

include $(DIR_COMMON)common.mk
include $(DIR_PC)pc.mk
include $(DIR_WINDOWS)windows.mk
include $(DIR_3RD)3rd-windows.mk


all: buildPaths Bizarre3rd Bizarre.exe

buildPaths:
	mkdir -p $(BUILDIDIRS_3RD)

Bizarre3rd:
	cd $(DIR_3RD)pc/bullet/ && $(MAKE)
	cd $(DIR_3RD)pc/zlib/ && $(MAKE)
	cd $(DIR_3RD)pc/libpng/ && $(MAKE)
	cd $(DIR_3RD)pc/npk/ && $(MAKE)
	cd $(DIR_3RD)pc/tinyxml/ && $(MAKE)
	cd $(DIR_3RD)pc/glee/ && $(MAKE)


CXXFLAGS = -O2 
LDFLAGS = $(LIBS_3RD) $(LIBS_WINDOWS) 
LIBDIRS = $(LIBDIRS_3RD) ./ 
INCDIRS = $(INCS_COMMON) $(INCS_3RD) $(INCS_WINDOWS) $(INCS_PC) 


src = $(OBJS_COMMON) \
	  $(OBJS_PC) \
	  $(OBJS_WINDOWS) 

obj = $(src:.cpp=.o)
INC_PARAMS=$(foreach d, $(INCDIRS), -I$d)
CXXFLAGS += $(INC_PARAMS)

INCLIBS_PARAMS=$(foreach d, $(LIBDIRS), -L$d)
LDFLAGS += $(INCLIBS_PARAMS)



Bizarre.exe: $(obj) 
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)



.PHONY: clean cleanAll

cleanAll:
	cd $(DIR_3RD)pc/bullet/ && $(MAKE) clean
	cd $(DIR_3RD)pc/zlib/ && $(MAKE) clean
	cd $(DIR_3RD)pc/libpng/ && $(MAKE) clean
	cd $(DIR_3RD)pc/npk/ && $(MAKE)
	cd $(DIR_3RD)pc/tinyxml/ && $(MAKE) clean
	cd $(DIR_3RD)pc/glee/ && $(MAKE) clean
	rm -f $(src) Bizarre.exe
	rmdir $(BUILDIDIRS_3RD)
	

clean:
	rm -f $(src) Bizarre.exe