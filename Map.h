#include "Platform.h"
#include "vector"

using namespace std;

class Map {
private:
	int num_platform;

public:
	vector<Platform> g_platforms;

	Map(int num_platform);
	~Map(void);

	void setPosition(int i, float x, float y, float z);
	void destroy(void);
};