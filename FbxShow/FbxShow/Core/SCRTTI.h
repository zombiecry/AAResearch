#ifndef SCRTTI_H
#define SCRTTI_H
#include "SCIMemberBase.h"
#include <vector>
#include <string>
using namespace std;

namespace sc{
	typedef std::vector <IMemberBase *> scMemberList;
	//the rtti information class
	class CRTTI{
	public:
		CRTTI();
		CRTTI(const char *className,CRTTI *baseClassRTTI);
		~CRTTI(){
			for (size_t i=0;i<m_members.size();i++){
				delete m_members[i];
			}
		}
		string GetClassName() const{
			return m_className;
		}
		const CRTTI *GetParentRTTI() const{
			return m_baseRTTI;
		}
		const scMemberList &GetMembers() const{
			return m_members;
		}
	public:
		static void PushBackMember(scMemberList &memberList,IMemberBase *member){
			memberList.push_back(member);
		}
	public:
		string			  m_className;
		const CRTTI		 *m_baseRTTI;
		scMemberList	  m_members;
	};
	///////////////////////

}
#endif