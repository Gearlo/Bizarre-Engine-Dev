INCS_COMMON = \
	../../includes \
	../../includes/core \
	../../includes/engine \
	../../includes/gui

OBJS_COMMON = \
	$(DIR_COMMON)core/BColor.o \
	$(DIR_COMMON)core/BDataLoader.o \
	$(DIR_COMMON)core/BDataManager.o \
	$(DIR_COMMON)core/BFileTools.o \
	$(DIR_COMMON)core/BImage.o \
	$(DIR_COMMON)core/BMaths.o \
	$(DIR_COMMON)core/BMatrix4x4.o \
	$(DIR_COMMON)core/BQuaternion.o \
	$(DIR_COMMON)core/BRenderInfo.o \
	$(DIR_COMMON)core/BSound.o \
	$(DIR_COMMON)core/BStdFile.o \
	$(DIR_COMMON)core/BString.o \
	$(DIR_COMMON)core/BStringTools.o \
	$(DIR_COMMON)core/BTimer.o \
	$(DIR_COMMON)core/BVector2f.o \
	$(DIR_COMMON)core/BVector3f.o \
	$(DIR_COMMON)core/BVector4f.o \
	$(DIR_COMMON)engine/BArmature.o \
	$(DIR_COMMON)engine/BArmatureAnim.o \
	$(DIR_COMMON)engine/BArmatureAnimRef.o \
	$(DIR_COMMON)engine/BBehavior.o \
	$(DIR_COMMON)engine/BBehaviorCreator.o \
	$(DIR_COMMON)engine/BBehaviorManager.o \
	$(DIR_COMMON)engine/BBox3d.o \
	$(DIR_COMMON)engine/Bizarre.o \
	$(DIR_COMMON)engine/BFXManager.o \
	$(DIR_COMMON)engine/BFont.o \
	$(DIR_COMMON)engine/BFontRef.o \
	$(DIR_COMMON)engine/BFrustum.o \
	$(DIR_COMMON)engine/BGame.o \
	$(DIR_COMMON)engine/BKey.o \
	$(DIR_COMMON)engine/BAssetsManager.o \
	$(DIR_COMMON)engine/ULog.o \
	$(DIR_COMMON)engine/BMaterial.o \
	$(DIR_COMMON)engine/BMaterialAnim.o \
	$(DIR_COMMON)engine/BMaterialsAnim.o \
	$(DIR_COMMON)engine/BMaterialsAnimRef.o \
	$(DIR_COMMON)engine/BMesh.o \
	$(DIR_COMMON)engine/BMeshRef.o \
	$(DIR_COMMON)engine/BMeshTools.o \
	$(DIR_COMMON)engine/BMorphingData.o \
	$(DIR_COMMON)engine/BOActor.o \
	$(DIR_COMMON)engine/BOBone.o \
	$(DIR_COMMON)engine/BOCamera.o \
	$(DIR_COMMON)engine/BOModel3d.o \
	$(DIR_COMMON)engine/BOCompositedModel3d.o \
	$(DIR_COMMON)engine/BOLight.o \
	$(DIR_COMMON)engine/BOSound.o \
	$(DIR_COMMON)engine/BOText.o \
	$(DIR_COMMON)engine/BObject3d.o \
	$(DIR_COMMON)engine/BObject3dAnim.o \
	$(DIR_COMMON)engine/BOSprite.o \
	$(DIR_COMMON)engine/BRenderer.o \
	$(DIR_COMMON)engine/BRendererCreator.o \
	$(DIR_COMMON)engine/BRendererManager.o \
	$(DIR_COMMON)engine/BScene.o \
	$(DIR_COMMON)engine/BScene2d.o \
	$(DIR_COMMON)engine/BShaderRef.o \
	$(DIR_COMMON)engine/BSkinData.o \
	$(DIR_COMMON)engine/BSoundRef.o \
	$(DIR_COMMON)engine/BTextureAnim.o \
	$(DIR_COMMON)engine/BTextureRef.o \
	$(DIR_COMMON)engine/BTexturesAnim.o \
	$(DIR_COMMON)engine/BTexturesAnimRef.o \
	$(DIR_COMMON)engine/BVariable.o \
	$(DIR_COMMON)engine/BWorld.o \
	$(DIR_COMMON)gui/BJoystick.o \
	$(DIR_COMMON)gui/BMouse.o 