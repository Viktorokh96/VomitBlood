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
	
	numeric_t getPointCount() const;
    	Vector2f getPoint(numeric_t index) const;
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
	sf::Texture *_texture;
public:
	Obstacle();
	Obstacle(std::vector<sf::Vector2f> vertices, string textureName);
	~Obstacle();

	void setInMapPosition(sf::Vector2f pos);
	void setInMapPosition(float x, float y);
	sf::Vector2f getInMapPosition();

	numeric_t getPointCount() const;
    	Vector2f getPoint(numeric_t index) const;

	bool isCollide(const sf::Shape &) const;
};

/*
 * Класс "Часть карты" или "Блок"
 * Служит строительным кирпичом всей карты.
 * Карта должна генерироваться из случайного набора блоков,
 * которые будут описаны в отдельном месте и построены 
 * загрузчиками.
 * Замечания:
 * distance <- расстояние на которое нужно передвинутся вниз
*/
class PartOfMap {
	unsigned _level; 			// Уровень сложности блока
	float _position;			// Позиция блока на карте
	std::vector<Obstacle> _obstacles;	// Препятствия блока

	void updateObstacles();
public:
	PartOfMap();
	PartOfMap(std::vector<Obstacle> obstacles, const unsigned level);
	~PartOfMap();
	void update(float distance);

	unsigned getLevel() const;

	// Установка позиции блока относительно верхней границы окна
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

	void drawInfo() const;
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
	float getMapVelocity();
};

class GameMenuView : public IView {
	int _status;
	unsigned long _points;
	void showStatus();
	void showPoints();
	void showGameOverScreen();
	void showPauseScreen();

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
