#include <vomitblood.hpp>
#include <new>
#include <iostream>
using namespace std;

GameView::GameView() 
{
	try {
		_map = new Map();
		_tadpole = new Tadpole(_map);
	} catch (bad_alloc bad) {
		return;
	}
}

void GameView::newGame()
{
	_map->newMap();
	_map->setVelocity(START_MAP_VELOCITY);
	_tadpole->goToStart();
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
}

void GameView::draw()
{
	window.clear();

	_map->draw();
	window.draw(*_tadpole);

	window.display();
}

/*
 * Метод перерасчёта позиции и столковении
 * значение dt - секунды (float)
*/
cmd_t GameView::update(sf::Time dt)
{
	cmd_t retCmd;
	retCmd.clear();

	static int framesPerStep = 60;

	framesPerStep--;

	if(!framesPerStep) {
		retCmd.tadpoleStep = 1;
		framesPerStep = 60;
	}

	_map->update(dt);
	_tadpole->updatePosition(dt);

	if(_tadpole->isCollide())
		retCmd.tadpoleCollide = 1;

	return retCmd;
}

