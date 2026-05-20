#ifndef OBSERVER_H
#define OBSERVER_H

typedef struct Observer {
    void* contexto; 
    void (*atualizar)(void* contexto, const char* mensagem);
} Observer;

#endif