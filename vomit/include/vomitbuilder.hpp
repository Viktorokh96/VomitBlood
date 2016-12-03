#ifndef VOMIT_BUILDER
#define VOMIT_BUILDER 1

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
public:
	virtual ~AbstractBuilder() {}
	virtual void build() = 0;
};

////////////////////////////////////////////////////////

class GameBuilder : public AbstractBuilder {
public:
	~GameBuilder() {}
	void build();
};

class MenuBuilder : public AbstractBuilder {
public:
	~MenuBuilder() {}
	void build();
};

class RatingBuilder : public AbstractBuilder {
public:
	~RatingBuilder() {}
	void build();
};

class SettingBuilder : public AbstractBuilder {
public:
	~SettingBuilder() {}
	void build();
};

#endif
