#pragma once
#include "IFileReader.h"

class InputData : IFileReader
{
public:
	// Inherited via IFileReader
	virtual std::vector<Process> ReadFromFile(std::ifstream& file) override;
};

