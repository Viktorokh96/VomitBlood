#ifndef _GAME_VIEW
#define _GAME_VIEW 1

#include "../cmd.hpp"
#include "../iview.hpp"
#include "../menu/view.hpp"

#include <SFML/Graphics.hpp>
using namespace sf;

class Map;

/*
 * Класс "Головастик"
 * протагонист этой игры.
 * Управляется игроком
*/
class Tadpole : public sf::Shape {
	VertexArray _vertices;
	Map *_map;
public:
	Tadpole(Map *map);
	~Tadpole();
	void update(sf::Time dt);
	void goToStart();
	bool isCollide();
	bool isClicked();
	
	std::size_t getPointCount() const;
    	Vector2f getPoint(std::size_t index) const;
};

/*
 * Класс "Препятствие"
 * антагонист этой игры.
 * С ним может столкнутся головастик.
 * Является шаблоном для самых различных
 * видов препятствии
*/
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

	bool isCollide(const sf::Shape &) const;
};

/*
 * distance <- расстояние на которое нужно передвинутся вниз
 * TODO:Толстые стенки в начале и в конце блока
*/
class PartOfMap {
	std::vector<Obstacle> _obstacles;
	float _position;

	void updateObstacles();
public:
	PartOfMap();
	PartOfMap(vector<Obstacle *> obstacles);
	~PartOfMap();
	void update(float distance);

	void setPosition(float position);
	float getPosition();

	void draw() const;

	bool isCollide(const sf::Shape &) const;
};

/*
 * Класс "Карта" - отвечает за перерисовку
 * карты игры, за скорость, уровень и 
 * создание и удаление своих частей
 * из случайных компонентов "Часть карты"
 * для генерации бесконечной карты
*/
class Map {
	float _velocity;
	int _level;
	unsigned long _points;
	std::vector<PartOfMap> _parts;

	void drawPoints() const;
public:
	Map();
	~Map();

	void newMap();

	void setPoints(unsigned);
	
	void setVelocity(float);
	float getVelocity();

	void setLevel(int);
	int getLevel();

	void update(sf::Time dt);
	void draw() const;

	bool isCollide(const sf::Shape &) const;
};

/*
 * Класс "Представление игры"
 * Представляет из себя фасад подсистемы визуализации игры.
 * В целом вся визуализация и взаимодействие с пользователем
 * происходят в пределах View.
*/
class GameView : public IView {
	Map * _map;	
	Tadpole *_tadpole;
	sf::Time _dt;

	void newGame();
	bool _tadpoleSleep;
public:
	GameView();
	~GameView();

	cmd_t update();
	void draw();

	void setFrameTime(sf::Time dt);
	void setPoints(unsigned long);
	void makeTadpoleSleep();
	void addVelocity();
	void addLevel();
};

class GameMenuView : public IView {
	int _status;
	unsigned long _points;
	void showStatus();
	void showPoints();

	map<char, Button> _buttons;	
	typedef map<char, Button>::iterator _buttonIter;
public:
	GameMenuView();
	~GameMenuView();

	cmd_t update();
	void draw();

	void setPoints(unsigned long);
	void setGameStatus(gameStatus);
};

#endif
