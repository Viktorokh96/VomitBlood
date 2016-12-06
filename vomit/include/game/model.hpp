#ifndef _GAME_MODEL
#define _GAME_MODEL 1

typedef int cmd_t;

class GameModel {
public:
	GameModel();
	
	cmd_t tadpoleMakeStep();
	cmd_t tadpoleCollide();
};

#endif
