#include "Eleicao.hpp"
#include "Candidato.hpp"
#include "Partido.hpp"
#include <map>



Eleicao::Eleicao(){
    this->qtdVereadoresEleitos = 0;
    this->qtdFeminino =0;
    this->qtdMasculino=0;
    this->qtdVotosLegenda =0;
    this->qtdVotosNominais=0;
}


Candidato* Eleicao::criaCandidato(int codigoMunicipio, int codigoCargo, int numeroCandidato, const std::string &nomeUrna, int numeroFederacao, SituacaoCandidato resultadoTurno, Genero &genero,  Partido *partido,  Data& dataNascimento, Data &dataAtual){

    auto it = this->candidatos.find(numeroCandidato);

    
    if (it != this->candidatos.end()) {

        return it->second;
    }


    Candidato *candidato = new Candidato(codigoMunicipio, codigoCargo,numeroCandidato, nomeUrna,  numeroFederacao, resultadoTurno, genero, partido, dataNascimento, dataAtual);

    this->candidatos.insert({numeroCandidato, candidato});
    partido->adicionarCandidato(candidato);

    return candidato;
}


Candidato* Eleicao::getCandidato(int numeroCandidato)const{
     return candidatos.at(numeroCandidato);
}

const std::map<int, Candidato*>& Eleicao::getCandidatos()const{

    return this->candidatos;
}


Partido* Eleicao::criaPartido(int numeroPartido, const std::string &siglaPartido) {
    
   
    auto it = this->partidos.find(numeroPartido);

    
    if (it != this->partidos.end()) {

        return it->second;
    }

    Partido *partido = new Partido(numeroPartido, siglaPartido);
    this->partidos.insert({numeroPartido, partido});
    
    return partido;
}


Partido* Eleicao::getPartido(int numeroPartido)const{

    return partidos.at(numeroPartido);
}


const std::map<int, Partido*>& Eleicao::getPartidos()const{

    return this->partidos;
}



void Eleicao::incrementrarQtdMasculino(){
    this->qtdMasculino++;
}

void Eleicao::incrementrarQtdFeminino(){
    this->qtdFeminino++;
}

void Eleicao::incrementarQtdNominal(int qtdVotos){
    this->qtdVotosNominais+=qtdVotos;
}

void Eleicao::incrementarQtdLegenda(int qtdVotos){
    this->qtdVotosLegenda+=qtdVotos;
}
void Eleicao::incrementarVereadoresEleitos(){
    this->qtdVereadoresEleitos++;
}


int Eleicao::getQtdVereadoresEleitos()const{

    return this->qtdVereadoresEleitos;
}

int Eleicao::getQtdMasculino()const{

    return this->qtdMasculino;
    
}

int Eleicao::getQtdFeminino()const{

    return this->qtdFeminino;
}

int Eleicao::getQtdVotosNominais()const{

    return this->qtdVotosNominais;
    
}

int Eleicao::getQtdVotosLegenda()const{

    return this->qtdVotosLegenda;
    
}


 Eleicao::~Eleicao(){


    for(auto &par: this->partidos){
         delete par.second;
    }

    for(auto &par : this->candidatos){
        delete par.second;
    }
 }