#ifndef CANDIDATO_H
#define CANDIDATO_H

#include <stdbool.h>
#include "microfone.h"
#include "observer.h"

typedef struct {
    char nome[50];
    Microfone* microfone;
    bool ja_perguntou;
    Observer* eleitores[10];
    int total_eleitores;
} Candidato;

// A estrutura do Builder
typedef struct {
    char nome[50];
    Microfone* microfone;
} CandidatoBuilder;

// Funções do Builder
CandidatoBuilder* iniciar_candidato_builder();
void builder_com_nome(CandidatoBuilder* b, const char* nome);
void builder_com_microfone(CandidatoBuilder* b, Microfone* mic);
Candidato* builder_construir(CandidatoBuilder* b);

// Funções do Candidato
void adicionar_eleitor(Candidato* c, Observer* obs);
void notificar_eleitores(const Candidato* c, const char* msg);

#endif