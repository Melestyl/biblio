#ifndef BIBLIO_H // compilation conditionnelle
#define BIBLIO_H

#include "livre.h"
#include <time.h>
#include <ctype.h>

#define CAPACITE_BIBLIO 20 // nb maximum de livres ds la bibliotheque

typedef T_livre T_tabloDeLivres[CAPACITE_BIBLIO];

FILE* fp;
int NBLivres;

typedef struct
{
	T_tabloDeLivres etagere;
	int nbLivres; // nb de livres actuellement ds la bibliotheque

} T_Bibliotheque;

// prototypes
void init(T_Bibliotheque *ptrB);
int ajouterLivre();
int afficherBibliotheque();
int rechercherLivreTitre(const char titre[]);
int afficherLivresAuteur();
int supprimerLivre();
int rechercherLivreCode(unsigned id);
int emprunterLivre();
int rendreLivre();
void trierTitre(T_Bibliotheque *ptrB);
void trierAuteur(T_Bibliotheque *ptrB);
void trierAnnee(T_Bibliotheque *ptrB);

int afficherLivresDisponibles(const T_Bibliotheque *ptrB);
int afficherLivresEnRetard(const T_Bibliotheque *ptrB);


//FICHIERS
void sauvegarde(T_Bibliotheque *ptrB);
int chargement(T_Bibliotheque *ptrB);
void lectureFichierTXT();
unsigned int getID();
void setID(unsigned int id);

//DATE
void lireDateSysteme(T_Emp *E);

//FICHIERS ++++
void allerDebut();
void avancer();
void reculer();
void allerA(unsigned pos);
int getNBLivres();
void setNBLivres();
void ecrireLivre(T_livre livre);
T_livre lireLivre();

#endif