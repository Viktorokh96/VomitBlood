#ifndef _GAME_VIEW
#define _GAME_VIEW 1

#include <../iview.hpp>
#include "controller.hpp"

/*
 * Класс "Представление игры"
 * Представляет из себя фасад подсистемы визуализации игры.
 * В целом вся визуализация и взаимодействие с пользователем
 * происходят в пределах View.
*/
class GameView {
	GameController * const _controller;
public:
	GameView( GameController * controller);
	~GameView();

	void setSpeed(int);
	void startGame();
};
