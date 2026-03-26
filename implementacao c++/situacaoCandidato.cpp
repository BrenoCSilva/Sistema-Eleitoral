#include "SituacaoCandidato.hpp"

SituacaoCandidato converteSituacao(int codigo){

    if(codigo == 2){
        return SituacaoCandidato::ELEITO_POR_QP;
    }
    else if (codigo == 3){
        return SituacaoCandidato::ELEITOR_POR_MEDIA;
    }

    else{
        return SituacaoCandidato::NAO_ELEITO;
    }
}