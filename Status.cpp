#include "Status.h"
#include <algorithm>

using std::find_if;
using std::exception;

Status::Status() {
	this->numStage = 1;
	this->isGameOver = false;
}

void Status::setNumStage(unsigned int numStage) {
	this->numStage = numStage;
}

unsigned int Status::getNumStage() const noexcept {
	return numStage;
}


void Status::setIsGameOver(bool isGameOver) {
	this->isGameOver = isGameOver;
}
bool Status::getIsGameOver() const noexcept {
	return isGameOver;
}