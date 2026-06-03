#include <stdio.h>
#include "fachada_debate.h"
#include "logger.h"

int main() {
    resetar_log();
    inicializar_sistema();
    vincular_eleitor_padrao();

    printf("--- CONTROLE DE DEBATE ---\n");
    printf("1. Iniciar rodada\n2. Sair\n");
    
    int opcao;
    while(1) {
        printf("\nEscolha: ");
        if (scanf("%d", &opcao) != 1 || opcao != 1) break;
        executar_debate();
    }
    return 0;
}