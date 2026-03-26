#ifndef LEITOR_HPP
#define LEITOR_HPP

#include<iostream>
#include <string>
#include "Eleicao.hpp"

class Leitor{


public: 

    void static carregarArquivoCandidatos(std::string caminho, int municipioInteresse, Eleicao &eleicao, Data &dataAtual);
    void static carregarArquivoVotacao(std::string caminho, int municipioInteresse,  Eleicao &eleicao);


};



#endif 