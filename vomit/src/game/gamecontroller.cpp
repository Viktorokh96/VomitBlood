#include <vomitblood.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <new>
using namespace std;

////////////////////// GameMenuController //////////////////////

GameMenuController::GameMenuController()
{
	_view = NULL;
}

void GameMenuController::setGameStatus(gameStatus stat)
{
	if(_view)
		_view->setGameStatus(stat);
}

void GameMenuController::init()
{
	try {
		_view = new GameMenuView();
	} catch (bad_alloc bad) {
		return;
	}
}

void GameMenuController::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event)) {
		if(event.type == sf::Event::Closed) {
			window.close();
			_isRunning = false;
		}	
	}
}

void GameMenuController::setPoints(unsigned p)
{
	if(_view)
		_view->setPoints(p);
}

void GameMenuController::dispose()
{
	delete _view;
}

cmd_t GameMenuController::startMenu()
{
	cmd_t retCmd;
	retCmd.clear();

	if(!_view)
		return retCmd;

	// Установка постоянного значения длительности кадра
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);

	// Инициализация таймера
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	_isRunning = true;

	while(_isRunning) {
		
		// Обработка событий, пришедших от пользователя
		processEvents();

		// Узнаём сколько времени прошло с окончания предыдущей итерации просчёта
		// И заодно перезапускаем таймер для нового подсчёта
		timeSinceLastUpdate += clock.restart();

		while (timeSinceLastUpdate > timePerFrame) {
			timeSinceLastUpdate -= timePerFrame;

			processEvents();

			retCmd = _view->update();
			
			if(retCmd.exitGame || retCmd.restart || retCmd.resume)
				_isRunning = false;
		}
		
		// Производим рендер меню
		_view->draw();
	}

	return retCmd;
}

GameMenuController::~GameMenuController()
{
}

////////////////////// GameController //////////////////////

GameController::GameController()
{
	_model = NULL;
	_view = NULL;
}

void GameController::init()
{
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

	_menu->init();
}

void GameController::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event)) {
		if(event.type == sf::Event::Closed) {
			window.close();
			_gameLoopisRunning = false;
		}	

		if(event.type == sf::Event::KeyPressed) {
			if(event.key.code == sf::Keyboard::Escape) {
				_menu->setGameStatus(gamePause);
				_gameLoopisRunning = false;
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
		_gameLoopisRunning = false;
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

/*
 * Основной цикл игры
 *\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
 * TimePerFrame - время выделенное на физический кадр (dt) игры ( 1/60 = 16,6 ms )
 * 	Это значит что просчёт столкновении и передвижении будет производится 60
 * 	раз в секунду на любом компьютере в независимост от его производительности.
 *	Хочу подчернкуть что FPS может гулять в любых пределах, но только не dt!
 *\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
 * timeSinceLastUpdate - время пройденное с последнего обновления
 * 	просчёта игровых передвижений.
 *\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
 * _view->draw() - непосредственный рендер игрового поля. Очень медленная операция.
 * 	Если не использовать нижеприведенный механизм, то физика игры будет сильно
 * 	зависеть от аппаратных ресурсов компьютера, на котором запущена игра, что 
 * 	очень не хорошо.
 * \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
void GameController::mainGameLoop()
{
	if(!(_view || _model)) return;

	cmd_t cmd;

	_gameLoopisRunning = true;

	// Установка постоянного значения длительности кадра
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);

	// Инициализация таймера
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while(_gameLoopisRunning) {
		
		// Обработка событий, пришедших от пользователя
		processEvents();

		// Узнаём сколько времени прошло с окончания предыдущей итерации просчёта
		// И заодно перезапускаем таймер для нового подсчёта
		timeSinceLastUpdate += clock.restart();

		// Если с окончания предыдущей итерации прошло много времени для
		// игрового движка, то наверстываем упущенное ( убираем лаги )
		while (timeSinceLastUpdate > timePerFrame) {
			timeSinceLastUpdate -= timePerFrame;

			processEvents();

			// Производим новый расчёт положений и столкновений объектов игры
			cmd = _view->update(timePerFrame);

			if (cmd.tadpoleCollide)
				tadpoleCollide();
			if (cmd.tadpoleStep)
				tadpoleMakeStep();
		}
		
		// Производим рендер игрового поля
		_view->draw();
	}	
}

void GameController::startGame()
{
	cmd_t cmd;


	while (window.isOpen()) {

		mainGameLoop();

		cmd = _menu->startMenu();
		if(cmd.resume)
			continue;
		if(cmd.restart)
			createNewGame();
		if(cmd.exitGame)
			break;
	} 
}

void GameController::dispose() 
{
	_menu->dispose();

	delete _model;
	delete _view;
	delete _menu;
}

GameController::~GameController()
{
}
