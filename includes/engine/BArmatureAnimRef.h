/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bizarre
// BArmatureAnimRef.h
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


#ifndef _M_ARMATURE_ANIM_REF_H
#define _M_ARMATURE_ANIM_REF_H


// Armature Anim ref
class M_ENGINE_EXPORT BArmatureAnimRef : public BDataRef
{
private:

	// data
	BArmatureAnim * m_armatureAnim;

public:

	// constructor / destructor
	BArmatureAnimRef(BArmatureAnim * armatureAnim, const char * filename);
	~BArmatureAnimRef(void);

	// clear / destroy
	void clear(void);
	void destroy(void);

	// get new
	static BArmatureAnimRef * getNew(BArmatureAnim * armatureAnim, const char * filename);

public:
	//load
	inline bool isLoaded(void){ return m_armatureAnim; }

	// update
	void update(void);

	// type
	int getType(void){ return U_REF_ARMATURE_ANIM; }

	// get data
	inline BArmatureAnim * getArmatureAnim(void){ return m_armatureAnim; }
};

#endif