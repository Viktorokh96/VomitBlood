#ifndef _GAME_MODEL
#define _GAME_MODEL 1

class GameModel {
public:
	GameModel();
	
	cmd_t tadpoleMakeStep();
	cmd_t tadpoleCollide();
};

#endif
