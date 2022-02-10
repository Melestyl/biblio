#include "es.h"

char *lire(char *lachaine, int nbMAXcaracAsaisir)
{
	char car;
	int i = 0, nbesp = 0;
	do
	{
		car = getchar();
		// printf("\n>>%c",car);
		if (car != '\n')
		{
			if (car != ' ') // ou if (car!=32)
			{
				lachaine[i++] = car;
				nbesp = 0;
			}
			else
			{ // c'est un espace
				if (i != 0 && nbesp == 0)
				{
					lachaine[i++] = car;
					nbesp++;
				}
			}
		}
	} while (car != '\n' && i < nbMAXcaracAsaisir);
	// le caractere \n est rangé dans lachaine !!
	lachaine[i] = '\0';

	if (i == nbMAXcaracAsaisir)
		if (lachaine[i - 2] == ' ')
			lachaine[i - 2] = '\0';
		else
			lachaine[i - 1] = '\0';
	else // i<MAX
		if (lachaine[i - 1] == ' ')
			lachaine[i - 1] = '\0';

	return lachaine;
}

char *lireChaine(const char *nomChamps, char *chaine, int nbcarac)
{
	printf("%s  ", nomChamps);
	lire(chaine, nbcarac); // lire du TP4 (modifiée)
	return chaine;
}

void afficherChaine(const char *nomChamp, const char *valeur)
{
	printf("%s %s", nomChamp, valeur);
}

// FICHIER
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

void chargement(T_Bibliotheque *ptrB)
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
	}
	else
		puts("ECHEC DE CHARGEMENT  !!!!!  ");
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
		fprintf(stderr, "Impossible d'ouvrir le fichier. Création de id.dat.\n");
		fclose(fp);
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