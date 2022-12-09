#include "CWall.h"

#define WIDTH 50
#define HEIGHT 50
#define CENTERX(x) x-WIDTH/2	// 
#define CENTERZ(z) z-HEIGHT/2	// 

class Platform {
private:
	D3DXMATRIX m_mLocal;
	D3DMATERIAL9 m_mtrl;
	ID3DXMesh* m_pBoundMesh;

	float x, z;	// left top point of square
	float width, depth, height;

public:

};