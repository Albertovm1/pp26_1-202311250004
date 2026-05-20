#include "Livro.hpp"
#include <iostream>

Livro::Livro(Implementador* implementador) : Publicacao(implementador) {}

void Livro::getISBN() {
    std::cout << "Metodo getISBN chamado na classe Livro" << std::endl;
}

void Livro::getTitulo() {
    std::cout << "Metodo getTitulo chamado na classe Livro" << std::endl;
}

void Livro::getAutor(int id) {
    std::cout << "Metodo getAutor (ID: " << id << ") chamado na classe Livro" << std::endl;
}