/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bizarre
// BMeshTools.h
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


#ifndef _B_MESH_TOOLS_H
#define _B_MESH_TOOLS_H



M_ENGINE_EXPORT bool animateFloat(BKey * keys, unsigned int keysNumber, float t, float * value);
M_ENGINE_EXPORT bool animateVector2(BKey * keys, unsigned int keysNumber, float t, BVector2f * vector2);
M_ENGINE_EXPORT bool animateVector3(BKey * keys, unsigned int keysNumber, float t, BVector3f * vector3);
M_ENGINE_EXPORT bool animateQuaternion(BKey * keys, unsigned int keysNumber, float t, BQuaternion * quaternion);

M_ENGINE_EXPORT void animateArmature(
	BArmature * armature,
	BArmatureAnim * armatureAnim,
	float t
	);

M_ENGINE_EXPORT void animateTextures(
	BMesh * mesh,
	BTexturesAnim * texturesAnim,
	float t
	);

M_ENGINE_EXPORT void animateMaterials(
	BMesh * mesh,
	BMaterialsAnim * materialsAnim,
	float t
	);

M_ENGINE_EXPORT void computeSkinning(
	BArmature * armature,
	BSkinData * skinData,
	const BVector3f * baseVertices,
	const BVector3f * baseNormals,
	const BVector3f * baseTangents,
	BVector3f * vertices,
	BVector3f * normals,
	BVector3f * tangents
	);

M_ENGINE_EXPORT bool isRaytraced(
	const BVector3f & origin,
	const BVector3f & dest, 
	const void * indices, 
	U_TYPES indicesType,
	const BVector3f * vertices, 
	unsigned int size
	);

M_ENGINE_EXPORT bool getNearestRaytracedPosition(
	const BVector3f & origin, 
	const BVector3f & dest, 
	const void * indices, 
	U_TYPES indicesType,
	const BVector3f * vertices, 
	unsigned int size, 
	BVector3f * intersection,
	bool invertNormal = false
	);

M_ENGINE_EXPORT BVector3f computeTangent(
	const BVector3f & P1,  const BVector3f & P2,  const BVector3f & P3,
	const BVector2f & UV1, const BVector2f & UV2, const BVector2f & UV3);

class BSubMesh;
M_ENGINE_EXPORT void generateTangents(BSubMesh * subMesh);
#endif