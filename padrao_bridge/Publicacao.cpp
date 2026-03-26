#include "Publicacao.hpp"
#include <iostream>

Publicacao::Publicacao(Implementador* implementador) : imp(implementador) {}

Publicacao::~Publicacao() {}

void Publicacao::obterDados(std::string tipo) {
    std::cout << "[Publicacao] Solicitando dados ao implementador..." << std::endl;
    imp->getDados(tipo);
}

void Publicacao::getTitulo() {
    std::cout << "[Publicacao] Chamado: getTitulo" << std::endl;
}