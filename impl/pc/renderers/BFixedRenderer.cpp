/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Maratis
// BFixedRenderer.cpp
/////////////////////////////////////////////////////////////////////////////////////////////////////////

//========================================================================
// Copyright (c) 2003-2011 Anael Seghezzi <www.maratis3d.com>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//========================================================================

#include <tinyutf8.h>
#include <BEngine.h>
#include <BFixedRenderer.h>


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Init
/////////////////////////////////////////////////////////////////////////////////////////////////////////

BFixedRenderer::BFixedRenderer(void):
m_verticesNumber(0),
m_normalsNumber(0),
m_vertices(NULL),
m_normals(NULL)
{
}

BFixedRenderer::~BFixedRenderer(void)
{
	// delete skin cache
	SAFE_DELETE_ARRAY(m_vertices);
	SAFE_DELETE_ARRAY(m_normals);
}

void BFixedRenderer::destroy(void)
{
	delete this;
}

BRenderer * BFixedRenderer::getNew(void)
{
	return new BFixedRenderer();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Drawing
/////////////////////////////////////////////////////////////////////////////////////////////////////////

BVector3f * BFixedRenderer::getVertices(unsigned int size)
{
	if(size == 0)
		return NULL;

	if(size > m_verticesNumber)
	{
		SAFE_DELETE_ARRAY(m_vertices);
		m_vertices = new BVector3f[size];
		m_verticesNumber = size;
	}

	return m_vertices;
}

BVector3f * BFixedRenderer::getNormals(unsigned int size)
{
	if(size == 0)
		return NULL;

	if(size > m_normalsNumber)
	{
		SAFE_DELETE_ARRAY(m_normals);
		m_normals = new BVector3f[size];
		m_normalsNumber = size;
	}

	return m_normals;
}

void BFixedRenderer::updateSkinning(BMesh * mesh, BArmature * armature)
{
	unsigned int s;
	unsigned int sSize = mesh->getSubMeshsNumber();
	for(s=0; s<sSize; s++)
	{
		BSubMesh * subMesh = &mesh->getSubMeshs()[s];

		// data
		BVector3f * vertices = subMesh->getVertices();

		if(! vertices)
			continue;

		BSkinData * skinData = subMesh->getSkinData();
		if(armature && skinData)
		{
			unsigned int verticesSize = subMesh->getVerticesSize();
			BVector3f * skinVertices = getVertices(verticesSize);

			computeSkinning(armature, skinData, vertices, NULL, NULL, skinVertices, NULL, NULL);
			subMesh->getBoundingBox()->initFromPoints(skinVertices, verticesSize);
		}
	}

	mesh->updateBoundingBox();
}

void BFixedRenderer::drawDisplay(BSubMesh * subMesh, BDisplay * display, BVector3f * vertices, BVector3f * normals, BColor * colors)
{
	Bizarre * engine = Bizarre::getInstance();
	BRenderingContext * render = engine->getRenderingContext();


	render->setColor4(BVector4f(1, 1, 1, 1));


	// get material
	BMaterial * material = display->getMaterial();
	{
		float opacity = material->getOpacity();
		if(opacity <= 0.0f)
			return;

		// data
		U_TYPES indicesType = subMesh->getIndicesType();
		void * indices = subMesh->getIndices();
		BVector2f * texCoords = subMesh->getTexCoords();

		// begin / size
		unsigned int begin = display->getBegin();
		unsigned int size = display->getSize();

		// get properties
		U_PRIMITIVE_TYPES primitiveType = display->getPrimitiveType();
		M_BLENDING_MODES blendMode = material->getBlendMode();
		U_CULL_MODES cullMode = display->getCullMode();
		BVector3f diffuse = material->getDiffuse();
		BVector3f specular = material->getSpecular();
		BVector3f emit = material->getEmit();
		float shininess = material->getShininess();

		// get current fog color
		BVector3f currentFogColor;
		render->getFogColor(&currentFogColor);

		// set cull mode
		if(cullMode == U_CULL_NONE){
			render->disableCullFace();
		}
		else{
			render->enableCullFace();
			render->setCullMode(cullMode);
		}

		// texture passes
		unsigned int texturesPassNumber = MIN(8, material->getTexturesPassNumber());

		// set blending mode
		render->setBlendingMode(blendMode);

		// alpha test
		if(blendMode != M_BLENDING_ALPHA && texturesPassNumber > 0)
		{
			BTexturePass * texturePass = material->getTexturePass(0);
			BTexture * texture = texturePass->getTexture();
			if(texture)
			{
				if(texture->getTextureRef()->getComponents() > 3)
					render->setAlphaTest(0.5f);
			}
		}

		// set fog color depending on blending
		switch(blendMode)
		{
			case M_BLENDING_ADD:
			case M_BLENDING_LIGHT:
				render->setFogColor(BVector3f(0, 0, 0));
				break;
			case M_BLENDING_PRODUCT:
				render->setFogColor(BVector3f(1, 1, 1));
				break;
		}

		// fixed pipeline
		{
			// no FX
			render->bindFX(0);

			// Vertex
			render->enableVertexArray();
			render->setVertexPointer(M_FLOAT, 3, vertices);

			// Normal
			if(normals)
			{
				render->enableNormalArray();
				render->setNormalPointer(M_FLOAT, normals);
			}
			else
			{
				render->disableNormalArray();
			}

			// Color
			if(colors)
			{
				render->disableLighting();
				render->enableColorArray();
				render->setColorPointer(M_UBYTE, 4, colors);
			}
			else
			{
				render->disableColorArray();
			}

			// Material
			render->setMaterialDiffuse(BVector4f(diffuse.x, diffuse.y, diffuse.z, opacity));
			render->setMaterialSpecular(BVector4f(specular));
			render->setMaterialAmbient(BVector4f());
			render->setMaterialEmit(BVector4f(emit));
			render->setMaterialShininess(shininess);

			// switch to texture matrix mode
			if(texturesPassNumber > 0)
				render->setMatrixMode(M_MATRIX_TEXTURE);
			else
			{
				render->bindTexture(0);
				render->disableTexture();
				render->disableTexCoordArray();
			}

			// Textures
			int id = texturesPassNumber;
			for(unsigned int t=0; t<texturesPassNumber; t++)
			{
				BTexturePass * texturePass = material->getTexturePass(t);

				BTexture * texture = texturePass->getTexture();
				if((! texture) || (! texCoords))
				{
					render->bindTexture(0, t);
					render->disableTexture();
					render->disableTexCoordArray();
					continue;
				}

				// texCoords
				unsigned int offset = 0;
				if(subMesh->isMapChannelExist(texturePass->getMapChannel()))
					offset = subMesh->getMapChannelOffset(texturePass->getMapChannel());

				// texture id
				unsigned int textureId = 0;
				BTextureRef * texRef = texture->getTextureRef();
				if(texRef)
					textureId = texRef->getTextureId();

				// bind texture
				render->bindTexture(textureId, t);
				render->enableTexture();
				render->setTextureCombineMode(texturePass->getCombineMode());
				render->setTextureUWrapMode(texture->getUWrapMode());
				render->setTextureVWrapMode(texture->getVWrapMode());

				// texture matrix
				render->loadIdentity();
				render->translate(BVector2f(0.5f, 0.5f));
				render->scale(texture->getTexScale());
				render->rotate(BVector3f(0, 0, -1), texture->getTexRotate());
				render->translate(BVector2f(-0.5f, -0.5f));
				render->translate(texture->getTexTranslate());

				// texture coords
				render->enableTexCoordArray();
				render->setTexCoordPointer(M_FLOAT, 2, texCoords + offset);
			}

			// switch back to modelview matrix mode
			if(texturesPassNumber > 0)
				render->setMatrixMode(M_MATRIX_MODELVIEW);

			// draw
			if(indices)
			{
				switch(indicesType)
				{
					case U_USHORT:
						render->drawElement(primitiveType, size, indicesType, (unsigned short*)indices + begin);
						break;
					case U_UINT:
						render->drawElement(primitiveType, size, indicesType, (unsigned int*)indices + begin);
						break;
				}
			}
			else{
				render->drawArray(primitiveType, begin, size);
			}


			// disable arrays
			render->disableVertexArray();
			render->disableNormalArray();
			render->disableColorArray();

			// restore textures
			for(int t=(int)(id-1); t>=0; t--)
			{
				render->bindTexture(0, t);
				render->disableTexture();
				render->disableTexCoordArray();
				render->setTextureCombineMode(M_TEX_COMBINE_MODULATE);

				render->setMatrixMode(M_MATRIX_TEXTURE);
				render->loadIdentity();
				render->setMatrixMode(M_MATRIX_MODELVIEW);
			}
		}

		// restore fog and alpha test
		render->setFogColor(currentFogColor);
		if(blendMode != M_BLENDING_ALPHA)
			render->setAlphaTest(0.0f);

		// restore lighting
		if(colors)
			render->enableLighting();
	}
}

void BFixedRenderer::drawDisplayTriangles(BSubMesh * subMesh, BDisplay * display, BVector3f * vertices)
{
	BRenderingContext * render = Bizarre::getInstance()->getRenderingContext();

	// begin / size
	unsigned int begin = display->getBegin();
	unsigned int size = display->getSize();

	// display properties
	U_PRIMITIVE_TYPES primitiveType = display->getPrimitiveType();
	U_CULL_MODES cullMode = display->getCullMode();

	// cull mode
	if(cullMode == U_CULL_NONE){
		render->disableCullFace();
	}
	else{
		render->enableCullFace();
		render->setCullMode(cullMode);
	}

	// indices
	U_TYPES indicesType = subMesh->getIndicesType();
	void * indices = subMesh->getIndices();

	// FX
	render->bindFX(0);

	// Vertex
	render->enableVertexArray();
	render->setVertexPointer(M_FLOAT, 3, vertices);

	// draw
	if(indices)
	{
		switch(indicesType)
		{
			case U_USHORT:
				render->drawElement(primitiveType, size, indicesType, (unsigned short*)indices + begin);
				break;
			case U_UINT:
				render->drawElement(primitiveType, size, indicesType, (unsigned int*)indices + begin);
				break;
		}
	}
	else
		render->drawArray(primitiveType, begin, size);

	// disable vertex array
	render->disableVertexArray();

	// restore FX
	render->bindFX(0);
}

void BFixedRenderer::drawOpaques(BSubMesh * subMesh, BArmature * armature)
{
	// data
	BVector3f * vertices = subMesh->getVertices();
	BVector3f * normals = subMesh->getNormals();
	BColor * colors = subMesh->getColors();

	if(! vertices)
		return;

	BSkinData * skinData = subMesh->getSkinData();
	if(armature && skinData)
	{
		unsigned int verticesSize = subMesh->getVerticesSize();
		unsigned int normalsSize = subMesh->getNormalsSize();

		BVector3f * skinVertices = getVertices(verticesSize);
		BVector3f * skinNormals = getNormals(normalsSize);

		computeSkinning(armature, skinData, vertices, normals, NULL, skinVertices, skinNormals, NULL);
		subMesh->getBoundingBox()->initFromPoints(skinVertices, verticesSize);

		vertices = skinVertices;
		normals = skinNormals;
	}

	unsigned int i;
	unsigned int displayNumber = subMesh->getDisplaysNumber();
	for(i=0; i<displayNumber; i++)
	{
		BDisplay * display = subMesh->getDisplay(i);
		if(! display->isVisible())
			continue;

		BMaterial * material = display->getMaterial();
		if(material)
		{
			if(material->getBlendMode() == M_BLENDING_NONE)
				drawDisplay(subMesh, display, vertices, normals, colors);
		}
	}
}

void BFixedRenderer::drawTransparents(BSubMesh * subMesh, BArmature * armature)
{
	BRenderingContext * render = Bizarre::getInstance()->getRenderingContext();

	// data
	BVector3f * vertices = subMesh->getVertices();
	BVector3f * normals = subMesh->getNormals();
	BColor * colors = subMesh->getColors();

	if(! vertices)
		return;

	BSkinData * skinData = subMesh->getSkinData();
	if(armature && skinData)
	{
		unsigned int verticesSize = subMesh->getVerticesSize();
		unsigned int normalsSize = subMesh->getNormalsSize();

		BVector3f * skinVertices = getVertices(verticesSize);
		BVector3f * skinNormals = getNormals(normalsSize);

		computeSkinning(armature, skinData, vertices, normals, NULL, skinVertices, skinNormals, NULL);
		subMesh->getBoundingBox()->initFromPoints(skinVertices, verticesSize);

		vertices = skinVertices;
		normals = skinNormals;
	}

	
	unsigned int i;
	unsigned int displayNumber = subMesh->getDisplaysNumber();
	
	/*
	// not sure of this technique
	render->setColorMask(0, 0, 0, 0);

	for(i=0; i<displayNumber; i++)
	{
		BDisplay * display = subMesh->getDisplay(i);
		if((! display->isVisible()) || (! display->getMaterial()))
			continue;

		if(display->getMaterial()->getBlendMode() == M_BLENDING_ALPHA)
			drawDisplayTriangles(subMesh, display, vertices);
	}

	render->setColorMask(1, 1, 1, 1);
	render->setDepthMask(0);*/

	for(i=0; i<displayNumber; i++)
	{
		BDisplay * display = subMesh->getDisplay(i);
		if(! display->isVisible())
			continue;

		BMaterial * material = display->getMaterial();
		if(material)
		{
			if(material->getBlendMode() != M_BLENDING_NONE)
				drawDisplay(subMesh, display, vertices, normals, colors);
		}
	}

	//render->setDepthMask(1);
}

float BFixedRenderer::getDistanceToCam(BOCamera * camera, const BVector3f & pos)
{
	if(! camera->isOrtho())
	{
		return (pos - camera->getTransformedPosition()).getSquaredLength();
	}

	BVector3f axis = camera->getRotatedVector(BVector3f(0, 0, -1)).getNormalized();
	float dist = (pos - camera->getTransformedPosition()).dotProduct(axis);
	return dist*dist;
}

void BFixedRenderer::updateVisibility(BScene * scene, BOCamera * camera)
{
	// make frustum
	camera->getFrustum()->makeVolume(camera);

	// compute object visibility
	unsigned int i;
	unsigned int oSize = scene->getObjectsNumber();
	for(i=0; i<oSize; i++)
	{
		BObject3d * object = scene->getObjectByIndex(i);
		if(object->isActive())
			object->updateVisibility(camera);
	}
}

void BFixedRenderer::enableFog(BOCamera * camera)
{
	BRenderingContext * render = Bizarre::getInstance()->getRenderingContext();

	float fogMin = camera->getClippingFar()*0.9999f;
	if(camera->hasFog())
	{
		render->enableFog();
		float camFogMin = camera->getClippingFar() - camera->getFogDistance();
		if(camFogMin < fogMin)
			fogMin = camFogMin;
	}
	else {
		render->disableFog();
	}

	render->setFogColor(camera->getClearColor());
	render->setFogDistance(fogMin, camera->getClippingFar());
}



void BFixedRenderer::drawText(BOText * textObj)
{
	BFont * font = textObj->getFont();
	const char * text = textObj->getText();
	vector <float> * linesOffset = textObj->getLinesOffset();

	if(! (strlen(text) > 0 && font))
		return;

	if(linesOffset->size() == 0)
		return;

	BRenderingContext * render = Bizarre().getInstance()->getRenderingContext();


	render->enableBlending();
	render->enableTexture();
	render->disableLighting();
	render->disableCullFace();
	render->setDepthMask(0);

	render->setColor4(textObj->getColor());
	render->setBlendingMode(M_BLENDING_ALPHA);

	static BVector2f vertices[4];
	static BVector2f texCoords[4];

	render->disableNormalArray();
	render->disableColorArray();
	render->enableVertexArray();
	render->enableTexCoordArray();

	render->setVertexPointer(M_FLOAT, 2, vertices);
	render->setTexCoordPointer(M_FLOAT, 2, texCoords);

	render->bindTexture(font->getTextureId());

	unsigned int lineId = 0;
	float lineOffset = (*linesOffset)[0];

	float size = textObj->getSize();
	float tabSize = size*2;
	float fontSize = (float)font->getFontSize();
	float widthFactor = font->getTextureWith() / fontSize;
	float heightFactor = font->getTextureHeight() / fontSize;
	float xc = 0, yc = 0;

	unsigned int charCode;
	unsigned int state = 0;
	unsigned char* s = (unsigned char*)text;	
	for(; *s; ++s)
	{
		if(utf8_decode(&state, &charCode, *s) != UTF8_ACCEPT)
			continue;
	
		if(charCode == '\n') // return
		{
			lineId++;
			lineOffset = (*linesOffset)[lineId];

			yc += size;
			xc = 0;
			continue;
		}

		if(charCode == '\t') // tab
		{
			int tab = (int)(xc / tabSize) + 1;
			xc = tab*tabSize;
			continue;
		}

		// get character
		BCharacter * character = font->getCharacter(charCode);
		if(! character)
			continue;

		BVector2f pos = character->getPos();
		BVector2f scale = character->getScale();
		BVector2f offset = character->getOffset() * size + BVector2f(lineOffset, 0);

		float width = scale.x * widthFactor * size;
		float height = scale.y * heightFactor * size;

		// construct quad
		texCoords[0] = BVector2f(pos.x, (pos.y + scale.y));
		vertices[0] = BVector2f(xc, (yc + height)) + offset;

		texCoords[1] = BVector2f((pos.x + scale.x), (pos.y + scale.y));
		vertices[1] = BVector2f((xc + width), (yc + height)) + offset;

		texCoords[3] = BVector2f((pos.x + scale.x), pos.y);
		vertices[3] = BVector2f((xc + width), yc) + offset;

		texCoords[2] = BVector2f(pos.x, pos.y);
		vertices[2] = BVector2f(xc, yc) + offset;

		// draw quad
		render->drawArray(U_PRIMITIVE_TRIANGLE_STRIP, 0, 4);

		//move to next character
		xc += character->getXAdvance() * size;
	}
	
	render->setDepthMask(1);
}

/*
void BFixedRenderer::drawText(BOText * textObj)
{
	BFont * font = textObj->getFont();
	const char * text = textObj->getText();
	vector <float> * linesOffset = textObj->getLinesOffset();

	if(! (strlen(text) > 0 && font))
		return;

	if(linesOffset->size() == 0)
		return;

	BRenderingContext * render = Bizarre().getInstance()->getRenderingContext();


	render->enableBlending();
	render->enableTexture();
	render->disableLighting();
	render->disableCullFace();
	render->setDepthMask(0);

	render->setColor4(textObj->getColor());
	render->setBlendingMode(M_BLENDING_ALPHA);

	static BVector2f vertices[4];
	static BVector2f texCoords[4];

	render->disableNormalArray();
	render->disableColorArray();
	render->enableVertexArray();
	render->enableTexCoordArray();

	render->setVertexPointer(M_FLOAT, 2, vertices);
	render->setTexCoordPointer(M_FLOAT, 2, texCoords);

	render->bindTexture(font->getTextureId());

	unsigned int lineId = 0;
	float lineOffset = (*linesOffset)[0];

	float size = textObj->getSize();
	float tabSize = size*2;
	float fontSize = (float)font->getFontSize();
	float widthFactor = font->getTextureWith() / fontSize;
	float heightFactor = font->getTextureHeight() / fontSize;
	float xc = 0, yc = 0;

	unsigned int i;
	unsigned int textLen = strlen(text);
	for(i=0; i<textLen; i++)
	{
		if(text[i] == '\n') // return
		{
			if(((i+1) < textLen))
			{
				lineId++;
				lineOffset = (*linesOffset)[lineId];

				yc += size;
				xc = 0;
			}
			continue;
		}

		if(text[i] == '\t') // tab
		{
			int tab = (int)(xc / tabSize) + 1;
			xc = tab*tabSize;
			continue;
		}

		// get character
		unsigned int charCode = (unsigned int)((unsigned char)text[i]);
		BCharacter * character = font->getCharacter(charCode);
		if(! character)
			continue;

		BVector2f pos = character->getPos();
		BVector2f scale = character->getScale();
		BVector2f offset = character->getOffset() * size + BVector2f(lineOffset, 0);

		float width = scale.x * widthFactor * size;
		float height = scale.y * heightFactor * size;

		// construct quad
		texCoords[0] = BVector2f(pos.x, (pos.y + scale.y));
		vertices[0] = BVector2f(xc, (yc + height)) + offset;

		texCoords[1] = BVector2f((pos.x + scale.x), (pos.y + scale.y));
		vertices[1] = BVector2f((xc + width), (yc + height)) + offset;

		texCoords[3] = BVector2f((pos.x + scale.x), pos.y);
		vertices[3] = BVector2f((xc + width), yc) + offset;

		texCoords[2] = BVector2f(pos.x, pos.y);
		vertices[2] = BVector2f(xc, yc) + offset;

		// draw quad
		render->drawArray(U_PRIMITIVE_TRIANGLE_STRIP, 0, 4);

		//move to next character
		xc += character->getXAdvance() * size;
	}
	
	render->setDepthMask(1);
}

*/

void BFixedRenderer::drawScene(BScene * scene, BOCamera * camera)
{
	struct BEntityLight
	{
		BBox3d lightBox;
		BOLight * light;
	};

	struct BSubMeshPass
	{
		unsigned int subMeshId;
		unsigned int lightsNumber;
		BObject3d * object;
		BOLight * lights[4];
	};

	// sub objects
	#define MAX_TRANSP_SUBOBJ 4096
	static int transpList[MAX_TRANSP_SUBOBJ];
	static float transpZList[MAX_TRANSP_SUBOBJ];
	static BSubMeshPass transpSubObjs[MAX_TRANSP_SUBOBJ];

	// lights list
	#define MAX_ENTITY_LIGHTS 256
	static int entityLightsList[MAX_ENTITY_LIGHTS];
	static float entityLightsZList[MAX_ENTITY_LIGHTS];
	static BEntityLight entityLights[MAX_ENTITY_LIGHTS];


	// get render
	BRenderingContext * render = Bizarre::getInstance()->getRenderingContext();
	render->enableLighting();
	render->enableBlending();


	// make frustum
	BFrustum * frustum = camera->getFrustum();
	frustum->makeVolume(camera);

	// update visibility
	updateVisibility(scene, camera);

	// fog
	enableFog(camera);

	// camera
	BVector3f cameraPos = camera->getTransformedPosition();


	// transp sub obj number
	unsigned int transpSubObsNumber = 0;

	// lights
	unsigned int l;
	unsigned int lSize = scene->getLightsNumber();

	// entities
	unsigned int i;
	unsigned int eSize = scene->getEntitiesNumber();
	for(i=0; i<eSize; i++)
	{
		// get entity
		BOModel3d * entity = scene->getModelByIndex(i);
		BMesh * mesh = entity->getMesh();

		if(! entity->isActive())
			continue;

		if(! entity->isVisible())
		{
			if(mesh)
			{
				BArmature * armature = mesh->getArmature();
				BArmatureAnim * armatureAnim = mesh->getArmatureAnim();
				if(armature)
				{
					// animate armature
					if(mesh->getArmature())
					{
						BArmature * armature = mesh->getArmature();
						if(mesh->getArmatureAnim())
						{
							animateArmature(
								mesh->getArmature(),
								mesh->getArmatureAnim(),
								entity->getCurrentFrame()
							);
						}
						else
						{
							armature->processBonesLinking();
							armature->updateBonesSkinMatrix();
						}
					}

					// TODO : optimize and add a tag to desactivate it
					updateSkinning(mesh, armature);
					(*entity->getBoundingBox()) = (*mesh->getBoundingBox());
				}
			}

			continue;
		}

		// draw mesh
		if(mesh)
		{
			BVector3f scale = entity->getTransformedScale();
			BBox3d * entityBox = entity->getBoundingBox();

			float minScale = scale.x;
			minScale = MIN(minScale, scale.y);
			minScale = MIN(minScale, scale.z);
			minScale = 1.0f / minScale;

			unsigned int entityLightsNumber = 0;
			for(l=0; l<lSize; l++)
			{
				// get entity
				BOLight * light = scene->getLightByIndex(l);

				if(! light->isActive())
					continue;

				if(! light->isVisible())
					continue;

				// light box
				BVector3f lightPos = light->getTransformedPosition();
				BVector3f localPos = entity->getInversePosition(lightPos);

				float localRadius = light->getRadius() * minScale;

				BBox3d lightBox(
								BVector3f(localPos - localRadius),
								BVector3f(localPos + localRadius)
								);

				if(! entityBox->isInCollisionWith(lightBox))
					continue;

				BEntityLight * entityLight = &entityLights[entityLightsNumber];
				entityLight->lightBox = lightBox;
				entityLight->light = light;

				entityLightsNumber++;
				if(entityLightsNumber == MAX_ENTITY_LIGHTS)
					break;
			}

			// animate armature
			if(mesh->getArmature())
			{
				BArmature * armature = mesh->getArmature();
				if(mesh->getArmatureAnim())
				{
					animateArmature(
						mesh->getArmature(),
						mesh->getArmatureAnim(),
						entity->getCurrentFrame()
					);
				}
				else
				{
					armature->processBonesLinking();
					armature->updateBonesSkinMatrix();
				}
			}

			// animate textures
			if(mesh->getTexturesAnim())
				animateTextures(mesh, mesh->getTexturesAnim(), entity->getCurrentFrame());

			// animate materials
			if(mesh->getMaterialsAnim())
				animateMaterials(mesh, mesh->getMaterialsAnim(), entity->getCurrentFrame());

			unsigned int s;
			unsigned int sSize = mesh->getSubMeshsNumber();
			for(s=0u; s<sSize; s++)
			{
				BSubMesh * subMesh = &mesh->getSubMeshs()[s];
				BBox3d * box = subMesh->getBoundingBox();

				// check if submesh visible
				if(sSize > 1)
				{
					BVector3f * min = &box->min;
					BVector3f * max = &box->max;

					BVector3f points[8] = {
						entity->getTransformedVector(BVector3f(min->x, min->y, min->z)),
						entity->getTransformedVector(BVector3f(min->x, max->y, min->z)),
						entity->getTransformedVector(BVector3f(max->x, max->y, min->z)),
						entity->getTransformedVector(BVector3f(max->x, min->y, min->z)),
						entity->getTransformedVector(BVector3f(min->x, min->y, max->z)),
						entity->getTransformedVector(BVector3f(min->x, max->y, max->z)),
						entity->getTransformedVector(BVector3f(max->x, max->y, max->z)),
						entity->getTransformedVector(BVector3f(max->x, min->y, max->z))
					};

					if(! frustum->isVolumePointsVisible(points, 8))
						continue;
				}

				// subMesh center
				BVector3f center = box->min + (box->max - box->min)*0.5f;
				center = entity->getTransformedVector(center);

				// sort entity lights
				unsigned int lightsNumber = 0;
				for(l=0; l<entityLightsNumber; l++)
				{
					BEntityLight * entityLight = &entityLights[l];
					if(! box->isInCollisionWith(entityLight->lightBox))
						continue;

					BOLight * light = entityLight->light;

					float z = (center - light->getTransformedPosition()).getLength();
					entityLightsList[lightsNumber] = l;
					entityLightsZList[l] = (1.0f/z)*light->getRadius();
					lightsNumber++;
				}

				if(lightsNumber > 1)
					sortFloatList(entityLightsList, entityLightsZList, 0, (int)lightsNumber-1);

				// local lights
				if(lightsNumber > 4)
					lightsNumber = 4;

				for(l=0; l<lightsNumber; l++)
				{
					BEntityLight * entityLight = &entityLights[entityLightsList[l]];
					BOLight * light = entityLight->light;

					// attenuation
					float quadraticAttenuation = (8.0f / light->getRadius());
					quadraticAttenuation = (quadraticAttenuation*quadraticAttenuation)*light->getIntensity();

					// color
					BVector3f color = light->getFinalColor();

					// set light
					render->enableLight(l);
					render->setLightPosition(l, light->getTransformedPosition());
					render->setLightDiffuse(l, BVector4f(color));
					render->setLightSpecular(l, BVector4f(color));
					render->setLightAmbient(l, BVector3f(0, 0, 0));
					render->setLightAttenuation(l, 1, 0, quadraticAttenuation);

					// spot
					render->setLightSpotAngle(l, light->getSpotAngle());
					if(light->getSpotAngle() < 90){
						render->setLightSpotDirection(l, light->getRotatedVector(BVector3f(0, 0, -1)).getNormalized());
						render->setLightSpotExponent(l, light->getSpotExponent());
					}
					else {
						render->setLightSpotExponent(l, 0.0f);
					}
				}

				for(l=lightsNumber; l<4; l++){
					render->disableLight(l);
				}

				render->pushMatrix();
				render->multMatrix(entity->getMatrix());

				// draw opaques
				drawOpaques(subMesh, mesh->getArmature());

				if(subMesh->hasTransparency())
				{
					if(transpSubObsNumber < MAX_TRANSP_SUBOBJ)
					{
						// transparent subMesh pass
						BSubMeshPass * subMeshPass = &transpSubObjs[transpSubObsNumber];

						// lights
						subMeshPass->lightsNumber = lightsNumber;
						for(l=0; l<lightsNumber; l++)
							subMeshPass->lights[l] = entityLights[entityLightsList[l]].light;

						// z distance to camera
						float z = getDistanceToCam(camera, center);

						// set values
						transpList[transpSubObsNumber] = transpSubObsNumber;
						transpZList[transpSubObsNumber] = z;
						subMeshPass->subMeshId = s;
						subMeshPass->object = entity;

						transpSubObsNumber++;
					}
				}

				render->popMatrix();
			}

			mesh->updateBoundingBox();
			(*entity->getBoundingBox()) = (*mesh->getBoundingBox());
		}
	}


	// texts
	unsigned int tSize = scene->getTextsNumber();
	for(i=0; i<tSize; i++)
	{
		BOText * text = scene->getTextByIndex(i);
		if(text->isActive() && text->isVisible())
		{
			// transparent pass
			BSubMeshPass * subMeshPass = &transpSubObjs[transpSubObsNumber];

			// center
			BBox3d * box = text->getBoundingBox();
			BVector3f center = box->min + (box->max - box->min)*0.5f;
			center = text->getTransformedVector(center);

			// z distance to camera
			float z = getDistanceToCam(camera, center);

			// set values
			transpList[transpSubObsNumber] = transpSubObsNumber;
			transpZList[transpSubObsNumber] = z;
			subMeshPass->object = text;

			transpSubObsNumber++;
		}
	}


	// sort transparent list
	if(transpSubObsNumber > 1)
		sortFloatList(transpList, transpZList, 0, (int)transpSubObsNumber-1);

	// draw transparents
	render->setDepthMask(0);
	
	for(i=0; i<transpSubObsNumber; i++)
	{
		BSubMeshPass * subMeshPass = &transpSubObjs[transpList[i]];
		BObject3d * object = subMeshPass->object;

		// objects
		switch(object->getType())
		{
			case U_OBJECT3D_MODEL:
			{
				BOModel3d * entity = (BOModel3d *)object;
				unsigned int subMeshId = subMeshPass->subMeshId;
				BMesh * mesh = entity->getMesh();
				BSubMesh * subMesh = &mesh->getSubMeshs()[subMeshId];

				// animate armature
				if(mesh->getArmature())
				{
					BArmature * armature = mesh->getArmature();
					if(mesh->getArmatureAnim())
					{
						animateArmature(
							mesh->getArmature(),
							mesh->getArmatureAnim(),
							entity->getCurrentFrame()
						);
					}
					else
					{
						armature->processBonesLinking();
						armature->updateBonesSkinMatrix();
					}
				}

				// animate textures
				if(mesh->getTexturesAnim())
					animateTextures(mesh, mesh->getTexturesAnim(), entity->getCurrentFrame());

				// animate materials
				if(mesh->getMaterialsAnim())
					animateMaterials(mesh, mesh->getMaterialsAnim(), entity->getCurrentFrame());

				// lights
				for(l=0; l<subMeshPass->lightsNumber; l++)
				{
					BOLight * light = subMeshPass->lights[l];

					// attenuation
					float quadraticAttenuation = (8.0f / light->getRadius());
					quadraticAttenuation = (quadraticAttenuation*quadraticAttenuation)*light->getIntensity();

					// color
					BVector3f color = light->getFinalColor();

					// set light
					render->enableLight(l);
					render->setLightPosition(l, light->getTransformedPosition());
					render->setLightDiffuse(l, BVector4f(color));
					render->setLightSpecular(l, BVector4f(color));
					render->setLightAmbient(l, BVector3f(0, 0, 0));
					render->setLightAttenuation(l, 1, 0, quadraticAttenuation);

					// spot
					render->setLightSpotAngle(l, light->getSpotAngle());
					if(light->getSpotAngle() < 90){
						render->setLightSpotDirection(l, light->getRotatedVector(BVector3f(0, 0, -1)).getNormalized());
						render->setLightSpotExponent(l, light->getSpotExponent());
					}
					else {
						render->setLightSpotExponent(l, 0.0f);
					}
				}

				for(l=subMeshPass->lightsNumber; l<4; l++){
					render->disableLight(l);
				}

				render->pushMatrix();
				render->multMatrix(entity->getMatrix());
				drawTransparents(subMesh, mesh->getArmature());
				render->popMatrix();

				mesh->updateBoundingBox();
				(*entity->getBoundingBox()) = (*mesh->getBoundingBox());
			}
				break;

			case U_OBJECT3D_TEXT:
			{
				BOText * text = (BOText *)object;

				render->pushMatrix();
				render->multMatrix(text->getMatrix());
				drawText(text);
				render->popMatrix();
			}
				break;
		}
	}
	
	render->setDepthMask(1);

	render->disableLighting();
	render->disableFog();
}
