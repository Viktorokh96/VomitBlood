/*
 * Визуализатор частей карты PartOfMap
 * Автор: Охотников Виктор <viktorokh96@mail.ru>
 * Дата: 19 декабря 2016 г. 19:08
 */

#include <vomitblood.hpp>
#include <iostream>
using namespace std;


/////////////////////////////////// Obstacle ////////////////////////////////////

Obstacle::Obstacle()
{
	sf::RectangleShape r(sf::Vector2f(120, 40));
	for(unsigned i = 0; i < r.getPointCount(); ++i)
		_vertices.append(sf::Vector2f(r.getPoint(i)));
	update();
}

Obstacle::~Obstacle()
{
	_vertices.clear();
}

void Obstacle::setInMapPosition(sf::Vector2f pos)
{
	_inMapPosition = pos;
}

void Obstacle::setInMapPosition(float x, float y)
{
	sf::Vector2f position(x,y);
	setInMapPosition(position);
}

sf::Vector2f Obstacle::getInMapPosition()
{
	return _inMapPosition;
}

std::size_t Obstacle::getPointCount() const
{
	return _vertices.getVertexCount();
}

Vector2f Obstacle::getPoint(std::size_t index) const
{
	return _vertices[index].position;
}

/////////////////////////////////// PartOfMap ////////////////////////////////////

PartOfMap::PartOfMap(float position) 
{
	_position = position;
	_obstacles.clear();

	Obstacle ob1, ob2, ob3, ob4, ob5;
	ob1.setInMapPosition(0, 0);
	ob2.setInMapPosition(WINDOW_WIDTH-120, 0);
	ob3.setInMapPosition(0,PART_HEIGHT-40);
	ob4.setInMapPosition(WINDOW_WIDTH-120,PART_HEIGHT-40);
	ob5.setInMapPosition((WINDOW_WIDTH/2)-60,(PART_HEIGHT/2)-40);

	_obstacles.push_back(ob1);
	_obstacles.push_back(ob2);
	_obstacles.push_back(ob3);
	_obstacles.push_back(ob4);
	_obstacles.push_back(ob5);

	updateObstacles();
}

PartOfMap::~PartOfMap()
{
	_obstacles.clear();
}

void PartOfMap::updateObstacles()
{
	std::vector<Obstacle>::iterator it = _obstacles.begin();
	while(it != _obstacles.end()) {

		it->setPosition
		(
			it->getInMapPosition().x,
			_position + it->getInMapPosition().y
		);

		it++;
	}
}

void PartOfMap::setPosition(float position)
{
	_position = position;

	updateObstacles();
}

float PartOfMap::getPosition()
{
	return _position;
}

void PartOfMap::draw() const
{
	std::vector<Obstacle>::const_iterator it = _obstacles.begin();
	while(it != _obstacles.end()) {
		window.draw(*it);
		it++;
	}
}

///////////////////////////////////глобальные данные////////////////////////////////////

PartOfMap *part;

sf::View view;

bool _isMovingUp = false;
bool _isMovingDown = false;
int delta = 0;

char *pathToPart;

int initMap()
{
	part = new PartOfMap(WINDOW_HEIGHT - PART_HEIGHT);

	return 0;
}

void updatePart()
{
	delete part;

	part = new PartOfMap(WINDOW_HEIGHT - PART_HEIGHT);

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

	if (argc < 2)
	{
		cout << "Использование:" << argv[0] << " + файл с описанием карты" << endl;
		return -1;
	}

	pathToPart = argv[1];

	if(initMap() < 0) {
		cerr << "Ошибка инициализации карты! Сворачиваюсь!" << endl;
		return -2;
	}

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

	return 0;
}
