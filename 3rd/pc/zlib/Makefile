
OBJS_BULLET = ./adler32.o \
			./compress.o \
			./crc32.o \
			./deflate.o \
			./gzclose.o \
			./gzlib.o \
			./gzread.o \
			./gzwrite.o \
			./infback.o \
			./inffast.o \
			./inflate.o \
			./inftrees.o \
			./trees.o \
			./uncompr.o \
			./zutil.o 

 


CC = gcc
CXX = g++
CFLAGS = -O3 -fPIC
INCDIRS = .
 
src =$(OBJS_BULLET)

obj = $(src:.c=.o)
INC_PARAMS=$(foreach d, $(INCDIRS), -I$d)
CFLAGS += $(INC_PARAMS)

INCLIBS_PARAMS=$(foreach d, $(LIBDIRS), -L$d)
LDFLAGS += $(INCLIBS_PARAMS)

../build/libzlib.a: $(obj)
	ar rcs $@ $^ 

.PHONY: clean


clean: 
	rm -f $(src) ../build/libzlib.a