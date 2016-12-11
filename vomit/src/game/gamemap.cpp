#include <vomitblood.hpp>
#include <iostream>
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

/////////////////////////////////// PartOfMap ////////////////////////////////////

PartOfMap::PartOfMap(float position) 
: _boundary(sf::FloatRect(0,0, WINDOW_WIDTH, WINDOW_HEIGHT))
{
	_position = sf::Vector2f(0,position);
	_obstacles.clear();

	Obstacle ob1, ob2, ob3, ob4, ob5;
	ob1.setInMapPosition(0, 0);
	ob2.setInMapPosition(WINDOW_WIDTH-80, 0);
	ob3.setInMapPosition(0,WINDOW_HEIGHT-80);
	ob4.setInMapPosition(WINDOW_WIDTH-80,WINDOW_HEIGHT-80);
	ob5.setInMapPosition((WINDOW_WIDTH/2)-40,(WINDOW_HEIGHT/2)-40);

	_obstacles.push_back(ob1);
	_obstacles.push_back(ob2);
	_obstacles.push_back(ob3);
	_obstacles.push_back(ob4);
	_obstacles.push_back(ob5);
}

PartOfMap::~PartOfMap()
{
	_obstacles.clear();
}

void PartOfMap::updateObstacles()
{
	std::vector<Obstacle>::iterator it = _obstacles.begin();
	while(it != _obstacles.end()) {
		it->setPosition(_position + it->getInMapPosition());
		it++;
	}
}

void PartOfMap::setPosition(sf::Vector2f &pos)
{
	_position = sf::Vector2f(pos);

	updateObstacles();
}

void PartOfMap::setPosition(float x, float y)
{
	sf::Vector2f vect(x,y);
	setPosition(vect);
}

float PartOfMap::getPosition()
{
	return _position.y;
}

void PartOfMap::update(float distance)
{
	_position.y += distance;

	updateObstacles();
}

void PartOfMap::draw() const
{
	std::vector<Obstacle>::const_iterator it = _obstacles.begin();
	while(it != _obstacles.end()) {
		window.draw(*it);
		it++;
	}
}

////////////////////////////////////// Map ///////////////////////////////////////

Map::Map()
{
	_parts.clear();
	_velocity = 0;
}

Map::~Map()
{
	_parts.clear();
}

void Map::newMap()
{
	_parts.push_back(PartOfMap(0));
	_parts.push_back(PartOfMap(-WINDOW_HEIGHT));
}

void Map::update(sf::Time dt)
{
	std::vector<PartOfMap>::iterator it = _parts.begin();

	while(it != _parts.end()) {
		it->update(_velocity * dt.asSeconds());
		it++;
	}

	if(_parts.begin()->getPosition() > WINDOW_HEIGHT) {
		_parts.push_back(PartOfMap(_parts.rbegin()->getPosition()-WINDOW_HEIGHT));
		_parts.erase(_parts.begin());
		std::clog << "NEW PART PASTED!" << std::endl;
		std::clog << _parts.size() << std::endl;
	}
}

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
