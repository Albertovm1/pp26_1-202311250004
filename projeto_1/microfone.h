#ifndef MICROFONE_H
#define MICROFONE_H

typedef struct {
    int id;
    int tempo_limite;
} Microfone;

Microfone* criar_microfone(int id);
void configurar_tempo(Microfone* m, int segundos);
int ligar_microfone(Microfone* m);

#endif