#ifndef _MAP_
#include "Platform.h"
#include "vector"

class Map {
private :
	int num_platform;
	vector<Platform> g_platforms;
	
public :
	Map(int num_platform);
	~Map(void);
	
	bool drawMap1(IDirect3DDevice9* Device);
	void destroy(void);
};

#endif