#ifndef _GAME_CONTROLLER
#define _GAME_CONTROLLER 1

#include "../cmd.hpp" 
#include "../icontroller.hpp" 
#include "model.hpp" 
#include "view.hpp" 

class GameMenuController : public IController {
	GameMenuView *_view;
	bool _isRunning;
	void processEvents();
public:
	GameMenuController();
	~GameMenuController();

	void setGameStatus(gameStatus);
	void init();
	void dispose();

	void setPoints(unsigned);

	cmd_t startMenu();
};

/*
 * Контроллер игры
 * Главный игровой цикл находится здесь
*/

class GameController : public IController {
	GameModel * _model;
	GameView *_view;
	GameMenuController *_menu;
	bool _gameLoopisRunning;

	void processEvents();
	void createNewGame();
	void tadpoleMakeStep();
	void tadpoleCollide();
	void mainGameLoop();
public:
	GameController();
	~GameController();

	void init();
	void dispose();

	void startGame();
};

#endif
