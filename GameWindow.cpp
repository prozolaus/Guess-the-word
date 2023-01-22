#include "GameWindow.h"

void GameWindow::runGame()
{
	while (isOpen())
	{
		Game game{ menu() };
		play(game);
	}
}

//------------------------------------------------------------------------------------------------

MenuSettings GameWindow::menu()
{
	MenuSettings mset{};
	bool isMenu = true,
		UA_lang = false, RU_lang = false,
		three_ls = false, four_ls = false,
		school_lvl = false, normal_lvl = false, erudite_lvl = false;
	const int x = 100, y = 100;
	sf::Font font;
	font.loadFromFile("Bebas_Neue_Cyrillic.ttf");

	sf::Text start{ "Start", font }, lang{ "Language:", font }, ua{ "UA", font }, ru{ "RU", font };
	start.setFillColor(sf::Color::Black);
	lang.setFillColor(sf::Color::Black);
	ua.setFillColor(sf::Color::Black);
	ru.setFillColor(sf::Color::Black);
	start.setPosition(300, 600);
	lang.setPosition(x, y);
	ua.setPosition(x + lang.getGlobalBounds().width + x / 3, y);
	ru.setPosition(ua.getPosition().x + x / 2, y);

	sf::Text lttrs{ "Letters:", font }, three{ "3", font }, four{ "4", font };
	lttrs.setFillColor(sf::Color::Black);
	three.setFillColor(sf::Color::Black);
	four.setFillColor(sf::Color::Black);
	lttrs.setPosition(x, 1.5 * y);
	three.setPosition(ua.getPosition().x, 1.5 * y);
	four.setPosition(ru.getPosition().x, 1.5 * y);

	sf::Text lvl{ "Level:", font }, school{ "School", font }, normal{ "Normal", font }, erudite{ "Erudite", font };
	lvl.setFillColor(sf::Color::Black);
	school.setFillColor(sf::Color::Black);
	normal.setFillColor(sf::Color::Black);
	erudite.setFillColor(sf::Color::Black);
	lvl.setPosition(x, 2 * y);
	school.setPosition(three.getPosition().x, 2 * y);
	normal.setPosition(school.getPosition().x + school.getGlobalBounds().width + x / 3, 2 * y);
	erudite.setPosition(normal.getPosition().x + normal.getGlobalBounds().width + x / 3, 2 * y);

	while (isMenu && isOpen())
	{
		sf::Event event;
		while (pollEvent(event))
			if (event.type == sf::Event::Closed)
				close();

		sf::Vector2i pos = sf::Mouse::getPosition(*this);
		clear(sf::Color::White);
		start.setFillColor(sf::Color::Black);
		if (!UA_lang) ua.setFillColor(sf::Color::Black);
		if (!RU_lang) ru.setFillColor(sf::Color::Black);
		if (!three_ls) three.setFillColor(sf::Color::Black);
		if (!four_ls) four.setFillColor(sf::Color::Black);
		if (!school_lvl) school.setFillColor(sf::Color::Black);
		if (!normal_lvl) normal.setFillColor(sf::Color::Black);
		if (!erudite_lvl) erudite.setFillColor(sf::Color::Black);

		if (ua.getGlobalBounds().contains(pos.x, pos.y))
			UA_lang ? ua.setFillColor(sf::Color::Blue) : ua.setFillColor(sf::Color::Green);
		if (ru.getGlobalBounds().contains(pos.x, pos.y))
			RU_lang ? ru.setFillColor(sf::Color::Blue) : ru.setFillColor(sf::Color::Green);
		if (three.getGlobalBounds().contains(pos.x, pos.y))
			three_ls ? three.setFillColor(sf::Color::Blue) : three.setFillColor(sf::Color::Green);
		if (four.getGlobalBounds().contains(pos.x, pos.y))
			four_ls ? three.setFillColor(sf::Color::Blue) : four.setFillColor(sf::Color::Green);
		if (school.getGlobalBounds().contains(pos.x, pos.y))
			school_lvl ? school.setFillColor(sf::Color::Blue) : school.setFillColor(sf::Color::Green);
		if (normal.getGlobalBounds().contains(pos.x, pos.y))
			normal_lvl ? normal.setFillColor(sf::Color::Blue) : normal.setFillColor(sf::Color::Green);
		if (erudite.getGlobalBounds().contains(pos.x, pos.y))
			erudite_lvl ? erudite.setFillColor(sf::Color::Blue) : erudite.setFillColor(sf::Color::Green);
		if (start.getGlobalBounds().contains(pos.x, pos.y))
			start.setFillColor(sf::Color::Blue);


		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (start.getGlobalBounds().contains(pos.x, pos.y) && (UA_lang || RU_lang) && (three_ls || four_ls) && (school_lvl || normal_lvl || erudite_lvl))
				isMenu = false;
			if (ua.getGlobalBounds().contains(pos.x, pos.y))
			{
				ua.setFillColor(sf::Color::Blue);
				mset.language = Language::UKR;
				UA_lang = true;
				RU_lang = false;
			}
			if (ru.getGlobalBounds().contains(pos.x, pos.y))
			{
				ru.setFillColor(sf::Color::Blue);
				mset.language = Language::RUS;
				RU_lang = true;
				UA_lang = false;
			}
			if (three.getGlobalBounds().contains(pos.x, pos.y))
			{
				three.setFillColor(sf::Color::Blue);
				mset.letters = Letters::THREE;
				three_ls = true;
				four_ls = false;
			}
			if (four.getGlobalBounds().contains(pos.x, pos.y))
			{
				four.setFillColor(sf::Color::Blue);
				mset.letters = Letters::FOUR;
				four_ls = true;
				three_ls = false;
			}
			if (school.getGlobalBounds().contains(pos.x, pos.y))
			{
				school.setFillColor(sf::Color::Blue);
				mset.level = Level::SCHOOL;
				school_lvl = true;
				normal_lvl = false;
				erudite_lvl = false;
			}
			if (normal.getGlobalBounds().contains(pos.x, pos.y))
			{
				normal.setFillColor(sf::Color::Blue);
				mset.level = Level::NORMAL;
				normal_lvl = true;
				erudite_lvl = false;
				school_lvl = false;
			}
			if (erudite.getGlobalBounds().contains(pos.x, pos.y))
			{
				erudite.setFillColor(sf::Color::Blue);
				mset.level = Level::ERUDITE;
				erudite_lvl = true;
				school_lvl = false;
				normal_lvl = false;
			}
		}
		draw(start);
		draw(lang);
		draw(ua);
		draw(ru);
		draw(lttrs);
		draw(three);
		draw(four);
		draw(lvl);
		draw(school);
		draw(normal);
		draw(erudite);
		display();
	}
	return mset;
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
						game.isMove = true;
						game.dX = pixelPos.x - game.sprites[i].getPosition().x;
						game.dY = pixelPos.y - game.sprites[i].getPosition().y;
						game.myspr = &game.sprites[i];
						break;
					}
			if (event.key.code == sf::Mouse::Right)
				for (int i = 0; i < game.sprites.size(); i++)
					if (game.sprites[i].getGlobalBounds().contains(pixelPos.x, pixelPos.y))
					{
						game.isHide = true;
						game.dX = pixelPos.x - game.sprites[i].getPosition().x;
						game.dY = pixelPos.y - game.sprites[i].getPosition().y;
						game.myspr = &game.sprites[i];
						break;
					}
		}

		if (event.type == sf::Event::MouseButtonReleased)
			if (event.key.code == sf::Mouse::Left && game.isMove)
			{
				game.isMove = false;
				game.myspr->setColor(sf::Color::White);
				if (game.myspr->isHidden)
					game.myspr->setColor(sf::Color{ 255,255,255,20 });
				int i = 0;
				for (; i < game.rectangles.size(); i++)
					if (game.rectangles[i].getGlobalBounds().contains(pixelPos.x, pixelPos.y) && !game.rectangles[i].isfull)
					{
						if (game.myspr->rec)
							game.myspr->rec->isfull = false;
						game.myspr->setPosition(game.rectangles[i].getPosition().x, game.rectangles[i].getPosition().y);
						game.myspr->rec = &game.rectangles[i];
						game.rectangles[i].isfull = true;
						game.word[i] = game.myspr->letter;
						break;
					}
				if (i == game.rectangles.size())
				{
					game.myspr->setStartPosition();
					if (game.myspr->rec)
						game.myspr->rec->isfull = false;
					game.myspr->rec = nullptr;
				}
			}
		game.menu_text.setFillColor(sf::Color::Black);
		if (game.menu_text.getGlobalBounds().contains(pixelPos.x, pixelPos.y))
			game.menu_text.setFillColor(sf::Color::Blue);
		if (game.isMove)
		{
			game.myspr->setColor(sf::Color::Green);
			game.myspr->setPosition(pixelPos.x - game.dX, pixelPos.y - game.dY);
		}
		if (game.isHide)
		{
			(game.myspr->getColor() == sf::Color::White) ? game.myspr->setColor(sf::Color{ 255,255,255,20 }) : game.myspr->setColor(sf::Color::White);
			game.myspr->isHidden ? game.myspr->isHidden = false : game.myspr->isHidden = true;
			game.myspr->setStartPosition();
			if (game.myspr->rec)
				game.myspr->rec->isfull = false;
			game.myspr->rec = nullptr;
			game.isHide = false;
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

		for (int i = 0; i < game.rectangles.size(); i++)
			draw(game.rectangles[i]);

		for (int i = game.sprites.size() - 1; i >= 0; i--)
			draw(game.sprites[i]);

		if (game.rectanglesFull())
		{
			pair<int, int> result = game.getResult();
			game.result_sprites[result.first].setPosition(game.resultrect1.getPosition());
			game.result_sprites2[result.second].setPosition(game.resultrect2.getPosition());
			if (result.first == game.wordSize() && result.second == game.wordSize())
				draw(game.win_text);
		}
		else
			for (int i = 0; i < game.result_sprites.size(); i++)
			{
				game.result_sprites[i].setStartPosition();
				game.result_sprites2[i].setStartPosition();
			}

		draw(game.resultrect1);
		draw(game.resultrect2);

		for (int i = 0; i < game.result_sprites.size(); i++)
		{
			draw(game.result_sprites[i]);
			draw(game.result_sprites2[i]);
		}

		draw(game.result_text);
		draw(game.menu_text);

		display();
	}
}

//-----------------------------------------------------------------------------------------------