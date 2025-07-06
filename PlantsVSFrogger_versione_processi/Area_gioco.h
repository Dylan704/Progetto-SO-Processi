//
// Created by dylan on 22/12/23.
//

#ifndef PLANTS_VS_FROGGER_AREA_GIOCO_H
#define PLANTS_VS_FROGGER_AREA_GIOCO_H
#include "Struct_enum.h"

void schermo();
void area_gioco(WINDOW* gioco, WINDOW* marciapiede_rana, WINDOW* laghetto, WINDOW* marciapiede_piante, WINDOW* tane, WINDOW* stats);
void gameplay(WINDOW* gioco, Difficolta difficolta);

void stampa_punteggio(WINDOW* gioco, int punteggio, int inizio_y, int inizio_x);
void stampa_oggetti(WINDOW* gioco, int num_max_piante, bool piante_libere[num_max_piante], Character pianta[num_max_piante],
                    int num_corsie, int num_coccodrilli_max_corsia, Character coccodrilli[num_corsie][num_coccodrilli_max_corsia], bool coccodrilli_liberi[num_corsie][num_coccodrilli_max_corsia],
                    int dir_coccodrilli[num_corsie],
                    Character rana, int num_max_proiettili_rana, bool slot_liberi_proiettili_rana[num_max_proiettili_rana], Character proiettili_rana[num_max_proiettili_rana],
                    int num_max_proiettili_piante, Character proiettili_pianta[num_max_piante][num_max_proiettili_piante], bool slot_liberi_proiettili_pianta[num_max_piante][num_max_proiettili_piante],
                    int num_tane, Character tana[num_tane], bool tana_aperta[num_tane],
                    int tempo_massimo, Character timer, int hp_max, int hp_rana, int punteggio, int punteggio_precedente);

void schermata_vittoria(WINDOW* gioco, int punteggio);
void schermata_sconfitta(WINDOW* gioco, int punteggio);
void schermata_quit(WINDOW* gioco, int punteggio);

#endif //PLANTS_VS_FROGGER_AREA_GIOCO_H
