#ifndef BIBLIO_H // compilation conditionnelle
#define BIBLIO_H

#include "livre.h"

#define CAPACITE_BIBLIO 20 // nb maximum de livres ds la bibliotheque

typedef T_livre T_tabloDeLivres[CAPACITE_BIBLIO];

typedef struct
{
	T_tabloDeLivres etagere;
	int nbLivres; // nb de livres actuellement ds la bibliotheque

} T_Bibliotheque;

// prototypes
void init(T_Bibliotheque *ptrB);
int ajouterLivre(T_Bibliotheque *ptrB);
int afficherBibliotheque(const T_Bibliotheque *ptrB);
int rechercherLivreTitre(const T_Bibliotheque *ptrB, const char titre[]);
int afficherLivresAuteur(const T_Bibliotheque *ptrB);
int supprimerLivre(T_Bibliotheque *ptrB);
int rechercherLivreCode(T_Bibliotheque *ptrB, unsigned id);
int emprunterLivre(T_Bibliotheque *ptrB);
int rendreLivre(T_Bibliotheque *ptrB);
void trierTitre(T_Bibliotheque *ptrB);
void trierAuteur(T_Bibliotheque *ptrB);
void trierAnnees(T_Bibliotheque *ptrB);

int afficherLivresDisponibles(const T_Bibliotheque *ptrB);

//FICHIERS
void sauvegarde(T_Bibliotheque *ptrB);
int chargement(T_Bibliotheque *ptrB);
void lectureFichierTXT();
unsigned int getID();
void setID(unsigned int id);

#endif