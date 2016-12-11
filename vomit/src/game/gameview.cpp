#include <vomitblood.hpp>
#include <iostream>
using namespace std;

GameView::GameView() 
{
}

GameView::~GameView()
{
}

void GameView::addVelocity()
{
}

void GameView::addLevel()
{
}

void GameView::render()
{
}

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

	int r = rand();
	/* Тестовая эмуляция ошибки игрока */
	if((r % 332394) == 0)
		retCmd.tadpoleCollide = 1;

	window.clear();
	window.display();

	return retCmd;
}

void GameView::newGame()
{
}
