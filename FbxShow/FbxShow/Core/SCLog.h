#ifndef SCLOG_H
#define SCLOG_H
#include <fstream>
#include <string>
using namespace std;
#include "SCSingleton.h"
namespace sc{
#undef SCSAY
#undef SC_LOG_ASSERT


#define DEBUG_MODE 1

#if	DEBUG_MODE
#define SCSAY(...) \
	CLog::GetInstance()->Say(__VA_ARGS__);
#define SCSAYD(...)					\
	{								\
	SCSAY("In ");					\
	SCSAY("\"%s\" ",__FILE__);		\
	SCSAY("%s ",__FUNCTION__);		\
	SCSAY(" (%d) :\n",__LINE__);	\
	SCSAY(__VA_ARGS__);				\
	SCSAY("\n");					\
    }

#define SCASSERT(x)                 \
	if (!x){						\
	SCSAY("Assert failed In ");		\
	SCSAY("\"%s\" ",__FILE__);		\
	SCSAY("%s ",__FUNCTION__);		\
	SCSAY(" (%d) :\n",__LINE__);	\
	SCSAY(#x);						\
	SCSAY("\n");					\
    }

#else
#define SCSAY(...) 
#define SCSAYD(...)
#define SCASSERT(x)
#endif
	class CLog{
		DECLARE_SINGLETON(CLog)
	public:
		CLog() ;
		~CLog() ;
		void Say(const char *pcStr, ...);
		void Say(const string str);
		static ofstream &GetOStream();
	private:
		ofstream m_kFout;
	};
}
#endif