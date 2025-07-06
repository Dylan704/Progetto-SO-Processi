//
// Created by dylan on 22/12/23.
//
#include "Area_gioco.h"
#include "Struct_enum.h"
#include "Personaggi.h"
#include "Menu.h"

/**
 * Funzione per inizializzare loschermo e i colori da usare per il resto del programma
 */
void schermo()
{
    //inizializza una nuova finestra
    initscr();
    //abilita ultilizzo dei colori
    start_color();
    //impedisce che l'input dell'utente non appaia a schermo
    noecho();
    //cursone non visibile
    curs_set(0);
    //non c'è bisogno di premere invio per iniviare un input
    cbreak();
    //abilita l'utilizzo del keypad (inutile per questo programma)
    keypad(stdscr, true);

    //sfinza di creazioni di colori e creazione copie di colori
    init_color(NERO_VERO, 0, 0, 0);
    init_pair(BG_BLACK, COLOR_WHITE, NERO_VERO);

    init_color(VERDOGNOLO, 200, 500, 200);
    init_pair(BG_MARCIAPIEDE_PIANTE, COLOR_WHITE, VERDOGNOLO);

    init_color(VIOLOGNOLO, 300, 62, 350);
    init_pair(BG_MARCIAPIEDE_RANA_TANE, COLOR_WHITE, VIOLOGNOLO);

    init_color(BLU_MARE, 150, 450, 900);
    init_pair(BG_LAGHETTO, COLOR_WHITE, BLU_MARE);

    init_color(VERDE_RANA, 0, 800, 0);
    init_pair(VERDE_RANA, COLOR_WHITE, VERDE_RANA);

    init_color(VERDE_PIANTA, 100, 900, 400);
    init_pair(VERDE_PIANTA, VERDE_PIANTA, VERDOGNOLO);

    init_pair(ROSSO_PROIETTILE_PIANTA, COLOR_WHITE, COLOR_RED);
    init_pair(GIALLO_PROIETTILE_RANA, COLOR_WHITE, COLOR_YELLOW);

    init_pair(BG_CYAN, COLOR_WHITE, COLOR_CYAN);
    init_pair(BG_GREEN, COLOR_WHITE, COLOR_GREEN);

    init_color(VERDE_COCCODRILLO_BUONO, 300, 500, 300);
    init_pair(VERDE_COCCODRILLO_BUONO, COLOR_WHITE, VERDE_COCCODRILLO_BUONO);

    init_color(ROSSO_COCCODRILLO_MALVAGIO, 500, 300, 200);
    init_pair(ROSSO_COCCODRILLO_MALVAGIO, COLOR_WHITE, ROSSO_COCCODRILLO_MALVAGIO);

    init_color(COLORE_TANA, 700, 350, 150);
    init_pair(COLORE_TANA, VIOLOGNOLO, COLORE_TANA);

    init_pair(COLORE_TESTO_PUNTEGGIO, COLOR_RED, NERO_VERO);

    init_pair(BG_BLACK_C_GREEN, COLOR_GREEN, NERO_VERO);
    init_pair(BG_BLACK_C_RED, COLOR_RED, NERO_VERO);
    init_pair(BG_GREEN_C_PURPLE, COLOR_GREEN, VIOLOGNOLO);

    init_pair(ROSSO_TIMER, COLOR_WHITE, COLOR_RED);

    refresh();
}

/**
 * creazione zone dello schermo, colorazione sfondo e reset
 *
 * @param gioco finestra di gioco dove si stampa
 * @param marciapiede_rana finestra nella quale viene creata la rana
 * @param laghetto finestra nella quale vengono creati i coccodrilli
 * @param marciapiede_piante finestra nella quale vengono create le piante
 * @param tane finestra nella quale vengonoo create le tane
 * @param stats finestra nella quale si trovano le statistiche del giocatore
 */
void area_gioco(WINDOW* gioco, WINDOW* marciapiede_rana, WINDOW* laghetto, WINDOW* marciapiede_piante, WINDOW* tane, WINDOW* stats)
{
    ///RESET BOX GIOCO
    //linea che divide l'area di gioco dalle stats
    for (int i = 1; i < LARGHEZZA_SCHERMO-1; ++i)
    {
        mvwaddch(gioco, ALTEZZA_STATS, i, ACS_HLINE);
    }
    box(gioco, ACS_VLINE, ACS_HLINE);

    ///CREAZIONE FINESTRE DERIVATE PER LO SFONDO
    marciapiede_rana = derwin(gioco, ALTEZZA_MARCIAPIEDE_RANA, LARGHEZZA_SCHERMO-2, ALTEZZA_SCHERMO-ALTEZZA_MARCIAPIEDE_RANA-1, 1);
    laghetto = derwin(gioco, ALTEZZA_LAGHETTO, LARGHEZZA_SCHERMO-2, ALTEZZA_SCHERMO-ALTEZZA_MARCIAPIEDE_RANA-ALTEZZA_LAGHETTO-1, 1);
    marciapiede_piante = derwin(gioco, ALTEZZA_MARCIAPIEDE_PIANTE, LARGHEZZA_SCHERMO-2, ALTEZZA_SCHERMO-ALTEZZA_MARCIAPIEDE_PIANTE-
                                                                                        ALTEZZA_MARCIAPIEDE_RANA-ALTEZZA_LAGHETTO-1, 1);
    tane = derwin(gioco, ALTEZZA_TANE, LARGHEZZA_SCHERMO-2, ALTEZZA_SCHERMO-ALTEZZA_MARCIAPIEDE_PIANTE-
                                                            ALTEZZA_TANE-ALTEZZA_MARCIAPIEDE_RANA-ALTEZZA_LAGHETTO-1, 1);
    stats = derwin(gioco, ALTEZZA_STATS, LARGHEZZA_SCHERMO-2, ALTEZZA_SCHERMO-ALTEZZA_MARCIAPIEDE_PIANTE-
                                                              ALTEZZA_TANE-ALTEZZA_MARCIAPIEDE_RANA-
                                                              ALTEZZA_STATS-ALTEZZA_LAGHETTO-1, 1);

    ///APPLICAZIONE SFONDO ALLE VARIE FINESTRE
    wbkgd(marciapiede_rana, COLOR_PAIR(BG_MARCIAPIEDE_RANA_TANE));
    wbkgd(laghetto, COLOR_PAIR(BG_LAGHETTO));
    wbkgd(marciapiede_piante, COLOR_PAIR(BG_MARCIAPIEDE_PIANTE));
    wbkgd(tane, COLOR_PAIR(BG_MARCIAPIEDE_RANA_TANE));

    ///RESET FINESTRE DERIVATE PER LO SFONDO
    delwin(marciapiede_rana);
    delwin(laghetto);
    delwin(marciapiede_piante);
    delwin(tane);
    delwin(stats);

    ///REFRESH GIOCO
    wrefresh(gioco);
}

/**
 * creazione processo rana
 *
 * @param gioco finestra di gioco dove si stampa
 * @param difficolta difficoltà scelta dal giocatore
 */
void gameplay(WINDOW* gioco, Difficolta difficolta)
{
    wbkgd(gioco, COLOR_PAIR(BG_BLACK));
    //linea che divide l'area di gioco dalle stats
    for (int i = 1; i < LARGHEZZA_SCHERMO-1; ++i)
    {
        mvwaddch(gioco, ALTEZZA_STATS, i, ACS_HLINE);
    }

    //inizializzazione pipe
    int pipefd[2];
    if(pipe(pipefd)==-1)
    {
        perror("Errore creazione pipe\n");
        endwin();
        exit(ERRORE_CREAZIONE_PIPE);
    }

    //generazione processo rana
    pid_t pid_rana;
    pid_rana=fork();
    switch(pid_rana)
    {
        case -1: 	//errore
            perror("Errore fork rana\n");
            endwin();
            exit(ERRORE_FORK_RANA);
        case 0:		//figlio rana
            close(pipefd[0]);
            pos_rana(pipefd[1]);
            return;

        default:	//padre controllo
            controllo(gioco, difficolta, pipefd[0], pipefd[1]);

            //kill del pid_rana successivamente che si è usciti dalla partita
            kill(pid_rana, SIGKILL);
            waitpid(pid_rana, NULL, 0);
    }
}

/**
 * Funzione che si occupa di stampare il punteggio
 *
 * @param gioco finestra di gioco dove si stampa
 * @param punteggio punteggio corrente del giocatore
 * @param inizio_y coordinate iniziale stampa
 * @param inizio_x coordinate iniziale stampa
 */
void stampa_punteggio(WINDOW* gioco, int punteggio, int inizio_y, int inizio_x)
{
    //serie di caricamento dello sprite points e di tutti i numeri da 0 a 9
    char sprite_punteggio[ALTEZZA_PUNTEGGIO][LARGHEZZA_PUNTEGGIO+1]=
            {
                    " _____ _____ _____ _____ _____ _____     ",
                    "|  _  |     |     |   | |_   _|   __|    ",
                    "|   __|  |  |-   -| | | | | | |__   |  o ",
                    "|__|  |_____|_____|_|___| |_| |_____|  o "
            };

    char sprite_zero[ALTEZZA_NUMERI][LARGHEZZA_NUMERI+1]=
            {
                    "  __  ",
                    " /  \\ ",
                    "| () |",
                    " \\__/  "
            };

    char sprite_uno[ALTEZZA_NUMERI][LARGHEZZA_NUMERI+1]=
            {
                    "  _   ",
                    " / |  ",
                    " | |  ",
                    " |_|  "
            };
    char sprite_due[ALTEZZA_NUMERI][LARGHEZZA_NUMERI+1]=
            {
                    "  ___ ",
                    " |_  )",
                    "  / / ",
                    " /___|"
            };
    char sprite_tre[ALTEZZA_NUMERI][LARGHEZZA_NUMERI+1]=
            {
                    "  ____",
                    " |__ /",
                    " |_  \\ ",
                    " |___/",
            };
    char sprite_quattro[ALTEZZA_NUMERI][LARGHEZZA_NUMERI+1]=
            {
                    " _ _  ",
                    "| | | ",
                    "|_  _| ",
                    "  |_| "
            };
    char sprite_cinque[ALTEZZA_NUMERI][LARGHEZZA_NUMERI+1]=
            {
                    "  ___ ",
                    " | __|",
                    " |__ \\",
                    " |___/"
            };
    char sprite_sei[ALTEZZA_NUMERI][LARGHEZZA_NUMERI+1]=
            {
                    "   __ ",
                    "  / / ",
                    " / _ \\",
                    " \\___/"
            };
    char sprite_sette[ALTEZZA_NUMERI][LARGHEZZA_NUMERI+1]=
            {
                    " ____ ",
                    "|__  |",
                    "  / / ",
                    " /_/  "
            };
    char sprite_otto[ALTEZZA_NUMERI][LARGHEZZA_NUMERI+1]=
            {
                    "  ___ ",
                    " ( _ )",
                    " / _ \\",
                    " \\___/"
            };
    char sprite_nove[ALTEZZA_NUMERI][LARGHEZZA_NUMERI+1]=
            {
                    "  ___ ",
                    " / _ \\",
                    " \\_, /",
                    "  /_/ "
            };

    ///STAMPA PUNTEGGIO
    wattron(gioco, COLOR_PAIR(COLORE_TESTO_PUNTEGGIO));
    stampa_sprite_personaggio(gioco, inizio_y, inizio_x, ALTEZZA_PUNTEGGIO, LARGHEZZA_PUNTEGGIO, sprite_punteggio);
    wattroff(gioco, COLOR_PAIR(COLORE_TESTO_PUNTEGGIO));

    int carattere_punteggio;
    for (int i = 0; i < 3; ++i)
    {
        if(i==0)
        {
            carattere_punteggio = 1000;
        }
        else if(i==1)
        {
            carattere_punteggio = 100;
        }
        else if(i==2)
        {
            carattere_punteggio = 10;
        }

        //selezione carattere punteggio da stampare tramite modulo
        carattere_punteggio = punteggio % carattere_punteggio / (carattere_punteggio/10);

        //selzione stampa in base al valore di carattere_punteggio
        switch (carattere_punteggio)
        {
            case 0:
                wattron(gioco, COLOR_PAIR(COLORE_TESTO_PUNTEGGIO));
                stampa_sprite_personaggio(gioco, inizio_y, inizio_x + LARGHEZZA_PUNTEGGIO + i*LARGHEZZA_NUMERI, ALTEZZA_NUMERI, LARGHEZZA_NUMERI, sprite_zero);
                wattroff(gioco, COLOR_PAIR(COLORE_TESTO_PUNTEGGIO));
                break;

            case 1:
                wattron(gioco, COLOR_PAIR(COLORE_TESTO_PUNTEGGIO));
                stampa_sprite_personaggio(gioco, inizio_y, inizio_x + LARGHEZZA_PUNTEGGIO + i*LARGHEZZA_NUMERI, ALTEZZA_NUMERI, LARGHEZZA_NUMERI, sprite_uno);
                wattroff(gioco, COLOR_PAIR(COLORE_TESTO_PUNTEGGIO));
                break;

            case 2:
                wattron(gioco, COLOR_PAIR(COLORE_TESTO_PUNTEGGIO));
                stampa_sprite_personaggio(gioco, inizio_y, inizio_x + LARGHEZZA_PUNTEGGIO + i*LARGHEZZA_NUMERI, ALTEZZA_NUMERI, LARGHEZZA_NUMERI, sprite_due);
                wattroff(gioco, COLOR_PAIR(COLORE_TESTO_PUNTEGGIO));
                break;

            case 3:
                wattron(gioco, COLOR_PAIR(COLORE_TESTO_PUNTEGGIO));
                stampa_sprite_personaggio(gioco, inizio_y, inizio_x + LARGHEZZA_PUNTEGGIO + i*LARGHEZZA_NUMERI, ALTEZZA_NUMERI, LARGHEZZA_NUMERI, sprite_tre);
                wattroff(gioco, COLOR_PAIR(COLORE_TESTO_PUNTEGGIO));
                break;

            case 4:
                wattron(gioco, COLOR_PAIR(COLORE_TESTO_PUNTEGGIO));
                stampa_sprite_personaggio(gioco, inizio_y, inizio_x + LARGHEZZA_PUNTEGGIO + i*LARGHEZZA_NUMERI, ALTEZZA_NUMERI, LARGHEZZA_NUMERI, sprite_quattro);
                wattroff(gioco, COLOR_PAIR(COLORE_TESTO_PUNTEGGIO));
                break;

            case 5:
                wattron(gioco, COLOR_PAIR(COLORE_TESTO_PUNTEGGIO));
                stampa_sprite_personaggio(gioco, inizio_y, inizio_x + LARGHEZZA_PUNTEGGIO + i*LARGHEZZA_NUMERI, ALTEZZA_NUMERI, LARGHEZZA_NUMERI, sprite_cinque);
                wattroff(gioco, COLOR_PAIR(COLORE_TESTO_PUNTEGGIO));
                break;

            case 6:
                wattron(gioco, COLOR_PAIR(COLORE_TESTO_PUNTEGGIO));
                stampa_sprite_personaggio(gioco, inizio_y, inizio_x + LARGHEZZA_PUNTEGGIO + i*LARGHEZZA_NUMERI, ALTEZZA_NUMERI, LARGHEZZA_NUMERI, sprite_sei);
                wattroff(gioco, COLOR_PAIR(COLORE_TESTO_PUNTEGGIO));
                break;

            case 7:
                wattron(gioco, COLOR_PAIR(COLORE_TESTO_PUNTEGGIO));
                stampa_sprite_personaggio(gioco, inizio_y, inizio_x + LARGHEZZA_PUNTEGGIO + i*LARGHEZZA_NUMERI, ALTEZZA_NUMERI, LARGHEZZA_NUMERI, sprite_sette);
                wattroff(gioco, COLOR_PAIR(COLORE_TESTO_PUNTEGGIO));
                break;

            case 8:
                wattron(gioco, COLOR_PAIR(COLORE_TESTO_PUNTEGGIO));
                stampa_sprite_personaggio(gioco, inizio_y, inizio_x + LARGHEZZA_PUNTEGGIO + i*LARGHEZZA_NUMERI, ALTEZZA_NUMERI, LARGHEZZA_NUMERI, sprite_otto);
                wattroff(gioco, COLOR_PAIR(COLORE_TESTO_PUNTEGGIO));
                break;

            case 9:
                wattron(gioco, COLOR_PAIR(COLORE_TESTO_PUNTEGGIO));
                stampa_sprite_personaggio(gioco, inizio_y, inizio_x + LARGHEZZA_PUNTEGGIO + i*LARGHEZZA_NUMERI, ALTEZZA_NUMERI, LARGHEZZA_NUMERI, sprite_nove);
                wattroff(gioco, COLOR_PAIR(COLORE_TESTO_PUNTEGGIO));
                break;
        }
    }
}

/**
 * stampa ogni oggetto nel gioco
 *
 * @param gioco finestra di gioco dove si stampa
 * @param num_max_piante numero massimo di piante in partita
 * @param piante_libere array di booleani che indicano se lo slot i è in gioco (false) o meno (true) per le piante
 * @param pianta array di pianta
 * @param num_corsie numero di corsie del laghetto
 * @param num_coccodrilli_max_corsia numero massimo di coccodrilli per corsia
 * @param coccodrilli matrice di coccodrilli che contiene tutti i coccodrilli per ogni corsia
 * @param coccodrilli_liberi matrice di booleani che indicano se lo slot i j è in gioco (false) o meno (true) per i coccodrilli
 * @param dir_coccodrilli array che indica la direzione di ogni corsia
 * @param rana character dell'utente
 * @param num_max_proiettili_rana numero massimo di proiettili che può sparare la rana
 * @param slot_liberi_proiettili_rana array di booleani che indicano se lo slot i è in gioco (false) o meno (true) per i proiettili della rana
 * @param proiettili_rana array di proiettili della rana
 * @param num_max_proiettili_piante numero massimo di proiettili che può sparare ogni pianta
 * @param proiettili_pianta matrice di proiettili di tutte le piante
 * @param slot_liberi_proiettili_pianta matrice di booleani che indicano se lo slot i j è in gioco (false) o meno (true) per i proiettili delle piante
 * @param num_tane numero di tane totali
 * @param tana array di tane
 * @param tana_aperta array di booleani che indicano se la porta i è aperta (true) o chiusa (false)
 * @param tempo_massimo tempo massimo per ogni manche
 * @param timer timer della manche
 * @param hp_max hp massimo che può avere la rana in una partita
 * @param hp_rana hp correnti della rana
 * @param punteggio punteggio corrente del giocatore
 * @param punteggio_precedente punteggio del ciclo controllo precedente
 */
void stampa_oggetti(WINDOW* gioco, int num_max_piante, bool piante_libere[num_max_piante], Character pianta[num_max_piante],
                    int num_corsie, int num_coccodrilli_max_corsia, Character coccodrilli[num_corsie][num_coccodrilli_max_corsia], bool coccodrilli_liberi[num_corsie][num_coccodrilli_max_corsia],
                    int dir_coccodrilli[num_corsie],
                    Character rana, int num_max_proiettili_rana, bool slot_liberi_proiettili_rana[num_max_proiettili_rana], Character proiettili_rana[num_max_proiettili_rana],
                    int num_max_proiettili_piante, Character proiettili_pianta[num_max_piante][num_max_proiettili_piante], bool slot_liberi_proiettili_pianta[num_max_piante][num_max_proiettili_piante],
                    int num_tane, Character tana[num_tane], bool tana_aperta[num_tane], int tempo_massimo, Character timer, int hp_max, int hp_rana, int punteggio, int punteggio_precedente)
{
    ///SPRITE OGGETTI DI GIOCO
    //sprite rana
    char rana_pazza[ALTEZZA_RANA][LARGHEZZA_RANA+1]={"/^\\",
                                        "|-|"};

    //sprite del coccodrillo che varia in base alla direzione della corsia
    char coccodrillo_pazzo_dx[ALTEZZA_COCCODRILLO][LARGHEZZA_COCCODRILLO+1]={"^^^-/''\\_",
                                                                             "------==-"};
    char coccodrillo_pazzo_sx[ALTEZZA_COCCODRILLO][LARGHEZZA_COCCODRILLO+1]={"_/''\\-^^^",
                                                                             "-==-------"};

    //sprite del coccodrillo che si sta immergendo che varia in base alla direzione della corsia
    char coccodrillo_pazzo_immersione_dx[ALTEZZA_COCCODRILLO-1][LARGHEZZA_COCCODRILLO+1]={"^^^-/''\\_"};
    char coccodrillo_pazzo_immersione_sx[ALTEZZA_COCCODRILLO-1][LARGHEZZA_COCCODRILLO+1]={ "_/''\\-^^^"};

    //sprite pianta
    char pianta_malvagia[ALTEZZA_PIANTA][LARGHEZZA_PIANTA+1]={"('')=",
                                                              "\\||/  "};

    //sprite proittile ovvero uno spazio che verrà colorato in base al personaggio che spara
    char proiettile_sprite[1][1+1]={" "};

    //sprite della tana
    char tana_pazza[ALTEZZA_TANA][LARGHEZZA_TANA+1]={"+-------+",
                                                     "|       |",
                                                     "|       |",
                                                     "|       |"};

    ///SPRITE DELLE STATS
    //sprite della vita rimossa
    char sprite_vite_morta[ALTEZZA_VITE][LARGHEZZA_VITE+1]=
            {
                    " ()~() ",
                    "(-___-)",
                    "==`-'=="
            }
    ;

    //sprite della vita corrente
    char sprite_vite_viva[ALTEZZA_VITE][LARGHEZZA_VITE+1]=
            {

                    "(l)-(l)",
                    "/_____\\",
                    "\\_____/",
            }
    ;
    //sprite per indicare quali proittili dell'utente sono stati sparati
    char sprite_proiettile[ALTEZZA_PROIETTILE][LARGHEZZA_PROIETTILE+1]=
            {
                    " __ ",
                    "|__)"
            }
    ;

    ///STAMPA MESSAGGIO TASTO USCITA
    mvwprintw(gioco, ALTEZZA_STATS-1, LARGHEZZA_SCHERMO- strlen("press 'q' to EXIT")-1, "press 'q' to EXIT");

    ///STAMPA PIANTE
    for (int i = 0; i < num_max_piante; ++i)
    {
        if(piante_libere[i]==false)
        {
            wattron(gioco, COLOR_PAIR(VERDE_PIANTA));
            stampa_sprite_personaggio(gioco, pianta[i].y, pianta[i].x-LARGHEZZA_PIANTA+1, ALTEZZA_PIANTA, LARGHEZZA_PIANTA,
                                      pianta_malvagia);
            wattroff(gioco, COLOR_PAIR(VERDE_PIANTA));
        }
    }

    ///STAMPA COCCODRILLI
    for (int i = 0; i < num_corsie; ++i)
    {
        for (int j = 0; j < num_coccodrilli_max_corsia; ++j)
        {
            //controllo se il coccodrillo è in gioco o visibile
            if(coccodrilli[i][j].x != UNDEFINED_X_COCCODRILLO && coccodrilli[i][j].y != UNDEFINED_X_COCCODRILLO && (coccodrilli[i][j].signal==EMERSO || coccodrilli[i][j].signal==PROMPT_IMMERSIONE) && coccodrilli_liberi[i][j]==false)
            {
                //colore in base allo status
                if(coccodrilli[i][j].status==BUONO)
                {
                    wattron(gioco, COLOR_PAIR(VERDE_COCCODRILLO_BUONO));
                }
                else if(coccodrilli[i][j].status==CATTIVO)
                {
                    wattron(gioco, COLOR_PAIR(ROSSO_COCCODRILLO_MALVAGIO));
                }

                //stampa sprite coccodrillo che si sta immergendo
                if(coccodrilli[i][j].signal==PROMPT_IMMERSIONE)
                {
                    if (dir_coccodrilli[i] == -1) {
                        stampa_sprite_personaggio(gioco, coccodrilli[i][j].y+1, coccodrilli[i][j].x,
                                                  ALTEZZA_COCCODRILLO-1, LARGHEZZA_COCCODRILLO, coccodrillo_pazzo_immersione_sx);
                    } else {
                        stampa_sprite_personaggio(gioco, coccodrilli[i][j].y+1, coccodrilli[i][j].x,
                                                  ALTEZZA_COCCODRILLO-1, LARGHEZZA_COCCODRILLO, coccodrillo_pazzo_immersione_dx);
                    }
                }
                //stampa sprite coccodrillo emerso
                else if(coccodrilli[i][j].signal==EMERSO)
                {
                    if (dir_coccodrilli[i] == -1) {
                        stampa_sprite_personaggio(gioco, coccodrilli[i][j].y, coccodrilli[i][j].x,
                                                  ALTEZZA_COCCODRILLO, LARGHEZZA_COCCODRILLO, coccodrillo_pazzo_sx);
                    } else {
                        stampa_sprite_personaggio(gioco, coccodrilli[i][j].y, coccodrilli[i][j].x,
                                                  ALTEZZA_COCCODRILLO, LARGHEZZA_COCCODRILLO, coccodrillo_pazzo_dx);
                    }
                }


                if(coccodrilli[i][j].status==BUONO)
                {
                    wattroff(gioco, COLOR_PAIR(VERDE_COCCODRILLO_BUONO));
                }
                else if(coccodrilli[i][j].status==CATTIVO)
                {
                    wattroff(gioco, COLOR_PAIR(ROSSO_COCCODRILLO_MALVAGIO));
                }
            }
        }
    }

    ///STAMPA RANA
    wattron(gioco, COLOR_PAIR(VERDE_RANA));
    stampa_sprite_personaggio(gioco, rana.y, rana.x-1, ALTEZZA_RANA, LARGHEZZA_RANA, rana_pazza);
    wattroff(gioco, COLOR_PAIR(VERDE_RANA));

    ///STAMPA PROIETTILI RANA
    for (int i = 0; i < num_max_proiettili_rana; ++i)
    {
        if(proiettili_rana[i].y!=0 && proiettili_rana[i].x!=0 && slot_liberi_proiettili_rana[i]==false)
        {
            wattron(gioco, COLOR_PAIR(GIALLO_PROIETTILE_RANA));
            stampa_sprite_personaggio(gioco, proiettili_rana[i].y, proiettili_rana[i].x, 1,
                                      1, proiettile_sprite);
            wattroff(gioco, COLOR_PAIR(GIALLO_PROIETTILE_RANA));
        }

    }

    ///STAMPA PROIETTILI PIANTE
    for (int i = 0; i < num_max_piante; ++i)
    {
        for (int j = 0; j < num_max_proiettili_piante; ++j)
        {
            if(slot_liberi_proiettili_pianta[i][j]==false)
            {
                wattron(gioco, COLOR_PAIR(ROSSO_PROIETTILE_PIANTA));
                stampa_sprite_personaggio(gioco, proiettili_pianta[i][j].y, proiettili_pianta[i][j].x, 1,
                                          1, proiettile_sprite);
                wattroff(gioco, COLOR_PAIR(ROSSO_PROIETTILE_PIANTA));
            }
        }
    }

    ///STAMPA TANE
    for (int i = 0; i < num_tane; ++i)
    {
        //stampa tana aperta
        if(tana_aperta[i]==true)
        {
            wattron(gioco, COLOR_PAIR(COLORE_TANA));
            stampa_sprite_personaggio(gioco, tana[i].y, tana[i].x, ALTEZZA_TANA, LARGHEZZA_TANA, tana_pazza);
            wattroff(gioco, COLOR_PAIR(COLORE_TANA));
            wattron(gioco, COLOR_PAIR(BG_BLACK_C_GREEN));

            //stampa interno della tana più scuro
            for (int j = 1; j < ALTEZZA_TANA; ++j)
            {
                for (int k = 1; k < LARGHEZZA_TANA-1; ++k)
                {
                    mvwaddch(gioco, tana[i].y+j, tana[i].x+k, ' ');
                }
            }
            wattroff(gioco, COLOR_PAIR(BG_BLACK_C_GREEN));

        }
        //stampa tana chiusa
        else if(tana_aperta[i]==false)
        {
            wattron(gioco, COLOR_PAIR(COLORE_TANA));
            stampa_sprite_personaggio(gioco, tana[i].y, tana[i].x, ALTEZZA_TANA, LARGHEZZA_TANA, tana_pazza);
            wattroff(gioco, COLOR_PAIR(COLORE_TANA));
        }
    }

    ///STAMPA TIMER
    if(timer.tempo_rimasto<=TEMPO_MASSIMO)
    {
        for (int i = 1; i < 3; ++i)
        {
            for (int j = 0; j < tempo_massimo; ++j)
            {
                if(j<timer.tempo_rimasto)
                {
                    //stampa per i primi 2/3 del timer colore unico
                    if(timer.tempo_rimasto>=TEMPO_MASSIMO/3)
                    {
                        wattron(gioco, COLOR_PAIR(VERDE_RANA));
                        mvwaddch(gioco, i, LARGHEZZA_SCHERMO-TEMPO_MASSIMO-3+j, ' ');
                        wattroff(gioco, COLOR_PAIR(VERDE_RANA));
                    }
                    else
                    {
                        //stampa per l'ultimo 1/3 del timer cono colore che cambia in base al valore del timer (se pari o dispari)
                        if(timer.tempo_rimasto%2 == 0)
                        {
                            wattron(gioco, COLOR_PAIR(VERDE_RANA));
                            mvwaddch(gioco, i, LARGHEZZA_SCHERMO-TEMPO_MASSIMO-3+j, ' ');
                            wattroff(gioco, COLOR_PAIR(VERDE_RANA));
                        }else
                        {
                            wattron(gioco, COLOR_PAIR(GIALLO_PROIETTILE_RANA));
                            mvwaddch(gioco, i, LARGHEZZA_SCHERMO-TEMPO_MASSIMO-3+j, ' ');
                            wattroff(gioco, COLOR_PAIR(GIALLO_PROIETTILE_RANA));
                        }

                    }
                }
                else
                {
                    wattron(gioco, COLOR_PAIR(ROSSO_TIMER));
                    mvwaddch(gioco, i, LARGHEZZA_SCHERMO-TEMPO_MASSIMO-3+j, ' ');
                    wattroff(gioco, COLOR_PAIR(ROSSO_TIMER));
                }
            }
        }
    }

    ///STAMPA VITE RIMASTE
    for (int i = 0; i < hp_max; ++i)
    {
        if(i < hp_rana)
        {
            wattron(gioco, COLOR_PAIR(BG_BLACK_C_GREEN));
            stampa_sprite_personaggio(gioco, 1, 2+(i*(LARGHEZZA_VITE+1)), ALTEZZA_VITE, LARGHEZZA_VITE, sprite_vite_viva);
            wattroff(gioco, COLOR_PAIR(BG_BLACK_C_GREEN));
        }
        else
        {
            wattron(gioco, COLOR_PAIR(BG_BLACK_C_RED));
            stampa_sprite_personaggio(gioco, 1, 2+(i*(LARGHEZZA_VITE+1)), ALTEZZA_VITE, LARGHEZZA_VITE, sprite_vite_morta);
            wattroff(gioco, COLOR_PAIR(BG_BLACK_C_RED));
        }
    }


    ///STAMPA PROIETTILI RANA RIMASTI
    for (int i = 0; i < num_max_proiettili_rana; ++i)
    {
        if(slot_liberi_proiettili_rana[i]==true)
        {
            wattron(gioco, COLOR_PAIR(BG_BLACK_C_GREEN));
            stampa_sprite_personaggio(gioco, 1+ALTEZZA_VITE+1, 2+(i*(LARGHEZZA_PROIETTILE+1)), ALTEZZA_PROIETTILE, LARGHEZZA_PROIETTILE, sprite_proiettile);
            wattroff(gioco, COLOR_PAIR(BG_BLACK_C_GREEN));
        }
        else
        {
            wattron(gioco, COLOR_PAIR(BG_BLACK_C_RED));
            stampa_sprite_personaggio(gioco, 1+ALTEZZA_VITE+1, 2+(i*(LARGHEZZA_PROIETTILE+1)), ALTEZZA_PROIETTILE, LARGHEZZA_PROIETTILE, sprite_proiettile);
            wattroff(gioco, COLOR_PAIR(BG_BLACK_C_RED));
        }
    }

    ///STAMPA PUNTEGGIO
    if(punteggio_precedente <= punteggio)
    {
        stampa_punteggio(gioco, punteggio, 3, LARGHEZZA_SCHERMO-LARGHEZZA_PUNTEGGIO-LARGHEZZA_NUMERI*3 - 20);
    }

}

/**
 * stampa di fine gioco in caso di vittoria con stampa del punteggio totalizzato
 *
 * @param gioco finestra di gioco dove si stampa
 * @param punteggio punteggio corrente del giocatore
 */
void schermata_vittoria(WINDOW* gioco, int punteggio)
{
    char sprite_rana_vittoria[ALTEZZA_RANA_VITTORIA][LARGHEZZA_RANA_VITTORIA+1];
    char sprite_testo_vittoria[ALTEZZA_TESTO_VITTORIA][LARGHEZZA_TESTO_VITTORIA+1];


    caricamento_sprite(FILE_TESTO_VITTORIA, ALTEZZA_TESTO_VITTORIA, LARGHEZZA_TESTO_VITTORIA, sprite_testo_vittoria);
    caricamento_sprite(FILE_RANA_VITTORIA, ALTEZZA_RANA_VITTORIA, LARGHEZZA_RANA_VITTORIA, sprite_rana_vittoria);

    stampa_sprite(gioco, ALTEZZA_TESTO_VITTORIA, LARGHEZZA_TESTO_VITTORIA, sprite_testo_vittoria, 2, ((LARGHEZZA_SCHERMO-LARGHEZZA_TESTO_VITTORIA)/2) );
    stampa_sprite(gioco, ALTEZZA_RANA_VITTORIA, LARGHEZZA_RANA_VITTORIA, sprite_rana_vittoria, ALTEZZA_SCHERMO/3, ((LARGHEZZA_SCHERMO-LARGHEZZA_RANA_VITTORIA)/10) );
    stampa_sprite(gioco, ALTEZZA_RANA_VITTORIA, LARGHEZZA_RANA_VITTORIA, sprite_rana_vittoria, ALTEZZA_SCHERMO/3, ((LARGHEZZA_SCHERMO-LARGHEZZA_RANA_VITTORIA*2)/10) * 9  + LARGHEZZA_RANA_VITTORIA);

    stampa_punteggio(gioco, punteggio, ALTEZZA_SCHERMO/5*2, (LARGHEZZA_SCHERMO-LARGHEZZA_PUNTEGGIO-LARGHEZZA_NUMERI*3)/2);

}

/**
 * stampa di fine gioco in caso di sconfitta con stampa del punteggio totalizzato
 *
 * @param gioco finestra di gioco dove si stampa
 * @param punteggio punteggio corrente del giocatore
 */
void schermata_sconfitta(WINDOW* gioco, int punteggio)
{
    char sprite_rana_sconfitta[ALTEZZA_RANA_SCONFITTA][LARGHEZZA_RANA_SCONFITTA+1];
    char sprite_testo_sconfitta[ALTEZZA_TESTO_SCONFITTA][LARGHEZZA_TESTO_SCONFITTA+1];


    caricamento_sprite(FILE_TESTO_SCONFITTA, ALTEZZA_TESTO_SCONFITTA, LARGHEZZA_TESTO_SCONFITTA, sprite_testo_sconfitta);
    caricamento_sprite(FILE_RANA_SCONFITTA, ALTEZZA_RANA_SCONFITTA, LARGHEZZA_RANA_SCONFITTA, sprite_rana_sconfitta);

    stampa_sprite(gioco, ALTEZZA_TESTO_SCONFITTA, LARGHEZZA_TESTO_SCONFITTA, sprite_testo_sconfitta, 2, ((LARGHEZZA_SCHERMO-LARGHEZZA_TESTO_SCONFITTA)/2) );
    stampa_sprite(gioco, ALTEZZA_RANA_SCONFITTA, LARGHEZZA_RANA_SCONFITTA, sprite_rana_sconfitta, ALTEZZA_SCHERMO/3, ((LARGHEZZA_SCHERMO-LARGHEZZA_RANA_SCONFITTA*2)/10) );
    stampa_sprite(gioco, ALTEZZA_RANA_SCONFITTA, LARGHEZZA_RANA_SCONFITTA, sprite_rana_sconfitta, ALTEZZA_SCHERMO/3, ((LARGHEZZA_SCHERMO-LARGHEZZA_RANA_SCONFITTA*2)/10) * 9 +LARGHEZZA_RANA_SCONFITTA);

    stampa_punteggio(gioco, punteggio, ALTEZZA_SCHERMO/5*2, (LARGHEZZA_SCHERMO-LARGHEZZA_PUNTEGGIO-LARGHEZZA_NUMERI*3)/2);

}

/**
 * stampa di fine gioco in caso di quit con stampa del punteggio totalizzato
 *
 * @param gioco finestra di gioco dove si stampa
 * @param punteggio punteggio corrente del giocatore
 */
void schermata_quit(WINDOW* gioco, int punteggio)
{
    char sprite_rana_quit[ALTEZZA_RANA_QUIT][LARGHEZZA_RANA_QUIT+1];
    char sprite_testo_quit[ALTEZZA_TESTO_QUIT][LARGHEZZA_TESTO_QUIT+1];

    caricamento_sprite(FILE_TESTO_QUIT, ALTEZZA_TESTO_QUIT, LARGHEZZA_TESTO_QUIT, sprite_testo_quit);
    caricamento_sprite(FILE_RANA_QUIT, ALTEZZA_RANA_QUIT, LARGHEZZA_RANA_QUIT, sprite_rana_quit);

    stampa_sprite(gioco, ALTEZZA_TESTO_QUIT, LARGHEZZA_TESTO_QUIT, sprite_testo_quit, 2, ((LARGHEZZA_SCHERMO-LARGHEZZA_TESTO_QUIT)/2) );
    stampa_sprite(gioco, ALTEZZA_RANA_QUIT, LARGHEZZA_RANA_QUIT, sprite_rana_quit, ALTEZZA_SCHERMO/3, ((LARGHEZZA_SCHERMO-LARGHEZZA_RANA_QUIT*2)/10) );
    stampa_sprite(gioco, ALTEZZA_RANA_QUIT, LARGHEZZA_RANA_QUIT, sprite_rana_quit, ALTEZZA_SCHERMO/3, ((LARGHEZZA_SCHERMO-LARGHEZZA_RANA_QUIT*2)/10) * 9 +LARGHEZZA_RANA_QUIT);

    stampa_punteggio(gioco, punteggio, ALTEZZA_SCHERMO/5*2, (LARGHEZZA_SCHERMO-LARGHEZZA_PUNTEGGIO-LARGHEZZA_NUMERI*3)/2);

}