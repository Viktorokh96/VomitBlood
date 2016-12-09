#include <vomitblood.hpp>
#include <iostream>
using namespace std;

#define VELOCITY_ADD_STEPS 	100
#define LEVEL_ADD_STEPS 	1000

GameModel::GameModel()
{
	_stepsCounter = 0;
}

cmd_t GameModel::tadpoleMakeStep()
{
	cmd_t retCmd;
	retCmd.clear();

	_stepsCounter++;

	if ((_stepsCounter % (VELOCITY_ADD_STEPS-1)) == 0) {
		retCmd.status.addVelocity = 1;
		retCmd.value = 1;
	}

	if (_stepsCounter == (LEVEL_ADD_STEPS-1)) {
		retCmd.status.addLevel = 1;
		_stepsCounter = 0;
	}

	return retCmd;
}

cmd_t GameModel::tadpoleCollide()
{
	cmd_t retCmd;
	retCmd.clear();

	retCmd.status.gameOver = 1;

	return retCmd;
}

GameModel::~GameModel()
{
}
