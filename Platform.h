#include "CWall.h"

#define WIDTH 50
#define HEIGHT 50
#define LTX(x) x - WIDTH / 2	// x of Left Top point
#define LTZ(z) z + HEIGHT / 2	// z of Left Top point

class Platform {
private:
	D3DXMATRIX m_mLocal;
	D3DMATERIAL9 m_mtrl;
	ID3DXMesh* m_pBoundMesh;

	float x, z;	// left top point of square
	float width, depth, height;

public:

};