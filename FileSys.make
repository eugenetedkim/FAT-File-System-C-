FileSys: main.o Sdisk.o FileSys.o
	g++ main.o Sdisk.o FileSys.o -o FileSys

main.o: main.cpp
	g++ -c main.cpp

FileSys.o:: FileSys.cpp
	g++ -c FileSys.cpp

Sdisk.o: Sdisk.cpp
	g++ -c Sdisk.cpp

make clean:
	rm *.o FileSys
