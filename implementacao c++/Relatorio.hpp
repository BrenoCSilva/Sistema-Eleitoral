#ifndef RELATORIO_HPP
#define RELATORIO_HPP

#include <iostream>
#include "Eleicao.hpp"


class Relatorio{



public:
    static void gerarRelatorios(Eleicao &eleicao);
    static std::map<int, Candidato>  relatorio2_vereadoresEleitos(Eleicao &eleicao);
    static std::map<int, Candidato>  relatorio3_maisVotados(Eleicao &eleicao);
    static void relatorio4_naoEleitosQueSeriam(Eleicao &eleicao, std::map<int, Candidato> &candidatosEleitosProporcional);
    static void relatorio5_beneficiadosProporcional(Eleicao &eleicao, std::map<int, Candidato> &candidatosEleitosProporcional, std::map<int, Candidato> &candidatosEleitosMajoritaria);
    static void  relatorio1NumeroDeVagas(Eleicao &eleicao);
    static void relatorio6_votacaoPorPartido(Eleicao &eleicao);
    static void relatorio7_extremidadesDoPartido(Eleicao &eleicao);
    static void relatorio8_faixaEtaria( Eleicao& eleicao, std::map<int,Candidato>& candidatosEleitosProporcional);
    static void relatorio9_genero(Eleicao& eleicao);
    static void relatorio10_votosValidos( Eleicao& eleicao);
};

#endif