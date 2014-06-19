#ifndef SCMEMBERBASE_H
#define SCMEMBERBASE_H
#include <iostream>
#include <string>
#include <vector>
#include "tinyxml.h"
using namespace std;

namespace sc{
	enum MemberType{
		MemberType_int,
		MemberType_float,
		MemberType_double,
		MemberType_string,
		MemberType_bool,
		MemberType_enum,
		MemberType_unknow,		//treat it as sub class member.
		MemberType_num
	};

	enum MemberDescriptionType{
		MemberDescriptionType_Save = 1<<0,
		MemberDescriptionType_Load = 1<<1,
		MemberDescriptionType_Persistence = MemberDescriptionType_Load | MemberDescriptionType_Save,
		MemberDescriptionType_Display = 1<<2,
		MemberDescriptionType_Edit =1<<3,
		MemberDescriptionType_Ui = MemberDescriptionType_Display | MemberDescriptionType_Edit,
		MemberDescriptionType_All = MemberDescriptionType_Persistence | MemberDescriptionType_Ui
	};
	typedef unsigned int scUInt;

	class CBaseObject;
	//the ADT for SCMember, used to dynamic identify the 'MemberType' of SCMember
	class IMemberBase{
	public:
		virtual ~IMemberBase(){}
		virtual MemberType				GetTypeID() const =0;
		virtual scUInt					GetDescriptionType() const =0;
		virtual void					Set(	   CBaseObject* parent,const char* data) const=0;
		virtual const char			   *Get(const CBaseObject *parent) const=0;
		const string				   &GetMemberName() const{
			return ms_memberName;
		}
		virtual void					Save(const CBaseObject *parent,	   TiXmlElement *xmlNode) const=0;
		virtual void				    Load(CBaseObject *parent,const TiXmlElement *xmlNode) const=0;
	protected:
		string ms_memberName;
	protected:
		IMemberBase(){}
	};
}



#endif