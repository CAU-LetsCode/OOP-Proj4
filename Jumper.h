#include <string>

#include "d3dUtility.h"

using std::string;

class Jumper {
private:
	float x, z;
	float v_x, v_z;
	float pre_x, pre_z;

	string jumperImageFileName = string();

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
	double getVelocity_X();
	double getVelocity_Z();
	void setPower(double vx, double vz);
	const D3DXMATRIX& getLocalTransform(void) const;
	void setLocalTransform(const D3DXMATRIX& mLocal);
	D3DXVECTOR3 getPosition() const;
	void adjustPosition(Jumper& jumper);
	void setPosition(float x, float y, float z);

	void disable() noexcept;
	void enable() noexcept;
	int getDisableTurn() const noexcept;
	bool isDisabled() const noexcept;
};