#include <stdio.h>
#include <string.h> // Necessário para snprintf
#include "gerenciador_debate.h"
#include "logger.h"
#include <unistd.h> 

void executar_interacao(Candidato* inquiridor, Candidato* inquirido) {
    FaseDebate fluxo[] = {FASE_PERGUNTA, FASE_RESPOSTA, FASE_REPLICA, FASE_TREPLICA};
    
    for (int i = 0; i < 4; i++) {
        Candidato* atual = (i == 0 || i == 2) ? inquiridor : inquirido;
        char msg[128];
        
        // Formata a mensagem de log
        snprintf(msg, sizeof(msg), "Candidato %s está falando (Fase: %s)", atual->nome, nome_da_fase(fluxo[i]));
        
        // LOG E NOTIFICAÇÃO
        registrar_log(msg); // <--- AQUI ESTAVA FALTANDO!
        notificar_eleitores(atual, msg);

        if (i > 0) printf("[Hardware] Microfone DESLIGADO.\n");
        printf("[Hardware] Microfone do %s ATIVADO.\n", atual->nome);
        
        sleep(1); // Reduzi para 1s para o teste ser mais rápido
    }
    printf("[Hardware] Microfone DESLIGADO.\n");
    registrar_log("Fim da interação de debate.");
}

const char* nome_da_fase(FaseDebate fase) {
    switch(fase) {
        case FASE_PERGUNTA: return "PERGUNTA";
        case FASE_RESPOSTA: return "RESPOSTA";
        case FASE_REPLICA:  return "RÉPLICA";
        case FASE_TREPLICA: return "TRÉPLICA";
        default: return "DESCONHECIDO";
    }
}