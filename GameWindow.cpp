#include "GameWindow.h"

//------------------------------------------------------------------------------------------------

MenuSettings GameWindow::menu()
{
	Menu menu(getSize().x, getSize().y);

	while (isOpen())
	{
		sf::Event event;
		while (pollEvent(event))
			if (event.type == sf::Event::Closed)
				close();

		menu.pos = sf::Mouse::getPosition(*this);
		clear(sf::Color::White);
		menu.setAllTextBlack();
		menu.changeColorOnHover();

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (menu.isStartGame()) 
				break;
			menu.mouseClickHandling();
		}
		menu.drawMenu(*this);
		display();
	}
	return menu.getMenuSettings();
}


//------------------------------------------------------------------------------------------------

void GameWindow::updateTitle(MenuSettings ms)
{
	string gname = "Guess the word";
	string lang = (ms.language == Language::UKR) ? "UKR" : "RUS";
	string lrs = (ms.letters == Letters::THREE) ? "3" : "4";
	string lvl;
	switch (ms.level)
	{
	case Level::SCHOOL:	lvl = "school";	break;
	case Level::NORMAL:	lvl = "normal";	break;
	case Level::ERUDITE: lvl = "erudite"; break;
	default: break;
	}
	string title = gname + ": " + lang + " - " + lrs;
	if (ms.guesser == Guesser::PLAYER)
		title += " - " + lvl;
	setTitle(title);
}

//------------------------------------------------------------------------------------------------

void GameWindow::runGame()
{
	MenuSettings ms;
	while (isOpen())
	{
		if (!restart)
		{
			ms = menu();
			updateTitle(ms);
		}
		Game game{ ms };
		restart = game.play(*this);
	}
}

//-----------------------------------------------------------------------------------------------