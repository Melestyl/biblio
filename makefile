c=gcc
op=-Wall -Wextra

all : es.o livre.o biblio.o tpBiblio.c 	
	$(c) $(op)  es.o livre.o biblio.o tpBiblio.c -o exe

es.o : es.c es.h
	$(c) $(op) -c es.c	
livre.o : livre.c livre.h
	$(c) $(op) -c livre.c	
biblio.o : biblio.c biblio.h
	$(c) $(op) -c biblio.c	

