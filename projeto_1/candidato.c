#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "candidato.h"

Candidato* criar_candidato(const char* nome, Microfone* mic) {
    Candidato* c = (Candidato*)calloc(1, sizeof(Candidato));
    if (!c) return NULL;
    
    strncpy(c->nome, nome, 50);
    c->microfone = mic;
    c->ja_perguntou = false;
    c->total_eleitores = 0; 
    return c;
}

void adicionar_eleitor(Candidato* c, Observer* obs) {
    if (c->total_eleitores < 10) {
        // Armazena o ponteiro do observer
        c->eleitores[c->total_eleitores] = obs;
        c->total_eleitores++;
    }
}

void notificar_eleitores(const Candidato* c, const char* msg) {
    for (int i = 0; i < c->total_eleitores; i++) {
        if (c->eleitores[i] != NULL) {
            c->eleitores[i]->atualizar(c->eleitores[i]->contexto, msg);
        }
    }
}