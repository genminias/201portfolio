portfolio.o: portfolio.c classes.h
	gcc -c portfolio.c

classes.o: classes.c classes.h
	gcc -c classes.c

portfolio: portfolio.o classes.o
	gcc portfolio.o classes.o -o portfolio