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

// You can use this to test your Filesys class 

int main()
{
  	Sdisk disk1("disk1", 256, 128);
  	FileSys fsys("disk1", 256, 128);
  	fsys.newFile("file1");
	fsys.newFile("file2");

	string bfile1;
	string bfile2;

  	for (int i = 1; i <= 1024; i++)
    {
    	bfile1 += "1";
    }

  	vector<string> blocks = fsys.block(bfile1, 128);

	int blockNumber = 0;

  	for (int i = 0; i < blocks.size(); i++)
    {
    	blockNumber = fsys.addBlock("file1", blocks[i]);
    }

	fsys.delBlock("file1", fsys.getFirstBlock("file1"));


  	for (int i = 1; i <= 2048; i++)
    {
    	bfile2 += "2";
    }

	blocks = fsys.block(bfile2, 128);

  	for (int i = 0; i < blocks.size(); i++)
    {
    	blockNumber = fsys.addBlock("file2", blocks[i]);
    }
 
  	fsys.delBlock("file2", blockNumber);
}
