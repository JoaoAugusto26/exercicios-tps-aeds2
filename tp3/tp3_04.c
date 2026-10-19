/**
 * Nome: Joao Augusto Moreira Cunha
 * Materia: AEDS II - PUC Minas
 * tp3_04 - C
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
 * Converte letra maiuscula para minuscula
 * @param c caractere a converter
 * @return o caractere em minuscula, ou ele mesmo se nao for maiuscula
 */
char minusc(char c){
    char resp = c;

    if(c >= 'A' && c <= 'Z'){
        resp = c + ('a' - 'A');
    }

    return resp;
}

/**
 * Compara modelos ignorando diferenca de maiusculas e minusculas
 * O strcmp compara pelo codigo do caractere e colocaria CTS antes de
 * Cayman S, porque toda maiuscula vem antes de qualquer minuscula. A
 * saida esperada usa ordem alfabetica, sem essa separacao.
 * @param a primeiro modelo
 * @param b segundo modelo
 * @return negativo se a vem antes, positivo se vem depois, zero se iguais
 */
int compararModelo(char* a, char* b){
    int i = 0;
    int resp = 0;

    while(resp == 0 && (a[i] != '\0' || b[i] != '\0')){
        char ca = minusc(a[i]);
        char cb = minusc(b[i]);

        if(ca < cb){
            resp = -1;
        } else if(ca > cb){
            resp = 1;
        }

        i++;
    }

    return resp;
}

/**
 * Celula de uma lista simplesmente encadeada.
 * Guarda um registro e o endereco da proxima celula. A ultima aponta para
 * NULL, e e assim que o percurso sabe onde parar.
 */
typedef struct Celula {
    Veiculo veic;
    struct Celula* prox;
} Celula;

/**
 * Lista com alocacao flexivel.
 * O ponteiro primeiro aponta para uma celula cabeca, que nao guarda registro
 * util. Ela existe para que inserir e remover no inicio nao precisem de um
 * caso especial: sempre ha uma celula antes da primeira de verdade.
 * Com a lista vazia, primeiro e ultimo apontam para essa mesma cabeca.
 */
typedef struct {
    Celula* primeiro;
    Celula* ultimo;
} Lista;

/**
 * Aloca uma celula nova ja com o registro dentro.
 * @param v registro a ser guardado
 * @return endereco da celula criada
 */
Celula* novaCelula(Veiculo v){
    Celula* nova = (Celula*) malloc(sizeof(Celula));
    nova->veic = v;
    nova->prox = NULL;

    return nova;
}

/**
 * Deixa a lista vazia, criando a celula cabeca.
 * @param l lista a ser iniciada
 */
void iniciarLista(Lista* l){
    l->primeiro = (Celula*) malloc(sizeof(Celula));
    l->primeiro->prox = NULL;
    l->ultimo = l->primeiro;
}

/**
 * Insere um registro no fim da lista.
 * Como a lista guarda o endereco da ultima celula, nao e preciso percorrer
 * nada: basta pendurar a nova celula ali e atualizar o ultimo.
 * @param l lista que recebe o registro
 * @param v registro a ser inserido
 */
void inserirFim(Lista* l, Veiculo v){
    l->ultimo->prox = novaCelula(v);
    l->ultimo = l->ultimo->prox;
}

/**
 * Escreve os registros da lista, do primeiro ao ultimo.
 * O percurso comeca depois da cabeca e segue os ponteiros ate encontrar
 * NULL.
 * @param l lista a ser mostrada
 */
void mostrarLista(Lista* l){
    Celula* i = l->primeiro->prox;

    while(i != NULL){
        char saida[1024];
        formatVeic(i->veic, saida);
        printf("%s\n", saida);
        i = i->prox;
    }
}

/**
 * Ordena a lista pelo modelo com selecao. Para cada celula procura a de menor
 * modelo dali para frente e troca os registros das duas.
 * @param l lista a ser ordenada
 */
void selecao(Lista* l){
    Celula* i = l->primeiro->prox;

    while(i != NULL && i->prox != NULL){
        Celula* menor = i;
        Celula* j = i->prox;

        while(j != NULL){
            if(compararModelo(j->veic.modelo, menor->veic.modelo) < 0){
                menor = j;
            }

            j = j->prox;
        }

        Veiculo temp = i->veic;
        i->veic = menor->veic;
        menor->veic = temp;

        i = i->prox;
    }
}

/**
 * Libera todas as celulas da lista, inclusive a cabeca.
 * @param l lista a ser liberada
 */
void liberarLista(Lista* l){
    Celula* i = l->primeiro;

    while(i != NULL){
        Celula* prox = i->prox;
        free(i);
        i = prox;
    }
}

/**
 * Le os ids ate o -1, guarda os veiculos escolhidos na lista, ordena e
 * imprime.
 * @return 0 ao termino normal do programa
 */
int main(){
    int numVeic = 0;
    Veiculo* frota = lerCsv("/tmp/veiculos.csv", &numVeic);

    Lista lista;
    iniciarLista(&lista);

    char entrada[50];

    while(scanf("%49s", entrada) == 1 && strcmp(entrada, "-1") != 0){
        int idPesq = atoi(entrada);

        for(int i = 0; i < numVeic; i++){
            if(frota[i].id == idPesq){
                inserirFim(&lista, frota[i]);
                break;
            }
        }
    }

    selecao(&lista);
    mostrarLista(&lista);

    liberarLista(&lista);
    free(frota);
    return 0;
}
