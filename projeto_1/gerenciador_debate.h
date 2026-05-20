#ifndef GERENCIADOR_DEBATE_H
#define GERENCIADOR_DEBATE_H

#include "candidato.h"

typedef enum {
    FASE_PERGUNTA,
    FASE_RESPOSTA,
    FASE_REPLICA,
    FASE_TREPLICA
} FaseDebate;

const char* nome_da_fase(FaseDebate fase); 

void executar_interacao(Candidato* inquiridor, Candidato* inquirido);

#endif