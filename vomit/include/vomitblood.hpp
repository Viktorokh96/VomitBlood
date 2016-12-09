#ifndef _VOMITGAME
#define _VOMITGAME 1

#include <SFML/Graphics.hpp>

typedef struct _cmd {
	struct  {
		unsigned tadpoleCollide:1;
		unsigned tadpoleStep:1;
		unsigned gameOver:1;
		unsigned exitGame:1;
		unsigned addVelocity:1;
		unsigned addLevel:1;
	} status;

	int value;

	void clear()
	{
		status.tadpoleCollide = 0;
		status.tadpoleStep = 0;
		status.gameOver = 0;
		status.exitGame = 0;
		status.addVelocity = 0;
		status.addLevel = 0;
		value = 0;
	}
} cmd_t;

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
