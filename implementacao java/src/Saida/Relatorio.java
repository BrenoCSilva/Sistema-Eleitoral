package Saida;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.text.NumberFormat;

import Dominio.Candidato;
import Dominio.Eleicao;
import Dominio.Partido;

public class Relatorio {

    private static  Locale brasil = new Locale("pt", "BR");
    private static  NumberFormat nfInt = NumberFormat.getInstance(brasil);
    private static  NumberFormat nfDouble = NumberFormat.getInstance(brasil);

    static{
        nfDouble.setMaximumFractionDigits(2);
        nfDouble.setMinimumFractionDigits(2);
    }
    
    public static void gerarRelatorios(Eleicao eleicao) {
        relatorio1NumeroDeVagas(eleicao);
        Map<Integer, Candidato> eleitosProporcional = relatorio2_vereadoresEleitos(eleicao);
        Map<Integer, Candidato> eleitosMajoritaria = relatorio3_maisVotados(eleicao);
        relatorio4_naoEleitosQueSeriam(eleicao, eleitosProporcional);
        relatorio5_beneficiadosProporcional(eleicao, eleitosProporcional, eleitosMajoritaria);
        relatorio6_votacaoPorPartido(eleicao);
        relatorio7_extremidadesDoPartido(eleicao);
        relatorio8_faixaEtaria(eleicao, eleitosProporcional);
        relatorio9_genero(eleicao);
        relatorio10_votosValidos(eleicao);
    }

    private static void relatorio1NumeroDeVagas(Eleicao eleicao) {
        System.out.println("Número de vagas: " + nfInt.format(eleicao.getQtdCandidatosEleitos()));
    }

    private static Map<Integer, Candidato> relatorio2_vereadoresEleitos(Eleicao eleicao) {
        
        Map<Integer, Candidato> candidatosEleitosProporcional = new LinkedHashMap<>();
        List<Candidato> candidatos = new ArrayList<>(eleicao.getCandidatos().values());
        Collections.sort(candidatos);
            System.out.println("\nVereadores eleitos:"); // RELATORIO 2
            int i=1;
            for(Candidato c : candidatos){

                if((c.getResultadoTurno() == true)){

                     if(c.getNumeroFederacao() != -1){
                        System.out.print(i +" - *");
                        System.out.println(c.getNomeUrna() + " (" + c.getPartido().getSiglaPartido() + ", " +  nfInt.format(c.getQtdVotosRecebidos()) + " votos)");
                        i++;
                    }
                     else{
                        System.out.print(i +" - ");
                        System.out.println(c.getNomeUrna() + " (" + c.getPartido().getSiglaPartido() + ", " +  nfInt.format(c.getQtdVotosRecebidos()) + " votos)");
                        i++;
                    }

                    candidatosEleitosProporcional.put(c.getNumeroCandidato(), c);

                    if(i > eleicao.getQtdCandidatosEleitos()){ // se os candidatos eleitos já foram identificados pode parar de varrer a lista de 3.000.000 milhoes de candidatos
                        break;
                    }

                }
            }

            return candidatosEleitosProporcional;
        }

    private static Map<Integer, Candidato> relatorio3_maisVotados(Eleicao eleicao) {
        
            Map<Integer, Candidato> candidatosEleitosMajoritaria = new LinkedHashMap<>();
            List<Candidato> candidatos = new ArrayList<>(eleicao.getCandidatos().values());
            Collections.sort(candidatos);
            System.out.println("\nCandidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):"); // RELATORIO 3
            int i=1;
            for(Candidato c : candidatos){  

                if(i <= eleicao.getQtdCandidatosEleitos()){

                    candidatosEleitosMajoritaria.put(c.getNumeroCandidato(), c);

                    if(c.getNumeroFederacao() != -1){
                        System.out.print(i +" - *");
                        System.out.println(c.getNomeUrna() + " (" + c.getPartido().getSiglaPartido() + ", " +  nfInt.format(c.getQtdVotosRecebidos()) + " votos)");
                        i++;
                    }

                    else{
                        System.out.print(i +" - ");
                        System.out.println(c.getNomeUrna() + " (" + c.getPartido().getSiglaPartido() + ", " +  nfInt.format(c.getQtdVotosRecebidos()) + " votos)");
                        i++;
                    }
                }
                else{
                    break;
                }

            }

            return candidatosEleitosMajoritaria;
        }

    private static void relatorio4_naoEleitosQueSeriam(Eleicao eleicao, Map<Integer, Candidato> candidatosEleitosProporcional) {

            List<Candidato> candidatos = new ArrayList<>(eleicao.getCandidatos().values());
            Collections.sort(candidatos);
            System.out.println("\nTeriam sido eleitos se a votação fosse majoritária, e não foram eleitos:\n (com sua posição no ranking de mais votados)"); // RELATORIO 4
            int i=1;
            for(Candidato c : candidatos){  

               if(i <= eleicao.getQtdCandidatosEleitos()){

                    if(candidatosEleitosProporcional.get(c.getNumeroCandidato()) == null){

                        if(c.getNumeroFederacao() != -1){
                            System.out.print(i +" - *");
                            System.out.println(c.getNomeUrna() + " (" + c.getPartido().getSiglaPartido() + ", " +  nfInt.format(c.getQtdVotosRecebidos()) + " votos)");

                        }

                        else{
                            System.out.print(i +" - ");
                            System.out.println(c.getNomeUrna() + " (" + c.getPartido().getSiglaPartido() + ", " +  nfInt.format(c.getQtdVotosRecebidos()) + " votos)");
                        
                        }
                    }
                    i++;
               }
               else{
                   break;
               }

            }
        }

    private static void relatorio5_beneficiadosProporcional(Eleicao eleicao, Map<Integer, Candidato> candidatosEleitosProporcional, Map<Integer, Candidato> candidatosEleitosMajoritaria){
        System.out.println("\nEleitos, que se beneficiaram do sistema proporcional:\n (com sua posição no ranking de mais votados)"); // RELATORIO 5
        List<Candidato> candidatos = new ArrayList<>(eleicao.getCandidatos().values());
        Collections.sort(candidatos);
        int i;
        for(Candidato c : candidatosEleitosProporcional.values()){  

         

            if(candidatosEleitosMajoritaria.get(c.getNumeroCandidato()) == null){

                i = candidatos.indexOf(c);
                i++;
                if(c.getNumeroFederacao() != -1){
                    System.out.print(i +" - *");
                    System.out.println(c.getNomeUrna() + " (" + c.getPartido().getSiglaPartido() + ", " +  nfInt.format(c.getQtdVotosRecebidos()) + " votos)");
                    
                }
                else{
                    System.out.print(i +" - ");
                    System.out.println(c.getNomeUrna() + " (" + c.getPartido().getSiglaPartido() + ", " +  nfInt.format(c.getQtdVotosRecebidos()) + " votos)");
                
                }
            }
        }
    }
    
    private static void relatorio6_votacaoPorPartido(Eleicao eleicao){
        List<Partido> partidos = new ArrayList<>(eleicao.getPartidos().values());
        Collections.sort(partidos);
        System.out.println("\nVotação dos partidos e número de candidatos eleitos:"); // RELATORIO 6
        int i=1;

        for(Partido p : partidos){
            
            String string = "";
            string += (i +" - ");
            string += (p.getSiglaPartido()+ " - " + p.getNumeroPartido() + ", " + nfInt.format(p.getVotosTotais()));

            if(p.getVotosTotais() > 1){
                string += " votos (";
            }
            else{
                string += " voto (";
            }
            
            string += nfInt.format(p.getVotosNominais());
            if(p.getVotosNominais() > 1){    
                string += (" nominais e ");
            }else{
                string += (" nominal e "); 
            }
            
            string += ( nfInt.format(p.getVotosLegenda()) + " de legenda), ");

            if(p.getCandidatosEleitos().size() > 1){
                string +=(nfInt.format(p.getCandidatosEleitos().size()) + " candidatos eleitos");
            }
            else{
                string +=(nfInt.format(p.getCandidatosEleitos().size()) + " candidato eleito");
            }
            
            System.out.println(string);
            i++;
        }

    }

    private static void relatorio7_extremidadesDoPartido(Eleicao eleicao){
        List<Partido> partidos = new ArrayList<>(eleicao.getPartidos().values());
        Collections.sort(partidos);
        
        System.out.println("\nPrimeiro e último colocados de cada partido:");

        Comparator<Partido> votoNominal = Comparator.comparingInt(Partido::candidatoMaisVotado).reversed().thenComparing(Partido::getNumeroPartido);
        partidos.sort(votoNominal);


        int i=1;
        
        for(Partido p : partidos){

            List<Candidato> candidatosPartido = new ArrayList<>(p.getCandidatos());


            if (candidatosPartido.size() > 1 ) { // o partido tem que ter no minimo 2 candidatos para apresentar seus extremos
   
                Collections.sort(candidatosPartido);
                
                Candidato maisVotado = candidatosPartido.get(0);
                Candidato menosVotado = candidatosPartido.get(candidatosPartido.size() - 1);

                if(p.getVotosNominais() > 0){

                    System.out.print(i +" - ");
                    System.out.print(p.getSiglaPartido() + " - " + p.getNumeroPartido() + ", " + maisVotado.getNomeUrna() + "(" + maisVotado.getNumeroCandidato() + ", " + nfInt.format(maisVotado.getQtdVotos()) + " votos) / " + menosVotado.getNomeUrna() + "(" + menosVotado.getNumeroCandidato() + ", ");
                    
                    if(menosVotado.getQtdVotos() > 1){
                        System.out.println(nfInt.format(menosVotado.getQtdVotos()) + " votos)");
                    }
                    else{
                        System.out.println(nfInt.format(menosVotado.getQtdVotos()) + " voto)");
                    }
                }
            }
            i++;

            
        }
    }

    private static void relatorio8_faixaEtaria(Eleicao eleicao,  Map<Integer, Candidato> candidatosEleitosProporcional){
        int c1 = 0, c2=0, c3=0, c4=0, c5=0;
        for(Candidato c : candidatosEleitosProporcional.values()){

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
        if(candidatosEleitosProporcional.size() > 0){
            divisor = candidatosEleitosProporcional.size();
        }

        System.out.println("\nEleitos, por faixa etária (na data da eleição):");
        System.out.println("      Idade < 30: " + nfInt.format(c1) + "(" + nfDouble.format(c1 * 100.0 / divisor) + "%)");
        System.out.println("30 <= Idade < 40: " + nfInt.format(c2) + "(" + nfDouble.format(c2 * 100.0 / divisor) + "%)");
        System.out.println("40 <= Idade < 50: " + nfInt.format(c3) + "(" + nfDouble.format(c3 * 100.0 / divisor) + "%)");
        System.out.println("50 <= Idade < 60: " + nfInt.format(c4) + "(" + nfDouble.format(c4 * 100.0 / divisor) + "%)");
        System.out.println("60 <= Idade     : " + nfInt.format(c5) + "(" + nfDouble.format(c5 * 100.0 / divisor) + "%)");
    }
        
    private static void relatorio9_genero(Eleicao eleicao){
    
        int totalGenero = eleicao.getQtdMasculino() + eleicao.getQtdFeminino();
        double divisor = totalGenero;
        if(totalGenero == 0){
            divisor = 1.0;
        }
        System.out.println("\nEleitos, por gênero:");
        System.out.println("Feminino:  " + eleicao.getQtdFeminino() + " (" + nfDouble.format((eleicao.getQtdFeminino()*1.0/ divisor *100.0))  + "%)");
        System.out.println("Masculino: " + eleicao.getQtdMasculino() + " (" + nfDouble.format(eleicao.getQtdMasculino()*1.0 / divisor *100.0) + "%)");

    }
    
    private static void relatorio10_votosValidos(Eleicao eleicao){

        int totalVotos = eleicao.getQtdVotosLegenda() + eleicao.getQtdVotosNominais();
        double divisor = totalVotos;
        if(totalVotos == 0){
            divisor = 1.0;
        }
        double porcentagemNominal = eleicao.getQtdVotosNominais() * 1.0 / divisor * 1.0;
        double porcentagemLegenda = eleicao.getQtdVotosLegenda() * 1.0 / divisor * 1.0;

        System.out.println("\nTotal de votos válidos:    " + nfInt.format(totalVotos));
        System.out.println("Total de votos nominais:   " + nfInt.format(eleicao.getQtdVotosNominais()) + " (" + nfDouble.format(porcentagemNominal * 100.0) + "%)");
        System.out.println("Total de votos de legenda: " +  nfInt.format(eleicao.getQtdVotosLegenda()) + " (" + nfDouble.format(porcentagemLegenda * 100.0) + "%)");
    }
        
}
