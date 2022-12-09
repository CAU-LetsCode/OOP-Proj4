#ifndef _CBORDER_
#define _CBORDER_

#include "d3dUtility.h"
#include <vector>

// -----------------------------------------------------------------------------
// CBorder class definition
// 당구대(다이)의 테두리에 관련한 클래스에 대한 정의 (3ds max와 maya로 작업)
// -----------------------------------------------------------------------------
class CBorder 
{
private:
	float m_width;
	float m_depth;
	float center_x, center_y, center_z;
	D3DMATERIAL9 m_mtrl;
	D3DXMATRIX              m_mLocal;
	ID3DXMesh* mesh;
	std::vector<D3DMATERIAL9> Mtrls;
	std::vector<IDirect3DTexture9*> Textures;
	ID3DXMesh* m_pBoundMesh;
	void setLocalTransform(const D3DXMATRIX& mLocal);
public:
	CBorder(D3DXCOLOR color); // 테두리의 생성자
	~CBorder(); // 테두리의 소멸자
	void setPosition(float x, float y, float z);
	bool create(IDirect3DDevice9* pDevice, float ix, float iz, float iwidth, float iheight, float idepth, D3DXCOLOR color); // 테두리를 화면에 생성함
	void draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld); // 테두리를 화면에 그려냄
	void destroy(); // 테두리를 화면에서 소멸시킴
};

#endif
