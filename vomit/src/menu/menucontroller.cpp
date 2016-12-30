#include <vomitblood.hpp>
#include <new>
#include <iostream>
using namespace std;

MenuController::MenuController()
{
	try {
		_view = new MenuView();
	} catch (bad_alloc bad) {
		return;
	}
}

void MenuController::processCommands(cmd_t cmd)
{
	if(cmd.startGame) {
		_game = new GameController();
		_game->startGame();		
		delete _game;
	} 
	else if(cmd.exitGame){
		stopManage();
	}
}

void MenuController::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event)) {
		if(event.type == sf::Event::Closed) {
			stopManage();
			window.close();
		}	
	}
}

void MenuController::startMenu()
{
	if(!_view)
		return;

	manage(*_view, window);
}

MenuController::~MenuController()
{
	delete _view;
}
