#include "biblio.h"

void init(T_Bibliotheque *ptrB)
{
    ptrB->nbLivres = 0;
    return;
}

int ajouterLivre(T_Bibliotheque *ptrB)
{

    return 0;
}

int afficherBibliotheque(const T_Bibliotheque *ptrB)
{
    int i; //Boucleur
    printf("\nAffichage de la bibliothèque :\n");
    for(i = 0; i < ptrB->nbLivres; i++)
        printf("\n\n-----------------\n");
        printf("Titre : %s\n", ptrB->etagere[i].titre);
        printf("Auteur : %s\n", ptrB->etagere[i].auteur);
    return 0;
}
