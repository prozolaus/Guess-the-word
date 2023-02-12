#pragma once
#include "Menu.h"

class GameWindow : public sf::RenderWindow
{
	bool restart = false;
	using sf::RenderWindow::RenderWindow;
	MenuSettings menu();

public:
	void runGame();
	void updateTitle(MenuSettings ms);
};

//-----------------------------------------------------------------------------