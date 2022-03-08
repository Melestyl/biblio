#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
// TP GESTION D'UNE BIBLIOTHEQUE
#include "biblio.h"
#include <signal.h>
#include <unistd.h>

T_Bibliotheque B; // VARIABLE GLOBALE DE CE FICHIER

void terminate() {
	sauvegarde(&B);
}

void sig_handler(int signum){
	printf("\nCtrl+C detecté.\n");
	exit(0);
}

void draw_menu(WINDOW *menubar, char functNames[26][51]);
void decallage(char commandHistory[30][150], int historySize, const int maxHistorySize);
void inputFunction(char entree[], char entreeDesc[], WINDOW *right, WINDOW *left, char functNames[26][51], int COLS, int LINES);

int main(void) {
    WINDOW *left, *right, *bott; // Définitions des sections
    initscr(); 

    int i; // Boucleur

    int selecteur = 255;
    int historySize = 1; // 1 parce qu'on y met le message de démarrage
    int stringLen; 
    int status = 1; // Main boucle working ?

    char input1[100], input2[100], input3[100], input4[100];

    /* void (*func[25])(void); // Tableau de pointeurs de fonctions
    func[24] = errorMessage;
    func[0] = afficherBibliotheque;
    func[1] = afficherLivresDisponibles;
    func[2] = rechercherLivreCode;
    func[3] = rechercherLivreTitre;
    func[4] = afficherLivresAuteur; */
    
    char commandHistory[30][150];
    char temp[30] = ">>> Lancement du programme."; // Message de démarrage
    strcpy(commandHistory[i], temp);

    // Définition des noms de fonction : 
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




    left= subwin(stdscr, 3* LINES / 4, COLS/3, 0, 0);        // Créé une fenêtre de 'LINES / 2' lignes et de COLS colonnes en 0, 0
    right= subwin(stdscr, 3* LINES / 4, 2*COLS/3 + 1, 0, COLS/3); // Créé la même fenêtre que ci-dessus sauf que les coordonnées changent
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

    inputFunction(input1, "Veuillez entrer quelque chose :", right, left, functNames, COLS, LINES);
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
            if (selecteur == 255){
                werase(left);
                box(right, ACS_VLINE, ACS_HLINE);
                mvwprintw(right, 0, 2, "RESULTATS");
                mvwprintw(right, 3*LINES/8 , (3*COLS/4)/2 -38/2, "NOTHING SELECTED - DO PLEASE TRY AGAIN"); //38
            }
            else{
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

    int maxInputLen = 40;
    // On vide la chaine :
    entree[0] = '\0';

    move(LINES, COLS);

    // Calcul de centrage :
    int leftPos = (3*COLS/4)/2 -maxInputLen/2;
    int topPos = (3*LINES/4)/2;
    

    char temp[100];
    sprintf(temp, "%d", 3*COLS/12);
    mvwprintw(right, 2, 2, temp);

    wrefresh(right);
    mvwprintw(right, topPos, leftPos, entreeDesc);
    while (status){
        choix = getch();
        if (longueurChaine < maxInputLen && ((choix >= 'a' && choix <= 'z') || (choix >= 'A' && choix <= 'Z') || (choix >= 32 && choix <= 64))){ //|| (choix >= 91 && choix <= 96)){
            chaine[0] = choix;
            /* if (chaine[0] != '['  && chaine[0] != 'A'){
                strcat(entree, chaine);
                longueurChaine++;
            } */
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
    // La boucle est terminée on en sort :)
};
