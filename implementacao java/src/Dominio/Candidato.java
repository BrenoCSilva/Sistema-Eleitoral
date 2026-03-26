package Dominio;
import java.time.LocalDate;
import java.time.Period;


public class Candidato implements Comparable<Candidato>{

    private int codigoMunicipio;
    private int codigoCargo;
    private int numeroCandidato;
    private String nomeUrna;
    private int numeroFederacao;
    private LocalDate dataNascimento;
    private boolean resultadoTurno;
    private Genero genero;
    private int idade;
    private Partido partido;
    private int qtdVotosRecebidos;
    
    

    public Candidato(int codigoMunicipio, int codigoCargo, int numeroCandidato, String nomeUrna, int numeroFederacao, LocalDate dataNascimento, boolean resultadoTurno, Genero genero,  Partido partido, LocalDate dataAtual) {

        this.codigoMunicipio = codigoMunicipio;
        this.codigoCargo = codigoCargo;
        this.numeroCandidato = numeroCandidato;
        this.nomeUrna = nomeUrna;
        this.numeroFederacao = numeroFederacao;
        this.dataNascimento = dataNascimento;
        this.resultadoTurno = resultadoTurno;
        this.genero = genero;
        this.partido = partido;
        this.idade = calculaIdade(dataAtual);
       
    }
    
    public boolean getResultadoTurno() {
        return resultadoTurno;
    }
    public int getNumeroFederacao() {
        return numeroFederacao;
    }

    public Genero getGenero() {
        return genero;
    }

    public int getIdade() {
        return idade;
    }

    public int getQtdVotosRecebidos() {
        return qtdVotosRecebidos;
    }

    public LocalDate getDataNascimento() {
        return dataNascimento;
    }

    public String getNomeUrna() {
        return nomeUrna;
    }
    
    
    public int getNumeroCandidato() {
        return numeroCandidato;
    }
    
    
    public Partido getPartido() {
        return partido;
    }

    
    public int getQtdVotos(){
        return this.qtdVotosRecebidos;
    }

    
    public void incrementarVotos(int qtd){
        this.qtdVotosRecebidos += qtd;
        this.partido.atualizaAtributos(qtd, 0);
    }

    private int calculaIdade(LocalDate dataAtual)
    {   
     return Period.between(this.dataNascimento, dataAtual).getYears();
    }

    @Override
    public int compareTo(Candidato candidato){
        int compCriterioI = Integer.compare(candidato.getQtdVotos(), this.qtdVotosRecebidos);
        
        if(compCriterioI != 0){
            return compCriterioI;
        }

        return this.dataNascimento.compareTo(candidato.getDataNascimento());
    }
}
