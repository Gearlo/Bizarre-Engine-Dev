
OBJS_BULLET = ./png.o \
			./pngerror.o \
			./pngget.o \
			./pngmem.o \
			./pngpread.o \
			./pngread.o \
			./pngrio.o \
			./pngrtran.o \
			./pngrutil.o \
			./pngset.o \
			./pngtrans.o \
			./pngwio.o \
			./pngwrite.o \
			./pngwtran.o \
			./pngwutil.o \

 


CC = gcc
CXX = g++
CFLAGS = -O3 -fPIC
INCDIRS = . ../zlib/
 
src =$(OBJS_BULLET)

obj = $(src:.c=.o)
INC_PARAMS=$(foreach d, $(INCDIRS), -I$d)
CFLAGS += $(INC_PARAMS)

INCLIBS_PARAMS=$(foreach d, $(LIBDIRS), -L$d)

LDFLAGS = -lzlib
LDFLAGS += $(INCLIBS_PARAMS) -L../build/

../build/libpng.a: $(obj)
	ar rcs $@ $^ 

.PHONY: clean


clean: 
	rm -f $(src) ../build/libpng.a