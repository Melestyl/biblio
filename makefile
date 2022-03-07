c=gcc
#op=-Wall -Wextra 

all : es.o livre.o biblio.o tpBiblio.c 	
	$(c) $(op)  es.o livre.o biblio.o tpBiblio.c -o exe
	@echo "Pensez à 'make install' pour installer les librairies si vous ne les possédez pas"

es.o : es.c es.h
	$(c) $(op) -c es.c	
livre.o : livre.c livre.h
	$(c) $(op) -c livre.c	
biblio.o : biblio.c biblio.h
	$(c) $(op) -c biblio.c	


install:  #Linux
	sudo apt-get install libncurses5-dev libncursesw5-dev -y

clean:
	$(RM) *.o exe 

reset: clean
	$(RM) id.dat baseLivres 
