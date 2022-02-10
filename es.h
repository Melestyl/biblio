#ifndef ES_H // compilation conditionnelle
#define ES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "biblio.h"

char *lire(char *lachaine, int nbMAXcaracAsaisir);
char *lireChaine(const char *, char *, int);
void afficherChaine(const char *, const char *);
//FICHIER
void sauvegarde(T_Bibliotheque *ptrB);
void chargement(T_Bibliotheque *ptrB);
void lectureFichierTXT();
unsigned int getID();
void setID(unsigned int id);

#endif
