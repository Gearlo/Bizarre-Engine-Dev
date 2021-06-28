/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bizarre
// BObject3d.h
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


#ifndef _B_OBJECT3D_H
#define _B_OBJECT3D_H


class M_ENGINE_EXPORT BObject3d
{
public:

	// constructor
	BObject3d(void);

	// destructor
	virtual ~BObject3d(void);

	// copy constructor
	BObject3d(const BObject3d & object);
	
protected:

	// name
	BString m_name;

	// transform
	BVector3f   m_position;
	BVector3f   m_scale;
	BQuaternion m_rotation;

	// matrices
	BMatrix4x4 m_matrix;

	// childs
	vector <BObject3d *> m_childs;

	// properties
	bool m_isActive;
	bool m_isVisible;
	bool m_needToUpdate;

	// linking
	BObject3d * m_parent;

	// behaviors
	vector <BBehavior *> m_behaviors; // eliminacion planeada

private:

	void removeChild(BObject3d * child);

protected:
	
	void clearObject3d(void);

public:
	virtual void load(void){ std::cout << "base load" << std::endl; }
	virtual inline bool isLoaded(void){ return true; }

public:

	// matrices
	void updateMatrix(void);
	void computeLocalMatrix(void);
	inline BMatrix4x4 *	getMatrix(void){ return &m_matrix; }

	// childs
	void unlinkChilds(void);
	void computeChildsMatrices(void);

	// transform
	BVector3f getUniformRotatedVector(const BVector3f & vector);
	inline BVector3f	getInverseRotatedVector(const BVector3f & vector) const	{ return m_matrix.getInverseRotatedVector3(vector); }
	inline BVector3f	getRotatedVector(const BVector3f & vector) const			{ return m_matrix.getRotatedVector3(vector); }
	inline BVector3f	getInversePosition(const BVector3f & position) const		{ return m_matrix.getInverse() * position; }
	inline BVector3f	getTransformedVector(const BVector3f & vector) const		{ return m_matrix * vector; }

	// position
	virtual void setPosition(const BVector3f & position);
	inline BVector3f	getTransformedPosition(void) const { return BVector3f(m_matrix.entries[12], m_matrix.entries[13], m_matrix.entries[14]); }
	inline BVector3f getPosition(void) const { return m_position; }

	// rotation
	virtual void setEulerRotation(const BVector3f & euler);
	void setAxisAngleRotation(const BVector3f & axis, float angle);
	void addAxisAngleRotation(const BVector3f & axis, float angle);
	void setRotation(const BQuaternion & rotation);
	inline BVector3f	getTransformedRotation(void) const { return m_matrix.getEulerAngles(); }
	inline BVector3f getEulerRotation(void) const { return m_rotation.getEulerAngles(); }
	inline BQuaternion getRotation(void) const { return m_rotation; }

	// scale
	void setScale(const BVector3f & scale);
	inline BVector3f getTransformedScale(void) const { return m_matrix.getScale(); }
	inline BVector3f getScale(void) const { return m_scale; }
	
	// linking
	void linkTo(BObject3d * parent);
	void unLink(void);
	inline void setParent(BObject3d * object){ m_parent = object; }
	inline void addChild(BObject3d * child){ m_childs.push_back(child); }
	inline bool hasParent(void){ return (m_parent != NULL); }
	inline unsigned int getChildsNumber(void){ return m_childs.size(); }
	inline BObject3d * getParent(void){ return m_parent; }
	inline BObject3d * getChild(unsigned int id){ return m_childs[id]; }

	// behaviors
	void updateBehaviors(void);
	void drawBehaviors(void);
	void deleteBehavior(unsigned int id);
	void invertBehavior(unsigned int idA, unsigned int idB);
	void changeBehavior(unsigned int id, BBehavior * behavior);
	inline void addBehavior(BBehavior * behavior){ m_behaviors.push_back(behavior); }
	inline unsigned int getBehaviorsNumber(void){ return m_behaviors.size(); }
	inline BBehavior * getBehavior(unsigned int id){ return m_behaviors[id]; }

	// need to update
	inline bool needToUpdate(void){ return m_needToUpdate; }

	// active
	virtual void setActive(bool active){ m_isActive = active; }
	inline bool isActive(void){ return m_isActive; }

	// visibility
	inline void setVisible(bool visible){ m_isVisible = visible; }
	inline bool isVisible(void){ return m_isVisible; }
	virtual void updateVisibility(BOCamera * camera){}

	// name
	void setName(const char * name);
	inline const char * getName(void){ return m_name.getSafeString(); }

	// type
	virtual int getType(void){ return U_OBJECT3D; }

	// update
	virtual void update(void);
};

#endif