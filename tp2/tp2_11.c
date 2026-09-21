/**
 * Nome: Joao Augusto Moreira Cunha
 * Materia: AEDS II - PUC Minas
 * tp2_11 - C
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
 * Celula de uma lista simplesmente encadeada.
 * Guarda um registro e o endereco da proxima celula. A ultima aponta para
 * NULL, e e assim que o percurso sabe onde parar.
 */
typedef struct Celula {
    Veiculo veiculo;
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
    nova->veiculo = v;
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
 * Insere um registro logo depois da cabeca, isto e, na primeira posicao.
 * Diferente da lista sequencial, nada e deslocado: so dois ponteiros mudam.
 * Se a lista estava vazia, a nova celula tambem passa a ser a ultima.
 * @param l lista que recebe o registro
 * @param v registro a ser inserido
 */
void inserirInicio(Lista* l, Veiculo v){
    Celula* nova = novaCelula(v);
    nova->prox = l->primeiro->prox;
    l->primeiro->prox = nova;

    if(l->ultimo == l->primeiro){
        l->ultimo = nova;
    }
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
 * Insere um registro na posicao informada.
 * O percurso anda posicao passos a partir da cabeca e para na celula
 * anterior ao destino, porque numa lista encadeada so se insere depois de
 * uma celula conhecida.
 * @param l lista que recebe o registro
 * @param v registro a ser inserido
 * @param posicao posicao de destino, contada a partir de zero
 */
void inserir(Lista* l, Veiculo v, int posicao){
    Celula* i = l->primeiro;

    for(int j = 0; j < posicao; j++){
        i = i->prox;
    }

    Celula* nova = novaCelula(v);
    nova->prox = i->prox;
    i->prox = nova;

    if(nova->prox == NULL){
        l->ultimo = nova;
    }
}

/**
 * Remove e devolve o primeiro registro.
 * A cabeca antiga e liberada e a celula que guardava o primeiro registro
 * passa a ser a nova cabeca. Por isso o registro devolvido e lido dela.
 * @param l lista de onde sai o registro
 * @return o registro removido
 */
Veiculo removerInicio(Lista* l){
    Celula* antiga = l->primeiro;
    l->primeiro = l->primeiro->prox;
    Veiculo resp = l->primeiro->veiculo;

    free(antiga);

    return resp;
}

/**
 * Remove e devolve o ultimo registro.
 * Aqui o percurso e inevitavel: numa lista simplesmente encadeada nao ha
 * como voltar da ultima celula para a anterior, entao e preciso caminhar
 * desde a cabeca ate achar quem aponta para o fim.
 * @param l lista de onde sai o registro
 * @return o registro removido
 */
Veiculo removerFim(Lista* l){
    Celula* i = l->primeiro;

    while(i->prox != l->ultimo){
        i = i->prox;
    }

    Veiculo resp = l->ultimo->veiculo;
    free(l->ultimo);
    l->ultimo = i;
    l->ultimo->prox = NULL;

    return resp;
}

/**
 * Remove e devolve o registro da posicao informada.
 * O percurso para na celula anterior ao alvo, que e religada diretamente a
 * celula seguinte. Se o alvo era o ultimo, o ponteiro ultimo recua.
 * @param l lista de onde sai o registro
 * @param posicao posicao do registro, contada a partir de zero
 * @return o registro removido
 */
Veiculo remover(Lista* l, int posicao){
    Celula* i = l->primeiro;

    for(int j = 0; j < posicao; j++){
        i = i->prox;
    }

    Celula* alvo = i->prox;
    Veiculo resp = alvo->veiculo;
    i->prox = alvo->prox;

    if(i->prox == NULL){
        l->ultimo = i;
    }

    free(alvo);

    return resp;
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
        formatVeiculo(i->veiculo, saida);
        printf("%s\n", saida);
        i = i->prox;
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
 * Escreve a marca e o modelo de um registro que saiu da lista.
 * A saida esperada nao tem espaco entre o parentese e a marca.
 * @param v registro removido
 */
void mostrarRemovido(Veiculo v){
    printf("(R)%s %s\n", v.marca, v.modelo);
}

/**
 * Le o dataset e processa a entrada padrao em duas partes.
 * Na primeira, cada id vira um registro inserido no fim da lista; ela
 * termina na linha com -1.
 * Na segunda, a primeira linha diz quantos comandos virao, e cada comando
 * seguinte insere ou remove: II no inicio, IF no fim, I* na posicao
 * informada, RI do inicio, RF do fim e R* da posicao informada. No I* a
 * posicao vem antes do id.
 * Cada remocao escreve uma linha; no fim a lista inteira e mostrada.
 * @return 0 ao termino normal do programa
 */
int main(){
    int numVeiculos = 0;
    Veiculo* frota = lerCsv("/tmp/veiculos.csv", &numVeiculos);

    Lista lista;
    iniciarLista(&lista);

    char linha[1024];

    while(fgets(linha, 1024, stdin) != NULL){
        tirarQuebra(linha);

        if(strcmp(linha, "-1") == 0){
            break;
        }

        int pos = procurar(frota, numVeiculos, atoi(linha));

        if(pos >= 0){
            inserirFim(&lista, frota[pos]);
        }
    }

    int numComandos = 0;

    if(fgets(linha, 1024, stdin) != NULL){
        tirarQuebra(linha);
        numComandos = atoi(linha);
    }

    for(int c = 0; c < numComandos; c++){
        if(fgets(linha, 1024, stdin) == NULL){
            break;
        }

        tirarQuebra(linha);

        if(linha[0] == 'I' && linha[1] == 'I'){
            int id = 0;
            sscanf(linha + 2, "%d", &id);
            int pos = procurar(frota, numVeiculos, id);

            if(pos >= 0){
                inserirInicio(&lista, frota[pos]);
            }
        } else if(linha[0] == 'I' && linha[1] == 'F'){
            int id = 0;
            sscanf(linha + 2, "%d", &id);
            int pos = procurar(frota, numVeiculos, id);

            if(pos >= 0){
                inserirFim(&lista, frota[pos]);
            }
        } else if(linha[0] == 'I' && linha[1] == '*'){
            int posicao = 0;
            int id = 0;
            sscanf(linha + 2, "%d %d", &posicao, &id);
            int pos = procurar(frota, numVeiculos, id);

            if(pos >= 0){
                inserir(&lista, frota[pos], posicao);
            }
        } else if(linha[0] == 'R' && linha[1] == 'I'){
            mostrarRemovido(removerInicio(&lista));
        } else if(linha[0] == 'R' && linha[1] == 'F'){
            mostrarRemovido(removerFim(&lista));
        } else if(linha[0] == 'R' && linha[1] == '*'){
            int posicao = 0;
            sscanf(linha + 2, "%d", &posicao);
            mostrarRemovido(remover(&lista, posicao));
        }
    }

    mostrarLista(&lista);

    free(frota);
    return 0;
}
