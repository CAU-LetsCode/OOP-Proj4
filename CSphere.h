#ifndef _CSPHERE_
#define _CSPHERE_

#include "d3dUtility.h"
#include "Player.h"
#include "string"

using std::string;

class CSphere 
{
protected:
	float center_x, center_y, center_z;
	float m_radius;
	float m_velocity_x;
	float m_velocity_z;
	
	string ballImageFileName = string();
	D3DXMATRIX ballRoll;

	int disableTurn = -1;
	float pre_center_x, pre_center_z;
	typedef CSphere super;

	IDirect3DTexture9* Tex = nullptr;
	LPD3DXMESH _createMappedSphere(IDirect3DDevice9* pDev);
	D3DXMATRIX              m_mLocal;
	D3DMATERIAL9            m_mtrl;
	ID3DXMesh* m_pSphereMesh;

	BallType ballType;

public:
	CSphere(void);
	CSphere(const char* ballImageFileName);
	virtual ~CSphere(void);

	bool create(IDirect3DDevice9* pDevice);
	void destroy(void);
	void draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld);
	bool hasIntersected(CSphere& ball);
	void hitBy(CSphere& ball);
	void ballUpdate(float timeDiff);
	double getVelocity_X();
	double getVelocity_Z();
	void setPower(double vx, double vz);
	float getRadius(void) const;
	const D3DXMATRIX& getLocalTransform(void) const;
	void setLocalTransform(const D3DXMATRIX& mLocal);
	D3DXVECTOR3 getPosition() const;
	void adjustPosition(CSphere& ball);
	void setPosition(float x, float y, float z);
	double CSphere::getPreCenter_x() const;
	double CSphere::getPreCenter_z() const;
	BallType getBallType() const;

	void disable() noexcept; 
	void enable() noexcept; 
	int getDisableTurn() const noexcept; 
	bool isDisabled() const noexcept; 
};

#endif