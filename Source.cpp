#include "GameWindow.h"

int main()
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
try
{
	GameWindow window(sf::VideoMode(700, 700), "Guess the word", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	window.runGame();
	
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