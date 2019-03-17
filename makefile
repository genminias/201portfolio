portfolio.o: portfolio.c classes.h
	gcc -c portfolio.c -Wall

classes.o: classes.c classes.h
	gcc -c classes.c -Wall

portfolio: portfolio.o classes.o
	gcc portfolio.o classes.o -o portfolio