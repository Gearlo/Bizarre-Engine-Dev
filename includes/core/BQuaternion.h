/////////////////////////////////////////////////////////////////////////////////////////////////////////
// BCore
// BQuaternion.h
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


#ifndef _M_QUATERNION_H
#define _M_QUATERNION_H


class M_CORE_EXPORT BQuaternion
{
public:

	float values[4];

public:

	BQuaternion(void)
	{
		loadIdentity();
	}

	BQuaternion(float val0, float val1, float val2, float val3)
	{
		values[0] = val0;
		values[1] = val1;
		values[2] = val2;
		values[3] = val3;
	}

	BQuaternion(float angle, const BVector3f & axis)
	{
		setFromAngleAxis(angle, axis);
	}

	BQuaternion(float xAngle, float yAngle, float zAngle)
	{
		setFromAngles(xAngle, yAngle, zAngle);
	}

	BQuaternion(const BQuaternion & q1, BQuaternion q2, float interpolation)
	{
		slerp(q1, q2, interpolation);
	}

public:

	BQuaternion operator * (const BQuaternion & quat) const;

	void operator *= (const BQuaternion & quat);

	BQuaternion operator - (void) const
	{
		return BQuaternion(-values[0], -values[1], -values[2], -values[3]);
	}

	inline bool operator == (const BQuaternion & quat) const
	{
		if(values[0] == quat.values[0] && 
		   values[1] == quat.values[1] &&
		   values[2] == quat.values[2] &&
		   values[3] == quat.values[3])
			return true;

		return false;
	}

	inline bool operator != (const BQuaternion & quat) const
	{	
		return !((*this) == quat);
	}

public:

	void normalize(void);
	void loadIdentity(void);
	void setFromAngles(float xAngle, float yAngle, float zAngle);
	void slerp(const BQuaternion & q1, const BQuaternion & q2, float interpolation);
	void invert(void);
	void setFromAngleAxis(float angle, const BVector3f & axis);
	void setFromVectors(const BVector3f & source, const BVector3f & destination);

	BVector3f getEulerAngles(void) const;

	float getAngle(void) const;
	BVector3f getAxis(void) const;
};

#endif