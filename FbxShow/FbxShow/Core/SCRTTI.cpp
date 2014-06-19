#include "SCRTTI.h"
#include <iostream>
using namespace std;
//the rtti information class
namespace sc{
	CRTTI::CRTTI(){
		m_baseRTTI=NULL;
	}
	CRTTI::CRTTI(const char *className,CRTTI *baseClassRTTI)
	{
		m_className=string(className);
		m_baseRTTI=baseClassRTTI;
	}
}
////////////////////////////////////////////////////////////