#include <stdio.h>
#include "fachada_debate.h"
#include "logger.h"

int main() {
    inicializar_sistema();
    resetar_log();
    
    int opcao;
    printf("--- CONTROLE DE DEBATE ---\n");
    printf("1. Iniciar rodada de debate\n");
    printf("2. Sair\n");
    
    while(1) {
        printf("\nEscolha: ");
        if(scanf("%d", &opcao) != 1) break; 
        
        if (opcao == 1) {
            executar_debate();
        } else {
            break;
        }
    }
    
    finalizar_sistema();
    return 0;
}