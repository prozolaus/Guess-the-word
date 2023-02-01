#pragma once
#include "Menu.h"

class GameWindow : public sf::RenderWindow
{
	bool gaming = true, restart = false;
	using sf::RenderWindow::RenderWindow;
	MenuSettings menu();
	void eventHandling(Game&);
	void play(Game&);
	void oneTimeLeftActions(Game&, sf::Vector2i);
	void oneTimeRightActions(Game&, sf::Vector2i);
	void actions(Game&, sf::Vector2i);
	void explTextFormatting(sf::Text&, wstring& ws);
	void wordExplaining(Game&);

public:
	void runGame();
};

//-----------------------------------------------------------------------------