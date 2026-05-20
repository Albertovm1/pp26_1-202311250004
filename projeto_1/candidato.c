#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "candidato.h"

Candidato* criar_candidato(const char* nome, Microfone* mic) {
    Candidato* c = (Candidato*)malloc(sizeof(Candidato));
    if (!c) return NULL;
    
    strncpy(c->nome, nome, 50);
    c->ja_perguntou = false; // Inicializa como false
    c->total_eleitores = 0;
    c->microfone = mic;
    return c;
}

void adicionar_eleitor(Candidato* c, Observer* obs) {
    if (c && c->total_eleitores < MAX_ELEITORES) {
        c->eleitores[c->total_eleitores++] = obs;
    }
}

void notificar_eleitores(const Candidato* c, const char* msg) {
    if (!c) return;
    for (int i = 0; i < c->total_eleitores; i++) {
        // Notifica cada eleitor observador
        c->eleitores[i]->atualizar(c->eleitores[i]->contexto, msg);
    }
}