## 📂 Organização do Projeto

O repositório está organizado da seguinte forma:

* **`src/`**: Contém o código-fonte Java organizado por pacotes (`Dominio`, `Entrada`, `Saida`).
* **`build.xml`**: Ficheiro de configuração do **Apache Ant**. É responsável por automatizar a compilação e a geração do ficheiro executável `.jar`.
* **`Relatorio.pdf`**: Relatório técnico detalhando a modelação OO, tratamento de exceções, descrição dos testes e diagramas.
* **`diagramaUML.png`**: Diagrama de classes UML que representa a arquitetura e os relacionamentos do sistema.
* **`casosverificados`**: são casos criados para estressar o programa (Ler seção 2 do relatório).

---

## 🚀 Como Executar 

Existem duas formas principais de validar e executar o projeto:

### 1. Utilizando o Script de Testes Automatizados

O script de testes verifica se as saídas do seu programa coincidem exatamente com as saídas de referência.

1.  Expanda o conteúdo do ficheiro zip (`testes-script-poo-trab1`).
2.  Coloque a pasta deste trabalho dentro diretório  `testes-script-poo-trab1`, ou seja onde está o `test.sh`.
3.  No terminal, execute:
    ```bash
    ./test.sh
    ```

O script inclui dados de municípios dos estados do **Acre (AC), Espírito Santo (ES) e Pernambuco (PE)**. O código é capaz de processar dados de qualquer município, desde que fornecidos os ficheiros CSV corretos.

### 2. Execução Manual (via Terminal)

O projeto utiliza o Ant para gerir o ciclo de vida da aplicação. Siga os passos abaixo:

1.  **Compilar o código:**
    ```bash
    ant compile
    ```
2.  **Gerar o ficheiro executável (.jar):**
    ```bash
    ant jar
    ```
3.  **Executar a aplicação:**
    ```bash
    java -jar vereadores.jar <codigo_municipio> <caminho_candidatos> <caminho_votacao> <data_eleicao>
    ```

#### 📍 Exemplo Prático (Rio Branco - AC)

Para analisar o município de Rio Branco (código 1392), utilizando os dados de exemplo:

```bash
java -jar vereadores.jar 1392 AC1392/in/candidatos.csv AC1392/in/votacao.csv 25/03/2026
```

## Requisitos para execução
 
Para compilar e executar este projeto é necessário instalar o **Java JDK** (Java Development Kit), que inclui a máquina virtual Java (JVM) e a ferramenta de build **Apache Ant**. Para executar os testes de script, é necessário utilizar o Java JDK 17 (versão de referência da disciplina).

Siga os passos abaixo de acordo com o seu sistema operacional.

---

## 🐧 Para utilizadores de Linux

### 1. Instalar e verificar o Java JDK 17
Abra o terminal e execute os seguintes comandos para atualizar os pacotes e instalar o JDK 17:

```bash
sudo apt update
sudo apt install openjdk-17-jdk -y
```
Para verificar a instalação, digite **java -version**, e para verificar o compilador digite **javac -version**.

### 2. Instalar e verificar o Apache Ant

```bash
sudo apt install ant -y
```
Verifique com **ant -version**.



