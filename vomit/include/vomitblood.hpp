#ifndef _VOMITGAME
#define _VOMITGAME 1

#include <SFML/Graphics.hpp>

typedef int cmd_t;

#include "game/view.hpp"
#include "game/controller.hpp"
#include "game/model.hpp"
//
// Создаем главное окно приложения
sf::RenderWindow window(sf::VideoMode(800, 800), "VomitBlood", sf::Style::Titlebar | sf::Style::Close);
sf::CircleShape circle;

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
