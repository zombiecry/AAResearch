#ifndef SCBASEOBJECT_H
#define SCBASEOBJECT_H
#include "SCRTTI.h"
#include "SCVirtualMember.h"
#include "SCEnumMember.h"
#include <iostream>
using namespace std;
namespace sc{
	//all classes wanna to impl reflection must public inherentance this class
	//for multi-inhe this class must be put as the first father
	//since there's will be (CBaseObject *)<--(char *) conversion for the member class.
	class CBaseObject{
	public:
		static  const CRTTI *GetClassRTTI(){
			return &ms_rtti;
		}
		virtual const CRTTI *GetRTTI() const{
			return &ms_rtti;
		}
		
		template <class MemberType>
		const MemberType &GetMember(const IMemberBase *member)const{
			return *((MemberType *)member->Get(this));
		}
		template <class MemberType>
		MemberType &GetMember(const IMemberBase *member){
			return *((MemberType *)member->Get(this));
		}
		template <class MemberType>
		void SetMember(const IMemberBase *member,const MemberType &value){
			member->Set(this,(const char *)(&value));
		}
		void			SaveToXML(const char *fileName) const;
		void			LoadFromXML(const char *fileName);
		void			SaveAsMember(TiXmlNode *xmlNode,const char *memberName) const;
		void			LoadAsMember(const TiXmlNode *xmlNode,const char *memberName);
		void			Save(const CRTTI *rtti,TiXmlNode *xmlNode)const;
		void			Load(const CRTTI *rtti,TiXmlNode *xmlNode);
	public:
		static CRTTI ms_rtti;
	};

#define DECLARE_BASE_OBJECT(className,parentClassName)							\
private:																		\
	static CRTTI ms_rtti;														\
	static bool   ms_initialized;												\
	static void   className::InitRTTI(){										\
		ms_rtti.m_className=#className;											\
		ms_rtti.m_baseRTTI=parentClassName::GetClassRTTI();						\
		RegisterMembers();														\
	}																			\
	static void RegisterMembers();												\
public:																			\
	static const CRTTI *GetClassRTTI();											\
	virtual const CRTTI *GetRTTI() const;													

#define BEGIN_PROPERTIES_DESCRIPTION(className)									\
	bool   className::ms_initialized(false);									\
	CRTTI  className::ms_rtti;													\
	const CRTTI *className::GetRTTI() const{									\
		if (!ms_initialized){													\
			InitRTTI();															\
		}																		\
		ms_initialized=true;													\
		return &ms_rtti;														\
	}																			\
	const CRTTI *className::GetClassRTTI(){										\
		if (!ms_initialized){													\
			InitRTTI();															\
		}																		\
		ms_initialized=true;													\
		return &ms_rtti;														\
	}																			\
	void className::RegisterMembers(){											\
		scMemberList &memberList=ms_rtti.m_members;								\
		typedef className objectType;

#define TEMPLATE1_CLASS_DECLARE(t)	\
	class t
#define TEMPLATE2_CLASS_DECLARE(t1,t2)	\
	TEMPLATE1_CLASS_DECLARE(t1),class t2

#define TEMPLATE3_CLASS_DECLARE(t1,t2,t3)	\
	TEMPLATE2_CLASS_DECLARE(t1,t2),class t3

#define TEMPLATE4_CLASS_DECLARE(t1,t2,t3,t4)	\
	TEMPLATE3_CLASS_DECLARE(t1,t2,t3),class t4

#define TEMPLATE5_CLASS_DECLARE(t1,t2,t3,t4,t5)	\
	TEMPLATE4_CLASS_DECLARE(t1,t2,t3,t4),class t5

#define TEMPLATE6_CLASS_DECLARE(t1,t2,t3,t4,t5,t6)	\
	TEMPLATE5_CLASS_DECLARE(t1,t2,t3,t4,t5),class t6

#define TEMPLATE_PARAM(...)			\
	__VA_ARGS__



#define BEGIN_TEMPLATE1_PROPERTIES_DESCRIPTION(className,...)					\
	BEGIN_TEMPLATE_PROPERTIES_DESCRIPTION_(className,TEMPLATE1_CLASS_DECLARE(__VA_ARGS__),TEMPLATE_PARAM(__VA_ARGS__))
#define BEGIN_TEMPLATE2_PROPERTIES_DESCRIPTION(className,...)					\
	BEGIN_TEMPLATE_PROPERTIES_DESCRIPTION_(className,TEMPLATE2_CLASS_DECLARE(__VA_ARGS__),TEMPLATE_PARAM(__VA_ARGS__))
#define BEGIN_TEMPLATE3_PROPERTIES_DESCRIPTION(className,...)					\
	BEGIN_TEMPLATE_PROPERTIES_DESCRIPTION_(className,TEMPLATE3_CLASS_DECLARE(__VA_ARGS__),TEMPLATE_PARAM(__VA_ARGS__))
#define BEGIN_TEMPLATE4_PROPERTIES_DESCRIPTION(className,...)					\
	BEGIN_TEMPLATE_PROPERTIES_DESCRIPTION_(className,TEMPLATE4_CLASS_DECLARE(__VA_ARGS__),TEMPLATE_PARAM(__VA_ARGS__))
#define BEGIN_TEMPLATE5_PROPERTIES_DESCRIPTION(className,...)					\
	BEGIN_TEMPLATE_PROPERTIES_DESCRIPTION_(className,TEMPLATE5_CLASS_DECLARE(__VA_ARGS__),TEMPLATE_PARAM(__VA_ARGS__))
#define BEGIN_TEMPLATE6_PROPERTIES_DESCRIPTION(className,...)					\
	BEGIN_TEMPLATE_PROPERTIES_DESCRIPTION_(className,TEMPLATE6_CLASS_DECLARE(__VA_ARGS__),TEMPLATE_PARAM(__VA_ARGS__))


#define BEGIN_TEMPLATE_PROPERTIES_DESCRIPTION_(className,templateClassDeclare,templateParam)			\
	template <templateClassDeclare> bool  className<templateParam>::ms_initialized(false);				\
	template <templateClassDeclare> CRTTI className<templateParam>::ms_rtti;							\
	template <templateClassDeclare> const CRTTI *className<templateParam>::GetRTTI() const{				\
		if (!ms_initialized){																			\
			InitRTTI();																					\
		}																								\
		ms_initialized=true;																			\
		return &ms_rtti;																				\
	}																									\
	template <templateClassDeclare> const CRTTI *className<templateParam>::GetClassRTTI(){				\
		if (!ms_initialized){																			\
		InitRTTI();																						\
		}																								\
		ms_initialized=true;																			\
		return &ms_rtti;																				\
	}																									\
	template <templateClassDeclare> void className<templateParam>::RegisterMembers(){					\
		scMemberList &memberList=ms_rtti.m_members;														\
		typedef className objectType;

#define END_PROPERTIES_DESCRIPTION()											\
	}

}





#endif