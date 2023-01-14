#include "Dictionary.h"

int main()
try
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	srand(unsigned(std::time(0)));

	Dictionary d1{ Language::RUS, Letters::THREE, Level::SCHOOL };

	cout << d1.hword_explanation() << endl;
	auto res = d1.get_result("мат");
	cout << res.first << ":" << res.second << endl;

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
}
catch (const std::exception& e)
{
	std::cerr << "\nError: " << e.what() << endl;
}
