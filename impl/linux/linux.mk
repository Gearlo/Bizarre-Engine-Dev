INCS_LINUX = $(DIR_LINUX)includes/ #/usr/include/python2.7

LIBS_LINUX = -lpthread -lGL -lXxf86vm -lX11

OBJS_LINUX = $(DIR_LINUX)context/x11_keysym2unicode.o \
			 $(DIR_LINUX)context/BX11Window.o \
			 $(DIR_LINUX)context/BJoystickLinux.o