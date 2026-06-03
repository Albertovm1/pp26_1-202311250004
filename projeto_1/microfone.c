#include <stdio.h>
#include <stdlib.h>
#include "microfone.h"

Microfone* criar_microfone(int tempo) { // Mude o nome para fazer sentido
    Microfone* m = (Microfone*)malloc(sizeof(Microfone));
    if (m) {
        m->id = 1;              // Pode deixar um ID padrão fixo
        m->tempo_limite = tempo; // Agora sim o tempo é dinâmico!
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