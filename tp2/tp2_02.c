/**
 * Nome: Joao Augusto Moreira Cunha
 * Materia: AEDS II - PUC Minas
 * tp2_02 - C
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Estrutura para representar a data de registro de um veiculo.
 */
typedef struct {
    int ano;
    int mes;
    int dia;
} Data;

/**
 * Estrutura principal que armazena os atributos de um veiculo.
 * A matriz de combustivel armazena ate 10 tipos diferentes, gerenciados pelo
 * contador numCombustiveis.
 */
typedef struct {
    int id;
    char marca[100];
    char modelo[100];
    int ano;
    char categoria[100];
    char combustivel[10][50]; 
    int numCombustiveis;     
    int cilindros;
    double cilindrada;
    char transmissao[100];
    char tracao[100];
    double consumoCidade;
    double consumoEstrada;
    double co2;
    int turbo;
    Data dataRegistro;
} Veiculo;

/**
 * Calcula o numero de caracteres de uma string.
 * @param s String terminada em '\0'.
 * @return Quantidade de caracteres da string.
 */
int taman(char* s){
    int resp = 0;

    while(s[resp] != '\0'){
        resp++;
    }

    return resp;
}

/**
 * Copia o conteudo da string de origem para o vetor de destino.
 * @param destino Vetor que recebera a copia.
 * @param origem String a ser copiada.
 */
void copiar(char* destino, char* origem){
    int i = 0;

    while(origem[i] != '\0'){
        destino[i] = origem[i];
        i++;
    }

    destino[i] = '\0';
}

/**
 * Concatena a string de origem ao final da string de destino.
 * @param destino String que sera estendida.
 * @param origem String a ser anexada.
 */
void concatenar(char* destino, char* origem){
    int i = taman(destino);
    int j = 0;

    while(origem[j] != '\0'){
        destino[i] = origem[j];
        i++;
        j++;
    }

    destino[i] = '\0';
}

/**
 * Converte uma string no formato "AAAA-MM-DD" para a estrutura Data.
 * @param s String contendo a data.
 * @return Estrutura Data preenchida.
 */
Data parseData(char* s){
    Data d;
    sscanf(s, "%d-%d-%d", &d.ano, &d.mes, &d.dia);
    return d;
}

/**
 * Formata uma estrutura Data para o padrao "DD/MM/AAAA".
 * @param d Estrutura Data a ser formatada.
 * @param buffer Vetor de caracteres que recebera o resultado.
 */
void formatData(Data d, char* buffer){
    sprintf(buffer, "%02d/%02d/%04d", d.dia, d.mes, d.ano);
}

/**
 * Formata uma estrutura Data para o padrao "DD/MM/AAAA".
 * @param d Estrutura Data a ser formatada.
 * @param buffer Vetor de caracteres que recebera o resultado.
 */
void splitCsvLine(char* linha, char colunas[][200], int* numColunas){
    int col = 0;
    int pos = 0;
    for(int i = 0; linha[i] != '\0' && linha[i] != '\n' && linha[i] != '\r'; i++){
        if(linha[i] == ','){
            colunas[col][pos] = '\0';
            col++;
            pos = 0;
        } else {
            colunas[col][pos++] = linha[i];
        }
    }
    colunas[col][pos] = '\0';
    *numColunas = col + 1;
}

/**
 * Formata um numero real com ponto como separador decimal e zeros a esquerda, se necessario.
 * @param valor Numero de ponto flutuante a ser formatado.
 * @param casas Quantidade de casas decimais desejadas (1 ou 2).
 * @param buffer Vetor de caracteres que recebera o resultado.
 */
void formatDouble(double valor, int casas, char* buffer){
    long fator = 1;
    for(int i = 0; i < casas; i++){
        fator *= 10;
    }
    
    long total = (long)(valor * fator + 0.5);
    long parteInteira = total / fator;
    long parteDecimal = total % fator;
    
    if(casas == 1){
        sprintf(buffer, "%ld.%01ld", parteInteira, parteDecimal);
    } else if(casas == 2){
        sprintf(buffer, "%ld.%02ld", parteInteira, parteDecimal);
    }
}

/**
 * Instancia e preenche a estrutura Veiculo a partir de uma linha do arquivo CSV.
 * @param s Linha completa do arquivo.
 * @return Estrutura Veiculo com os dados mapeados.
 */
Veiculo parseVeiculo(char* s){
    Veiculo v;
    char colunas[20][200];
    int numColunas;
    
    splitCsvLine(s, colunas, &numColunas);

    v.id = atoi(colunas[0]);
    copiar(v.marca, colunas[1]);
    copiar(v.modelo, colunas[2]);
    v.ano = atoi(colunas[3]);
    copiar(v.categoria, colunas[4]);

    v.numCombustiveis = 0;
    char* pt = strtok(colunas[5], ";");
    while(pt != NULL){
        copiar(v.combustivel[v.numCombustiveis++], pt);
        pt = strtok(NULL, ";");
    }

    if(taman(colunas[6]) > 0){
        v.cilindros = atoi(colunas[6]);
    } else {
        v.cilindros = 0;
    }

    if(taman(colunas[7]) > 0){
        v.cilindrada = atof(colunas[7]);
    } else {
        v.cilindrada = 0.0;
    }

    copiar(v.transmissao, colunas[8]);
    copiar(v.tracao, colunas[9]);
    if(taman(colunas[10]) > 0){
        v.consumoCidade = atof(colunas[10]);
    } else {
        v.consumoCidade = 0.0;
    }

    if(taman(colunas[11]) > 0){
        v.consumoEstrada = atof(colunas[11]);
    } else {
        v.consumoEstrada = 0.0;
    }

    if(taman(colunas[12]) > 0){
        v.co2 = atof(colunas[12]);
    } else {
        v.co2 = 0.0;
    }

    
    if(strcmp(colunas[13], "true") == 0 || strcmp(colunas[13], "TRUE") == 0){
        v.turbo = 1;
    } else {
        v.turbo = 0;
    }

    v.dataRegistro = parseData(colunas[14]);

    return v;
}

/**
 * Gera a string formatada de saida com todos os dados do veiculo.
 * @param v Estrutura Veiculo a ser processada.
 * @param buffer Vetor de caracteres que armazenara a linha de saida final.
 */
void formatVeiculo(Veiculo v, char* buffer){
    char dataStr[30];
    formatData(v.dataRegistro, dataStr);

    char listaCombustivel[250] = "";
    for(int i = 0; i < v.numCombustiveis; i++){
        concatenar(listaCombustivel, v.combustivel[i]);
        if(i < v.numCombustiveis - 1){
            concatenar(listaCombustivel, ",");
        }
    }

    char* turboStr;

    if(v.turbo == 1){
        turboStr = "true";
    } else {
        turboStr = "false";
    }

    char ciliStr[30], cidStr[30], estStr[30], co2Str[30];
    formatDouble(v.cilindrada, 1, ciliStr);
    formatDouble(v.consumoCidade, 2, cidStr);
    formatDouble(v.consumoEstrada, 2, estStr);
    formatDouble(v.co2, 1, co2Str);

    sprintf(buffer, "[%d ## %s ## %s ## %d ## %s ## [%s] ## %d ## %s ## %s ## %s ## %s ## %s ## %s ## %s ## %s]",
            v.id, v.marca, v.modelo, v.ano, v.categoria, listaCombustivel,
            v.cilindros, ciliStr, v.transmissao, v.tracao, cidStr, estStr, co2Str,
            turboStr, dataStr);
}

/**
 * Carrega a base de dados do arquivo CSV para um vetor em memoria.
 * @param caminhoArquivo Caminho absoluto ou relativo do dataset.
 * @param n Ponteiro que armazenara o numero total de registros lidos.
 * @return Ponteiro para o vetor alocado dinamicamente com os veiculos.
 */
Veiculo* lerCsv(char* caminhoArquivo, int* n){
    FILE* file = fopen(caminhoArquivo, "r");
    if(file == NULL){
        *n = 0;
        return NULL;
    }

    Veiculo* vetor = (Veiculo*) malloc(50000 * sizeof(Veiculo));
    *n = 0;
    char linha[1024];

    fgets(linha, 1024, file);

    while(fgets(linha, 1024, file)){
        if(taman(linha) > 2){ 
            vetor[*n] = parseVeiculo(linha);
            (*n)++;
        }
    }
    
    fclose(file);
    return vetor;
}

/**
 * Fluxo de execucao principal: le o CSV, processa a entrada padrao e 
 * realiza pesquisas sequenciais por ID ate encontrar o marcador "-1".
 * @return 0 para execucao bem-sucedida.
 */
int main(){
    int numVeiculos = 0;
    Veiculo* frota = lerCsv("/tmp/veiculos.csv", &numVeiculos);
    
    char entrada[50];

    while(scanf("%49s", entrada) == 1 && strcmp(entrada, "-1") != 0){
        int idPesquisa = atoi(entrada);
        
        for(int i = 0; i < numVeiculos; i++){
            if(frota[i].id == idPesquisa){
                char saida[1024];
                formatVeiculo(frota[i], saida);
                printf("%s\n", saida);
                break;
            }
        }
    }
    
    free(frota);
    return 0;
}