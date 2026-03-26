#include "Candidato.hpp"
#include "Partido.hpp"

Candidato::Candidato(int codigoMunicipio, int codigoCargo, int numeroCandidato, const std::string &nomeUrna, int numeroFederacao, SituacaoCandidato resultadoTurno, Genero &genero,  Partido *partido, Data& dataNascimento,  Data &dataAtual)
    : codigoMunicipio(codigoMunicipio),      
      codigoCargo(codigoCargo),             
      numeroCandidato(numeroCandidato),      
      nomeUrna(nomeUrna),
      numeroFederacao(numeroFederacao),
      dataNascimento(dataNascimento),     
      resultadoTurno(resultadoTurno),
      genero(genero),
      partido(partido),
      qtdVotosRecebidos(0)                 
{
    this->idade = calculaIdade(dataAtual);
}

const std::string& Candidato::getNome() const{
    return this->nomeUrna;
}

int Candidato::getVotos() const{
    return this->qtdVotosRecebidos;
}

int Candidato::getNumeroCandidato() const{
    return this->numeroCandidato;
}

int Candidato::getNumeroFederacao() const{
    return this->numeroFederacao;
}

Partido* Candidato::getPartido() const{
    return this->partido;
}

SituacaoCandidato Candidato::getResultadoTurno() const{
    return this->resultadoTurno;
}

void Candidato::incrementarVotos(int votos){

    this->qtdVotosRecebidos += votos;
    this->partido->atualizaAtributos(votos, 0);
}


bool Candidato::operator<(Candidato const &outro)const{

    if (this->getVotos() != outro.getVotos()) {

        return this->getVotos() > outro.getVotos();
    }

    return this->getIdade() > outro.getIdade();
 }

bool Candidato::operator==(Candidato const&outro) const{
    return this->getNumeroCandidato() == outro.getNumeroCandidato();
}

int Candidato::getIdade() const{
    return this->idade;
}

int Candidato::calculaIdade(const Data& dataAtual) const{
 
    auto time_point_nascimento = this->dataNascimento.getTimePoint();
    auto time_point_eleicao = dataAtual.getTimePoint();

    std::time_t t_nascimento = std::chrono::system_clock::to_time_t(time_point_nascimento);
    std::time_t t_eleicao = std::chrono::system_clock::to_time_t(time_point_eleicao);

    std::tm tm_nascimento = *std::localtime(&t_nascimento);
    std::tm tm_eleicao = *std::localtime(&t_eleicao);

    int anos = tm_eleicao.tm_year - tm_nascimento.tm_year;
    
    if (tm_eleicao.tm_mon < tm_nascimento.tm_mon || 
       (tm_eleicao.tm_mon == tm_nascimento.tm_mon && tm_eleicao.tm_mday < tm_nascimento.tm_mday)) {
        anos--; 
    }
    
    return anos;
}