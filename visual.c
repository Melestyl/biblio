#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
// TP GESTION D'UNE BIBLIOTHEQUE
#include "biblio.h"
#include <signal.h>
#include <unistd.h>
#include <math.h>

T_Bibliotheque B; // VARIABLE GLOBALE DE CE FICHIER

void terminate() {
	sauvegarde(&B);
}

void sig_handler(int signum){
	printf("\nCtrl+C detecte.\n");
	exit(0);
}

void draw_menu(WINDOW *menubar, char functNames[26][51]);
void decallage(char commandHistory[30][150], int historySize, const int maxHistorySize);
void inputFunction(char entree[], char entreeDesc[], WINDOW *right, WINDOW *left, char functNames[26][51], int COLS, int LINES);
void affichageUni(WINDOW *right, const int COLS, const int LINES, int currPage, char description[]);
void affichageMulti(WINDOW *right, const int COLS, const int LINES, int currPage, char description[]);

int main(void) {
    WINDOW *left, *right, *bott; // Definitions des sections
    initscr(); 

    int i; // Boucleur

    int selecteur = 255;
    int historySize = 1; // 1 parce qu'on y met le message de demarrage
    int stringLen; 
    int status = 1; // Main boucle working ?

    int onScreen = 255;
    int nbPage = 0;

    char input1[100], input2[100], input3[100], input4[100];

    /* void (*func[25])(void); // Tableau de pointeurs de fonctions
    func[24] = errorMessage;
    func[0] = afficherBibliotheque;
    func[1] = afficherLivresDisponibles;
    func[2] = rechercherLivreCode;
    func[3] = rechercherLivreTitre;
    func[4] = afficherLivresAuteur; */
    
    char commandHistory[30][150];
    char temp[30] = ">>> Lancement du programme."; // Message de demarrage
    strcpy(commandHistory[i], temp);

    // Definition des noms de fonction : 
    char functNames[26][51] =   {
                                    {"  ----------   FONCTIONS D'AFFICHAGE   ----------  "},
                                    {""},
                                    {"Afficher la bibliotheque"},
                                    {"Afficher les livres disponibles"},
                                    {""},
                                    {"  ----------  FONCTIONS DE RECHERCHE   ----------  "},
                                    {""},
                                    {"Rechercher un livre - Par code"},
                                    {"Rechercher un livre - Par titre"},
                                    {"Rechercher un livre - Par auteur"},
                                    {""},
                                    {"  ----------     FONCTIONS DE TRI      ----------  "},
                                    {""},
                                    {"Trier les livres - Par titre"},
                                    {"Trier les livres - Par auteur"},
                                    {"Trier les livres - Par annee"},
                                    {""},
                                    {"  ----------    FONCTIONS D'EMPRUNT    ----------  "},
                                    {""},
                                    {"Emprunter un livre"},
                                    {"Restituer un livre"},
                                    {""},
                                    {"  ---------- FONCTIONS DE MODIFICATION ----------  "},
                                    {""},
                                    {"Ajouter un livre"},
                                    {"Supprimer un livre"}
                                };
    int unclickable[26] = {1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0};




    left= subwin(stdscr, 3* LINES / 4, COLS/3, 0, 0);        // Cree une fenêtre de 'LINES / 2' lignes et de COLS colonnes en 0, 0
    right= subwin(stdscr, 3* LINES / 4, 2*COLS/3 + 1, 0, COLS/3); // Cree la même fenêtre que ci-dessus sauf que les coordonnees changent
    bott= subwin(stdscr, LINES / 4, COLS, 3* LINES / 4, 0);

    box(left, ACS_VLINE, ACS_HLINE);
    box(right, ACS_VLINE, ACS_HLINE);
    box(bott, ACS_VLINE, ACS_HLINE);
    




    draw_menu(left, functNames);

    mvwprintw(right, 0, 2, "RESULTATS");
    mvwprintw(bott, 0, 2, "HISTORIQUE DE MANIPULATIONS");

    start_color();  
    init_color(COLOR_BLUE, 300, 0, 1000);
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    wbkgd(left, COLOR_PAIRS);
    wbkgd(right, COLOR_PAIRS);
    wbkgd(bott, COLOR_PAIRS);

    int maxHistorySize = LINES/4 - 3;
    for (i = 0; i < historySize && i < maxHistorySize; i++){
        mvwprintw(bott, 2+i, 4, commandHistory[i]);
    }

    wrefresh(left);
    wrefresh(right);
    wrefresh(bott);

    int choix;
    char test[100];
    while (status){
        choix = getch();
        // Menu checking for input
        /* sprintf(test, "%d", choix);
        mvwprintw(left, 0, 0, test); */
        switch (choix)
        {
        case 65: //Up Arrow
            werase(left);
            werase(right);
            werase(bott);
            selecteur--;
            if(selecteur < 2)
                selecteur = 25;
            else if(selecteur > 25)
                selecteur = 2;
            while (unclickable[selecteur])
                selecteur--;
            break;

        case 66: //Down Arrow
            werase(left);
            werase(right);
            werase(bott);
            selecteur++;
            if(selecteur > 25)
                selecteur = 0;
            while (unclickable[selecteur])
                selecteur++;
            break;

        case 10: //Enter
            switch (selecteur)
            {
            case 255:
                werase(left);
                box(right, ACS_VLINE, ACS_HLINE);
                mvwprintw(right, 0, 2, "RESULTATS");
                mvwprintw(right, 3*LINES/8 , (3*COLS/4)/2 -38/2, "NOTHING SELECTED - DO PLEASE TRY AGAIN"); //38
                break;
            
            case 2:
                onScreen = 2;
                nbPage = 0;
                break;
            
            case 3:
                onScreen = 3;
                nbPage = 0;
                break;

            case 7:
                onScreen = 7;
                nbPage = 0;
                break;
            
            case 8:
                onScreen = 8;
                nbPage = 0;
                break;

             case 9:
                onScreen = 9;
                nbPage = 0;
                break;
            

            case 13:
                onScreen = 13;
                nbPage = 0;
                break;
            
            case 14:
                onScreen = 14;
                nbPage = 0;
                break;

            case 15:
                onScreen = 15;
                nbPage = 0;
                break;

            case 19:
                inputFunction(input1, "Entrez le code d'un livre a emprunter", right, left, functNames, COLS, LINES);
                onScreen = 19;
                break;
            
            case 20:
                inputFunction(input1, "Entrez le code d'un livre a rendre", right, left, functNames, COLS, LINES);
                onScreen = 20;
                break;

            case 24:
                inputFunction(input1, "Entrez le code d'un livre a ajouter", right, left, functNames, COLS, LINES);
                onScreen = 24;
                break;
            
            case 25:
                inputFunction(input1, "Entrez le code d'un livre a supprimer", right, left, functNames, COLS, LINES);
                inputFunction(input2, "Etes vous sur de vouloir supprimer ce livre ? O/n", right, left, functNames, COLS, LINES);
                onScreen = 25;
                break;
            
    

            default:
                break;
            }

            if (selecteur != 255){
                werase(bott);
                decallage(commandHistory, historySize, maxHistorySize);
                temp[0] = '\0';
                strcpy(temp, ">>> ");
                strcat(temp, functNames[selecteur]);
                stringLen = strlen(functNames[selecteur]);
                temp[stringLen + 4] = '\0';
                strcpy(commandHistory[0], temp);
                historySize++;
            
            }
            break;

        case 67:
            nbPage++;
            if (onScreen == 2){
                werase(right);
                affichageMulti(right, COLS, LINES, nbPage, "Livres de la bibliothèque :");
            }
            break;

        case 68:
            nbPage--;
            if (onScreen == 2){
                werase(right);
                affichageMulti(right, COLS, LINES, nbPage, "Livres de la bibliothèque :");
            }
            break;
            

        default:
            break;  
        }
        if(selecteur != 255){
            box(right, ACS_VLINE, ACS_HLINE);
            box(bott, ACS_VLINE, ACS_HLINE);
            wbkgd(left, COLOR_PAIRS);
            wbkgd(right, COLOR_PAIRS);
            wbkgd(bott, COLOR_PAIRS);
            draw_menu(left, functNames);
            wattron(left, A_STANDOUT);
            mvwprintw(left, (3*LINES/4 - 26)/2 + selecteur, (COLS/3-51)/2, functNames[selecteur]);
            wattroff(left, A_STANDOUT);
            

            mvwprintw(right, 0, 2, "RESULTATS");
            mvwprintw(bott, 0, 2, "HISTORIQUE DE MANIPULATIONS");
        }

        else if(selecteur == 255){
            draw_menu(left, functNames);
        }

        else
            box(left, ACS_VLINE, ACS_HLINE); 
        

        for (i = 0; i < historySize && i < maxHistorySize; i++){
            mvwprintw(bott, 2+i, 4, commandHistory[i]);
        }
        werase(left);
        draw_menu(left, functNames);
        wattron(left, A_STANDOUT);
        mvwprintw(left, (3*LINES/4 - 26)/2 + selecteur, (COLS/3-51)/2, functNames[selecteur]);
        wattroff(left, A_STANDOUT);

        

        switch (onScreen)
        {
        case 2:
            werase(right);
            affichageMulti(right, COLS, LINES, nbPage, "Livres de la bibliothèque :");
            break;
        
        case 3:
            werase(right);
            affichageMulti(right, COLS, LINES, nbPage, "Livres disponibles :");
            break;

        case 7:
            werase(right);
            affichageMulti(right, COLS, LINES, nbPage, "Recherche de livre - par code");
            break;
        
        case 8:
            werase(right);
            affichageMulti(right, COLS, LINES, nbPage, "Recherche de livre - par titre");
            break;

        case 9:
            werase(right);
            affichageMulti(right, COLS, LINES, nbPage, "Recherche de livre - par auteur");
            break;
        
        case 13:
            werase(right);
            affichageMulti(right, COLS, LINES, nbPage, "Livres tries - par titre");
            break;
        
        case 14:
            werase(right);
            affichageMulti(right, COLS, LINES, nbPage, "Livres tries - par auteur");
            break;

        case 15:
            werase(right);
            affichageMulti(right, COLS, LINES, nbPage, "Livres tries - par annee");
            break;
        
        case 19:
            werase(right);
            affichageUni(right, COLS, LINES, nbPage, "Le livre emprunte");
            break;
        
        case 20:
            werase(right);
            affichageUni(right, COLS, LINES, nbPage, "Le livre rendu : ");
            break;

        case 24:
            werase(right);
            affichageUni(right, COLS, LINES, nbPage, "Le livre cree: ");
            break;
        
        case 25:
            werase(right);
            affichageUni(right, COLS, LINES, nbPage, "Le livre supprimee : ");
            break;

        default:
            break;
        }

        sprintf(test, "%d", choix);
        mvwprintw(left, 0, 0, test);
        wrefresh(left);
        wrefresh(right);
        wrefresh(bott);
    
    }

    
    getch();
    endwin();
    
    free(left);
    free(right);
    free(bott);
    
    return 0;
}


void draw_menu(WINDOW *menubar, char functNames[26][51]){
    int i; //Boucleur
    start_color();  
    init_color(COLOR_BLUE, 300, 0, 1000);
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
     wbkgd(menubar, COLOR_PAIRS);

    //  ----- Menu Window ----- //
    box(menubar, ACS_VLINE, ACS_HLINE);
    mvwprintw(menubar, 0, 2, "MENU DE FONCTIONS");
    for (i = 0; i < 26; i++)    
        mvwprintw(menubar, (3*LINES/4 - 26)/2 + i, (COLS/3-51)/2, functNames[i]);
}


void decallage(char commandHistory[30][150], int historySize, const int maxHistorySize){
    int max = (historySize > maxHistorySize) ? historySize:maxHistorySize;

    for(int i = max-1; i >= 0 ; i--)
        strcpy(commandHistory[i+1], commandHistory[i]);
}


void inputFunction(char entree[], char entreeDesc[], WINDOW *right, WINDOW *left, char functNames[26][51], int COLS, int LINES){
    int status = 1;
    int choix;
    int longueurChaine = 0;
    char chaine[2];
    int lastWasBracket = 0;

    int maxInputLen = 40;
    // On vide la chaine :
    entree[0] = '\0';

    move(LINES, COLS);

    // Calcul de centrage :
    int leftPos = (3*COLS/4)/2 -maxInputLen/2;
    int topPos = (3*LINES/4)/2;
    werase(right);
    box(right, ACS_VLINE, ACS_HLINE);
    mvwprintw(right, 0, 2, "RESULTATS");
    mvwprintw(right, topPos, leftPos, entreeDesc);
    werase(left);
    draw_menu(left,  functNames);
    wrefresh(left);
    wrefresh(right);
    while (status){
        move(topPos+1, leftPos+(COLS/4)+maxInputLen/2-1+longueurChaine);
        choix = getch();
        if (longueurChaine < maxInputLen && ((choix >= 'a' && choix <= 'z') || (choix >= 'A' && choix <= 'Z') || (choix >= 32 && choix <= 64))){
            chaine[0] = choix;
            strcat(entree, chaine);
            longueurChaine++;
        }

        else if (choix == 10)
            status = 0;

        else if (choix == 127){
            if (longueurChaine > 0){
                entree[longueurChaine-1] = '\0';
                longueurChaine--;
            }
        }
        werase(right);
        werase(left);
        draw_menu(left,  functNames);
        box(right, ACS_VLINE, ACS_HLINE);
        mvwprintw(right, 0, 2, "RESULTATS");
        mvwprintw(right, topPos, leftPos, entreeDesc);
        mvwprintw(right, topPos+1, leftPos, entree);
        wrefresh(right);
        wrefresh(left);
    }
};


void affichageUni(WINDOW *right, const int COLS, const int LINES, int currPage, char description[]){ //Need a string tab
    //On suppose la longueur max de la description de 50:
    int bookW = 50;
    int bookH = 9;
    int x = (3*LINES/4)/2 - bookH/2;
    int y = (3*COLS/4)/2 - bookW/2;
    int z;
    int spaceBetween = 0;
    box(right, ACS_VLINE, ACS_HLINE);
    mvwprintw(right, 0, 2, "RESULTATS");

    mvwprintw(right, x-2, y, description);

    for(z = 0; z<=bookW; z++)
        mvwprintw(right, x, y+z, "-");
    mvwprintw(right, 1+x, y-1, "|");
    mvwprintw(right, 1+x, y, "Titre du livre");
    mvwprintw(right, 1+x, y+bookW, "|");

    //Auteur
    mvwprintw(right, 2+x, y-1, "|");
    mvwprintw(right, 2+x, y, "Auteur du livre");
    mvwprintw(right, 2+x, y+bookW, "|");

    //Editeur
    mvwprintw(right, 3+x, y-1, "|");
    mvwprintw(right, 3+x, y, "Editeur du livre");
    mvwprintw(right, 3+x, y+bookW, "|");

    //Annee
    mvwprintw(right, 4+x, y-1, "|");
    mvwprintw(right, 4+x, y, "Annee du livre");
    mvwprintw(right, 4+x, y+bookW, "|");

    //Code
    mvwprintw(right, 5+x, y-1, "|");
    mvwprintw(right, 5+x, y, "Code du livre");
    mvwprintw(right, 5+x, y+bookW, "|");

    //Emprunteur
    mvwprintw(right, 6+x, y-1, "|");
    mvwprintw(right, 6+x, y, "Emprunteur ?");
    mvwprintw(right, 6+x, y+bookW, "|");

    //Date d'emprunt
    mvwprintw(right, 7+x, y-1, "|");
    mvwprintw(right, 7+x, y, "Date d'emprunt");
    mvwprintw(right, 7+x, y+bookW, "|");
    for(z = 0; z<=bookW; z++)
        mvwprintw(right, x+8, y+z, "-");
    wrefresh(right);
}


void affichageMulti(WINDOW *right, const int COLS, const int LINES, int currPage, char description[]){ //Need a string tab
    int sectionW = 3*COLS/4;
    int sectionH = 3*LINES/4;
    int i,y,z; //Boucleurs
    int posi = 0;

    char other[50] = "";
    char nb[25] = "";
    char total[25] = "";

    //TEMP
    int nbBook = 25; // Passe en paramètres

    // Not responsive at all
    int bookW = (sectionW-10)/3 - 11;
    int bookH = 9;
    int nbBookPage = 9;
    int nbBookLastPage = nbBook%nbBookPage;
    int nbPages = ceil(nbBook/nbBookPage);

    int nbLign = 0;
    int nbColo = 0;
    
    int spaceBetween = (sectionH - 3*bookH)/4;
    //spaceBetween = 5;

    currPage++; //Pour qu'on ait une première page a 1

    nbPages = 9;
    while (currPage>nbPages)
        currPage += -nbPages;
    while (currPage<= 0)
        currPage += nbPages;

    box(right, ACS_VLINE, ACS_HLINE);
    mvwprintw(right, 0, 2, "RESULTATS");

    mvwprintw(right, 2, 2, description);
        
    if (currPage != nbPages || nbBookLastPage == 0){ // Si on n'est pas sur la dernière page
        for(i = 0; i < nbBookPage/3; i++){
            for (y = 0; y < 3; y++){

                if (y>0)
                    posi = 1;
                else  
                    posi = 0;

                //Titre
                for(z = 0; z<=bookW; z++)
                    mvwprintw(right, 4+spaceBetween+i*(bookH+spaceBetween)-1, 5+(y*bookW)+y*5+z, "-");
                mvwprintw(right, 4+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+y*5, "|");
                mvwprintw(right, 4+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+y*5+2, "Titre du livre");
                mvwprintw(right, 4+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+bookW + y*5, "|");

                //Auteur
                mvwprintw(right, 5+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+y*5, "|");
                mvwprintw(right, 5+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+y*5+2, "Auteur du livre");
                mvwprintw(right, 5+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+bookW + y*5, "|");

                //Editeur
                mvwprintw(right, 6+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+y*5, "|");
                mvwprintw(right, 6+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+y*5+2, "Editeur du livre");
                mvwprintw(right, 6+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+bookW + y*5, "|");

                //Annee
                mvwprintw(right, 7+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+y*5, "|");
                mvwprintw(right, 7+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+y*5+2, "Annee du livre");
                mvwprintw(right, 7+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+bookW + y*5, "|");

                //Code
                mvwprintw(right, 8+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+y*5, "|");
                mvwprintw(right, 8+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+y*5+2, "Code du livre");
                mvwprintw(right, 8+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+bookW + y*5, "|");

                //Emprunteur
                mvwprintw(right, 9+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+y*5, "|");
                mvwprintw(right, 9+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+y*5+2, "Emprunteur ?");
                mvwprintw(right, 9+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+bookW + y*5, "|");

                //Date d'emprunt
                mvwprintw(right, 10+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+y*5, "|");
                mvwprintw(right, 10+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+y*5+2, "Date d'emprunt");
                mvwprintw(right, 10+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+bookW + y*5, "|");
                for(z = 0; z<=bookW; z++)
                    mvwprintw(right, 10+spaceBetween+i*(bookH+spaceBetween)+1, 5+(y*bookW)+y*5+z, "-");
            }
        }
    }

    else{ // Si on n'est pas sur la dernière page
        nbLign = nbBookLastPage/3;
        nbColo = nbBookLastPage%3;
        for(i = 0; i < nbLign; i++){
            for (y = 0; y < 3; y++){

                if (y>0)
                    posi = 1;
                else  
                    posi = 0;

                //Titre
                for(z = 0; z<=bookW; z++)
                    mvwprintw(right, 0+spaceBetween+i*(bookH+spaceBetween)-1, 5+(y*bookW)+y*5+z, "-");
                mvwprintw(right, 0+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+y*5, "|");
                mvwprintw(right, 0+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+y*5+2, "Titre du livre");
                mvwprintw(right, 0+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+bookW + y*5, "|");

                //Auteur
                mvwprintw(right, 1+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+y*5, "|");
                mvwprintw(right, 1+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+y*5+2, "Auteur du livre");
                mvwprintw(right, 1+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+bookW + y*5, "|");

                //Editeur
                mvwprintw(right, 2+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+y*5, "|");
                mvwprintw(right, 2+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+y*5+2, "Editeur du livre");
                mvwprintw(right, 2+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+bookW + y*5, "|");

                //Annee
                mvwprintw(right, 3+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+y*5, "|");
                mvwprintw(right, 3+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+y*5+2, "Annee du livre");
                mvwprintw(right, 3+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+bookW + y*5, "|");

                //Code
                mvwprintw(right, 4+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+y*5, "|");
                mvwprintw(right, 4+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+y*5+2, "Code du livre");
                mvwprintw(right, 4+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+bookW + y*5, "|");

                //Emprunteur
                mvwprintw(right, 5+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+y*5, "|");
                mvwprintw(right, 5+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+y*5+2, "Emprunteur ?");
                mvwprintw(right, 5+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+bookW + y*5, "|");

                //Date d'emprunt
                mvwprintw(right, 6+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+y*5, "|");
                mvwprintw(right, 6+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+y*5+2, "Date d'emprunt");
                mvwprintw(right, 6+spaceBetween+i*(bookH+spaceBetween), 5+(y*bookW)+bookW + y*5, "|");
                for(z = 0; z<=bookW; z++)
                    mvwprintw(right, 6+spaceBetween+i*(bookH+spaceBetween)+1, 5+(y*bookW)+y*5+z, "-");
            }
        }
    }


    if (currPage>9)
            sprintf(nb, "%d", currPage);
        else
            sprintf(nb, "0%d", currPage);

        if (nbPages>9)
            sprintf(total, "%d", nbPages);
        else
            sprintf(total, "0%d", nbPages);

        mvwprintw(right, sectionH-2, sectionW/2-8, "<");
        sprintf(other, "%s/%s", nb, total);
        mvwprintw(right, sectionH-2, sectionW/2-6, other);
        mvwprintw(right, sectionH-2, sectionW/2, ">");

        sprintf(other, "Et %d autres livres..", nbBook-nbBookPage);
        mvwprintw(right, sectionH-2, sectionW-50, other);    
    wrefresh(right);
}
