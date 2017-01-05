#ifndef _VOMITGAME
#define _VOMITGAME 1

#include <SFML/Graphics.hpp>

#define CONFIGURATION_PATH "./config/config.cfg"

/* 
 * Стандартные конфигурации игры
*/
#define UPDATES_PER_STEP 	1

#define VELOCITY_ADD_STEPS 	1200
#define LEVEL_ADD_STEPS 	4800

#define WINDOW_WIDTH 		800
#define WINDOW_HEIGHT 		700

#define PART_HEIGHT 		1400

#define VELOCITY_INCREMENT 	15

#include "defines.hpp"

#include "configuration.hpp"

#include "game/view.hpp"
#include "game/controller.hpp"
#include "game/model.hpp"

#include "menu/view.hpp"
#include "menu/controller.hpp"

#include "holder/holder.hpp"

#include "loader/loader.hpp"
#include "loader/loaderException.hpp"

// Создаем главное окно приложения
extern sf::RenderWindow window;
// Глобальный объект Configuration
extern Configuration config;
// Глобальный объект Holder
extern Holder resourceHolder;


/*
 * Application - главный класс игры
 * Его задача заключается в полном обслуживании 
 * процесса игры, а именно:
 * 	init() - Подготовка системного окружения к началу игры
 * 	start() - Передача управления контроллеру (Меню)
 * 	dispose() - Окончательное освобождение всех игровых ресурсов
 *
 * Следует создавать лишь один экземпляр этого класса для работы игры
 * Типичное применение:
 * 	int main() 
 * 	{
 * 		VomitGame game;
 *		
 *		game.init();
 *		game.start();
 *		game.dispose();
 *
 * 		return 0;
 * 	}
*/
class Application {
	MenuController *_menu;
public:
	void load();
	int init();
	void start();
	void dispose();
};

#endif
