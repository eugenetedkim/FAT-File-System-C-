#include <iostream>
#include <string>

#include "Sdisk.h"
#include "FileSys.h"
#include "Shell.h"
#include "Table.h"

using namespace std;

int main()
{
	/*
		This main program inputs commands to the shell.
		It inputs commands as : command op1 op2
		You should modify it to work for your implementation.
	*/

	Sdisk sDisk = Sdisk("sDisk.txt", 256, 128); // Creates the software disk  of chars using hash tags
	FileSys fSys = FileSys("sDisk.txt", 256, 128); // Creates a file system on the software disk
	//Table table = Table("sDisk.txt", 256, 128, "flat", "index"); // 
	Table table = Table("sDisk.txt", 256, 128);
	table.buildTable("data.txt");
	Shell shell = Shell("sDisk.txt", 256, 128); // Creates a shell to access the file system

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
			// use the ls function
			shell.dir();
		}
		if (command == "search")
		{
			// The variable op1 is the date
			table.search(op1);
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