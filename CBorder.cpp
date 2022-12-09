#include "d3dUtility.h"
#include "CBorder.h"

// 테두리의 생성자
CBorder::CBorder(D3DXCOLOR color)
{
	D3DXMatrixIdentity(&m_mLocal);
	ZeroMemory(&m_mtrl, sizeof(m_mtrl));
	mesh = nullptr;

	m_mtrl.Ambient = color;
	m_mtrl.Diffuse = color;
	m_mtrl.Specular = color;
	m_mtrl.Emissive = d3d::BLACK;
	m_mtrl.Power = 5.0f;
}

// 테두리의 소멸자
CBorder::~CBorder()
{
	d3d::Release<ID3DXMesh*>(mesh);

	for (int i = 0; i < Textures.size(); i++)
	{
		d3d::Release<IDirect3DTexture9*>(Textures[i]);
	}
}

bool CBorder::create(IDirect3DDevice9* pDevice, float ix, float iz, float iwidth, float iheight, float idepth, D3DXCOLOR color = d3d::WHITE)
{
	if (NULL == pDevice)
		return false;

	m_mtrl.Ambient = color;
	m_mtrl.Diffuse = color;
	m_mtrl.Specular = color;
	m_mtrl.Emissive = d3d::BLACK;
	m_mtrl.Power = 5.0f;

	m_width = iwidth;
	m_depth = idepth;

	if (FAILED(D3DXCreateBox(pDevice, iwidth, iheight, idepth, &m_pBoundMesh, NULL)))
		return false;
	return true;
}

// 벽을 화면에서 소멸시킴
void CBorder::destroy()
{
	if (mesh != nullptr)
	{
		mesh->Release();
		mesh = nullptr;
	}
}

// 테두리를 화면에 그려냄
void CBorder::draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld)
{
	if (NULL == pDevice)
		return;
	pDevice->SetTransform(D3DTS_WORLD, &mWorld);
	pDevice->MultiplyTransform(D3DTS_WORLD, &m_mLocal);
	pDevice->SetMaterial(&m_mtrl);
	m_pBoundMesh->DrawSubset(0);
}

void CBorder::setPosition(float x, float y, float z)
{
	D3DXMATRIX m;
	/*this->m_x = x;
	this->m_z = z;*/
	this->center_x = x;
	this->center_y = y;
	this->center_z = z;

	D3DXMatrixTranslation(&m, x, y, z);
	setLocalTransform(m);
}
void CBorder::setLocalTransform(const D3DXMATRIX& mLocal) { m_mLocal = mLocal; }