/*************************************************************
* Programmer: Eugene Kim
* Quarter: Fall 2019
* Course: CSE 461 Advanced Operating Systems
* Professor: Owen Murphy
* Assignment: Lab 6
* Assigned: November 5, 2019
* Due: November 12, 2019
* File Name: Shell.cpp
* Description: This is the shell implementation which calls
* the filesystem's public member functions
*************************************************************/
#include <iostream>
#include <string>
#include <vector>

#include "FileSys.h"
#include "Shell.h"

using namespace std;

Shell::Shell(string fileName, int blockSize, int numberOfBlocks)
  : FileSys(fileName, blockSize, numberOfBlocks)
{
}

// dir lists files in the class Shell
int Shell::dir() // lists all files
{
  cout << "calling dir";
  vector<string> fList = ls();

  for (int i = 0; i < fList.size(); i++)
  {
    cout << fList[i] << endl;
  }
  return 0;
}

int Shell::add(string file) // add a new file using input from the keyboard
{
  string input;

  int code1 = newFile(file);

  if (code1 == -1)
  {
    cout << "No space in the ROOT directory" << endl;
    return 0;
  }
  else
  {
    cout << "Enter a string to add: ";
    getline(cin, input);
    input = input + " ";
    addBlock(file, input);
  }
  return 1;
}

int Shell::del(string file) // deletes the files
{

  while (getFirstBlock(file) != 0)
  {
    delBlock(file, getFirstBlock(file));
  }


  rmFile(file);
  return 1;
}

int Shell::type(string file) // lists the content of file
{
  string buffer;
  int first = getFirstBlock(file);
  while (first != 0)
  {
    readBlock(file, first, buffer);
    cout << buffer << endl;
    buffer.clear();
    first = nextBlock(file, first);
  }

  return 1;
}

int Shell::copy(string file1, string file2)
{
  int code = getFirstBlock(file1);

  if (code  == -1)
  {
    cout << file2 << " does not exist" << endl;
    return 0;
  }

  int code2 = getFirstBlock(file2);

  if (code2 != 0)
  {
    cout << file2 << " exists and its contents will not be overwritten" << endl;
    return 0;
  }

  int code3 = newFile(file2);

  if (code3 == -1) 
  {
    cout << "No space in the ROOT directory" << endl;
    return 0;
  }

  int iBlock = code; // iBlock is the first block in the file

  while (iBlock != 0)
  {
    string b;
    getBlock(iBlock, b);
    int code4 = addBlock(file2, b);
    if (code4 == -1)
    {
      cout << "No space left" << endl;
      delBlock(file2, iBlock);
      return 0;
    }
    iBlock = nextBlock(file1, iBlock);
  }

  return 1;
}
