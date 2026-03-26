
## 📂 Organização do Projeto

O repositório está organizado de forma simplificada:

* **Ficheiros `.cpp` e `.hpp`**: Localizados na raiz do projeto, contêm toda a implementação das classes de domínio (`Candidato`, `Partido`, `Eleicao`), lógica de leitura (`Leitor`) e formatação de relatórios (`Relatorio`).
* **`Makefile`**: Ficheiro de configuração para o utilitário **Make**. Automatiza a compilação do código C++ e a geração do executável final.

---

## 🚀 Como Executar 

Existem duas formas principais de validar e executar o projeto:

### 1. Utilizando o Script de Testes Automatizados

O script de testes verifica se as saídas do seu programa coincidem exatamente com as saídas de referência.

1.  Expanda o conteúdo do ficheiro zip (`testes-script-poo-trab2`).
2.  Coloque a pasta deste trabalho num **subdiretório** a partir de onde está o ficheiro `test.sh`.
3.  No terminal, execute:
    ```bash
    ./test.sh
    ```

O script inclui dados de municípios dos estados do **Acre (AC), Espírito Santo (ES) e Pernambuco (PE)**. O código é capaz de processar dados de qualquer município, desde que fornecidos os ficheiros CSV corretos.

### 2. Execução Manual (via Terminal)

Diferente da versão Java, utilizamos o **Make** para compilar o binário nativo.

1.  **Compilar o código:**
    ```bash
    make
    ```
    *(Isso gerará o executável chamado `vereadores` na pasta atual)*

2.  **Executar a aplicação:**
    ```bash
    ./vereadores <codigo_municipio> <caminho_candidatos> <caminho_votacao> <data_eleicao>
    ```

#### 📍 Exemplo Prático (Rio Branco - AC)

Para analisar o município de Rio Branco (código 1392) com os dados da pasta de teste:
```bash
./vereadores 1392 AC1392/in/candidatos.csv AC1392/in/votacao.csv 25/03/2026

