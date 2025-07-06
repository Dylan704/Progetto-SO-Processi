//
// Created by dylan on 22/12/23.
//

#ifndef PLANTS_VS_FROGGER_PERSONAGGI_H
#define PLANTS_VS_FROGGER_PERSONAGGI_H
#include "Struct_enum.h"
void stampa_sprite_personaggio(WINDOW* gioco, int y_inizio, int x_inizio, int rows, int cols, char sprite[rows][cols+1]);

void pos_rana(int pipeout);
void pos_coccodrillo(int pipeout, int dir, int id_coccodrillo_corsia, int id_coccodrillo_numero, int velocita, int status_coccodrillo);
void pos_proiettile(int pipeout, int dir_proiettile, int personaggio_sparo, int id_proiettile1, int id_proiettile2);
void pos_pianta(int pipeout, int id_pianta);

void gen_dir_coccodrilli(int num_corsie, int dir_coccodrilli[num_corsie]);
void gen_vel_coccodrilli(int num_corsie, int possibilita, int velocita_corsia[num_corsie], int velocita_coccodrilli[possibilita]);
void gen_coccodrilli_ogni_manche(int* slot_libero_coccodrillo, int num_corsie, int num_coccodrilli_max_corsia,
                                 bool coccodrilli_liberi[num_corsie][num_coccodrilli_max_corsia], Character coccodrilli[num_corsie][num_coccodrilli_max_corsia],
                                 pid_t pid_coccodrilli[num_corsie][num_coccodrilli_max_corsia], int dir_coccodrilli[num_corsie], int velocita_corsia[num_corsie],
                                 int possibilita_velocita, int velocita_coccodrilli[possibilita_velocita], int pipein, int pipeout);
void gen_continua_coccodrilli(int* slot_libero_coccodrillo, int *status_coccodrillo, int difficolta,
                              int num_corsie, int num_coccodrilli_max_corsia, int cooldown_corsia[num_corsie],
                              bool coccodrilli_liberi[num_corsie][num_coccodrilli_max_corsia], Character coccodrilli[num_corsie][num_coccodrilli_max_corsia],
                              pid_t pid_coccodrilli[num_corsie][num_coccodrilli_max_corsia], int dir_coccodrilli[num_corsie], int velocita_corsia[num_corsie],
                              int possibilita_velocita, int velocita_coccodrilli[possibilita_velocita], Character timer,
                              int pipein, int pipeout);

void gen_continua_piante(int num_max_piante, int* num_piante_in_game, int *cooldown_generazione_piante, bool piante_libere[num_max_piante],
                         Character pianta[num_max_piante], pid_t pid_piante[num_max_piante], Character timer, int pipein,int pipeout);

void timer_partita(int pipeout, int tempo_rimasto_partita);

void total_kill(int num_corsie, int num_coccodrilli_max_corsia, pid_t pid_coccodrilli[num_corsie][num_coccodrilli_max_corsia], bool coccodrilli_liberi[num_corsie][num_coccodrilli_max_corsia],
                int num_max_proiettili_rana, pid_t pid_proiettili_rana[num_max_proiettili_rana], bool slot_liberi_proiettili_rana[num_max_proiettili_rana],
                int num_max_piante, int num_max_proiettili_piante, pid_t pid_proiettili_pianta[num_max_piante][num_max_proiettili_piante], bool slot_liberi_proiettili_pianta[num_max_piante][num_max_proiettili_piante],
                bool piante_libere[num_max_piante], pid_t pid_piante[num_max_piante], pid_t pid_timer);

void reset_globale_manche(int num_corsie, int num_coccodrilli_max_corsia, pid_t pid_coccodrilli[num_corsie][num_coccodrilli_max_corsia], bool coccodrilli_liberi[num_corsie][num_coccodrilli_max_corsia],
                          int num_max_proiettili_rana, pid_t pid_proiettili_rana[num_max_proiettili_rana], bool slot_liberi_proiettili_rana[num_max_proiettili_rana],
                          int num_max_piante, int num_max_proiettili_piante, pid_t pid_proiettili_pianta[num_max_piante][num_max_proiettili_piante], bool slot_liberi_proiettili_pianta[num_max_piante][num_max_proiettili_piante],
                          int cooldown_corsie[num_corsie], int *num_piante_in_game, bool piante_libere[num_max_piante], int *cooldown_generazione_piante,
                          pid_t pid_timer, pid_t pid_piante[num_max_piante]);


bool collisione_proj_piante_rana(int num_max_piante, int num_max_proiettili_piante, bool slot_liberi_proiettili_pianta[num_max_piante][num_max_proiettili_piante],
                                 Character proiettili_pianta[num_max_piante][num_max_proiettili_piante], Character rana);

Stati_rana_endgame collisione_rana_tana_o_muro(int num_tane, Character rana, Character tana[num_tane], bool tana_aperta[num_tane]);

bool rana_morte_acqua(int num_corsie, int num_coccodrilli_max_corsia, Character rana, bool coccodrilli_liberi[num_corsie][num_coccodrilli_max_corsia],
                      Character coccodrilli[num_corsie][num_coccodrilli_max_corsia]);

bool rana_morte_pianta(int num_max_piante, bool piante_libere[num_max_piante], Character rana, Character pianta[num_max_piante]);

void collisione_proj_pianta_proj_rana(int num_max_proiettili_rana, bool slot_liberi_proiettili_rana[num_max_proiettili_rana], Character proiettili_rana[num_max_proiettili_rana],
                                      int num_max_piante, int num_max_proiettili_pianta, Character proiettili_pianta[num_max_piante][num_max_proiettili_pianta], bool slot_liberi_proiettili_pianta[num_max_piante][num_max_proiettili_pianta],
                                      pid_t pid_proiettili_rana[num_max_proiettili_rana],  pid_t pid_proiettili_pianta[num_max_piante][num_max_proiettili_pianta],
                                      int *punteggio, int id1, int id2 );
void collisione_proj_rana_proj_piante(int id, int num_max_piante, int num_max_proiettili_pianta, int num_max_proiettili_rana, bool slot_liberi_proiettili_pianta[num_max_piante][num_max_proiettili_pianta],
                                      bool slot_liberi_proiettili_rana[num_max_proiettili_rana], pid_t pid_proiettili_rana[num_max_proiettili_rana], Character proiettili_rana[num_max_proiettili_rana],
                                      Character proiettili_pianta[num_max_piante][num_max_proiettili_pianta], pid_t pid_proiettili_pianta[num_max_piante][num_max_proiettili_pianta], int* punteggio);

void collisione_proj_rana_coccodrilli(int id, int num_corsie, int num_coccodrilli_max_corsia, bool coccodrilli_liberi[num_corsie][num_coccodrilli_max_corsia], Character coccodrilli[num_corsie][num_coccodrilli_max_corsia],
                                    int velocita_corsia[num_corsie], int dir_coccodrilli[num_corsie], pid_t pid_coccodrilli[num_corsie][num_coccodrilli_max_corsia],
                                    int num_max_proiettili_rana, bool slot_liberi_proiettili_rana[num_max_proiettili_rana], Character proiettili_rana[num_max_proiettili_rana],
                                    pid_t pid_proiettili_rana[num_max_proiettili_rana], int* punteggio, int pipein, int pipeout);

void collisione_proj_pianta(int id, int num_max_piante, int num_max_proiettili_rana, int* punteggio, bool piante_libere[num_max_piante], Character proiettili_rana[num_max_proiettili_rana],
                            bool slot_liberi_proiettili_rana[num_max_proiettili_rana], pid_t pid_proiettili_rana[num_max_proiettili_rana], int *num_piante_in_game, pid_t pid_piante[num_max_piante],
                            Character pianta[num_max_piante]);

void collisione_coccodrilli_proj_rana(int id1, int id2, int num_corsie, int num_coccodrilli_max_corsia, Character coccodrilli[num_corsie][num_coccodrilli_max_corsia],
                                      int velocita_corsia[num_corsie], int dir_coccodrilli[num_corsie], pid_t pid_coccodrilli[num_corsie][num_coccodrilli_max_corsia],
                                      int num_max_proiettili_rana, bool slot_liberi_proiettili_rana[num_max_proiettili_rana], Character proiettili_rana[num_max_proiettili_rana],
                                      pid_t pid_proiettili_rana[num_max_proiettili_rana], int* punteggio, int pipein,int pipeout);

void controllo(WINDOW* gioco, Difficolta difficolta, int pipein, int pipeout);

#endif //PLANTS_VS_FROGGER_PERSONAGGI_H
