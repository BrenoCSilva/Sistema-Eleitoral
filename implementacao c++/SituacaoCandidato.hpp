#ifndef SITUACAO_CANDIDATO  
#define SITUACAO_CANDIDATO


enum class SituacaoCandidato : int{

    ELEITO_POR_QP = 2,
    ELEITOR_POR_MEDIA = 3,
    NAO_ELEITO = 4

};

SituacaoCandidato converteSituacao(int codigo);

#endif