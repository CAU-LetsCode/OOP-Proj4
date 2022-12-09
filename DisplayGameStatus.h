#ifndef _DISPLAYGAMESTATUS_
#define _DISPLAYGAMESTATUS_

#include <vector>
#include <string>

#include "Player.h"
#include "d3dUtility.h"
#include "d3dfont.h"
#include "status.h"
using std::vector;
using std::string;

class DisplayGameStatus 
{
private:

	int windowWidth; 
	int windowHeight; 

	string playerName[2]; 
	string playerBallCount[2]; 
	string playerBallType[2]; 

	string turnStatus; 

	Player* players; 
	CD3DFont* FontObjects[7]; 
	
public:
	DisplayGameStatus(const int windowWidth, const int windowHeight, Player* players);
	~DisplayGameStatus();

	bool create(const char* fontFamily, const int fontSize, IDirect3DDevice9* pDevice);
	void destory();

	bool update(); 

private:
	string _getBallType(const BallType b);
	string _getTurnStatus();
};

#endif