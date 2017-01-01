#ifndef _GAME_MODEL
#define _GAME_MODEL 1

#include "../cmd.hpp"

class GameModel {
	unsigned long int _stepsCounter;
	unsigned long int _points;
public:
	GameModel();
	~GameModel();

	cmd_t tadpoleMakeStep(float mapSpeed);
	cmd_t tadpoleCollide();
	unsigned long getPoints();
	void savePoints();
};

#endif
