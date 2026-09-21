/**
 * Nome: Joao Augusto Moreira Cunha
 * Materia: AEDS II - PUC Minas
 * tp2_06 - C
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct para a data de registro
typedef struct {
    int ano;
    int mes;
    int dia;
} Data;

// Struct principal do veiculo
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
 * Retorna o tamanho da string
 * @param s string terminada em '\0'
 * @return quantidade de caracteres antes do terminador
 */
int taman(char* s){
    int resp = 0;
    while(s[resp] != '\0'){
        resp++;
    }
    return resp;
}

/**
 * Copia a string de origem para o destino 
 * @param destino vetor que recebe a copia, com espaco suficiente
 * @param origem string a ser copiada
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
 * Concatena duas strings
 * @param destino string que sera estendida, com espaco suficiente
 * @param origem string a ser acrescentada
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
 * Converte uma string no formato AAAA-MM-DD em uma Data.
 * @param s trecho da linha do arquivo com a data
 * @return a Data correspondente
 */
Data parseData(char* s){
    Data d;
    sscanf(s, "%d-%d-%d", &d.ano, &d.mes, &d.dia);
    return d;
}

/**
 * Formata a data para o padrao DD/MM/AAAA
 * @param d data a ser formatada
 * @param buffer vetor que recebe o texto, com espaco suficiente
 */
void formatData(Data d, char* buffer){
    sprintf(buffer, "%02d/%02d/%04d", d.dia, d.mes, d.ano);
}

/**
 * Separa a linha do CSV pelas virgulas
 * @param l linha lida do arquivo
 * @param colunas matriz que recebe os campos separados
 * @param numColunas recebe a quantidade de campos encontrados
 */
void splitCsvLine(char* l, char colunas[][200], int* numColunas){
    int col = 0;
    int pos = 0;
    for(int i = 0; l[i] != '\0' && l[i] != '\n' && l[i] != '\r'; i++){
        if(l[i] == ','){
            colunas[col][pos] = '\0';
            col++;
            pos = 0;
        } else {
            colunas[col][pos++] = l[i];
        }
    }
    colunas[col][pos] = '\0';
    *numColunas = col + 1;
}

/**
 * Formata double com casas decimais e ponto
 * @param valor numero a ser formatado
 * @param casas quantidade de casas decimais, 1 ou 2
 * @param buffer vetor que recebe o texto, com espaco suficiente
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
 * Monta a struct Veiculo lendo os campos da linha do CSV
 * @param s linha lida do arquivo
 * @return o veiculo com os campos preenchidos
 */
Veiculo parseVeic(char* s){
    Veiculo v;
    char colunas[20][200];
    int numColunas;
    
    splitCsvLine(s, colunas, &numColunas);

    v.id = atoi(colunas[0]);
    copiar(v.marca, colunas[1]);
    copiar(v.modelo, colunas[2]);
    v.ano = atoi(colunas[3]);
    copiar(v.categoria, colunas[4]);

    // Separa os combustiveis por ponto e virgula
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
 * Prepara a string formatada do veiculo para printar
 * @param v veiculo a ser formatado
 * @param buffer vetor que recebe o texto, com espaco suficiente
 */
void formatVeic(Veiculo v, char* buffer){
    char dataStr[30];
    formatData(v.dataRegistro, dataStr);

    char listaComb[250] = "";
    for(int i = 0; i < v.numCombustiveis; i++){
        concatenar(listaComb, v.combustivel[i]);
        if(i < v.numCombustiveis - 1){
            concatenar(listaComb, ",");
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
            v.id, v.marca, v.modelo, v.ano, v.categoria, listaComb,
            v.cilindros, ciliStr, v.transmissao, v.tracao, cidStr, estStr, co2Str,
            turboStr, dataStr);
}

/**
 * Le o arquivo CSV inteiro e carrega o vetor
 * @param caminho caminho do arquivo do dataset
 * @param n recebe a quantidade de veiculos lidos
 * @return ponteiro para o vetor alocado, ou NULL se o arquivo nao abrir
 */
Veiculo* lerCsv(char* caminho, int* n){
    FILE* file = fopen(caminho, "r");
    if(file == NULL){
        *n = 0;
        return NULL;
    }

    Veiculo* vetor = (Veiculo*) malloc(50000 * sizeof(Veiculo));
    *n = 0;
    char l[1024];

    fgets(l, 1024, file);

    while(fgets(l, 1024, file)){
        if(taman(l) > 2){ 
            vetor[*n] = parseVeic(l);
            (*n)++;
        }
    }
    
    fclose(file);
    return vetor;
}

/**
 * Ordena o vetor olhando um unico digito do ano, usando Counting Sort.
 * O parametro exp diz qual digito observar: 1 para a unidade, 10 para a
 * dezena, 100 para a centena e assim por diante. A divisao por exp seguida
 * do resto por dez isola o digito desejado.
 * Como sao apenas dez digitos possiveis, a tabela de contagem tem tamanho
 * fixo. A contagem e guardada deslocada de uma posicao para que a soma
 * acumulada devolva direto o indice onde cada digito comeca.
 * Esta passada precisa ser estavel, senao o Radixsort nao funciona: a ordem
 * obtida pelos digitos anteriores seria perdida. Por isso a distribuicao
 * percorre do inicio ao fim, ocupando sempre a proxima posicao livre.
 * @param v vetor de veiculos a ser ordenado
 * @param n quantidade de veiculos no vetor
 * @param exp potencia de dez que seleciona o digito observado
 */
void countingSort(Veiculo* v, int n, int exp){
    int cont[11];

    for(int i = 0; i < 11; i++){
        cont[i] = 0;
    }

    for(int i = 0; i < n; i++){
        int digito = (v[i].ano / exp) % 10;
        cont[digito + 1]++;
    }

    for(int i = 1; i < 11; i++){
        cont[i] = cont[i] + cont[i - 1];
    }

    Veiculo* ordenado = (Veiculo*) malloc(n * sizeof(Veiculo));

    for(int i = 0; i < n; i++){
        int digito = (v[i].ano / exp) % 10;
        ordenado[cont[digito]] = v[i];
        cont[digito]++;
    }

    for(int i = 0; i < n; i++){
        v[i] = ordenado[i];
    }

    free(ordenado);
}

/**
 * Ordena o vetor pelo atributo ano usando o Radixsort.
 * Em vez de comparar os anos inteiros, o algoritmo ordena um digito por vez,
 * comecando pela unidade e terminando no digito mais significativo. Cada
 * passada usa o Counting Sort, que e estavel, entao a ordem conquistada nas
 * passadas anteriores e preservada. Ao terminar o ultimo digito, o vetor
 * esta ordenado pelo numero completo.
 * O maior ano determina quantas passadas sao necessarias: o laco avanca o
 * exp de dez em dez ate ultrapassar esse valor. Para anos de quatro digitos
 * sao quatro passadas.
 * @param v vetor de veiculos a ser ordenado
 * @param n quantidade de veiculos no vetor
 */
void radixSort(Veiculo* v, int n){
    int maior = 0;

    for(int i = 0; i < n; i++){
        if(v[i].ano > maior){
            maior = v[i].ano;
        }
    }

    for(int exp = 1; (maior / exp) > 0; exp = exp * 10){
        countingSort(v, n, exp);
    }
}

/**
 * Le o dataset, guarda em um vetor proprio os veiculos cujos ids aparecem
 * na entrada padrao, ordena esse vetor por ano e imprime o resultado.
 * @return 0 ao termino normal do programa
 */
int main(){
    int numVeic = 0;
    Veiculo* frota = lerCsv("/tmp/veiculos.csv", &numVeic);
    
    Veiculo* selec = (Veiculo*) malloc(50000 * sizeof(Veiculo));
    int numSelec = 0;

    char entrada[50];

    while(scanf("%49s", entrada) == 1 && strcmp(entrada, "-1") != 0){
        int idPesq = atoi(entrada);
        
        for(int i = 0; i < numVeic; i++){
            if(frota[i].id == idPesq){
                if(numSelec < 50000){
                    selec[numSelec] = frota[i];
                    numSelec++;
                }

                break;
            }
        }
    }
    
    radixSort(selec, numSelec);

    for(int i = 0; i < numSelec; i++){
        char saida[1024];
        formatVeic(selec[i], saida);
        printf("%s\n", saida);
    }
    
    free(selec);
    free(frota);
    return 0;
}