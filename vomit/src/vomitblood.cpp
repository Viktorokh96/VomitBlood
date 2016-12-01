#include <iostream>
#include <vomitgame.hpp>
using namespace std;

int main()
{
	VomitGame game;

	if( game.init() < 0 )
		cerr << "Ошибка инициализации!\n";

	game.start();
	game.dispose();

	return 0;
}
