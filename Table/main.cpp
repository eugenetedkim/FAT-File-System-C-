/*************************************************************
* Programmer: Eugene Kim
* Quarter: Fall 2019
* Course: CSE 461 Advanced Operating Systems
* Professor: Owen Murphy
* Assignment: Lab 7 / Lab 8 / Homework 4 / Project 4
* Assigned: November 19, 2019
* Due: December 3, 2019
* File Name: main.cpp
* Description: This program allows the user to open a flat
* file (data.txt in our case) and store it on a file system
* which is stored on a software disk. The user is able to 
* enter commands in a shell program to view, add, or delete
* the file.
*************************************************************/

#include <iostream>
#include <string>

#include "Sdisk.h"
#include "FileSys.h"
#include "Shell.h"
#include "Table.h"

using namespace std;

int main()
{
	Sdisk sDisk = Sdisk("sDisk.txt", 256, 128);
	FileSys fSys = FileSys("sDisk.txt", 256, 128);
	Table table = Table("sDisk.txt", 256, 128);
	table.buildTable("data.txt");
	Shell shell = Shell("sDisk.txt", 256, 128);
	string s;
	string command = "go";
	string op1, op2;

	while (command != "quit")
	{
		command.clear();
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
		if (command == "search")
		{
			table.search(op1);
		}
		if (command == "add")
		{
		    shell.add(op1);
		}
		if (command == "del")
		{
			shell.del(op1);
		}
		if (command == "type")
		{
			shell.type(op1);
		}
		if (command == "copy")
		{
			shell.copy(op1, op2);
		}
		if (command == "clobber")
		{
			shell.clobber(op1);
		}
	}
	return 0;
}