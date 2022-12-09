#define PLATFORMWIDTH 50
#define PLATFORMHEIGHT 50
#define LTX(x) x - PLATFORMWIDTH / 2	// x of Left Top point
#define LTZ(z) z + PLATFORMHEIGHT / 2	// z of Left Top point

class Platform {
private:
	D3DXMATRIX m_mLocal;
	D3DMATERIAL9 m_mtrl;
	ID3DXMesh* m_pBoundMesh;

	float x, z;	// left top point of square
	float width, depth, height;

public:

};