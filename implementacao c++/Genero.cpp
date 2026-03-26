#include "Genero.hpp"



int getIdGenero(Genero genero) {
    
    return static_cast<int>(genero);
}

Genero generoCandidato(int codigo){
    switch (codigo) {
        case 2:
            return Genero::MASCULINO;
        case 4:
            return Genero::FEMININO;
        default:
            throw std::invalid_argument("Código de gênero inválido: " + std::to_string(codigo));
    }
}