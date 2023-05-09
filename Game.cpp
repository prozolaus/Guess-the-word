#include "Game.h"

Game::Game(Settings ms)
	: settings{ ms },
	alphabet_size{ 33 },
	dictionary{ settings.language, settings.letters, settings.level },
	sprite_size{ 64 },
	word_size{ int(settings.letters) }, fncount{ 0 }, firstsetcount{ 0 },
	motion{ false }, hiding{ false }, isEmptyFirstSet{ false }, noOptions{ false }, gameover{ false },
	dX{ 0 }, dY{ 0 },
	pixelPos{ 0, 0 },
	defsprcolor{ sf::Color::White }, bgcolor{ sf::Color{ 230, 230, 255 } }, 
	hidcolor{ sf::Color{ 255,255,255,45 } }, wincolor{ sf::Color{ 153,255,204 } },
	textures{ alphabet_size },
	result_textures{ word_size + 1 },
	myspr{ nullptr },
	result{ make_pair(-1,-1) },
	word(word_size, ' ')
{
	setGame();
	if (settings.guesser == Guesser::COMPUTER)
	{
		strset = dictionary.generate_first_set();
		nextWordFromSet();
	}
	if (settings.sound == SOUND::ON)
		startgamesound.play();
}

void Game::setGame()
{
	setTextures();
	setLetterSprites();
	setLetterRectangles();
	setResultSprites(result_sprites.first, 166);
	setResultSprites(result_sprites.second, 262);
	result_rectangles.assign(2, MyRectangleShape{ sf::Vector2f(sprite_size, sprite_size) });
	setResultRect(result_rectangles[0], 166.f);
	setResultRect(result_rectangles[1], 262.f);
	setResultDot(dot1, 570.f);
	setResultDot(dot2, 590.f);
	setFonts();
	setText();
	lettersInit();
	setImages();
	setSounds();
}

void Game::setOneImage(const std::string& imgname, sf::Texture& imgtexture, sf::Sprite& imgsprite)
{
	if (!imgtexture.loadFromFile(imgname))
		throw runtime_error("Game::setOneImage(): Cannot open an image file " + imgname);
	imgsprite.setTexture(imgtexture);
}

void Game::setImages()
{
	setOneImage("images\\firework.jpg", winimagetexture, winimagesprite);
	winimagesprite.move(20, 20);
	setOneImage("images\\speaker-off.png", soundofftexture, soundsprite);
	setOneImage("images\\speaker-on.png", soundontexture, soundsprite);
	soundsprite.move(650, 650);
	soundsprite.setTexture(settings.sound == SOUND::OFF ? soundofftexture : soundontexture);
}

void Game::setOneSound(const std::string& sndname, sf::SoundBuffer& sndbuffer, sf::Sound& snd)
{
	if (!sndbuffer.loadFromFile(sndname))
		throw runtime_error("Game::setOneSound(): Cannot open an sound file " + sndname);
	snd.setBuffer(sndbuffer);
}

void Game::setSounds()
{
	setOneSound("sounds\\win.ogg", winsoundbuffer, winsound);
	setOneSound("sounds\\inrect.ogg", inrectsoundbuffer, inrectsound);
	setOneSound("sounds\\allrect.ogg", allrectsoundbuffer, allrectsound);
	setOneSound("sounds\\wrong.ogg", wrongsoundbuffer, wrongsound);
	setOneSound("sounds\\arrow.ogg", arrowsoundbuffer, arrowsound);
	setOneSound("sounds\\hid.ogg", hidsoundbuffer, hidsound);
	setOneSound("sounds\\tostart.ogg", tostartsoundbuffer, tostartsound);
	setOneSound("sounds\\game-start.ogg", startgamesoundbuffer, startgamesound);
	setOneSound("sounds\\hoveringame.ogg", hoversoundbuffer, hoversound);
	setOneSound("sounds\\click.ogg", clicksoundbuffer, clicksound);
}

void Game::setTextures()
{
	for (int i = 0; i < alphabet_size; i++)
	{
		string lng = settings.language == Language::UKR ? "ukr\\" : "rus\\";
		string s = "letters\\" + lng + std::to_string(i) + ".png";
		textures[i].loadFromFile(s);
	}
	for (int i = 0; i <= word_size; i++)
	{
		std::string s = "numbers\\" + std::to_string(i) + ".png";
		result_textures[i].loadFromFile(s);
	}
}

void Game::setLetterSprites()
{
	int shift = settings.guesser == Guesser::PLAYER ? 0 : 500;
	for (int i = 0, count = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
		{
			if (count == alphabet_size)
				break;
			letter_sprites.push_back(MyLetterSprite{ textures[count++] });
			letter_sprites.back().setStartCoords(j * sprite_size - shift + 45, i * sprite_size + 15);
			letter_sprites.back().setColor(defsprcolor);
		}
}

void Game::setLetterRectangles()
{
	letter_rectangles.assign(word_size, MyRectangleShape{ sf::Vector2f(sprite_size, sprite_size) });
	for (int i = 0, xr = settings.letters == Letters::THREE ? 150 : 118; i < letter_rectangles.size(); i++)
	{
		letter_rectangles[i].setFillColor(settings.guesser == Guesser::COMPUTER ? sf::Color::White : sf::Color::Yellow);
		letter_rectangles[i].move(xr + i * (sprite_size + 1), 450);
		letter_rectangles[i].setOutlineColor(sf::Color::Black);
		letter_rectangles[i].setOutlineThickness(1.f);
	}
}

void Game::setResultSprites(std::vector<MyLetterSprite>& rsprites, int x)
{
	int shift = settings.guesser == Guesser::PLAYER ? 400 : 0;
	for (int i = 0; i <= word_size; i++)
	{
		rsprites.push_back(MyLetterSprite{ result_textures[i] });
		rsprites.back().setStartCoords(x - shift, (word_size - i) * sprite_size + sprite_size);
		rsprites.back().setNumber(i);
	}
}

void Game::setResultRect(sf::RectangleShape& rect, float x)
{
	rect.move(x, 550.f);
	rect.setFillColor(settings.guesser == Guesser::COMPUTER ? sf::Color::Yellow : sf::Color::White);
	rect.setOutlineColor(sf::Color::Black);
	rect.setOutlineThickness(1.f);
}

void Game::setResultDot(sf::CircleShape& dot, int y)
{
	dot.setRadius(3);
	dot.setPosition(243, y);
	dot.setFillColor(sf::Color{128,128,128});
	dot.setOutlineThickness(1);
	dot.setOutlineColor(sf::Color::Black);
}

void Game::setFonts()
{
	string fontname = "fonts\\Academy.ttf", fontname2 = "fonts\\Arial.ttf", er = "Game::setGame(): cannot open a font file ";
	if (!font.loadFromFile(fontname))
		throw runtime_error(er + fontname);
	if (!font2.loadFromFile(fontname2))
		throw runtime_error(er + fontname2);
}

void Game::setText()
{
	wstring congrats = settings.language == Language::UKR ? L"Перемога!" : L"Победа!";
	wstring wrword;
	if (settings.guesser == Guesser::PLAYER)
		wrword = settings.language == Language::UKR ? L"Такого слова немає в базі даних гри!" : L"Такого слова нет в базе данных игры!";
	else
		wrword = settings.language == Language::UKR ? L"Друга цифра не може бути більше першої!" : L"Вторая цифра не может быть больше первой!";
	wstring clword;
	if (settings.guesser == Guesser::PLAYER)
		clword = settings.language == Language::UKR ? L"Підказка" : L"Подсказка";
	wstring explword = settings.language == Language::UKR ? L"Показати тлумачення слова" : L"Показать толкование слова";

	word_text.setFont(font);
	word_text.setFillColor(sf::Color::Blue);
	word_text.move(20, 465);
	word_text.setString(L"Слово:");
	word_text.setCharacterSize(28);

	result_text.setFont(font);
	result_text.setFillColor(sf::Color::Blue);
	result_text.move(20, 565);
	result_text.setString(L"Результат:");
	result_text.setCharacterSize(28);

	up_text.setFont(font2);
	up_text.setFillColor(bgcolor);
	up_text.move(letter_rectangles.back().getPosition().x + letter_rectangles.back().getGlobalBounds().width + 10, 445);
	up_text.setString(L"↑");
	up_text.setCharacterSize(50);

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

	wrong_action_text.setFont(font);
	wrong_action_text.setCharacterSize(20);
	wrong_action_text.setFillColor(bgcolor);
	wrong_action_text.move(20, 410);
	wrong_action_text.setString(wrword);

	word_expl_text.setFont(font);
	word_expl_text.move(20, 650);
	word_expl_text.setString(explword);
	word_expl_text.setCharacterSize(24);

	restart_text.setFont(font);
	restart_text.setFillColor(sf::Color::Black);
	restart_text.move(620, 60);
	restart_text.setString(L"Рестарт");
	restart_text.setCharacterSize(22);

	clue_text.setFont(font);
	clue_text.move((settings.language == Language::RUS ? 610 : 620), 100);
	clue_text.setString(clword);
	clue_text.setCharacterSize(20);
	clue_text.setFillColor(sf::Color::Black);
}

void Game::lettersInit()
{
	int count = -32;
	if (settings.language == Language::UKR)
		for (int i = 0; i < alphabet_size; i++)
		{
			if (i == 4)
				letter_sprites[i].setLetter(char(-76));	//ґ
			else if (i == 7)
				letter_sprites[i].setLetter(char(-70));	//є
			else if (i == 11)
				letter_sprites[i].setLetter(char(-77));	//і
			else if (i == 12)
				letter_sprites[i].setLetter(char(-65));	//ї
			else if (i == 30)
				letter_sprites[i].setLetter(char(-4));	//ь
			else if (i == 31)
				letter_sprites[i].setLetter(char(-2));	//ю
			else if (i == 32)
				letter_sprites[i].setLetter(char(-1));	//я
			else
				letter_sprites[i].setLetter(char(count++));
		}
	else if (settings.language == Language::RUS)
		for (int i = 0; i < alphabet_size; i++)
		{
			if (i == 6)
				letter_sprites[i].setLetter(char(-72));	//ё
			else
				letter_sprites[i].setLetter(char(count++));
		}
}

//-------------------------------------------------------------------------------------

bool Game::allRectanglesFull()
{
	std::vector<MyRectangleShape>* vspr = nullptr;
	vspr = settings.guesser == Guesser::PLAYER ? &letter_rectangles : &result_rectangles;
	for (int i = 0; i < vspr->size(); i++)
		if (vspr->at(i).getFilling() == false)
			return false;
	return true;
}

void Game::drawAll(sf::RenderWindow& window)
{
	for (int i = 0; i < history.size(); i++)
		window.draw(history[i]);

	window.draw(word_text);
	window.draw(result_text);
	window.draw(up_text);
	window.draw(menu_text);
	window.draw(clue_text);
	window.draw(win_text);
	window.draw(wrong_action_text);
	window.draw(word_expl_text);
	window.draw(restart_text);
	window.draw(soundsprite);
	window.draw(dot1);
	window.draw(dot2);

	window.draw(result_rectangles[0]);
	window.draw(result_rectangles[1]);

	for (int i = 0; i < clues.size(); i++)
		window.draw(clues[i]);

	for (int i = 0; i < letter_rectangles.size(); i++)
		window.draw(letter_rectangles[i]);

	for (int i = letter_sprites.size() - 1; i >= 0; i--)
		window.draw(letter_sprites[i]);

	for (int i = 0; i < result_sprites.first.size(); i++)
	{
		window.draw(result_sprites.first[i]);
		window.draw(result_sprites.second[i]);
	}
	if (gameover)
		window.draw(winimagesprite);
}

bool Game::isAnySpriteContainMousePos()
{
	std::vector<MyLetterSprite>* vspr = nullptr;
	vspr = settings.guesser == Guesser::PLAYER ? &letter_sprites : &result_sprites.first;
	const int n = settings.guesser == Guesser::PLAYER ? 1 : 2;
	for (int k = 1; k <= n; k++)
	{
		if (k == 2)	vspr = &result_sprites.second;
		for (int i = 0; i < vspr->size(); i++)
			if (vspr->at(i).getGlobalBounds().contains(pixelPos.x, pixelPos.y))
			{
				myspr = &vspr->at(i);
				dX = pixelPos.x - myspr->getPosition().x;
				dY = pixelPos.y - myspr->getPosition().y;
				return true;
			}
	}
	return false;
}

bool Game::isAnySpriteinRect()
{
	std::vector<MyRectangleShape>* vrects = nullptr;
	vrects = settings.guesser == Guesser::PLAYER ? &letter_rectangles : &result_rectangles;
	motion = false;
	myspr->setColor(defsprcolor);
	if (settings.guesser == Guesser::PLAYER && myspr->getLetterHiding())
		myspr->setColor(hidcolor);
	int i = 0;
	for (; i < vrects->size(); i++)
		if (vrects->at(i).getGlobalBounds().contains(pixelPos.x, pixelPos.y) && !vrects->at(i).getFilling())
		{
			if (myspr->getConnectedRectangle())
			{
				myspr->getConnectedRectangle()->setFilling(false);
				myspr->getConnectedRectangle()->setFillColor(sf::Color::Yellow);
			}
			myspr->setPosition(vrects->at(i).getPosition().x, vrects->at(i).getPosition().y);
			myspr->connectRectangle(&vrects->at(i));
			vrects->at(i).setFilling(true);
			if (settings.guesser == Guesser::PLAYER)
			{
				word.at(i) = myspr->getLetter();
				vrects->at(i).setFillColor(defsprcolor);
			}
			else
				!i ? result.first = myspr->getNumber() : result.second = myspr->getNumber();
			break;
		}
	return i == vrects->size() ? false : true;
}

void Game::resetCurrentSprite()
{
	if (myspr)
	{
		myspr->setStartPosition();
		if (myspr->getConnectedRectangle())
		{
			myspr->getConnectedRectangle()->setFilling(false);
			myspr->getConnectedRectangle()->setFillColor(sf::Color::Yellow);
		}
		myspr->connectRectangle(nullptr);
	}
}

void Game::moveSprite()
{
	int transparency = myspr->getLetterHiding() ? 45 : 255;
	myspr->setColor(sf::Color{0, 255, 0, sf::Uint8(transparency)});
	myspr->setPosition(pixelPos.x - dX, pixelPos.y - dY);
}

void Game::setSpriteHidingOptions()
{
	if (myspr->getLetterHiding())
	{
		myspr->setColor(defsprcolor);
		myspr->setLetterHiding(false);
		auto it = find(hidden_letters.begin(), hidden_letters.end(), myspr->getLetter());
		hidden_letters.erase(it);
	}
	else
	{
	if (settings.sound == SOUND::ON)
			hidsound.play();
		myspr->setColor(hidcolor);
		myspr->setLetterHiding(true);
		hidden_letters.insert(myspr->getLetter());
	}
}

void Game::resetResultSprites()
{
	for (int i = 0; i < result_sprites.first.size(); i++)
	{
		result_sprites.first[i].setStartPosition();
		result_sprites.second[i].setStartPosition();
	}
}

void Game::resetLetterSprites()
{
	for (int i = 0; i < letter_sprites.size(); i++)
	{
		letter_sprites[i].setStartPosition();
		if (letter_sprites[i].getConnectedRectangle())
			letter_sprites[i].getConnectedRectangle()->setFillColor(sf::Color::Yellow);
	}
}

void Game::resetRectangleLetters()
{
	for (int i = 0; i < letter_rectangles.size(); i++)
		if (!letter_rectangles[i].getFilling())
			word.at(i) = ' ';
}

void Game::resetResultRectNumbers()
{
	if (!result_rectangles[0].getFilling())
		result.first = -1;
	if (!result_rectangles[1].getFilling())
		result.second = -1;
}

void Game::resetAfterArrowClick()
{
	if (settings.sound == SOUND::ON)
		arrowsound.play();
	resetCurrentSprite();
	resetLetterSprites();
	resetResultSprites();
	for (int i = 0; i < letter_sprites.size(); i++)
		letter_sprites[i].connectRectangle(nullptr);
	for (int i = 0; i < letter_rectangles.size(); i++)
		letter_rectangles[i].setFilling(false);
	resetRectangleLetters();
}

void Game::addWordToHistory()
{
	if (find(history_vs.begin(), history_vs.end(), word) == history_vs.end())
	{
		history_vs.push_back(word);
		string s{ word + " - " + to_string(result.first) + ":" + to_string(result.second) };
		sf::Text t{ filesystem::path(s).wstring(), font, 22 };
		history.push_back(t);
		history.back().setPosition(470, history.size() * 24);
		history.back().setFillColor(sf::Color::Blue);
	}
}

void Game::resultHandling()
{
	result = dictionary.get_result(word);
	result_sprites.first[result.first].setPosition(result_rectangles[0].getPosition());
	result_sprites.second[result.second].setPosition(result_rectangles[1].getPosition());
	addWordToHistory();
	if (result.first == word_size && result.second == word_size)
		winHandling();
	else if (result.first == 0 && result.second == 0)
		for (int i = 0; i < letter_sprites.size(); i++)
			if (letter_sprites[i].getConnectedRectangle())
			{
				letter_sprites[i].setColor(hidcolor);
				letter_sprites[i].setLetterHiding(true);
				hidden_letters.insert(letter_sprites[i].getLetter());
			}
}

bool Game::isWinwordContainLetter(char l)
{
	for (char ch : winword)
		if (ch == l)
			return true;
	return false;
}

void Game::winHandling()
{
	win_text.setFillColor(sf::Color::Magenta);
	winword = word;
	gameover = true;
	up_text.setPosition(-sprite_size, -sprite_size);
	clue_text.setPosition(-sprite_size, -sprite_size);
	for (int i = 0; i < letter_sprites.size(); i++)
		if (!isWinwordContainLetter(letter_sprites[i].getLetter()))
			letter_sprites[i].setStartCoords(-sprite_size, -sprite_size);
		else
			letter_sprites[i].setStartCoords(letter_sprites[i].getPosition().x, letter_sprites[i].getPosition().y);
	for (int i = 0; i < result_sprites.first.size(); i++)
	{
		result_sprites.first[i].setStartCoords(-sprite_size, -sprite_size);
		result_sprites.second[i].setStartCoords(-sprite_size, -sprite_size);
	}
	result_sprites.first[result.first].setStartCoords(result_rectangles[0].getPosition().x, result_rectangles[0].getPosition().y);
	result_sprites.second[result.second].setStartCoords(result_rectangles[1].getPosition().x, result_rectangles[1].getPosition().y);

	if (settings.sound == SOUND::ON)
		winsound.play();
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
		clues[i] = sf::Text{ filesystem::path(clue_words[i]).wstring(), font, 18 };
		clues[i].move(640, 130 + (i * 20));
		clues[i].setFillColor(sf::Color::Black);
	}
	if (clue_words.size() == 1 && clue_words[0].size() > word.size())	//no words found
	{
		clues[0].setPosition(570, 130);
		clues[0].setFillColor(sf::Color::Red);
	}
}

void Game::hideClues()
{
	for (sf::Text& c : clues)
		c.setFillColor(!gameover ? bgcolor : wincolor);
}

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
			ws[i] = L'\n';
		}
		text.setString(ws);
	}
	text.move(20, 20);
	text.setFillColor(sf::Color::Black);
}

void Game::wordExplaining(sf::RenderWindow& window)
{
	sf::Font font;
	string fontname = "fonts\\Academy.ttf";
	if (!font.loadFromFile(fontname))
		throw runtime_error("GameWindow::wordExplaining(): cannot open a font file " + fontname);
	wstring ws = filesystem::path(word + "\n\n" + dictionary.word_explanation(word)).wstring();
	wstring backstr = settings.language == Language::UKR ? L"Для виходу на попередній екран натисніть Esc або закрийте вікно" : L"Для выхода на предыдущий экран нажмите Esc или закройте окно";
	sf::Text text{ ws, font, 21 }, back_text{ backstr, font, 20 };
	explTextFormatting(window, text, ws);
	back_text.move(50, window.getSize().y - 50);
	back_text.setFillColor(sf::Color::Red);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				return;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			break;

		window.clear(bgcolor);
		window.draw(text);
		window.draw(back_text);
		window.display();
	}
}

void Game::compGuessing()
{
	if (allRectanglesFull() && result.first >= result.second)
	{
		if (++firstsetcount == (settings.letters == Letters::THREE ? (int)FirstSetSizeFor::THREE : (int)FirstSetSizeFor::FOUR))
		{
			fncount = word_size + 1;
			isEmptyFirstSet = true;
		}
		if (result.first == word_size && result.second == word_size)
			winHandling();
		else
		{
			addWordToHistory();
			resetLetterSprites();
			resetResultSprites();
			result_rectangles[0].setFilling(false);
			result_rectangles[1].setFilling(false);

			if (result.first == 0 && result.second == 0)
				for (char c : word)
					hidden_letters.insert(c);
			else
			{
				comp_words[word] = result;
				fncount += result.first;
				if (fncount > word_size && !isEmptyFirstSet)
					noOptions = true;
				else if (fncount == word_size)
				{
					for (const string& str : strset)
						for (char c : str)
							hidden_letters.insert(c);
					strset.clear();
					isEmptyFirstSet = true;
				}
			}
			if (isEmptyFirstSet)
				updateSet();
			if (!noOptions)
				nextWordFromSet();
		}
	}
}

void Game::nextWordFromSet()
{
	if (strset.begin() != strset.end())
	{
		word = *strset.begin();
		strset.erase(word);
		for (int i = 0; i < word.size(); i++)
			for (int j = 0; j < letter_sprites.size(); j++)
				if (letter_sprites[j].getLetter() == word[i])
					letter_sprites[j].setPosition(letter_rectangles[i].getPosition().x, letter_rectangles[i].getPosition().y);
	}
	else
		noOptions = true;
}

void Game::updateSet()
{
	strset.clear();
	std::set<string> ss = dictionary.generate_another_set(history_vs, hidden_letters);
	for (const string& s : ss)
	{
		int cnt = 0;
		for (auto cw : comp_words)
			if (dictionary.get_result(s, cw.first) == cw.second)
				cnt++;
		if (cnt == comp_words.size())
			strset.insert(s);
	}
}

//------------------------------------------------------------------------------

Settings Game::play(sf::RenderWindow& window)
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
					{
						settings.restart = false;
						return settings;
					}
					else if (restart_text.getGlobalBounds().contains(pixelPos.x, pixelPos.y))
					{
						settings.restart = true;
						return settings;
					}
					else if (soundsprite.getGlobalBounds().contains(pixelPos.x, pixelPos.y))
					{
						settings.sound = settings.sound == SOUND::OFF ? SOUND::ON : SOUND::OFF;
						soundsprite.setTexture(settings.sound == SOUND::OFF ? soundofftexture : soundontexture);
					}
					else if (clue_text.getGlobalBounds().contains(pixelPos.x, pixelPos.y))
						updateClueWords();
					else if (up_text.getGlobalBounds().contains(pixelPos.x, pixelPos.y))
						resetAfterArrowClick();
					else if (!gameover && isAnySpriteContainMousePos())
						motion = true;

				if (event.key.code == sf::Mouse::Right)
					if (!gameover && isAnySpriteContainMousePos())
						hiding = true;
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.key.code == sf::Mouse::Left && word_expl_text.getGlobalBounds().contains(pixelPos.x, pixelPos.y))
					if (settings.guesser == Guesser::COMPUTER || allRectanglesFull() && !dictionary.is_wrong_word(word))
						wordExplaining(window);
				if (event.key.code == sf::Mouse::Left && motion)
					oneTimeLeftActions();
				if (event.key.code == sf::Mouse::Right && hiding)
					oneTimeRightActions();
			}
		}
		actions();
		window.clear(!gameover ? bgcolor : wincolor);
		drawAll(window);
		window.display();
	}
}

//------------------------------------------------------------------------------

void Game::oneTimeLeftActions()
{
	if (!isAnySpriteinRect())
	{
		resetCurrentSprite();
		if (settings.sound == SOUND::ON)
			tostartsound.play();
	}
	else if (settings.sound == SOUND::ON)
		inrectsound.play();
	if (settings.guesser == Guesser::PLAYER)
	{
		if (allRectanglesFull())
		{
			if (!dictionary.is_wrong_word(word))
			{
				resultHandling();
				hideClues();
				if (settings.sound == SOUND::ON && !gameover)
					allrectsound.play();
			}
			else if (settings.sound == SOUND::ON)
				wrongsound.play();
		}
		else
		{
			resetResultSprites();
			resetRectangleLetters();
		}
	}
	else compGuessing();
}

void Game::oneTimeRightActions()
{
	setSpriteHidingOptions();
	resetCurrentSprite();
	hiding = false;
	if (!allRectanglesFull())
	{
		resetResultSprites();
		resetRectangleLetters();
	}
}

void Game::hoverActions(GameText& text, sf::Color defcolor, sf::Color hovercolor, bool sound)
{
	if (text.getGlobalBounds().contains(pixelPos.x, pixelPos.y))
	{
		text.setFillColor(hovercolor);
		if (sound && !text.underMouse && settings.sound == SOUND::ON)
		{
			hoversound.play();
			text.underMouse = true;
		}
	}
	else 
	{
		text.setFillColor(defcolor);
		text.underMouse = false;
	}

}

void Game::actions()
{
	hoverActions(menu_text, sf::Color::Black, sf::Color::Blue, true);
	hoverActions(restart_text, sf::Color::Black, sf::Color::Blue, true);
	hoverActions(clue_text, sf::Color::Black, sf::Color::Blue, true);
	wrong_action_text.setFillColor(bgcolor);

	if (settings.guesser == Guesser::COMPUTER)
	{
		hoverActions(word_expl_text, sf::Color{ 0,128,255 }, sf::Color::Blue, true);
		if (allRectanglesFull())
			wrong_action_text.setFillColor(result.second > result.first ? sf::Color::Red : bgcolor);
		else
			resetResultRectNumbers();

		if (noOptions)
		{
			wrong_action_text.setString(settings.language == Language::UKR
				? "В базі немає такого слова, як Ви загадали, або Ви давали неправильні результати!"
				: "В базе нет такого слова, как Вы загадали, или Вы давали неправильные результаты!");
			wrong_action_text.setFillColor(sf::Color::Red);
			resetLetterSprites();
		}
	}
	else
	{
		if (allRectanglesFull())
		{
			hoverActions(up_text, sf::Color::Green, sf::Color::Blue, false);
			if (!dictionary.is_wrong_word(word))
				hoverActions(word_expl_text, sf::Color{ 0,128,255 }, sf::Color::Blue, true);
			else
				wrong_action_text.setFillColor(sf::Color::Red);
		}
		else
		{
			word_expl_text.setFillColor(bgcolor);
			up_text.setFillColor(bgcolor);
		}
	}
	if (motion) moveSprite();
}

//------------------------------------------------------------------------------------------------