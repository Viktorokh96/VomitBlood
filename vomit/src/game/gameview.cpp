#include <cmd.hpp>
#include <vomitblood.hpp>
#include <new>
#include <cmath>
#include <iostream>
#include <cstdlib>
using namespace std;

////////////////////// GameMenuView //////////////////////

static sf::Font font;

GameMenuView::GameMenuView()
{
	if (!font.loadFromFile("media/FEASFBRG.TTF")) {
		clog << "ERROR!" << endl;
	}

	_points = 0;
}

cmd_t GameMenuView::update()
{
	cmd_t retCmd;
	retCmd.clear();

	if(_status == windowClosed)
		retCmd.exitGame = 1;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		retCmd.exitGame = 1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
		retCmd.restart = 1;

	if(_status == gamePause) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
			retCmd.resume = 1;
	}

	return retCmd;
}

void GameMenuView::showStatus()
{
	sf::Text status;
	status.setFont(font);
	status.setCharacterSize(60);
	status.setColor(sf::Color::Red);
	status.setStyle(sf::Text::Bold);

	if(_status == gamePause)
		status.setString("Pause");
	else
		status.setString("You died!");

	sf::FloatRect b = status.getLocalBounds();

	status.setPosition((WINDOW_WIDTH/2) - (b.width/2), (WINDOW_HEIGHT/2) - b.height);

	window.draw(status);
}

void GameMenuView::showPoints()
{
	sf::Text points;
	points.setFont(font);
	points.setCharacterSize(30);
	points.setColor(sf::Color::Red);
	points.setStyle(sf::Text::Bold);

	char score[64];
	sprintf(score,"Your score is %ld",_points);

	points.setString(score);

	sf::FloatRect b = points.getLocalBounds();

	points.setPosition((WINDOW_WIDTH/2) - (b.width/2), (WINDOW_HEIGHT/2) + (b.height));

	window.draw(points);
}

void GameMenuView::setPoints(unsigned long p)
{
	_points = p;
}

void GameMenuView::draw()
{
	window.clear();

	showStatus();
	if(_status == gameOver)
		showPoints();


	window.display();
}

void GameMenuView::setGameStatus(gameStatus stat)
{
	_status = stat;
}

GameMenuView::~GameMenuView()
{
}

////////////////////// GameView //////////////////////

GameView::GameView() 
{
	try {
		_map = new Map();
		_tadpole = new Tadpole(_map);
	} catch (bad_alloc bad) {
		return;
	}

	newGame();
}

void GameView::newGame()
{
	_map->newMap();
	_map->setVelocity(START_MAP_VELOCITY);
	_map->setLevel(START_MAP_LEVEL);
	_tadpole->goToStart();
	_tadpoleClicked = false;
}

GameView::~GameView()
{
	delete _map;
	delete _tadpole;
}

void GameView::addVelocity()
{
	_map->setVelocity(_map->getVelocity()+VELOCITY_INCREMENT);
}

void GameView::addLevel()
{
	_map->setLevel(_map->getLevel()+1);
}

void GameView::draw()
{
	window.clear();

	_map->draw();
	window.draw(*_tadpole);

	window.display();
}

void GameView::setPoints(unsigned long p)
{
	_map->setPoints(p);
}

/*
 * Метод перерасчёта позиции и столковении
 * значение dt - секунды (float)
*/
cmd_t GameView::update()
{
	cmd_t retCmd;
	retCmd.clear();

	if (_tadpoleClicked) {
		static int updatesPerStep = UPDATES_PER_STEP;

		updatesPerStep--;

		if(!updatesPerStep) {
			retCmd.tadpoleStep = 1;
			updatesPerStep = UPDATES_PER_STEP;
		}

		_map->update(_dt);
		_tadpole->update(_dt);

		if(_tadpole->isCollide())
			retCmd.tadpoleCollide = 1;
	} else {
		if(_tadpole->isClicked()) {
			_tadpole->setScale(1.f,1.f);
			_tadpoleClicked = true;
		}

		/* Мерцание головастиком, для привлечения внимания игрока */
		if(!_tadpoleClicked) {
			static double a = 0.f;	
			_tadpole->setScale(abs(cos(a)), abs(cos(a)));
			a += 0.04f;
			if(a > 1000) a = 0;
		}
	}

	return retCmd;
}

void GameView::setFrameTime(sf::Time dt)
{
	_dt = dt;
}

