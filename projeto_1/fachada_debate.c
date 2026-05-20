#include "fachada_debate.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "gerenciador_debate.h"
#include "candidato.h"
#include "eleitor.h"
#include "logger.h"
#include "microfone.h"

static Candidato* banco_candidatos[10];
static int total_candidatos = 0;

int inicializar_sistema() {
    banco_candidatos[0] = criar_candidato("Candidato A", criar_microfone(1)); // 1s
    banco_candidatos[1] = criar_candidato("Candidato B", criar_microfone(1));
    total_candidatos = 2;
    return 1;
}

void vincular_eleitor_padrao() {
    Eleitor* e1 = criar_eleitor(1, "Joao Silva");
    Eleitor* e2 = criar_eleitor(2, "Maria Souza");
    
    Observer* obs1 = (Observer*)malloc(sizeof(Observer));
    obs1->contexto = e1;
    obs1->atualizar = atualizar_eleitor;

    Observer* obs2 = (Observer*)malloc(sizeof(Observer));
    obs2->contexto = e2;
    obs2->atualizar = atualizar_eleitor;
    
    for(int i = 0; i < total_candidatos; i++) {
        adicionar_eleitor(banco_candidatos[i], obs1);
        adicionar_eleitor(banco_candidatos[i], obs2);
    }
}

void realizar_sorteio_dinamico() {
    Candidato* inq = NULL;
    Candidato* inqdo = NULL;

    for(int i = 0; i < total_candidatos; i++) {
        if (!banco_candidatos[i]->ja_perguntou) {
            inq = banco_candidatos[i];
            break;
        }
    }
    for(int i = 0; i < total_candidatos; i++) {
        if (banco_candidatos[i] != inq) {
            inqdo = banco_candidatos[i];
            break;
        }
    }

    if (inq && inqdo) {
        printf("\n>> Sorteio: Inquiridor: %s | Inquirido: %s\n", inq->nome, inqdo->nome);
        executar_interacao(inq, inqdo);
        inq->ja_perguntou = true;
    }
}

void executar_debate() { realizar_sorteio_dinamico(); }
void finalizar_sistema() { /* ... free memoria ... */ }