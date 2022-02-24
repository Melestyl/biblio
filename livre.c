#include "livre.h"

void saisirLivre(T_livre *ptrL)
{
	lireChaine("TITRE :", (ptrL->titre), MAX_TITRE);
	lireChaine("AUTEUR :", (ptrL->auteur), MAX);
	lireChaine("EDITEUR :", ptrL->editeur, K_MaxEdit);
	ptrL->emprunteur.emprunt = 0;
	printf("ANNEE : "); scanf("%d", &ptrL->annee);
	
}

void afficherLivre(const T_livre *ptrL)
{
	afficherChaine("TITRE :", (ptrL->titre));
	printf(" - ");
	afficherChaine("AUTEUR :", (ptrL->auteur));
	printf(" - ");
	afficherChaine("EDITEUR :", ptrL->editeur);
	printf(" - ");
	printf("ANNEE : %d", ptrL->annee);
	printf(" - ");
	printf("CODE : %u", (ptrL->code));
	if (ptrL->emprunteur.emprunt) {
		printf(" - ");
		afficherChaine("EMPRUNTEUR :", ptrL->emprunteur.nom);
		printf(" - ");
		printf("DATE D'EMPRUNT : %s %d %s %d", ptrL->emprunteur.lejour, ptrL->emprunteur.ledate, ptrL->emprunteur.lemois, ptrL->emprunteur.lannee);
	}
	printf("\n");
}

