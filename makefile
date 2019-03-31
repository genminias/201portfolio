portfolio.o: portfolio.c functions.h
	gcc -c portfolio.c -Wall -std=c11

functions.o: functions.c functions.h
	gcc -c functions.c -Wall -std=c11

portfolio: portfolio.o functions.o
	gcc portfolio.o functions.o -o portfolio