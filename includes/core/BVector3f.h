/////////////////////////////////////////////////////////////////////////////////////////////////////////
// BCore
// BVector3f.h
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


#ifndef _M_VECTOR3_H
#define _M_VECTOR3_H


class M_CORE_EXPORT BVector3f
{
public:

	float x;
	float y;
	float z;

public:

	BVector3f(void):	
		x(0.0f), 
		y(0.0f), 
		z(0.0f)
	{}

	BVector3f(float newX, float newY, float newZ):	
		x(newX), 
		y(newY), 
		z(newZ)
	{}

	BVector3f(const float value):	
		x(value), 
		y(value), 
		z(value)
	{}

	BVector3f(const float * values):	
		x(*(values)), 
		y(*(values+1)), 
		z(*(values+2))
	{}

	BVector3f(const BVector3f & vec):	
		x(vec.x), 
		y(vec.y), 
		z(vec.z)
	{}

	BVector3f(const BVector4f & vec);
	
	BVector3f(const BVector2f & vec):	
		x(vec.x), 
		y(vec.y), 
		z(0)
	{}

public:

	inline BVector3f operator + (const BVector3f & vec) const
	{	
		return BVector3f(x + vec.x, y + vec.y, z + vec.z);
	}
	
	inline BVector3f operator - (const BVector3f & vec) const
	{	
		return BVector3f(x - vec.x, y - vec.y, z - vec.z);
	}

	inline BVector3f operator + (const float & value) const
	{	
		return BVector3f(x + value, y + value, z + value);
	}

	inline BVector3f operator - (const float & value) const
	{	
		return BVector3f(x - value, y - value, z - value);
	}

	inline BVector3f operator * (const float value) const
	{	
		return BVector3f(x * value, y * value, z * value);
	}

	inline BVector3f operator * (const BVector3f & vec) const
	{	
		return BVector3f(x * vec.x, y * vec.y, z * vec.z);
	}

	inline BVector3f operator / (const BVector3f & vec) const
	{	
		return BVector3f(x / vec.x, y / vec.y, z / vec.z);
	}
	
	inline BVector3f operator / (const float value) const
	{	
		if(value == 0) return BVector3f(0.0f, 0.0f, 0.0f);
		float i = 1.0f / value;
		return BVector3f(x*i, y*i, z*i);
	}

	friend inline BVector3f operator * (float factor, const BVector3f & vec)
	{
		return vec * factor;
	}

	inline bool operator == (const BVector3f & vec) const
	{
		if(x == vec.x && y == vec.y && z == vec.z)
			return true;

		return false;
	}

	inline bool operator != (const BVector3f & vec) const
	{	
		return !((*this) == vec);
	}

	inline void operator += (const BVector3f & vec)
	{	
		x += vec.x;
		y += vec.y;	
		z += vec.z;
	}

	inline void operator -= (const BVector3f & vec)
	{	
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
	}

	inline void operator *= (const float value)
	{	
		x *= value;	
		y *= value;	
		z *= value;	
	}

	inline void operator = (const float value)
	{	
		x = value;	
		y = value;	
		z = value;	
	}
	
	inline void operator /= (const float value)
	{	
		if(value == 0.0f)
			return;

		float i = 1.0f / value;
		x *= i; 
		y *= i; 
		z *= i;	
	}

	inline BVector3f operator - (void) const
	{
		return BVector3f(-x, -y, -z);
	}

	inline BVector3f operator + (void) const 
	{
		return *this;
	}

	inline operator float* () const 
	{
		return (float*) this;
	}

	inline operator const float* () const 
	{
		return (const float*) this;
	}

public:

	inline void set(const float newX, const float newY, const float newZ)
	{	
		x = newX;	
		y = newY;	
		z = newZ;
	}

	inline void loadIdentity(void)
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	
	inline BVector3f crossProduct(const BVector3f & vec) const
	{	
		return BVector3f((y*vec.z) - (z*vec.y), (z*vec.x) - (x*vec.z), (x*vec.y) - (y*vec.x));
	}

	inline float dotProduct(const BVector3f & vec) const
	{	
		return (x*vec.x) + (y*vec.y) + (z*vec.z);
	}
	
	void normalize();

	BVector3f getNormalized() const;

	inline float getLength() const
	{	
		return sqrtf((x*x) + (y*y) + (z*z));
	}
	
	inline float getSquaredLength() const
	{	
		return (x*x) + (y*y) + (z*z);
	}

	void rotateX(double angle);
	void rotateY(double angle);
	void rotateZ(double angle);
	void rotateAxis(double angle, const BVector3f & axis);

	BVector3f getRotatedX(double angle) const;
	BVector3f getRotatedY(double angle) const;
	BVector3f getRotatedZ(double angle) const;
	BVector3f getRotatedAxis(double angle, const BVector3f & axis) const;

	inline BVector3f lerp(const BVector3f & vec, float factor) const
	{	
		return ((*this) * (1.0f - factor)) + (vec * factor);
	}
};

#endif