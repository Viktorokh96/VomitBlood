#include <vomitblood.hpp>

#define RADIUS 20

Tadpole::Tadpole(Map *map)
: _map(map)
{
	_vertices.clear();
	sf::CircleShape c(RADIUS);
	for(unsigned i = 1; i < c.getPointCount(); ++i)
		_vertices.append(sf::Vector2f(c.getPoint(i)));
	update();

	setFillColor(sf::Color::Yellow);
	goToStart();
}

Tadpole::~Tadpole()
{
	_vertices.clear();
}

void Tadpole::goToStart()
{
	setPosition(300, 600);
}

void Tadpole::updatePosition(sf::Time dt)
{
	sf::Vector2i velocity
	(
		REDIGITY*(sf::Mouse::getPosition(window).x-getPosition().x-RADIUS),
		REDIGITY*(sf::Mouse::getPosition(window).y-getPosition().y-RADIUS)
	);

	float t = dt.asSeconds();
	move(velocity.x*t,velocity.y*t);
}

bool Tadpole::isCollide()
{
	return _map->isCollide(*this);
}

std::size_t Tadpole::getPointCount() const
{
	return _vertices.getVertexCount();
}

Vector2f Tadpole::getPoint(std::size_t index) const
{
	return _vertices[index].position;
}
