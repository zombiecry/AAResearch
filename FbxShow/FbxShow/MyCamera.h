#ifndef MYCAMERA_H
#define MYCAMERA_H
#include "stdafx.h"
#include "DXUTcamera.h"

namespace sc{
	class CMyCamera:public CBaseObject,public CFirstPersonCamera{
	DECLARE_SINGLETON(CMyCamera)
	DECLARE_BASE_OBJECT(CMyCamera,CBaseObject)
	public:
		CMyCamera ();
		void OnResetDevice(const D3DSURFACE_DESC* pBackBufferSurfaceDesc);
	protected:
		virtual D3DUtil_CameraKeys MapKey( UINT nKey )
		{
			// Provide custom mapping here.
			// Same as default mapping but disable arrow keys.
			switch( nKey )
			{
			case 'A':
				return CAM_STRAFE_LEFT;
			case 'D':
				return CAM_STRAFE_RIGHT;
			case 'W':
				return CAM_MOVE_FORWARD;
			case 'S':
				return CAM_MOVE_BACKWARD;
			case 'Q':
				return CAM_MOVE_DOWN;
			case 'E':
				return CAM_MOVE_UP;

			case VK_HOME:
				return CAM_RESET;
			}

			return CAM_UNKNOWN;
		}
	private:
		float		m_scaler1;
		float       m_scaler2;
		bool		m_leftButton;
		bool		m_midButton;
		bool		m_rightButton;
		CVec3		m_eye;
		CVec3		m_look;
	};
}


#endif