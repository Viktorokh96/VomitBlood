#include <vomitblood.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <new>
using namespace std;

////////////////////// GameMenuController //////////////////////

GameMenuController::GameMenuController()
{
	_view = NULL;

	try {
		_view = new GameMenuView();
	} catch (bad_alloc bad) {
		return;
	}
}

void GameMenuController::setGameStatus(gameStatus stat)
{
	if(_view)
		_view->setGameStatus(stat);
}

void GameMenuController::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event)) {
		if(event.type == sf::Event::Closed) {
			window.close();
			stopManage();
		}	
	}
}

void GameMenuController::setPoints(unsigned p)
{
	if(_view)
		_view->setPoints(p);
}

void GameMenuController::processCommands(cmd_t cmd)
{
	retCmd = cmd;
	if(retCmd.exitGame || retCmd.restart || retCmd.resume)
		stopManage();
}

cmd_t GameMenuController::startMenu()
{
	retCmd.clear();

	if(!_view)
		return retCmd;

	manage(*_view);

	return retCmd;
}

GameMenuController::~GameMenuController()
{
	delete _view;
}

////////////////////// GameController //////////////////////

GameController::GameController()
{
	_model = NULL;
	_view = NULL;
	_menu = NULL;

	// Создаём новый игровой мир, для начала игры
	createNewGame();
}

void GameController::createNewGame()
{
	if(_model) delete _model;
	if(_view) delete _view;
	if(_menu) delete _menu;

	try {
		_model = new GameModel();
		_view = new GameView();
		_menu = new GameMenuController();
	} catch (bad_alloc bad) {
		return;
	}
	
	// Установка постоянного значения длительности кадра
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);

	_view->setFrameTime(timePerFrame);
}

void GameController::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event)) {
		if(event.type == sf::Event::Closed) {
			window.close();
			stopManage();
		}	

		if(event.type == sf::Event::KeyPressed) {
			if(event.key.code == sf::Keyboard::Escape) {
				_menu->setGameStatus(gamePause);
				stopManage();
			}	
		}
	}
}

void GameController::tadpoleCollide()
{
	cmd_t cmd;

	clog << "VIEW:tadpole Collide!" << endl;
	cmd = _model->tadpoleCollide();

	if (cmd.gameOver) {
		clog << "MODEL:GAME OVER!" << endl;
		_menu->setGameStatus(gameOver);
		_menu->setPoints(_model->getPoints());
		stopManage();
	}
}

void GameController::tadpoleMakeStep()
{
	cmd_t cmd;

	clog << "VIEW:tadpole steps!" << endl;
	cmd = _model->tadpoleMakeStep();

	if (cmd.addVelocity) {
		clog << "MODEL:map add velocity!" << endl;
		_view->addVelocity();
	}
	if (cmd.addLevel) {
		clog << "MODEL:map add level!" << endl;
		_view->addLevel();
	}
}

void GameController::processCommands(cmd_t cmd)
{
	if (cmd.tadpoleCollide)
		tadpoleCollide();
	if (cmd.tadpoleStep)
		tadpoleMakeStep();
}

void GameController::startGame()
{
	cmd_t cmd;

	while (window.isOpen()) {

		manage(*_view);

		cmd = _menu->startMenu();

		if(cmd.resume)
			continue;
		if(cmd.restart)
			createNewGame();
		if(cmd.exitGame)
			break;
	} 
}

GameController::~GameController()
{
	delete _model;
	delete _view;
	delete _menu;
}
