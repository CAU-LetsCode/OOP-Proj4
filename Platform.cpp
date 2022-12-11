#include "Platform.h"

Platform::Platform(void) {
    D3DXMatrixIdentity(&m_mLocal);
    ZeroMemory(&m_mtrl, sizeof(m_mtrl));
    x, z = 0;
    width = PLATFORMWIDTH;
    height = PLATFORMHEIGHT;
    depth = PLATFORMDEPTH;
    m_pBoundMesh = nullptr;
}

Platform::~Platform(void) {

}

bool Platform::create(IDirect3DDevice9* pDevice, D3DXCOLOR color) {
    if (NULL == pDevice)
        return false;

    m_mtrl.Ambient = color;
    m_mtrl.Diffuse = color;
    m_mtrl.Specular = color;
    m_mtrl.Emissive = d3d::BLACK;
    m_mtrl.Power = 5.0f;

    if (FAILED(D3DXCreateBox(pDevice, PLATFORMWIDTH, PLATFORMHEIGHT, PLATFORMDEPTH, &m_pBoundMesh, NULL)))
        return false;
    return true;
}

void Platform::destroy(void) {
    if (m_pBoundMesh) {
        m_pBoundMesh->Release();
        m_pBoundMesh = NULL;
    }
}

void Platform::draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld) {
    if (!pDevice) return;

    pDevice->SetTransform(D3DTS_WORLD, &mWorld);
    pDevice->MultiplyTransform(D3DTS_WORLD, &m_mLocal);
    pDevice->SetMaterial(&m_mtrl);
    m_pBoundMesh->DrawSubset(0);
}

void Platform::setPosition(float x, float y, float z) {
    D3DXMATRIX m;

    this->x = x;
    this->y = y;
    this->z = z;

    D3DXMatrixTranslation(&m, x, y, z);
    setLocalTransform(m);
}

float Platform::getHeight(void) const {
    //todo
    return PLATFORMHEIGHT;
}

void Platform::setLocalTransform(const D3DXMATRIX& mLocal) { m_mLocal = mLocal; }

//void adjustPosition(CSphere& ball);   //todo

D3DXVECTOR3 Platform::getPosition() const {
    D3DXVECTOR3 org(this->x, this->y, this->z);
    return org;
}