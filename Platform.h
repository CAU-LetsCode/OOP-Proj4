#ifndef _PLATFORM
#define _PLATFORM

#include "d3dUtility.h"

#define PLATFORMWIDTH 0.4f
#define PLATFORMHEIGHT 0.1f
#define PLATFORMDEPTH 0.05f
#define LTX(x) x - PLATFORMWIDTH / 2	// x of Left Top point
#define LTZ(z) z + PLATFORMHEIGHT / 2	// z of Left Top point

class Platform {
private:
	D3DXMATRIX m_mLocal;
	D3DMATERIAL9 m_mtrl;
	ID3DXMesh* m_pBoundMesh;

	float x, y, z;	// center point of box
	float width, depth, height;

	void setLocalTransform(const D3DXMATRIX& mLocal);

public:
    Platform(void);
    ~Platform(void);
    bool create(IDirect3DDevice9* pDevice, D3DXCOLOR color);
    void destroy(void);
    void draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld);
    void setPosition(float x, float y, float z);
    float getHeight(void) const;
    //void adjustPosition(CSphere& ball);   //todo
    D3DXVECTOR3 getPosition() const;
};

#endif