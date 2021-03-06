/////////////////////////////////////////////////////////////////////////////////////////////////////////
// BCore
// BCore.h
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


#ifndef _M_CORE_H
#define _M_CORE_H

#ifdef WIN32

	#ifdef _MSC_VER
		#pragma warning(disable: 4251)
	#endif

	// M_CORE_EXPORT
/*	#if defined(MCORE_DLL)
		#define M_CORE_EXPORT __declspec( dllexport )
	#elif defined(MCORE_STATIC)
		#define M_CORE_EXPORT
	#else
		#define M_CORE_EXPORT __declspec( dllimport )
	#endif
*/

#define M_CORE_EXPORT

#else

	// M_CORE_EXPORT
	#define M_CORE_EXPORT

#endif


class BImage;
class BSound;

#include "BUtils.h"
#include "BString.h"
#include "BFile.h"
#include "BStdFile.h"
#include "BFileTools.h"
#include "BMaths.h"
#include "BSystemContext.h"
#include "BInputContext.h"
#include "BRenderInfo.h"
#include "BRenderingContext.h"
#include "BSoundContext.h"
#include "BPhysicsContext.h"
#include "BScriptContext.h"
#include "BThreadingContext.h"
#include "BImage.h"
#include "BSound.h"
#include "BStringTools.h"
#include "BDataManager.h"
#include "BDataLoader.h"
#include "BList.h"
#include "BTimer.h"

#endif