#----- Modify CC and CFLAGS as appropriate in your environment
CC = gcc
CFLAGS = -O3 -fopenmp

LIB = -lm -lc

UNITFILES = 

#------------ EXECUTABLE FILES ---------------

histo_locks : histo_locks.o $(UNITFILES)
	$(CC) $(CFLAGS) -o histo_locks histo_locks.o $(UNITFILES) $(LIB)

clean:
	rm -f histo_locks *_locks.o

histo_locks.o : histo_locks.c
	$(CC) $(CFLAGS) -c histo_locks.c $(INCLUDE) 


