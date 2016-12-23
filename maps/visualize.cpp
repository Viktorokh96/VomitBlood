/*
 * Визуализатор частей карты PartOfMap
 * Автор: Охотников Виктор <viktorokh96@mail.ru>
 * Дата: 19 декабря 2016 г. 19:08
 */

#include <vomitblood.hpp>
#include <fstream>
#include <iostream>

#define SEGMENTS_PER_CURVE 25

using namespace std;

/////////////////////////////////// Obstacle ////////////////////////////////////

Obstacle::Obstacle()
{
	_vertices.clear();
}

Obstacle::Obstacle(std::vector<sf::Vector2f> vertices)
{
	std::vector<sf::Vector2f>::iterator iter = vertices.begin();
	while(iter != vertices.end()) {
		_vertices.append(*iter);
		iter++;
	}
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

PartOfMap::PartOfMap() 
{
	_position = 0.f;
	_obstacles.clear();

	updateObstacles();
}

PartOfMap::PartOfMap(vector<Obstacle *> obstacles)
{
	_obstacles.clear();

	vector<Obstacle *>::iterator iter = obstacles.begin();
	while(iter != obstacles.end()) {
		_obstacles.push_back(*(*iter));
		iter++;
	}

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

char *pathToObstacles;
char *pathToPart;

typedef vector<sf::Vector2f> vertices_t;
enum state { NONE, MOVE_ABS, CURVE_ABS, MOVE_TO, CURVE_TO };

state checkState(char ch, state current)
{
	switch(ch)
	{
		case 'M': return MOVE_ABS;
		case 'm': return MOVE_TO;
		case 'C': return CURVE_ABS;
		case 'c': return CURVE_TO;
	}

	return current;
}

sf::Vector2f CalculateBezierPoint(float t, sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3)
{
	float u = 1 - t;
	float tt = t*t;
	float uu = u*u;
	float uuu = uu * u;
	float ttt = tt * t;

	sf::Vector2f p = uuu * p0;
	p += 3 * uu * t * p1;
	p += 3 * u * tt * p2;
	p += ttt * p3;

	return p;
}

vertices_t getObtacleVertices(ifstream &in)
{
	vertices_t readed;
	readed.clear();

	state st = NONE;

	char ch = 0;
	string xS, yS;

	sf::Vector2f lastPos(0,0);

	while(in)
	{
		in.get(ch);
		st = checkState(ch, st);

		xS.clear(); yS.clear();

		switch(st)
		{
			case NONE:
				break;	
			case MOVE_ABS:
				if(isdigit(ch)) 
				{
					while(ch != ',') 
					{
						xS += ch;	
						in.get(ch);
					}
					in.get(ch);
					while(!isspace(ch))
				       	{
						yS += ch;
						in.get(ch);
					}

					lastPos = sf::Vector2f(atof(xS.c_str()), atof(yS.c_str()));
					readed.push_back(lastPos);
				}
				break;
			case CURVE_ABS:			
				if(isdigit(ch))
				{
					sf::Vector2f p[4];
					p[0] = sf::Vector2f(lastPos);	

					for(int i = 1; i < 4; ++i)
					{
						xS.clear(); yS.clear();
						while(!isdigit(ch)) in.get(ch);
						while(ch != ',') 
						{
							xS += ch;	
							in.get(ch);
						}
						in.get(ch);
						while(!isspace(ch))
						{
							yS += ch;
							in.get(ch);
						}

						p[i] = sf::Vector2f(atof(xS.c_str()), atof(yS.c_str()));	
					}

					lastPos = p[3];
					
					for(int j = 1; j <= SEGMENTS_PER_CURVE; ++j)
					{
						float t = j/ (float) SEGMENTS_PER_CURVE;
						readed.push_back(CalculateBezierPoint(t, p[0], p[1], p[2], p[3]));
					}
					
				}
				break;
		}
	}

	return readed;
}

int initMap()
{
	vector<Obstacle *> ob;	
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

	if (argc < 2)
	{
		cout << "Использование:" << argv[0] << " + файл с описанием карты" << endl;
		return -1;
	}

	pathToObstacles = argv[1];

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
