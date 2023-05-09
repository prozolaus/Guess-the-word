#include "GameWindow.h"

//------------------------------------------------------------------------------------------------

GameWindow::GameWindow(sf::VideoMode vm, const sf::String wndwname, sf::Uint32 style)
	: sf::RenderWindow(vm, wndwname, style)
{
	windowname = wndwname;
}

//------------------------------------------------------------------------------------------------

Settings GameWindow::showmenu(Menu& menu)
{
	while (isOpen())
	{
		menu.setMousePos(sf::Mouse::getPosition(*this));
		sf::Event event;
		while (pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				close();
			if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
			{
				if (menu.isStartGame())
					return menu.getMenuSettings();
				menu.mouseClickHandling();
			}
		}
		clear(sf::Color::White);
		menu.setAllTextBlack();
		menu.changeColorOnHover();
		menu.drawMenu(*this);
		display();
	}
	return menu.getMenuSettings();
}

//------------------------------------------------------------------------------------------------

void GameWindow::wait(Language lang)
{
	string fontname = "fonts\\Academy.ttf";
	sf::Font font;
	font.loadFromFile(fontname);
	if (!font.loadFromFile(fontname))
		throw runtime_error("GameWindow::wait(): cannot open a font file " + fontname);
	clear(sf::Color::White);
	wstring phrase = lang == Language::UKR ? L"Будь ласка, зачекайте!" : L"Пожалуйста, подождите!";
	sf::Text text{ phrase, font, 30 };
	text.setPosition(getSize().x / 2 - text.getGlobalBounds().width / 2, getSize().y / 2);
	text.setFillColor(sf::Color::Red);
	draw(text);
	display();
}

//------------------------------------------------------------------------------------------------

void GameWindow::updateTitle(Settings ms)
{
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
	string title = windowname + ": " + lang + " - " + lrs;
	if (ms.guesser == Guesser::PLAYER)
		title += " - " + lvl;
	setTitle(title);
}

//------------------------------------------------------------------------------------------------

void GameWindow::runGame()
{
	Settings ms;
	Menu menu(getSize().x, getSize().y);
	bool firstgame = true;
	while (isOpen())
	{
		if (!ms.restart)
		{
			if (!firstgame)
				menu.set(ms);
			ms = showmenu(menu);
			firstgame = false;
			updateTitle(ms);
		}
		wait(ms.language);
		Game game{ ms };
		ms = game.play(*this);
	}
}

//-----------------------------------------------------------------------------------------------