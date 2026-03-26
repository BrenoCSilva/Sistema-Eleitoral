#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "Eleicao.hpp"
#include "Leitor.hpp"
#include "Candidato.hpp"
#include "Partido.hpp"
#include "SituacaoCandidato.hpp"



namespace { 

    std::string limparAspas(const std::string& string) {
        
      
        if (string.length() >= 2 && string.front() == '"' && string.back() == '"') {
           
            return string.substr(1, string.length() - 2);
        }
        
        return string;
    }

    std::string iso_8859_1_to_utf8(std::string &str){
    
        std::string strOut;
        for (std::string::iterator it = str.begin(); it != str.end(); ++it)
        {
          uint8_t ch = *it;
          if (ch < 0x80)
          {
            strOut.push_back(ch);
          }
          else
          {
 
            strOut.push_back(0b11000000 | (ch >> 6));
        
            strOut.push_back(0b10000000 | (ch & 0b00111111));
          }
        }
        return strOut;
    }

}

void Leitor::carregarArquivoCandidatos(std::string caminho, int municipioInteresse, Eleicao&eleicao, Data &dataAtual) {
    
    std::ifstream in(caminho);
    
    int qtd=0;
    std::string linha;
    std::getline(in, linha); // Descarta o cabeçalho

    while (std::getline(in, linha)) {
        
        std::stringstream extrair(linha);
        std::string coluna;
        std::vector<std::string> colunas;

    
        while (std::getline(extrair, coluna, ';')) {
            colunas.push_back(coluna);
        }

        if (colunas.size() > 48) {
               
            int codigoMunicipio = std::stoi(limparAspas(colunas[11]));
            int codigoCargo = std::stoi(limparAspas(colunas[13]));
            int numeroCandidato = std::stoi(limparAspas(colunas[16]));
            std::string nomeUrna = limparAspas(colunas[18]);
            int numeroPartido = std::stoi(limparAspas(colunas[25]));
            std::string siglaPartido = limparAspas(colunas[26]);
            int numeroFederacao = std::stoi(limparAspas(colunas[28]));
            std::string dataNascimento = limparAspas(colunas[36]);
            int codigoGenero = std::stoi(limparAspas(colunas[38]));
            int codigoResultadoTurno = std::stoi(limparAspas(colunas[48]));
            
            std::string nomeUrnaUTF = iso_8859_1_to_utf8(nomeUrna);
            std::string siglaPartidoUTF = iso_8859_1_to_utf8(siglaPartido);

            SituacaoCandidato situacao = converteSituacao(codigoResultadoTurno);

            Data dataNascimentoformatada(dataNascimento);
            
            Genero genero = generoCandidato(codigoGenero);
            
            Partido *partido = eleicao.criaPartido(numeroPartido, siglaPartidoUTF);
            
            if(municipioInteresse == codigoMunicipio && codigoCargo == 13 && codigoResultadoTurno != -1){
                
                Candidato *candidato = eleicao.criaCandidato(codigoMunicipio, codigoCargo,numeroCandidato, nomeUrnaUTF,  numeroFederacao, situacao, genero, partido, dataNascimentoformatada, dataAtual);
                qtd++;
                                
                if(situacao == SituacaoCandidato::ELEITO_POR_QP || situacao == SituacaoCandidato::ELEITOR_POR_MEDIA){
    
                    eleicao.incrementarVereadoresEleitos();
                    partido->adicionarCandidatoEleito(candidato);

                    if(genero == Genero::MASCULINO){
                    eleicao.incrementrarQtdMasculino();

                    }
                    else if(genero == Genero::FEMININO){
                        eleicao.incrementrarQtdFeminino();
                    }
                }
                
               
            }
        }
    }
    in.close();
}


void  Leitor::carregarArquivoVotacao(std::string caminho, int municipioInteresse,  Eleicao &eleicao){
  
    std::ifstream in(caminho);
    std::string linha;
    std::getline(in, linha); // Descarta o cabeçalho

    while (std::getline(in, linha)) {
        
        std::stringstream extrair(linha);
        std::string coluna;
        std::vector<std::string> colunas;

    
        while (std::getline(extrair, coluna, ';')) {
            colunas.push_back(coluna);
        }
        if (colunas.size() > 21) {
               
            int codigoMunicipio = std::stoi(limparAspas(colunas[13]));
            int codigoCargo = std::stoi(limparAspas(colunas[17]));
            int voto = std::stoi(limparAspas(colunas[19]));
            int qtd_votos = std::stoi(limparAspas(colunas[21]));
            
            if(codigoMunicipio == municipioInteresse && codigoCargo == 13){
                
                if(voto < 95 ){  //voto branco, nulo ou de legenda
                    
                    Partido *partido = eleicao.getPartido(voto);
                    if(partido != nullptr){  //  se nao for voto nulo ou branco ou de um partido nao cadastrado
                       
                        partido->atualizaAtributos(0, qtd_votos);
                        eleicao.incrementarQtdLegenda(qtd_votos);
                  
                    }
                    

                }

                else if(voto > 100){ // votoNominal
                   
                   try {
                        Candidato* candidatoEncontrado = eleicao.getCandidato(voto);
                        candidatoEncontrado->incrementarVotos(qtd_votos);
                         eleicao.incrementarQtdNominal(qtd_votos);

                    } catch (const std::out_of_range& e) {
                      
                    }
                      
        
                }
            }
        }
    }
    in.close();
}