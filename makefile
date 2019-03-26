portfolio.o: portfolio.c classes.h
	gcc -c portfolio.c -Wall -std=c11

classes.o: classes.c classes.h
	gcc -c classes.c -Wall -std=c11

portfolio: portfolio.o classes.o
	gcc portfolio.o classes.o -o portfolio