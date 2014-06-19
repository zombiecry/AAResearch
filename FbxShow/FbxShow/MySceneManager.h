#ifndef MYSCENEMANAGER_H
#define MYSCENEMANAGER_H
#include "stdafx.h"

namespace sc{
	class CMySceneManager:public CBaseObject{
		DECLARE_SINGLETON(CMySceneManager)
		DECLARE_BASE_OBJECT(CMySceneManager,CBaseObject)
	public:
		CMySceneManager();
		~CMySceneManager();
		void Init(IDirect3DDevice9* pd3dDevice);
		void Draw(IDirect3DDevice9* pd3dDevice);
	private:
		LPDIRECT3DVERTEXBUFFER9 m_pVB; // Buffer to hold vertices
	};
}







#endif