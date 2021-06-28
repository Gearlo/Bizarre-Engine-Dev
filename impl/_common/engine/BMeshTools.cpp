/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bizarre
// BMeshTools.cpp
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

#include <BEngine.h>

// blend matrices optim
#ifdef __SSE2__
#include <mmintrin.h>
#include <xmmintrin.h>

static void blendMatrices(BMatrix4x4 * matrix, const BMatrix4x4 * skinMatrix, const float weight)
{
	__m128 w = _mm_set1_ps(weight);
				
	for(int i=0; i<16; i+=4)
	{
		__m128 a = _mm_loadu_ps(matrix->entries + i);
		__m128 b = _mm_loadu_ps(skinMatrix->entries + i);
		__m128 c = _mm_mul_ps(b, w);
		__m128 d = _mm_add_ps(a, c);
		_mm_storeu_ps(matrix->entries + i, d);
	}
}
#else
static void blendMatrices(BMatrix4x4 * matrix, const BMatrix4x4 * skinMatrix, const float weight)
{
	for(int i=0; i<16; i++)
		matrix->entries[i] += skinMatrix->entries[i] * weight;
}
#endif

// animation
bool animateFloat(BKey * keys, unsigned int keysNumber, float t, float * value)
{
	// no keys
	if(keysNumber == 0)
		return false;

	// one key
	if(keysNumber == 1){
		(*value) = *((float *)keys->getData());
		return true;
	}

	// out of range
	BKey * keyMin = keys;
	BKey * keyMax = keys + (keysNumber - 1);

	int tMin = keyMin->getT();
	int tMax = keyMax->getT();

	if (t <= tMin)
    {
		(*value) = *((float *)keyMin->getData());
		return true;
	}

	if (t >= tMax)
    {
		(*value) = *((float *)keyMax->getData());
		return true;
	}

	// interpolation
	for (unsigned int i = 1; i < keysNumber; i++)
	{
		BKey * key0 = keys;
		BKey * key1 = keys+1;

		int t0 = key0->getT();
		int t1 = key1->getT();

		if ((t >= t0) && (t <= t1))
		{
			float factor = (t - t0) / (float)(t1 - t0);
			float * data0 = (float *)key0->getData();
			float * data1 = (float *)key1->getData();

			(*value) = (*data0) + ((*data1) - (*data0))*factor;
			return true;
		}

		keys++;
	}

	return false;
}

bool animateVector2(BKey * keys, unsigned int keysNumber, float t, BVector2f * vector2)
{
	// no keys
	if (keysNumber == 0)
		return false;

	// one key
	if (keysNumber == 1)
    {
		(*vector2) = *((BVector2f *)keys->getData());
		return true;
	}

	// out of range
	BKey * keyMin = keys;
	BKey * keyMax = keys + (keysNumber - 1);

	int tMin = keyMin->getT();
	int tMax = keyMax->getT();

	if (t <= tMin)
    {
		(*vector2) = *((BVector2f *)keyMin->getData());
		return true;
	}

	if (t >= tMax)
    {
		(*vector2) = *((BVector2f *)keyMax->getData());
		return true;
	}

	// interpolation
	for (unsigned int i = 1; i < keysNumber; i++)
	{
		BKey * key0 = keys;
		BKey * key1 = keys+1;

		int t0 = key0->getT();
		int t1 = key1->getT();

		if ((t >= t0) && (t <= t1))
		{
			float factor = (t - t0) / (float)(t1 - t0);
			BVector2f * data0 = (BVector2f *)key0->getData();
			BVector2f * data1 = (BVector2f *)key1->getData();

			(*vector2) = (*data0) + ((*data1) - (*data0))*factor;
			return true;
		}

		keys++;
	}

	return false;
}

bool animateVector3(BKey * keys, unsigned int keysNumber, float t, BVector3f * vector3)
{
	// no keys
	if (keysNumber == 0)
		return false;

	// one key
	if (keysNumber == 1)
    {
		(*vector3) = *((BVector3f *)keys->getData());
		return true;
	}

	// out of range
	BKey * keyMin = keys;
	BKey * keyMax = keys + (keysNumber - 1);

	int tMin = keyMin->getT();
	int tMax = keyMax->getT();

	if (t <= tMin)
    {
		(*vector3) = *((BVector3f *)keyMin->getData());
		return true;
	}

	if (t >= tMax)
    {
		(*vector3) = *((BVector3f *)keyMax->getData());
		return true;
	}

	// interpolation
	for (unsigned int i = 1; i < keysNumber; i++)
	{
		BKey * key0 = keys;
		BKey * key1 = keys+1;

		int t0 = key0->getT();
		int t1 = key1->getT();

		if ((t >= t0) && (t <= t1))
		{
			float factor = (t - t0) / (float)(t1 - t0);
			BVector3f * data0 = (BVector3f *)key0->getData();
			BVector3f * data1 = (BVector3f *)key1->getData();

			(*vector3) = (*data0) + ((*data1) - (*data0))*factor;
			return true;
		}

		keys++;
	}

	return false;
}

bool animateQuaternion(BKey * keys, unsigned int keysNumber, float t, BQuaternion * quaternion)
{
	// no keys
	if (keysNumber == 0)
		return false;

	// one key
	if (keysNumber == 1)
    {
		(*quaternion) = *((BQuaternion *)keys->getData());
		return true;
	}

	// out of range
	BKey * keyMin = keys;
	BKey * keyMax = keys + (keysNumber - 1);

	int tMin = keyMin->getT();
	int tMax = keyMax->getT();

	if (t <= tMin)
    {
		(*quaternion) = *((BQuaternion *)keyMin->getData());
		return true;
	}

	if (t >= tMax)
    {
		(*quaternion) = *((BQuaternion *)keyMax->getData());
		return true;
	}

	// interpolation
	for (unsigned int i = 1; i < keysNumber; i++)
	{
		BKey * key0 = keys;
		BKey * key1 = keys+1;

		int t0 = key0->getT();
		int t1 = key1->getT();

		if (t == t0)
		{
			(*quaternion) = *(BQuaternion *)key0->getData();
			return true;
		}

		if (t == t1)
		{
			(*quaternion) = *(BQuaternion *)key1->getData();
			return true;
		}

		if ((t > t0) && (t < t1))
		{
			float factor = (t - t0) / (float)(t1 - t0);
			BQuaternion * data0 = (BQuaternion *)key0->getData();
			BQuaternion * data1 = (BQuaternion *)key1->getData();

			(*quaternion) = BQuaternion(*data0, *data1, factor);
			return true;
		}

		keys++;
	}

	return false;
}

void animateArmature(BArmature * armature, BArmatureAnim * armatureAnim, float t)
{
	BObject3dAnim * bonesAnim = armatureAnim->getBonesAnim();

	BVector3f position;
	BVector3f scale;
	BQuaternion rotation;

	unsigned int b;
	unsigned int bSize = armatureAnim->getBonesAnimNumber();
	for (b = 0; b < bSize; b++)
	{
		BOBone * bone = armature->getBone(b);
		
		// position
		if(animateVector3(bonesAnim->getPositionKeys(), bonesAnim->getPositionKeysNumber(), t, &position))
			bone->setPosition(position);

		// scale
		if(animateVector3(bonesAnim->getScaleKeys(), bonesAnim->getScaleKeysNumber(), t, &scale))
			bone->setScale(scale);

		// rotation
		if(animateQuaternion(bonesAnim->getRotationKeys(), bonesAnim->getRotationKeysNumber(), t, &rotation))
			bone->setRotation(rotation);

		bonesAnim++;
	}

	armature->processBonesLinking();
	armature->updateBonesSkinMatrix();
}

void animateTextures(BMesh * mesh, BTexturesAnim * texturesAnim, float t)
{
	BTextureAnim * texAnim = texturesAnim->getTexturesAnim();

	float rotation;
	BVector2f translate;
	BVector2f scale;

	unsigned int tex;
	unsigned int texSize = texturesAnim->getTexturesAnimNumber();
	for (tex = 0; tex < texSize; tex++)
	{
		BTexture * texture = mesh->getTexture(tex);
		
		// rotation
		if(animateFloat(texAnim->getRotationKeys(), texAnim->getRotationKeysNumber(), t, &rotation))
			texture->setTexRotate(rotation);

		// translate
		if(animateVector2(texAnim->getTranslateKeys(), texAnim->getTranslateKeysNumber(), t, &translate))
			texture->setTexTranslate(translate);

		// scale
		if(animateVector2(texAnim->getScaleKeys(), texAnim->getScaleKeysNumber(), t, &scale))
			texture->setTexScale(scale);

		texAnim++;
	}
}

void animateMaterials(BMesh * mesh, BMaterialsAnim * materialsAnim, float t)
{
	BMaterialAnim * matAnim = materialsAnim->getMaterialsAnim();

	float opacity;
	float shininess;
	float customValue;
	BVector3f diffuse;
	BVector3f specular;
	BVector3f emit;
	BVector3f customColor;

	unsigned int m;
	unsigned int mSize = materialsAnim->getMaterialsAnimNumber();
	for (m = 0; m < mSize; m++)
	{
		BMaterial * material = mesh->getMaterial(m);
		
		// opacity
		if(animateFloat(matAnim->getOpacityKeys(), matAnim->getOpacityKeysNumber(), t, &opacity))
			material->setOpacity(opacity);

		// shininess
		if(animateFloat(matAnim->getShininessKeys(), matAnim->getShininessKeysNumber(), t, &shininess))
			material->setShininess(shininess);

		// customValue
		if(animateFloat(matAnim->getCustomValueKeys(), matAnim->getCustomValueKeysNumber(), t, &customValue))
			material->setCustomValue(customValue);

		// diffuse
		if(animateVector3(matAnim->getDiffuseKeys(), matAnim->getDiffuseKeysNumber(), t, &diffuse))
			material->setDiffuse(diffuse);

		// specular
		if(animateVector3(matAnim->getSpecularKeys(), matAnim->getSpecularKeysNumber(), t, &specular))
			material->setSpecular(specular);

		// emit
		if(animateVector3(matAnim->getEmitKeys(), matAnim->getEmitKeysNumber(), t, &emit))
			material->setEmit(emit);

		// customColor
		if(animateVector3(matAnim->getCustomColorKeys(), matAnim->getCustomColorKeysNumber(), t, &customColor))
			material->setCustomColor(customColor);

		matAnim++;
	}
}


// skinning
void computeSkinning(BArmature * armature, BSkinData * skinData, const BVector3f * baseVertices, const BVector3f * baseNormals, const BVector3f * baseTangents, BVector3f * vertices, BVector3f * normals, BVector3f * tangents)
{
	BMatrix4x4 matrix;

	unsigned int p;
	unsigned int pSize = skinData->getPointsNumber();
	if(baseTangents && baseNormals)
	{
		for(p = 0; p < pSize; p++)
		{
			BSkinPoint * point = skinData->getPoint(p);
			const unsigned short * bonesIds = point->getBonesIds();
			const float * bonesWeights = point->getBonesWeights();
			
			unsigned int vertexId = point->getVertexId();
			unsigned int b, bSize = point->getBonesNumber();
			
			memset(matrix.entries, 0, sizeof(float)*16);
			
			for(b=0; b<bSize; b++)
			{
				BOBone * bone = armature->getBone(bonesIds[b]);
				blendMatrices(&matrix, bone->getSkinMatrix(), bonesWeights[b]);
			}
			
			vertices[vertexId] = matrix * baseVertices[vertexId];
			normals [vertexId] = matrix.getRotatedVector3(baseNormals[vertexId]);
			tangents[vertexId] = matrix.getRotatedVector3(baseTangents[vertexId]);
		}
	}
	else if(baseNormals)
	{
		for(p = 0; p < pSize; p++)
		{
			BSkinPoint * point = skinData->getPoint(p);
			const unsigned short * bonesIds = point->getBonesIds();
			const float * bonesWeights = point->getBonesWeights();
			
			unsigned int vertexId = point->getVertexId();
			unsigned int b, bSize = point->getBonesNumber();
			
			memset(matrix.entries, 0, sizeof(float)*16);
			
			for(b=0; b<bSize; b++)
			{
				BOBone * bone = armature->getBone(bonesIds[b]);
				blendMatrices(&matrix, bone->getSkinMatrix(), bonesWeights[b]);
			}
			
			vertices[vertexId] = matrix * baseVertices[vertexId];
			normals[vertexId] = matrix.getRotatedVector3(baseNormals[vertexId]);
		}
	}
	else
	{
		for(p = 0; p < pSize; p++)
		{
			BSkinPoint * point = skinData->getPoint(p);
			const unsigned short * bonesIds = point->getBonesIds();
			const float * bonesWeights = point->getBonesWeights();
			
			unsigned int vertexId = point->getVertexId();
			unsigned int b, bSize = point->getBonesNumber();
			
			memset(matrix.entries, 0, sizeof(float)*16);
			
			for(b=0; b<bSize; b++)
			{
				BOBone * bone = armature->getBone(bonesIds[b]);
				blendMatrices(&matrix, bone->getSkinMatrix(), bonesWeights[b]);
			}
			
			vertices[vertexId] = matrix * baseVertices[vertexId];
		}
	}
}


// simple raytracing
bool isRaytraced(const BVector3f & origin, const BVector3f & dest, const void * indices, U_TYPES indicesType, const BVector3f * vertices, unsigned int size)
{
	switch(indicesType)
	{
	case U_USHORT:
		{
			unsigned int v;
			unsigned short * idx = (unsigned short *)indices;
			for(v = 0; v < size; v += 3)
			{
				const BVector3f * v1 = &vertices[idx[v]];
				const BVector3f * v2 = &vertices[idx[v+1]];
				const BVector3f * v3 = &vertices[idx[v+2]];

				// make normal
				BVector3f normal = getTriangleNormal(*v1, *v2, *v3);

				// if ray intersection return true
				if(isEdgeTriangleIntersection(origin, dest, *v1, *v2, *v3, normal, NULL))
					return true;
			}
		}
		break;
            
	case U_UINT:
		{
			unsigned int v;
			unsigned int * idx = (unsigned int *)indices;
			for(v = 0; v < size; v += 3)
			{
				const BVector3f * v1 = &vertices[idx[v]];
				const BVector3f * v2 = &vertices[idx[v+1]];
				const BVector3f * v3 = &vertices[idx[v+2]];

				// make normal
				BVector3f normal = getTriangleNormal(*v1, *v2, *v3);

				// if ray intersection return true
				if(isEdgeTriangleIntersection(origin, dest, *v1, *v2, *v3, normal, NULL))
					return true;
			}
		}
            break;
            
        default:
            break;
	}

	return false;
}

bool getNearestRaytracedPosition(const BVector3f & origin, const BVector3f & dest, const void * indices, U_TYPES indicesType, const BVector3f * vertices, unsigned int size, BVector3f * intersection, bool invertNormal)
{
	bool isRaytraced = false;
	float dist;
	float nearDist;
	BVector3f I;
	BVector3f rayVector = dest - origin;

	// init near dist
	nearDist = rayVector.getSquaredLength();

	switch(indicesType)
	{
	case U_USHORT:
		{
			unsigned int v;
			unsigned short * idx = (unsigned short *)indices;
			for(v = 0; v < size; v += 3)
			{
				const BVector3f * v1 = &vertices[idx[v]];
				const BVector3f * v2 = &vertices[idx[v+1]];
				const BVector3f * v3 = &vertices[idx[v+2]];

				// make normal
				BVector3f normal = getTriangleNormal(*v1, *v2, *v3);
				
				bool intersect;
				if(invertNormal)
					intersect = isEdgeTriangleIntersection(origin, dest, *v3, *v2, *v1, -normal, &I);
				else
					intersect = isEdgeTriangleIntersection(origin, dest, *v1, *v2, *v3, normal, &I);

				if(intersect)
				{
					rayVector = I - origin;
					dist = rayVector.getSquaredLength();
					if(dist < nearDist)
					{
						nearDist = dist;
						(*intersection) = I;
					}
					isRaytraced = true;
				}
			}
		}
		break;
            
	case U_UINT:
		{
			unsigned int v;
			unsigned int * idx = (unsigned int *)indices;
			for(v = 0; v < size; v += 3)
			{
				const BVector3f * v1 = &vertices[idx[v]];
				const BVector3f * v2 = &vertices[idx[v+1]];
				const BVector3f * v3 = &vertices[idx[v+2]];

				// make normal
				BVector3f normal = getTriangleNormal(*v1, *v2, *v3);
				
				bool intersect;
				if(invertNormal)
					intersect = isEdgeTriangleIntersection(origin, dest, *v3, *v2, *v1, -normal, &I);
				else
					intersect = isEdgeTriangleIntersection(origin, dest, *v1, *v2, *v3, normal, &I);
				
				if(intersect)
				{
					rayVector = I - origin;
					dist = rayVector.getSquaredLength();
					if(dist < nearDist)
					{
						nearDist = dist;
						(*intersection) = I;
					}
					isRaytraced = true;
				}
			}
		}
            break;
            
        default:
            break;
	}
	return isRaytraced;
}


BVector3f computeTangent(
	const BVector3f & P1,  const BVector3f & P2,  const BVector3f & P3,
	const BVector2f & UV1, const BVector2f & UV2, const BVector2f & UV3)
{
	BVector3f Edge1 = P2 - P1;
	BVector3f Edge2 = P3 - P1;
	BVector2f Edge1uv = UV2 - UV1;
	BVector2f Edge2uv = UV3 - UV1;

	float cp = Edge1uv.y * Edge2uv.x - Edge1uv.x * Edge2uv.y;

	if(cp != 0.0f)
	{
		float mul = 1.0f / cp;
		BVector3f tangent = (Edge1 * -Edge2uv.y + Edge2 * Edge1uv.y) * mul;

		return tangent.getNormalized();
	}

	return BVector3f(0.0f, 0.0f, 0.0f);
}

void generateTangents(BSubMesh * subMesh)
{
	BVector3f * vertices = subMesh->getVertices();
	BVector3f * normals = subMesh->getNormals();
	BVector2f * texCoords = subMesh->getTexCoords();

	if(! (vertices && normals && texCoords))
		return;


	bool generate = false;
	unsigned int mapChannel;

	// find normal mapChannel
	unsigned int d;
	unsigned int dSize = subMesh->getDisplaysNumber();
	for(d=0; d<dSize; d++)
	{
		BDisplay * display = subMesh->getDisplay(d);
		BMaterial * material = display->getMaterial();
		if(material)
		{
			if(material->getType() == 1) // standard
			{
				if(material->getTexturesPassNumber() > 2)
				{
					BTexturePass * texturePass = material->getTexturePass(2); // Normal map pass
					if(texturePass)
					{
						mapChannel = texturePass->getMapChannel();
						generate = true;
					}
				}
			}
			else
			{
				unsigned tSize = material->getTexturesPassNumber();
				unsigned int t;
				for(t=0; t<tSize; t++)
				{
					BTexturePass * texturePass = material->getTexturePass(t);
					if(texturePass)
					{
						if(texturePass->getCombineMode() == M_TEX_COMBINE_DOT)
						{
							mapChannel = texturePass->getMapChannel();
							generate = true;
						}
					}
				}
			}
		}
	}

	// generate
	if(generate)
	{
		U_TYPES indicesType = subMesh->getIndicesType();
		void * indices = subMesh->getIndices();
		BVector3f * tangents = subMesh->allocTangents(subMesh->getNormalsSize());

		// texCoord offset
		unsigned int offset = 0;
		if(subMesh->isMapChannelExist(mapChannel))
			offset = subMesh->getMapChannelOffset(mapChannel);

		texCoords = texCoords + offset;

		// scan triangles to generate tangents from vertices and texCoords
		for(d=0; d<dSize; d++)
		{
			BDisplay * display = subMesh->getDisplay(d);

			if(display->getPrimitiveType() == U_PRIMITIVE_TRIANGLES)
			{
				unsigned int begin = display->getBegin();
				unsigned int size = display->getSize();

				if(! indices)
				{
					for(unsigned int i=begin; i<(begin+size); i+=3)
					{
						BVector3f * P1 = &vertices[i];
						BVector3f * P2 = &vertices[i+1];
						BVector3f * P3 = &vertices[i+2];

						BVector3f * N1 = &normals[i];
						BVector3f * N2 = &normals[i+1];
						BVector3f * N3 = &normals[i+2];

						BVector2f * UV1 = &texCoords[i];
						BVector2f * UV2 = &texCoords[i+1];
						BVector2f * UV3 = &texCoords[i+2];

						BVector3f tangent = computeTangent(*P1, *P2, *P3, *UV1, *UV2, *UV3);

						tangents[i]   = (tangent - ((*N1) * tangent.dotProduct(*N1))).getNormalized();
						tangents[i+1] = (tangent - ((*N2) * tangent.dotProduct(*N2))).getNormalized();
						tangents[i+2] = (tangent - ((*N3) * tangent.dotProduct(*N3))).getNormalized();
					}
				}
				else if(indicesType == U_USHORT)
				{
					unsigned short * _indices = (unsigned short *)indices;
					for(unsigned int i=begin; i<(begin+size); i+=3)
					{
						unsigned short A = _indices[i];
						unsigned short B = _indices[i+1];
						unsigned short C = _indices[i+2];

						BVector3f * P1 = &vertices[A];
						BVector3f * P2 = &vertices[B];
						BVector3f * P3 = &vertices[C];

						BVector3f * N1 = &normals[A];
						BVector3f * N2 = &normals[B];
						BVector3f * N3 = &normals[C];

						BVector2f * UV1 = &texCoords[A];
						BVector2f * UV2 = &texCoords[B];
						BVector2f * UV3 = &texCoords[C];

						BVector3f tangent = computeTangent(*P1, *P2, *P3, *UV1, *UV2, *UV3);

						tangents[A] = (tangent - ((*N1) * tangent.dotProduct(*N1))).getNormalized();
						tangents[B] = (tangent - ((*N2) * tangent.dotProduct(*N2))).getNormalized();
						tangents[C] = (tangent - ((*N3) * tangent.dotProduct(*N3))).getNormalized();
					}
				}
				else if(indicesType == U_UINT)
				{
					unsigned int * _indices = (unsigned int *)indices;
					for(unsigned int i=begin; i<(begin+size); i+=3)
					{
						unsigned int A = _indices[i];
						unsigned int B = _indices[i+1];
						unsigned int C = _indices[i+2];

						BVector3f * P1 = &vertices[A];
						BVector3f * P2 = &vertices[B];
						BVector3f * P3 = &vertices[C];

						BVector3f * N1 = &normals[A];
						BVector3f * N2 = &normals[B];
						BVector3f * N3 = &normals[C];

						BVector2f * UV1 = &texCoords[A];
						BVector2f * UV2 = &texCoords[B];
						BVector2f * UV3 = &texCoords[C];

						BVector3f tangent = computeTangent(*P1, *P2, *P3, *UV1, *UV2, *UV3);

						tangents[A] = (tangent - ((*N1) * tangent.dotProduct(*N1))).getNormalized();
						tangents[B] = (tangent - ((*N2) * tangent.dotProduct(*N2))).getNormalized();
						tangents[C] = (tangent - ((*N3) * tangent.dotProduct(*N3))).getNormalized();
					}
				}
			}
		}
	}
}