#include <vomitblood.hpp>
#include <iostream>

#define RADIUS 20

#define TADPOLE_START_X 300
#define TADPOLE_START_Y 600

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
	setPosition(TADPOLE_START_X, TADPOLE_START_Y);
}

void Tadpole::updatePosition(sf::Time dt)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	sf::Vector2f tadpolePosition = getPosition();
	
	/* Проверка от выхода за пределы верхней и нижней границы карты */
	if (((tadpolePosition.y < 0) || (tadpolePosition.y > WINDOW_HEIGHT-2*RADIUS))
	&& ((mousePosition.y < 0) || (mousePosition.y > WINDOW_HEIGHT-2*RADIUS)))
		return;

	sf::Vector2i velocity
	(
		REDIGITY*(mousePosition.x-tadpolePosition.x-RADIUS),
		REDIGITY*(mousePosition.y-tadpolePosition.y-RADIUS)
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
