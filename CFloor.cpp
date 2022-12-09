#include "CFloor.h"
#include "CSphere.h"
#include <iostream>
using namespace std;

#define M_RADIUS 0.21   
#define PI 3.14159265
#define M_HEIGHT 0.01
#define DECREASE_RATE 0.9982

const float CFloor::LOSS_RATIO = 0.006;

CFloor::CFloor(void) {
    D3DXMatrixIdentity(&m_mLocal);
    ZeroMemory(&m_mtrl, sizeof(m_mtrl));
    m_width = 0;
    m_depth = 0;
    m_pBoundMesh = NULL;
}

CFloor::CFloor(float iwidth, float iheight, float idepth, D3DXCOLOR color) {
    D3DXMatrixIdentity(&m_mLocal);
    ZeroMemory(&m_mtrl, sizeof(m_mtrl));

    m_mtrl.Ambient = color;
    m_mtrl.Diffuse = color;
    m_mtrl.Specular = color;
    m_mtrl.Emissive = d3d::BLACK;
    m_mtrl.Power = 5.0f;
    m_width = iwidth;
    m_height = iheight;
    m_depth = idepth;
    m_pBoundMesh = nullptr;
}

CFloor::~CFloor(void) {}

bool CFloor::create(IDirect3DDevice9* pDevice, float ix, float iz, float iwidth, float iheight, float idepth, D3DXCOLOR color = d3d::WHITE) {
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

void CFloor::destroy(void) {
    if (m_pBoundMesh != NULL) {
        m_pBoundMesh->Release();
        m_pBoundMesh = NULL;
    }
}

void CFloor::draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld) {
    if (NULL == pDevice)
        return;
    pDevice->SetTransform(D3DTS_WORLD, &mWorld);
    pDevice->MultiplyTransform(D3DTS_WORLD, &m_mLocal);
    pDevice->SetMaterial(&m_mtrl);
    m_pBoundMesh->DrawSubset(0);
}


void CFloor::setPosition(float x, float y, float z) {
    D3DXMATRIX m;
    this->m_x = x;
    this->m_z = z;

    D3DXMatrixTranslation(&m, x, y, z);
    setLocalTransform(m);
}

float CFloor::getHeight(void) const { return M_HEIGHT; }

void CFloor::setLocalTransform(const D3DXMATRIX& mLocal) { m_mLocal = mLocal; }

void CFloor::setType(int type) { type = type; }

D3DXVECTOR3 CFloor::getPosition() const {
    D3DXVECTOR3 org(center_x, center_y, center_z);
    return org;
}

