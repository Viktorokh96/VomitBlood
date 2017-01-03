#include <cmd.hpp>
#include <vomitblood.hpp>
#include <iostream>
using namespace std;

#define BUTT_RAD 50

/////////////////////////////// Button ///////////////////////////////

Button::Button()
{
}

Button::Button(sf::Vector2f pos, float radius)
: sf::CircleShape(radius)
{
	setPosition(pos);	
}

bool Button::isClicked()
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

	return (getGlobalBounds().contains(
				static_cast<float>(mousePosition.x), 
				static_cast<float>(mousePosition.y)) &&
			sf::Mouse::isButtonPressed(sf::Mouse::Left));
}

Button::~Button()
{
}

/////////////////////////////// MenuView ///////////////////////////////

static sf::Font font;
static sf::Text promt;
static sf::Sprite backScreen;

MenuView::MenuView()
{
	sf::Texture *startTexture;
	sf::Texture *screenTexture;
	sf::Texture *endTexture;

	_buttons.clear();

	startTexture = resourceHolder.getTexture("startButton");
	screenTexture = resourceHolder.getTexture("background");
	endTexture = resourceHolder.getTexture("exitButton");

	if(!font.loadFromFile("media/menu/FEASFBRG.TTF"))
	{
		cerr << "MenuViuew: ERROR LOADING FONT!" << endl;
	}

	backScreen = sf::Sprite(*screenTexture);
	backScreen.setTextureRect(sf::IntRect(0, 0, 800, 644));
	backScreen.setPosition(0,28);

	if(startTexture)
		startTexture->setSmooth(true);
	if(endTexture)
		endTexture->setSmooth(true);
	if(screenTexture)
		screenTexture->setSmooth(true);

	promt.setFont(font);
	promt.setCharacterSize(120);
	promt.setFillColor(sf::Color::Red);
	promt.setStyle(sf::Text::Bold);
	promt.setString("Vomit Blood");

	sf::FloatRect b = promt.getLocalBounds();
	promt.setPosition((WINDOW_WIDTH/2) - (b.width/2), 2*(WINDOW_HEIGHT/15));

	Button button(sf::Vector2f((WINDOW_WIDTH/2)-BUTT_RAD, 
				   6*(WINDOW_HEIGHT/15)), BUTT_RAD);

	button.setTextureRect(sf::IntRect(18,18, 300, 300));

	if(startTexture)
		button.setTexture(startTexture);

	// start button
	_buttons.insert(make_pair('s', button));

	if(endTexture)
		button.setTexture(endTexture);

	button.setPosition(sf::Vector2f((WINDOW_WIDTH/2)-BUTT_RAD, 
					9*(WINDOW_HEIGHT/15)));
	// end game button
	_buttons.insert(make_pair('e', button));
}

cmd_t MenuView::update()
{
	cmd_t retCmd;
	retCmd.clear();

	_buttonIter iter = _buttons.begin();

	while(iter != _buttons.end()) {
		if(((iter->second).isClicked())) {
			switch(iter->first) {
				case 's':
					retCmd.startGame = 1;
					break;
				case 'e':
					retCmd.exitGame = 1;
					break;
			}
		}

		iter++;
	}

	return retCmd;
}

void MenuView::draw()
{
	window.clear();

	window.draw(backScreen);

	_buttonIter iter = _buttons.begin();
	while(iter != _buttons.end()) {
		window.draw(iter->second);
		iter++;
	}

	window.draw(promt);

	window.display();
}

MenuView::~MenuView()
{
	_buttons.clear();
}
