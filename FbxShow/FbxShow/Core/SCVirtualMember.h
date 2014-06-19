#ifndef SCVIRTUALMEMBER_H
#define SCVIRTUALMEMBER_H
#include "SCMember.h"
#include "SCLog.h"

namespace sc{
	//the impl for virtual member which use method to accomplish 'set','get'
	template <class ObjectType,class MemberType,scUInt descriptionFlags>
	class CVirtualMember:public CMemberType<MemberType>{
		typedef void (ObjectType::*SetMemberFunctionPtr)(const MemberType &);
		typedef const MemberType &(ObjectType::*GetMemberFunctionPtr)();
	public:
		CVirtualMember (const char *propertyName,SetMemberFunctionPtr setter,GetMemberFunctionPtr getter){
			ms_memberName=propertyName;
			m_setter=setter;
			m_getter=getter;
		}
		virtual void Set(CBaseObject* parent,const char* data) const{
			(((ObjectType *)parent)->*m_setter)(*((MemberType *)data));
		}
		virtual const char* Get(const CBaseObject *parent) const{
			return (char *)(&((((ObjectType *)parent)->*m_getter)()));
		}
		virtual void Save(const CBaseObject *parent,TiXmlElement *xmlNode) const{
			if (descriptionFlags & MemberDescriptionType_Save){
				CMemberType::SaveType(xmlNode,*((MemberType *)Get(parent)),GetMemberName().c_str());
			}
		}
		virtual void Load(CBaseObject *parent,const TiXmlElement *xmlNode) const{
			if (descriptionFlags & MemberDescriptionType_Load){
				MemberType tempMember;
				CMemberType::LoadType(xmlNode,tempMember,GetMemberName().c_str());
				(((ObjectType *)parent)->*m_setter)(tempMember);
			}
		}
		virtual scUInt	GetDescriptionType() const{
			return descriptionFlags;
		}
	private:
		//the member-pointer is an offset inside the ObjectType class
		SetMemberFunctionPtr	m_setter;
		GetMemberFunctionPtr	m_getter;
	};



#define REGISTER_VIRTUAL_MEMBER(propertyName,memberSetter,memberGetter,descriptionFlags)		\
	{																							\
		IMemberBase	*property=SCMemberFactory::CreateMember<descriptionFlags>				\
													(propertyName,&memberSetter,&memberGetter);	\
		CRTTI::PushBackMember(memberList,property);											\
	}

	namespace SCMemberFactory{
		template <scUInt descriptionFlags,class ObjectType,class MemberType>
		static IMemberBase * CreateMember(const char *propertyName,
										   void (ObjectType::*memberSetterPtr)(const MemberType &),
										   const MemberType &(ObjectType::*memberGetterPtr)()){
			return new CVirtualMember<ObjectType,MemberType,descriptionFlags> 
								(propertyName,memberSetterPtr,memberGetterPtr);
		}
	}
}


#endif