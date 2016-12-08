#ifndef _GAME_CONTROLLER
#define _GAME_CONTROLLER 1

#include "../icontroller.hpp" 
#include "model.hpp" 
#include "view.hpp" 

/*
 * Контроллер игры
 * Главный цикл находится здесь
*/

class GameController : public IController {
	GameModel * _model;
	GameView *_view;

	void tadpoleMakeStep();
	void tadpoleCollide();
	void pause();
public:
	GameController();
	~GameController();

	void startGame();
};

#endif
