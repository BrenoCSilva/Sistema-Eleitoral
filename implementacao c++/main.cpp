#include <iostream>
#include <string>
#include <locale>
#include "Leitor.hpp"
#include "Eleicao.hpp"
#include "Relatorio.hpp"
#include "Data.hpp"

int main(int argc, char *argv[]) {

    if (argc != 5) {
        std::cerr << "Erro: Número incorreto de argumentos." << std::endl;
        std::cerr << "Uso: ./vereadores <codigo_municipio> <caminho_candidatos> <caminho_votacao> <data>" << std::endl;
        return 1; // saida de erro
    }

    try {
        std::locale brasilLocale("pt_BR.UTF-8");
        std::cout.imbue(brasilLocale);
    } catch (const std::runtime_error& e) {
        std::cerr << "Aviso: Nao foi possivel configurar o locale para pt_BR.UTF-8." << std::endl;
    }
    

    // argv[0] é ./vereadores
    int codigoMunicipio = std::stoi(argv[1]); 
    std::string caminhoCandidatos = argv[2];
    std::string caminhoVotacao = argv[3];
    std::string dataString = argv[4];



    try {
        Eleicao eleicao;
        Data dataEleicao(dataString);

        Leitor::carregarArquivoCandidatos(caminhoCandidatos, codigoMunicipio, eleicao, dataEleicao);
        Leitor::carregarArquivoVotacao(caminhoVotacao, codigoMunicipio, eleicao);
        Relatorio::gerarRelatorios(eleicao);
    
    } catch (const std::invalid_argument& e) {
        std::cerr << "Erro de argumento: Codigo do municipio deve ser um numero inteiro." << std::endl;
        return 1;
    } catch (const std::runtime_error& e) {
        std::cerr << "Erro de argumento: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Ocorreu um erro durante o processamento: " << e.what() << std::endl;
        return 1;
    }

    return 0; 
}