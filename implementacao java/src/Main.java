
import java.io.IOException;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;

import Dominio.Eleicao;
import Entrada.Leitor;
import Saida.Relatorio;

public class Main {
    public static void main(String[] args) {
        
            // validacao da quantidade de argumentos na entrada

        if (args.length != 4) {
            System.err.println("Erro: Número incorreto de argumentos. Foram fornecidos " + args.length + ", mas são esperados 4.");
            System.out.println("Para execução correta é necessário seguir o padrão estabelecido de 4 argumentos: java -jar vereadores.jar <codigo_municipio> <arquivo_candidatos> <arquivo_votacao> <data>");
            return;
        }

        int  codigoMunicipio;
        LocalDate dataEleicao;

        try {
            codigoMunicipio = Integer.parseInt(args[0]);
            DateTimeFormatter formatador = DateTimeFormatter.ofPattern("dd/MM/yyyy");
            dataEleicao = LocalDate.parse(args[3], formatador);

        } catch (NumberFormatException e) {
            System.err.println("ERRO DE FORMATO: O código do município deve ser um número inteiro.");
            System.err.println("Valor recebido: '" + args[0] + "'");
            return; 
        } catch (DateTimeParseException e) {
            System.err.println("ERRO DE FORMATO: A data da eleição não está no formato esperado 'dd/MM/yyyy'.");
            System.err.println("Valor recebido: '" + args[3] + "'");
            return; 
        }

        String arquivoCandidatos = args[1];
        String arquivoVotacao = args[2];

        try {
            Eleicao eleicao = new Eleicao();
            Leitor.carregarArquivoCandidatos(arquivoCandidatos, codigoMunicipio, eleicao, dataEleicao);
            Leitor.carregarArquivoVotacao(arquivoVotacao, codigoMunicipio, eleicao);
            Relatorio.gerarRelatorios(eleicao);

        } catch (IOException e) {
            System.err.println("ERRO DE ARQUIVO: Não foi possível ler um dos arquivos.");
            System.err.println("Verifique os caminhos: '" + arquivoCandidatos + "', '" + arquivoVotacao + "'");
            e.getMessage();
        } catch (Exception e) {
           
            System.err.println("ERRO INESPERADO durante o processamento dos arquivos.");
            e.printStackTrace();
        }
    }
}

