#ifndef _STATUS_
#define _STATUS_
#include <exception>
#include <algorithm>
#include <vector>
#define noexcept throw ()
#define BLANK_BLOCK {}

using std::vector;
using std::exception;


class Status
{
private:
	unsigned int numStage;
	unsigned int numFinalStage;
	bool isGameOver;

public:
	Status();

	void setNumStage(unsigned int numStage);
	unsigned int getNumStage() const noexcept;
	void setNumFinalStage();
	unsigned int getNumFinalStage() const noexcept;

	void setIsGameOver(bool isGameOver);
	bool getIsGameOver() const noexcept;
};

#endif