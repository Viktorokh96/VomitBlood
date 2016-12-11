#ifndef _GAME_VIEW
#define _GAME_VIEW 1

#include "../cmd.hpp"

#include <SFML/Graphics.hpp>
using namespace sf;

class Tadpole : public sf::Shape {
	VertexArray _vertices;
public:
	Tadpole();
	~Tadpole();
	void update(sf::Time dt);
	bool isCollide();
	
	std::size_t getPointCount() const;
    	Vector2f getPoint(std::size_t index) const;
};

class Obstacle : public sf::Shape {
	VertexArray _vertices;
	sf::Vector2f _inMapPosition;
public:
	Obstacle();
	~Obstacle();

	void setInMapPosition(sf::Vector2f pos);
	void setInMapPosition(float x, float y);
	sf::Vector2f getInMapPosition();

	std::size_t getPointCount() const;
    	Vector2f getPoint(std::size_t index) const;
};

/*
 * distance <- расстояние на которое нужно передвинутся вниз
 * TODO:Толстые стенки в начале и в конце блока
*/
class PartOfMap {
	std::vector<Obstacle> _obstacles;
	FloatRect _boundary;
	sf::Vector2f _position;

	void updateObstacles();
public:
	PartOfMap(float position);
	~PartOfMap();
	void update(float distance);

	void setPosition(sf::Vector2f &pos);
	void setPosition(float x, float y);
	float getPosition();

	void draw() const;
};

/*
 * TODO: Заменить vector<PartOfMap> на
 * queue<PartOfMap>.
 * Очередь наиболее правильная структура
 * на мой взгляд. Потому что она всегда
 * заполняется с одной стороны и 
 * высвобождается с противоположной.
*/
class Map {
	float _velocity;
	std::vector<PartOfMap> _parts;
public:
	Map();
	~Map();

	void newMap();
	
	void setVelocity(float);
	float getVelocity();

	void update(sf::Time dt);
	void draw() const;
};

/*
 * Класс "Представление игры"
 * Представляет из себя фасад подсистемы визуализации игры.
 * В целом вся визуализация и взаимодействие с пользователем
 * происходят в пределах View.
*/
class GameView {
	Map * _map;	
	Tadpole *_tadpole;
public:
	GameView();
	~GameView();

	cmd_t update(sf::Time dt);
	void draw();

	void addVelocity();
	void addLevel();
	void newGame();
};

#endif
