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

    return 0;
}
