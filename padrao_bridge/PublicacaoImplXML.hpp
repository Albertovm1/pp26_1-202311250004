#ifndef PUBLICACAO_IMPL_XML_HPP
#define PUBLICACAO_IMPL_XML_HPP

#include "Implementador.hpp"

class PublicacaoImplXML : public Implementador {
public:
    void getDados(std::string tipo) override;
};

#endif