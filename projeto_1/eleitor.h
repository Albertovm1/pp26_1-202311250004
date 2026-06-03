#ifndef ELEITOR_H
#define ELEITOR_H

#include "observer.h"

typedef struct {
    int id;
    char nome[50];
} Eleitor;

// Construtor original
Eleitor* criar_eleitor(int id, const char* nome);

// Método do Padrão Prototype (Clonagem)
Eleitor* clonar_eleitor(const Eleitor* prototipo, int novo_id, const char* novo_nome);

// Função do Observer
void atualizar_eleitor(void* contexto, const char* mensagem);

#endif  