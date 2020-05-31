#include "pch.h"
#include "CppUnitTest.h"
#include "../cw/Graph.h"
#include "../cw/Functions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace cwtests
{
	TEST_CLASS(cwtests)
	{
	public:
		
		TEST_METHOD(max_flow_1)
		{
			std::vector<std::string> rows{ "S A 5", "S C 11", "A C 17", "A B 17", "C D 7",
				"D B 13", "C E 13", "D E 1", "D F 2", "B G 10", "F G 13", 
				"E H 18", "F H 6", "G T 8", "F T 8", "H T 13" };
			Graph g(rows);
			Assert::IsTrue(g.max_flow() == 16);
		}
		TEST_METHOD(max_flow_2)
		{
			std::vector<std::string> rows{ "S A 13", "S E 12", "S D 12", "A B 11", "B C 1", "D E 2",
				"C E 3", "C F 15", "E F 4", "F G 1", "E G 12", "H G 11", "H T 2", "G T 17" };
			Graph g(rows);
			Assert::IsTrue(g.max_flow() == 13);
		}
		TEST_METHOD(read_data_success)
		{
			std::fstream file;
			file.open("test_data_0.txt", std::ios::in);
			std::vector<std::string> rows = read_data(file);
			file.close();
			std::cout << "hey";
			std::vector<std::string> true_rows{ "S T 5", "S A 11", "A S 17" };
			Assert::IsTrue(rows == true_rows);
			
		}
		TEST_METHOD(read_data_fail)
		{
			std::fstream file;
			file.open("test_data_1.txt", std::ios::in);
			std::vector<std::string> rows = read_data(file);
			file.close();
			Assert::IsTrue(rows.empty());
		}
		TEST_METHOD(is_number_success)
		{
			Assert::IsTrue(is_number("12847187"));
		}
		TEST_METHOD(is_number_fail)
		{
			Assert::IsFalse(is_number("random text"));
		}
	};
}
