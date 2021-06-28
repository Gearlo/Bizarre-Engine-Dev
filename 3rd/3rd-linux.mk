uname_m := $(shell uname -m)

INCS_3RD = $(DIR_3RD)pc/bullet/ \
		   $(DIR_3RD)pc/glee/ \
		   $(DIR_3RD)pc/freetype \
		   $(DIR_3RD)pc/zlib/ \
		   $(DIR_3RD)pc/libpng/ \
		   $(DIR_3RD)pc/npk/include/ \
		   $(DIR_3RD)pc/openal/ \
		   $(DIR_3RD)pc/tinyutf8/ \
		   $(DIR_3RD)pc/tinyxml/ \
		   $(DIR_3RD)linux/includes/ \
		   $(DIR_3RD)linux/includes/python/ \
		   

BUILDIDIRS_3RD = $(DIR_3RD)pc/build/
ifeq ($(uname_m),x86_64)
PREBUILDDIRS_3RD = $(DIR_3RD)linux/bin_x64/   
endif

ifeq ($(uname_m),i686)
PREBUILDDIRS_3RD = $(DIR_3RD)linux/bin_x86/   
endif



LIBDIRS_3RD = $(BUILDIDIRS_3RD)  $(PREBUILDDIRS_3RD)   

LIBS_3RD = -lpython2.7 -ldl -lutil -lfreetype -lpng -lzlib -lnpk -ltinyxml -lbullet -lopenal -lopenmpt -lzlib

OBJS_3RD = $(DIR_3RD)pc/glee/GLee.o

