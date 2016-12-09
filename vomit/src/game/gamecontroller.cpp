#include <vomitblood.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <new>
using namespace std;

////////////////////// GameController //////////////////////

GameController::GameController()
{
	_isRunning = true;
}

void GameController::init()
{
	try {
		_model = new GameModel();
		_view = new GameView();
	} catch (bad_alloc bad) {
		return;
	}
}

void GameController::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event)) {
		if(event.type == sf::Event::Closed) {
			_isRunning = false;
		}	
	}
}

void GameController::tadpoleCollide()
{
	cmd_t cmd;

	clog << "VIEW:tadpole Collide!" << endl;
	cmd = _model->tadpoleCollide();

	if (cmd.status.gameOver) {
		clog << "MODEL:GAME OVER!" << endl;
		_isRunning = false;
	}
}

void GameController::tadpoleMakeStep()
{
	cmd_t cmd;

	clog << "VIEW:tadpole steps!" << endl;
	cmd = _model->tadpoleMakeStep();

	if (cmd.status.addVelocity) {
		clog << "MODEL:map add velocity!" << endl;
		_view->setSpeed(cmd.value);
	}
	if (cmd.status.addLevel) {
		clog << "MODEL:map add level!" << endl;
	}
}

/*
 * Основной цикл игры
*/
void GameController::startGame()
{
	cmd_t cmd;
	while(_isRunning) {
		
		processEvents();

		cmd = _view->update();

		if (cmd.status.tadpoleCollide)
			tadpoleCollide();
		if (cmd.status.tadpoleStep)
			tadpoleMakeStep();
	}
}

void GameController::dispose() 
{
	delete _model;
	delete _view;
}

GameController::~GameController()
{
}
