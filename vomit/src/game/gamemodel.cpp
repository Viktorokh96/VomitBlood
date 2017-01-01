#include <vomitblood.hpp>
#include <iostream>
#include <cmath>
using namespace std;

GameModel::GameModel()
{
	_stepsCounter = 0;
	_points = 0;
}

cmd_t GameModel::tadpoleMakeStep(float mapSpeed)
{
	cmd_t retCmd;
	retCmd.clear();
	static long stepSumForAddVel = 0;
	static long stepSumForAddLevel = 0;

	unsigned stepIncrement = (mapSpeed / 100);
	_stepsCounter += stepIncrement;

	/* Функция расчёта очков */
	_points = (_stepsCounter*_stepsCounter)/(1 + 1000*(sqrt(_stepsCounter)));

	stepSumForAddVel += stepIncrement;
	if (stepSumForAddVel >= VELOCITY_ADD_STEPS - 1)
	{
		retCmd.addVelocity = 1;
		stepSumForAddVel = 0;
	}

	stepSumForAddLevel += stepIncrement;
	if (stepSumForAddLevel >= LEVEL_ADD_STEPS - 1)
	{
		retCmd.addLevel = 1;
		stepSumForAddLevel = 0;
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
