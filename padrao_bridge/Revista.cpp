#include "Revista.hpp"
#include <iostream>

Revista::Revista(Implementador* implementador) : Publicacao(implementador) {}

void Revista::getArtigo() {
    std::cout << "Metodo getArtigo() chamado na classe Revista" << std::endl;
}

void Revista::getTitulo() {
    std::cout << "Metodo getTitulo() chamado na classe Revista" << std::endl;
}

void Revista::getAutor(int id) {
    std::cout << "Metodo getAutor(id: " << id << ") chamado na classe Revista" << std::endl;
}