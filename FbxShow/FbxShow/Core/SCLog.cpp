#include "SCLog.h"
#include <stdarg.h>	
#include <stdio.h>
namespace sc{
	DEFINE_SINGLETON(CLog)
	CLog::CLog():m_kFout("SCFluid.log",ios::trunc) {
	}
	CLog::~CLog() {
		m_kFout.close();
	}

	void CLog::Say(const char *pcStr, ...) {
		char		acStr[256];
		va_list		kAp;				
		if (pcStr == NULL) {					
			return;	
		}
		va_start(kAp, pcStr);		
		vsprintf_s(acStr, pcStr, kAp);
		va_end(kAp);
		string sStr(acStr);
		m_kFout<<acStr;
		m_kFout.flush();
	}

	void CLog::Say(const string str) {
		m_kFout<<str;
	}
	ofstream &CLog::GetOStream(){
		return GetInstance()->m_kFout;
	}
};