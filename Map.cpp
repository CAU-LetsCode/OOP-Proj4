#include "Map.h"

using namespace std;


Map::Map(int num_platform) {
    this->num_platform = num_platform;
    this->g_platforms.resize(16);
}

Map::~Map(void) {

}


void Map::setPosition(int i, float x, float y, float z) {

    // create platform
    this->g_platforms[i].setPosition(x, y, z);
}


void  Map::destroy(void) {
    for (int i = 0; i < num_platform; i++) {
        g_platforms[i].destroy();
    }
}