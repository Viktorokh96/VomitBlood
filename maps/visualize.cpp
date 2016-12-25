/*
 * Визуализатор частей карты PartOfMap
 * Автор: Охотников Виктор <viktorokh96@mail.ru>
 * Дата: 19 декабря 2016 г. 19:08
 */

#include <vomitblood.hpp>
#include <set>
#include <iostream>
#include <SFML/Window/ContextSettings.hpp>

#define SEGMENTS_PER_CURVE 25

using namespace std;

ObstacleLoader *obstLoader;
PartOfMapLoader *partsLoader;
VisualizeHolder visualizeHolder(resourceHolder);

sf::ContextSettings settings;
///////////////////////////////////глобальные данные////////////////////////////////////

PartOfMap part;

sf::View view;

bool _isMovingUp = false;
bool _isMovingDown = false;
int delta = 0;

int initMap()
{
	obstLoader = new ObstacleLoader();
	delete obstLoader;

	partsLoader = new PartOfMapLoader();
	delete partsLoader;

	part = visualizeHolder.getCurrentPartOfMap();
	part.setPosition(WINDOW_HEIGHT - PART_HEIGHT);

	return 0;
}

void updatePart()
{
	initMap();

	clog << "Part is updated!" << endl;
}

void handleInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
		_isMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		_isMovingDown = isPressed;
	else if (key == sf::Keyboard::D)
		if (!isPressed) visualizeHolder.choiceNextPartOfMap();
	else if (key == sf::Keyboard::A)
		if (!isPressed) visualizeHolder.choicePastPartOfMap();
}

void update()
{
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	float scrollSpeed = 30.f;

	view = window.getView();

	if(((view.getCenter().y > WINDOW_HEIGHT) && _isMovingDown)
	|| ((view.getCenter().y < -WINDOW_HEIGHT) && _isMovingUp))
		return;

	if(_isMovingUp)
	{
		view.move(0.f, -scrollSpeed * timePerFrame.asSeconds());
	}
	else if(_isMovingDown)
	{
		view.move(0.f, scrollSpeed * timePerFrame.asSeconds());
	}
	
	window.setView(view);
}

sf::RenderWindow window;

// Для очерчивания границ карты
VertexArray bounds (sf::Lines, 4);

int main(int argc, char *argv[])
{
	if(initMap() < 0) {
		cerr << "Ошибка инициализации карты! Сворачиваюсь!" << endl;
		return -2;
	}

	settings.antialiasingLevel = 2;
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
		"VomitBlood", sf::Style::Titlebar | sf::Style::Close, settings);

	bounds[0].position = sf::Vector2f(0, WINDOW_HEIGHT-PART_HEIGHT);
	bounds[1].position = sf::Vector2f(WINDOW_WIDTH+1, WINDOW_HEIGHT-PART_HEIGHT);
	bounds[2].position = sf::Vector2f(WINDOW_WIDTH+1, WINDOW_HEIGHT);
	bounds[3].position = sf::Vector2f(0, WINDOW_HEIGHT);

	sf::Clock timer;

	while(window.isOpen())
	{
		sf::Event event;


		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::KeyPressed)
			{
				handleInput(event.key.code, true);
			}
			else if(event.type == sf::Event::KeyReleased)
			{
				handleInput(event.key.code, false);
			}
			else if(event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		update();

		if(timer.getElapsedTime().asSeconds() > 1.f) {
			updatePart();
			timer.restart();
		}

		window.clear();
		part.draw();
		window.draw(bounds);
		window.display();	
	}

	return 0;
}
