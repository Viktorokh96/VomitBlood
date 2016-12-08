#include <vomitblood.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

////////////////////// GameController //////////////////////

GameController::GameController()
{
	_model = new GameModel();
	_view = new GameView();
}

/*
 * Основной цикл игры
*/
void GameController::startGame()
{
	cmd_t cmd;
	bool isRunning = true;

	while(isRunning) {
		cmd = _view->update();
	}
}

GameController::~GameController() 
{
	delete _model;
	delete _view;
}
