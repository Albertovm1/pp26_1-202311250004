#include "Livro.hpp"
#include "Revista.hpp"
#include "PublicacaoImplBD.hpp"
#include "PublicacaoImplXML.hpp"
#include <iostream>

int main() {
    Implementador* banco = new PublicacaoImplBD();
    Implementador* arquivo = new PublicacaoImplXML();

    std::cout << "\n[CASE 1] Livro no Banco de Dados:" << std::endl;
    Publicacao* p1 = new Livro(banco);
    p1->obterDados("Academico");
    p1->getTitulo();
    std::cout << "----------------------------------------" << std::endl;

    std::cout << "[CASE 2] Livro no arquivo XML:" << std::endl;
    Publicacao* p2 = new Livro(arquivo);
    p2->obterDados("Literatura");
    p2->getTitulo();
    std::cout << "----------------------------------------" << std::endl;

    std::cout << "[CASE 3] Revista no Banco de Dados:" << std::endl;
    Publicacao* p3 = new Revista(banco);
    p3->obterDados("Cientifico");
    p3->getAutor(55);
    std::cout << "----------------------------------------" << std::endl;

    std::cout << "[CASE 4] Revista no arquivo XML:" << std::endl;
    Publicacao* p4 = new Revista(arquivo);
    p4->obterDados("Informatica");
    p4->getAutor(99);
    std::cout << "----------------------------------------" << std::endl;

    delete p1; 
    delete p2; 
    delete p3; 
    delete p4;
    delete banco; 
    delete arquivo;
    return 0;
}