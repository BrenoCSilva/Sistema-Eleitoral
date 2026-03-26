#ifndef ELEICAO_HPP
#define ELEICAO_HPP


#include <iostream>
#include <map>
#include "Genero.hpp"
#include "Data.hpp"
#include "SituacaoCandidato.hpp"

class Candidato;
class Partido;

class Eleicao{

    std::map<int, Candidato*> candidatos;
    std::map<int, Partido*> partidos;
    int qtdVereadoresEleitos;
    int qtdVotosLegenda;
    int qtdVotosNominais;
    int qtdMasculino;
    int qtdFeminino;

public:

    Eleicao();
    ~Eleicao();
    
    Candidato* criaCandidato(int codigoMunicipio, int codigoCargo, int numeroCandidato, const std::string &nomeUrna, int numeroFederacao, SituacaoCandidato resultadoTurno, Genero &genero,  Partido *partido,  Data& dataNascimento,  Data &dataAtual);
    Candidato* getCandidato(int numeroCandidato)const;
    const std::map<int, Candidato*>& getCandidatos()const;

    Partido* criaPartido(int numeroPartido, const std::string &siglaPartido);
    Partido* getPartido(int numeroPartido)const;
    const std::map<int, Partido*>& getPartidos()const;




    void incrementarVereadoresEleitos();
    void incrementrarQtdMasculino();
    void incrementrarQtdFeminino();
    void incrementarQtdLegenda(int qtdVotos);
    void incrementarQtdNominal(int qtdVotos);

    int getQtdMasculino()const;
    int getQtdFeminino()const;
    int getQtdVereadoresEleitos()const;
    int getQtdVotosLegenda()const;
    int getQtdVotosNominais()const;

  
};





#endif