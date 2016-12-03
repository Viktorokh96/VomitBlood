#ifndef GAME_BUILDER
#define GAME_BUILDER 1

#include "../model/gamemodel.hpp"
#include "../controller/gamecontroller.hpp"

/*
 * Построитель игрового пространства
 * 
 * Этот класс обеспечивает подготовку объектов игры
 * к использованию - инстационирует соответсвтующие
 * классы моделей, представления и контроллеров, а после
 * передаёт управлению контроллеру для запуска игры.
 *
 * Таким образом реализуется переход программы в 
 * состояние "Игра".
*/
class GameBuilder : public AbstractBuilder {
	GameModelFacade *_modelFacade;
	MapModel *_map;
	TadpoleModel *_tadpole;

	GameController *_controller;

protected:
	void buildObjects();
	void disposeObjects();
public:
	GameBuilder();
	~GameBuilder() {}
	void build();
};

#endif
