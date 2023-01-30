#pragma once

#include <vector>
class ITape
{
public:

	virtual void readFile(std::vector<int>& tapeData) = 0;
	virtual void writeFile(std::vector<int>* tapeData) = 0;
	virtual void moveTape(bool forward) = 0;
	virtual void rewindTape(bool forward, int steps) = 0;

	virtual ~ITape() {};
};

