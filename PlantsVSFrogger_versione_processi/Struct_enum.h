//
// Created by dylan on 26/12/23.
//

#ifndef PLANTS_VS_FROGGER_STRUCT_ENUM_H
#define PLANTS_VS_FROGGER_STRUCT_ENUM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <curses.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

///MACRO

//dimensioni schermo
#define ALTEZZA_SCHERMO 42
#define LARGHEZZA_SCHERMO (COLS)

//macro usate nel menu di gioco
#define DIM_NOME_FILE
#define ROWS_TITOLO 12
#define COLS_TITOLO 42
#define SCOSTAMENTO_V_TITOLO 3

#define FILE_TITOLO "./sprite/titolo.txt"
#define FILE_SCELTA_DIFFICOLTA "./sprite/scelta_difficolta.txt"
#define FILE_TEXT_RANA "./sprite/guida_rana.txt"
#define FILE_TEXT_COCCODRILLI "./sprite/guida_coccodrilli.txt"
#define FILE_TEXT_PIANTE "./sprite/guida_piante.txt"
#define FILE_PEASHOOTER "./sprite/peashooter.txt"
#define FILE_RANA_MENU "./sprite/rana_menu.txt"

#define FILE_TESTO_VITTORIA "./sprite/sprite_testo_vittoria.txt"
#define FILE_RANA_VITTORIA  "./sprite/sprite_rana_vittoria.txt"

#define FILE_TESTO_SCONFITTA "./sprite/sprite_testo_sconfitta.txt"
#define FILE_RANA_SCONFITTA "./sprite/sprite_rana_sconfitta.txt"

#define FILE_TESTO_QUIT "./sprite/sprite_testo_quit.txt"
#define FILE_RANA_QUIT "./sprite/sprite_rana_quit.txt"

#define ALTEZZA_PEASHOOTER 20
#define LARGHEZZA_PEASHOOTER 45

#define ALTEZZA_RANA_MENU 19
#define LARGHEZZA_RANA_MENU 41

#define ALTEZZA_TASTO 5
#define LARGHEZZA_TASTO 25

#define ALTEZZA_RANA_VITTORIA 15
#define LARGHEZZA_RANA_VITTORIA 28
#define ALTEZZA_TESTO_VITTORIA 7
#define LARGHEZZA_TESTO_VITTORIA 69

#define ALTEZZA_RANA_SCONFITTA 12
#define LARGHEZZA_RANA_SCONFITTA 33
#define ALTEZZA_TESTO_SCONFITTA 7
#define LARGHEZZA_TESTO_SCONFITTA 73

#define ALTEZZA_RANA_QUIT 22
#define LARGHEZZA_RANA_QUIT 34
#define ALTEZZA_TESTO_QUIT 6
#define LARGHEZZA_TESTO_QUIT 90

#define TESTO_GIOCA "GIOCA"
#define TESTO_HELP "BESTIARIO"
#define TESTO_NORMALE "NORMALE"
#define TESTO_DIFFICILE "DIFFICILE"

#define ALTEZZA_TEXT 22
#define LARGHEZZA_TEXT 80

#define ALTEZZA_GUIDA_RANA 16
#define LARGHEZZA_GUIDA_RANA 44
#define ALTEZZA_GUIDA_COCCODRILLO 12
#define LARGHEZZA_GUIDA_COCCODRILLO 66
#define ALTEZZA_GUIDA_PIANTA 19
#define LARGHEZZA_GUIDA_PIANTA 35

#define ALTEZZA_ANIMAZIONE_RANA (ALTEZZA_TEXT - 6)
#define LARGHEZZA_ANIMAZIONE_RANA (LARGHEZZA_TANA + 6)
#define ALTEZZA_ANIMAZIONE_COCCODRILLI (ALTEZZA_COCCODRILLO * 2 + 2)
#define LARGHEZZA_ANIMAZIONE_COCCODRILLI (LARGHEZZA_TEXT - 8)
#define ALTEZZA_ANIMAZIONE_PIANTE (ALTEZZA_TEXT - 6)
#define LARGHEZZA_ANIMAZIONE_PIANTE (LARGHEZZA_PIANTA * 2 + 7)

//dimensioni zone schermata di gioco
#define ALTEZZA_MARCIAPIEDE_RANA 4
#define ALTEZZA_LAGHETTO 20
#define ALTEZZA_MARCIAPIEDE_PIANTE 4
#define ALTEZZA_TANE 4
#define ALTEZZA_STATS 8

///MACRO OGGETTI DI GIOCO
//macro usata per input processo rana
#define NO_CHOICE_INPUT ' '

//macro coccodrilli
#define NUM_COCCODRILLI_MAX_CORSIA 8
#define NUM_CORSIE 10

#define POSSIBILITA_VELOCITA 3

#define PROBABILITA_COCCODRILLI_VERDI_NORMALE 80
#define PROBABILITA_COCCODRILLI_VERDI_DIFFICILE 60

#define TEMPO_MIN_IMMERSIONE_EMERSIONE 25
#define TEMPO_MAX_IMMERSIONE_EMERSIONE 70

//macro piante
#define NUM_MAX_PIANTE_NORMALE 4
#define NUM_MAX_PIANTE_DIFFICILE 7

#define NUM_MAX_PROIETTILI_PIANTE 4
#define NUM_MAX_PROIETTILI_RANA 2

#define ATTESA_SPARO_PIANTE 5000000

//macro tane
#define NUM_TANE 5

//macro proiettili
#define VEL_PROIETTILI 380000

//macro stats
#define TEMPO_MASSIMO 80
#define HP_MAX_NORMALE 5
#define HP_MAX_DIFFICILE 3
#define MAX_PUNTEGGIO 999
#define PUNTEGGIO_TANA 25
#define PUNTEGGIO_PROITTILE 1
#define PUNTEGGIO_PIANTE 15
#define PUNTEGGIO_COCCODRILLI 10
#define PUNTEGGIO_HPUP 50


///DIMENSIONI PERSONAGGI
#define ALTEZZA_RANA 2
#define LARGHEZZA_RANA 3

#define ALTEZZA_COCCODRILLO 2
#define LARGHEZZA_COCCODRILLO 9

#define ALTEZZA_PIANTA 2
#define LARGHEZZA_PIANTA 5

#define ALTEZZA_TANA 4
#define LARGHEZZA_TANA 9

#define ALTEZZA_VITE 3
#define LARGHEZZA_VITE 7

#define ALTEZZA_PROIETTILE 2
#define LARGHEZZA_PROIETTILE 4

#define ALTEZZA_PUNTEGGIO 4
#define LARGHEZZA_PUNTEGGIO 41

#define ALTEZZA_NUMERI 4
#define LARGHEZZA_NUMERI 6

///MACRO ERRORI
#define ERRORE_DIMENSIONE_FINESTRA 0

#define ERRORE_FORK_RANA (-1)
#define ERRORE_FORK_COCCODRILLI (-2)
#define ERRORE_FORK_PROIETTILI_PIANTA (-3)
#define ERRORE_FORK_PROIETTILI_RANA (-4)
#define ERRORE_FORK_PIANTE (-5)

#define ERRORE_APERTURA_FILE (-5)
#define ERRORE_CREAZIONE_FINESTRA (-6)

#define ERRORE_CREAZIONE_PIPE (-7)
#define ERRORE_FORK_INPUT_BESTIARIO (-8)

#define ERRORE_FORK_TIMER (-9)

///ENUMERAZIONI
typedef enum{UP=0, DOWN, BACK, NOCHOICE}Scelta_gioco;
typedef enum{RANA=0, COCCODRILLO, PROIETTILE, PIANTA, TIMER}Personaggi;
typedef enum{INPUT, COCCODRILLO_GUIDA, RANA_GUIDA, PROIETTILE_GUIDA}Personaggi_guida;
typedef enum{BUONO, CATTIVO}Status;
typedef enum{SPARO = 1, IMMERSO, EMERSO, PROMPT_IMMERSIONE, USCITA, CONTINUE}Signal_character;
typedef enum{UNDEFINED_X_COCCODRILLO=-100, UNDEFINED_X_PROIETTILE_RANA=0, UNDEFINED_X_PROIETTILE_PIANTA=-50}Undefined_positions;
typedef enum{RANA_IN_TANA, RANA_CONTRO_MURO, RANA_IN_GAME} Stati_rana_endgame;
typedef enum{VITTORIA, SCONFITTA, QUIT}Stati_fine_partita;
typedef enum{NORMALE, DIFFICILE}Difficolta;

///ID COLORI
typedef enum{VERDOGNOLO=100, VIOLOGNOLO, BLU_MARE, NERO_VERO, VERDE_RANA, ROSSO_COCCODRILLO_MALVAGIO, VERDE_COCCODRILLO_BUONO, VERDE_PIANTA, ROSSO_TIMER,
             ROSSO_PROIETTILE_PIANTA, GIALLO_PROIETTILE_RANA, COLORE_TESTO_PUNTEGGIO, COLORE_TANA}colori;
typedef enum{BG_CYAN=150, BG_GREEN, BG_BLACK, BG_MARCIAPIEDE_PIANTE=200, BG_MARCIAPIEDE_RANA_TANE, BG_LAGHETTO, BG_BLACK_C_RED, BG_BLACK_C_GREEN, BG_GREEN_C_PURPLE
            }sfondi_colore;

///STRUTTURA OGGETTI DI GIOCO
typedef struct
{
    //coordinate
    int y;
    int x;

    //id per differenziare gli oggetti nella pipe
    Personaggi id;

    Signal_character signal;

    int personaggio_signal;  //RANA oppure PIANTA

    int id_riga;
    int id_colonna;

    Status status;

    int tempo_rimasto;
}Character;

typedef struct
{
    Personaggi_guida ID;

    int y;
    int x;
    Status status;

    char c;
}Character_guida;

#endif //PLANTS_VS_FROGGER_STRUCT_ENUM_H
