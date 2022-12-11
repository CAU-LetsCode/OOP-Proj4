
#include "d3dUtility.h"
#include "Jumper.h"
#include "string"

using std::string;

class Goal
{
protected:
	float center_x, center_y, center_z;
	float m_radius;

	string goalImageFileName = string();

	IDirect3DTexture9* Tex = nullptr;
	LPD3DXMESH _createMappedSphere(IDirect3DDevice9* pDev);
	D3DXMATRIX              m_mLocal;
	D3DMATERIAL9            m_mtrl;
	ID3DXMesh* m_pSphereMesh;


public:
	Goal(void);
	virtual ~Goal(void);

	bool create(IDirect3DDevice9* pDevice);
	void destroy(void);
	void draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld);
	bool hasIntersected(Jumper& ball);
	void hitBy(Jumper& ball);
	const D3DXMATRIX& getLocalTransform(void) const;
	void setLocalTransform(const D3DXMATRIX& mLocal);
	void setPosition(float x, float y, float z);
	D3DXVECTOR3 getPosition() const;
	float getRadius(void) const;
};
