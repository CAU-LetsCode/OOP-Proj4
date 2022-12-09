#ifndef _PLAYER_
#define _PLAYER_

enum class BallType
{
	HAND, // 수구
	EIGHT, // 8번 공
	STRIPE,
	SOLID,
	NONE
};

class Player
{
private:
	unsigned int playerID; 
	unsigned int numTakenBall; 

	BallType playerBallType; 

public:
	Player(unsigned int playerID);
	void setTakenBall(unsigned int numBall); 
	unsigned int getNumTakenBall() const; 
	unsigned int getPlayerId() const; 

	BallType getBallType() const; 
	void setBallType(BallType ballType); 
};

#endif