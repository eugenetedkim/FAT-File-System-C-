/*************************************************************
* Programmer: Eugene Kim
* Quarter: Fall 2019
* Course: CSE 461 Advanced Operating Systems
* Professor: Owen Murphy
* Assignment: Lab 6
* Assigned: November 5, 2019
* Due: November 12, 2019
* File Name: Shell.make
* Description: This make file allows testing and compilation
* to be more convenient
*************************************************************/
Shell: main.o Sdisk.o FileSys.o Shell.o
	g++ main.o Sdisk.o FileSys.o Shell.o -o Shell

main.o: main.cpp
	g++ -c main.cpp

Shell.o: Shell.cpp
	g++ -c Shell.cpp

FileSys.o: FileSys.cpp
	g++ -c FileSys.cpp

Sdisk.o: Sdisk.cpp
	g++ -c Sdisk.cpp

make clean:
	rm *.o Shell
