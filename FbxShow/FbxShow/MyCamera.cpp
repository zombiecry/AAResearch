#include "MyCamera.h"
namespace sc{
	DEFINE_SINGLETON(CMyCamera)
	BEGIN_PROPERTIES_DESCRIPTION(CMyCamera)
		REGISTER_MEMBER("m_scaler1",m_scaler1,MemberDescriptionType_Persistence)
		REGISTER_MEMBER("m_scaler2",m_scaler2,MemberDescriptionType_Persistence)
		REGISTER_MEMBER("m_leftButton",m_leftButton,MemberDescriptionType_Persistence)
		REGISTER_MEMBER("m_midButton",m_midButton,MemberDescriptionType_Persistence)
		REGISTER_MEMBER("m_rightButton",m_rightButton,MemberDescriptionType_Persistence)
		REGISTER_MEMBER("m_eye",m_eye,MemberDescriptionType_Persistence)
		REGISTER_MEMBER("m_look",m_look,MemberDescriptionType_Persistence)
	END_PROPERTIES_DESCRIPTION()

	CMyCamera::CMyCamera (){
		this->LoadFromXML("Data/CMyCamera.xml");
		this->SaveToXML("Data/CMyCamera.xml");
	}

	void CMyCamera::OnResetDevice(const D3DSURFACE_DESC* pBackBufferSurfaceDesc){
		// Setup the camera's projection parameters
		float fAspectRatio = pBackBufferSurfaceDesc->Width / ( FLOAT )pBackBufferSurfaceDesc->Height;
		this->SetProjParams( D3DX_PI / 4, fAspectRatio, 0.1f, 100.0f );
	}

}