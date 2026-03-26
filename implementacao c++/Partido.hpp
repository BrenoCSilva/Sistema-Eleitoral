#ifndef PARTIDO_HPP
#define PARTIDO_HPP

#include <iostream>
#include <set>

class Candidato;

class Partido{

     int numeroPartido;
     std::string siglaPartido;
     int votosNominais;
     int votosLegenda;
     int votosTotais;
     
    std::set<const Candidato*>candidatos;
    std::set<const Candidato*>candidatosEleitos;

public:

    Partido(int numeroPartido, const std::string &siglaPartido);

    void atualizaAtributos(int nominais, int legenda);

    int getNumeroPartido() const;
    std::string getSiglaPartido() const;
    std::set<const Candidato*> getCandidatosEleitos();
    int getVotosTotais() const;
    int getVotosNominais()const;
    int getVotosLegenda()const;
    bool operator<(Partido const &outro)const;


    void adicionarCandidato(const Candidato *candidato);
    void adicionarCandidatoEleito(const Candidato *candidato);

    const Candidato* candidatoMaisVotado() const;
    const Candidato* candidatoMenosVotado() const;
 

};



#endif