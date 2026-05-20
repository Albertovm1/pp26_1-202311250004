#ifndef OBSERVER_H
#define OBSERVER_H

// Interface pura para o Padrão Observer
typedef struct Observer {
    void* contexto; 
    void (*atualizar)(void* contexto, const char* mensagem);
} Observer;

#endif