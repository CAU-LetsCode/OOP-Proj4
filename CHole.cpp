#include "d3dUtility.h"
#include "CHole.h"
#include <cmath>

CHole::CHole() : m_radius(0.25) {
	D3DXMatrixIdentity(&m_mLocal); 
	D3DXMatrixIdentity(&rotationMat); 
	ZeroMemory(&m_mtrl, sizeof(m_mtrl)); 
	m_pSphereMesh = nullptr;

	m_mtrl.Ambient = d3d::BLACK;
	m_mtrl.Diffuse = d3d::BLACK;
	m_mtrl.Specular = d3d::BLACK;
	m_mtrl.Emissive = d3d::BLACK;
	m_mtrl.Power = 5.0f;
}

CHole::~CHole() {
}

bool CHole::create(IDirect3DDevice9* pDevice) {
	if (pDevice == nullptr) {
		return false;
	}

	HRESULT hr = D3DXCreateCylinder(pDevice, m_radius, m_radius, 0.50f, 50, 50, &m_pSphereMesh, nullptr);
	D3DXMatrixRotationX(&rotationMat, 33);
	setLocalTransform(m_mLocal);

	if (FAILED(hr)) {
		return false;
	}

	return true;
} 

void CHole::destroy() {
	if (m_pSphereMesh != nullptr) {
		m_pSphereMesh->Release();
		m_pSphereMesh = nullptr;
	}
}

void CHole::draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld) {
	if (NULL == pDevice) return;

	pDevice->SetTransform(D3DTS_WORLD, &mWorld);
	pDevice->MultiplyTransform(D3DTS_WORLD, &m_mLocal);
	pDevice->MultiplyTransform(D3DTS_WORLD, &rotationMat);

	pDevice->SetMaterial(&m_mtrl);
	m_pSphereMesh->DrawSubset(0);
}

bool CHole::hasIntersected(CSphere& ball) const {
	double xDistance = pow((this->center_x - ball.getPosition().x), 2);
	double zDistance = pow((this->center_z - ball.getPosition().z), 2);
	double totalDistance = sqrt(xDistance + zDistance);

	if (totalDistance < (this->getRadius())) {
		return true;
	}
	
	return false;
}


void CHole::hitBy(CSphere& ball) {
	if (this->hasIntersected(ball) && !ball.isDisabled()) {
		ball.setPosition(100000, ball.getPosition().y, 100000);
		ball.setPower(0.0f, 0.0f);
		ball.disable();
	}
}

float CHole::getRadius(void) const {
	return m_radius;
}