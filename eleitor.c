#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eleitor.h"

Eleitor* criar_eleitor(int id, const char* nome) {
    Eleitor* e = (Eleitor*)malloc(sizeof(Eleitor));
    if (e) {
        e->id = id;
        strncpy(e->nome, nome, 50);
    }
    return e;
}

void atualizar_eleitor(void* contexto, const char* mensagem) {
    Eleitor* e = (Eleitor*)contexto;
    printf("[Notificação para Eleitor ID %d - %s]: %s\n", e->id, e->nome, mensagem);
}