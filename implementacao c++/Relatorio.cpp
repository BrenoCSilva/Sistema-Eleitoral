#include "Relatorio.hpp"
#include <vector>
#include <algorithm>
#include <iterator>  // Necessário para std::distance
#include "Candidato.hpp"
#include "Partido.hpp"
#include <locale>
#include <iomanip> 


void Relatorio::gerarRelatorios(Eleicao &eleicao){

    relatorio1NumeroDeVagas(eleicao);
    std::map<int, Candidato> candidatosEleitosProporcional = relatorio2_vereadoresEleitos(eleicao);
    std::map<int, Candidato> candidatosEleitosMajoritaria = relatorio3_maisVotados(eleicao);
    relatorio4_naoEleitosQueSeriam(eleicao, candidatosEleitosProporcional) ;
    relatorio5_beneficiadosProporcional(eleicao, candidatosEleitosProporcional, candidatosEleitosMajoritaria);
    relatorio6_votacaoPorPartido(eleicao);
    relatorio7_extremidadesDoPartido(eleicao);
    relatorio8_faixaEtaria(eleicao, candidatosEleitosProporcional);
    relatorio9_genero(eleicao);
    relatorio10_votosValidos(eleicao);
}


void Relatorio::relatorio1NumeroDeVagas(Eleicao &eleicao){

    std::cout << "\nNúmero de vagas: " << eleicao.getQtdVereadoresEleitos() << std::endl;
 }


std::map<int, Candidato> Relatorio::relatorio2_vereadoresEleitos(Eleicao &eleicao){
    
    std::cout << "\nVereadores eleitos: " << std::endl;
    std::vector<Candidato> candidatos;
    std::map<int, Candidato> candidatosEleitosProporcional;
    
    for(auto const &par : eleicao.getCandidatos()){
       candidatos.push_back(*(par.second));
    }

    std::sort(candidatos.begin(), candidatos.end());

    int i=1;
    for(Candidato &candidato : candidatos){
        
        if(candidato.getResultadoTurno() == SituacaoCandidato::ELEITO_POR_QP || candidato.getResultadoTurno() == SituacaoCandidato::ELEITOR_POR_MEDIA){
    
            if(i > eleicao.getQtdVereadoresEleitos()){
                break;
            }
          
            if(candidato.getNumeroFederacao() != -1){
                std::cout << i << " - *";
                std::cout << candidato.getNome() << " (" << candidato.getPartido()->getSiglaPartido() << ", " << candidato.getVotos() << " votos)" << std::endl;
                i++;
            }else{
                std::cout << i << " - ";
                std::cout << candidato.getNome() << " (" << candidato.getPartido()->getSiglaPartido() << ", " << candidato.getVotos() << " votos)" << std::endl;
                i++;
            }
            candidatosEleitosProporcional.insert({candidato.getNumeroCandidato(), candidato});
        }
    }

    return candidatosEleitosProporcional;
}


std::map<int, Candidato> Relatorio::relatorio3_maisVotados(Eleicao &eleicao){

    std::map<int, Candidato> candidatosEleitosMajoritaria;
    std::vector<Candidato> candidatos;
    std::cout << "\nCandidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):" << std::endl;

    for(auto const &par : eleicao.getCandidatos()){
        candidatos.push_back(*(par.second));
    }
    std::sort(candidatos.begin(), candidatos.end());

    int i=1;
    for(Candidato &candidato : candidatos){

        if(i > eleicao.getQtdVereadoresEleitos()){
            break;
        }

        std::cout << i << " - ";

        if(candidato.getNumeroFederacao() != -1){
            std::cout << "*";
        }
       
        std::cout << candidato.getNome() << " (" << candidato.getPartido()->getSiglaPartido() << ", " << candidato.getVotos() << " votos)" << std::endl;
        i++;
        candidatosEleitosMajoritaria.insert({candidato.getNumeroCandidato(), candidato});
    }

    return candidatosEleitosMajoritaria;
}


void Relatorio::relatorio4_naoEleitosQueSeriam(Eleicao &eleicao, std::map<int, Candidato> &candidatosEleitosProporcional){

    std::cout << "\nTeriam sido eleitos se a votação fosse majoritária, e não foram eleitos:\n (com sua posição no ranking de mais votados)" << std::endl;
    std::vector<Candidato> candidatos;

   for(auto const &par : eleicao.getCandidatos()){
        candidatos.push_back(*(par.second));
    }

    std::sort(candidatos.begin(), candidatos.end());

    int i=1;
    for(Candidato &candidato : candidatos){
            
        if(i > eleicao.getQtdVereadoresEleitos()){
            break;
        }
        auto it = candidatosEleitosProporcional.find(candidato.getNumeroCandidato());
        if(it == candidatosEleitosProporcional.end()){
            std::cout << i << " - ";
            if (candidato.getNumeroFederacao() != -1) {
                std::cout << "*";
            }

            std::cout << candidato.getNome() << " (" << candidato.getPartido()->getSiglaPartido() << ", "<< candidato.getVotos() << " votos)" << std::endl;
        }
        i++;       
    }
}


void Relatorio::relatorio5_beneficiadosProporcional(Eleicao &eleicao, std::map<int, Candidato> &candidatosEleitosProporcional, std::map<int, Candidato> &candidatosEleitosMajoritaria){


    std::cout << "\nEleitos, que se beneficiaram do sistema proporcional:\n (com sua posição no ranking de mais votados)\n"; // RELATORIO 5
    std::vector<Candidato> candidatos;
    std::vector<Candidato> candidatosProporcional;

    for(auto const &par : eleicao.getCandidatos()){
        candidatos.push_back(*(par.second));
    }

    for(auto const &par : candidatosEleitosProporcional){
        candidatosProporcional.push_back(par.second);
    }

   std::sort(candidatos.begin(), candidatos.end());
   std::sort(candidatosProporcional.begin(), candidatosProporcional.end());

   for(Candidato &candidatoProporcional : candidatosProporcional){
        
        auto it = candidatosEleitosMajoritaria.find(candidatoProporcional.getNumeroCandidato());
        if(it == candidatosEleitosMajoritaria.end()){
            
            
            auto candidadoBusca = std::find(candidatos.begin(), candidatos.end(), candidatoProporcional);

            int indice = std::distance(candidatos.begin(), candidadoBusca);

            std::cout << indice + 1  << " - "; 
            if (candidatoProporcional.getNumeroFederacao() != -1) {
                std::cout << "*";
            }
            std::cout << candidatoProporcional.getNome() << " (" 
                    << candidatoProporcional.getPartido()->getSiglaPartido() << ", "
                    << candidatoProporcional.getVotos() << " votos)" << std::endl;
        }      

    }
       

}

void Relatorio::relatorio6_votacaoPorPartido(Eleicao &eleicao){
    
    std::vector<Partido> partidos;
    
    for(auto const &par : eleicao.getPartidos()){
        partidos.push_back(*(par.second));
    }
    
    std::sort(partidos.begin(), partidos.end());
    std::cout << "\nVotação dos partidos e número de candidatos eleitos:\n"; // RELATORIO 6
    
    int i=1;
    
    for(Partido &partido : partidos){
        
        std::cout << i << " - " << partido.getSiglaPartido() << " - " << partido.getNumeroPartido() << ", " << partido.getVotosTotais();

        if (partido.getVotosTotais() > 1) {
            std::cout << " votos (";
        } else {
            std::cout << " voto (";
        }

        std::cout << partido.getVotosNominais();

      
        if (partido.getVotosNominais() > 1) {    
            std::cout << " nominais e "; 
            
        } else {
            std::cout << " nominal e ";
        }

        std::cout << partido.getVotosLegenda() << " de legenda), ";

        std::cout << partido.getCandidatosEleitos().size();

        if (partido.getCandidatosEleitos().size() >1) {
            std::cout << " candidatos eleitos\n";
        } else {
            std::cout << " candidato eleito\n";
        }
        i++;
    }
}



bool cmpMaisVotado(const Partido& p1, const Partido& p2) {
    const Candidato* maisVotado1 = p1.candidatoMaisVotado();
    const Candidato* maisVotado2 = p2.candidatoMaisVotado();

    // nenhum tem candidatos, ordena pelo número do partido
    if (!maisVotado1 && !maisVotado2) {
        return p1.getNumeroPartido() < p2.getNumeroPartido();
    }

    // apenas p1 tem candidato
    if (maisVotado1 && !maisVotado2) return true;

    // apenas p2 tem candidato
    if (!maisVotado1 && maisVotado2) return false;

    // ambos tem candidatos
    if (maisVotado1->getVotos() != maisVotado2->getVotos()) {
        return maisVotado1->getVotos() > maisVotado2->getVotos(); // decrescente
    }

    // empate: desempata pelo número do partido (crescente)
    return p1.getNumeroPartido() < p2.getNumeroPartido();
}


void Relatorio::relatorio7_extremidadesDoPartido(Eleicao &eleicao){

    std::vector<Partido*> partidos;

    for (auto const& par : eleicao.getPartidos()) {
        partidos.push_back(par.second);
    }

    std::stable_sort(partidos.begin(), partidos.end(), [](Partido* p1, Partido* p2) {
        return cmpMaisVotado(*p1, *p2);
    });


    std::cout << "\nPrimeiro e último colocados de cada partido:\n"; // RELATORIO 7

    int i=1;
    std::locale brasilLocale("pt_BR.UTF-8");

    for(Partido *partido : partidos){
        
        const Candidato *maisVotado = partido->candidatoMaisVotado();
        const Candidato *menosVotado = partido->candidatoMenosVotado();
        
        if(maisVotado != nullptr && menosVotado != nullptr && maisVotado != menosVotado){
            
            std::cout.imbue(std::locale::classic());
            
            std::cout << i;
            std::cout << " - " << partido->getSiglaPartido() << " - " << partido->getNumeroPartido() 
            << ", " << maisVotado->getNome() << " ("; 
            std::cout << maisVotado->getNumeroCandidato() ;
            
            std::cout.imbue(brasilLocale);
            
            std::cout << ", " <<
            maisVotado->getVotos() << " votos) / " << menosVotado->getNome() << " (" ;

            std::cout.imbue(std::locale::classic());
            std::cout <<menosVotado->getNumeroCandidato() << ", " ;
            std::cout.imbue(brasilLocale);
            std::cout <<  menosVotado->getVotos();
            
            if(menosVotado->getVotos() > 1){
                std::cout << " votos)\n";
            }
            else{
                std::cout << " voto)\n";
            }
            i++;
        }
    
    }
}


void Relatorio::relatorio8_faixaEtaria( Eleicao& eleicao,  std::map<int,Candidato>& candidatosEleitosProporcional){

    int c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0;
    for (const auto& par : candidatosEleitosProporcional) {
 
    const Candidato& c = par.second;

    if (c.getIdade() < 30) {
        c1++;
    } else if (c.getIdade() < 40) {
        c2++;
    } else if (c.getIdade() < 50) {
        c3++;
    } else if (c.getIdade() < 60) {
        c4++;
    } else {
        c5++;
    }
}

    double divisor = 1.0;
    if (!candidatosEleitosProporcional.empty()) {
        divisor = candidatosEleitosProporcional.size();
    }

    std::cout << "\nEleitos, por faixa etária (na data da eleição):" << std::endl;

    std::cout << std::fixed << std::setprecision(2);

    std::cout << "      Idade < 30: " << c1 << " (" << (c1 * 100.0 / divisor) << "%)" << std::endl;
    std::cout << "30 <= Idade < 40: " << c2 << " (" << (c2 * 100.0 / divisor) << "%)" << std::endl;
    std::cout << "40 <= Idade < 50: " << c3 << " (" << (c3 * 100.0 / divisor) << "%)" << std::endl;
    std::cout << "50 <= Idade < 60: " << c4 << " (" << (c4 * 100.0 / divisor) << "%)" << std::endl;
    std::cout << "60 <= Idade     : " << c5 << " (" << (c5 * 100.0 / divisor) << "%)" << std::endl;
}


void Relatorio::relatorio9_genero(Eleicao& eleicao){
    
    int totalGenero = eleicao.getQtdMasculino() + eleicao.getQtdFeminino();
    double divisor = totalGenero;

    if (totalGenero == 0) {
        divisor = 1.0;
    }

    std::cout << "\nEleitos, por gênero:" << std::endl;

    std::cout << std::fixed << std::setprecision(2);

    std::cout << "Feminino:  " << eleicao.getQtdFeminino() << " ("
              << (eleicao.getQtdFeminino() * 100.0 / divisor) << "%)" << std::endl;

    std::cout << "Masculino: " << eleicao.getQtdMasculino() << " ("
              << (eleicao.getQtdMasculino() * 100.0 / divisor) << "%)" << std::endl;
}


void Relatorio::relatorio10_votosValidos(Eleicao& eleicao){
   
    int totalVotos = eleicao.getQtdVotosLegenda() + eleicao.getQtdVotosNominais();
    double divisor = totalVotos;

    if (totalVotos == 0) {
        divisor = 1.0;
    }

    double porcentagemNominal = eleicao.getQtdVotosNominais() * 100.0 / divisor;
    double porcentagemLegenda = eleicao.getQtdVotosLegenda() * 100.0 / divisor;

    std::cout << std::fixed << std::setprecision(2);

    std::cout << "\nTotal de votos válidos:    " << totalVotos << std::endl;
    std::cout << "Total de votos nominais:   " << eleicao.getQtdVotosNominais() << " (" << porcentagemNominal << "%)" << std::endl;
    std::cout << "Total de votos de legenda: " << eleicao.getQtdVotosLegenda() << " (" << porcentagemLegenda << "%)" << std::endl;
}

