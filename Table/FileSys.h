/*************************************************************
* Programmer: Eugene Kim
* Quarter: Fall 2019
* Course: CSE 461 Advanced Operating Systems
* Professor: Owen Murphy
* Assignment: Lab 7 / Lab 8 / Homework 4 / Project 4
* Assigned: November 19, 2019
* Due: December 3, 2019
* File Name: FileSys.h
* Description: This is the file system interface that connects
* the file system with the underlying software disk
*************************************************************/

#ifndef FILESYS_H
#define FILESYS_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <stdlib.h>

#include "Sdisk.h"

class FileSys: public Sdisk
{
private:
	int rootSize;
	int fatSize;
	vector<string> fileName;
	vector<int> firstBlock;
	vector<int> fat;
public:
	FileSys(string diskName, int numberOfBlocks, int blockSize);
	int fsSynch();
	int fsClose();
	int newFile(string file);
	int rmFile(string file);
	int getFirstBlock(string file);
	int addBlock(string file, string block);
	int delBlock(string file, int blockNumber);
	int checkBlock(string file, int blockNumber);
	int readBlock(string file, int blockNumber, string& buffer);
	int writeBlock(string file, int blockNumber, string buffer);
	int nextBlock(string file, int blockNumber);
	vector<string> block(string s, int b);
	vector<string> ls();
};

#endif
