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
    registrar_log("Fachada: Inicializando componentes com Builder...");

    // Construindo o Candidato A passo a passo
    CandidatoBuilder* b1 = iniciar_candidato_builder();
    builder_com_nome(b1, "Candidato A");
    builder_com_microfone(b1, criar_microfone(5)); // Define 5 segundos
    banco_candidatos[0] = builder_construir(b1);

    // Construindo o Candidato B passo a passo
    CandidatoBuilder* b2 = iniciar_candidato_builder();
    builder_com_nome(b2, "Candidato B");
    builder_com_microfone(b2, criar_microfone(5));
    banco_candidatos[1] = builder_construir(b2);

    total_candidatos = 2;
    return 1;
}

void vincular_eleitor_padrao() {
    // 1. Criamos o nosso Eleitor Protótipo (o modelo base)
    Eleitor* eleitor_base = criar_eleitor(0, "Prototipo Base");

    // 2. Usamos o Prototype para clonar o modelo base mudando apenas o necessário
    Eleitor* e1 = clonar_eleitor(eleitor_base, 1, "Joao Silva");
    Eleitor* e2 = clonar_eleitor(eleitor_base, 2, "Maria Souza");
    Eleitor* e3 = clonar_eleitor(eleitor_base, 3, "Carlos Andrade"); // Fácil de adicionar mais!

    // Criando os invólucros do Observer para cada clone
    Observer* obs1 = (Observer*)malloc(sizeof(Observer));
    obs1->contexto = e1; obs1->atualizar = atualizar_eleitor;

    Observer* obs2 = (Observer*)malloc(sizeof(Observer));
    obs2->contexto = e2; obs2->atualizar = atualizar_eleitor;

    Observer* obs3 = (Observer*)malloc(sizeof(Observer));
    obs3->contexto = e3; obs3->atualizar = atualizar_eleitor;
    
    // Vincula todos os clones aos candidatos
    for(int i = 0; i < total_candidatos; i++) {
        adicionar_eleitor(banco_candidatos[i], obs1);
        adicionar_eleitor(banco_candidatos[i], obs2);
        adicionar_eleitor(banco_candidatos[i], obs3);
    }

    // Como usamos o protótipo apenas como molde, podemos liberá-lo se não formos mais usar
    free(eleitor_base);
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