#ifndef _GAME_CONTROLLER
#define _GAME_CONTROLLER 1

#include "../icontroller.hpp" 
#include "model.hpp" 

class GameController : public IController {
	GameModel * _model;
	// представление
public:
	GameController();
	~GameController() {} 
	void manage();
};

#endif
