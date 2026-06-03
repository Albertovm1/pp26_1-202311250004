#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "candidato.h"
#include "logger.h"

CandidatoBuilder* iniciar_candidato_builder() {
    CandidatoBuilder* b = (CandidatoBuilder*)malloc(sizeof(CandidatoBuilder));
    if (b) {
        b->nome[0] = '\0';
        b->microfone = NULL;
    }
    return b;
}

void builder_com_nome(CandidatoBuilder* b, const char* nome) {
    if (b) {
        strncpy(b->nome, nome, 49);
        b->nome[49] = '\0';
    }
}

void builder_com_microfone(CandidatoBuilder* b, Microfone* mic) {
    if (b) {
        b->microfone = mic;
    }
}

Candidato* builder_construir(CandidatoBuilder* b) {
    if (!b) return NULL;
    
    // Aloca a memória limpa para o candidato final
    Candidato* c = (Candidato*)calloc(1, sizeof(Candidato));
    if (!c) return NULL;
    
    // Transfere os dados acumulados no Builder para o Candidato
    strncpy(c->nome, b->nome, 50);
    c->microfone = b->microfone;
    c->ja_perguntou = false;
    c->total_eleitores = 0;

    char msg_log[100];
    snprintf(msg_log, sizeof(msg_log), "Builder: Candidato '%s' construido com sucesso.", c->nome);
    registrar_log(msg_log);
    
    // Libera a memória do Builder, pois o objeto já foi construído
    free(b); 
    
    return c;
}

void adicionar_eleitor(Candidato* c, Observer* obs) {
    if (c && c->total_eleitores < 10) {
        c->eleitores[c->total_eleitores] = obs;
        c->total_eleitores++;
    }
}

void notificar_eleitores(const Candidato* c, const char* msg) {
    if (!c) return;
    for (int i = 0; i < c->total_eleitores; i++) {
        if (c->eleitores[i] != NULL) {
            c->eleitores[i]->atualizar(c->eleitores[i]->contexto, msg);
        }
    }
}