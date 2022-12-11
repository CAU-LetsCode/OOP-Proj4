#ifndef _DISPLAYGAMESTATUS_
#define _DISPLAYGAMESTATUS_

#include <vector>
#include <string>

#include "Jumper.h"
#include "d3dUtility.h"
#include "d3dfont.h"

using std::vector;
using std::string;

class DisplayGameStatus
{
private:

	int windowWidth;
	int windowHeight;

	string jumperName;
	string playerBallCount[2];

	string turnStatus;

	Jumper jumper;
	CD3DFont* FontObjects[9];

public:
	DisplayGameStatus(const int windowWidth, const int windowHeight, Jumper jumper);
	~DisplayGameStatus();

	bool create(const char* fontFamily, const int fontSize, IDirect3DDevice9* pDevice);
	void destroy();

	bool update();
};

#endif