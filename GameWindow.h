#pragma once
#include "Game.h"

class GameWindow : public sf::RenderWindow
{
	using sf::RenderWindow::RenderWindow;
	bool check_event(sf::Event& event, Game& game, sf::Vector2i& pixelPos);
	MenuSettings menu();
	void play(Game&);

public:
	void runGame();
};