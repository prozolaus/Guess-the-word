#pragma once
#include "Menu.h"

class GameWindow : public sf::RenderWindow
{
	bool restart = false;
	using sf::RenderWindow::RenderWindow;
	MenuSettings menu();
	void wait(Language lang);

public:
	void runGame();
	void updateTitle(MenuSettings ms);
};

//-----------------------------------------------------------------------------