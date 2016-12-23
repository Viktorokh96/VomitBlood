/*
 * Визуализатор частей карты PartOfMap
 * Автор: Охотников Виктор <viktorokh96@mail.ru>
 * Дата: 19 декабря 2016 г. 19:08
 */

#include <vomitblood.hpp>
#include <set>
#include <iostream>

#define SEGMENTS_PER_CURVE 25

using namespace std;

ObstacleLoader *obstLoader;
///////////////////////////////////глобальные данные////////////////////////////////////

PartOfMap *part;

sf::View view;

bool _isMovingUp = false;
bool _isMovingDown = false;
int delta = 0;

int initMap()
{
	obstLoader = new ObstacleLoader();
	
	delete obstLoader;
	/*vector<Obstacle *> ob;	
	ob.clear();

	Obstacle *o;
	Obstacle *o1;
	vector<sf::Vector2f> vertices;
	vertices.clear();

	ifstream obsFile("obstacle.obs");
	if(!obsFile)
       	{
		cout << "Can't open file with obstacles!";
		return -1;
	}

	vertices_t obsVertices = getObtacleVertices(obsFile);

	o = new Obstacle(obsVertices);
	o1 = new Obstacle(obsVertices);

	o->setInMapPosition(0, PART_HEIGHT/2);
	o1->rotate(180);
	o1->setInMapPosition(WINDOW_WIDTH, PART_HEIGHT/2);
	ob.push_back(o);
	ob.push_back(o1);

	part = new PartOfMap(ob);
	part->setPosition(WINDOW_HEIGHT - PART_HEIGHT);
	*/

	return 0;
}

void updatePart()
{
	delete part;

	initMap();

	clog << "Part is updated!" << endl;
}

void handleInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
		_isMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		_isMovingDown = isPressed;
	else if (key == sf::Keyboard::U && (!isPressed))
		updatePart();
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

sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "VomitBlood", sf::Style::Titlebar | sf::Style::Close);

int main(int argc, char *argv[])
{
	if(initMap() < 0) {
		cerr << "Ошибка инициализации карты! Сворачиваюсь!" << endl;
		return -2;
	}
/*
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

		window.clear();
		part->draw();
		window.display();	
	}
*/
	return 0;
}
