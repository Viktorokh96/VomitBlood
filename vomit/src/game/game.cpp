#include <vomitgame.hpp>
#include <new>

enum builderName { game, menu, rating, setting };

int VomitGame::init()
{
	try {
		_builder[game] = new GameBuilder;
		_builder[menu] = new MenuBuilder;
		_builder[rating] = new RatingBuilder;
		_builder[setting] = new SettingBuilder;

	} catch (std::bad_alloc bad) {
		return -1;
	}
	
	return 0;
}

void VomitGame::start()
{
	_builder[menu]->build();
}

void VomitGame::dispose()
{
	for (int i = 0; i < _buildQuantity; ++i)
		if ( _builder[i] )
			delete _builder[i];
}
