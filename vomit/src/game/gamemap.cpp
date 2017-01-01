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
	_vertices.clear();

	update();
}

Obstacle::Obstacle(std::vector<sf::Vector2f> vertices, string textureName)
{
	std::vector<sf::Vector2f>::iterator iter = vertices.begin();
	while(iter != vertices.end()) {
		_vertices.append(*iter);
		iter++;
	}
	
	if((_texture = resourceHolder.getTexture(textureName)))
		setTexture(_texture);
	update();
}

Obstacle::~Obstacle()
{
	_vertices.clear();
}

void Obstacle::setInMapPosition(sf::Vector2f pos)
{
	_inMapPosition = pos;

	update();
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

	//DEBUG COLLISIONS
/*
	VertexArray arr1(sf::Lines, 2);
	VertexArray arr2(sf::Lines, 2);

	arr1[0].position = sf::Vector2f(l1[0].x, l1[0].y);
	arr1[1].position = sf::Vector2f(l1[1].x, l1[1].y);

	arr2[0].position = sf::Vector2f(l2[0].x, l2[0].y);
	arr2[1].position = sf::Vector2f(l2[1].x, l2[1].y);

	window.draw(arr1);
	window.draw(arr2);
	window.display();
*/
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
				(obj.getPoint(i)) + obj.getPosition(),
				(obj.getPoint(i+1)) + obj.getPosition()
			};
			for(int j = 0; j < obstacleCount-1; ++j) {
				sf::Vector2f _obstLine[2] =
				{
					(getTransform()*getPoint(j)),
					(getTransform()*getPoint(j+1))
				};
				if(linesIntersects(_objLine, _obstLine))
					return true;
			}
		}
	}

	return false;
}

/////////////////////////////////// PartOfMap ////////////////////////////////////

PartOfMap::PartOfMap(vector<Obstacle> obstacles, const unsigned level)
: _level(level)
{
	_obstacles.clear();

	vector<Obstacle>::iterator iter = obstacles.begin();
	while(iter != obstacles.end()) {
		_obstacles.push_back(*iter);
		iter++;
	}

	updateObstacles();
}

PartOfMap::PartOfMap() 
: _level(1)
{
	_position = 0.f;
	_obstacles.clear();

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

unsigned PartOfMap::getLevel() const
{
	return _level;
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

static sf::Font font;

Map::Map()
{
	_parts.clear();
	_velocity = 0;
	_level = 1;
	_points = 0;

	if (!font.loadFromFile("media/menu/FEASFBRG.TTF")) {
		clog << "ERROR! LOADING FONT IN MAP CONSTRUCTOR!" << endl;
	}
}

Map::~Map()
{
	_parts.clear();
}

void Map::newMap()
{
	_parts.clear();

	PartOfMap part; 

	part = resourceHolder.getStartPartOfMap();
	part.setPosition(WINDOW_HEIGHT-PART_HEIGHT);
	_parts.push_back(part);

	part = resourceHolder.getRandomPartOfMap(_level);
	part.setPosition(WINDOW_HEIGHT-(2*PART_HEIGHT));
	_parts.push_back(part);
}

void Map::update(sf::Time dt)
{
	std::vector<PartOfMap>::iterator it = _parts.begin();

	while(it != _parts.end()) {
		it->update(_velocity * dt.asSeconds());
		it++;
	}

	if(_parts.begin()->getPosition() > WINDOW_HEIGHT) {
		PartOfMap part = resourceHolder.getRandomPartOfMap(_level); 
		part.setPosition(_parts.rbegin()->getPosition()-PART_HEIGHT);
		_parts.push_back(part);
		_parts.erase(_parts.begin());
	} 
}

void Map::drawInfo() const
{
	sf::Text points, level;
	points.setFont(font);
	level.setFont(font);
	points.setCharacterSize(30);
	level.setCharacterSize(30);
	points.setColor(sf::Color::Red);
	level.setColor(sf::Color::Green);
	points.setStyle(sf::Text::Bold);
	level.setStyle(sf::Text::Bold);

	char score[16], levelString[8];
	sprintf(score,"Score:%ld",_points);
	sprintf(levelString, "Level:%d", _level);
	points.setString(score);
	level.setString(levelString);

	sf::FloatRect bp = points.getLocalBounds();
	sf::FloatRect bl = level.getLocalBounds();

	points.setPosition(4*(WINDOW_WIDTH/5) - (bp.width/2), (bp.height));
	level.setPosition(1*(WINDOW_WIDTH/5) - (bl.width/2), (bl.height));

	window.draw(points);
	window.draw(level);

}

void Map::draw() const
{
	std::vector<PartOfMap>::const_iterator it = _parts.begin();
	while(it != _parts.end()) {
		it->draw();
		it++;
	}
	
	drawInfo();
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

void Map::setPoints(unsigned p)
{
	_points = p;
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
