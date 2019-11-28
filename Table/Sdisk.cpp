/*************************************************************
* Programmer: Eugene Kim
* Quarter: Fall 2019
* Course: CSE 461 Advanced Operating Systems
* Professor: Owen Murphy
* Assignment: Lab 7 / Lab 8 / Homework 4 / Project 4
* Assigned: November 19, 2019
* Due: December 3, 2019
* File Name: Sdisk.cpp
* Description: This is the software disk implementation
* which calls the input/output stream's public member 
* functions
*************************************************************/
#include <cstdlib>
#include <iostream>
#include <string>

#include <fstream>

#include "Sdisk.h"

using namespace std;

Sdisk::Sdisk(string diskName, int numberOfBlocks, int blockSize)
{
	this->diskName = diskName;
	this->numberOfBlocks = numberOfBlocks;
	this-> blockSize = blockSize;

	fstream inFile;
	inFile.open(diskName.c_str(), ios::in | ios::out); // Allows input (read operations) from a stream and allows output (write operations) to a stream.
	if (inFile.good())
	{
		cout << diskName << " has been opened." << endl;
	}
	else
	{
		cout << diskName << " has been created."<< endl;
		inFile.open(diskName.c_str(), ios::out);
		for (int i = 0; i < (blockSize * numberOfBlocks); i++)
		{
			inFile.put('#');
		}
	}

	inFile.close();
}

int Sdisk::getBlock(int blockNumber, string& buffer) // retrieves block blockNumber from the disk and stores the data in the string buffer. It returns an error code of 1 if successful amd 0 otherwise.
{

	fstream iFile;
	iFile.open(diskName.c_str(), ios::in | ios::out);
	iFile.seekg(blockNumber * blockSize);
	if (iFile.good())
	{
		for (int i = 0; i < blockSize; i++)
		{
			buffer += iFile.get();
		}

		iFile.close();
		return 1;
	}
	else
	{
		return 0;
	}
}

int Sdisk::putBlock(int blockNumber, string buffer)
{
	fstream outFile;
	outFile.open(diskName.c_str(), ios::in | ios::out);
	outFile.seekg(blockNumber * blockSize);
	if (outFile.good())
	{
		for (int i = 0; i < buffer.length() && i < blockSize; i++)
		{
			outFile.put(buffer[i]);
		}
		outFile.close();
		buffer.clear();
		return 1;
	}
	else
	{
		cout << "Error" << endl;
		return 0;
	}
}

int Sdisk::getNumberOfBlocks()
{
	return numberOfBlocks;
}

int Sdisk::getBlockSize()
{
	return blockSize;
}

vector<string> Sdisk::block(string s, int b)
{
	// s IS buffer
	// b IS blockSize, A PRIVATE DATA MEMBER
	// RETURNS A VECTOR OF STRING(S)
	// EACH STRING HAS b BYTES

	vector<string> blocks;
	int numberOfBlocks = 0; // numberOfBlocks IS A PRIVATE DATA MEMBER


	// SETS numberOfBlocks ACCORDING TO THE BUFFER SIZE OF, s,
	// THAT HAS BEEN PASSED-IN AS A PARAMETER
	if(s.size() % b == 0)
	{
		numberOfBlocks = s.size() / b;
	}
	else
	{
		numberOfBlocks = s.size() / b + 1;
	}

	// AFTER SETTING numberOfBlocks, THIS LOOP SETS EACH BLOCK WITH
	// A STRING FROM THE BUFFER
	for (int i = 0; i < numberOfBlocks; i++)
	{
		// b * i EQUALS A POSITION THAT BEGINS AT ONE BLOCK.
		// b IS THE BLOCKSIZE OR NUMBER OF BYTES OR NUMBER OF CHARACTERS
		// AS i ITERATES UP, EACH BLOCK WILL HAVE A SUB-STRING.
		blocks.push_back(s.substr(b * i, b));
	}


	return blocks;
}