package Dominio;
public enum Genero{
    
    MASCULINO(2),FEMININO(4);


    private int id;

    Genero(int id){
        this.id = id;
    }

    public int getIdGenero(){
        return id;
    }

    public static Genero generoCandidato(int codigo){
        
        for(Genero genero: values()){
            if(genero.id == codigo){
                return genero;
            }
        }
        throw new IllegalArgumentException("Código de gênero inválido: " + codigo);
    }
}