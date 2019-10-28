/*************************************************************
* Programmer: Eugene Kim
* Quarter: Fall 2019
* Course: CSE 461 Advanced Operating Systems
* Professor: Owen Murphy
* Assignment: Lab 3
* Assigned: October 8, 2019
* Due: October 22, 2019
* File Name: FileSys.cpp
* Description: This file defines the class member functions
*************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>

#include "Sdisk.h"
#include "FileSys.h"

using namespace std;

FileSys::FileSys(string diskName, int numberOfBlocks, int blockSize): Sdisk(diskName, numberOfBlocks, blockSize)
{
	rootSize = blockSize / 13;
	fatSize = 4 * numberOfBlocks / blockSize + 1;
	string buffer;
	getBlock(1, buffer);
	if (buffer[0] == '#') //No file system
	{
		cout << "No file system found" << endl;
		//Creating ROOT directory
		for (int i = 0; i < this->rootSize; i++)
		{
			fileName.push_back("xxxxxxxx");
			firstBlock.push_back(0);
		}

		fat.push_back(2 + fatSize);
		fat.push_back(-1);
		for (int i = 1; i <= fatSize; i++)
		{
			fat.push_back(-1);
		}
		for (int i = fatSize + 2; i < getNumberOfBlocks(); i++)
		{
			fat.push_back(i + 1);
		}
		fat.push_back(0);
		fsSynch();
	}
	else //File system exists
	{
		cout << "Reading existing file system..." << endl;
		//Read-in ROOT directory
		string readBuffer, file;
		int block;
		istringstream inStream;
		getBlock(1, readBuffer);
		inStream.str(readBuffer);

		for (int i = 0; i < rootSize; i++)
		{
			inStream >> file >> block;
			fileName.push_back(file);
			firstBlock.push_back(block);
		}
		//Read-in FAT directory
		istringstream inStream2;
		buffer.clear();
		for (int i = 0; i < fatSize; i++)
		{
			string b;
			getBlock(2 + i, b);
			buffer = buffer + b;
		}
		inStream2.str(buffer);
		int toInt;
		for (int i = 0; i < numberOfBlocks; i++)
		{
			inStream2 >> toInt;
			fat.push_back(toInt);
		}
	}
	fsSynch();
}

int FileSys::fsSynch()
{
	// Synching the ROOT directory to the software disk
	string buffer;
	ostringstream outStream;
	for (int i = 0; i < fileName.size(); ++i)
	{
		outStream << std::left << setfill(' ') << setw(8) << fileName[i] << " " << std::left << setfill(' ') << setw(3) << firstBlock[i] << " ";
	}
	buffer = outStream.str();
	vector<string> blocks = block(buffer, 13);
	buffer.clear();
	for (int i = 0; i < blocks.size(); ++i)
	{
		buffer = buffer + blocks[i];
	}
	blocks.clear();
	putBlock(1, buffer);
	buffer.clear();

	// Synching the FAT to the software disk
	ostringstream outStream2;
	for (int i = 0; i < fat.size(); i++)
	{
		outStream2 <<  std::left << setfill(' ') << setw(3) << fat[i] << " ";
	}
	buffer = outStream2.str();
	blocks = block(buffer, getBlockSize());
	buffer.clear();
	outStream2.str("");

	for (int i = 0; i < blocks.size(); ++i)
	{	
		putBlock(2 + i, blocks[i]);
	}

	return 1;
}

int FileSys::fsClose()
{
	fsSynch();
}

int FileSys::newFile(string file)
{
	for (int i = 0; i < rootSize; i++)
	{
		if (fileName[i] == file)
		{
			cout << "File already exists. " << endl;
			return 0;
		}
	}

	for (int i = 0; i < rootSize; i++)
	{
		if (fileName[i] == "xxxxxxxx")
		{
			fileName[i] = file;
			fsSynch();
			return 1;
		}
	}
	return 0;
}

int FileSys::rmFile(string file)
{
	for (int i = 0; i < rootSize; i++)
	{
		if (fileName[i] == file)
		{
			if (firstBlock[i] != 0)
			{
				cout << "File is not empty." << endl;
				return 0;
			}
			else
			{
				fileName[i] = "xxxxxxxx";
				fsSynch();
				return 1;
			}
		}
	}
	cout << "File does not exist." << endl;
	return 0;
}

int FileSys::getFirstBlock(string file)
{
	for (int i = 0; i < rootSize; i++)
	{
		if (fileName[i] == file)
		{
			return firstBlock[i];
		}
		else
		{
			cout << "No such file" << endl;
			return 0;
		}
	}
}

int FileSys::addBlock(string file, string block)
{
	//                 adding  adding
	//                 testing testing2
	// fat[0]   [11] -> [12] -> [13] -> [14]
	// fat[1]   [-1]    [-1]    [-1]    [-1]
	// fat[2]   [-1]    [-1]    [-1]    [-1]
	// fat[3]   [-1]    [-1]    [-1]    [-1]
	// fat[4]   [-1]    [-1]    [-1]    [-1]
	// fat[5]   [-1]    [-1]    [-1]    [-1]
	// fat[6]   [-1]    [-1]    [-1]    [-1]
	// fat[7]   [-1]    [-1]    [-1]    [-1]
	// fat[8]   [-1]    [-1]    [-1]    [-1]
	// fat[9]   [-1]    [-1]    [-1]    [-1]
	// fat[10]  [-1]    [-1]    [-1]    [-1]
	// fat[11]  [12] -> [0]     [12]    [12]
	// fat[12]  [13]    [13] -> [0 ]    [13]
	// fat[13]  [14]    [14]    [14] -> [0 ]
	// fat[14]  [15]    [15]    [15]    [15]

	int first = getFirstBlock(file);
	if (first == -1)
	{
		return 0;
	}

	int allocate = fat[0];
	if (allocate == 0)
	{
		return 0;
	}

	fat[0] = fat[fat[0]];
	fat[allocate] = 0;

	if (first == 0)
	{
		for (int i = 0; i < rootSize; i++)
		{
			if (fileName[i] == file)
			{
				firstBlock[i] = allocate;
				fsSynch();
				putBlock(allocate, block);
				return allocate;
			}
		}
	}
	else
	{
		int iBlock = first;
		while (fat[iBlock] != 0)
		{
			iBlock = fat[iBlock];
		}
		fat[iBlock] = allocate;
		fat[allocate] = 0;
		fsSynch();
		putBlock(allocate, block);
		return allocate;
	}
}


int FileSys::checkBlock(string file, int blockNumber)
{
	int iBlock = getFirstBlock(file);
	while(iBlock != 0)
	{
		if (iBlock == blockNumber)
		{
			return true;
		}
		iBlock = fat[iBlock];
	}
	return false;
}

int FileSys::delBlock(string file, int blockNumber)
{
	if (!checkBlock(file, blockNumber))
	{
		return 0;
	}

	int deAllocate = blockNumber;

	if (blockNumber == getFirstBlock(file))
	{
		for (int i = 0; i < fileName.size(); i++)
		{
			if (file == fileName[i])
			{
				firstBlock[i] = fat[blockNumber];
				break;
			}
		}
		fat[deAllocate] = fat[0];
		fat[0] = deAllocate;
		string hashTags;
		for (int i = 0; i < getBlockSize(); i++)
		{
			hashTags = hashTags + '#'; 
		}
		putBlock(deAllocate, hashTags);
		fsSynch();
	}
	else
	{
		int iBlock = getFirstBlock(file);
		while (fat[iBlock] != blockNumber)
		{
			iBlock = fat[iBlock];
		}
		// fat[iBlock] == blockNumber
		fat[iBlock] = fat[blockNumber];
		fat[deAllocate] = fat[0];
		fat[0] = deAllocate;
		string hashTags;
		for (int i = 0; i < getBlockSize(); i++)
		{
			hashTags = hashTags + '#'; 
		}
		putBlock(deAllocate, hashTags);
		fsSynch();
	}
}

int FileSys::readBlock(string file, int blockNumber, string& buffer)
{
	if (checkBlock(file, blockNumber))
	{
		getBlock(blockNumber, buffer);
		cout << "Block number " << blockNumber << " contains " << '"'<< buffer << '"' << endl;
		return 1;
	}
	else
	{
		cout << "No such block number in " << file << endl;
		return 0;
	}
}

int FileSys::writeBlock(string file, int blockNumber, string buffer)
{
	if (checkBlock(file, blockNumber))
	{
		string hashTags;
		for (int i = 0; i < getBlockSize(); i++)
		{
			hashTags = hashTags + '#'; 
		}
		putBlock(blockNumber, hashTags);
		putBlock(blockNumber, buffer);
		fsSynch();
		return 1;
	}
	else
	{
		return 0;
	}
}

int FileSys::nextBlock(string file, int blockNumber)
{
	if (checkBlock(file, blockNumber))
	{
		return fat[blockNumber];
	}
	else
	{
		return -1;
	}
}






















