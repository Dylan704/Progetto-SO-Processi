//
// Created by dylan on 22/12/23.
//

#include "Menu.h"
#include "Struct_enum.h"

/**
 * Funzione che carica gli sprite all'interno di una stringa
 *
 * @param nome_file
 * @param rows numero righe stringa
 * @param cols numero colonne stringa
 * @param sprite stringa
 */
void caricamento_sprite(char nome_file[DIM_NOME_FILE], int rows, int cols, char sprite[rows][cols+1])
{
    //pulizia stringa
    pulisci_sprite(rows, cols, sprite);

    //apertura file
    FILE *file = fopen(nome_file, "r");
    if (file == NULL)
    {
        perror("Errore nell'apertura del file titolo");
        endwin();
        exit(ERRORE_APERTURA_FILE);
    }

    //lettura caratteri del file
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            fscanf(file, "%c", &sprite[i][j]);

            if (sprite[i][j] == '\n')
            {
                sprite[i][j] = '\0';
                break;
            }
        }
    }

    // Chiusura il file
    fclose(file);
}

/**
 * Funzione di stampa dello sprite letto
 *
 * @param gioco finestra di gioco dove si stampa
 * @param rows numero righe sprite
 * @param cols numero colonne sprite
 * @param sprite sprite da stampare
 * @param inizio_y coordinata di partenza della stampa
 * @param inizio_x coordinata di partenza della stampa
 */
void stampa_sprite(WINDOW* gioco, int rows, int cols, char sprite[rows][cols+1], int inizio_y, int inizio_x)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (sprite[i][j] != '\0')
            {
                mvwaddch(gioco, inizio_y + i, inizio_x + j, sprite[i][j]);
            }
        }
    }
}

/**
 * Funzione che sovrascrive con spazi vuoti
 *
 * @param rows numero righe sprite
 * @param cols numero colonne sprite
 * @param sprite sprite da stampare
 */
void pulisci_sprite(int rows, int cols, char sprite[rows][cols+1])
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            sprite[i][j]=' ';
        }
    }
}

/**
 * Funzione di creazione interfaccia menu di gioco
 *
 * @param gioco finestra di gioco dove si stampa
 * @param rows numero righe sprite
 * @param cols numero colonne sprite
 * @param sprite sprite da stampare
 * @param scelta variabile ausiliare che stabilisce che tasto viene cliccato
 * @return
 */
WINDOW* inizializzazione_menu(WINDOW* gioco, int rows, int cols, char sprite [rows][cols+1], int* scelta)
{
    char sprite_peashooter[ALTEZZA_PEASHOOTER][LARGHEZZA_PEASHOOTER+1];
    char sprite_rana_menu[ALTEZZA_RANA_MENU][LARGHEZZA_RANA_MENU+1];

    //errore in caso l'utente abbia il terminale troppo piccolo per visualizzare la schermata di gioco
    if (LINES < ALTEZZA_SCHERMO)
    {
        perror("Terminale non a schermo intero\n");
        endwin();
        exit(ERRORE_DIMENSIONE_FINESTRA);
    }

    //inizializzazione nuova finestra
    gioco = newwin(ALTEZZA_SCHERMO, LARGHEZZA_SCHERMO, ((LINES-1)-ALTEZZA_SCHERMO)/2, ((COLS-1)-LARGHEZZA_SCHERMO)/2);
    if (gioco == NULL)      //errore inizializzazione
    {
        perror("Error creating window");
        endwin();
        exit(ERRORE_CREAZIONE_FINESTRA);
    }

    //delimitazione box di gioco
    box(gioco, ACS_VLINE, ACS_HLINE);

    //colorazione sfondo box gioco
    wbkgd(gioco, COLOR_PAIR(BG_BLACK_C_GREEN));

    //stampa grafiche menu
    caricamento_sprite(FILE_PEASHOOTER, ALTEZZA_PEASHOOTER, LARGHEZZA_PEASHOOTER, sprite_peashooter);
    stampa_sprite(gioco, ALTEZZA_PEASHOOTER, LARGHEZZA_PEASHOOTER, sprite_peashooter, ALTEZZA_SCHERMO/5, (LARGHEZZA_SCHERMO-2*LARGHEZZA_PEASHOOTER-COLS_TITOLO)/2);
    caricamento_sprite(FILE_RANA_MENU, ALTEZZA_RANA_MENU, LARGHEZZA_RANA_MENU, sprite_rana_menu);
    stampa_sprite(gioco, ALTEZZA_RANA_MENU, LARGHEZZA_RANA_MENU, sprite_rana_menu, ALTEZZA_SCHERMO/5, (LARGHEZZA_SCHERMO-2*LARGHEZZA_PEASHOOTER-COLS_TITOLO)/2 + LARGHEZZA_PEASHOOTER + COLS_TITOLO+6);

    //stampa titolo menu
    stampa_sprite(gioco, rows, cols, sprite, SCOSTAMENTO_V_TITOLO, (LARGHEZZA_SCHERMO-COLS_TITOLO)/2 + 1);

    creazione_tasti(gioco, scelta,  ALTEZZA_SCHERMO/2+1, (ALTEZZA_SCHERMO/2) + ALTEZZA_TASTO + 5, strlen(TESTO_GIOCA), strlen(TESTO_HELP),TESTO_GIOCA, TESTO_HELP);

    return gioco;
}

/**
 * Funzione che crea due tasti selezionabili verticalmente nello schermo,
 * la grafica e' interattiva e colora e ingrandisce il tasto selezionato
 *
 * @param gioco finestra di gioco
 * @param scelta variabile aux che indica il tasto cliccato
 * @param posizione_y_tasto1 posizione verticale tasto1
 * @param posizione_y_tasto2 posizione verticale tasto2
 * @param lung_testo1 lunghezza stringa tasto1
 * @param lung_testo2 lunghezza stringa tasto2
 * @param testo1 stringa tasto1
 * @param testo2 stringa tasto2
 */
void creazione_tasti(WINDOW* gioco, int*scelta, int posizione_y_tasto1, int posizione_y_tasto2, int lung_testo1, int lung_testo2, char testo1[], char testo2[])
{
    //creazione sottofinestre tasti
    WINDOW *tasto_up, *tasto_down;

    //inizializzazione finestre derivate tasti
    //derwin fa una subwin ma usa come coordinate quelle relative alla finestra madre
    tasto_up = derwin(gioco, ALTEZZA_TASTO, LARGHEZZA_TASTO, posizione_y_tasto1, (LARGHEZZA_SCHERMO-LARGHEZZA_TASTO)/2);
    //errore creazione derwin
    if (tasto_up == NULL) {
        perror("Error creating window tasto_up");
        endwin();
        exit(ERRORE_CREAZIONE_FINESTRA);
    }
    box(tasto_up, ACS_VLINE, ACS_HLINE);

    tasto_down = derwin(gioco, ALTEZZA_TASTO, LARGHEZZA_TASTO, posizione_y_tasto2, (LARGHEZZA_SCHERMO-LARGHEZZA_TASTO)/2);
    //errore creazione derwin
    if (tasto_down == NULL) {
        perror("Error creating window tasto_down");
        endwin();
        exit(ERRORE_CREAZIONE_FINESTRA);
    }
    box(tasto_down, ACS_VLINE, ACS_HLINE);

    wbkgd(tasto_up, COLOR_PAIR(BG_BLACK_C_GREEN));
    wbkgd(tasto_down, COLOR_PAIR(BG_BLACK_C_GREEN));

    //stampa stringhe
    mvwprintw(tasto_up, (ALTEZZA_TASTO)/2, (LARGHEZZA_TASTO-lung_testo1)/2, testo1);
    mvwprintw(tasto_down, (ALTEZZA_TASTO)/2, (LARGHEZZA_TASTO-lung_testo2)/2, testo2);

    wrefresh(gioco);


    selezione_tasto(gioco, tasto_up, tasto_down, scelta, strlen(testo1), strlen(testo2), testo1, testo2);

}

/**
 * Funzione che permette la selezione e il cambiamento interattivo della grafica del tasto tramite wresize e
 * cambiamenti di colore dello sfondo dei tasti
 *
 * @param gioco finestra di gioco
 * @param tasto_up tasto superiore
 * @param tasto_down tasto inferiore
 * @param scelta variabile aux che indica la scelta fatta
 * @param lung_testo1 lunghezza stringa tasto superiore
 * @param lung_testo2 lunghezza stringa tasto inferiore
 * @param testo1 stringa superiore
 * @param testo2 stringa inferiore
 */
void selezione_tasto(WINDOW* gioco, WINDOW *tasto_up, WINDOW* tasto_down, int* scelta, int lung_testo1, int lung_testo2, char testo1[], char testo2[])
{
    //disattivazione delay input
    nodelay(stdscr, 1);

    //variabile di input
    int c;
    c=NO_CHOICE_INPUT;

    while(true)
    {
        c=getch();

        switch(c)
        {
            //selezione tasto superiore
            case 'w':

                //ridimensiono a dimensione ingrandita
                wresize(tasto_up, ALTEZZA_TASTO+2, LARGHEZZA_TASTO);
                wresize(tasto_down, ALTEZZA_TASTO+2, LARGHEZZA_TASTO);

                //pulisco le sottofinestre
                wclear(tasto_up);
                wclear(tasto_down);

                //coloro tasto NON selezionato
                wbkgd(tasto_down, COLOR_PAIR(BG_BLACK_C_GREEN));

                wrefresh(tasto_up);
                wrefresh(tasto_down);

                //reingrandisco solo il tasto piu grande
                wresize(tasto_up, ALTEZZA_TASTO+2, LARGHEZZA_TASTO);
                wresize(tasto_down, ALTEZZA_TASTO, LARGHEZZA_TASTO);

                //colorazione diversa per i due tasti
                wbkgd(tasto_down, COLOR_PAIR(BG_BLACK_C_GREEN));
                wbkgd(tasto_up, COLOR_PAIR(BG_GREEN_C_PURPLE));

                //creazione contorno
                box(tasto_up, ACS_VLINE, ACS_HLINE);
                box(tasto_down, ACS_VLINE, ACS_HLINE);

                //stampa testo
                mvwprintw(tasto_up, (ALTEZZA_TASTO)/2+1, (LARGHEZZA_TASTO-lung_testo1)/2, testo1);
                mvwprintw(tasto_down, (ALTEZZA_TASTO)/2, (LARGHEZZA_TASTO-lung_testo2)/2, testo2);

                //aggiornamento scelta
                (*scelta)=UP;
                break;

                //scelta tasto inferiore, uguale a quella superiore ma ovviamente invertita
            case 's':
                wresize(tasto_up, ALTEZZA_TASTO+2, LARGHEZZA_TASTO);
                wresize(tasto_down, ALTEZZA_TASTO+2, LARGHEZZA_TASTO);

                wclear(tasto_up);
                wclear(tasto_down);

                wbkgd(tasto_up, COLOR_PAIR(BG_BLACK_C_GREEN));

                wrefresh(tasto_up);
                wrefresh(tasto_down);

                wresize(tasto_up, ALTEZZA_TASTO, LARGHEZZA_TASTO);
                wresize(tasto_down, ALTEZZA_TASTO+2, LARGHEZZA_TASTO);

                wbkgd(tasto_up, COLOR_PAIR(BG_BLACK_C_GREEN));
                wbkgd(tasto_down, COLOR_PAIR(BG_GREEN_C_PURPLE));

                box(tasto_up, ACS_VLINE, ACS_HLINE);
                box(tasto_down, ACS_VLINE, ACS_HLINE);

                mvwprintw(tasto_up, (ALTEZZA_TASTO)/2, (LARGHEZZA_TASTO-lung_testo1)/2, testo1);
                mvwprintw(tasto_down, (ALTEZZA_TASTO)/2+1, (LARGHEZZA_TASTO-lung_testo2)/2, testo2);

                (*scelta)=DOWN;
                break;
            case 'i':
                //scelta per tornare alla schermata precedente
                (*scelta)=BACK;
                break;
            default:
                break;
        }

        wrefresh(tasto_up);
        wrefresh(tasto_down);

        //selezione di un tasto con SPAZIO oppure selezione 'i' per tornare alla schermata precedente
        if((c==' ' || c=='i') && (*scelta)!=NOCHOICE)
        {
            //cancellazione tasti
            delwin(tasto_up);
            delwin(tasto_down);

            wclear(gioco);
            box(gioco, ACS_VLINE, ACS_HLINE);
            wbkgd(gioco, COLOR_PAIR(BG_BLACK_C_GREEN));

            break;
        }
    }
}

/**
 * Funzione che permette la visualizzazione di una guida di gioco animata,
 * con conseguente gestione di processi in base alla pagina visualizzata
 *
 * @param gioco finestra di gioco
 */
void bestiario(WINDOW* gioco)
{
    //dichiarazione finestra text e tasti
    WINDOW *text;
    WINDOW *tasto_sinistra, *tasto_centro, *tasto_destra;

    //creazione finestra text
    text = derwin(gioco, ALTEZZA_TEXT, LARGHEZZA_TEXT, (ALTEZZA_SCHERMO-ALTEZZA_TEXT)/2-4, (LARGHEZZA_SCHERMO-LARGHEZZA_TEXT)/2);
    box(text, ACS_VLINE, ACS_HLINE);
    if (text == NULL)
    {
        perror("Errore creazione finestra");
        endwin();
        exit(ERRORE_CREAZIONE_FINESTRA);
    }

    //dichiarazione stringhe tasti
    char testo_sinistra[]={"RANA"}, testo_centro[]={"COCCODRILLO"}, testo_destra[]={"PIANTA"};

    //derwin fa una subwin ma usa come coordinate quelle relative alla finestra madre
    tasto_sinistra = derwin(gioco, ALTEZZA_TASTO, LARGHEZZA_TASTO, ALTEZZA_SCHERMO/6 *5-1, (LARGHEZZA_SCHERMO-3*LARGHEZZA_TASTO)/4);
    //errore creazione derwin
    if (tasto_sinistra == NULL) {
        perror("Error creating window tasto_sinistra");
        endwin();
        exit(ERRORE_CREAZIONE_FINESTRA);
    }
    box(tasto_sinistra, ACS_VLINE, ACS_HLINE);

    tasto_centro = derwin(gioco, ALTEZZA_TASTO, LARGHEZZA_TASTO, ALTEZZA_SCHERMO/6 *5-1, (LARGHEZZA_SCHERMO-3*LARGHEZZA_TASTO)/2 + LARGHEZZA_TASTO );
    //errore creazione derwin
    if (tasto_centro == NULL) {
        perror("Error creating window tasto_centro");
        endwin();
        exit(ERRORE_CREAZIONE_FINESTRA);
    }
    box(tasto_centro, ACS_VLINE, ACS_HLINE);

    tasto_destra = derwin(gioco, ALTEZZA_TASTO, LARGHEZZA_TASTO, ALTEZZA_SCHERMO/6 *5-1, (LARGHEZZA_SCHERMO-3*LARGHEZZA_TASTO)/4 * 3 + LARGHEZZA_TASTO * 2);
    //errore creazione derwin
    if (tasto_destra == NULL) {
        perror("Error creating window tasto_destra");
        endwin();
        exit(ERRORE_CREAZIONE_FINESTRA);
    }
    box(tasto_destra, ACS_VLINE, ACS_HLINE);

    //colorazione base tasti
    wbkgd(tasto_sinistra, COLOR_PAIR(BG_BLACK_C_GREEN));
    wbkgd(tasto_centro, COLOR_PAIR(BG_BLACK_C_GREEN));
    wbkgd(tasto_destra, COLOR_PAIR(BG_BLACK_C_GREEN));

    //stampa stringhe
    mvwprintw(tasto_sinistra, (ALTEZZA_TASTO)/2, (LARGHEZZA_TASTO-strlen(testo_sinistra))/2, testo_sinistra);
    mvwprintw(tasto_centro, (ALTEZZA_TASTO)/2, (LARGHEZZA_TASTO-strlen(testo_centro))/2, testo_centro);
    mvwprintw(tasto_destra, (ALTEZZA_TASTO)/2, (LARGHEZZA_TASTO-strlen(testo_destra))/2, testo_destra);

    mvwprintw(gioco, 1, LARGHEZZA_SCHERMO-strlen("PREMERE i PER TORNARE ALLA SCHERMATA PRECEDENTE")-2, "PREMERE i PER TORNARE ALLA SCHERMATA PRECEDENTE");

    wrefresh(gioco);

    selezione_tasti_bestiario( gioco, text, tasto_sinistra,  tasto_centro, tasto_destra, testo_sinistra,  testo_centro,  testo_destra);
}

/**
 * Funzione che ricolora e evidenzia il tasto selezionato nella schermata bestiario
 *
 * puntatori a finestra dei tasti
 * @param tasto_selezionato
 * @param tasto1
 * @param tasto2
 *
 * stringhe tasti
 * @param testo_t_selezionato
 * @param testo1
 * @param testo2
 */
void grafica_selezione_tasto(WINDOW *tasto_selezionato, WINDOW* tasto1, WINDOW* tasto2, char testo_t_selezionato[], char testo1[], char testo2[])
{
    wclear(tasto_selezionato);
    wclear(tasto1);
    wclear(tasto2);

    //resetto colore tasti non selezionati
    wbkgd(tasto_selezionato, COLOR_PAIR(BG_GREEN_C_PURPLE));
    wbkgd(tasto1, COLOR_PAIR(BG_BLACK_C_GREEN));
    wbkgd(tasto2, COLOR_PAIR(BG_BLACK_C_GREEN));

    box(tasto_selezionato, ACS_VLINE, ACS_HLINE);
    box(tasto1, ACS_VLINE, ACS_HLINE);
    box(tasto2, ACS_VLINE, ACS_HLINE);

    mvwprintw(tasto_selezionato, (ALTEZZA_TASTO)/2, (LARGHEZZA_TASTO - strlen(testo_t_selezionato))/2, testo_t_selezionato);
    mvwprintw(tasto1, (ALTEZZA_TASTO)/2, (LARGHEZZA_TASTO - strlen(testo1))/2, testo1);
    mvwprintw(tasto2, (ALTEZZA_TASTO)/2, (LARGHEZZA_TASTO - strlen(testo2))/2, testo2);

}

/**
 * Funzione specifica per l'interfaccia del bestiario che crea e gestisce la grafica e i processi delle varie
 * pagine, utilizzando fork oppure thread a seconda della versione.
 * Ogni volta che si visualizza una delle 3 pagine si creano i processi/thread concorrenti e quando si cambia pagina
 * vengono terminati per rigenerare i nuovi relativi alla nuova pagina
 *
 * @param gioco finestra di gioco
 * @param text pagina del bestiario contenente descrizione e animazioni
 * //tre tasti selezione
 * @param tasto_sx
 * @param tasto_cntr
 * @param tasto_dx
 * //stringhe da stampare nei 3 tasti
 * @param testo_sx
 * @param testo_cntr
 * @param testo_dx
 */
void selezione_tasti_bestiario(WINDOW* gioco, WINDOW* text, WINDOW *tasto_sx, WINDOW* tasto_cntr, WINDOW *tasto_dx, char testo_sx[], char testo_cntr[], char testo_dx[])
{

    //sprite di gioco utilizzati nelle animazioni
    char coccodrillo_pazzo_dx[ALTEZZA_COCCODRILLO][LARGHEZZA_COCCODRILLO+1]={"^^^-/''\\_",
                                                                             "------==-"};
    char coccodrillo_pazzo_immersione_dx[ALTEZZA_COCCODRILLO-1][LARGHEZZA_COCCODRILLO+1]={"^^^-/''\\_"};
    char rana_pazza[ALTEZZA_RANA][3+1]={"/^\\",
                                        "|-|"};
    char pianta_malvagia[ALTEZZA_PIANTA][LARGHEZZA_PIANTA+1]={"('')=",
                                                              "\\||/  "};
    char proiettile_sprite[1][1]={" "};
    char tana_pazza[ALTEZZA_TANA][LARGHEZZA_TANA+1]={"+-------+",
                                                     "|       |",
                                                     "|       |",
                                                     "|       |"};

    //finestre dove si visualizzano gli sprite
    WINDOW  *animazione_rana=NULL, *animazione_coccodrilli=NULL, *animazione_piante=NULL;

    char testo_guida_rana[ALTEZZA_GUIDA_RANA][LARGHEZZA_GUIDA_RANA+1];
    char testo_guida_coccodrilli[ALTEZZA_GUIDA_COCCODRILLO][LARGHEZZA_GUIDA_COCCODRILLO+1];
    char testo_guida_piante[ALTEZZA_GUIDA_PIANTA][LARGHEZZA_GUIDA_RANA+1];

    int tasto_precedente=-1;
    int tasto_corrente=COCCODRILLO;

    //struttura che conterra' i dati letti dalla pipe
    Character_guida aux;
    aux.ID=-1;
    aux.y=NOCHOICE;
    aux.x=NOCHOICE;
    aux.c=NO_CHOICE_INPUT;

    //pid processi utilizzati
    pid_t pid_input;
    pid_t pid_coccodrillo;
    pid_t pid_rana;
    pid_t pid_proiettile_pianta;

    int posizione_coccodrilli_animazione_rana[2];
    for (int i = 0; i < 2; ++i)
    {
        posizione_coccodrilli_animazione_rana[i]=(LARGHEZZA_ANIMAZIONE_RANA-LARGHEZZA_COCCODRILLO)/2 + (rand()%5)-2;
    }

    //creazione processo input
    int pipefd[2];
    if(pipe(pipefd)==-1)
    {
        perror("Errore creazione pipe\n");
        endwin();
        exit(ERRORE_CREAZIONE_PIPE);
    }

    pid_input=fork();
    switch(pid_input)
    {
        case -1: 	//errore
            perror("Errore fork input\n");
            exit(ERRORE_FORK_INPUT_BESTIARIO);
        case 0:		//figlio rana
            close(pipefd[0]);
            input(pipefd[1]);
            break;
        default:	//padre controllo
        break;
    }


    //ciclo di lettura
    do
    {
        //lettura pipe
        read(pipefd[0], &aux, sizeof(Character_guida));

        if(aux.c != NO_CHOICE_INPUT)
        {
            tasto_precedente=tasto_corrente;
        }

        //se leggo un valore di spostamento in input da tastiera cambio pagina
        if(aux.ID==INPUT)
        {
            switch (aux.c)
            {
                case 'a':
                    if(tasto_corrente==COCCODRILLO)
                    {
                        tasto_corrente=RANA;
                    }
                    else if(tasto_corrente==PIANTA)
                    {
                        tasto_corrente=COCCODRILLO;
                    }
                    break;
                case 'd':
                    if(tasto_corrente==RANA)
                    {
                        tasto_corrente=COCCODRILLO;
                    }
                    else if(tasto_corrente==COCCODRILLO)
                    {
                        tasto_corrente=PIANTA;
                    }
                    break;
                default:
                    break;
            }
        }

        //in base alla pagina visualizzata creo le sottofinestre e stampo le grafiche opportune, creando quindi anche i processi corretti
        switch (tasto_corrente)
        {
            ///TASTO AL CENTRO
            case COCCODRILLO:
                wclear(text);

                if(animazione_coccodrilli==NULL)
                {
                    animazione_coccodrilli = derwin(text, ALTEZZA_ANIMAZIONE_COCCODRILLI , LARGHEZZA_ANIMAZIONE_COCCODRILLI, ALTEZZA_GUIDA_COCCODRILLO + 3, (LARGHEZZA_TEXT-LARGHEZZA_ANIMAZIONE_COCCODRILLI)/2);
                    if (animazione_coccodrilli == NULL)
                    {
                        perror("Errore creazione finestra");
                        endwin();
                        exit(ERRORE_CREAZIONE_FINESTRA);
                    }

                    box(animazione_coccodrilli, ACS_VLINE, ACS_HLINE);

                    pid_coccodrillo=fork();
                    switch (pid_coccodrillo)
                    {
                        case -1:
                            perror("Errore fork coccodrillo");
                            exit(ERRORE_FORK_COCCODRILLI);
                        case 0:
                            close(pipefd[0]);
                            pos_coccodrilli_guida(pipefd[1]);
                            break;
                        default:
                            break;
                    }
                }

                if(animazione_coccodrilli!=NULL)
                {
                    box(animazione_coccodrilli, ACS_VLINE, ACS_HLINE);

                    //stampa sfondo
                    wattron(animazione_coccodrilli, COLOR_PAIR(BG_LAGHETTO));
                    for (int i = 1; i < ALTEZZA_ANIMAZIONE_COCCODRILLI-1; ++i)
                    {
                        for (int j = 1; j < LARGHEZZA_ANIMAZIONE_COCCODRILLI-1; ++j)
                        {
                            mvwaddch(animazione_coccodrilli, i, j, ' ');
                        }
                    }
                    wattroff(animazione_coccodrilli, COLOR_PAIR(BG_LAGHETTO));

                    //lettura valori coccodrillo dalla pipe
                    if(aux.ID==COCCODRILLO_GUIDA)
                    {
                        if(aux.status == BUONO)
                        {
                            wattron(animazione_coccodrilli, COLOR_PAIR(VERDE_COCCODRILLO_BUONO));
                        }
                        else
                        {
                            wattron(animazione_coccodrilli, COLOR_PAIR(ROSSO_COCCODRILLO_MALVAGIO));
                        }

                        //se il coccodrillo e' cattivo visualizziamo le varie fasi di immersione
                        if(aux.status==CATTIVO)
                        {
                            if(aux.x <= (LARGHEZZA_ANIMAZIONE_COCCODRILLI-2)/4)
                            {
                                stampa_sprite(animazione_coccodrilli, ALTEZZA_COCCODRILLO, LARGHEZZA_COCCODRILLO, coccodrillo_pazzo_dx, aux.y, aux.x);
                            }
                            else if(aux.x <= (LARGHEZZA_ANIMAZIONE_COCCODRILLI-2)/4 * 2)
                            {
                                stampa_sprite(animazione_coccodrilli, 1, LARGHEZZA_COCCODRILLO, coccodrillo_pazzo_immersione_dx, aux.y+1, aux.x);
                            }
                            else if(aux.x <= (LARGHEZZA_ANIMAZIONE_COCCODRILLI-2)/4 * 3)
                            {
                                ;
                            }
                            else
                            {
                                stampa_sprite(animazione_coccodrilli, ALTEZZA_COCCODRILLO, LARGHEZZA_COCCODRILLO, coccodrillo_pazzo_dx, aux.y, aux.x);
                            }
                        }
                        else
                        {
                            stampa_sprite(animazione_coccodrilli, ALTEZZA_COCCODRILLO, LARGHEZZA_COCCODRILLO, coccodrillo_pazzo_dx, aux.y, aux.x);
                        }

                        if(aux.status == BUONO)
                        {
                            wattroff(animazione_coccodrilli, COLOR_PAIR(VERDE_COCCODRILLO_BUONO));
                        }
                        else
                        {
                            wattroff(animazione_coccodrilli, COLOR_PAIR(ROSSO_COCCODRILLO_MALVAGIO));
                        }

                        wrefresh(animazione_coccodrilli);
                    }
                }

                //stampa grafiche
                grafica_selezione_tasto(tasto_cntr, tasto_sx, tasto_dx, testo_cntr, testo_sx, testo_dx);
                caricamento_sprite(FILE_TEXT_COCCODRILLI, ALTEZZA_GUIDA_COCCODRILLO, LARGHEZZA_GUIDA_COCCODRILLO, testo_guida_coccodrilli);
                stampa_sprite(text, ALTEZZA_GUIDA_COCCODRILLO, LARGHEZZA_GUIDA_COCCODRILLO, testo_guida_coccodrilli, 1, (LARGHEZZA_TEXT-LARGHEZZA_GUIDA_COCCODRILLO)/2);

                break;


                ///TASTO A SINISTRA
            case RANA:
                wclear(text);

                if(animazione_rana==NULL)
                {
                    animazione_rana = derwin(text, ALTEZZA_ANIMAZIONE_RANA , LARGHEZZA_ANIMAZIONE_RANA, 2, 7);
                    if (animazione_rana == NULL)
                    {
                        perror("Errore creazione finestra");
                        endwin();
                        exit(ERRORE_CREAZIONE_FINESTRA);
                    }
                    box(animazione_rana, ACS_VLINE, ACS_HLINE);

                    pid_rana=fork();
                    switch (pid_rana)
                    {
                        case -1:
                            perror("Errore fork rana");
                            exit(ERRORE_FORK_RANA);
                        case 0:
                            close(pipefd[0]);
                            pos_rana_guida(pipefd[1]);
                            break;
                        default:
                            break;
                    }
                }

                if(animazione_rana!=NULL)
                {
                    box(animazione_rana, ACS_VLINE, ACS_HLINE);

                    //stampa grafiche sottofinestra pagina
                    for (int i = 1; i < ALTEZZA_ANIMAZIONE_RANA-1; ++i)
                    {
                        if(i<ALTEZZA_TANA+2)
                        {
                            wattron(animazione_rana, COLOR_PAIR(BG_MARCIAPIEDE_RANA_TANE));

                        }else if(i<ALTEZZA_TANA+2+ALTEZZA_COCCODRILLO*2)
                        {
                            wattron(animazione_rana, COLOR_PAIR(BG_LAGHETTO));
                        }else
                        {
                            wattron(animazione_rana, COLOR_PAIR(BG_MARCIAPIEDE_RANA_TANE));
                        }

                        //stampa carattere con sfondo scelto in base alla posizione
                        for (int j = 1; j < LARGHEZZA_ANIMAZIONE_RANA-1; ++j)
                        {
                            mvwaddch(animazione_rana, i,j, ' ');
                        }

                        if(i<ALTEZZA_TANA+2)
                        {
                            wattroff(animazione_rana, COLOR_PAIR(BG_MARCIAPIEDE_RANA_TANE));
                        }else if(i<ALTEZZA_TANA+2+ALTEZZA_COCCODRILLO*2)
                        {
                            wattroff(animazione_rana, COLOR_PAIR(BG_LAGHETTO));
                        }else
                        {
                            wattroff(animazione_rana, COLOR_PAIR(BG_MARCIAPIEDE_RANA_TANE));
                        }
                    }
                    for (int i = 0; i < 2; ++i)
                    {
                        wattron(animazione_rana, COLOR_PAIR(VERDE_COCCODRILLO_BUONO));
                        stampa_sprite(animazione_rana, ALTEZZA_COCCODRILLO, LARGHEZZA_COCCODRILLO, coccodrillo_pazzo_dx, ALTEZZA_TANA+2 + i*2, posizione_coccodrilli_animazione_rana[i]);
                        wattroff(animazione_rana, COLOR_PAIR(VERDE_COCCODRILLO_BUONO));
                    }

                    wattron(animazione_rana, COLOR_PAIR(COLORE_TANA));
                    stampa_sprite(animazione_rana, ALTEZZA_TANA, LARGHEZZA_TANA, tana_pazza, 1, (LARGHEZZA_ANIMAZIONE_RANA-LARGHEZZA_TANA)/2);
                    wattroff(animazione_rana, COLOR_PAIR(COLORE_TANA));

                    wattron(gioco, COLOR_PAIR(BG_BLACK_C_GREEN));
                    for (int j = 1; j < ALTEZZA_TANA; ++j)
                    {
                        for (int k = 1; k < LARGHEZZA_TANA-1; ++k)
                        {
                            mvwaddch(animazione_rana, 1+j, 3+k, ' ');
                        }
                    }
                    wattroff(gioco, COLOR_PAIR(BG_BLACK_C_GREEN));

                    //lettura e stampa nuova posizione della rana
                    if(aux.ID==RANA_GUIDA)
                    {
                        wattron(animazione_rana, COLOR_PAIR(VERDE_RANA));
                        stampa_sprite(animazione_rana, ALTEZZA_RANA, LARGHEZZA_RANA, rana_pazza, aux.y, aux.x);
                        wattroff(animazione_rana, COLOR_PAIR(VERDE_RANA));
                        wrefresh(animazione_rana);

                    }

                }

                //stampa testo pagina
                grafica_selezione_tasto(tasto_sx, tasto_cntr, tasto_dx, testo_sx, testo_cntr, testo_dx);
                caricamento_sprite(FILE_TEXT_RANA, ALTEZZA_GUIDA_RANA, LARGHEZZA_GUIDA_RANA, testo_guida_rana);
                stampa_sprite(text, ALTEZZA_GUIDA_RANA, LARGHEZZA_GUIDA_RANA, testo_guida_rana, 2, LARGHEZZA_TEXT/2-5);

                break;

            ///TASTO A DESTRA

            case PIANTA:
                wclear(text);
                if(animazione_piante==NULL)
                {
                    animazione_piante = derwin(text, ALTEZZA_ANIMAZIONE_PIANTE , LARGHEZZA_ANIMAZIONE_PIANTE, (ALTEZZA_TEXT-ALTEZZA_ANIMAZIONE_PIANTE)/2, LARGHEZZA_TEXT-LARGHEZZA_GUIDA_PIANTA + 8);
                    if (animazione_piante == NULL)
                    {
                        perror("Errore creazione finestra");
                        endwin();
                        exit(ERRORE_CREAZIONE_FINESTRA);
                    }
                    box(animazione_piante, ACS_VLINE, ACS_HLINE);

                    pid_proiettile_pianta=fork();
                    switch (pid_proiettile_pianta)
                    {
                        case -1:
                            perror("Errore fork proiettile pianta");
                            exit(ERRORE_FORK_PROIETTILI_PIANTA);
                        case 0:
                            close(pipefd[0]);
                            pos_proiettile_pianta_guida(pipefd[1]);
                            break;
                        default:
                            break;
                    }
                }

                if(animazione_piante!=NULL)
                {
                    box(animazione_piante, ACS_VLINE, ACS_HLINE);

                    for (int i = 1; i < ALTEZZA_ANIMAZIONE_PIANTE-1; ++i)
                    {
                        for (int j = 1; j < LARGHEZZA_ANIMAZIONE_PIANTE-1; ++j)
                        {
                            if(i<ALTEZZA_MARCIAPIEDE_PIANTE)
                            {
                                wattron(animazione_piante, COLOR_PAIR(BG_MARCIAPIEDE_PIANTE));
                            }
                            else
                            {
                                wattron(animazione_piante, COLOR_PAIR(BG_LAGHETTO));
                            }

                            mvwaddch(animazione_piante, i, j, ' ');

                            if(i<ALTEZZA_MARCIAPIEDE_PIANTE)
                            {
                                wattroff(animazione_piante, COLOR_PAIR(BG_MARCIAPIEDE_PIANTE));
                            }
                            else
                            {
                                wattroff(animazione_piante, COLOR_PAIR(BG_LAGHETTO));
                            }
                        }
                    }

                    wattron(animazione_piante, COLOR_PAIR(VERDE_PIANTA));
                    stampa_sprite(animazione_piante, ALTEZZA_PIANTA, LARGHEZZA_PIANTA, pianta_malvagia, 2,(LARGHEZZA_ANIMAZIONE_PIANTE-LARGHEZZA_PIANTA)/2);
                    wattroff(animazione_piante, COLOR_PAIR(VERDE_PIANTA));

                    //lettura e stampa nuovo movimento proiettile
                    if(aux.ID==PROIETTILE_GUIDA)
                    {
                        wattron(animazione_piante, COLOR_PAIR(ROSSO_PROIETTILE_PIANTA));
                        stampa_sprite(animazione_piante, 1, 1, proiettile_sprite, aux.y, aux.x);
                        wattroff(animazione_piante, COLOR_PAIR(ROSSO_PROIETTILE_PIANTA));
                        wrefresh(animazione_piante);
                    }
                }

                //stampa testo pagina
                grafica_selezione_tasto(tasto_dx, tasto_sx, tasto_cntr, testo_dx, testo_sx, testo_cntr);
                caricamento_sprite(FILE_TEXT_PIANTE, ALTEZZA_GUIDA_PIANTA, LARGHEZZA_GUIDA_PIANTA, testo_guida_piante);
                stampa_sprite(text, ALTEZZA_GUIDA_PIANTA, LARGHEZZA_GUIDA_PIANTA, testo_guida_piante, 1, 2);

                break;

        }

        box(text, ACS_VLINE, ACS_HLINE);

        //refresh e kill finestre e processi della pagina precedente
        if(tasto_precedente!=tasto_corrente)
        {
            wrefresh(text);

            wrefresh(tasto_sx);
            wrefresh(tasto_cntr);
            wrefresh(tasto_dx);

            if(tasto_precedente==COCCODRILLO)
            {
                delwin(animazione_coccodrilli);
                animazione_coccodrilli = NULL;

                kill(pid_coccodrillo, SIGKILL);
                waitpid(pid_coccodrillo, NULL, 0);
            }
            if(tasto_precedente==RANA)
            {
                for (int i = 0; i < 2; ++i)
                {
                    posizione_coccodrilli_animazione_rana[i]=(LARGHEZZA_ANIMAZIONE_RANA-LARGHEZZA_COCCODRILLO)/2 + (rand()%5)-2;
                }

                delwin(animazione_rana);
                animazione_rana = NULL;

                kill(pid_rana, SIGKILL);
                waitpid(pid_rana, NULL, 0);
            }
            if(tasto_precedente==PIANTA)
            {
                delwin(animazione_piante);
                animazione_piante = NULL;

                kill(pid_proiettile_pianta, SIGKILL);
                waitpid(pid_proiettile_pianta, NULL, 0);
            }
        }

        //se torno alla schermata precedente nel menu killo i processi attivi in quel momento
        if(aux.c=='i')
        {
            if(tasto_corrente==COCCODRILLO)
            {
                kill(pid_coccodrillo, SIGKILL);
                waitpid(pid_coccodrillo, NULL, 0);
            }
            if(tasto_corrente==RANA)
            {
                kill(pid_rana, SIGKILL);
                waitpid(pid_rana, NULL, 0);
            }
            if(tasto_corrente==PIANTA)
            {
                kill(pid_proiettile_pianta, SIGKILL);
                waitpid(pid_proiettile_pianta, NULL, 0);
            }

            break;
        }

    }while(true);

    //kill processo input bestiario
    kill(pid_input, SIGKILL);
    waitpid(pid_input, NULL, 0);


}

/**
 * Funzione processo input bestiario
 *
 * @param pipeout descrittore in scrittura
 */
void input(int pipeout)
{
    nodelay(stdscr, 1);
    Character_guida input_utente;

    input_utente.ID=INPUT;
    input_utente.y=NOCHOICE;
    input_utente.x=NOCHOICE;
    input_utente.c=NO_CHOICE_INPUT;

    do
    {
        write(pipeout, &input_utente, sizeof(Character_guida));

        input_utente.c=getch();

    }while(true);
}

/**
 * Funzione processo coccodrillo bestiario
 *
 * @param pipeout descrittore in scrittura
 */
void pos_coccodrilli_guida(int pipeout)
{
    Character_guida coccodrillo;

    coccodrillo.ID=COCCODRILLO_GUIDA;
    coccodrillo.y=2;
    coccodrillo.x=1;
    coccodrillo.c=NO_CHOICE_INPUT;

    if(rand()%2==0)
    {
        coccodrillo.status=BUONO;
    }else
    {
        coccodrillo.status=CATTIVO;
    }

    do
    {
        write(pipeout, &coccodrillo, sizeof(Character_guida));

        coccodrillo.x+=1;

        if(coccodrillo.x==LARGHEZZA_ANIMAZIONE_COCCODRILLI-LARGHEZZA_COCCODRILLO)
        {
            coccodrillo.x=1;
        }

        usleep(250000);
    }while(true);
}

/**
 * Funzione processo rana bestiario
 *
 * @param pipeout descrittore in scrittura
 */
void pos_rana_guida(int pipeout)
{
    Character_guida rana;

    rana.ID=RANA_GUIDA;
    rana.y=ALTEZZA_ANIMAZIONE_RANA-ALTEZZA_RANA-1;
    rana.x=(LARGHEZZA_ANIMAZIONE_RANA-2)/2;
    rana.c=NO_CHOICE_INPUT;


    do
    {
        write(pipeout, &rana, sizeof(Character_guida));

        rana.y-=1;

        if(rana.y==ALTEZZA_TANA/2)
        {
            rana.y=ALTEZZA_ANIMAZIONE_RANA-ALTEZZA_RANA-1;
        }

        usleep(300000);
    }while(true);
}

/**
 * Funzione processo proiettile sparato dalla pianta del bestiario
 *
 * @param pipeout descrittore in scrittura
 */
void pos_proiettile_pianta_guida(int pipeout)
{
    Character_guida proiettile;

    proiettile.ID=PROIETTILE_GUIDA;
    proiettile.y=ALTEZZA_PIANTA+1;
    proiettile.x=(LARGHEZZA_ANIMAZIONE_PIANTE - LARGHEZZA_PIANTA)/2 + LARGHEZZA_PIANTA-1;;
    proiettile.c=NO_CHOICE_INPUT;

    do
    {
        write(pipeout, &proiettile, sizeof(Character_guida));

        proiettile.y+=1;

        if(proiettile.y==ALTEZZA_ANIMAZIONE_PIANTE-1)
        {
            proiettile.y=ALTEZZA_PIANTA+1;
        }

        usleep(300000);
    }while(true);
}
