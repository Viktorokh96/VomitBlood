#ifndef GAME_BUILDER
#define GAME_BUILDER 1

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
	enum _modelsNames { modelFacade, map, obstacle, tadpole };
	static const int _modelsQuantity = 4;
protected:
	void buildObjects();
	void disposeObjects();
public:
	GameBuilder();
	~GameBuilder() {}
	void build();
};

#endif
