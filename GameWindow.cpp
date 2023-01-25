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

		sf::Vector2i pos = sf::Mouse::getPosition(*this);
		clear(sf::Color::White);
		menu.setAllTextBlack();
		menu.changeColorOnHover(pos);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (menu.isStartGame(pos)) 
				break;
			menu.mouseClickHandling(pos);
		}
		menu.drawMenu(*this);
		display();
	}
	return menu.getMenuSettings();
}

//------------------------------------------------------------------------------------------------

bool GameWindow::check_event(sf::Event& event, Game& game, sf::Vector2i& pixelPos)
{
	while (pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			close();

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.key.code == sf::Mouse::Left)
				if (game.menu_text.getGlobalBounds().contains(pixelPos.x, pixelPos.y))
					return false;
				else for (int i = 0; i < game.sprites.size(); i++)
					if (game.sprites[i].getGlobalBounds().contains(pixelPos.x, pixelPos.y))
					{
						game.setMotion(true);
						game.setdX(pixelPos.x - game.sprites[i].getPosition().x);
						game.setdY(pixelPos.y - game.sprites[i].getPosition().y);
						game.myspr = &game.sprites[i];
						break;
					}
			if (event.key.code == sf::Mouse::Right)
				for (int i = 0; i < game.sprites.size(); i++)
					if (game.sprites[i].getGlobalBounds().contains(pixelPos.x, pixelPos.y))
					{
						game.setHiding(true);
						game.setdX(pixelPos.x - game.sprites[i].getPosition().x);
						game.setdY(pixelPos.y - game.sprites[i].getPosition().y);
						game.myspr = &game.sprites[i];
						break;
					}
		}

		if (event.type == sf::Event::MouseButtonReleased)
			if (event.key.code == sf::Mouse::Left && game.getMotion())
			{
				game.setMotion(false);
				game.myspr->setColor(sf::Color::White);
				if (game.myspr->getLetterHiding())
					game.myspr->setColor(sf::Color{ 255,255,255,20 });
				int i = 0;
				for (; i < game.rectangles.size(); i++)
					if (game.rectangles[i].getGlobalBounds().contains(pixelPos.x, pixelPos.y) && !game.rectangles[i].getFilling())
					{
						if (game.myspr->getConnectedRectangle())
							game.myspr->getConnectedRectangle()->setFilling(false);
						game.myspr->setPosition(game.rectangles[i].getPosition().x, game.rectangles[i].getPosition().y);
						game.myspr->connectRectangle(&game.rectangles[i]);
						game.rectangles[i].setFilling(true);
						game.setLetterInWord(i, game.myspr->getLetter());
						break;
					}
				if (i == game.rectangles.size())
				{
					game.myspr->setStartPosition();
					if (game.myspr->getConnectedRectangle())
						game.myspr->getConnectedRectangle()->setFilling(false);
					game.myspr->connectRectangle(nullptr);
				}
				if (game.allRectanglesFull() && !game.isWrongWord())
				{
					pair<int, int> result = game.getResult();
					game.result_sprites[result.first].setPosition(game.resultrect1.getPosition());
					game.result_sprites2[result.second].setPosition(game.resultrect2.getPosition());
					string s{ game.word + " - " + to_string(result.first) + ":" + to_string(result.second) };
					game.history.push_back(sf::Text{ filesystem::path(s).wstring(), game.font, 18 });
					game.history.back().setPosition(500, game.history.size() * 20);
					game.history.back().setFillColor(sf::Color::Blue);
					if (result.first == game.wordSize() && result.second == game.wordSize())
						game.win_text.setFillColor(sf::Color::Magenta);
				}
			}
		game.menu_text.setFillColor(sf::Color::Black);
		if (game.menu_text.getGlobalBounds().contains(pixelPos.x, pixelPos.y))
			game.menu_text.setFillColor(sf::Color::Blue);
		if (game.getMotion())
		{
			game.myspr->setColor(sf::Color::Green);
			game.myspr->setPosition(pixelPos.x - game.getdX(), pixelPos.y - game.getdY());
		}
		if (game.getHiding())
		{
			(game.myspr->getColor() == sf::Color::White) ? game.myspr->setColor(sf::Color{ 255,255,255,20 }) : game.myspr->setColor(sf::Color::White);
			game.myspr->getLetterHiding() ? game.myspr->setLetterHiding(false) : game.myspr->setLetterHiding(true);
			game.myspr->setStartPosition();
			if (game.myspr->getConnectedRectangle())
				game.myspr->getConnectedRectangle()->setFilling(false);
			game.myspr->connectRectangle(nullptr);
			game.setHiding(false);
		}
		if (!game.allRectanglesFull())
			for (int i = 0; i < game.result_sprites.size(); i++)
			{
				game.result_sprites[i].setStartPosition();
				game.result_sprites2[i].setStartPosition();
			}
	}
	return true;
}

//------------------------------------------------------------------------------------------------

void GameWindow::play(Game& game)
{
	bool isGame = true;
	while (isOpen() && isGame)
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(*this);

		sf::Event event;
		isGame = check_event(event, game, pixelPos);

		clear(sf::Color::White);
		game.drawAll(*this);
		display();
	}
}

//------------------------------------------------------------------------------------------------

void GameWindow::runGame()
{
	while (isOpen())
	{
		Game game{ menu() };
		play(game);
	}
}

//-----------------------------------------------------------------------------------------------