#ifndef _MENU_CONTROLLER_
#define _MENU_CONTROLLER_ 1

#include "../acontroller.hpp"
#include "../vomitblood.hpp"

class MenuController : public AController {
	MenuView * _view;
	GameController *_game;
protected:
	void processCommands(cmd_t cmd);
	void processEvents();
public:
	MenuController();
	~MenuController();

	void startMenu();
};

#endif
