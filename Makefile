pasteboard : main.o clipboard.o
	g++ -o pasteboard Main.o clipboard.o

main.o : src/Main.cpp
	g++ -c src/Main.cpp

clipboard.o : src/Clipboard.cpp src/Clipboard.h
	g++ -c src/Clipboard.cpp

.PHONY: clean

clean :
	del /Q /S pasteboard.exe
	del /Q /S *.o