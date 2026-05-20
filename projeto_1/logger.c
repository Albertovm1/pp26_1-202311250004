#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "logger.h"

void registrar_log(const char* mensagem) {
    FILE* f = fopen("debate.log", "a");
    if (f == NULL) {
        printf("Erro ao abrir arquivo de log.\n");
        return;
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    fprintf(f, "[%d-%02d-%02d %02d:%02d:%02d] %s\n", 
            tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, 
            tm.tm_hour, tm.tm_min, tm.tm_sec, mensagem);

    fclose(f);
}

void resetar_log() {
    FILE* f = fopen("debate.log", "w");
    if (f) {
        fprintf(f, "--- NOVO DEBATE INICIADO ---\n");
        fclose(f);
    }
}