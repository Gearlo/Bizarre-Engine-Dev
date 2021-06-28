INCS_PC = $(DIR_PC)includes/

OBJS_PC = $(DIR_PC)main.o \
		 $(DIR_PC)context/BALContext.o \
		 $(DIR_PC)context/BBulletContext.o \
		 $(DIR_PC)context/BGLContext.o \
		 $(DIR_PC)context/BInput.o \
		 $(DIR_PC)context/BTThreadingContext.o \
		 $(DIR_PC)context/BWinContext.o \
		 $(DIR_PC)engine/BGame.o \
         $(DIR_PC)engine/Bizarre.o \
		 $(DIR_PC)loaders/BMeshLoad.o \
		 $(DIR_PC)loaders/BImageLoader.o \
		 $(DIR_PC)loaders/BModMusicLoader.o \
		 $(DIR_PC)loaders/BWavSoundLoader.o \
		 $(DIR_PC)loaders/BBinFontLoader.o \
		 $(DIR_PC)loaders/BFreetypeLoader.o \
		 $(DIR_PC)managers/MPackageManagerNPK.o \
		 $(DIR_PC)renderers/BFixedRenderer.o \
		 $(DIR_PC)renderers/BStandardRenderer.o \
		 $(DIR_PC)scripting/BScriptContext.o \
		 