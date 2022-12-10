#include "Jumper.h"

#define FVF_VERTEX D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1

struct _VERTEX {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 norm;
	float tu;
	float tv;
};

Jumper::Jumper(void) {
	D3DXMatrixIdentity(&m_mLocal);
	ZeroMemory(&m_mtrl, sizeof(m_mtrl));
	v_x = v_z = 0;
	m_pJumperMesh = NULL;
}

Jumper::Jumper(const char* jumperImageFileName) {
	Jumper();
	this->jumperImageFileName = jumperImageFileName;
}

Jumper::~Jumper(void) {

}

bool Jumper::create(IDirect3DDevice9* pDevice) {
	if (!pDevice) return false;

	m_mtrl.Diffuse = d3d::WHITE;
	m_mtrl.Ambient = d3d::WHITE;
	m_mtrl.Specular = d3d::WHITE;
	m_mtrl.Emissive = d3d::BLACK;
	m_mtrl.Power = 100.0f;

	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	this->m_pJumperMesh = _createMappedBox(pDevice);

	string filePath = "./image/" + jumperImageFileName + ".bmp";
	if (FAILED(D3DXCreateTextureFromFile(pDevice, filePath.c_str(), &Tex))) {
		return false;
	}

	return true;
}

void Jumper::destroy(void) {
	if (m_pJumperMesh != NULL) {
		m_pJumperMesh->Release();
		m_pJumperMesh = NULL;
	}
}

void Jumper::draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld) {
	if (NULL == pDevice)
		return;

	pDevice->SetTransform(D3DTS_WORLD, &mWorld);
	pDevice->MultiplyTransform(D3DTS_WORLD, &m_mLocal);
	pDevice->SetTexture(0, Tex);
	pDevice->SetMaterial(&m_mtrl);
	m_pJumperMesh->DrawSubset(0);
}

bool Jumper::hasIntersected(Platform& platform) {
	D3DXVECTOR3 cord = this->getPosition();
	D3DXVECTOR3 platform_cord = platform.getPosition();

	double xDistance = cord.x - LTX(platform_cord.x);
	double zDistance = cord.z - LTZ(platform_cord.z);

	if (-JUMPERWIDTH < xDistance && xDistance < PLATFORMWIDTH) {
		if (0 < zDistance && zDistance < PLATFORMHEIGHT) {
			return true;
		}
	}

	return false;
}

double Jumper::getVelocity_X() {
	return v_x;
}

double Jumper::getVelocity_Z() {
	return v_z;
}

void Jumper::setPower(double vx, double vz) {
	v_x = vx;
	v_z = vz;
}

const D3DXMATRIX& Jumper::getLocalTransform(void) const {
	return m_mLocal;
}

void Jumper::setLocalTransform(const D3DXMATRIX& mLocal) {
	m_mLocal = mLocal;
}

D3DXVECTOR3 Jumper::getPosition() const {
	D3DXVECTOR3 org(x, y, z);
	return org;
}

void Jumper::adjustPosition(Jumper& jumper) {
	// todo
}

void Jumper::setPosition(float x, float y, float z) {
	D3DXMATRIX m;

	this->x = x;
	this->y = y;
	this->z = z;

	D3DXMatrixTranslation(&m, x, y, z);
	setLocalTransform(m);
}

LPD3DXMESH Jumper::_createMappedBox(IDirect3DDevice9* pDev) {
	LPD3DXMESH mesh;
	if (FAILED(D3DXCreateSphere(pDev, 50, 50, 50, &mesh, NULL)))
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