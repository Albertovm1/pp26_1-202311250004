#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "gerenciador_debate.h"
#include "logger.h"
#include "candidato.h"

const char* nome_da_fase(FaseDebate fase) {
    switch(fase) {
        case FASE_PERGUNTA: return "PERGUNTA";
        case FASE_RESPOSTA: return "RESPOSTA";
        case FASE_REPLICA:  return "RÉPLICA";
        case FASE_TREPLICA: return "TRÉPLICA";
        default: return "DESCONHECIDO";
    }
}

void rodar_cronometro(int segundos) {
    for (int i = segundos; i > 0; i--) {
        printf("\r[Cronômetro] Tempo restante: %d segundos... ", i);
        fflush(stdout);
        sleep(1);
    }
    printf("\r[Cronômetro] Tempo esgotado!            \n");
}

void executar_interacao(Candidato* inquiridor, Candidato* inquirido) {
    FaseDebate fluxo[] = {FASE_PERGUNTA, FASE_RESPOSTA, FASE_REPLICA, FASE_TREPLICA};
    
    for (int i = 0; i < 4; i++) {
        Candidato* atual = (i == 0 || i == 2) ? inquiridor : inquirido;
        char msg[128];
        
        snprintf(msg, sizeof(msg), "Candidato %s está falando (Fase: %s)", atual->nome, nome_da_fase(fluxo[i]));
        
        registrar_log(msg);
        notificar_eleitores(atual, msg);

        printf("\n[Hardware] Microfone do %s ATIVADO.\n", atual->nome);
        rodar_cronometro(atual->microfone->tempo_limite);
        printf("[Hardware] Microfone do %s DESLIGADO.\n", atual->nome);
        fflush(stdout);
    }
    registrar_log("Fim da interação de debate.");
}