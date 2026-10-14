CC = g++
CFLAGS = -std=c++17
CDEBUG = -g -fsanitize=address

log_file_analyzer: main.o
	$(CC) $(CFLAGS) $(CDEBUG) -o log_file_analyzer main.o
main.o: main.cpp
	$(CC) $(CFLAGS) $(CDEBUG) -c main.cpp
clean:
	rm -f main.o log_file_analyzer
