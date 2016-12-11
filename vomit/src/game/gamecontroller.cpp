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

	// Создаём новый игровой мир, для начала игры
	_view->newGame();
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

	if (cmd.gameOver) {
		clog << "MODEL:GAME OVER!" << endl;
		_isRunning = false;
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
void GameController::startGame()
{
	// Установка постоянного значения длительности кадра
	sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

	// Инициализация таймера
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	cmd_t cmd;
	while(_isRunning) {
		
		// Обработка событий, пришедших от пользователя
		processEvents();

		// Узнаём сколько времени прошло с окончания предыдущей итерации просчёта
		// И заодно перезапускаем таймер для нового подсчёта
		timeSinceLastUpdate += clock.restart();

		// Если с окончания предыдущей итерации прошло много времени для
		// игрового движка, то наверстываем упущенное ( убираем лаги )
		while (timeSinceLastUpdate > TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();

			// Производим новый расчёт положений и столкновений объектов игры
			cmd = _view->update(TimePerFrame);

			if (cmd.tadpoleCollide)
				tadpoleCollide();
			if (cmd.tadpoleStep)
				tadpoleMakeStep();
		}
		
		// Производим рендер игрового поля
		_view->draw();
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
