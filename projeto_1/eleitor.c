#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eleitor.h"
#include "logger.h"

Eleitor* criar_eleitor(int id, const char* nome) {
    Eleitor* e = (Eleitor*)malloc(sizeof(Eleitor));
    if (e) {
        e->id = id;
        strncpy(e->nome, nome, 49);
        e->nome[49] = '\0';
    }
    return e;
}

// Implementação do Prototype
Eleitor* clonar_eleitor(const Eleitor* prototipo, int novo_id, const char* novo_nome) {
    if (!prototipo) return NULL;

    // Aloca memória para o novo clone
    Eleitor* clone = (Eleitor*)malloc(sizeof(Eleitor));
    if (!clone) return NULL;

    // 1. Copia o estado do protótipo original (Deep Copy / Cópia Profunda)
    memcpy(clone, prototipo, sizeof(Eleitor));

    // 2. Personaliza apenas os dados específicos da nova instância
    clone->id = novo_id;
    strncpy(clone->nome, novo_nome, 49);
    clone->nome[49] = '\0';

    char msg_log[100];
    snprintf(msg_log, sizeof(msg_log), "Prototype: Eleitor ID %d ('%s') clonado a partir do modelo.", clone->id, clone->nome);
    registrar_log(msg_log);

    return clone;
}

void atualizar_eleitor(void* contexto, const char* mensagem) {
    Eleitor* e = (Eleitor*)contexto;
    if (e) {
        printf("[Notificação para Eleitor ID %d - %s]: %s\n", e->id, e->nome, mensagem);
    }
}