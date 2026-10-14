CC = g++
CFLAGS = -std=c++17
CDEBUG = -g -fsanitize=address

merklerex: main.o MerkelMain.o OrderBook.o OrderBookEntry.o CSVReader.o Wallet.o
	$(CC) $(CFLAGS) $(CDEBUG) -o merklerex main.o MerkelMain.o OrderBook.o OrderBookEntry.o CSVReader.o Wallet.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

MerkelMain.o: MerkelMain.cpp
	$(CC) $(CFLAGS) -c MerkelMain.cpp

OrderBook.o: OrderBook.cpp
	$(CC) $(CFLAGS) -c OrderBook.cpp

OrderBookEntry.o: OrderBookEntry.cpp
	$(CC) $(CFLAGS) -c OrderBookEntry.cpp

CSVReader.o: CSVReader.cpp
	$(CC) $(CFLAGS) -c CSVReader.cpp

Wallet.o: Wallet.cpp
	$(CC) $(CFLAGS) -c Wallet.cpp
clean:
	rm -f merklerex *.o
