#include "biblio.h"

void init(T_Bibliotheque *ptrB)
{
	if (chargement(ptrB))
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
	livre.emprunteur.emprunt = 0;
	ptrB->etagere[ptrB->nbLivres] = livre;
	ptrB->nbLivres++;
	printf("\nLe livre possède le code %u.\n", id);
	setID(id + 1);
	return 0;
}

int afficherBibliotheque(const T_Bibliotheque *ptrB)
{
	printf("\nAffichage de la bibliothèque :\n");
	if (ptrB->nbLivres == 0)
		return 1;
	for (int i = 0; i < ptrB->nbLivres; i++)
	{
		afficherLivre(&ptrB->etagere[i]);
	}
	return 0;
}

int rechercherLivreTitre(const T_Bibliotheque *ptrB, const char titre[])
{
	int compteur = 0;
	for (int i = 0; i < ptrB->nbLivres; i++)
	{
		if (!strcmp(ptrB->etagere[i].titre, titre))
		{
			afficherLivre(&ptrB->etagere[i]);
			compteur++;
		}
	}

	if (compteur == 0)
		return 1;
	printf("\nIl existe %d livre(s) de ce titre dans la bibliothèque.", compteur);
	return 0;
}

int afficherLivresAuteur(const T_Bibliotheque *ptrB)
{
	char name[50];
	int compteur = 0;

	printf("\nEntrez le nom de l'auteur recherché : ");
	fgets(name, 50, stdin);
	name[strlen(name) - 1] = '\0'; // Supprime le retour à la ligne
	for (int i = 0; i < ptrB->nbLivres; i++)
	{
		if (!strcmp(ptrB->etagere[i].auteur, name))
		{
			compteur++;
			afficherLivre(&ptrB->etagere[i]);
		}
	}
	if (!compteur)
		return 1;
	return 0;
}

int supprimerLivre(T_Bibliotheque *ptrB)
{
	unsigned int code, position;
	char choice;

	printf("\nEntrez le code du livre à supprimer : ");
	scanf("%u", &code);
	position = rechercherLivreCode(ptrB, code);
	if (position == 0)
		return 1; // Non trouvé, position impossible
	else
	{
		printf("Voulez-vous supprimer le livre suivant ?\n");
		afficherLivre(&ptrB->etagere[position]);
		printf("O/n : ");
		getchar();
		scanf("%c", &choice);
		switch (choice)
		{
		case 'o':
		case 'O':
		case 'y':
		case 'Y':
			ptrB->nbLivres--;
			for (unsigned i = position; i < ptrB->nbLivres; i++)
			{
				ptrB->etagere[i] = ptrB->etagere[i + 1];
			}
			break;

		default:
			return 1;
			break;
		}
	}
	return 0;
}

int rechercherLivreCode(T_Bibliotheque *ptrB, unsigned id)
{
	for (unsigned i = 0; i < ptrB->nbLivres; i++)
	{
		if (ptrB->etagere[i].code == id)
			return i;
	}
	return 0; // N'existe pas
}

int emprunterLivre(T_Bibliotheque *ptrB)
{
	char emp[20];
	unsigned id, position;

	printf("\nQuel est le code du livre ? ");
	scanf("%u", &id);
	position = rechercherLivreCode(ptrB, id);
	if (position == 0)
		return 1;
	else
	{
		getchar();
		lireChaine("Quel est le nom de l'emprunteur ?", emp, K_MaxEmp);
		strcpy(ptrB->etagere[position].emprunteur.nom, emp);
		ptrB->etagere[position].emprunteur.emprunt = 1;
		lireDateSysteme(&ptrB->etagere[position].emprunteur);
	}
	return 0;
}

int rendreLivre(T_Bibliotheque *ptrB)
{
	unsigned id, position;

	printf("\nQuel est le code du livre ? ");
	scanf("%u", &id);
	position = rechercherLivreCode(ptrB, id);
	if (ptrB->etagere[position].emprunteur.emprunt)
		ptrB->etagere[position].emprunteur.emprunt = 0;
	else
		return 1;
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

void trierTitre(T_Bibliotheque *ptrB)
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
}