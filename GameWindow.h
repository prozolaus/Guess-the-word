#pragma once
#include "Menu.h"

class GameWindow : public sf::RenderWindow
{
	bool restart;
	sf::Vector2u startSize;
	string windowname;
	MenuSettings menu();
	void wait(Language lang);

public:
	GameWindow(sf::VideoMode, const sf::String);
	void runGame();
	void updateTitle(MenuSettings ms);
	void setStartSize() { setSize(startSize); }
	sf::Vector2u getStartSize() const { return startSize; }
};

//-----------------------------------------------------------------------------