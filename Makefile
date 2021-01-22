pasteboard : main.o clipboard.o
	g++ -o pasteboard main.o clipboard.o

main.o : src/main.cpp
	g++ -c src/main.cpp

clipboard.o : src/clipboard.cpp src/clipboard.h
	g++ -c src/clipboard.cpp

.PHONY: clean

clean :
	del /Q /S pasteboard.exe
	del /Q /S *.o