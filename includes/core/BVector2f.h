/////////////////////////////////////////////////////////////////////////////////////////////////////////
// BCore
// BVector2f.h
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


#ifndef _M_VECTOR2_H
#define _M_VECTOR2_H


class M_CORE_EXPORT BVector2f
{
public:

	float x;
	float y;

public:

	BVector2f(void):
		x(0.0f), 
		y(0.0f)
	{}

	BVector2f(float newX, float newY):
		x(newX), 
		y(newY)
	{}

	BVector2f(const float value):
		x(value), 
		y(value)
	{}

	BVector2f(const float * values):
		x((*values)), 
		y((*values)+1)
	{}

	BVector2f(const BVector2f & vec):
		x(vec.x), 
		y(vec.y)
	{}

	BVector2f(const BVector3f & vec);

public:

	inline BVector2f operator + (const float value) const
	{	
		return BVector2f(x + value, y + value);
	}

	inline BVector2f operator - (const float value) const
	{	
		return BVector2f(x - value, y - value);
	}

	inline BVector2f operator + (const BVector2f & vec) const
	{	
		return BVector2f(x + vec.x, y + vec.y);
	}

	inline BVector2f operator - (const BVector2f & vec) const
	{	
		return BVector2f(x - vec.x, y - vec.y);
	}

	inline BVector2f operator * (const float value) const
	{	
		return BVector2f(x * value, y * value);
	}
	
	inline BVector2f operator * (const BVector2f & vec) const
	{	
		return BVector2f(x * vec.x, y * vec.y);
	}

	inline BVector2f operator / (const BVector2f & vec) const
	{	
		return BVector2f(x / vec.x, y / vec.y);
	}

	inline BVector2f operator / (const float value) const
	{	
		if(value == 0.0f) return BVector2f(0.0f, 0.0f);
		return BVector2f(x / value, y / value);
	}

	friend inline BVector2f operator * (float factor, const BVector2f & vec) 
	{
		return vec * factor;
	}

	inline bool operator == (const BVector2f & vec) const
	{
		if(x == vec.x && y == vec.y){
			return true;
		}

		return false;
	}

	inline void operator = (const float value)
	{	
		x = value;	
		y = value;	
	}

	inline bool operator != (const BVector2f & vec) const
	{	
		return !((*this) == vec);
	}

	inline void operator += (const BVector2f & vec) 
	{	
		x += vec.x;
		y += vec.y;
	}

	inline void operator -= (const BVector2f & vec)
	{	
		x -= vec.x;	
		y -= vec.y;
	}

	inline void operator *= (const BVector2f & vec) 
	{	
		x *= vec.x;	
		y *= vec.y;
	}

	inline void operator /= (const BVector2f & vec) 
	{	
		x /= vec.x;	
		y /= vec.y;
	}

	inline void operator *= (const float value) 
	{	
		x *= value;	
		y *= value;
	}

	inline void operator /= (const float value) 
	{	
		if(value == 0.0f){
			x = 0.0f;
			y = 0.0f;
		}
		else
		{	
			x /= value; 
			y /= value;
		}
	}

	inline BVector2f operator - (void) const 
	{
		return BVector2f(-x, -y);
	}

	inline BVector2f operator + (void) const 
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

	inline void set(float newX, float newY)
	{	
		x = newX;	
		y = newY;
	}
	
	inline void loadIdentity(void)
	{
		x = 0.0f;
		y = 0.0f;
	}
	
	void normalize();
	void rotate(const float angle);	

	BVector2f getNormalized() const;
	BVector2f getRotated(const float angle) const;	

	// return angle that vec needs to rotate
	inline float getAngleBetween(const BVector2f & vec)
	{
		float angle = (float)((atan2(y, x) - atan2(vec.y, vec.x))*RAD_TO_DEG);
		
		if(angle > 180)
			angle -= 360;
		if(angle < -180)
			angle += 360;
		
		return angle;
	}

	inline float getLength() const
	{	
		return sqrtf((x*x) + (y*y));
	}

	inline float getSquaredLength() const
	{	
		return ((x*x) + (y*y));
	}

	inline float crossProduct(const BVector2f & vec) const
	{
		return x*vec.y - y*vec.x;
	}
	
	inline float dotProduct(const BVector2f & vec) const
	{	
		return (x*vec.x) + (y*vec.y);
	}

	inline BVector2f lerp(const BVector2f & vec, float factor) const
	{	
		return ((*this) * (1.0f - factor)) + (vec * factor);
	}
};

#endif