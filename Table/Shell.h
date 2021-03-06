/*************************************************************
* Programmer: Eugene Kim
* Quarter: Fall 2019
* Course: CSE 461 Advanced Operating Systems
* Professor: Owen Murphy
* Assignment: Lab 7 / Lab 8 / Homework 4 / Project 4
* Assigned: November 19, 2019
* Due: December 3, 2019
* File Name: Shell.h
* Description: This is the shell interface that connects the
* interactive shell with the underlying file system
*************************************************************/

#include <iostream>
#include <string>

#include "FileSys.h"

using namespace std;

#ifndef SHELL_H
#define SHELL_H

class Shell: public FileSys
{
public:
    Shell(string fileName, int blockSize, int numberOfBlocks);
    int dir();
    int add(string file);
    int del(string file);
    int type(string file);
    int copy(string file1, string file2);
    int clobber(string file);
private:
	void clobber_helper(string file, int block);
};

#endif
