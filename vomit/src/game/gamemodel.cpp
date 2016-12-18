#include <vomitblood.hpp>
#include <iostream>
#include <cmath>
using namespace std;

GameModel::GameModel()
{
	_stepsCounter = 0;
	_points = 0;
}

cmd_t GameModel::tadpoleMakeStep()
{
	cmd_t retCmd;
	retCmd.clear();

	_stepsCounter++;

	/* Функция расчёта очков */
	_points = (_stepsCounter*_stepsCounter)/(1 + (sqrt(_stepsCounter)));

	if ((_stepsCounter % (VELOCITY_ADD_STEPS-1)) == 0) {
		retCmd.addVelocity = 1;
	}

	if ((_stepsCounter % (LEVEL_ADD_STEPS)) == 0 ) {
		retCmd.addLevel = 1;
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

unsigned long GameModel::getPoints()
{
	return _points;
}

void GameModel::savePoints()
{
}

GameModel::~GameModel()
{
}
