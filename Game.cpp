#include "Game.h"

Game::Game(MenuSettings ms)
	: alphabet_size{ 33 },
	dictionary{ ms.language, ms.letters, ms.level },
	language{ ms.language },
	letters{ ms.letters },
	motion{ false }, hiding{ false },
	dX{ 0 }, dY{ 0 },
	textures{ alphabet_size },
	result_textures{ wordSize() + 1 },
	bgcolor{sf::Color::White}
{
	setGame();
}

void Game::setGame()
{
	word.resize(wordSize());
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
	rectangles.assign(wordSize(), MyRectangleShape{ sf::Vector2f(64.f, 64.f) });
	for (int i = 0, xr = letters == Letters::THREE ? 150 : 118; i < rectangles.size(); i++)
	{
		rectangles[i].setFillColor(sf::Color(175, 180, 240));
		rectangles[i].move(xr + i * 64, 450);
		rectangles[i].setOutlineColor(sf::Color::Black);
		rectangles[i].setOutlineThickness(1.f);
	}
	for (int i = 0; i <= wordSize(); i++)
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
	setText();
	letterInit();
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
	wrong_word_text.setFillColor(bgcolor);
	wrong_word_text.move(20, 400);
	wrong_word_text.setString(wrword);
	word_expl_text.setFont(font);
	word_expl_text.move(20, 650);
	word_expl_text.setString(explword);
	word_expl_text.setCharacterSize(24);
}

bool Game::isWrongWord()
{
	return dictionary.is_wrong_word(word) ? true : false;
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
	window.draw(win_text);
	window.draw(wrong_word_text);
	window.draw(word_expl_text);

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

bool Game::isAnySpriteContain(int x, int y)
{
	for (int i = 0; i < sprites.size(); i++)
		if (sprites[i].getGlobalBounds().contains(x, y))
		{
			setdX(x - sprites[i].getPosition().x);
			setdY(y - sprites[i].getPosition().y);
			myspr = &sprites[i];
			return true;
		}
	return false;
}

bool Game::isAnySpriteinRect(int x, int y)
{
	setMotion(false);
	myspr->setColor(sf::Color::White);
	if (myspr->getLetterHiding())
		myspr->setColor(sf::Color{ 255,255,255,20 });
	int i = 0;
	for (; i < rectangles.size(); i++)
		if (rectangles[i].getGlobalBounds().contains(x, y) && !rectangles[i].getFilling())
		{
			if (myspr->getConnectedRectangle())
				myspr->getConnectedRectangle()->setFilling(false);
			myspr->setPosition(rectangles[i].getPosition().x, rectangles[i].getPosition().y);
			myspr->connectRectangle(&rectangles[i]);
			rectangles[i].setFilling(true);
			setLetterInWord(i, myspr->getLetter());
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

void Game::moveSprite(int x, int y)
{
	myspr->setColor(sf::Color::Green);
	myspr->setPosition(x - getdX(), y - getdY());
}

void Game::setSpriteHidingOptions()
{
	(myspr->getColor() == sf::Color::White) ? myspr->setColor(sf::Color{ 255,255,255,20 }) : myspr->setColor(sf::Color::White);
	myspr->getLetterHiding() ? myspr->setLetterHiding(false) : myspr->setLetterHiding(true);
}

void Game::resetResultSprites()
{
	for (int i = 0; i < result_sprites.size(); i++)
	{
		result_sprites[i].setStartPosition();
		result_sprites2[i].setStartPosition();
	}
}

void Game::resultHandling()
{
	pair<int, int> result = dictionary.get_result(word);
	result_sprites[result.first].setPosition(resultrect1.getPosition());
	result_sprites2[result.second].setPosition(resultrect2.getPosition());
	string s{ word + " - " + to_string(result.first) + ":" + to_string(result.second) };
	sf::Text t{ filesystem::path(s).wstring(), font, 22 };
	history.push_back(t);
	history.back().setPosition(470, history.size() * 24);
	history.back().setFillColor(sf::Color::Blue);
	if (history.size() > 1 && history[history.size() - 2].getString() == t.getString())
		history.pop_back();
	if (result.first == wordSize() && result.second == wordSize())
		win_text.setFillColor(sf::Color::Magenta);
}
