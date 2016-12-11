#ifndef _VOMITGAME
#define _VOMITGAME 1

#include <SFML/Graphics.hpp>

#define VELOCITY_ADD_STEPS 	5
#define LEVEL_ADD_STEPS 	50

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

#define START_MAP_VELOCITY 200
#define VELOCITY_INCREMENT 20

#include "game/view.hpp"
#include "game/controller.hpp"
#include "game/model.hpp"

// Создаем главное окно приложения
extern sf::RenderWindow window;

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
	GameController *_game;
public:
	int init();
	void start();
	void dispose();
};

#endif
