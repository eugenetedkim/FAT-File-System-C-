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
	for (int i = 0; i < fat.size(); ++i)
	{
		cout << fat[i] << endl;
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
		outStream << std::left << setfill(' ') << setw(8) << fileName[i] << " " << std::left << setfill('0') << setw(3) << firstBlock[i] << " ";
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


