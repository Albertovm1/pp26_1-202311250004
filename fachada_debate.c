#include "fachada_debate.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "gerenciador_debate.h"
#include "candidato.h"
#include "logger.h"

// Lista estática de candidatos (gerenciada internamente)
static Candidato* banco_candidatos[10];
static int total_candidatos = 0;

int inicializar_sistema() {
    registrar_log("Fachada: Inicializando componentes...");
    
    // Inicialização simples para exemplo
    banco_candidatos[0] = criar_candidato("Candidato A", criar_microfone(1));
    banco_candidatos[1] = criar_candidato("Candidato B", criar_microfone(2));
    banco_candidatos[2] = criar_candidato("Candidato C", criar_microfone(3));
    
    total_candidatos = 3;
    
    // Verificação de segurança
    for(int i = 0; i < total_candidatos; i++) {
        if (banco_candidatos[i] == NULL) return 0;
    }
    
    return 1; // Sucesso
}

void realizar_sorteio_dinamico() {
    Candidato* inq = NULL;
    Candidato* inqdo = NULL;

    // Busca inquiridor (quem ainda não perguntou)
    for(int i = 0; i < total_candidatos; i++) {
        if (!banco_candidatos[i]->ja_perguntou) {
            inq = banco_candidatos[i];
            break;
        }
    }

    // Busca inquirido (o próximo disponível que não é o inquiridor)
    for(int i = 0; i < total_candidatos; i++) {
        if (banco_candidatos[i] != inq) {
            inqdo = banco_candidatos[i];
            break;
        }
    }

    if (inq && inqdo) {
        printf(">> Sorteio: Inquiridor: %s | Inquirido: %s\n", inq->nome, inqdo->nome);
        executar_interacao(inq, inqdo);
        inq->ja_perguntou = true; // Marca como inquiridor usado
    } else {
        printf(">> Erro: Não foi possível realizar sorteio (todos já perguntaram?).\n");
    }
}

void executar_debate() {
    realizar_sorteio_dinamico();
}

void finalizar_sistema() {
    registrar_log("Fachada: Liberando recursos...");
    for(int i = 0; i < total_candidatos; i++) {
        if (banco_candidatos[i]) {
            free(banco_candidatos[i]->microfone);
            free(banco_candidatos[i]);
        }
    }
}