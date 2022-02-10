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
        printf("-----------------\n");
        printf("Titre : %s\n", ptrB->etagere[i].titre);
        printf("Auteur : %s\n", ptrB->etagere[i].auteur);
    }
    return 0;
}

int rechercherLivreTitre(const T_Bibliotheque *ptrB, const char titre[]){
    int compteur = 0;
    for(int i=0; i < ptrB->nbLivres; i++) {
        if(!strcmp(ptrB->etagere[i].titre,titre)){
            afficherLivre(&ptrB->etagere[i]);
            compteur++;
        }
    }
    if (compteur == 0)
        return 1;
    printf("\nIl existe %d livre(s) de ce titre dans la bibliothèque.", compteur);
    return 0;
}