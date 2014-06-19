#ifndef SCENUMMEMBER_H
#define SCENUMMEMBER_H
#include "SCMember.h"
namespace sc{
	//impl for the enum type reflection, is there some better design?
	class CEnumMemberBase:public IMemberBase{
	public:
		virtual ~CEnumMemberBase(){}
		virtual int           GetValueFromEnumName(const char *enumValueName) const=0;
		virtual const string &GetEnumNameFromValue(int enumValue) const=0;
		struct EnumValue{
			string		m_name;
			int			m_value;
		};
		typedef std::vector	<EnumValue *> scEnumValueList;
		virtual const scEnumValueList &GetEnumValueList()const=0;
	protected:
		CEnumMemberBase(){}
	};


	template <scUInt descriptionFlags>
	class SCEnumMember:public CEnumMemberBase{
	public:
		SCEnumMember (const char *propertyName,IMemberBase *valueMember){
			ms_memberName=propertyName;
			m_valueMember=valueMember;
			m_nextEnumValue=0;
		}
		~SCEnumMember(){
			for (size_t i=0;i<m_enumValueList.size();i++){
				delete m_enumValueList[i];
			}
		}
		virtual MemberType GetTypeID() const{
			return MemberType_enum;
		}
		IMemberBase *GetValueMember(){
			return m_valueMember;
		}
		virtual void Set(CBaseObject* parent,const char* data) const{
			m_valueMember->Set(parent,data);
		}
		virtual const char* Get(const CBaseObject *parent) const{
			return m_valueMember->Get(parent);
		}
		virtual void Save(const CBaseObject *parent,TiXmlElement *xmlNode) const{
			if (descriptionFlags & MemberDescriptionType_Save){
				TiXmlElement *root=new TiXmlElement(GetMemberName());
				root->SetAttribute("MemberType","Enum");
				m_valueMember->Save(parent,root);
				for (size_t i=0;i<m_enumValueList.size();i++){
					TiXmlElement *element=new TiXmlElement(m_enumValueList[i]->m_name);
					element->SetAttribute("Value",m_enumValueList[i]->m_value);
					root->LinkEndChild(element);
				}
				xmlNode->LinkEndChild(root);
			}
		}
		virtual void Load(CBaseObject *parent,const TiXmlElement *xmlNode) const{
			if (descriptionFlags & MemberDescriptionType_Load){
				const TiXmlElement *root=xmlNode->FirstChildElement(GetMemberName());
				if (!root){
					SCSAY("Error in SCEnumMember Load, enum node not found!\n");
					return;
				}
				m_valueMember->Load(parent,root);
			}
		}
		virtual scUInt	GetDescriptionType() const{
			return descriptionFlags;
		}



		void AddEnumValue(const char *enumValueName){
			EnumValue *newEnumValue=new EnumValue;
			newEnumValue->m_name=string(enumValueName);
			newEnumValue->m_value=m_nextEnumValue;
			m_enumValueList.push_back(newEnumValue);
			m_nextEnumValue++;
		}
		void AddEnumValue(const char *enumValueName,int customEnumValue){
			EnumValue *newEnumValue=new EnumValue;
			newEnumValue->m_name=string(enumValueName);
			newEnumValue->m_value=customEnumValue;
			m_enumValueList.push_back(newEnumValue);
			m_nextEnumValue=customEnumValue+1;
		}
		virtual int  GetValueFromEnumName(const char *enumValueName) const{
			for (size_t i=0;i<m_enumValueList.size();i++){
				if (m_enumValueList[i]->m_name==enumValueName){
					return m_enumValueList[i]->m_value;
				}
			}
			return -9999;
		}

		const string &GetEnumNameFromValue(int enumValue) const{
			for (size_t i=0;i<m_enumValueList.size();i++){
				if (m_enumValueList[i]->m_value==enumValue){
					return m_enumValueList[i]->m_name;
				}
			}
			static string nullStr("NULL");
			return nullStr;
		}
		virtual const scEnumValueList &GetEnumValueList()const{
			return m_enumValueList;
		}
	private:
		IMemberBase	*m_valueMember;
		scEnumValueList  m_enumValueList;
		int				 m_nextEnumValue;
	};

	//impl for enum value reflection
#define BEGIN_ENUM_MEMBER(enumPropertyName,enumMemberName,descriptionFlags)				\
	{																					\
		IMemberBase	*property=SCMemberFactory::CreateMember							\
											<descriptionFlags>							\
						("sel"enumPropertyName,&objectType::enumMemberName);			\
		SCEnumMember<descriptionFlags> *enumMember=										\
			new SCEnumMember<descriptionFlags>(enumPropertyName,property);				\
	CRTTI::PushBackMember(memberList,enumMember);

#define REGISTER_ENUM_VALUE(enumValueName)												\
	enumMember->AddEnumValue(enumValueName);

#define REGISTER_CUSTOM_ENUM_VALUE(enumValueName,customEnumValue)						\
	enumMember->AddEnumValue(enumValueName,customEnumValue);

#define END_ENUM_MEMBER()																\
	}
}



#endif