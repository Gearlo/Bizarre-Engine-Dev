/////////////////////////////////////////////////////////////////////////////////////////////////////////
// BCore
// BVector4f.h
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


#ifndef _M_VECTOR4_H
#define _M_VECTOR4_H


class M_CORE_EXPORT BVector4f
{
public:

	float x;
	float y;
	float z;
	float w;

public:

	BVector4f(void):
		x(0.0f),
		y(0.0f),
		z(0.0f),
		w(0.0f)
	{}

	BVector4f(float newX, float newY, float newZ, float newW):
		x(newX),
		y(newY),
		z(newZ),
		w(newW)
	{}

	BVector4f(const float value):
		x(value),
		y(value),
		z(value),
		w(value)
	{}
	
	BVector4f(const float * values):
		x(*(values)),
		y(*(values + 1)),
		z(*(values + 2)),
		w(*(values + 3))
	{}

	BVector4f(const BVector4f & vec):
		x(vec.x),
		y(vec.y),
		z(vec.z),
		w(vec.w)
	{}

	BVector4f(const BVector3f & vec):
		x(vec.x),
		y(vec.y),
		z(vec.z),
		w(1.0f)
	{}

	BVector4f(const BColor & color);

public:

	BVector4f operator + (const BVector4f & vec) const
	{
		return BVector4f(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
	}

	BVector4f operator - (const BVector4f & vec) const
	{
		return BVector4f(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
	}

	BVector4f operator * (const float value) const
	{
		return BVector4f(x * value, y * value, z * value, w * value);
	}

	BVector4f operator / (const float value) const
	{
		if(value == 0.0f) return BVector4f(0.0f, 0.0f, 0.0f, 0.0f);
		return BVector4f(x / value, y / value, z / value, w / value);
	}

	friend BVector4f operator * (float factor, const BVector4f & vec)
	{
		return vec * factor;
	}

	bool operator == (const BVector4f & vec) const
	{
		if(x == vec.x && y == vec.y && z == vec.z && w == vec.w){
			return true;
		}

		return false;
	}

	bool operator != (const BVector4f & vec) const
	{
		return !((*this) == vec);
	}

	void operator += (const BVector4f & vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		w += vec.w;
	}

	void operator -= (const BVector4f & vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		w -= vec.w;
	}

	void operator *= (const float value)
	{
		x *= value;
		y *= value;
		z *= value;
		w *= value;
	}

	void operator /= (const float value)
	{
		if(value == 0.0f){
			return;
		}
		else
		{
			x /= value;
			y /= value;
			z /= value;
			w /= value;
		}
	}

	BVector4f operator - (void) const
	{
		return BVector4f(-x, -y, -z, -w);
	}

	BVector4f operator + (void) const
	{
		return (*this);
	}

	operator float* () const
	{
		return (float*) this;
	}

	operator const float* () const
	{
		return (const float*) this;
	}

	operator BVector3f();

public:

	void set(float newX, float newY, float newZ, float newW)
	{
		x = newX;
		y = newY;
		z = newZ;
		w = newW;
	}

	void loadIdentity(void)
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	}

	float dotProduct(const BVector4f & vec)
	{
		return x*vec.x + y*vec.y + z*vec.z + w*vec.w;
	}

	BVector4f lerp(const BVector4f & vec, float factor) const
	{
		return ((*this) * (1.0f - factor)) + (vec * factor);
	}
};

#endif
