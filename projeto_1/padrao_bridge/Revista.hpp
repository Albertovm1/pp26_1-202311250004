#ifndef REVISTA_HPP
#define REVISTA_HPP

#include "Publicacao.hpp"

class Revista : public Publicacao {
public:
    Revista(Implementador* implementador);
    void getArtigo();
    void getTitulo() override;
    void getAutor(int id) override;
};

#endif