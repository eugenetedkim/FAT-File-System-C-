/*
CSE 461 Lab 7
In this laboratory you are going to start working on the last project.

The data is here.

Here is the interface for the class Table:

All functions return 1 if successful and 0 otherwise.
Work on the constructor.
Work on the buildTable function.
*/

#include <iostream>
#include <string>

#include "FileSys.h"

using namespace std;

#ifndef TABLE_H
#define TABLE_H

class Table : public FileSys
{

	string flatFile;
	string indexFile;
	int numberOfRecords;
	FileSys fileSystem;
	int indexSearch(string value);

public:

	Table(string diskName, string flatFile, string indexFile);
	int buildTable(string inputFile);
	int search(string value);

};

#endif TABLE_H