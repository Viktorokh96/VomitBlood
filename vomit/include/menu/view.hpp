#ifndef _MENU_VIEW_
#define _MENU_VIEW_ 1

#include "../cmd.hpp"
#include "../iview.hpp"

#include <SFML/Graphics.hpp>
#include <map>
using namespace std;

class Button : public sf::CircleShape {
public:
	Button();
	Button(sf::Vector2f pos, float radius);
	~Button();

	bool isClicked();
};

class MenuView : public IView {
	map<char, Button> _buttons;	
	typedef map<char, Button>::iterator _buttonIter;
public:
	MenuView();
	~MenuView();

	cmd_t update();
	void draw();
};

#endif
