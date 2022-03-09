#include "biblio.h"

void init(T_Bibliotheque *ptrB)
{
	if (chargement(ptrB))
		ptrB->nbLivres = 0;
}

int ajouterLivre()
{
	unsigned int id = getID();

	if (NBLivres == CAPACITE_BIBLIO)
		return 1;
	T_livre livre;
	saisirLivre(&livre);
	livre.code = id;
	livre.emprunteur.emprunt = 0;
	ecrireLivre(livre);
	NBLivres++;
	printf("\nLe livre possède le code %u.\n", id);
	setID(id + 1);
	return 0;
}

int afficherBibliotheque()
{
	T_livre livre;

	printf("\nAffichage de la bibliothèque :\n");
	if (NBLivres == 0)
		return 1;
	allerDebut();
	for (int i = 0; i < NBLivres; i++)
	{
		livre = lireLivre();
		afficherLivre(&livre);
	}
	return 0;
}

int rechercherLivreTitre(const char titre[])
{
	int compteur = 0;
	T_livre livre;

	allerDebut();
	for (int i = 0; i < NBLivres; i++)
	{
		livre = lireLivre();
		if (!strcmp(livre.titre, titre))
		{
			afficherLivre(&livre);
			compteur++;
		}
	}

	if (compteur == 0)
		return 1;
	printf("\nIl existe %d livre(s) de ce titre dans la bibliothèque.", compteur);
	return 0;
}

int afficherLivresAuteur()
{
	char name[50];
	int compteur = 0;
	T_livre livre;

	printf("\nEntrez le nom de l'auteur recherché : ");
	fgets(name, 50, stdin);
	name[strlen(name) - 1] = '\0'; // Supprime le retour à la ligne

	allerDebut();
	for (int i = 0; i < NBLivres; i++)
	{
		livre = lireLivre();
		if (!strcmp(livre.auteur, name))
		{
			compteur++;
			afficherLivre(&livre);
		}
	}
	if (!compteur)
		return 1;
	return 0;
}

int supprimerLivre()
{
	unsigned int code, position;
	char choice;
	T_livre livre;

	printf("\nEntrez le code du livre à supprimer : ");
	scanf("%u", &code);
	position = rechercherLivreCode(code);
	if (position == 0)
		return 1; // Non trouvé, position impossible
	else
	{
		allerA(position);
		livre = lireLivre();
		allerA(position);
		printf("Voulez-vous supprimer le livre suivant ?\n");
		afficherLivre(&livre);
		printf("o/n : ");
		getchar();
		scanf("%c", &choice);
		switch (choice)
		{
		case 'o':
		case 'O':
		case 'y':
		case 'Y':
			NBLivres--;
			for (unsigned i = position; i < NBLivres; i++)
			{
				avancer();
				livre = lireLivre();
				reculer();
				reculer();
				ecrireLivre(livre);
			}
			break;

		default:
			return 1;
			break;
		}
	}
	return 0;
}

int rechercherLivreCode(unsigned id)
{
	T_livre livre;

	allerDebut();
	for (unsigned i = 0; i < NBLivres; i++)
	{
		livre = lireLivre();
		if (livre.code == id)
			return i;
	}
	return 0; // N'existe pas
}

int emprunterLivre()
{
	char emp[20];
	unsigned id, position;
	T_livre livre;

	printf("\nQuel est le code du livre ? ");
	scanf("%u", &id);
	position = rechercherLivreCode(id);
	if (position == 0)
		return 1;
	else
	{
		allerA(position);
		livre = lireLivre();
		getchar();
		lireChaine("Quel est le nom de l'emprunteur ?", emp, K_MaxEmp);
		strcpy(livre.emprunteur.nom, emp);
		livre.emprunteur.emprunt = 1;
		lireDateSysteme(&livre.emprunteur);
		reculer();
		ecrireLivre(livre);
	}
	return 0;
}

int rendreLivre()
{
	unsigned id, position;
	T_livre livre;

	printf("\nQuel est le code du livre ? ");
	scanf("%u", &id);
	position = rechercherLivreCode(id);
	allerA(position);
	livre = lireLivre();
	if (livre.emprunteur.emprunt)
		livre.emprunteur.emprunt = 0;
	else
		return 1;
	reculer();
	ecrireLivre(livre);
	return 0;
}

char *lowerString(char chaine[], char copieChaine[])
{ // Sert pour trier sans considérer les majuscules
	int i = 0;
	strcpy(copieChaine, chaine);
	for (; copieChaine[i] != '\0' && copieChaine[i] != '\n'; i++)
		copieChaine[i] = tolower(copieChaine[i]);
	copieChaine[i] = '\0';
	return copieChaine;
}

/* void trierTitre(T_Bibliotheque *ptrB)
{
	T_livre aux;
	int j, order;
	char s1[80], s2[80];

	printf("\nDans quel ordre souhaitez-vous trier ? \n1. Croissant\n-1. Inverse\n: ");
	scanf("%d", &order);

	if (order == -1)
	{
		for (unsigned i = 0; i < ptrB->nbLivres; i++)
		{
			j = i;
			while ((j > 0) && (strcmp(lowerString(ptrB->etagere[j - 1].titre, s1), lowerString(ptrB->etagere[j].titre, s2)) < 0))
			{ // Tant que c'est inférieur
				aux = ptrB->etagere[j];
				ptrB->etagere[j] = ptrB->etagere[j - 1];
				ptrB->etagere[j - 1] = aux;
				j--;
			}
		}
	}
	else
	{
		for (unsigned i = 0; i < ptrB->nbLivres; i++)
		{
			j = i;
			while ((j > 0) && (strcmp(lowerString(ptrB->etagere[j - 1].titre, s1), lowerString(ptrB->etagere[j].titre, s2)) > 0))
			{ // Tant que c'est supérieur
				aux = ptrB->etagere[j];
				ptrB->etagere[j] = ptrB->etagere[j - 1];
				ptrB->etagere[j - 1] = aux;
				j--;
			}
		}
	}
}

void trierAuteur(T_Bibliotheque *ptrB)
{
	T_livre aux;
	int j, order;
	char s1[80], s2[80];

	printf("\nDans quel ordre souhaitez-vous trier ? \n1. Croissant\n-1. Inverse\n: ");
	scanf("%d", &order);

	if (order == -1)
	{
		for (unsigned i = 0; i < ptrB->nbLivres; i++)
		{
			j = i;
			while ((j > 0) && (strcmp(lowerString(ptrB->etagere[j - 1].auteur, s1), lowerString(ptrB->etagere[j].auteur, s2)) < 0))
			{ // Tant que c'est inférieur
				aux = ptrB->etagere[j];
				ptrB->etagere[j] = ptrB->etagere[j - 1];
				ptrB->etagere[j - 1] = aux;
				j--;
			}
		}
	}
	else
	{
		for (unsigned i = 0; i < ptrB->nbLivres; i++)
		{
			j = i;
			while ((j > 0) && (strcmp(lowerString(ptrB->etagere[j - 1].auteur, s1), lowerString(ptrB->etagere[j].auteur, s2)) > 0))
			{ // Tant que c'est supérieur
				aux = ptrB->etagere[j];
				ptrB->etagere[j] = ptrB->etagere[j - 1];
				ptrB->etagere[j - 1] = aux;
				j--;
			}
		}
	}
}

void trierAnnee(T_Bibliotheque *ptrB)
{
	T_livre aux;
	int j, order;

	printf("\nDans quel ordre souhaitez-vous trier ? \n1. Croissant\n-1. Inverse\n: ");
	scanf("%d", &order);

	if (order == -1)
	{
		for (unsigned i = 0; i < ptrB->nbLivres; i++)
		{
			j = i;
			while ((j > 0) && (ptrB->etagere[j - 1].annee < ptrB->etagere[j].annee))
			{ // Tant que c'est inférieur
				aux = ptrB->etagere[j];
				ptrB->etagere[j] = ptrB->etagere[j - 1];
				ptrB->etagere[j - 1] = aux;
				j--;
			}
		}
	}
	else
	{
		for (unsigned i = 0; i < ptrB->nbLivres; i++)
		{
			j = i;
			while ((j > 0) && (ptrB->etagere[j - 1].annee > ptrB->etagere[j].annee))
			{ // Tant que c'est supérieur
				aux = ptrB->etagere[j];
				ptrB->etagere[j] = ptrB->etagere[j - 1];
				ptrB->etagere[j - 1] = aux;
				j--;
			}
		}
	}
}

int afficherLivresDisponibles(const T_Bibliotheque *ptrB)
{
	int compteur = 0;
	for (int i = 0; i < ptrB->nbLivres; i++)
	{
		if (!ptrB->etagere[i].emprunteur.emprunt)
		{
			afficherLivre(&ptrB->etagere[i]);
			compteur++;
		}
	}

	if (compteur == 0)
		return 1;
	return 0;
}

int afficherLivresEnRetard(const T_Bibliotheque *ptrB) {
	int compteur = 0;
	time_t now = time( NULL );
	int days = now / (86400);

	for (int i = 0; (i < ptrB->nbLivres) && (ptrB->etagere[i].emprunteur.emprunt); i++)
	{
		if (days >= ptrB->etagere[i].emprunteur.days_unix + 7)
		{
			afficherLivre(&ptrB->etagere[i]);
			compteur++;
		}
	}

	if (compteur == 0)
		return 1;
	return 0;
} */

// FICHIERS
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

unsigned int getID()
{
	unsigned int id = 1;
	FILE *fp = NULL;

	fp = fopen("id.dat", "rb");
	if (!fp)
	{
		fprintf(stderr, "ERR: Impossible d'ouvrir le fichier. Création de id.dat.\n");
		setID(1);
		return 1;
	}
	fread(&id, sizeof(unsigned int), 1, fp);
	fclose(fp);
	return id;
}

void setID(unsigned int id)
{
	FILE *fp = NULL;
	fp = fopen("id.dat", "wb");
	fwrite(&id, sizeof(unsigned int), 1, fp);
	fclose(fp);
}



// DATE
void lireDateSysteme(T_Emp *E)
{
	char*	   days[]  = {"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};
	char*	   month[] = {"janvier", "février", "mars", "avril", "mai",	"juin", "juillet", "septembre", "octobre", "novembre", "décembre"};

	time_t now = time( NULL );
	struct tm * local = localtime(&now);
	
	E->lannee = local->tm_year + 1900;
	strcpy(E->lemois, month[local->tm_mon]);
	strcpy(E->lejour, days[local->tm_wday]);
	E->ledate = local->tm_mday;
	E->days_unix = now / (86400);
}



// FICHIERS ++++
void allerDebut() {
	fseek(fp, sizeof(int), SEEK_SET);
}

void avancer() {
	fseek(fp, sizeof(T_livre), SEEK_CUR);
}

void reculer() {
	fseek(fp, -1 * sizeof(T_livre), SEEK_CUR);
}

void allerA(unsigned pos) {
	allerDebut();
	fseek(fp, pos * sizeof(T_livre), SEEK_SET);
}

int getNBLivres() {
	int NBLivres = 0;

	rewind(fp);
	if(fread(&NBLivres, sizeof(int), 1, fp) == 0)
		fwrite(&NBLivres, sizeof(int), 1, fp);

	allerDebut();
	return NBLivres;
}

void setNBLivres() {
	rewind(fp);
	fwrite(&NBLivres, sizeof(int), 1, fp);

	allerDebut();
}

void ecrireLivre(T_livre livre) {
	fwrite(&livre, sizeof(T_livre), 1, fp);
}

T_livre lireLivre() {
	T_livre livre;
	fread(&livre, sizeof(T_livre), 1, fp);
	return livre;
}