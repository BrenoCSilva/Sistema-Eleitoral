package Dominio;
import java.time.LocalDate;
import java.util.HashMap;
import java.util.Map;

public class Eleicao {
    
    private Map<Integer, Candidato> candidatos = new HashMap<>();
    private Map<Integer, Partido> partidos = new HashMap<>();

    private int qtdCandidatosEleitos;
    private int qtdVotosNominais;
    private int qtdVotosLegenda;
    private int qtdMasculino;
    private int qtdFeminino;

    public Candidato criaCandidato(int codigo_municipio, int codigo_cargo, int numero_candidato, String nome_urna, int numero_federacao, LocalDate data_nascimento, boolean resultado_turno, Genero genero, Partido partido, LocalDate dataAtual){
        
        Candidato candidato = new Candidato(codigo_municipio, codigo_cargo, numero_candidato, nome_urna, numero_federacao, data_nascimento, resultado_turno, genero, partido, dataAtual );
        candidatos.put(numero_candidato, candidato);
        partido.adicionarCandidato(candidato);
        return candidato;
    }

    public Partido criaPartido(int numero_partido, String sigla_partido){
        
        Partido partido = this.partidos.get(numero_partido);
        
        if(partido == null){
            
           partido = new Partido(numero_partido, sigla_partido);
           partidos.put(numero_partido, partido);

        }

        return partido;
    }

    //                                                                getters
    
    public Map<Integer, Candidato> getCandidatos(){
        return new HashMap<>(candidatos);
    }

    public Candidato getCandidato(int numero_candidato){
        return  candidatos.get(numero_candidato);   
    }

    public Map<Integer, Partido> getPartidos(){
        return new HashMap<>(partidos);
    }

    public Partido getPartido(int numeroPartido){
        return  partidos.get(numeroPartido);   
    }

    public int getQtdVotosLegenda() {
        return qtdVotosLegenda;
    }

    public int getQtdVotosNominais() {
        return qtdVotosNominais;
    }

    public int getQtdCandidatosEleitos() {
        return qtdCandidatosEleitos;
    }

    public int getQtdFeminino() {
        return qtdFeminino;
    }

    public int getQtdMasculino() {
        return qtdMasculino;
    }

    //                                                                      incrementadores

    public void incrementarQtdVotosNominais(int votos){
        this.qtdVotosNominais+=votos;
    }

    public void incrementarQtdLegenda(int votos){
        this.qtdVotosLegenda+=votos;
    }

    public void incrementaQtdCandidatosEleitos(){
        this.qtdCandidatosEleitos++;
    }


    public void incrementrarQtdMasculino(){
        qtdMasculino++;
    }

    public void incrementrarQtdFeminino(){
        qtdFeminino++;
    }


}
