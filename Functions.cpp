#include "Functions.h"

bool is_number(std::string str)
{
	for (char c : str)
		if (!isdigit(c)) return false;
	return true;
}

std::vector<std::string> read_data(std::fstream& file)
{
	std::vector<std::string> rows;
	std::string row;
	while (getline(file, row))
	{
		if (row.length() >= 5 && isalpha(row[0]) && row[1] == ' ' &&
			isalpha(row[2]) && row[3] == ' ' && is_number(row.substr(4, row.length() - 1)))
		{
			rows.push_back(row);
		}
		else
		{
			rows.clear();
			break;
		}
	}
	return rows;
}