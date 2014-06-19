#include "stdafx.h"

namespace sc{
	BEGIN_PROPERTIES_DESCRIPTION(CVec3)
		REGISTER_MEMBER("x",x,MemberDescriptionType_Persistence)
		REGISTER_MEMBER("y",y,MemberDescriptionType_Persistence)
		REGISTER_MEMBER("z",z,MemberDescriptionType_Persistence)
	END_PROPERTIES_DESCRIPTION()
}