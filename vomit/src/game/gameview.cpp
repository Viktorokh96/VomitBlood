#include <vomitblood.hpp>
#include <iostream>
using namespace std;

GameView::GameView() 
{
}

GameView::~GameView()
{
}

void GameView::setSpeed(int speed)
{
}

void GameView::setLevel(int level)
{
}

cmd_t GameView::update()
{
	cmd_t retCmd;
	retCmd.clear();

	static int framesPerStep = 60;

	framesPerStep--;

	if(!framesPerStep) {
		retCmd.status.tadpoleStep = 1;
		framesPerStep = 60;
	}

	int r = rand();
	/* Тестовая эмуляция ошибки игрока */
	if((r % 332394) == 0)
		retCmd.status.tadpoleCollide = 1;

	window.clear();
	window.display();

	return retCmd;
}

void GameView::newGame()
{
}
