#pragma once
#include "Menu.h"

class GameWindow : public sf::RenderWindow
{
	bool restart;
	string windowname;
	MenuSettings menu();
	void wait(Language lang);

public:
	GameWindow(sf::VideoMode, const sf::String, sf::Uint32);
	void runGame();
	void updateTitle(MenuSettings ms);
};

//-----------------------------------------------------------------------------