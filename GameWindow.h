#pragma once
#include "Menu.h"

class GameWindow : public sf::RenderWindow
{
	using sf::RenderWindow::RenderWindow;
	MenuSettings menu();
	bool check_event(sf::Event&, Game&, sf::Vector2i&);
	void play(Game&);

public:
	void runGame();
};

//-----------------------------------------------------------------------------