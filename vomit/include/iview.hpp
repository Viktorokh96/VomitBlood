#ifndef _VIEW_INTERFACE_
#define _VIEW_INTERFACE_ 1

/*
 * Делать ли это класс если есть SFML?
 * и наследование?
 * Либо сделать class View : sf::Shape { ... }; ???
 * TODO: Обдумать вышестоящий вопрос.
*/

class IView {
public:
	~IView() = 0;
	virtual void draw() = 0;
};

#endif
