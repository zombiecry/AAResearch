#include "SCBaseObject.h"
#include "SCLog.h"
#include <stack>
namespace sc{
	CRTTI CBaseObject::ms_rtti("SCBaseObject",NULL);

	void CBaseObject::SaveToXML(const char *fileName) const{
		TiXmlDocument doc;
		TiXmlDeclaration *decl=new TiXmlDeclaration("1.0","","");
		doc.LinkEndChild(decl);
		TiXmlElement *root=new TiXmlElement("Object");
		const CRTTI *rtti=GetRTTI();
		root->SetAttribute("ClassType",rtti->GetClassName());
		doc.LinkEndChild(root);
		Save(rtti,root);

		TiXmlDocument oldDoc(fileName);
		if (oldDoc.LoadFile()){
			string backupFileName=string(fileName)+string(".replace_backup.xml");
			oldDoc.SaveFile(backupFileName);
		}
		doc.SaveFile(fileName);
	}
	void CBaseObject::Save(const CRTTI *rtti,TiXmlNode *xmlNode)const{
		if (rtti->GetParentRTTI()){
			Save(rtti->GetParentRTTI(),xmlNode);
		}
		if (rtti==CBaseObject::GetClassRTTI()){
			return;
		}

		TiXmlElement *root=NULL;
		root=new TiXmlElement(rtti->GetClassName());
		if (!root){
			SCSAYD("new root xml element failed!\n")
			return;
		}
		const scMemberList &members=rtti->GetMembers();
		for (size_t i=0;i<members.size();i++){
			members[i]->Save(this,root);
		}
		xmlNode->LinkEndChild(root);
	}
	void CBaseObject::LoadFromXML(const char *fileName){
		TiXmlDocument doc(fileName);
		if (!doc.LoadFile()){
			SCSAY("LoadFromXML error! doc: %s cannot be opened!\n",fileName);
			return;
		}
		TiXmlHandle docHandle(&doc);
		TiXmlElement *firstElement=docHandle.FirstChildElement().FirstChildElement().Element();
		if (!firstElement){
			SCSAY("LoadFromXML error! no root element for the object!\n");
			return;
		}
		
		typedef stack <const CRTTI *> scRTTIStack;
		scRTTIStack rttiStack;
		const CRTTI *rtti=GetRTTI();
		while (rtti){
			if (rtti!=CBaseObject::GetClassRTTI()){
				rttiStack.push(rtti);
			}
			rtti=rtti->GetParentRTTI();
		}
		TiXmlElement *curElement=firstElement;
		while (!rttiStack.empty()){
			rtti=rttiStack.top();
			Load(rtti,curElement);
			rttiStack.pop();
			curElement=curElement->NextSiblingElement();
		}
	}
	void CBaseObject::Load(const CRTTI *rtti,TiXmlNode *xmlNode){
		const scMemberList &members=rtti->GetMembers();
		for (size_t i=0;i<members.size();i++){
			members[i]->Load(this,xmlNode->ToElement());
		}
	}
	void CBaseObject::SaveAsMember(TiXmlNode *xmlNode,const char *memberName) const{
		const CRTTI *rtti=GetRTTI();
		TiXmlElement *root=new TiXmlElement(memberName);
		root->SetAttribute("ClassType",rtti->GetClassName());
		xmlNode->LinkEndChild(root);
		//the child members
		const scMemberList &members=rtti->GetMembers();
		for (size_t i=0;i<members.size();i++){
			members[i]->Save(this,root);
		}

	}
	void CBaseObject::LoadAsMember(const TiXmlNode *xmlNode,const char *memberName){
		const TiXmlNode *currentNode=xmlNode->FirstChild(memberName);
		if (!currentNode){
			SCSAY("LoadAsMember error! no child node named: %s\n",memberName);
			return;
		}
		const TiXmlElement *element=currentNode->ToElement();
		const CRTTI *rtti=GetRTTI();
		const scMemberList &members=rtti->GetMembers();
		for (size_t i=0;i<members.size();i++){
			members[i]->Load(this,element);
		}

	}


}
