#include <stdio.h>
#include <stdlib.h>
#include "microfone.h"

Microfone* criar_microfone(int id) {
    Microfone* m = (Microfone*)malloc(sizeof(Microfone));
    if (m) {
        m->id = id;
        m->tempo_limite = 5; // Tempo padrão de 5 segundos
    }
    return m;
}

void configurar_tempo(Microfone* m, int segundos) {
    if (m) {
        m->tempo_limite = segundos;
    }
}

int ligar_microfone(Microfone* m) {
    if (!m) return 0;
    printf("Microfone %d ligado por %d segundos.\n", m->id, m->tempo_limite);
    return 1;
}