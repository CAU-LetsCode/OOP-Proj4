#ifndef _CHOLE_
#define _CHOLE_
#include "d3dUtility.h"
#include "CSphere.h"

class CHole : public CSphere
{
private:
	float m_radius;
	D3DMATERIAL9 m_mtrl;
	ID3DXMesh* m_pSphereMesh;
	D3DXMATRIX rotationMat;

public:
	CHole();
	~CHole();

	bool create(IDirect3DDevice9* pDevice); 
	void destroy(); 
	void draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld);
	bool hasIntersected(CSphere& ball) const; 
	void hitBy(CSphere& ball); 
	float getRadius() const; 	

};
#endif