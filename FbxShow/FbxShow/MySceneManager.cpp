#include "MySceneManager.h"
namespace sc{
	DEFINE_SINGLETON(CMySceneManager)
	BEGIN_PROPERTIES_DESCRIPTION(CMySceneManager)

	END_PROPERTIES_DESCRIPTION()

	// A structure for our custom vertex type
	struct CUSTOMVERTEX
	{
		FLOAT x, y, z;      // The untransformed, 3D position for the vertex
		DWORD color;        // The vertex color
	};

	// Our custom FVF, which describes our custom vertex structure
	#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)

	CMySceneManager::CMySceneManager(){
		//this->LoadFromXML("Data/CMySceneManager.xml");
		this->SaveToXML("Data/CMySceneManager.xml");
	}

	void CMySceneManager::Init(IDirect3DDevice9* pd3dDevice){
		//init a vertex buffer.
		m_pVB=NULL;
		{
			// Initialize three vertices for rendering a triangle
			CUSTOMVERTEX g_Vertices[] =
			{
				{ -1.0f,-1.0f, 0.0f, 0xffff0000, },
				{  1.0f,-1.0f, 0.0f, 0xff0000ff, },
				{  0.0f, 1.0f, 0.0f, 0xffffffff, },
			};

			// Create the vertex buffer.
			if( FAILED( pd3dDevice->CreateVertexBuffer( 3 * sizeof( CUSTOMVERTEX ),
				0, D3DFVF_CUSTOMVERTEX,
				D3DPOOL_DEFAULT, &m_pVB, NULL ) ) )
			{
				return ;
			}

			// Fill the vertex buffer.
			VOID* pVertices;
			if( FAILED( m_pVB->Lock( 0, sizeof( g_Vertices ), ( void** )&pVertices, 0 ) ) )
				return ;
			memcpy( pVertices, g_Vertices, sizeof( g_Vertices ) );
			m_pVB->Unlock();

		}


		return;
	}

	CMySceneManager::~CMySceneManager(){

	}
	void CMySceneManager::Draw(IDirect3DDevice9* pd3dDevice){
		// Render the vertex buffer contents
		pd3dDevice->SetStreamSource( 0, m_pVB, 0, sizeof( CUSTOMVERTEX ) );
		pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
		pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 1 );
	}
}

