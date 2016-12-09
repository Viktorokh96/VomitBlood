#ifndef _GAME_VIEW
#define _GAME_VIEW 1

#include <SFML/Graphics.hpp>
using namespace sf;

class Tadpole : public sf::Shape {
	VertexArray _vertices;
public:
	Tadpole();
	void update();
	bool isCollide();
	
	std::size_t getPointCount() const;
    	Vector2f getPoint(unsigned int index) const;
};

class Obstacle : public sf::Shape {
	VertexArray _vertices;
public:
	std::size_t getPointCount() const;
    	Vector2f getPoint(std::size_t index) const;
};

/*
 * TODO:Толстые стенки в начале и в конце блока
*/
class PartOfMap {
	std::vector<Obstacle> _obstacles;
public:
	void update();
	void draw(RenderTarget& target, RenderStates states) const;
};

class Map : public sf::Drawable {
	float _speed;
	std::vector<PartOfMap> _parts;
public:
	void update();
	void draw(RenderTarget& target, RenderStates states) const;
};

/*
 * Класс "Представление игры"
 * Представляет из себя фасад подсистемы визуализации игры.
 * В целом вся визуализация и взаимодействие с пользователем
 * происходят в пределах View.
*/
class GameView {
public:
	GameView();
	~GameView();

	cmd_t update();

	void setSpeed(int);
	void setLevel(int);
	void newGame();
};

#endif
