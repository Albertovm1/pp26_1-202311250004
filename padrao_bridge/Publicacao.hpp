#ifndef PUBLICACAO_HPP
#define PUBLICACAO_HPP

#include "Implementador.hpp"
#include <string>
#include <iostream>

class Publicacao {
protected:
    Implementador* imp;

public:
    Publicacao(Implementador* implementador);
    virtual ~Publicacao();

    virtual void obterDados(std::string tipo);
    virtual void getTitulo() = 0;
    virtual void getAutor(int id) = 0; 
};

#endif