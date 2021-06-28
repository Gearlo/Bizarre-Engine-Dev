/////////////////////////////////////////////////////////////////////////////////////////////////////////
// BCore
// BMaths.h
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


#ifndef _M_MATHS_H
#define _M_MATHS_H

#include <math.h>


// PI
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define QUASIZERO 0.00001f


// Degree/Radian conversions
#define DEG_TO_RAD ((M_PI * 2) / 360.0)
#define RAD_TO_DEG (1.0 / DEG_TO_RAD)

// MIN
#ifndef MIN
#define MIN(a, b)  (((a) < (b)) ? (a) : (b))
#endif

// MAX
#ifndef MAX
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))
#endif

// CLAMP
#ifndef CLAMP
#define CLAMP(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))
#endif

// ABS
#ifndef ABS
#define ABS(a)  (((a) < 0) ? -(a) : (a))
#endif

// Power of two
#define isPowerOfTwo(x)	(((x&(x - 1)) == 0) && (x != 0))
M_CORE_EXPORT unsigned int getNextPowerOfTwo(unsigned int x);

// loop
M_CORE_EXPORT float loopFloat(float val, float min, float max);


// structs
struct M_CORE_EXPORT BRange
{
	int start;
	int end;
};


// classes
class BVector2f;
class BVector3f;
class BVector4f;
class BColor;
class BMatrix4x4;
class BQuaternion;


// functions
M_CORE_EXPORT void sortFloatList(int indexList[], float floatList[], int start, int end);
M_CORE_EXPORT void sortFloatList(float floatList[], int start, int end);
M_CORE_EXPORT bool isBoxToBoxCollision(const BVector3f & minA, const BVector3f & maxA, const BVector3f & minB, const BVector3f & maxB);
M_CORE_EXPORT bool isBoxToBox2dCollision(const BVector2f & minA, const BVector2f & maxA, const BVector2f & minB, const BVector2f & maxB);
M_CORE_EXPORT bool isPointInBox(const BVector3f & point, const BVector3f & min, const BVector3f & max);
M_CORE_EXPORT bool isPointInBox2d(const BVector2f & point, const BVector2f & min, const BVector2f & max);
M_CORE_EXPORT bool isEdgeToBoxCollision(const BVector3f & origin, const BVector3f & dest, const BVector3f & min, const BVector3f & max);
M_CORE_EXPORT bool isEdgeToEdge2dIntersection(const BVector2f & A, const BVector2f & B, const BVector2f & C, const BVector2f & D, BVector2f * I);
M_CORE_EXPORT bool isPointInTriangle(const BVector3f & point, const BVector3f & a, const BVector3f & b, const BVector3f & c, const BVector3f & normal);
M_CORE_EXPORT bool isLineCircleIntersection(const BVector2f & origin, const BVector2f & dest, const BVector2f & circleCenter, float circleRadius);
M_CORE_EXPORT bool isRaySphereIntersection(const BVector3f & origin, const BVector3f & direction, const BVector3f & sphereCenter, float sphereRadius, BVector3f * point);
M_CORE_EXPORT bool isRayPlaneIntersection(const BVector3f & origin, const BVector3f & direction, const BVector3f & planePoint, const BVector3f & planeNormal, BVector3f * point);
M_CORE_EXPORT bool isEdgePlaneIntersection(const BVector3f & origin, const BVector3f & dest, const BVector3f & planePoint, const BVector3f & normal, BVector3f * point);
M_CORE_EXPORT bool isEdgeTriangleIntersection(const BVector3f & origin, const BVector3f & dest, const BVector3f & a, const BVector3f & b, const BVector3f & c, const BVector3f & normal, BVector3f * point);

M_CORE_EXPORT BVector3f getTriangleNormal(const BVector3f & a, const BVector3f & b, const BVector3f & c);

M_CORE_EXPORT void simplifyDP(float tol, BVector3f * v, int j, int k, int * mk);

M_CORE_EXPORT float linearInterpolation(float y1, float y2, float mu);
M_CORE_EXPORT float cubicInterpolation(float y0, float y1, float y2, float y3, float mu);
M_CORE_EXPORT float CatmullRomInterpolation(float y0, float y1, float y2, float y3, float mu);
M_CORE_EXPORT float HermiteInterpolation(float y0, float y1, float y2, float y3, float mu, float tension, float bias, bool begin = false, bool end = false);

// color convertions
M_CORE_EXPORT float HueToRGB(float v1, float v2, float vH);
M_CORE_EXPORT BVector3f RGBToHSV(BVector3f rgbColor);
M_CORE_EXPORT BVector3f HSVToRGB(BVector3f HSVColor);
M_CORE_EXPORT BVector3f RGBToHSL(BVector3f rgbColor);
M_CORE_EXPORT BVector3f HSLToRGB(BVector3f hslColor);






// include classes
#include "BVector2f.h"
#include "BVector3f.h"
#include "BVector4f.h"
#include "BColor.h"
#include "BMatrix4x4.h"
#include "BQuaternion.h"

#endif