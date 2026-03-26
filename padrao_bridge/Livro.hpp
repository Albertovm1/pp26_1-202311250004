#ifndef LIVRO_HPP
#define LIVRO_HPP

#include "Publicacao.hpp"

class Livro : public Publicacao {
public:
    Livro(Implementador* implementador);
    void getISBN();
    void getTitulo() override;
    void getAutor(int id) override;
};

#endif