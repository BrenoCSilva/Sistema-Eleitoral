#ifndef CANDIDATO_HPP
#define CANDIDATO_HPP

#include<iostream>

class Partido;

#include "Data.hpp"
#include "Genero.hpp"
#include "SituacaoCandidato.hpp"


class Candidato{

    int codigoMunicipio;
    int codigoCargo;
    int numeroCandidato;
    std::string nomeUrna;
    int numeroFederacao;
    Data dataNascimento;
    SituacaoCandidato resultadoTurno;
    Genero genero;
    int idade;
    Partido *partido;
    int qtdVotosRecebidos;

public: 

    Candidato(int codigoMunicipio, int codigoCargo, int numeroCandidato, const std::string &nomeUrna, int numeroFederacao, SituacaoCandidato resultadoTurno, Genero &genero,  Partido *partido, Data& dataNascimento, Data &dataAtual);

    void incrementarVotos(int votos);
    const std::string& getNome()const;
    int getVotos() const ;
    int getNumeroCandidato() const;
    int getNumeroFederacao() const;
    Partido* getPartido() const;
    bool operator<(Candidato const &outro) const;
    bool operator==(Candidato const&outro) const;
  
    SituacaoCandidato getResultadoTurno() const;

    int getIdade()const;

    int calculaIdade(const Data& dataAtual) const;
};






#endif