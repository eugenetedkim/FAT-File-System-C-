/*************************************************************
* Programmer: Eugene Kim
* Quarter: Fall 2019
* Course: CSE 461 Advanced Operating Systems
* Professor: Owen Murphy
* Assignment: Lab 7 / Lab 8 / Homework 4 / Project 4
* Assigned: November 19, 2019
* Due: December 3, 2019
* File Name: Sdisk.h
* Description: This is the software disk interface which
* connects the software disk to the underlying .txt file
*************************************************************/
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

#ifndef SDISK_H
#define SDISK_H

class Sdisk
{
private :
	string diskName;        // file name of software-disk
	int numberOfBlocks;     // number of blocks on disk
	int blockSize;          // block size in bytes

public :
	Sdisk(string diskName, int numberOfBlocks, int blockSize);
	int getBlock(int blockNumber, string& buffer); // retrieves block blockNumber from the disk and stores the data in the string buffer. It returns an error code of 1 if successful amd 0 otherwise.
	int putBlock(int blockNumber, string buffer); // writes the string buffer to block blockNumber. It returns an error code of 1 if successful and 0 otherwise.
	int getNumberOfBlocks(); // accessor function
	int getBlockSize(); // accessor function
	vector<string> block(string s, int b);
};

#endif
