#pragma once
#include <fstream>
#include <map>
#include <string>

class IFileReader
{
public:
	virtual ~IFileReader() {}
	virtual std::map<int, int> ReadFromFile(std::ifstream& file) = 0;
};

