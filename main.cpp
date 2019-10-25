/*************************************************************
* Programmer: Eugene Kim
* Quarter: Fall 2019
* Course: CSE 461 Advanced Operating Systems
* Professor: Owen Murphy
* Assignment: Lab 3
* Assigned: October 8, 2019
* Due: October 22, 2019
* File Name: main.cpp
* Description: This program creates a file system
*************************************************************/
#include <iostream>

#include "Sdisk.h"
#include "FileSys.h"

using namespace std;

int main()
{
	Sdisk disk1("disk1", 32, 16);
	FileSys fileSystem("disk1", 32, 16);
	fileSystem.newFile("dreams");

	fileSystem.addBlock("dreams", "testing");
	fileSystem.addBlock("dreams", "testing2");
	fileSystem.addBlock("dreams", "testing3");
}