#include <SFML/Graphics.hpp>
#include "Dictionary.h"

class MyRectangleShape : public sf::RectangleShape
{
	using RectangleShape::RectangleShape;

public:
	bool isfull = false;
};

class MyLetterSprite : public sf::Sprite
{
	using Sprite::Sprite;

public:
	char letter;
	bool isHidden = false;
	sf::Vector2i startpos;
	MyRectangleShape* rec = nullptr;
	void setStartPosition(int x, int y) { startpos.x = x; startpos.y = y; setStartPosition(); }
	void setStartPosition() { setPosition(startpos.x, startpos.y); }
};

class Game
{
	const int alphabet_size = 33;
	Letters letters;
	void setGame();

public:
	
	std::vector<sf::Texture> textures, result_textures;
	std::vector<MyLetterSprite> sprites, result_sprites, result_sprites2;
	std::vector<MyRectangleShape> rectangles;
	bool isMove = false, isHide = false;
	float dX = 0;
	float dY = 0;
	MyLetterSprite* myspr = nullptr;
	Dictionary dictionary;
	sf::RectangleShape resultrect1, resultrect2;
	sf::Text result_text, win_text, menu_text;
	sf::Font font;
	string word;

	Game(MenuSettings);
	void letterInit();
	bool rectanglesFull();
	int wordSize() { return int(letters); }
	pair<int, int> getResult() { return dictionary.get_result(word); }
};

Game::Game(MenuSettings ms)
	: dictionary{ms.language, ms.letters, ms.level}, 
	letters{ms.letters},
	textures{alphabet_size},
	result_textures{wordSize() + 1}
{
	setGame();
}

void Game::setGame()
{
	for (int i = 0; i < alphabet_size; i++)
	{
		std::string s = "letters\\" + std::to_string(i) + ".png";
		textures[i].loadFromFile(s);
	}
	for (int i = 0, count = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
		{
			if (count == 33)
				break;
			sprites.push_back(MyLetterSprite{ textures[count++] });
			sprites.back().setStartPosition(j * 64, i * 64);
		}
	rectangles.assign(wordSize(), MyRectangleShape{ sf::Vector2f(64.f, 64.f) });
	for (int i = 0; i < rectangles.size(); i++)
	{
		rectangles[i].setFillColor(sf::Color(175, 180, 240));
		rectangles[i].move(100 + i * 64, 450);
		rectangles[i].setOutlineColor(sf::Color::Black);
		rectangles[i].setOutlineThickness(1.f);
	}
	for (int i = 0; i <= wordSize(); i++)
	{
		std::string s = "numbers\\" + std::to_string(i) + ".png";
		result_textures[i].loadFromFile(s);
		result_sprites.push_back(MyLetterSprite{ result_textures[i] });
		result_sprites.back().setStartPosition(-200, i * 64);
		result_sprites2.push_back(MyLetterSprite{ result_textures[i] });
		result_sprites2.back().setStartPosition(-100, i * 64);
	}
	resultrect1 = sf::RectangleShape{ sf::Vector2f(64.f, 64.f) };
	resultrect2 = sf::RectangleShape{ sf::Vector2f(64.f, 64.f) };
	resultrect1.move(116.f, 550.f);
	resultrect1.setFillColor(sf::Color::Yellow);
	resultrect1.setOutlineColor(sf::Color::Black);
	resultrect1.setOutlineThickness(1.f);
	resultrect2.move(212.f, 550.f);
	resultrect2.setFillColor(sf::Color::Yellow);
	resultrect2.setOutlineColor(sf::Color::Black);
	resultrect2.setOutlineThickness(1.f);
	word.resize(wordSize());
	letterInit();
	font.loadFromFile("Bebas_Neue_Cyrillic.ttf");
	result_text.setFont(font);
	result_text.setFillColor(sf::Color::Blue);
	result_text.move(20, 560);
	result_text.setString("Result:");
	win_text.setFont(font);
	win_text.setFillColor(sf::Color::Magenta);
	win_text.move(300, 550);
	win_text.setString("Congratulations!");
	win_text.setCharacterSize(40);
	menu_text.setFont(font);
	menu_text.setFillColor(sf::Color::Black);
	menu_text.move(620, 20);
	menu_text.setString("Menu");
}

void Game::letterInit()
{
	int count = -32;
	for (int i = 0; i < alphabet_size; i++)
	{
		if (i == 4)
			sprites[i].letter = char(-76);	//´
		else if (i == 7)
			sprites[i].letter = char(-70);	//º
		else if (i == 11)
			sprites[i].letter = char(-77);	//³
		else if (i == 12)
			sprites[i].letter = char(-65);	//¿
		else if (i == 30)
			sprites[i].letter = char(-4);	//ü
		else if (i == 31)
			sprites[i].letter = char(-2);	//þ
		else if (i == 32)
			sprites[i].letter = char(-1);	//ÿ
		else
			sprites[i].letter = char(count++);
	}
}

bool Game::rectanglesFull() 
{
	for (int i = 0; i < rectangles.size(); i++)
		if (rectangles[i].isfull == false)
			return false;
	return true;
}

//------------------------------------------------------------------------------------------------

bool check_event(sf::RenderWindow& window, sf::Event& event, Game& game, sf::Vector2i& pixelPos)
{
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

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
			(game.myspr->getColor() == sf::Color::White) ? game.myspr->setColor(sf::Color{255,255,255,20}) : game.myspr->setColor(sf::Color::White);
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

void start(sf::RenderWindow& window, Game& game)
{
	bool isGame = true;
	while (window.isOpen() && isGame)
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

		sf::Event event;
		isGame = check_event(window, event, game, pixelPos);

		window.clear(sf::Color::White);

		for (int i = 0; i < game.rectangles.size(); i++)
			window.draw(game.rectangles[i]);

		for (int i = game.sprites.size() - 1; i >= 0; i--)
			window.draw(game.sprites[i]);

		if (game.rectanglesFull())
		{
			pair<int, int> result = game.getResult();
			game.result_sprites[result.first].setPosition(game.resultrect1.getPosition());
			game.result_sprites2[result.second].setPosition(game.resultrect2.getPosition());
			if (result.first == game.wordSize() && result.second == game.wordSize())
				window.draw(game.win_text);
		}
		else
			for (int i = 0; i < game.result_sprites.size(); i++)
			{
				game.result_sprites[i].setStartPosition();
				game.result_sprites2[i].setStartPosition();
			}

		window.draw(game.resultrect1);
		window.draw(game.resultrect2);

		for (int i = 0; i < game.result_sprites.size(); i++)
		{
			window.draw(game.result_sprites[i]);
			window.draw(game.result_sprites2[i]);
		}

		window.draw(game.result_text);
		window.draw(game.menu_text);
		
		window.display();
	}
}

//------------------------------------------------------------------------------------------------

MenuSettings menu(sf::RenderWindow& window)
{
	MenuSettings mset{};
	bool isMenu = true, 
		UA_lang = false, RU_lang = false, 
		three_ls = false, four_ls = false,
		school_lvl = false, normal_lvl = false, erudite_lvl = false;
	const int x = 100, y = 100;
	sf::Font font;
	font.loadFromFile("Bebas_Neue_Cyrillic.ttf");

	sf::Text start{"Start", font}, lang{"Language:", font}, ua{"UA", font}, ru{"RU", font};
	start.setFillColor(sf::Color::Black);
	lang.setFillColor(sf::Color::Black);
	ua.setFillColor(sf::Color::Black);
	ru.setFillColor(sf::Color::Black);
	start.setPosition(300, 600);
	lang.setPosition(x, y);
	ua.setPosition(x + lang.getGlobalBounds().width + x/3, y);
	ru.setPosition(ua.getPosition().x + x/2, y);

	sf::Text lttrs{ "Letters:", font }, three{ "3", font }, four{ "4", font };
	lttrs.setFillColor(sf::Color::Black);
	three.setFillColor(sf::Color::Black);
	four.setFillColor(sf::Color::Black);
	lttrs.setPosition(x, 1.5*y);
	three.setPosition(ua.getPosition().x, 1.5 * y);
	four.setPosition(ru.getPosition().x, 1.5*y);

	sf::Text lvl{ "Level:", font }, school{ "School", font }, normal{ "Normal", font }, erudite{ "Erudite", font };
	lvl.setFillColor(sf::Color::Black);
	school.setFillColor(sf::Color::Black);
	normal.setFillColor(sf::Color::Black);
	erudite.setFillColor(sf::Color::Black);
	lvl.setPosition(x, 2 * y);
	school.setPosition(three.getPosition().x, 2 * y);
	normal.setPosition(school.getPosition().x + school.getGlobalBounds().width + x / 3, 2 * y);
	erudite.setPosition(normal.getPosition().x + normal.getGlobalBounds().width + x / 3, 2 * y);

	while (isMenu && window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		sf::Vector2i pos = sf::Mouse::getPosition(window);
		window.clear(sf::Color::White);
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
			if (start.getGlobalBounds().contains(pos.x, pos.y) && (UA_lang || RU_lang) && (three_ls || four_ls)	&& (school_lvl || normal_lvl || erudite_lvl))
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
		window.draw(start);
		window.draw(lang);
		window.draw(ua);
		window.draw(ru);
		window.draw(lttrs);
		window.draw(three);
		window.draw(four);
		window.draw(lvl);
		window.draw(school);
		window.draw(normal);
		window.draw(erudite);
		window.display();
	}
	return mset;
}

//------------------------------------------------------------------------------------------------

int main()
try
{
	sf::RenderWindow window(sf::VideoMode(700, 700), "Guess the word");
	window.setFramerateLimit(60);

	while(window.isOpen())
	{
		Game game{ menu(window) };
		start(window, game);
	}

	return 0;
}
catch (const std::exception& e)
{
	std::cerr << "\nError: " << e.what() << endl;
}
catch (...)
{
	std::cerr << "\nUnknown error!\n\n";
}
