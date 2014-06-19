#pragma once
#include "DXUT.h"
#include "Core/SCBaseObject.h"
#include "Core/SCSingleton.h"
namespace sc{
	struct CVec3:public CBaseObject{
		DECLARE_BASE_OBJECT(CVec3,CBaseObject)
		float x;
		float y;
		float z;
	};


}  
