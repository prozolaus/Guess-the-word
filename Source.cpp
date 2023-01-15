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
	sf::Vector2i startpos;
	MyRectangleShape* rec = nullptr;
	void setStartPosition(int x, int y) { startpos.x = x; startpos.y = y; setStartPosition(); }
	void setStartPosition() { setPosition(startpos.x, startpos.y); }
};

class Game
{
public:
	const int letters_count = 33;
	Letters letters;
	std::vector<sf::Texture> textures, result_textures;
	std::vector<MyLetterSprite> sprites, result_sprites, result_sprites2;
	std::vector<MyRectangleShape> rectangles;
	bool isMove = false;
	float dX = 0;
	float dY = 0;
	MyLetterSprite* myspr = nullptr;
	Dictionary dictionary;
	string word;
	sf::RectangleShape resultrect1, resultrect2;
	sf::Text result_text;
	sf::Font font;

	Game(Letters);
	void letter_init();
	bool rectanglesFull();
};

Game::Game(Letters lttrs)
	: letters{ lttrs },
	textures{ letters_count },
	result_textures{ (int)lttrs + 1 },
	dictionary{Language::UKR, Letters::THREE, Level::SCHOOL},
	word{ "" }
{
	for (int i = 0; i < letters_count; i++)
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
	rectangles.assign((int)letters, MyRectangleShape{ sf::Vector2f(64.f, 64.f) });
	for (int i = 0; i < rectangles.size(); i++)
	{
		rectangles[i].setFillColor(sf::Color(175, 180, 240));
		rectangles[i].move(100 + i * 64, 450);
		rectangles[i].setOutlineColor(sf::Color::Black);
		rectangles[i].setOutlineThickness(1.f);
	}
	for (int i = 0; i <= (int)letters; i++)
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
	word.resize(int(letters));
	letter_init();
	font.loadFromFile("Bebas_Neue_Cyrillic.ttf");
	result_text.setFont(font);
	result_text.setFillColor(sf::Color::Blue);
	result_text.move(20, 560);
	result_text.setString("Result:");
}

void Game::letter_init()
{
	int count = -32;
	for (int i = 0; i < letters_count; i++)
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
			sprites[i].letter = char(-4);	//¿
		else if (i == 31)
			sprites[i].letter = char(-2);	//¿
		else if (i == 32)
			sprites[i].letter = char(-1);	//¿
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

void check_event(sf::RenderWindow& window, sf::Event& event, Game& game, sf::Vector2i& pixelPos)
{
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		if (event.type == sf::Event::MouseButtonPressed)
			if (event.key.code == sf::Mouse::Left)
				for (int i = 0; i < game.sprites.size(); i++)
					if (game.sprites[i].getGlobalBounds().contains(pixelPos.x, pixelPos.y))
					{
						game.isMove = true;
						game.dX = pixelPos.x - game.sprites[i].getPosition().x;
						game.dY = pixelPos.y - game.sprites[i].getPosition().y;
						game.myspr = &game.sprites[i];
						break;
					}

		if (event.type == sf::Event::MouseButtonReleased)
			if (event.key.code == sf::Mouse::Left && game.isMove)
			{
				game.isMove = false;
				game.myspr->setColor(sf::Color::White);

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
		if (game.isMove)
		{
			game.myspr->setColor(sf::Color::Green);
			game.myspr->setPosition(pixelPos.x - game.dX, pixelPos.y - game.dY);
		}

	}
}

//------------------------------------------------------------------------------------------------

void start(sf::RenderWindow& window, Game& game)
{
	while (window.isOpen())
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

		sf::Event event;
		check_event(window, event, game, pixelPos);

		window.clear(sf::Color::White);

		for (int i = 0; i < game.rectangles.size(); i++)
			window.draw(game.rectangles[i]);

		for (int i = game.sprites.size() - 1; i >= 0; i--)
			window.draw(game.sprites[i]);

		if (game.rectanglesFull())
		{
			pair<int, int> result = game.dictionary.get_result(game.word);
			game.result_sprites[result.first].setPosition(game.resultrect1.getPosition());
			game.result_sprites2[result.second].setPosition(game.resultrect2.getPosition());
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

		window.display();
	}
}

//------------------------------------------------------------------------------------------------

int main()
try
{
	/*
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	srand(unsigned(std::time(0)));

	Dictionary d1{ Language::RUS, Letters::THREE, Level::SCHOOL };

	cout << d1.hword_explanation() << endl;
	auto res = d1.get_result("ìàò");
	cout << res.first << ":" << res.second << endl;
	*/
	/*
	Dictionary d2{ Language::RUS, Letters::THREE, Level::NORMAL };
	Dictionary d3{ Language::RUS, Letters::THREE, Level::ERUDITE };
	Dictionary d4{ Language::RUS, Letters::FOUR, Level::SCHOOL };
	Dictionary d5{ Language::RUS, Letters::FOUR, Level::NORMAL };
	Dictionary d6{ Language::RUS, Letters::FOUR, Level::ERUDITE };
	Dictionary d7{ Language::UKR, Letters::THREE, Level::SCHOOL };
	Dictionary d8{ Language::UKR, Letters::THREE, Level::NORMAL };
	Dictionary d9{ Language::UKR, Letters::THREE, Level::ERUDITE };
	Dictionary d10{ Language::UKR, Letters::FOUR, Level::SCHOOL };
	Dictionary d11{ Language::UKR, Letters::FOUR, Level::NORMAL };
	Dictionary d12{ Language::UKR, Letters::FOUR, Level::ERUDITE };
	*/
	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	sf::RenderWindow window(sf::VideoMode(700, 700), "Guess the word");
	Game game(Letters::THREE);
	start(window, game);

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
