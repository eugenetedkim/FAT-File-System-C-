/*************************************************************
* Programmer: Eugene Kim
* Quarter: Fall 2019
* Course: CSE 461 Advanced Operating Systems
* Professor: Owen Murphy
* Assignment: Lab 6
* Assigned: November 5, 2019
* Due: November 12, 2019
* File Name: main.cpp
* Description: This main program creates an interactive shell,
* a file system, and a software disk which data is stored.

* Users can interact with the shell 
* using the following commands:

* $ dir - List all directories in the file system
* $ add [directory name] - Add a new directory
* $ del [directory name] - Delete a directory
* $ type [directory name] - Display the contents of a directory
* $ copy [directory name 1] [directory name 2] - Copy content of 
* directory 1 to a new directory name 2
*************************************************************/
#include <iostream>

#include "Sdisk.h"
#include "FileSys.h"
#include "Shell.h"

using namespace std;

// You can use this to test your Filesys class 

int main()
{
  Sdisk disk1("disk1", 256, 128);
  FileSys fSys("disk1", 256, 128);

  //
  // This main program inputs commands to the shell.
  // It inputs commands as : command op1 op2
  // You should modify it to work for your implementation.
  //

  string s;
  string command = "go";
  string op1, op2;
  Shell shell("disk1", 256, 128);

  while (command != "quit")
  {
    command.clear();
    s.clear(); // Why isn't this in here? All other strings get cleared but string s doesn't. Couldn't there be garbage?
    op1.clear();
    op2.clear();
    cout << "$ ";
    getline(cin, s);
    int firstBlank = s.find(' ');
    if (firstBlank < s.length())
    {
      s[firstBlank] = '#';
    }
    int secondBlank = s.find(' ');
    command = s.substr(0, firstBlank);

    if (firstBlank < s.length())
    {
      op1 = s.substr(firstBlank + 1, secondBlank - firstBlank - 1);
    }

    if (secondBlank < s.length())
    {
      op2 = s.substr(secondBlank + 1);
    }

    if (command == "dir")
    {
      shell.dir();
    }

    if (command == "add")
    {
      // The variable op1 is the new file
      shell.add(op1);
    }

    if (command == "del")
    {
      // The variable op1 is the file
      shell.del(op1);
    }
 
    if (command == "type")
    {
      // The variable op1 is the file
      shell.type(op1);
    }

    if (command == "copy")
    {
      // The variable op1 is the source file and the variable op2 is the destination file.
      shell.copy(op1, op2);
    }

  }

  return 0;
}
