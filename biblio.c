#include "biblio.h"

void init(T_Bibliotheque *ptrB)
{
    ptrB->nbLivres = 0;
    return;
}

int ajouterLivre(T_Bibliotheque *ptrB)
{
    if (ptrB->nbLivres == CAPACITE_BIBLIO)
        return 1;
    T_livre livre;
    saisirLivre(&livre);
    ptrB->etagere[ptrB->nbLivres] = livre;
    ptrB->nbLivres++;
    return 0;
}

int afficherBibliotheque(const T_Bibliotheque *ptrB)
{
    printf("\nAffichage de la bibliothèque :\n");
    if (ptrB->nbLivres == 0)
        return 1;
    for(int i=0; i < ptrB->nbLivres; i++) {
        printf("\n\n-----------------\n");
        printf("Titre : %s\n", ptrB->etagere[i].titre);
        printf("Auteur : %s\n", ptrB->etagere[i].auteur);
    }
    return 0;
}
