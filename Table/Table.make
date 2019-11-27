Table: main.o Sdisk.o FileSys.o Shell.o Table.o
	g++ main.o Sdisk.o FileSys.o Shell.o Table.o -o Table

main.o: main.cpp
	g++ -c main.cpp

Table.o: Table.cpp
	g++ -c Table.cpp

Shell.o: Shell.cpp
	g++ -c Shell.cpp

FileSys.o: FileSys.cpp
	g++ -c FileSys.cpp

Sdisk.o: Sdisk.cpp
	g++ -c Sdisk.cpp

make clean:
	rm *.o Table sDisk.txt
