/*************************************************************
* Programmer: Eugene Kim
* Quarter: Fall 2019
* Course: CSE 461 Advanced Operating Systems
* Professor: Owen Murphy
* Assignment: Lab 7 / Lab 8 / Homework 4 / Project 4
* Assigned: November 19, 2019
* Due: December 3, 2019
* File Name: Table.cpp
* Description:
*************************************************************/

#include <iostream>
#include <string>
#include <fstream>

#include "FileSys.h"
#include "Table.h"

using namespace std;

/*
	This constructor creates the table object.
	It creates 2 new files (flatFile and indexFile) in the file system on the Sdisk using diskName.
*/
Table::Table(string diskName, int numberOfBlocks, int blockSize): FileSys(diskName, numberOfBlocks, blockSize)
//Table::Table(string diskName, int numberOfBlocks, int blockSize, string flatFile, string indexFile): FileSys(diskName, numberOfBlocks, blockSize)
{
	flatFile = "flat";
	indexFile = "index";
	newFile(flatFile);
	newFile(indexFile);
}

/*
	This module will read records from the input file,
	add the records to the flatfile
*/
int Table::buildTable(string inputFile)
{
	ifstream inFile;

	inFile.open(inputFile.c_str());

	string record;

	int count = 0; // Tells how many records are read

	ostringstream outStream;
	vector<string> key;
	vector<string> iBlock;

	//getline(inFile, record);
	//while (inFile.good())
	while (getline(inFile, record))
	{
		// Process record

		string pKey = record.substr(0, 5); // pKey: primary key
		vector<string> oBlock = block(record, getBlockSize());
		int blockId = addBlock(flatFile, oBlock[0]);

		outStream << pKey << " " << blockId << " ";
		count++;
		if (count == 4)
		{
			// Time to addBlock to indexFile
			vector<string> o2Block = block(outStream.str(), getBlockSize());
			addBlock(indexFile, o2Block[0]);
			count = 0;
			outStream.str("");
		}
		//getline(inFile, record);
	}
	return 1;
}

int Table::indexSearch(string value)
{
	int blockId = getFirstBlock(indexFile);
	// Check if blockId == -1. If so, then something is wrong.
	while (blockId != 0)
	{
		istringstream inStream;
		string buffer;
		readBlock(indexFile, blockId, buffer);
		string k; // key
		int b; // block
		inStream.str(buffer);
		for (int i = 1; i <= 4; i++)
		{
			inStream >> k >> b;
			if (k == value)
			{
				return b;
			}
		}
		blockId = nextBlock(indexFile, blockId);
	}
	return 0;
}

int Table::search(string value)
{
	int b = indexSearch(value);
	string buffer;
	readBlock(flatFile, b, buffer);
	cout << buffer << endl;
	return 1;
}