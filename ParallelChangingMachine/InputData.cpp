#include "InputData.h"
#include <iostream>
#include <sstream>
#include <utility>
using namespace std;

std::map<int, int> InputData::ReadFromFile(std::ifstream& file)
{
	std::map<int, int> inputData;
	std::string line;
	if (file.is_open())
	{
		while (getline(file, line))
		{		 
			std::istringstream ss(line);
			int count = 0;			
			pair<int, int> coinStruct;
			do {
				std::string word;
				ss >> word;
				switch (count)
				{
				case 0:
					// Gets the coin number.
					coinStruct.first = stoi(word);
					break;
				case 1:
					// Gets coin's quantity.
					coinStruct.second = stoi(word);
					break;
				default:
					break;
				}
				count++;
#ifdef DEBUG
				std::cout << word << std::endl
#endif
			} while (ss);
			
			inputData[coinStruct.first] = coinStruct.second;
		}
		file.close();
	}

	return inputData;
}
