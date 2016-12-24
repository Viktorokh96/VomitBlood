#include <cmd.hpp>
#include <vomitblood.hpp>
#include <new>
#include <cmath>
#include <iostream>
#include <cstdlib>
using namespace std;

#define BUTT_RAD 35

////////////////////// GameMenuView //////////////////////

static sf::Font font;
sf::Texture *restartTexture;
sf::Texture *resumeTexture;
sf::Texture *exitTexture;
sf::Texture *gameOverTexture;
sf::Texture *pauseTexture;

GameMenuView::GameMenuView()
{
	_buttons.clear();

	if (!font.loadFromFile("media/menu/FEASFBRG.TTF")) {
		clog << "GameMenuVeiw:ERROR LOADING FONT!" << endl;
	}

//	restartTexture = resourceHolder.getTexture("restartButton");
//	resumeTexture = resourceHolder.getTexture("startButton");
//	exitTexture = resourceHolder.getTexture("exitButton");
//	gameOverTexture = resourceHolder.getTexture("gameOver");
//	pauseTexture = resourceHolder.getTexture("gamePause");
	
	restartTexture = resourceHolder.getTexture("restartButton");
	resumeTexture = resourceHolder.getTexture("startButton");
	exitTexture = resourceHolder.getTexture("exitButton");
	gameOverTexture = resourceHolder.getTexture("gameOver");
	pauseTexture = resourceHolder.getTexture("gamePause");


	if(restartTexture)
		(*restartTexture).setSmooth(true);
	if(resumeTexture)
		(*resumeTexture).setSmooth(true);		
	if(exitTexture)
		(*exitTexture).setSmooth(true);		

	Button button(sf::Vector2f((WINDOW_WIDTH/2)-BUTT_RAD, 
		   10*(WINDOW_HEIGHT/15)), BUTT_RAD);
	button.setTexture(restartTexture);
	button.setTextureRect(sf::IntRect(15,15, 164, 168));
	
	//restart button
	_buttons.insert(make_pair('r', button));

	button.setTextureRect(sf::IntRect(18,18, 300, 300));
	button.setTexture(resumeTexture);

	button.setPosition(sf::Vector2f((WINDOW_WIDTH/2)+2*BUTT_RAD, 
				   10*(WINDOW_HEIGHT/15)));

	//resume button (c - continue)
	_buttons.insert(make_pair('c', button));

	button.setTexture(exitTexture);
	button.setPosition(sf::Vector2f((WINDOW_WIDTH/2)-4*BUTT_RAD, 
				   10*(WINDOW_HEIGHT/15)));

	//exit button (e - exit)
	_buttons.insert(make_pair('e',button));

	_points = 0;
}

cmd_t GameMenuView::update()
{
	cmd_t retCmd;
	retCmd.clear();

	_buttonIter iter = _buttons.begin();

	while(iter != _buttons.end()) {
		if(((iter->second).isClicked())) {
			switch(iter->first) {
				case 'r':
					retCmd.restart = 1;
					break;
				case 'c':
					if(_status == gamePause)
						retCmd.resume = 1;
					break;
				case 'e':
					retCmd.exitGame = 1;
					break;
			}
		}
		iter++;
	}

	return retCmd;
}

void GameMenuView::showStatus()
{
	sf::Text status;
	status.setFont(font);
	status.setCharacterSize(80);
	status.setColor(sf::Color::Red);
	status.setStyle(sf::Text::Bold);

	if(_status == gamePause)
		status.setString("Pause");
	else
		status.setString("You died!");

	sf::FloatRect b = status.getLocalBounds();

	status.setPosition((WINDOW_WIDTH/2) - (b.width/2), (WINDOW_HEIGHT/2) - b.height);

	window.draw(status);
}

void GameMenuView::showPoints()
{
	sf::Text points;
	points.setFont(font);
	points.setCharacterSize(30);
	points.setColor(sf::Color::Red);
	points.setStyle(sf::Text::Bold);

	char score[64];
	sprintf(score,"Your score is %ld",_points);

	points.setString(score);

	sf::FloatRect b = points.getLocalBounds();

	points.setPosition((WINDOW_WIDTH/2) - (b.width/2), (WINDOW_HEIGHT/2) + (b.height));

	window.draw(points);
}

void GameMenuView::showGameOverScreen()
{
	sf::Sprite gameOverSprite(*gameOverTexture);
	gameOverSprite.setPosition(0, 47);

	window.draw(gameOverSprite);
}

void GameMenuView::showPauseScreen()
{
	sf::Sprite pauseSprite(*pauseTexture);
	pauseSprite.setColor(sf::Color(255,255,255,5));

	window.draw(pauseSprite);
}

void GameMenuView::setPoints(unsigned long p)
{
	_points = p;
}

void GameMenuView::draw()
{
	if(_status == gameOver) {
		window.clear();
		showGameOverScreen();
		showPoints();
	} else if (_status == gamePause) {
		showPauseScreen();
	}

	showStatus();

	_buttonIter iter = _buttons.begin();
	while(iter != _buttons.end()) {
		if(iter->first == 'c' && _status == gameOver) {
			iter++;
			continue;
		}

		window.draw(iter->second);
		iter++;
	}

	window.display();
}

void GameMenuView::setGameStatus(gameStatus stat)
{
	_status = stat;
}

GameMenuView::~GameMenuView()
{
}

////////////////////// GameView //////////////////////

GameView::GameView() 
{
	try {
		_map = new Map();
		_tadpole = new Tadpole(_map);
	} catch (bad_alloc bad) {
		return;
	}

	newGame();
}

void GameView::newGame()
{
	_map->newMap();
	_map->setVelocity(START_MAP_VELOCITY);
	_map->setLevel(START_MAP_LEVEL);
	_tadpole->goToStart();
	_tadpoleSleep = true;
}

GameView::~GameView()
{
	delete _map;
	delete _tadpole;
}

void GameView::addVelocity()
{
	_map->setVelocity(_map->getVelocity()+VELOCITY_INCREMENT);
}

void GameView::addLevel()
{
	_map->setLevel(_map->getLevel()+1);
}

void GameView::draw()
{
	window.clear();

	_map->draw();
	window.draw(*_tadpole);

	window.display();
}

void GameView::setPoints(unsigned long p)
{
	_map->setPoints(p);
}

void GameView::makeTadpoleSleep()
{
	_tadpoleSleep = true;
}

/*
 * Метод перерасчёта позиции и столковении
 * значение dt - секунды (float)
*/
cmd_t GameView::update()
{
	cmd_t retCmd;
	retCmd.clear();

	if (!_tadpoleSleep) {
		static int updatesPerStep = UPDATES_PER_STEP;

		updatesPerStep--;

		if(!updatesPerStep) {
			retCmd.tadpoleStep = 1;
			updatesPerStep = UPDATES_PER_STEP;
		}

		_map->update(_dt);
		_tadpole->update(_dt);

		if(_tadpole->isCollide())
			retCmd.tadpoleCollide = 1;
	} else {
	/* Мерцание головастиком, для привлечения внимания игрока */
		static double a = 0.f;	
		_tadpole->setScale(abs(cos(a)), abs(cos(a)));
		a += 0.04f;
		if(a > 1000) a = 0;

		if(_tadpole->isClicked()) {
			_tadpole->setScale(1.f,1.f);
			_tadpoleSleep = false;
		}
	}

	return retCmd;
}

void GameView::setFrameTime(sf::Time dt)
{
	_dt = dt;
}

