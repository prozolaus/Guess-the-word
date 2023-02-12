#include "Game.h"

Game::Game(MenuSettings ms)
	: alphabet_size{ 33 },
	dictionary{ ms.language, ms.letters, ms.level },
	language{ ms.language },
	letters{ ms.letters },
	word_size{int(letters)},
	motion{ false }, hiding{ false },
	dX{ 0 }, dY{ 0 },
	textures{ alphabet_size },
	result_textures{ word_size + 1 },
	bgcolor{sf::Color::White}
{
	setGame();
}

void Game::setGame()
{
	word.resize(word_size, ' ');
	for (int i = 0; i < alphabet_size; i++)
	{
		string lng = language == Language::UKR ? "ukr\\" : "rus\\";
		string s = "letters\\" + lng + std::to_string(i) + ".png";
		textures[i].loadFromFile(s);
	}
	for (int i = 0, count = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
		{
			if (count == 33)
				break;
			sprites.push_back(MyLetterSprite{ textures[count++] });
			sprites.back().setStartCoords(j * 64, i * 64);
		}
	rectangles.assign(word_size, MyRectangleShape{ sf::Vector2f(64.f, 64.f) });
	for (int i = 0, xr = letters == Letters::THREE ? 150 : 118; i < rectangles.size(); i++)
	{
		rectangles[i].setFillColor(sf::Color(175, 180, 240));
		rectangles[i].move(xr + i * 64, 450);
		rectangles[i].setOutlineColor(sf::Color::Black);
		rectangles[i].setOutlineThickness(1.f);
	}
	for (int i = 0; i <= word_size; i++)
	{
		std::string s = "numbers\\" + std::to_string(i) + ".png";
		result_textures[i].loadFromFile(s);
		result_sprites.push_back(MyLetterSprite{ result_textures[i] });
		result_sprites.back().setStartCoords(-200, i * 64);
		result_sprites2.push_back(MyLetterSprite{ result_textures[i] });
		result_sprites2.back().setStartCoords(-100, i * 64);
	}
	setResultRect(resultrect1, 166.f);
	setResultRect(resultrect2, 262.f);
	setResultDot(dot1, 570.f);
	setResultDot(dot2, 590.f);
	setText();
	letterInit();
}

void Game::setResultDot(sf::CircleShape& dot, int y)
{
	dot.setRadius(3);
	dot.setPosition(243, y);
	dot.setFillColor(sf::Color{ 220,220,220 });
	dot.setOutlineThickness(1);
}

void Game::setResultRect(sf::RectangleShape& rect, float x)
{
	rect = sf::RectangleShape{ sf::Vector2f(64.f, 64.f) };
	rect.move(x, 550.f);
	rect.setFillColor(sf::Color::Yellow);
	rect.setOutlineColor(sf::Color::Black);
	rect.setOutlineThickness(1.f);
}

void Game::setText()
{
	string fontname = "fonts\\Arial.ttf";
	if (!font.loadFromFile(fontname))
		throw runtime_error("Game::setGame(): cannot open a font file " + fontname);

	wstring congrats = language == Language::UKR ? L"Перемога!" : L"Победа!";
	wstring wrword = language == Language::UKR ? L"Такого слова немає в базі даних гри!" : L"Такого слова нет в базе данных игры!";
	wstring explword = language == Language::UKR ? L"Показати тлумачення слова" : L"Показать толкование слова";
	wstring clword = language == Language::UKR ? L"Підказка" : L"Подсказка";
	result_text.setFont(font);
	result_text.setFillColor(sf::Color::Blue);
	result_text.move(20, 565);
	result_text.setString(L"Результат:");
	result_text.setCharacterSize(28);
	win_text.setFont(font);
	win_text.setFillColor(bgcolor);
	win_text.move(350, 555);
	win_text.setString(congrats);
	win_text.setCharacterSize(40);
	menu_text.setFont(font);
	menu_text.setFillColor(sf::Color::Black);
	menu_text.move(620, 20);
	menu_text.setString(L"Меню");
	menu_text.setCharacterSize(24);
	wrong_word_text.setFont(font);
	wrong_word_text.setCharacterSize(20);
	wrong_word_text.setFillColor(bgcolor);
	wrong_word_text.move(20, 400);
	wrong_word_text.setString(wrword);
	word_expl_text.setFont(font);
	word_expl_text.move(20, 650);
	word_expl_text.setString(explword);
	word_expl_text.setCharacterSize(24);
	clue_text.setFont(font);
	clue_text.move(600, 660);
	clue_text.setString(clword);
	clue_text.setCharacterSize(20);
	clue_text.setFillColor(sf::Color::Black);
	restart_text.setFont(font);
	restart_text.setFillColor(sf::Color::Black);
	restart_text.move(620, 60);
	restart_text.setString(L"Рестарт");
	restart_text.setCharacterSize(20);
}

void Game::letterInit()
{
	int count = -32;
	if (language == Language::UKR)
		for (int i = 0; i < alphabet_size; i++)
		{
			if (i == 4)
				sprites[i].setLetter(char(-76));	//ґ
			else if (i == 7)
				sprites[i].setLetter(char(-70));	//є
			else if (i == 11)
				sprites[i].setLetter(char(-77));	//і
			else if (i == 12)
				sprites[i].setLetter(char(-65));	//ї
			else if (i == 30)
				sprites[i].setLetter(char(-4));	//ь
			else if (i == 31)
				sprites[i].setLetter(char(-2));	//ю
			else if (i == 32)
				sprites[i].setLetter(char(-1));	//я
			else
				sprites[i].setLetter(char(count++));
		}
	else if (language == Language::RUS)
		for (int i = 0; i < alphabet_size; i++)
		{
			if (i == 6)
				sprites[i].setLetter(char(-72));	//ё
			else
				sprites[i].setLetter(char(count++));
		}
}

bool Game::allRectanglesFull()
{
	for (int i = 0; i < rectangles.size(); i++)
		if (rectangles[i].getFilling() == false)
			return false;
	return true;
}

void Game::drawAll(sf::RenderWindow& window)
{
	for (int i = 0; i < history.size(); i++)
		window.draw(history[i]);

	window.draw(result_text);
	window.draw(menu_text);
	window.draw(clue_text);
	window.draw(win_text);
	window.draw(wrong_word_text);
	window.draw(word_expl_text);
	window.draw(restart_text);
	window.draw(dot1);
	window.draw(dot2);

	for (int i = 0; i < clues.size(); i++)
		window.draw(clues[i]);

	for (int i = 0; i < rectangles.size(); i++)
		window.draw(rectangles[i]);

	for (int i = sprites.size() - 1; i >= 0; i--)
		window.draw(sprites[i]);

	window.draw(resultrect1);
	window.draw(resultrect2);

	for (int i = 0; i < result_sprites.size(); i++)
	{
		window.draw(result_sprites[i]);
		window.draw(result_sprites2[i]);
	}
}

bool Game::isAnySpriteContainMousePos()
{
	for (int i = 0; i < sprites.size(); i++)
		if (sprites[i].getGlobalBounds().contains(pixelPos.x, pixelPos.y))
		{
			dX = pixelPos.x - sprites[i].getPosition().x;
			dY = pixelPos.y - sprites[i].getPosition().y;
			myspr = &sprites[i];
			return true;
		}
	return false;
}

bool Game::isAnySpriteinRect()
{
	motion = false;
	myspr->setColor(sf::Color::White);
	if (myspr->getLetterHiding())
		myspr->setColor(sf::Color{ 255,255,255,20 });
	int i = 0;
	for (; i < rectangles.size(); i++)
		if (rectangles[i].getGlobalBounds().contains(pixelPos.x, pixelPos.y) && !rectangles[i].getFilling())
		{
			if (myspr->getConnectedRectangle())
				myspr->getConnectedRectangle()->setFilling(false);
			myspr->setPosition(rectangles[i].getPosition().x, rectangles[i].getPosition().y);
			myspr->connectRectangle(&rectangles[i]);
			rectangles[i].setFilling(true);
			word.at(i) = myspr->getLetter();
			break;
		}
	return i == rectangles.size() ? false : true;
}

void Game::resetCurrentSprite()
{
	myspr->setStartPosition();
	if (myspr->getConnectedRectangle())
		myspr->getConnectedRectangle()->setFilling(false);
	myspr->connectRectangle(nullptr);
}

void Game::moveSprite()
{
	myspr->setColor(sf::Color::Green);
	myspr->setPosition(pixelPos.x - dX, pixelPos.y - dY);
}

void Game::setSpriteHidingOptions()
{
	(myspr->getColor() == sf::Color::White) ? myspr->setColor(sf::Color{ 255,255,255,45 }) : myspr->setColor(sf::Color::White);
	if (myspr->getLetterHiding())
	{
		myspr->setLetterHiding(false);
		auto it = find(hidden_letters.begin(), hidden_letters.end(), myspr->getLetter());
		hidden_letters.erase(it);
	}
	else
	{
		myspr->setLetterHiding(true);
		hidden_letters.push_back(myspr->getLetter());
	}
}

void Game::resetResultSprites()
{
	for (int i = 0; i < result_sprites.size(); i++)
	{
		result_sprites[i].setStartPosition();
		result_sprites2[i].setStartPosition();
	}
}

void Game::resetRectangleLetters()
{
	for (int i = 0; i < rectangles.size(); i++)
		if (!rectangles[i].getFilling())
			word.at(i) = ' ';
}

void Game::resultHandling()
{
	pair<int, int> result = dictionary.get_result(word);
	result_sprites[result.first].setPosition(resultrect1.getPosition());
	result_sprites2[result.second].setPosition(resultrect2.getPosition());
	history_vs.push_back(word);
	string s{ word + " - " + to_string(result.first) + ":" + to_string(result.second) };
	sf::Text t{ filesystem::path(s).wstring(), font, 22 };
	history.push_back(t);
	history.back().setPosition(470, history.size() * 24);
	history.back().setFillColor(sf::Color::Blue);
	if (history.size() > 1 && history[history.size() - 2].getString() == t.getString())
		history.pop_back();
	if (result.first == word_size && result.second == word_size)
		win_text.setFillColor(sf::Color::Magenta);
	else if (result.first == 0 && result.second == 0)
		for (int i = 0; i < sprites.size(); i++)
			if (sprites[i].getConnectedRectangle())
			{
				myspr = &sprites[i];
				myspr->setColor(sf::Color::White);
				setSpriteHidingOptions();
				myspr = nullptr;
			}
}

void Game::updateClueWords()
{
	unordered_map<unsigned int, char> umap;
	for (int i = 0; i < word.size(); i++)
		if (word[i] != ' ')
			umap.insert(make_pair(i, word[i]));
	if (umap.size() == word_size) return;
	clue_words = dictionary.get_clue_words(umap, history_vs, hidden_letters);
	clues.resize(clue_words.size());
	for (int i = 0; i < clues.size(); i++)
	{
		clues[i] = sf::Text{ filesystem::path(clue_words[i]).wstring(), font, 16 };
		clues[i].move(630, 630 - (i * 20));
		clues[i].setFillColor(sf::Color::Black);
	}
	if (clue_words.size() == 1 && clue_words[0].size() > word.size())
	{
		clues[0].setPosition(570, 630);
		clues[0].setFillColor(sf::Color::Red);
	}
}

void Game::hideClues()
{
	for (sf::Text& c : clues)
		c.setFillColor(bgcolor);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

bool Game::play(sf::RenderWindow& window)
{
	while (window.isOpen())
	{
		pixelPos = sf::Mouse::getPosition(window);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.key.code == sf::Mouse::Left)
					if (menu_text.getGlobalBounds().contains(pixelPos.x, pixelPos.y))
						return false;
					else if (restart_text.getGlobalBounds().contains(pixelPos.x, pixelPos.y))
						return true;
					else if (clue_text.getGlobalBounds().contains(pixelPos.x, pixelPos.y))
						updateClueWords();
					else if (isAnySpriteContainMousePos())
						motion = true;

				if (event.key.code == sf::Mouse::Right)
					if (isAnySpriteContainMousePos())
						hiding = true;
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.key.code == sf::Mouse::Left && word_expl_text.getGlobalBounds().contains(pixelPos.x, pixelPos.y))
					if (allRectanglesFull() && !dictionary.is_wrong_word(word)) wordExplaining(window);
				if (event.key.code == sf::Mouse::Left && motion)
					oneTimeLeftActions();
				if (event.key.code == sf::Mouse::Right && hiding)
					oneTimeRightActions();
			}
		}
		actions();
		window.clear(sf::Color::White);
		drawAll(window);
		window.display();
	}
}

//------------------------------------------------------------------------------------------------


void Game::oneTimeLeftActions()
{
	if (!isAnySpriteinRect())
		resetCurrentSprite();
	if (allRectanglesFull() && !dictionary.is_wrong_word(word))
	{
		resultHandling();
		hideClues();
	}
	else resetResultSprites();
}

//------------------------------------------------------------------------------------------------

void Game::oneTimeRightActions()
{
	setSpriteHidingOptions();
	resetCurrentSprite();
	hiding = false;
	if (!allRectanglesFull())
		resetResultSprites();
}

//------------------------------------------------------------------------------------------------

void Game::actions()
{
	menu_text.getGlobalBounds().contains(pixelPos.x, pixelPos.y) ? menu_text.setFillColor(sf::Color::Blue) : menu_text.setFillColor(sf::Color::Black);
	clue_text.getGlobalBounds().contains(pixelPos.x, pixelPos.y) ? clue_text.setFillColor(sf::Color::Blue) : clue_text.setFillColor(sf::Color::Black);
	restart_text.getGlobalBounds().contains(pixelPos.x, pixelPos.y) ? restart_text.setFillColor(sf::Color::Blue) : restart_text.setFillColor(sf::Color::Black);
	wrong_word_text.setFillColor(bgcolor);
	if (allRectanglesFull())
		if (!dictionary.is_wrong_word(word))
			word_expl_text.getGlobalBounds().contains(pixelPos.x, pixelPos.y) ? word_expl_text.setFillColor(sf::Color::Blue) : word_expl_text.setFillColor(sf::Color::Cyan);
		else wrong_word_text.setFillColor(sf::Color::Red);
	else
	{
		word_expl_text.setFillColor(bgcolor);
		resetRectangleLetters();
	}
	if (motion) moveSprite();
}

//------------------------------------------------------------------------------------------------

void Game::explTextFormatting(sf::RenderWindow& window, sf::Text& text, wstring& ws)
{
	for (int i = 0; i < ws.size(); i++)
	{
		if (ws[i] == L' ' && (ws[i + 1] == L'I' || ws[i + 1] == L'V') && (ws[i - 1] == L'.' || ws[i - 1] == L' '))
			ws.replace(ws.begin() + i, ws.begin() + i + 1, L"\n\n");

		else if (ws[i] == L' ' && ws[i + 1] >= L'0' && ws[i + 1] <= L'9' && ws[i + 2] == L'.')
			ws[i] = L'\n';

		else if (text.findCharacterPos(i).x > window.getSize().x - 50)
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

void Game::wordExplaining(sf::RenderWindow& window)
{
	sf::Font font;
	string fontname = "fonts\\Arial.ttf";
	if (!font.loadFromFile(fontname))
		throw runtime_error("GameWindow::wordExplaining(): cannot open a font file " + fontname);
	wstring ws = filesystem::path(dictionary.word_explanation(word)).wstring();
	wstring backstr = language == Language::UKR ? L"Для виходу на попередній екран натисніть Esc або закрийте вікно" : L"Для выхода на предыдущий экран нажмите Esc или закройте окно";
	sf::Text text{ ws, font, 16 }, back_text{ backstr, font, 18 };
	explTextFormatting(window, text, ws);
	back_text.move(50, window.getSize().y - 100);
	back_text.setFillColor(sf::Color::Red);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				return;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			break;

		window.clear(sf::Color::White);
		window.draw(text);
		window.draw(back_text);
		window.display();
	}
}