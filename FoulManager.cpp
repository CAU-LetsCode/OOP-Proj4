#include "FoulManager.h"
#include "TurnManager.h"
#include "Status.h"
#include "CHandSphere.h"
#include <cstdlib>
extern Status status;
extern array<CSphere*, 16> g_sphere;
extern Player players[2];

FoulManager::FoulManager() {
	reset();
}

void FoulManager::reset() {
	status.setFoulStatus(false);
}



void FoulManager::isHandBallInHole() {
	if (g_sphere[0]->getDisableTurn() == status.getCurrentTurnCount()) {
		g_sphere[0]->enable();
		g_sphere[0]->setPower(0, 0);
		g_sphere[0]->setPosition(0, g_sphere[0]->getPosition().y, 0);
		int i;
		while (true) {
			for (i = 1; i < 16; i++) {
				if (g_sphere[0]->hasIntersected(*g_sphere[i])) {
					g_sphere[0]->setPosition(rand() % 5, g_sphere[0]->getPosition().y, rand() % 5);
					break;
				}
			}
			if (i == 16)
				break;
		}
		status.setFoulStatus(true); 
	}
}


bool FoulManager::isEightBallIn() {
	if (g_sphere[8]->getDisableTurn() != -1 &&
		status.getTurnPlayer()->getNumTakenBall() != 7)
	{
		return true;
	}
	return false;
}

bool FoulManager::isEightBallWithFoul() {
	if (g_sphere[8]->getDisableTurn() != -1 &&
		(status.getFoulStatus() && status.getTurnPlayer()->getNumTakenBall() != 7))
	{
		return true;
	}
	return false;
}

void FoulManager::checkFoul() {
	isHandBallInHole();
}

bool FoulManager::isLose() {
	return (isEightBallIn() || isEightBallWithFoul());
}