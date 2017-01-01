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
	if (retCmd.exitGame || retCmd.restart || 
	retCmd.resume)
		stopManage();
}

cmd_t GameMenuController::startMenu()
{
	retCmd.clear();

	if(!_view)
		return retCmd;

	manage(*_view, window);

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

/*
 * Обработка событий пришедших с пользователя
 * в состоянии "Игра". В основном события, 
 * описанные здесь не влияют на логику работы
 * игры. Здесь обрабатываются, только внешние
 * по отношению к игре события, будь это пауза
 * или закрытие окна
*/
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

	cmd = _model->tadpoleCollide();

	if (cmd.gameOver) {
		_menu->setGameStatus(gameOver);
		_menu->setPoints(_model->getPoints());
		stopManage();
	}
}

void GameController::tadpoleMakeStep()
{
	cmd_t cmd;

	cmd = _model->tadpoleMakeStep(_view->getMapVelocity());

	if (cmd.addVelocity) {
		_view->addVelocity();
	}
	if (cmd.addLevel) {
		_view->addLevel();
	}

	unsigned points = _model->getPoints();
	_view->setPoints(points);
}

/*
 * Обработка команд, пришедних с представления игры.
 * Здесь происходит реагирование игры на правила,
 * установленные моделью
*/
void GameController::processCommands(cmd_t cmd)
{
	if (cmd.tadpoleCollide)
		tadpoleCollide();
	if (cmd.tadpoleStep)
		tadpoleMakeStep();
}

/*
 * Запуск игры
 * Реализуется переход в состояние "Игра"
 * Выход из этого состояния возможен только
 * по команде пользователя ( нажатие кнопки выход )
*/
void GameController::startGame()
{
	cmd_t cmd;

	while (window.isOpen()) {

		manage(*_view, window);

		cmd = _menu->startMenu();

		if(cmd.resume) {
			_view->makeTadpoleSleep();
			continue;
		}
		if(cmd.restart) {
			createNewGame();
		}
		if(cmd.exitGame) {
			break;
		}
	} 
}

GameController::~GameController()
{
	delete _model;
	delete _view;
	delete _menu;
}
