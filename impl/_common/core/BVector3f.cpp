/////////////////////////////////////////////////////////////////////////////////////////////////////////
// BCore
// BVector3f.cpp
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


#include <BCore.h>


BVector3f::BVector3f(const BVector4f & vec):	
x(vec.x), 
y(vec.y), 
z(vec.z)
{}

void BVector3f::normalize()
{
	float length = getLength();

	if(length == 1)
		return;

	else if(length == 0)
	{
		set(0, 0, 0);
		return;
	}

	float factor = 1.0f / length;
	x *= factor;
	y *= factor;
	z *= factor;
}

BVector3f BVector3f::getNormalized() const
{
	BVector3f result(*this);
	result.normalize();

	return result;
}

BVector3f BVector3f::getRotatedX(double angle) const
{
	if(angle == 0.0){
		return (*this);
	}

	float sinAngle = (float)sin(angle * DEG_TO_RAD);
	float cosAngle = (float)cos(angle * DEG_TO_RAD);

	return BVector3f(
		x,
		y * cosAngle - z * sinAngle,
		y * sinAngle + z * cosAngle
	);
}

void BVector3f::rotateX(double angle)
{
	(*this) = getRotatedX(angle);
}

BVector3f BVector3f::getRotatedY(double angle) const
{
	if(angle == 0.0){
		return (*this);
	}

	float sinAngle = (float)sin(angle * DEG_TO_RAD);
	float cosAngle = (float)cos(angle * DEG_TO_RAD);

	return BVector3f(
		x * cosAngle + z * sinAngle,
		y,
		-x * sinAngle + z * cosAngle
	);
}

void BVector3f::rotateY(double angle)
{
	(*this) = getRotatedY(angle);
}

BVector3f BVector3f::getRotatedZ(double angle) const
{
	if(angle == 0.0){
		return (*this);
	}

	float sinAngle = (float)sin(angle * DEG_TO_RAD);
	float cosAngle = (float)cos(angle * DEG_TO_RAD);
	
	return BVector3f(
		x * cosAngle - y * sinAngle,
		x * sinAngle + y * cosAngle,
		z
	);
}

void BVector3f::rotateZ(double angle)
{
	(*this) = getRotatedZ(angle);
}

BVector3f BVector3f::getRotatedAxis(double angle, const BVector3f & axis) const
{
	if(angle == 0.0){
		return (*this);
	}

	BVector3f u = axis.getNormalized();
	BVector3f rotMatrixRow0, rotMatrixRow1, rotMatrixRow2;

	float sinAngle = (float)sin(angle * DEG_TO_RAD);
	float cosAngle = (float)cos(angle * DEG_TO_RAD);
	float oneMinusCosAngle = 1.0f - cosAngle;

	rotMatrixRow0.x = (u.x)*(u.x) + cosAngle*(1-(u.x)*(u.x));
	rotMatrixRow0.y = (u.x)*(u.y)*(oneMinusCosAngle) - sinAngle*u.z;
	rotMatrixRow0.z = (u.x)*(u.z)*(oneMinusCosAngle) + sinAngle*u.y;

	rotMatrixRow1.x = (u.x)*(u.y)*(oneMinusCosAngle) + sinAngle*u.z;
	rotMatrixRow1.y = (u.y)*(u.y) + cosAngle*(1-(u.y)*(u.y));
	rotMatrixRow1.z = (u.y)*(u.z)*(oneMinusCosAngle) - sinAngle*u.x;
	
	rotMatrixRow2.x = (u.x)*(u.z)*(oneMinusCosAngle) - sinAngle*u.y;
	rotMatrixRow2.y = (u.y)*(u.z)*(oneMinusCosAngle) + sinAngle*u.x;
	rotMatrixRow2.z = (u.z)*(u.z) + cosAngle*(1-(u.z)*(u.z));

	return BVector3f(
		dotProduct(rotMatrixRow0),
		dotProduct(rotMatrixRow1),
		dotProduct(rotMatrixRow2)
	);
}

void BVector3f::rotateAxis(double angle, const BVector3f & axis)
{
	(*this) = getRotatedAxis(angle, axis);
}