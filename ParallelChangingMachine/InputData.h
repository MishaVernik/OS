#pragma once
#include "IFileReader.h"

class InputData : IFileReader
{
public:
	// Inherited via IFileReader
	virtual std::map<int,int> ReadFromFile(std::ifstream& file) override;
};

