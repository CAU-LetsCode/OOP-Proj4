#ifndef _FOULMANAGER_
#define _FOULMANAGER_

class FoulManager
{
	void isHandBallInHole();
	bool isEightBallIn();
	bool isEightBallWithFoul(); 

public:
	FoulManager();
	void reset(); 
	void checkFoul();
	bool isLose(); 
};

#endif