#include "biblio.h"

void init(T_Bibliotheque *ptrB)
{
	if(chargement(ptrB))
    	ptrB->nbLivres = 0;
}

int ajouterLivre(T_Bibliotheque *ptrB)
{
    unsigned int id = getID();

    if (ptrB->nbLivres == CAPACITE_BIBLIO)
        return 1;
    T_livre livre;
    saisirLivre(&livre);
    livre.code = id;
    ptrB->etagere[ptrB->nbLivres] = livre;
    ptrB->nbLivres++;
	printf("\nLe livre possède le code %u.\n", id);
    setID(id+1);
    return 0;
}

int afficherBibliotheque(const T_Bibliotheque *ptrB)
{
    printf("\nAffichage de la bibliothèque :\n");
    if (ptrB->nbLivres == 0)
        return 1;
    for(int i=0; i < ptrB->nbLivres; i++) {
        afficherLivre(&ptrB->etagere[i]);
        /* printf("-----------------\n");
        printf("Titre : %s\n", ptrB->etagere[i].titre);
        printf("Auteur : %s\n", ptrB->etagere[i].auteur); */
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
}

int afficherLivresAuteur(const T_Bibliotheque *ptrB) {
    char name[50];
    int compteur = 0;
    
    printf("\nEntrez le nom de l'auteur recherché : ");
    fgets(name, 50, stdin);
    name[strlen(name) - 1] = '\0'; //Supprime le retour à la ligne
    for (int i=0; i<ptrB->nbLivres; i++) {
        if (!strcmp(ptrB->etagere[i].auteur, name)) {
            compteur++;
            afficherLivre(&ptrB->etagere[i]);
        }
    }
    if (!compteur) return 1;
    return 0;
}

int supprimerLivre(T_Bibliotheque *ptrB) {
	unsigned int code, position;
	char choice;

	printf("\nEntrez le code du livre à supprimer : ");
	scanf("%u", &code);
	position = rechercherLivreCode(ptrB, code);
	if(position==0)
		return 1; //Non trouvé, position impossible
	else {
		printf("Voulez-vous supprimer le livre suivant ?\n");
		afficherLivre(&ptrB->etagere[position]);
		printf("O/n : ");
		getchar();
		scanf("%c", &choice);
		switch (choice) {
			case 'o':
			case 'O':
			case 'y':
			case 'Y':
				ptrB->nbLivres--;
				for (unsigned i=position; i<ptrB->nbLivres; i++) {
					ptrB->etagere[i] = ptrB->etagere[i+1];
				}
				break;
			
			default:
				return 1;
				break;
		}
	}
	return 0;
}

int rechercherLivreCode(T_Bibliotheque *ptrB, unsigned id) {
	for (unsigned i=0; i<ptrB->nbLivres; i++) {
		if (ptrB->etagere[i].code==id)
			return i;
	}
	return 0; //N'existe pas
}

//FICHIERS
void sauvegarde(T_Bibliotheque *ptrB)
{
	FILE *fic = NULL; // le type FILE
	int i;
	fic = fopen("baseLivres", "w"); // w = le mode = write avec ECRASEMENT
	// fopen renvoie NULL si probleme (disque plein, disque non accessible ...
	if (fic != NULL)
	{
		for (i = 0; i < ptrB->nbLivres; i++)
		{
			// fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
			fwrite(&(ptrB->etagere[i]), sizeof(T_livre), 1, fic);
		}
		fclose(fic);
		puts("SAUVEGARDE REUSSIE ..............");
	}
	else
		puts("ECHEC DE SAUVEGARDE  !!!!!  ");
}

int chargement(T_Bibliotheque *ptrB)
{
	FILE *fic = NULL; // le type FILE
	int i = 0;
	fic = fopen("baseLivres", "r"); // r = le mode read
	// fopen renvoie NULL si probleme (disque plein, disque non accessible ...
	if (fic != NULL)
	{
		do
		{

			fread(&(ptrB->etagere[i]), sizeof(T_livre), 1, fic);
			i++;
		} while (!feof(fic));
		fclose(fic);
		ptrB->nbLivres = i - 1;
		puts("CHARGEMENT  REUSSI ..............");
		return 0;
	}
	else
		puts("ECHEC DE CHARGEMENT  !!!!!  ");
		return 1;
}

void lectureFichierTXT()
{
	int M = 100;
	FILE *fic = NULL; // le type FILE
	char chaine[M];
	char chaine2[M];
	char c;
	fic = fopen("fic.txt", "rt"); // r = le mode read   w = mode write (avec ecrasement)
	// fopen renvoie NULL si probleme (fichier effac� , disque non accessible ...
	if (fic != NULL)
	{
		do
		{
			// fgets(chaine,M,fic);   //fputs pour �crire dans un fichier txt
			// fscanf(fic,"%s",chaine); //fprintf pour �crire dans un fichier txt
			//	fscanf(fic,"%s %s",chaine,chaine2);
			fscanf(fic, "%c", &c);
			// fscanf(fic,"%c",&chaine[0]);
			//	if (!feof(fic))
			// printf("\n\t >%s--%s<",chaine,chaine2);
			printf(">%c<", c);
		} while (!feof(fic));
		fclose(fic);
		puts("\nLECTURE REUSSIE ..............");
	}
	else
		puts("ECHEC DE LECTURE DU FICHIER TXT !!!!!  ");
}

unsigned int getID() {
	unsigned int id = 1;
	FILE* fp = NULL;
	
	fp = fopen("id.dat", "rb");
	if (!fp) {
		fprintf(stderr, "ERR: Impossible d'ouvrir le fichier. Création de id.dat.\n");
		setID(1);
		return 1;
	}
	fread(&id, sizeof(unsigned int), 1, fp);
	fclose(fp);
	return id;
}

void setID(unsigned int id) {
	FILE* fp = NULL;
	fp = fopen("id.dat", "wb");
	fwrite(&id, sizeof(unsigned int), 1, fp);
	fclose(fp);
}