#include <string>

#include "d3dUtility.h"
#include "Platform.h"

#define JUMPERWIDTH	0.2f
#define JUMPERHEIGHT 0.1f
#define JUMPERDEPTH 0.2f
#define LBX(x) x - JUMPERWIDTH / 2	// x of Left Bottom point
#define LBZ(z) z - JUMPERHEIGHT / 2	// z of Left Botton point

using std::string;

class Jumper {
private:
	float x, y, z;	// center cord
	float v_x, v_z;
	float pre_x, pre_z;
	bool onPlatform;

	string jumperImageFileName = "0";

	IDirect3DTexture9* Tex = nullptr;
	LPD3DXMESH _createMappedBox(IDirect3DDevice9* pDev);
	D3DXMATRIX m_mLocal;
	D3DMATERIAL9 m_mtrl;
	ID3DXMesh* m_pJumperMesh;

public:
	Jumper(void);
	Jumper(const char* jumperImageFileName);
	virtual ~Jumper(void);

	bool create(IDirect3DDevice9* pDevice);
	void destroy(void);
	void draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld);
	bool hasIntersected(Platform& platform);
	void jumperUpdate(float timeDiff);
	double getVelocity_X();
	double getVelocity_Z();
	void setVelocity(double vx, double vz);
	const D3DXMATRIX& getLocalTransform(void) const;
	void setLocalTransform(const D3DXMATRIX& mLocal);
	D3DXVECTOR3 getPosition() const;
	void adjustPosition(Jumper& jumper, Platform platform);
	void setPosition(float x, float y, float z);
	bool isOnPlatform();
	void setOnPlatform(bool flag);
};