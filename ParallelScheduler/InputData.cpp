#include "InputData.h"
#include <iostream>
#include <sstream>

std::vector<Process> InputData::ReadFromFile(std::ifstream& file)
{
	std::vector<Process> inputData;
	std::string line;
	if (file.is_open())
	{
		while (getline(file, line))
		{
			Process process;
			std::istringstream ss(line);	
			int count = 0;
			do {				
				std::string word;
				ss >> word;
				switch (count)
				{
					case 0:
						// Gets the process number
						process.number = stoi(word);
						break;
					case 1:
						// Gets time when current process starts
						process.startTime = stoi(word);
						break;
					case 2:
						// Gets time how long should this process works.
						process.workingTime = stoi(word);
						break;
					default:
						break;
				}
				count++;
#ifdef DEBUG
				std::cout << word << std::endl
#endif
			} while (ss);

			inputData.push_back(process);
		}
		file.close();
	}

	return inputData;
}
