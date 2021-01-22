pasteboard : main.o clipboard.o systemtrayicon.o
	g++ -o pasteboard Main.o clipboard.o systemtrayicon.o

main.o : src/Main.cpp
	g++ -c src/Main.cpp

clipboard.o : src/Clipboard.cpp src/Clipboard.h
	g++ -c src/Clipboard.cpp

systemtrayicon.o : src/SystemTrayIcon.cpp src/SystemTrayIcon.h
	g++ -c src/SystemTrayIcon.cpp

.PHONY: clean

clean :
	del /Q /S pasteboard.exe
	del /Q /S *.o