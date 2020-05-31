#include "Graph.h"
#include "Functions.h"

using namespace std;


int main()
{
	string file_name;
	cout << "Enter csv file name: ";
	cin >> file_name;
	fstream file;
	file.open(file_name, ios::in);
	if (!file.fail())
	{
		vector<string> rows = read_data(file);
		if (!rows.empty())
		{
			Graph g(rows);
			cout << "Maximum flow: " << g.max_flow();
		}
		else cout << "Wrong input!\n";
		file.close();
	}
	else cout << "File doesn't exist!\n";
	
}