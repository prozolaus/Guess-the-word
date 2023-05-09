#pragma once
#include "Menu.h"

class GameWindow : public sf::RenderWindow
{
	string windowname;
	Settings showmenu(Menu&);
	void wait(Language lang);

public:
	GameWindow(sf::VideoMode, const sf::String, sf::Uint32);
	void runGame();
	void updateTitle(Settings ms);
};

//-----------------------------------------------------------------------------