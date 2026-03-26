#include "Partido.hpp"
#include "Candidato.hpp"
#include <vector>
#include <algorithm> // Para std::max_element



Partido::Partido(int numeroPartido, const std::string &siglaPartido){

    this->numeroPartido = numeroPartido;
    this->siglaPartido = siglaPartido;
    
    this->votosLegenda = 0;
    this->votosNominais = 0;
    this->votosTotais = 0;
}

void Partido::atualizaAtributos(int nominais, int legenda){
    this->votosNominais += nominais;
    this->votosLegenda += legenda;
    
    this->votosTotais = this->votosNominais + this->votosLegenda;
}

std::set<const Candidato*> Partido::getCandidatosEleitos(){
    return this->candidatosEleitos;
}

int Partido::getNumeroPartido() const{

    return this->numeroPartido;

}

std::string Partido::getSiglaPartido() const{

    return this->siglaPartido;

}

int Partido::getVotosTotais() const{
    return this->votosTotais;
}

int Partido::getVotosNominais()const{
    return this->votosNominais;
}

int Partido::getVotosLegenda()const{
    return this->votosLegenda;
}

bool Partido::operator<(Partido const &outro)const{ 
    if(this->votosTotais != outro.votosTotais){
        return this->votosTotais > outro.votosTotais;
    }

    return this->numeroPartido < outro.numeroPartido;
}


void Partido::adicionarCandidato(const Candidato *candidato){

    this->candidatos.insert(candidato);

}

void Partido::adicionarCandidatoEleito(const Candidato *candidato){

    this->candidatosEleitos.insert(candidato);

}

const Candidato* Partido::candidatoMaisVotado()const {
   
    if (this->candidatos.empty()) {
        return nullptr;
    }

    auto comparador = [](const Candidato* a, const Candidato* b) {
        if(a->getVotos() != b->getVotos()){
            return a->getVotos() < b->getVotos();
        }
        return a->getIdade() < b->getIdade();
    };

    auto it_mais_votado = std::max_element(this->candidatos.begin(), this->candidatos.end(), comparador);

    return *it_mais_votado;
}


const Candidato* Partido::candidatoMenosVotado() const {
   
    if (this->candidatos.empty()) {
        return nullptr;
    }

    auto comparador = [](const Candidato* a, const Candidato* b) {
        if(a->getVotos() != b->getVotos()){
            return a->getVotos() < b->getVotos();
        }
        return a->getIdade() < b->getIdade();
    };

    auto it_mais_votado = std::min_element(this->candidatos.begin(), this->candidatos.end(), comparador);

    return *it_mais_votado;
}

