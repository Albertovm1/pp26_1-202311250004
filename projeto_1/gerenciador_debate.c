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
        
        // 1. Registra no Log a mudança de fase no debate
        char msg_fase[150];
        snprintf(msg_fase, sizeof(msg_fase), "Debate: Candidato '%s' assumiu a palavra na fase de %s.", atual->nome, nome_da_fase(fluxo[i]));
        registrar_log(msg_fase);

        // 2. Notifica os eleitores (Observer) sobre quem está falando
        char msg_obs[100];
        snprintf(msg_obs, sizeof(msg_obs), "Candidato %s está falando (Fase: %s)", atual->nome, nome_da_fase(fluxo[i]));
        notificar_eleitores(atual, msg_obs);

        // 3. Registra no Log a ativação do Hardware (Microfone)
        char msg_hw[150];
        snprintf(msg_hw, sizeof(msg_hw), "Hardware: Microfone ID %d ligado para %s por %d segundos.", atual->microfone->id, atual->nome, atual->microfone->tempo_limite);
        registrar_log(msg_hw);
        
        // 4. Executa a ação no console e roda o tempo do hardware
        printf("\n[Hardware] Ativando periferico...\n");
        ligar_microfone(atual->microfone); // Usa a função do microfone.c que você já tem
        
        rodar_cronometro(atual->microfone->tempo_limite);
        
        printf("[Hardware] Microfone do %s DESLIGADO.\n", atual->nome);
        fflush(stdout);
    }
    
    // Registra o fim do bloco de interações
    registrar_log("Debate: Fim da interacao da rodada entre os candidatos.");
}