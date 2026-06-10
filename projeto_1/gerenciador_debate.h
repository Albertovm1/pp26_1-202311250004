#ifndef GERENCIADOR_DEBATE_H
#define GERENCIADOR_DEBATE_H

#include "candidato.h"

// 1. FORWARD DECLARATION (Avisa o C que este tipo apelidado existirá logo abaixo)
typedef struct GerenciadorDebate GerenciadorDebate;

typedef enum {
    FASE_PERGUNTA,
    FASE_RESPOSTA,
    FASE_REPLICA,
    FASE_TREPLICA
} FaseDebate;

// 2. ESTRUTURA DO ESTADO (Agora usando o tipo limpo e sem a palavra 'struct')
typedef struct EstadoDebate {
    void (*executar_fluxo)(GerenciadorDebate* g);
    void (*pressionar_botao_dr)(GerenciadorDebate* g, Candidato* c);
} EstadoDebate;

// 3. ESTRUTURA DO CONTEXTO DA MÁQUINA DE ESTADOS
struct GerenciadorDebate {
    EstadoDebate* estado_atual;    // Ponteiro para o comportamento polimórfico ativo
    Candidato* fila_dr[10];        // Fila cronológica para múltiplos políticos
    int total_dr;                  // Contador de pedidos na fila
    Candidato* inquiridor;         // Candidato sorteado para fazer perguntas
    Candidato* inquirido;          // Candidato sorteado para responder
};

// Declaração das instâncias dos Estados Globais
extern EstadoDebate EstadoNormal;
extern EstadoDebate EstadoDireitoResposta;

// Funções públicas de controle chamadas pela Fachada do sistema
void inicializar_gerenciador(GerenciadorDebate* g, Candidato* inq, Candidato* inqdo);
void BlackBox_Executar(GerenciadorDebate* g);

#endif