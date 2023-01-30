#pragma once
#include "ITape.h"
#include <fstream>
#include <string>
#include <iostream>
#include <Windows.h>

class Tape : private ITape
{
	int size;

	std::fstream* file = NULL;
	
	int tapeCellSize = std::to_string(INT_MAX).length() + 1;
	int tapePos = 0;

	unsigned long moveSleep = 1;
	unsigned long rewindSleep = 1;
	unsigned long readSleep = 1;
	unsigned long writeSleep = 1;

	~Tape() {  };

public:

	Tape(std::fstream* inf, int N) { file = inf; size = N * tapeCellSize; };

	void readFile(std::vector<int>& tapeData) override;
	void writeFile(std::vector<int>* tapeData) override;
	void moveTape(bool forward) override;
	void rewindTape(bool forward, int positionsToMove) override;

	void setTimeouts(int move, 
		int rewind,
		int read,
		int write);

	void Delete() { delete this; }
};

void Tape::readFile(std::vector<int>& tapeData)
{
	int value;
	while (tapePos * tapeCellSize < size) {
		Sleep(readSleep);
		
		char* valueBlock;
		valueBlock = new char[tapeCellSize];
		
		file->read(valueBlock, tapeCellSize);
		
		value = atoi(valueBlock);
		tapeData.push_back(value);
		
		moveTape(true);

		delete[]valueBlock;
	}
}

void Tape::writeFile(std::vector<int>* tapeData) {

	std::vector<int> data = *tapeData;
	char* valueBlock;
	valueBlock = new char[tapeCellSize];

	while (tapePos * tapeCellSize < size) {
		
		Sleep(readSleep);

		std::string dataBlock = std::to_string(data[tapePos]);
		int blockWidth = dataBlock.length();
		int spacersNum = tapeCellSize - blockWidth;

		for (int j = 0; j < spacersNum; j++)
		{
			dataBlock.append(" ");
		}

		strcpy_s(valueBlock, tapeCellSize+1, dataBlock.c_str());
		file->write(valueBlock, tapeCellSize);

		moveTape(true);
	}
}

void Tape::moveTape(bool forward) {
	Sleep(moveSleep);
	if (forward)
	{
		if (!(file->is_open() && file->eof())) {
			tapePos++;
		}
	}
	else {
		if (file->tellg() > 0)
		{
			tapePos--;
		}
	}
	if ((0 < tapePos * tapeCellSize) && (tapePos * tapeCellSize < size))
	{
		file->seekg(tapePos * tapeCellSize, std::ios::beg);
	}
	
}

void Tape::rewindTape(bool forward, int positionsToMove) {
	Sleep(rewindSleep);
	if (forward)
	{
		if (!(file->is_open() && file->eof())) {
			tapePos += positionsToMove;
		}
	}
	else {
		if (file->tellg() > 0)
		{
			tapePos -= positionsToMove;
		}
	}
	if ((0 < tapePos * tapeCellSize) && (tapePos * tapeCellSize < size))
	{
		file->seekg(tapePos * tapeCellSize, std::ios::beg);
	}
}

void Tape::setTimeouts(int move, int rewind, int read, int write)
{
	moveSleep = move;
	rewindSleep = rewind;
	readSleep = read;
	writeSleep = write;

}

