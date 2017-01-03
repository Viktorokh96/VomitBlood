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
		_vertices.append(sf::Vector2f(c.getPoint(i) - sf::Vector2f(RADIUS,RADIUS)));
	sf::Shape::update(); // обращение к методу update предка

	//tex.loadFromFile();
	//setTexture("media/game/tadpole.png");
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
	int rigidity = config.getRigidity();
	sf::Vector2i velocity
	(
		rigidity*(mousePosition.x-tadpolePosition.x),
		rigidity*(mousePosition.y-tadpolePosition.y)
	);

	/* Проверка от выхода за пределы верхней и нижней границы карты */
	if (((tadpolePosition.y < RADIUS) || (tadpolePosition.y > WINDOW_HEIGHT-RADIUS))
	&& ((mousePosition.y < 0) || (mousePosition.y > WINDOW_HEIGHT-RADIUS)))
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

numeric_t Tadpole::getPointCount() const
{
	return _vertices.getVertexCount();
}

Vector2f Tadpole::getPoint(numeric_t index) const
{
	return _vertices[index].position;
}
