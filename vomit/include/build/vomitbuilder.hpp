#ifndef VOMIT_BUILDER
#define VOMIT_BUILDER 1

#include "../model/vomitmodel.hpp"

/* 
 * Внимание! Никогда не подключайте этот заголовочный файл самостоятельно!
 * Подключите файл vomitegame.hpp вместо этого!
*/

/*
 * Интерфейс построителя состояния игры
 *
 * специализация данного интерфейса должна обеспечивать
 * инстационирование объектов какого либо состояния
 * например: 
 * 	- состояние 'Игровое меню' - MenuBuilder
	 * 	- состояние 'Игра' - GameBuilder
	 * как только построитель завершает постройку объектов
	 * он передаёт управление объекту-контроллеру, определенного
	 * для вызванного состояния.
	 * После возврата управления контроллером, построитель
	 * обязан уничтожить созданные объекты. На его плечах
	 * критическое место - работа с большими блоками памяти,
	 * выделенные под объекты состояний
	*/
	class AbstractBuilder {
	protected:
		virtual void buildObjects() = 0;
		virtual void disposeObjects() = 0;
	public:
		virtual ~AbstractBuilder() {}
		virtual void build() = 0;
	};

	////////////////////////////////////////////////////////

#include "gamebuilder.hpp"

class MenuBuilder : public AbstractBuilder {
protected:
	void buildObjects();
	void disposeObjects();
public:
	~MenuBuilder() {}
	void build();
};

class RatingBuilder : public AbstractBuilder {
protected:
	void buildObjects();
	void disposeObjects();
public:
	~RatingBuilder() {}
	void build();
};

class SettingBuilder : public AbstractBuilder {
protected:
	void buildObjects();
	void disposeObjects();
public:
	~SettingBuilder() {}
	void build();
};

#endif
