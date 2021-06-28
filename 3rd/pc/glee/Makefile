
OBJS_BULLET = ./GLee.o 

CC = gcc
CXX = g++
CXXFLAGS = -O3 -fPIC
INCDIRS = .

src =$(OBJS_BULLET)

obj = $(src:.cpp=.o)
INC_PARAMS=$(foreach d, $(INCDIRS), -I$d)
CXXFLAGS += $(INC_PARAMS)

INCLIBS_PARAMS=$(foreach d, $(LIBDIRS), -L$d)
LDFLAGS += $(INCLIBS_PARAMS)

../build/libglee.a: $(obj)
	ar rcs $@ $^ 

.PHONY: clean


clean: 
	rm -f $(src) ../build/libglee.a