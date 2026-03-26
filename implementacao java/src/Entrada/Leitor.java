package Entrada;
import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;

import Dominio.Candidato;
import Dominio.Eleicao;
import Dominio.Partido;
import Dominio.Genero;


public class Leitor {
    
    public static void carregarArquivoCandidatos(String caminho, int municipioInteresse, Eleicao eleicao, LocalDate dataAtual) throws IOException, DateTimeParseException {

        try (BufferedReader br = Files.newBufferedReader(Paths.get(caminho), StandardCharsets.ISO_8859_1)) {
            
            String line;
            br.readLine();

            while ((line = br.readLine()) != null) {
               
                String[] coluna = line.split(";");

                
                int codigoMunicipio = Integer.parseInt(coluna[11].replace("\"", ""));// 11
                int codigoCargo = Integer.parseInt(coluna[13].replace("\"", ""));// 13
                int numeroCandidato = Integer.parseInt(coluna[16].replace("\"", ""));// 16
                String nomeUrna = coluna[18].replace("\"", "");// 18
                int numeroPartido = Integer.parseInt(coluna[25].replace("\"", ""));// 25
                String siglaPartido = coluna[26].replace("\"", ""); // 26
                int numeroFederacao = Integer.parseInt(coluna[28].replace("\"", "")); // 28
                String dataNascimento  = coluna[36].replace("\"", ""); // 36
                int codigoGenero = Integer.parseInt(coluna[38].replace("\"", "")); // 38
                int codigoResultadoTurno = Integer.parseInt(coluna[48].replace("\"", "")); //48
                
                //                                 formatações
                
                
                DateTimeFormatter formatacacaoData = DateTimeFormatter.ofPattern("dd/MM/yyyy");
                LocalDate dataNascimentoFormatada = LocalDate.parse(dataNascimento,formatacacaoData);
        
        
                Genero genero = Genero.generoCandidato(codigoGenero);

                boolean resultadoTurno;
                
                if(codigoResultadoTurno == 2 || codigoResultadoTurno == 3){
                    resultadoTurno = true;
                }else{
                    resultadoTurno = false;
                }


                Partido partido = eleicao.criaPartido(numeroPartido, siglaPartido);
                
                if(municipioInteresse == codigoMunicipio && codigoCargo == 13 && codigoResultadoTurno != -1){
                    
                    Candidato candidato = eleicao.criaCandidato(codigoMunicipio, codigoCargo, numeroCandidato, nomeUrna, numeroFederacao, dataNascimentoFormatada, resultadoTurno, genero, partido, dataAtual);
                    
                    
                    if(resultadoTurno == true){ // se o candidato foi eleito
                        eleicao.incrementaQtdCandidatosEleitos();
                        partido.adicionarCandidatoEleito(candidato);



                        if(codigoGenero == 2){
                            eleicao.incrementrarQtdMasculino();

                        }
                        else if(codigoGenero == 4){
                            eleicao.incrementrarQtdFeminino();
                        }
                        
                    }   
                }


            } 

        }
    }



    public static void carregarArquivoVotacao(String caminho, int municipioInteresse,  Eleicao eleicao) throws IOException{

        try (BufferedReader br = Files.newBufferedReader(Paths.get(caminho), StandardCharsets.ISO_8859_1)) {
            
            String line;
            br.readLine();
          
            while ((line = br.readLine()) != null) {
               
                String[] coluna = line.split(";");



                int codigo_municipio = Integer.parseInt(coluna[13].replace("\"", ""));// 13
                int codigo_cargo = Integer.parseInt(coluna[17].replace("\"", ""));// 17
                int voto = Integer.parseInt(coluna[19].replace("\"", ""));// 19
                int qtd_votos = Integer.parseInt(coluna[21].replace("\"", ""));// 21


             

                if(codigo_municipio == municipioInteresse && codigo_cargo == 13){
                    
                    if(voto < 95 ){  //voto branco, nulo ou de legenda

                        Partido partido = eleicao.getPartido(voto);
                        if(partido != null){  //  se nao for voto nulo ou branco ou de um partido nao cadastrado
                           
                            partido.atualizaAtributos(0, qtd_votos);
                            eleicao.incrementarQtdLegenda(qtd_votos);

                        }
    
                    }
    
                    else if(voto > 100){ // votoNominal
                         Candidato candidato = eleicao.getCandidato(voto);
                         if(candidato != null){  //  se nao for um candidato cadastrado
                             candidato.incrementarVotos(qtd_votos);
                         }
                         eleicao.incrementarQtdVotosNominais(qtd_votos);
                    }

                    
                }
        
            }                
    
        } 

    }
}
