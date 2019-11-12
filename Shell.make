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
