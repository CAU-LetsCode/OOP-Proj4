#include "Map.h"

using namespace std;


Map::Map(int num_platform) {
	this->num_platform = num_platform;
}

Map::~Map(void) {

}


bool Map::drawMap1(IDirect3DDevice9* Device) {
	
	vector<array<float, 3>> g_platform_cord(num_platform);
	// create platform
	this->g_platforms[0].setPosition(0, 0, 0);
	this->g_platforms[1].setPosition(-0.5, 0, 0.3);
	this->g_platforms[2].setPosition(+0.5, 0, 0.3);
	this->g_platforms[3].setPosition(-1.0, 0, 0.6);
	this->g_platforms[4].setPosition(+1.0, 0, 0.6);
	this->g_platforms[5].setPosition(-1.5, 0, 0.9);
	this->g_platforms[6].setPosition(+1.5, 0, 0.9);
	this->g_platforms[7].setPosition(-2.0, 0, 1.2);
	this->g_platforms[8].setPosition(+2.0, 0, 1.2);

	this->g_platforms[9].setPosition(+1.5, 0, 1.5);
	this->g_platforms[10].setPosition(-1.5, 0, 1.5);
	this->g_platforms[11].setPosition(+1.0, 0, 1.8);
	this->g_platforms[12].setPosition(-1.0, 0, 1.8);
	this->g_platforms[13].setPosition(+0.5, 0, 2.1);
	this->g_platforms[14].setPosition(-0.5, 0, 2.1);
	this->g_platforms[15].setPosition(+0.0, 0, 2.4);

	for (int i = 0; i < num_platform; i++) {
		if (!g_platforms[i].create(Device, d3d::GREEN)) return false;
		D3DXVECTOR3 m = g_platforms[i].getPosition();
		g_platforms[i].setPosition(m.x, m.y, m.z);
	}
}


void  Map::destroy(void) {
	for (int i = 0; i < num_platform; i++) {
		g_platforms[i].destroy();
	}
}
