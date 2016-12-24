#ifndef _GAME_CONTROLLER
#define _GAME_CONTROLLER 1

#include "../cmd.hpp" 
#include "../acontroller.hpp" 
#include "../menu/view.hpp" 
#include "model.hpp" 
#include "view.hpp" 

class GameMenuController : public AController {
	GameMenuView *_view;
	cmd_t retCmd;
protected:
	void processCommands(cmd_t cmd);
	void processEvents();
public:
	GameMenuController();
	~GameMenuController();

	void setGameStatus(gameStatus);

	void setPoints(unsigned);

	cmd_t startMenu();
};

/*
 * Контроллер игры
 * Главный игровой цикл находится здесь
*/

class GameController : public AController {
	GameModel * _model;
	GameView *_view;
	GameMenuController *_menu;

	void createNewGame();
	void tadpoleMakeStep();
	void tadpoleCollide();
	void mainGameLoop();
protected:
	void processCommands(cmd_t cmd);
	void processEvents();
public:
	GameController();
	~GameController();

	void startGame();
};

#endif
