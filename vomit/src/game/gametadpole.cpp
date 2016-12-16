#include <vomitblood.hpp>
#include <iostream>

#define RADIUS 20

#define TADPOLE_START_X (WINDOW_WIDTH/2 - RADIUS)
#define TADPOLE_START_Y (WINDOW_HEIGHT/2 - RADIUS)

/* 
 * Конструктор "Головастика" 
 * должен определять его геометрию.
 * Это делается посредством описания его вершин
 * через вектор вершин _vertices, с последующим
 * обязательным(!!!) вызовом метода предка update
 * Непосредственно предок sf::Shape после вызова
 * этого метода будет иметь полную информацию
 * о геометрии головастиа, таким образом вырисовывая
 * его на карте.
*/
Tadpole::Tadpole(Map *map)
: _map(map)
{
	_vertices.clear();
	sf::CircleShape c(RADIUS);
	for(unsigned i = 1; i < c.getPointCount(); ++i)
		_vertices.append(sf::Vector2f(c.getPoint(i)));
	sf::Shape::update(); // обращение к методу update предка

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

void Tadpole::update(sf::Time dt)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	sf::Vector2f tadpolePosition = getPosition();
	
	sf::Vector2i velocity
	(
		RIGIDITY*(mousePosition.x-tadpolePosition.x-RADIUS),
		RIGIDITY*(mousePosition.y-tadpolePosition.y-RADIUS)
	);

	/* Проверка от выхода за пределы верхней и нижней границы карты */
	if (((tadpolePosition.y < 0) || (tadpolePosition.y > WINDOW_HEIGHT-2*RADIUS))
	&& ((mousePosition.y < 0) || (mousePosition.y > WINDOW_HEIGHT-2*RADIUS)))
		velocity.y = 0;

	float t = dt.asSeconds();
	move(velocity.x*t,velocity.y*t);
}

bool Tadpole::isCollide()
{
	return _map->isCollide(*this);
}

bool Tadpole::isClicked()
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	FloatRect bounds = getGlobalBounds();
	return (bounds.contains(mousePosition.x, mousePosition.y) 
			&& sf::Mouse::isButtonPressed(sf::Mouse::Left));
}

std::size_t Tadpole::getPointCount() const
{
	return _vertices.getVertexCount();
}

Vector2f Tadpole::getPoint(std::size_t index) const
{
	return _vertices[index].position;
}
