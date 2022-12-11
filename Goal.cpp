#include "Goal.h"
#include <stdlib.h> 
#include <cstdlib>


#define M_RADIUS 0.14   
#define PI 3.14159265
#define M_HEIGHT 0.01
#define FVF_VERTEX    D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1

struct _VERTEX {
    D3DXVECTOR3 pos;
    D3DXVECTOR3 norm;
    float tu;
    float tv;
};

Goal::Goal(int stage) {
    this->stage = stage;
    ZeroMemory(&m_mtrl, sizeof(m_mtrl)); // memset을 통해 모두 0으로 초기화
    this->m_radius = M_RADIUS;
    this->m_pSphereMesh = nullptr;
    D3DXMatrixIdentity(&m_mLocal);
    this->goalImageFileName = "goal";
}


Goal::~Goal(void) {}

bool Goal::create(IDirect3DDevice9* pDevice) {
    if (NULL == pDevice) return false;

    m_mtrl.Diffuse = d3d::WHITE;
    m_mtrl.Ambient = d3d::WHITE;
    m_mtrl.Specular = d3d::WHITE;
    m_mtrl.Emissive = d3d::BLACK;
    m_mtrl.Power = 100.0f;

    pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

    this->m_pSphereMesh = _createMappedSphere(pDevice);

    string filePath = "./image/" + this->goalImageFileName + ".bmp";

    if (FAILED(D3DXCreateTextureFromFile(pDevice, filePath.c_str(), &Tex))) {
        return false;
    }

    return true;
}

void Goal::destroy(void) {
    if (m_pSphereMesh != NULL) {
        m_pSphereMesh->Release();
        m_pSphereMesh = NULL;
    }
}

void Goal::draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld) {
    if (NULL == pDevice)
        return;

    pDevice->SetTransform(D3DTS_WORLD, &mWorld);
    pDevice->MultiplyTransform(D3DTS_WORLD, &m_mLocal);
    pDevice->SetTexture(0, Tex);
    pDevice->SetMaterial(&m_mtrl);
    m_pSphereMesh->DrawSubset(0);

}

bool Goal::hasIntersected(Jumper& jumper) {
    D3DXVECTOR3 cord = this->getPosition();
    D3DXVECTOR3 jumper_cord = jumper.getPosition();

    double xDistance = abs((cord.x - jumper_cord.x) * (cord.x - jumper_cord.x));
    double zDistance = abs((cord.z - jumper_cord.z) * (cord.z - jumper_cord.z));
    double totalDistance = sqrt(xDistance + zDistance);

    if (totalDistance < (this->getRadius() + JUMPERWIDTH / 2)) {
        return true;
    }

    return false;
}

void Goal::hitBy(Jumper& jumper) {
    if (this->hasIntersected(jumper)) {
        if (stage == 1) jumper.setPosition(20, 0, 0.3);
        if (stage == 2) jumper.setPosition(40, 0, 0.3);
        if (stage == 3) jumper.setPosition(60, 0, 0.5);
    }
}



const D3DXMATRIX& Goal::getLocalTransform(void) const { return m_mLocal; }
void Goal::setLocalTransform(const D3DXMATRIX& mLocal) { m_mLocal = mLocal; }




void Goal::setPosition(float x, float y, float z) {
    D3DXMATRIX m;

    this->center_x = x;
    this->center_y = y;
    this->center_z = z;

    D3DXMatrixTranslation(&m, x, y, z);
    this->setLocalTransform(m);
}



LPD3DXMESH Goal::_createMappedSphere(IDirect3DDevice9* pDev) {
    LPD3DXMESH mesh;
    if (FAILED(D3DXCreateSphere(pDev, this->getRadius(), 50, 50, &mesh, NULL)))
        return nullptr;

    LPD3DXMESH texMesh;
    if (FAILED(mesh->CloneMeshFVF(D3DXMESH_SYSTEMMEM, FVF_VERTEX, pDev, &texMesh)))
        return mesh;

    mesh->Release();

    struct _VERTEX* pVerts;
    if (SUCCEEDED(texMesh->LockVertexBuffer(0, reinterpret_cast<void**>(&pVerts)))) {
        int numVerts = texMesh->GetNumVertices();

        for (int i = 0; i < numVerts; i++) {
            pVerts->tu = asinf(pVerts->norm.x) / D3DX_PI + 0.5f;
            pVerts->tv = asinf(pVerts->norm.y) / D3DX_PI + 0.5f;

            pVerts++;
        }
        texMesh->UnlockVertexBuffer();
    }

    return texMesh;
}

D3DXVECTOR3 Goal::getPosition() const {
    D3DXVECTOR3 org(center_x, center_y, center_z);
    return org;
}
float Goal::getRadius(void) const { return (float)(M_RADIUS); }