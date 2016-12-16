#include <vomitblood.hpp>
#include <iostream>
using namespace std;

class MVector2f : public sf::Vector2<float> {
public:
	MVector2f(sf::Vector2f f, sf::Vector2f s)
	{
		x = s.x - f.x;
		y = s.y - f.y;
	}

	float operator*(MVector2f v2)
	{
		return (x * v2.y) - (v2.x * y);
	}
};

/////////////////////////////////// Obstacle ////////////////////////////////////

Obstacle::Obstacle()
{
	sf::CircleShape c(40);
	for(unsigned i = 0; i < c.getPointCount(); ++i)
		_vertices.append(sf::Vector2f(c.getPoint(i)));
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

bool linesIntersects(sf::Vector2f l1[2], sf::Vector2f l2[2])
{
	float x1, x2, x3, x4;	
	float y1, y2, y3, y4;	

	// Быстрая проверка на пересечение квадратов 
	// диагоналями которых являются отрезки

	x1 = min(l1[0].x, l1[1].x);
	x2 = max(l1[0].x, l1[1].x);
	x3 = min(l2[0].x, l2[1].x);
	x4 = max(l2[0].x, l2[1].x);

	y1 = min(l1[0].y, l1[1].y);
	y2 = max(l1[0].y, l1[1].y);
	y3 = min(l2[0].y, l2[1].y);
	y4 = max(l2[0].y, l2[1].y);

 	//Если пересечение обнаружено - уточняем его
	if ((x2 >= x3) && (x4 >= x1) && (y2 >= y3) && (y4 > y1)) {		
		MVector2f v1(l1[0], l2[0]);	
		MVector2f v2(l1[0], l2[1]);	
		MVector2f v3(l1[0], l1[1]);	

		if ((v1*v3) * (v2*v3) <= 0) {
			v1 = MVector2f(l2[0], l1[0]);
			v2 = MVector2f(l2[0], l1[1]);
			v3 = MVector2f(l2[0], l2[1]);
			if ((v1*v3) * (v2*v3) <= 0)
				return true;		// Пересечение есть!
		}
	}

	return false;
}

bool Obstacle::isCollide(const sf::Shape &obj) const
{
	FloatRect objRect = obj.getGlobalBounds();
	FloatRect obstacleRect = getGlobalBounds();

	// Если пересекаются внешние квадраты - уточняем пересечение
	if(objRect.intersects(obstacleRect)) {
		int objCount = obj.getPointCount();	
		int obstacleCount = getPointCount();	
		
		for (int i = 0; i < objCount-1; ++i) {
			sf::Vector2f _objLine[2] =
			{
				obj.getPoint(i) + obj.getPosition(),
				obj.getPoint(i+1) + obj.getPosition()
			};
			for(int j = 0; j < obstacleCount-1; ++j) {
				sf::Vector2f _obstLine[2] =
				{
					getPoint(j) + getPosition(),
					getPoint(j+1) + getPosition()
				};
				if(linesIntersects(_objLine, _obstLine))
					return true;
			}
		}
	}

	return false;
}

/////////////////////////////////// PartOfMap ////////////////////////////////////

PartOfMap::PartOfMap(float position) 
{
	_position = position;
	_obstacles.clear();

	Obstacle ob1, ob2, ob3, ob4, ob5;
	ob1.setInMapPosition(0, 0);
	ob2.setInMapPosition(WINDOW_WIDTH-80, 0);
	ob3.setInMapPosition(0,PART_HEIGHT-80);
	ob4.setInMapPosition(WINDOW_WIDTH-80,PART_HEIGHT-80);
	ob5.setInMapPosition((WINDOW_WIDTH/2)-40,(PART_HEIGHT/2)-40);

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

void PartOfMap::update(float distance)
{
	_position += distance;

	std::vector<Obstacle>::iterator it = _obstacles.begin();
	while(it != _obstacles.end()) 
	{
		it->move(sf::Vector2f(0, distance));
		it++;
	}
}

void PartOfMap::draw() const
{
	std::vector<Obstacle>::const_iterator it = _obstacles.begin();
	while(it != _obstacles.end()) {
		window.draw(*it);
		it++;
	}
}

bool PartOfMap::isCollide(const sf::Shape &obj) const
{
	std::vector<Obstacle>::const_iterator it = _obstacles.begin();
	while(it != _obstacles.end()) {
		if(it->isCollide(obj))
			return true;
		it++;
	}

	return false;
}

////////////////////////////////////// Map ///////////////////////////////////////

Map::Map()
{
	_parts.clear();
	_velocity = 0;
	_level = 0;
}

Map::~Map()
{
	_parts.clear();
}

void Map::newMap()
{
	_parts.clear();
	_parts.push_back(PartOfMap(WINDOW_HEIGHT-PART_HEIGHT));
	_parts.push_back(PartOfMap(WINDOW_HEIGHT-(2*PART_HEIGHT)));
}

void Map::update(sf::Time dt)
{
	std::vector<PartOfMap>::iterator it = _parts.begin();

	while(it != _parts.end()) {
		it->update(_velocity * dt.asSeconds());
		it++;
	}

	if(_parts.begin()->getPosition() > WINDOW_HEIGHT) {
		_parts.push_back(PartOfMap(_parts.rbegin()->getPosition()-PART_HEIGHT));
		_parts.erase(_parts.begin());
	} }

void Map::draw() const
{
	std::vector<PartOfMap>::const_iterator it = _parts.begin();
	while(it != _parts.end()) {
		it->draw();
		it++;
	}
}

void Map::setVelocity(float vel)
{
	_velocity = vel;
}

float Map::getVelocity()
{
	return _velocity;
}

void Map::setLevel(int level)
{
	_level = level;
}

int Map::getLevel()
{
	return _level;
}

bool Map::isCollide(const sf::Shape &obj) const
{
	std::vector<PartOfMap>::const_iterator it = _parts.begin();
	while(it != _parts.end()) {
		if(it->isCollide(obj))
			return true;
		it++;
	}

	return false;
}
