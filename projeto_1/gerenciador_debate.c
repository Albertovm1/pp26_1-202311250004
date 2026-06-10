#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "gerenciador_debate.h"
#include "logger.h"
#include "candidato.h"
#include "microfone.h"

// Tradução interna de Enums para texto (usado exclusivamente no Log)
static const char* log_nome_da_fase(FaseDebate fase) {
    switch(fase) {
        case FASE_PERGUNTA: return "PERGUNTA";
        case FASE_RESPOSTA: return "RESPOSTA";
        case FASE_REPLICA:  return "REPLICA";
        case FASE_TREPLICA: return "TREPLICA";
        default: return "DESCONHECIDO";
    }
}

// Cronômetro visível no terminal representando o hardware real rodando
static void rodar_cronometro(int segundos) {
    for (int i = segundos; i > 0; i--) {
        printf("\r[Cronometro] Tempo restante: %d segundos... ", i);
        fflush(stdout);
        sleep(1);
    }
    printf("\r[Cronometro] Tempo esgotado!            \n");
}

// --- DECLARAÇÃO DAS FUNÇÕES INTERNAS DOS ESTADOS (MÁQUINA DE ESTADOS) ---
void normal_executar_fluxo(GerenciadorDebate* g);
void normal_pressionar_botao_dr(GerenciadorDebate* g, Candidato* c);
void dr_executar_fluxo(GerenciadorDebate* g);
void dr_pressionar_botao_dr(GerenciadorDebate* g, Candidato* c);

// Instanciação das estruturas dos Estados Globais
EstadoDebate EstadoNormal = { normal_executar_fluxo, normal_pressionar_botao_dr };
EstadoDebate EstadoDireitoResposta = { dr_executar_fluxo, dr_pressionar_botao_dr };


// --- IMPLEMENTAÇÃO: ESTADO NORMAL (FLUXO TRADICIONAL) ---

void normal_executar_fluxo(GerenciadorDebate* g) {
    FaseDebate fluxo[] = {FASE_PERGUNTA, FASE_RESPOSTA, FASE_REPLICA, FASE_TREPLICA};
    
    // Registros estritamente técnicos no LOG
    registrar_log("======================================================================");
    registrar_log("[PADRAO STATE] Gerenciador iniciou o -> ESTADO NORMAL");
    registrar_log("======================================================================");
    
    printf("\n>>> INICIANDO BLOCO TRADICIONAL DO DEBATE <<<\n");
    
    for (int i = 0; i < 4; i++) {
        Candidato* atual = (i == 0 || i == 2) ? g->inquiridor : g->inquirido;
        
        // Narração clara da dinâmica no Terminal
        printf("\n--------------------------------------------------\n");
        if (fluxo[i] == FASE_PERGUNTA) {
            printf("[DEBATE] %s inicia a fase de PERGUNTA direcionada a %s.\n", g->inquiridor->nome, g->inquirido->nome);
        } else if (fluxo[i] == FASE_RESPOSTA) {
            printf("[DEBATE] %s assume a palavra para a RESPOSTA.\n", g->inquirido->nome);
        } else if (fluxo[i] == FASE_REPLICA) {
            printf("[DEBATE] %s assume o microfone para a REPLICA.\n", g->inquiridor->nome);
        } else if (fluxo[i] == FASE_TREPLICA) {
            printf("[DEBATE] %s finaliza o bloco com a TREPLICA.\n", g->inquirido->nome);
        }
        printf("--------------------------------------------------\n");

        // Registra a fase técnica no Log
        char msg_fase[150];
        snprintf(msg_fase, sizeof(msg_fase), "Fluxo Comum: Candidato '%s' assumiu a palavra na fase de %s.", atual->nome, log_nome_da_fase(fluxo[i]));
        registrar_log(msg_fase);

        // Notifica Eleitores (Observer) - Corrigido para mostrar quem está falando
        char msg_obs[100];
        snprintf(msg_obs, sizeof(msg_obs), "Candidato %s esta discursando no bloco principal.", atual->nome);
        notificar_eleitores(atual, msg_obs);
        
        // Ativação do hardware do microfone e cronômetro
        ligar_microfone(atual->microfone);
        rodar_cronometro(atual->microfone->tempo_limite);
        
        // --- SIMULAÇÃO DO REQUISITO: MÚLTIPLOS POLÍTICOS ACIONANDO O BOTÃO ---
        // Candidato B se sente ofendido na Fase de Resposta e aperta o botão integrado ao microfone
        if (fluxo[i] == FASE_RESPOSTA) {
            g->estado_atual->pressionar_botao_dr(g, g->inquiridor); 
        }
        
        // Candidato A também se sente ofendido na Fase de Tréplica e aciona o botão logo em seguida
        if (fluxo[i] == FASE_TREPLICA) {
            g->estado_atual->pressionar_botao_dr(g, g->inquirido);
        }
    }
    
    registrar_log("[PADRAO STATE] Fim do ciclo de debate normal (Pergunta-Resposta-Replica-Treplica).");
    registrar_log("[PADRAO STATE] Gerente avaliando concessao de Direitos de Resposta acumulados...");

    // Regra de transição: Só após o ciclo completo, o gerente avalia a fila
    if (g->total_dr > 0) {
        char msg_transicao[150];
        snprintf(msg_transicao, sizeof(msg_transicao), "[PADRAO STATE] Transicao detectada! Fila com %d pedido(s). Alterando para: ESTADO DIREITO DE RESPOSTA.", g->total_dr);
        registrar_log(msg_transicao);
        
        // Transição polimórfica de estado
        g->estado_atual = &EstadoDireitoResposta; 
    }
}

void normal_pressionar_botao_dr(GerenciadorDebate* g, Candidato* c) {
    // Validação para evitar duplicidade do mesmo candidato na fila no mesmo bloco
    for (int i = 0; i < g->total_dr; i++) {
        if (g->fila_dr[i] == c) return;
    }
    
    if (g->total_dr < 10) {
        // Log registra o acionamento físico do periférico integrado
        char msg_hardware[150];
        snprintf(msg_hardware, sizeof(msg_hardware), "[HARDWARE] Botao DR integrado ao microfone acionado pelo politico: %s.", c->nome);
        registrar_log(msg_hardware);

        // Insere na fila respeitando estritamente a ordem cronológica de pressão do botão
        g->fila_dr[g->total_dr] = c;
        g->total_dr++;
        
        char msg_fila[150];
        snprintf(msg_fila, sizeof(msg_fila), "[FILA CRONOLOGICA] Gerente aceitou a solicitacao. Armazenado na posicao %d para: %s.", g->total_dr, c->nome);
        registrar_log(msg_fila);
    }
}


// --- IMPLEMENTAÇÃO: ESTADO DIREITO DE RESPOSTA (FLUXO INTERRUPTO) ---

void dr_executar_fluxo(GerenciadorDebate* g) {
    registrar_log("======================================================================");
    registrar_log("[PADRAO STATE] Gerenciador iniciou o -> ESTADO DIREITO DE RESPOSTA");
    registrar_log("======================================================================");
    
    printf("\n>>> ATENCAO: FLUXO NORMAL INTERROMPIDO PARA DIREITOS DE RESPOSTA <<<\n");
    
    // Processa a fila na ordem exata em que os botões foram pressionados
    for (int i = 0; i < g->total_dr; i++) {
        Candidato* atual = g->fila_dr[i];
        
        char msg_atendimento[150];
        snprintf(msg_atendimento, sizeof(msg_atendimento), "[FILA CRONOLOGICA] Atendendo solicitacao %d de %d: Concedendo palavra a '%s'.", i+1, g->total_dr, atual->nome);
        registrar_log(msg_atendimento);

        // Notifica Eleitores via Observer - Corrigido para mostrar quem está se defendendo
        char msg_obs[100];
        snprintf(msg_obs, sizeof(msg_obs), "Candidato %s entrou no ar em DIREITO DE RESPOSTA para se defender!", atual->nome);
        notificar_eleitores(atual, msg_obs);

        // Modifica temporariamente o hardware do microfone para o tempo de defesa
        int tempo_original = atual->microfone->tempo_limite;
        configurar_tempo(atual->microfone, 6); // 6 segundos para demonstração ágil em console
        
        ligar_microfone(atual->microfone);
        rodar_cronometro(6);
        
        // Restaura o tempo de fábrica do hardware
        configurar_tempo(atual->microfone, tempo_original);
        
        // --- SIMULAÇÃO DO REQUISITO: BLOQUEIO DE NOVOS PEDIDOS EM LOOP INDEVIDO ---
        // Durante a fala de defesa, simulamos que o adversário tenta pressionar o botão abusivamente
        Candidato* adversario = (atual == g->inquiridor) ? g->inquirido : g->inquiridor;
        g->estado_atual->pressionar_botao_dr(g, adversario);
    }
    
    // Limpa a fila cronológica de solicitações atendidas
    g->total_dr = 0;
    
    registrar_log("[PADRAO STATE] Todos os Direitos de Resposta do bloco foram processados.");
    registrar_log("[PADRAO STATE] Transicao detectada! Retornando para: ESTADO NORMAL.");
    registrar_log("======================================================================");
    
    printf("\n>>> Defesas concluidas. Retornando ao fluxo normal de execucao... <<<\n");
    
    // Retorna a máquina de estados para o estado padrão
    g->estado_atual = &EstadoNormal; 
}

void dr_pressionar_botao_dr(GerenciadorDebate* g, Candidato* c) {
    // Requisito de Segurança: No Estado de DR, o botão ignora e bloqueia novos pedidos para impedir loops infinitos
    char msg_bloqueio[150];
    snprintf(msg_bloqueio, sizeof(msg_bloqueio), "[BLOQUEIO STATE] Politico '%s' pressionou o botao DR, mas a acao foi REJEITADA (Bloqueio anti-loop ativo).", c->nome);
    registrar_log(msg_bloqueio);
}


// --- FUNÇÕES DE CONTROLE DO CONTEXTO (MÁQUINA DE ESTADOS) ---

void inicializar_gerenciador(GerenciadorDebate* g, Candidato* inq, Candidato* inqdo) {
    if (!g) return;
    g->estado_atual = &EstadoNormal; // Define o estado de partida padrão
    g->total_dr = 0;
    g->inquiridor = inq;
    g->inquirido = inqdo;
    registrar_log("[PADRAO STATE] Contexto do Gerenciador de Debate configurado com sucesso.");
}

void BlackBox_Executar(GerenciadorDebate* g) {
    // Força a execução contínua da Máquina de Estados enquanto houverem estados pendentes a processar
    while (g && g->estado_atual) {
        EstadoDebate* estado_anterior = g->estado_atual;
        
        // Delegação polimórfica: o comportamento muda completamente baseado no ponteiro do estado ativo
        g->estado_atual->executar_fluxo(g);
        
        // Se após executar o fluxo, o estado não mudou (voltou para o Normal), encerramos este bloco do debate
        if (g->estado_atual == estado_anterior || g->estado_atual == &EstadoNormal) {
            break;
        }
    }
}