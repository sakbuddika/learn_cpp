CC = g++
CFLAGS = -std=c++17
CDEBUG = -g -fsanitize=address

log_file_analyzer: main.o Menu.o LogReader.o Report.o
	$(CC) $(CFLAGS) $(CDEBUG) -o log_file_analyzer main.o Menu.o LogReader.o Report.o
main.o: main.cpp Menu.h LogReader.h Report.h
	$(CC) $(CFLAGS) -c main.cpp
Menu.o: Menu.cpp Menu.h LogReader.h Report.h
	$(CC) $(CFLAGS) -c Menu.cpp
LogReader.o: LogReader.cpp LogReader.h Report.h
	$(CC) $(CFLAGS) -c LogReader.cpp
Report.o: Report.cpp Report.h Menu.h LogReader.h
	$(CC) $(CFLAGS) -c Report.cpp
clean:
	rm -f log_file_analyzer *.o
