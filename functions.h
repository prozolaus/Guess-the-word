#pragma once
#include <iostream>
#include <filesystem>

using namespace std;

pair<int, int> get_result_for_4_letters(const string& computer_word, const string& player_word);

pair<int, int> get_result_for_3_letters(const string& computer_word, const string& player_word);