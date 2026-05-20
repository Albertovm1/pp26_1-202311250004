#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "logger.h"

// Implementação da função de registro
void registrar_log(const char* mensagem) {
    // Abre o arquivo em modo "append" (adiciona ao final)
    FILE* f = fopen("debate.log", "a");
    if (f == NULL) {
        printf("Erro ao abrir arquivo de log.\n");
        return;
    }

    // Obtém o timestamp atual
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // Escreve no log com formato: [YYYY-MM-DD HH:MM:SS] Mensagem
    fprintf(f, "[%d-%02d-%02d %02d:%02d:%02d] %s\n", 
            tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, 
            tm.tm_hour, tm.tm_min, tm.tm_sec, mensagem);

    fclose(f);
}

// Implementação da função de reset
void resetar_log() {
    // Abre em modo "w" (write) para sobrescrever o arquivo existente
    FILE* f = fopen("debate.log", "w");
    if (f) {
        fprintf(f, "--- NOVO DEBATE INICIADO ---\n");
        fclose(f);
    }
}