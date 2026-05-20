#ifndef CANDIDATO_H
#define CANDIDATO_H

#include "observer.h"
#include "microfone.h"
#include <stdbool.h>

#define MAX_ELEITORES 100

typedef struct {
    char nome[50];
    bool ja_perguntou; // Novo requisito: controlar sorteio
    Observer* eleitores[MAX_ELEITORES];
    int total_eleitores;
    Microfone* microfone;
} Candidato;

Candidato* criar_candidato(const char* nome, Microfone* mic);
void adicionar_eleitor(Candidato* c, Observer* obs);
void notificar_eleitores(const Candidato* c, const char* msg);
void liberar_candidato(Candidato* c);

#endif