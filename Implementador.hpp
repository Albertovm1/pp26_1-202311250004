#ifndef IMPLEMENTADOR_HPP
#define IMPLEMENTADOR_HPP

#include <iostream>
#include <string>

class Implementador {
public:
    virtual ~Implementador() {}
    virtual void getDados(std::string tipo) = 0;
};

#endif