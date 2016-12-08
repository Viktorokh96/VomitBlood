#include <vomitblood.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <new>
using namespace std;

////////////////////// GameController //////////////////////

GameController::GameController()
{
	try {
		_model = new GameModel();
		_view = new GameView();
	} catch (bad_alloc bad) {
		return;
	}
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
