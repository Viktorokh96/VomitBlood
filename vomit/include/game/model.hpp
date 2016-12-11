#ifndef _GAME_MODEL
#define _GAME_MODEL 1

#include "../cmd.hpp"

class GameModel {
	unsigned int _stepsCounter;
public:
	GameModel();
	~GameModel();
	
	cmd_t tadpoleMakeStep();
	cmd_t tadpoleCollide();
};

#endif
