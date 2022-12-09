#include "CWall.h"
#include "CSphere.h"
#include <iostream>
using namespace std;

#define M_RADIUS 0.21   // ball radius
#define PI 3.14159265
#define M_HEIGHT 0.01
#define DECREASE_RATE 0.9982

const float CWall::LOSS_RATIO = 0.006;

CWall::CWall(void)
{
    D3DXMatrixIdentity(&m_mLocal);
    ZeroMemory(&m_mtrl, sizeof(m_mtrl));
    m_width = 0;
    m_depth = 0;
    m_pBoundMesh = NULL;
}

CWall::CWall(float iwidth, float iheight, float idepth, D3DXCOLOR color) {
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

CWall::~CWall(void) {}

bool CWall::create(IDirect3DDevice9* pDevice, float ix, float iz, float iwidth, float iheight, float idepth, D3DXCOLOR color = d3d::WHITE) {
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
void CWall::destroy(void) {
    if (m_pBoundMesh != NULL) {
        m_pBoundMesh->Release();
        m_pBoundMesh = NULL;
    }
}

void CWall::draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld) {
    if (NULL == pDevice)
        return;
    pDevice->SetTransform(D3DTS_WORLD, &mWorld);
    pDevice->MultiplyTransform(D3DTS_WORLD, &m_mLocal);
    pDevice->SetMaterial(&m_mtrl);
    m_pBoundMesh->DrawSubset(0);
}

void CWall::setPosition(float x, float y, float z) {
    D3DXMATRIX m;

    this->center_x = x;
    this->center_y = y;
    this->center_z = z;

    D3DXMatrixTranslation(&m, x, y, z);
    setLocalTransform(m);
}

float CWall::getHeight(void) const { return M_HEIGHT; }

void CWall::setLocalTransform(const D3DXMATRIX& mLocal) { m_mLocal = mLocal; }

void CWall::setType(int type) { type = type; }

void CWall::adjustPosition(CSphere& ball){
    ball.setPosition((ball.getPosition().x + ball.getPreCenter_x()) / 2, ball.getPosition().y, (ball.getPosition().z + ball.getPreCenter_z()) / 2);
    if (this->hasIntersected(ball))
    {
        ball.setPosition(ball.getPreCenter_x(), ball.getPosition().y, ball.getPreCenter_z());
    }
}

D3DXVECTOR3 CWall::getPosition() const {
    D3DXVECTOR3 org(center_x, center_y, center_z);
    return org;
}

