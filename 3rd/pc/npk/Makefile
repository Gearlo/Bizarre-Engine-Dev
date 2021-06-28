
OBJS_BULLET = ./src/npk.o \
			  ./src/npk_common.o \
			  ./src/npk_dev.o \
			  ./external/tea/tea.o \
			  ./external/tea/tea_dev.o \
			  ./external/xxtea/xxtea.o \
			  ./external/xxtea/xxtea_dev.o \


 


CC = gcc
CXX = g++
CFLAGS = -O3 -fPIC
INCDIRS = ./include ../zlib/ ./external/tea/ ./external/xxtea/
 
src =$(OBJS_BULLET)

obj = $(src:.c=.o)
INC_PARAMS=$(foreach d, $(INCDIRS), -I$d)
CFLAGS += $(INC_PARAMS)

INCLIBS_PARAMS=$(foreach d, $(LIBDIRS), -L$d)

LDFLAGS = -lzlib
LDFLAGS += $(INCLIBS_PARAMS) -L../build/

../build/libnpk.a: $(obj)
	ar rcs $@ $^ 

.PHONY: clean


clean: 
	rm -f $(src) ../build/libnpk.a