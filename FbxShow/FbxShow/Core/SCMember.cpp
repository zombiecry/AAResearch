#include "SCMember.h"
namespace sc{
	template <> MemberType			   CMemberType<int>::ms_typeID	= MemberType_int;
	template <> MemberType			 CMemberType<float>::ms_typeID	= MemberType_float;
	template <> MemberType			 CMemberType<double>::ms_typeID = MemberType_double;
	template <> MemberType            CMemberType<bool>::ms_typeID	= MemberType_bool;
	template <> MemberType            CMemberType<string>::ms_typeID= MemberType_string;
	template <>
	void CMemberType<int>::SaveType(TiXmlElement *xmlNode,const int &member,const char *memberName){
		xmlNode->SetAttribute(memberName,member);
	}

	template <>
	void CMemberType<float>::SaveType(TiXmlElement *xmlNode,const float &member,const char *memberName){
		xmlNode->SetDoubleAttribute(memberName,member);
	}
	template <>
	void CMemberType<double>::SaveType(TiXmlElement *xmlNode,const double &member,const char *memberName){
		xmlNode->SetDoubleAttribute(memberName,member);
	}
	template <>
	void CMemberType<bool>::SaveType(TiXmlElement *xmlNode,const bool &member,const char *memberName){
		xmlNode->SetAttribute(memberName,member);
	}
	template <>
	void CMemberType<string>::SaveType(TiXmlElement *xmlNode,const string &member,const char *memberName){
		xmlNode->SetAttribute(memberName,member);
	}

	template <>
	void CMemberType<int>::LoadType(const TiXmlElement *xmlNode,int &member,const char *memberName){
		xmlNode->QueryIntAttribute(memberName,&member);
	}

	template <>
	void CMemberType<float>::LoadType(const TiXmlElement *xmlNode,float &member,const char *memberName){
		xmlNode->QueryFloatAttribute(memberName,&member);
	}
	template <>
	void CMemberType<double>::LoadType(const TiXmlElement *xmlNode,double &member,const char *memberName){
		xmlNode->QueryDoubleAttribute(memberName,&member);
	}
	template <>
	void CMemberType<bool>::LoadType(const TiXmlElement *xmlNode,bool &member,const char *memberName){
		xmlNode->QueryBoolAttribute(memberName,&member);
	}
	template <>
	void CMemberType<string>::LoadType(const TiXmlElement *xmlNode,string &member,const char *memberName){
		xmlNode->QueryStringAttribute(memberName,&member);
	}
}