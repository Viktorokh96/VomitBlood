#include <vomitblood.hpp>
#include <iostream>
using namespace std;

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
		retCmd.addVelocity = 1;
	}

	if (_stepsCounter == (LEVEL_ADD_STEPS-1)) {
		retCmd.addLevel = 1;
		_stepsCounter = 0;
	}

	return retCmd;
}

cmd_t GameModel::tadpoleCollide()
{
	cmd_t retCmd;
	retCmd.clear();

	retCmd.gameOver = 1;

	return retCmd;
}

GameModel::~GameModel()
{
}
