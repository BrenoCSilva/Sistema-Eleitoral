package Dominio;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Set;


public class Partido implements Comparable<Partido>{
    private int numeroPartido;
    private String siglaPartido;
    private int votosNominais;
    private int votosLegenda;
    private int votosTotais;
    private Set<Candidato> candidatosEleitos = new HashSet<>();
    private Set<Candidato> candidatos = new HashSet<>();

    public Partido(int numeroPartido, String siglaPartido){
        this.numeroPartido = numeroPartido;
        this.siglaPartido = siglaPartido;
    }

    public void atualizaAtributos(int nominais, int legenda){

        this.votosNominais += nominais;
        this.votosLegenda += legenda;
        
        this.votosTotais = this.votosNominais + this.votosLegenda;
    }

    public void adicionarCandidatoEleito(Candidato candidato){
        this.candidatosEleitos.add(candidato);

    }

    public void adicionarCandidato(Candidato candidato){
        this.candidatos.add(candidato);

    }

    public int candidatoMaisVotado(){

        if (this.candidatos.isEmpty()) {
            return -1; 
        }

        List<Candidato> listaOrdenavel = new ArrayList<>(this.candidatos);
        Collections.sort(listaOrdenavel);    

        return listaOrdenavel.get(0).getQtdVotosRecebidos();

    }


    public Set<Candidato> getCandidatos() {
        return new HashSet<>(this.candidatos);
    }


    public Set<Candidato> getCandidatosEleitos(){
        return new HashSet<>(this.candidatosEleitos);
    } 
    

    public String getSiglaPartido() {
        return siglaPartido;
    }

    public int getVotosTotais() {
        return this.votosTotais;
    }

    public int getNumeroPartido() {
        return numeroPartido;
    }

    public int getVotosNominais() {
        return votosNominais;
    }

    public int getVotosLegenda(){
        return votosLegenda;
    }

    @Override
    public int compareTo(Partido partido){
        int compCriterioI = Integer.compare(partido.getVotosTotais(), this.votosTotais);

        if(compCriterioI == 0){
            compCriterioI = Integer.compare(this.getNumeroPartido(), partido.getNumeroPartido());
        }

        return compCriterioI;

    }

     
}
