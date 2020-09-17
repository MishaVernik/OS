#pragma once
#include <fstream>
#include "Process.h"
#include <vector>
#include <string>

class IFileReader
{
public:
	virtual ~IFileReader() {}
	virtual std::vector<Process> ReadFromFile(std::ifstream& file) = 0;
};

