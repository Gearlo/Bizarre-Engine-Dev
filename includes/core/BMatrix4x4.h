/////////////////////////////////////////////////////////////////////////////////////////////////////////
// BCore
// BMatrix4x4.h
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


#ifndef _M_MATRIX4X4_H
#define _M_MATRIX4X4_H


class M_CORE_EXPORT BMatrix4x4
{
public:

	float entries[16];

public:

	BMatrix4x4(void){	
		loadIdentity();
	}

	BMatrix4x4(	float e0,	float e1,	float e2,	float e3,
				float e4,	float e5,	float e6,	float e7,
				float e8,	float e9,	float e10,	float e11,
				float e12,	float e13,	float e14,	float e15);

	BMatrix4x4(const float * value);
	BMatrix4x4(const BMatrix4x4 & mat);

	~BMatrix4x4(void){}

public:

	BMatrix4x4 operator + (const BMatrix4x4 & mat) const;
	BMatrix4x4 operator - (const BMatrix4x4 & mat) const;
	BMatrix4x4 operator * (const BMatrix4x4 & mat) const;
	BMatrix4x4 operator * (const float value) const;
	BMatrix4x4 operator / (const float value) const;
	
	friend BMatrix4x4 operator * (float factor, const BMatrix4x4 & mat);

	void operator += (const BMatrix4x4 & mat);
	void operator -= (const BMatrix4x4 & mat);
	void operator *= (const BMatrix4x4 & mat);
	void operator *= (const float value);
	void operator /= (const float value);

	bool operator == (const BMatrix4x4 & mat) const;
	bool operator != (const BMatrix4x4 & mat) const;

	BMatrix4x4 operator - (void) const;
	BMatrix4x4 operator + (void) const 
	{
		return (*this);
	}

	BVector4f operator * (const BVector4f mat) const;
	inline BVector3f operator * (const BVector3f mat) const
	{
		return BVector3f(
		  entries[0]*mat.x
		+ entries[4]*mat.y
		+ entries[8]*mat.z
		+ entries[12],

		  entries[1]*mat.x
		+ entries[5]*mat.y
		+ entries[9]*mat.z
		+ entries[13],

		  entries[2]*mat.x
		+ entries[6]*mat.y
		+ entries[10]*mat.z
		+ entries[14]
		);
	}

	float & operator () (int col, int row){
		return entries[row*4+col];
	} 

	operator float* () const {
		return (float*) this;
	}

	operator const float* () const {
		return (const float*) this;
	}

public:

	void loadIdentity(void);
	void loadZero(void);

	void invert(void);
	void transpose(void);
	void affineInvert(void);
	void invertTranspose(void);
	void affineInvertTranspose(void);

	void scale(const BVector3f & scaleFactor);
	void rotate(const BVector3f & axis, const float angle);
	void translate(const BVector3f translate);

	void setEntry(int position, float value);
	void setScale(const BVector3f & scaleFactor);
	void setUniformScale(const float size);
	void setTranslation(const BVector3f & translation);
	void setTranslationPart(const BVector3f & translation);
	void setRotationAxis(const float angle, const BVector3f & axis);
	void setRotationX(const float angle);
	void setRotationY(const float angle);
	void setRotationZ(const float angle);
	void setRotationEuler(const float angleX, const float angleY, const float angleZ);
	void setRotationPartEuler(const float angleX, const float angleY, const float angleZ);
	void setRotationPartEuler(const BVector3f & rotations)
	{
		setRotationPartEuler(rotations.x, rotations.y, rotations.z);
	}

	float getEntry(int position) const;

	inline BVector3f getRotatedVector3(const BVector3f & vec) const
	{
		return BVector3f(
			entries[0]*vec.x + entries[4]*vec.y + entries[8]*vec.z,
			entries[1]*vec.x + entries[5]*vec.y + entries[9]*vec.z,
			entries[2]*vec.x + entries[6]*vec.y + entries[10]*vec.z
		);
	}
	
	BVector3f getInverseRotatedVector3(const BVector3f & vec) const;
	BVector3f getTranslatedVector3(const BVector3f & vec) const;
	BVector3f getInversetranslatedVector3(const BVector3f & vec) const;

	inline BVector3f getTranslationPart(void) const { return BVector3f(entries[12], entries[13], entries[14]); }

	BVector3f getEulerAngles(void) const;

	BVector3f getScale(void) const;
	
	BVector4f getRow(int position) const;
	BVector4f getColumn(int position) const;

	BMatrix4x4 getInverse(void) const;
	BMatrix4x4 getTranspose(void) const;
	BMatrix4x4 getInversetranspose(void) const;
	BMatrix4x4 getAffineInverse(void) const;
	BMatrix4x4 getAffineInverseTranspose(void) const;

	void rotateVector3(BVector3f & vec) const
	{
		vec = getRotatedVector3(vec);
	}

	void inverseRotateVector3(BVector3f & vec) const
	{
		vec = getInverseRotatedVector3(vec);
	}

	void translateVector3(BVector3f & vec) const
	{
		vec = getTranslatedVector3(vec);
	}

	void inversetranslateVector3(BVector3f & vec) const
	{
		vec = getInversetranslatedVector3(vec);
	}
};

#endif