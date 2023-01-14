#include "functions.h"

pair<int, int> get_result_for_4_letters(const string& computer_word, const string& player_word)
{
	if (!(computer_word.size() == player_word.size() == 4))
		throw runtime_error("get_result_for_4_letters(): wrong string size");

	if (player_word[0] == computer_word[0] && player_word[1] == computer_word[1] && player_word[2] == computer_word[2] && player_word[3] == computer_word[3])
	{
		return make_pair(4, 4);
	}
	else if (player_word[0] == computer_word[0] && player_word[1] == computer_word[1] && player_word[2] == computer_word[2] ||
		player_word[0] == computer_word[0] && player_word[1] == computer_word[1] && player_word[3] == computer_word[3] ||
		player_word[0] == computer_word[0] && player_word[2] == computer_word[2] && player_word[3] == computer_word[3] ||
		player_word[1] == computer_word[1] && player_word[2] == computer_word[2] && player_word[3] == computer_word[3])
	{
		return make_pair(3, 3);
	}
	else if (player_word[0] == computer_word[0] && player_word[1] == computer_word[1] && player_word[2] == computer_word[3] && player_word[3] == computer_word[2] ||
		player_word[1] == computer_word[1] && player_word[2] == computer_word[2] && player_word[0] == computer_word[3] && player_word[3] == computer_word[0] ||
		player_word[2] == computer_word[2] && player_word[3] == computer_word[3] && player_word[1] == computer_word[0] && player_word[0] == computer_word[1] ||
		player_word[1] == computer_word[1] && player_word[3] == computer_word[3] && player_word[0] == computer_word[2] && player_word[2] == computer_word[0] ||
		player_word[0] == computer_word[0] && player_word[2] == computer_word[2] && player_word[1] == computer_word[3] && player_word[3] == computer_word[1] ||
		player_word[0] == computer_word[0] && player_word[3] == computer_word[3] && player_word[1] == computer_word[2] && player_word[2] == computer_word[1])
	{
		return make_pair(4, 2);
	}
	else if (player_word[0] == computer_word[0] && player_word[1] == computer_word[1] && (player_word[2] == computer_word[3] || player_word[3] == computer_word[2]) ||
		player_word[0] == computer_word[0] && player_word[2] == computer_word[2] && (player_word[1] == computer_word[3] || player_word[3] == computer_word[1]) ||
		player_word[0] == computer_word[0] && player_word[3] == computer_word[3] && (player_word[1] == computer_word[2] || player_word[2] == computer_word[1]) ||
		player_word[1] == computer_word[1] && player_word[2] == computer_word[2] && (player_word[0] == computer_word[3] || player_word[3] == computer_word[0]) ||
		player_word[1] == computer_word[1] && player_word[3] == computer_word[3] && (player_word[0] == computer_word[2] || player_word[2] == computer_word[0]) ||
		player_word[2] == computer_word[2] && player_word[3] == computer_word[3] && (player_word[1] == computer_word[0] || player_word[0] == computer_word[1]))
	{
		return make_pair(3, 2);
	}
	else if (player_word[0] == computer_word[0] && player_word[1] == computer_word[1] ||
		player_word[0] == computer_word[0] && player_word[2] == computer_word[2] ||
		player_word[0] == computer_word[0] && player_word[3] == computer_word[3] ||
		player_word[1] == computer_word[1] && player_word[2] == computer_word[2] ||
		player_word[1] == computer_word[1] && player_word[3] == computer_word[3] ||
		player_word[2] == computer_word[2] && player_word[3] == computer_word[3])
	{
		return make_pair(2, 2);
	}
	else if (player_word[0] == computer_word[0] && (player_word[1] == computer_word[2] || player_word[1] == computer_word[3]) && (player_word[2] == computer_word[1] || player_word[2] == computer_word[3]) && (player_word[3] == computer_word[2] || player_word[3] == computer_word[1]) ||
		player_word[1] == computer_word[1] && (player_word[0] == computer_word[2] || player_word[0] == computer_word[3]) && (player_word[2] == computer_word[0] || player_word[2] == computer_word[3]) && (player_word[3] == computer_word[0] || player_word[3] == computer_word[2]) ||
		player_word[2] == computer_word[2] && (player_word[0] == computer_word[1] || player_word[0] == computer_word[3]) && (player_word[1] == computer_word[0] || player_word[1] == computer_word[3]) && (player_word[3] == computer_word[0] || player_word[3] == computer_word[1]) ||
		player_word[3] == computer_word[3] && (player_word[0] == computer_word[1] || player_word[0] == computer_word[2]) && (player_word[1] == computer_word[0] || player_word[1] == computer_word[2]) && (player_word[2] == computer_word[0] || player_word[2] == computer_word[1]))
	{
		return make_pair(4, 1);
	}
	else if (player_word[0] == computer_word[0] && ((player_word[1] == computer_word[2] || player_word[1] == computer_word[3]) && (player_word[2] == computer_word[1] || player_word[2] == computer_word[3]) || (player_word[1] == computer_word[2] || player_word[1] == computer_word[3]) && (player_word[3] == computer_word[2] || player_word[3] == computer_word[1]) || (player_word[2] == computer_word[1] || player_word[2] == computer_word[3]) && (player_word[3] == computer_word[2] || player_word[3] == computer_word[1])) ||
		player_word[1] == computer_word[1] && ((player_word[0] == computer_word[2] || player_word[0] == computer_word[3]) && (player_word[2] == computer_word[0] || player_word[2] == computer_word[3]) || (player_word[0] == computer_word[2] || player_word[0] == computer_word[3]) && (player_word[3] == computer_word[2] || player_word[3] == computer_word[0]) || (player_word[2] == computer_word[0] || player_word[2] == computer_word[3]) && (player_word[3] == computer_word[2] || player_word[3] == computer_word[0])) ||
		player_word[2] == computer_word[2] && ((player_word[0] == computer_word[1] || player_word[0] == computer_word[3]) && (player_word[1] == computer_word[0] || player_word[1] == computer_word[3]) || (player_word[0] == computer_word[1] || player_word[0] == computer_word[3]) && (player_word[3] == computer_word[1] || player_word[3] == computer_word[0]) || (player_word[1] == computer_word[0] || player_word[1] == computer_word[3]) && (player_word[3] == computer_word[1] || player_word[3] == computer_word[0])) ||
		player_word[3] == computer_word[3] && ((player_word[0] == computer_word[1] || player_word[0] == computer_word[2]) && (player_word[1] == computer_word[0] || player_word[1] == computer_word[2]) || (player_word[0] == computer_word[1] || player_word[0] == computer_word[2]) && (player_word[2] == computer_word[1] || player_word[2] == computer_word[0]) || (player_word[1] == computer_word[0] || player_word[1] == computer_word[2]) && (player_word[2] == computer_word[1] || player_word[2] == computer_word[0])))
	{
		return make_pair(3, 1);
	}
	else if (player_word[0] == computer_word[0] && ((player_word[1] == computer_word[2] || player_word[1] == computer_word[3]) || (player_word[2] == computer_word[1] || player_word[2] == computer_word[3]) || (player_word[3] == computer_word[2] || player_word[3] == computer_word[1])) ||
		player_word[1] == computer_word[1] && ((player_word[0] == computer_word[2] || player_word[0] == computer_word[3]) || (player_word[2] == computer_word[0] || player_word[2] == computer_word[3]) || (player_word[3] == computer_word[2] || player_word[3] == computer_word[0])) ||
		player_word[2] == computer_word[2] && ((player_word[0] == computer_word[1] || player_word[0] == computer_word[3]) || (player_word[1] == computer_word[0] || player_word[1] == computer_word[3]) || (player_word[3] == computer_word[0] || player_word[3] == computer_word[1])) ||
		player_word[3] == computer_word[3] && ((player_word[0] == computer_word[1] || player_word[0] == computer_word[2]) || (player_word[1] == computer_word[0] || player_word[1] == computer_word[2]) || (player_word[2] == computer_word[0] || player_word[2] == computer_word[1])))
	{
		return make_pair(2, 1);
	}
	else if (player_word[0] == computer_word[0] || player_word[1] == computer_word[1] || player_word[2] == computer_word[2] || player_word[3] == computer_word[3])
	{
		return make_pair(1, 1);
	}
	else if ((player_word[0] == computer_word[1] || player_word[0] == computer_word[2] || player_word[0] == computer_word[3]) &&
		(player_word[1] == computer_word[0] || player_word[1] == computer_word[2] || player_word[1] == computer_word[3]) &&
		(player_word[2] == computer_word[0] || player_word[2] == computer_word[1] || player_word[2] == computer_word[3]) &&
		(player_word[3] == computer_word[0] || player_word[3] == computer_word[1] || player_word[3] == computer_word[2]))
	{
		return make_pair(4, 0);
	}
	else if (((player_word[0] == computer_word[1] || player_word[0] == computer_word[2] || player_word[0] == computer_word[3]) &&
		(player_word[1] == computer_word[0] || player_word[1] == computer_word[2] || player_word[1] == computer_word[3]) &&
		(player_word[2] == computer_word[0] || player_word[2] == computer_word[1] || player_word[2] == computer_word[3])) ||
		((player_word[1] == computer_word[0] || player_word[1] == computer_word[2] || player_word[1] == computer_word[3]) &&
			(player_word[2] == computer_word[0] || player_word[2] == computer_word[1] || player_word[2] == computer_word[3]) &&
			(player_word[3] == computer_word[0] || player_word[3] == computer_word[1] || player_word[3] == computer_word[2])) ||
		((player_word[0] == computer_word[1] || player_word[0] == computer_word[2] || player_word[0] == computer_word[3]) &&
			(player_word[2] == computer_word[0] || player_word[2] == computer_word[1] || player_word[2] == computer_word[3]) &&
			(player_word[3] == computer_word[0] || player_word[3] == computer_word[1] || player_word[3] == computer_word[2])) ||
		((player_word[0] == computer_word[1] || player_word[0] == computer_word[2] || player_word[0] == computer_word[3]) &&
			(player_word[1] == computer_word[0] || player_word[1] == computer_word[2] || player_word[1] == computer_word[3]) &&
			(player_word[3] == computer_word[0] || player_word[3] == computer_word[1] || player_word[3] == computer_word[2])))
	{
		return make_pair(3, 0);
	}
	else if (((player_word[0] == computer_word[1] || player_word[0] == computer_word[2] || player_word[0] == computer_word[3]) &&
		(player_word[1] == computer_word[0] || player_word[1] == computer_word[2] || player_word[1] == computer_word[3])) ||
		((player_word[0] == computer_word[1] || player_word[0] == computer_word[2] || player_word[0] == computer_word[3]) &&
			(player_word[2] == computer_word[0] || player_word[2] == computer_word[1] || player_word[2] == computer_word[3])) ||
		((player_word[0] == computer_word[1] || player_word[0] == computer_word[2] || player_word[0] == computer_word[3]) &&
			(player_word[3] == computer_word[0] || player_word[3] == computer_word[1] || player_word[3] == computer_word[2])) ||
		((player_word[1] == computer_word[0] || player_word[1] == computer_word[2] || player_word[1] == computer_word[3]) &&
			(player_word[2] == computer_word[0] || player_word[2] == computer_word[1] || player_word[2] == computer_word[3])) ||
		((player_word[1] == computer_word[0] || player_word[1] == computer_word[2] || player_word[1] == computer_word[3]) &&
			(player_word[3] == computer_word[0] || player_word[3] == computer_word[1] || player_word[3] == computer_word[2])) ||
		((player_word[2] == computer_word[0] || player_word[2] == computer_word[1] || player_word[2] == computer_word[3]) &&
			(player_word[3] == computer_word[0] || player_word[3] == computer_word[1] || player_word[3] == computer_word[2])))
	{
		return make_pair(2, 0);
	}
	else if ((player_word[0] == computer_word[1] || player_word[0] == computer_word[2] || player_word[0] == computer_word[3]) ||
		(player_word[1] == computer_word[0] || player_word[1] == computer_word[2] || player_word[1] == computer_word[3]) ||
		(player_word[2] == computer_word[0] || player_word[2] == computer_word[1] || player_word[2] == computer_word[3]) ||
		(player_word[3] == computer_word[0] || player_word[3] == computer_word[1] || player_word[3] == computer_word[2]))
	{
		return make_pair(1, 0);
	}
	return make_pair(0, 0);
}

pair<int, int> get_result_for_3_letters(const string& computer_word, const string& player_word)
{
	if (player_word[0] == computer_word[0] && player_word[1] == computer_word[1] && player_word[2] == computer_word[2])
	{
		return make_pair(3, 3);
	}
	else if (player_word[0] == computer_word[0] && player_word[1] == computer_word[1] ||
		player_word[0] == computer_word[0] && player_word[2] == computer_word[2] ||
		player_word[1] == computer_word[1] && player_word[2] == computer_word[2])
	{
		return make_pair(2, 2);
	}
	else if (player_word[0] == computer_word[0] && player_word[1] == computer_word[2] && player_word[2] == computer_word[1] ||
		player_word[1] == computer_word[1] && player_word[0] == computer_word[2] && player_word[2] == computer_word[0] ||
		player_word[2] == computer_word[2] && player_word[1] == computer_word[0] && player_word[0] == computer_word[1])
	{
		return make_pair(3, 1);
	}
	else if ((player_word[0] == computer_word[0] && player_word[2] == computer_word[1] || player_word[0] == computer_word[0] && player_word[1] == computer_word[2]) ||
		(player_word[1] == computer_word[1] && player_word[2] == computer_word[0] || player_word[1] == computer_word[1] && player_word[0] == computer_word[2]) ||
		(player_word[2] == computer_word[2] && player_word[0] == computer_word[1] || player_word[2] == computer_word[2] && player_word[1] == computer_word[0]))
	{
		return make_pair(2, 1);
	}
	else if (player_word[0] == computer_word[0] || player_word[1] == computer_word[1] || player_word[2] == computer_word[2])
	{
		return make_pair(1, 1);
	}
	else if ((player_word[0] == computer_word[1] || player_word[0] == computer_word[2]) &&
		(player_word[1] == computer_word[0] || player_word[1] == computer_word[2]) &&
		(player_word[2] == computer_word[0] || player_word[2] == computer_word[1]))
	{
		return make_pair(3, 0);
	}
	else if ((player_word[0] == computer_word[1] || player_word[0] == computer_word[2]) && (player_word[1] == computer_word[0] || player_word[1] == computer_word[2]) ||
		(player_word[0] == computer_word[1] || player_word[0] == computer_word[2]) && (player_word[2] == computer_word[0] || player_word[2] == computer_word[1]) ||
		(player_word[2] == computer_word[1] || player_word[2] == computer_word[0]) && (player_word[1] == computer_word[0] || player_word[1] == computer_word[2]))
	{
		return make_pair(2, 0);
	}
	else if ((player_word[0] == computer_word[1] || player_word[0] == computer_word[2]) ||
		(player_word[1] == computer_word[0] || player_word[1] == computer_word[2]) ||
		(player_word[2] == computer_word[0] || player_word[2] == computer_word[1]))
	{
		return make_pair(1, 0);
	}
	return make_pair(0, 0);
}