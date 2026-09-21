/**
 * Nome: Joao Augusto Moreira Cunha
 * Materia: AEDS II - PUC Minas
 * tp2_10 - C
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Capacidade maxima da fila, fixada em cinco pelo enunciado. O vetor tem uma
   posicao a mais para que fila cheia e fila vazia nao fiquem indistinguiveis:
   com CAPACIDADE + 1 posicoes, vazia e primeiro igual a ultimo, e cheia e
   ultimo uma casa atras de primeiro. */
#define CAPACIDADE 5

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
 * Corta a quebra de linha que o fgets deixa no fim do vetor.
 * @param s linha lida pelo fgets, alterada no lugar
 */
void tirarQuebra(char* s){
    int i = 0;

    while(s[i] != '\0' && s[i] != '\n' && s[i] != '\r'){
        i++;
    }

    s[i] = '\0';
}

/**
 * Fila circular de veiculos com alocacao sequencial.
 * O indice primeiro aponta para quem sai primeiro e ultimo para a proxima
 * posicao livre. Os dois andam em circulo pelo vetor, voltando ao inicio
 * quando passam do fim, e e isso que evita deslocar os registros a cada
 * remocao.
 */
typedef struct {
    Veiculo array[CAPACIDADE + 1];
    int primeiro;
    int ultimo;
} Fila;

/**
 * Deixa a fila vazia, com os dois indices na posicao zero.
 * @param f fila a ser iniciada
 */
void iniciarFila(Fila* f){
    f->primeiro = 0;
    f->ultimo = 0;
}

/**
 * Indica se a fila esta vazia, o que acontece quando os dois indices
 * coincidem.
 * @param f fila a ser consultada
 * @return 1 se estiver vazia, 0 caso contrario
 */
int filaVazia(Fila* f){
    int resp = 0;

    if(f->primeiro == f->ultimo){
        resp = 1;
    }

    return resp;
}

/**
 * Indica se a fila esta cheia, o que acontece quando ultimo esta uma casa
 * atras de primeiro. E por causa desse teste que o vetor tem uma posicao
 * sobrando: sem ela, cheia e vazia dariam a mesma condicao.
 * @param f fila a ser consultada
 * @return 1 se estiver cheia, 0 caso contrario
 */
int filaCheia(Fila* f){
    int resp = 0;

    if(((f->ultimo + 1) % (CAPACIDADE + 1)) == f->primeiro){
        resp = 1;
    }

    return resp;
}

/**
 * Insere um registro no fim da fila e avanca o indice ultimo em circulo.
 * @param f fila que recebe o registro
 * @param v registro a ser enfileirado
 */
void enfileirar(Fila* f, Veiculo v){
    f->array[f->ultimo] = v;
    f->ultimo = (f->ultimo + 1) % (CAPACIDADE + 1);
}

/**
 * Remove e devolve o registro do inicio da fila, avancando o indice primeiro
 * em circulo. Nada e deslocado: so o indice muda.
 * @param f fila de onde sai o registro
 * @return o registro removido
 */
Veiculo desenfileirar(Fila* f){
    Veiculo resp = f->array[f->primeiro];
    f->primeiro = (f->primeiro + 1) % (CAPACIDADE + 1);

    return resp;
}

/**
 * Escreve os registros da fila, do primeiro ao ultimo.
 * O percurso anda em circulo a partir de primeiro e para ao alcancar
 * ultimo, e nao com um for simples, porque os elementos podem estar
 * dando a volta no vetor.
 * @param f fila a ser mostrada
 */
void mostrarFila(Fila* f){
    int i = f->primeiro;

    while(i != f->ultimo){
        char saida[1024];
        formatVeiculo(f->array[i], saida);
        printf("%s\n", saida);
        i = (i + 1) % (CAPACIDADE + 1);
    }
}

/**
 * Localiza um veiculo do dataset pelo id, com pesquisa sequencial.
 * @param frota vetor com todos os veiculos lidos do arquivo
 * @param n quantidade de veiculos no vetor
 * @param id identificador procurado
 * @return a posicao do veiculo no vetor, ou -1 se nao existir
 */
int procurar(Veiculo* frota, int n, int id){
    int resp = -1;

    for(int i = 0; i < n; i++){
        if(frota[i].id == id){
            resp = i;
            break;
        }
    }

    return resp;
}

/**
 * Escreve a marca e o modelo de um registro que saiu da fila.
 * A saida esperada nao tem espaco entre o parentese e a marca.
 * @param v registro removido
 */
void mostrarRemovido(Veiculo v){
    printf("(R)%s %s\n", v.marca, v.modelo);
}

/**
 * Le o dataset e processa a entrada padrao em duas partes.
 * Na primeira, cada id e enfileirado; ela termina na linha com -1.
 * Na segunda, a primeira linha diz quantos comandos virao, e cada comando e
 * I seguido de um id para enfileirar, ou R sozinho para desenfileirar.
 * Como manda o enunciado, quando a fila esta cheia e chega uma insercao, uma
 * remocao acontece antes de abrir espaco, e essa remocao tambem e mostrada.
 * Cada registro que sai gera uma linha; no fim a fila inteira e mostrada.
 * @return 0 ao termino normal do programa
 */
int main(){
    int numVeiculos = 0;
    Veiculo* frota = lerCsv("/tmp/veiculos.csv", &numVeiculos);

    Fila fila;
    iniciarFila(&fila);

    char linha[1024];

    while(fgets(linha, 1024, stdin) != NULL){
        tirarQuebra(linha);

        if(strcmp(linha, "-1") == 0){
            break;
        }

        int pos = procurar(frota, numVeiculos, atoi(linha));

        if(pos >= 0){
            if(filaCheia(&fila) == 1){
                mostrarRemovido(desenfileirar(&fila));
            }

            enfileirar(&fila, frota[pos]);
        }
    }

    int numComandos = 0;

    if(fgets(linha, 1024, stdin) != NULL){
        tirarQuebra(linha);
        numComandos = atoi(linha);
    }

    for(int i = 0; i < numComandos; i++){
        if(fgets(linha, 1024, stdin) == NULL){
            break;
        }

        tirarQuebra(linha);

        if(linha[0] == 'I'){
            /* o atoi pula o espaco sozinho, entao basta comecar depois do I */
            int pos = procurar(frota, numVeiculos, atoi(linha + 1));

            if(pos >= 0){
                if(filaCheia(&fila) == 1){
                    mostrarRemovido(desenfileirar(&fila));
                }

                enfileirar(&fila, frota[pos]);
            }
        } else if(linha[0] == 'R'){
            if(filaVazia(&fila) == 0){
                mostrarRemovido(desenfileirar(&fila));
            }
        }
    }

    mostrarFila(&fila);

    free(frota);
    return 0;
}
