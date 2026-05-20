#ifndef ELEITOR_H
#define ELEITOR_H

#include "observer.h"

typedef struct {
    char nome[50];
    int id;
} Eleitor;

Eleitor* criar_eleitor(int id, const char* nome);
void atualizar_eleitor(void* contexto, const char* mensagem);

#endif