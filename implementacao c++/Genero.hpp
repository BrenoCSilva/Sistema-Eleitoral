#ifndef GENERO_HPP
#define GENERO_HPP


#include <stdexcept> 
#include <string>    


enum class Genero : int {
    MASCULINO = 2,
    FEMININO = 4
};

int getIdGenero(Genero genero);

Genero generoCandidato(int codigo);

#endif