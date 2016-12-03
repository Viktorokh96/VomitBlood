#ifndef _GAME_CONTROLLER
#define _GAME_CONTROLLER 1

#include "vomitcontroller.hpp" 
#include "../model/gamemodel.hpp" 

class GameController : public AbstractController {
	GameModelFacade * const _model;
public:
	GameController( GameModelFacade *model );
	~GameController() {} 
	void manage();
};

#endif
