#include "Personaggi.h"
#include "Menu.h"
#include "Area_gioco.h"
#include "Struct_enum.h"

int main()
{
    //generazione seme casuale
    srand(time(NULL));

    ///MENU DI AVVIO
    //dichiarazione sprite menu
    char sprite_titolo[ROWS_TITOLO][COLS_TITOLO+1];
    char sprite_peashooter[ALTEZZA_PEASHOOTER][LARGHEZZA_PEASHOOTER+1];
    char sprite_rana_menu[ALTEZZA_RANA_MENU][LARGHEZZA_RANA_MENU+1];

    //finestra di gioco
    WINDOW *gioco;

    //variabili aux menu
    int scelta=NOCHOICE;
    int scelta_nuova_partita=UP;

    //inizializzazione schermata di ncurses
    schermo();

    do{


        caricamento_sprite(FILE_TITOLO, ROWS_TITOLO, COLS_TITOLO, sprite_titolo);

        //creazione interfaccia menu principale
        gioco=inizializzazione_menu(gioco, ROWS_TITOLO, COLS_TITOLO, sprite_titolo, &scelta);

        do
        {
            //refresh e pagina menu di gioco
            wclear(gioco);
            box(gioco, ACS_VLINE, ACS_HLINE);
            wbkgd(gioco, COLOR_PAIR(BG_BLACK_C_GREEN));

            //ristampa grafiche
            caricamento_sprite(FILE_PEASHOOTER, ALTEZZA_PEASHOOTER, LARGHEZZA_PEASHOOTER, sprite_peashooter);
            stampa_sprite(gioco, ALTEZZA_PEASHOOTER, LARGHEZZA_PEASHOOTER, sprite_peashooter, ALTEZZA_SCHERMO/5, (LARGHEZZA_SCHERMO-2*LARGHEZZA_PEASHOOTER-COLS_TITOLO)/2);
            caricamento_sprite(FILE_RANA_MENU, ALTEZZA_RANA_MENU, LARGHEZZA_RANA_MENU, sprite_rana_menu);
            stampa_sprite(gioco, ALTEZZA_RANA_MENU, LARGHEZZA_RANA_MENU, sprite_rana_menu, ALTEZZA_SCHERMO/5, (LARGHEZZA_SCHERMO-2*LARGHEZZA_PEASHOOTER-COLS_TITOLO)/2 + LARGHEZZA_PEASHOOTER + COLS_TITOLO+6);

            wrefresh(gioco);

            ///SEZIONE GIOCO
            if((scelta)==UP)
            {
                mvwprintw(gioco, 1, LARGHEZZA_SCHERMO-strlen("PREMERE i PER TORNARE ALLA SCHERMATA PRECEDENTE")-2, "PREMERE i PER TORNARE ALLA SCHERMATA PRECEDENTE");

                //la scelta di tasto nel menu interno di base e' neutra
                scelta=NOCHOICE;

                //caricamento grafiche scelta difficolta
                caricamento_sprite(FILE_SCELTA_DIFFICOLTA, ROWS_TITOLO, COLS_TITOLO, sprite_titolo);
                stampa_sprite(gioco, ROWS_TITOLO, COLS_TITOLO, sprite_titolo, SCOSTAMENTO_V_TITOLO, (LARGHEZZA_SCHERMO-COLS_TITOLO)/2 + 1);
                creazione_tasti(gioco, &scelta, ALTEZZA_SCHERMO/2+1, (ALTEZZA_SCHERMO/2) + ALTEZZA_TASTO + 5, strlen(TESTO_NORMALE), strlen(TESTO_DIFFICILE), TESTO_NORMALE, TESTO_DIFFICILE);

                //se si compie una scelta, si esce dal ciclo e si seleziona la modalita' di gioco
                ///SCELTA GIOCO NORMALE
                if(scelta==UP)
                {
                    break;
                }
                ///SCELTA GIOCO DIFFICILE
                if(scelta==DOWN)
                {
                    break;
                }

                //altrimenti se si clicca 'i' si ritorna nel ciclo nell'esatto menu di prima, con HARD e NORMAL
                if(scelta==NOCHOICE)
                {
                    scelta=UP;
                }
            }

            ///SEZIONE BESTIARIO
            else if((scelta)==DOWN)
            {
                werase(gioco);
                box(gioco, ACS_VLINE, ACS_HLINE);

                bestiario(gioco);

                scelta=BACK;
            }

            ///SELEZIONE TASTI
            //scelta pagina precedente
            else if((scelta)==BACK)
            {
                caricamento_sprite(FILE_TITOLO, ROWS_TITOLO, COLS_TITOLO, sprite_titolo);
                stampa_sprite(gioco, ROWS_TITOLO, COLS_TITOLO, sprite_titolo, SCOSTAMENTO_V_TITOLO, (LARGHEZZA_SCHERMO-COLS_TITOLO)/2 + 1);
                creazione_tasti(gioco, &scelta,  ALTEZZA_SCHERMO/2+1, (ALTEZZA_SCHERMO/2) + ALTEZZA_TASTO + 5, strlen(TESTO_GIOCA), strlen(TESTO_HELP), TESTO_GIOCA, TESTO_HELP);
            }

        }while(true);

        ///SE SI ESCE DAL CICLO ALLORA --> UP=NORMALE, DOWN=DIFFICILE
        if(scelta==UP)
        {
            gameplay(gioco, NORMALE);
        }
        else if(scelta==DOWN)
        {
            gameplay(gioco, DIFFICILE);
        }

        ///CREAZIONE ITERFACCIA SCELTA NUOVA PARTITA
        scelta_nuova_partita=NOCHOICE;
        creazione_tasti(gioco, &scelta_nuova_partita,  ALTEZZA_SCHERMO/8*5, ALTEZZA_SCHERMO/8*5 +1 + ALTEZZA_TASTO+2, strlen("GIOCA ANCORA"), strlen("EXIT"), "GIOCA ANCORA", "EXIT");

        ///CHIUSURA GIOCO IN CASO DI CLICK SU 'EXIT'
    }while(scelta_nuova_partita!=DOWN && scelta_nuova_partita!=BACK);

    //chiusura interfaccia ncurses
    endwin();

    return 0;
}