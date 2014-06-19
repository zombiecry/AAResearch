#ifndef SCMEMBER_H
#define SCMEMBER_H
#include "SCIMemberBase.h"
namespace sc{
	//this class serves as an interpreter, convert the type information into real variable
	template <class T>
	class CMemberType:public IMemberBase{
	public:
		//impl for the adt
		virtual MemberType GetTypeID() const {
			return ms_typeID;
		}
	public:
		static void SaveType(      TiXmlElement *xmlNode,const T &member,const char *memberName);
		static void LoadType(const TiXmlElement *xmlNode,	   T &member,const char *memberName);
	private:
		static MemberType ms_typeID;
	};
	//init the typeID based on the template's parameter
	template <class T> MemberType	     CMemberType<T>::ms_typeID = MemberType_unknow;

	template <class T>
	void CMemberType<T>::SaveType(TiXmlElement *xmlNode,const T &member,const char *memberName){
		member.SaveAsMember(xmlNode,memberName);
	}
	template <>	void CMemberType<float>::SaveType(TiXmlElement *xmlNode,const float &member,const char *memberName);
	template <>	void CMemberType<double>::SaveType(TiXmlElement *xmlNode,const double &member,const char *memberName);
	template <>	void CMemberType<bool>::SaveType(TiXmlElement *xmlNode,const bool &member,const char *memberName);
	template <>	void CMemberType<int>::SaveType(TiXmlElement *xmlNode,const int &member,const char *memberName);
	template <>	void CMemberType<string>::SaveType(TiXmlElement *xmlNode,const string &member,const char *memberName);
	template <class T>
	void CMemberType<T>::LoadType(const TiXmlElement *xmlNode,	   T &member,const char *memberName){
		member.LoadAsMember(xmlNode,memberName);
	}
	template <>	void CMemberType<float>::LoadType(const TiXmlElement *xmlNode,	 float &member,const char *memberName);
	template <>	void CMemberType<double>::LoadType(const TiXmlElement *xmlNode,  double &member,const char *memberName);
	template <>	void CMemberType<bool>::LoadType(const TiXmlElement *xmlNode,	 bool &member,const char *memberName);
	template <>	void CMemberType<int>::LoadType(const TiXmlElement *xmlNode,	 int &member,const char *memberName);
	template <>	void CMemberType<string>::LoadType(const TiXmlElement *xmlNode,	 string &member,const char *memberName);
	//------------------------------------------------------------------------------------------------------
	//ObjectType, the type of the class which hold the member.
	template <class ObjectType,class MemberType,scUInt descriptionFlags>			
	class SCMember:public CMemberType<MemberType>{
	public:
		SCMember (const char *propertyName,MemberType ObjectType:: *memberPtr){
			ms_memberName=propertyName;
			m_memberPtr=memberPtr;
		}
		virtual void Set(CBaseObject* parent,const char* data)const{
			((ObjectType*)parent)->*m_memberPtr=*((MemberType *)data);
		}
		virtual const char* Get(const CBaseObject *parent) const{
			return (char *)(&(((ObjectType *)parent)->*m_memberPtr));
		}
		virtual void Save(const CBaseObject *parent,TiXmlElement *xmlNode) const{
			if (descriptionFlags & MemberDescriptionType_Save){
				CMemberType::SaveType(xmlNode,(((ObjectType *)parent)->*m_memberPtr),GetMemberName().c_str());
			}
		}
		virtual void Load(CBaseObject *parent,const TiXmlElement *xmlNode) const{
			if (descriptionFlags & MemberDescriptionType_Load){
				CMemberType::LoadType(xmlNode,(((ObjectType *)parent)->*m_memberPtr),GetMemberName().c_str());
			}
		}
		virtual scUInt	GetDescriptionType() const{
			return descriptionFlags;
		}
		//the member-pointer is an offset inside the ObjectType class
	private:
		MemberType ObjectType:: *m_memberPtr;
	};
	//------------------------------------------------------------------------------

//register the class member(memberName), serialized name as properName,with descriptionFlags
#define REGISTER_MEMBER(propertyName,memberName,descriptionFlags)				\
	{																			\
		IMemberBase	*property=SCMemberFactory::CreateMember						\
								<descriptionFlags>								\
								(propertyName,&objectType::memberName);			\
		CRTTI::PushBackMember(memberList,property);								\
	}

	namespace SCMemberFactory{
		//template function's explicity specification
		template <scUInt descriptionFlags,class ObjectType,class MemberType>
		static IMemberBase * CreateMember(const char *propertyName,MemberType ObjectType:: *memberPtr){
			return new SCMember<ObjectType,MemberType,descriptionFlags> (propertyName,memberPtr);
		}
	}
}









#endif