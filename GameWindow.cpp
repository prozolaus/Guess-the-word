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

void GameWindow::play(Game& game)
{
	gaming = true;
	while (isOpen() && gaming)
	{
		eventHandling(game);
		clear(sf::Color::White);
		game.drawAll(*this);
		display();
	}
}

//------------------------------------------------------------------------------------------------

void GameWindow::eventHandling(Game& game)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(*this);
	sf::Event event;
	while (pollEvent(event))
	{
		if (event.type == sf::Event::Closed) 
			close();
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.key.code == sf::Mouse::Left)
				if (game.isMenuTextContain(pixelPos.x, pixelPos.y))
					gaming = false;
				else if (game.isClueTextContain(pixelPos.x, pixelPos.y))
					game.updateClueWords();
				else if (game.isAnySpriteContain(pixelPos.x, pixelPos.y)) 
					game.setMotion(true);

			if (event.key.code == sf::Mouse::Right)
					if (game.isAnySpriteContain(pixelPos.x, pixelPos.y)) 
						game.setHiding(true);
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (event.key.code == sf::Mouse::Left && game.isExplTextContain(pixelPos.x, pixelPos.y))
				if (game.allRectanglesFull() && !game.isWrongWord()) wordExplaining(game);
			if (event.key.code == sf::Mouse::Left && game.getMotion())
				oneTimeLeftActions(game, pixelPos);
			if (event.key.code == sf::Mouse::Right && game.getHiding())
				oneTimeRightActions(game, pixelPos);
		}
	}
	actions(game, pixelPos);
}

//------------------------------------------------------------------------------------------------

void GameWindow::oneTimeLeftActions(Game& game, sf::Vector2i pixelPos)
{
	if (!game.isAnySpriteinRect(pixelPos.x, pixelPos.y))
		game.resetCurrentSprite();
	if (game.allRectanglesFull() && !game.isWrongWord())
	{
		game.resultHandling();
		game.hideClues();
	}
	else game.resetResultSprites();
}

//------------------------------------------------------------------------------------------------

void GameWindow::oneTimeRightActions(Game& game, sf::Vector2i pixelPos)
{
	game.setSpriteHidingOptions();
	game.resetCurrentSprite();
	game.setHiding(false);
	if (!game.allRectanglesFull())
		game.resetResultSprites();
}

//------------------------------------------------------------------------------------------------

void GameWindow::actions(Game& game, sf::Vector2i pixelPos)
{
	game.isMenuTextContain(pixelPos.x, pixelPos.y) ? game.setMenuTextColor(sf::Color::Blue) : game.setMenuTextColor(sf::Color::Black);
	game.isClueTextContain(pixelPos.x, pixelPos.y) ? game.setClueTextColor(sf::Color::Blue) : game.setClueTextColor(sf::Color::Black);
	game.setWrongWordTextColor(game.getBgColor());
	if (game.allRectanglesFull())
		if (!game.isWrongWord())
			game.isExplTextContain(pixelPos.x, pixelPos.y) ? game.setExplTextColor(sf::Color::Blue) : game.setExplTextColor(sf::Color::Cyan);
		else game.setWrongWordTextColor(sf::Color::Red);
	else
	{
		game.setExplTextColor(game.getBgColor());
		game.resetRectangleLetters();
	}
	if (game.getMotion()) game.moveSprite(pixelPos.x, pixelPos.y);
}

//------------------------------------------------------------------------------------------------

void GameWindow::explTextFormatting(sf::Text& text, wstring& ws)
{
	for (int i = 0; i < ws.size(); i++)
	{
		if (ws[i] == L' ' && (ws[i + 1] == L'I' || ws[i + 1] == L'V') && ws[i - 1] == L'.')
			ws.replace(ws.begin() + i, ws.begin() + i + 1, L"\n\n");

		else if (ws[i] == L' ' && ws[i + 1] >= L'0' && ws[i + 1] <= L'9' && ws[i + 2] == L'.')
			ws[i] = L'\n';

		else if (text.findCharacterPos(i).x > this->getSize().x - 50)
		{
			while (ws[i] != L' ') --i;
			ws.replace(ws.begin() + i, ws.begin() + i + 1, L"\n");
		}
		text.setString(ws);
	}
	text.move(20, 20);
	text.setFillColor(sf::Color::Black);
}

//------------------------------------------------------------------------------------------------

void GameWindow::wordExplaining(Game& game)
{
	sf::Font font;
	string fontname = "fonts\\Arial.ttf";
	if (!font.loadFromFile(fontname))
		throw runtime_error("GameWindow::wordExplaining(): cannot open a font file " + fontname);
	wstring ws = game.getWordExplanation();
	wstring backstr = game.getLanguage() == Language::UKR ? L"Для виходу на попередній екран натисніть Esc або закрийте вікно" : L"Для выхода на предыдущий экран нажмите Esc или закройте окно";
	sf::Text text{ ws, font, 16 }, back_text{backstr, font, 18};
	explTextFormatting(text, ws);
	back_text.move(50, getSize().y - 100);
	back_text.setFillColor(sf::Color::Red);

	while (isOpen())
	{
		sf::Event event;
		while (pollEvent(event))
			if (event.type == sf::Event::Closed)
				return;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			break;

		clear(sf::Color::White);
		draw(text);
		draw(back_text);
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