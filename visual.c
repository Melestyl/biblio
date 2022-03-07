#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

void draw_menu(WINDOW *menubar, char functNames[26][51]);

int main(void) {
    WINDOW *left, *right, *bott;
    int selecteur = 255;

    
    // Définition des noms de fonction :
    char functNames[26][51] =   {
                                    {"  ----------   FONCTIONS D'AFFICHAGE   ----------  "},
                                    {""},
                                    {"Afficher la bibliothèque"},
                                    {"Afficher les livres disponibles"},
                                    {""},
                                    {"  ----------  FONCTIONS DE RECHERCHE   ----------  "},
                                    {""},
                                    {"Recherche un livre - Par code"},
                                    {"Recherche un livre - Par titre"},
                                    {"Recherche un livre - Par auteur"},
                                    {""},
                                    {"  ----------     FONCTIONS DE TRI      ----------  "},
                                    {""},
                                    {"Trier les livres - Par titre"},
                                    {"Trier les livres - Par auteur"},
                                    {"Trier les livres - Par année"},
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

    initscr();

    int i; // Boucleur
    int status = 1; // Main boucle working ?


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


    int choix;
    char test[100];
    while (choix = getch()){
        // Menu checking for input
        sprintf(test, "%d", choix);
        mvwprintw(left, 0, 0, test);
        switch (choix)
        {
        case 65: //Up Arrow
            werase(left);
            werase(right);
            werase(bott);
            selecteur--;
            if(selecteur < 0)
                selecteur = 25;
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

        case 10: //Down Arrow
            werase(right);
            mvwprintw(right, 20, 20, "TEST");
            break;

        default:
            break;
        }
        if(selecteur != 255){
            box(left, ACS_VLINE, ACS_HLINE);
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


    //  ----- Menu Window ----- //
    mvwprintw(menubar, 0, 2, "MENU DE FONCTIONS");
    for (i = 0; i < 26; i++)    
        mvwprintw(menubar, (3*LINES/4 - 26)/2 + i, (COLS/3-51)/2, functNames[i]);
}