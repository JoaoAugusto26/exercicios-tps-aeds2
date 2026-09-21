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
 * Corta a quebra de linha que o fgets deixa no fim do vetor.
 * O taman conta ate o terminador e por isso incluiria a quebra; aqui a
 * busca para no primeiro '\n' ou '\r', e o terminador e gravado ali.
 * Sem isso a linha lida seria comparada com a quebra junto e nunca casaria
 * com -1 nem com FIM.
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
    Veiculo resp = l->primeiro->veic;

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

    Veiculo resp = l->ultimo->veic;
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
    Veiculo resp = alvo->veic;
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
        formatVeic(i->veic, saida);
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
 * Escreve a marca e o modelo de um registro que saiu da fila.
 * A saida esperada nao tem espaco entre o parentese e a marca.
 * @param v registro removido
 */
void mostrarRem(Veiculo v){
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
    int numVeic = 0;
    Veiculo* frota = lerCsv("/tmp/veiculos.csv", &numVeic);

    Lista lista;
    iniciarLista(&lista);

    char l[1024];

    while(fgets(l, 1024, stdin) != NULL){
        tirarQuebra(l);

        if(strcmp(l, "-1") == 0){
            break;
        }

        int pos = procurar(frota, numVeic, atoi(l));

        if(pos >= 0){
            inserirFim(&lista, frota[pos]);
        }
    }

    int numComandos = 0;

    if(fgets(l, 1024, stdin) != NULL){
        tirarQuebra(l);
        numComandos = atoi(l);
    }

    for(int c = 0; c < numComandos; c++){
        if(fgets(l, 1024, stdin) == NULL){
            break;
        }

        tirarQuebra(l);

        if(l[0] == 'I' && l[1] == 'I'){
            int id = 0;
            sscanf(l + 2, "%d", &id);
            int pos = procurar(frota, numVeic, id);

            if(pos >= 0){
                inserirInicio(&lista, frota[pos]);
            }
        } else if(l[0] == 'I' && l[1] == 'F'){
            int id = 0;
            sscanf(l + 2, "%d", &id);
            int pos = procurar(frota, numVeic, id);

            if(pos >= 0){
                inserirFim(&lista, frota[pos]);
            }
        } else if(l[0] == 'I' && l[1] == '*'){
            int posicao = 0;
            int id = 0;
            sscanf(l + 2, "%d %d", &posicao, &id);
            int pos = procurar(frota, numVeic, id);

            if(pos >= 0){
                inserir(&lista, frota[pos], posicao);
            }
        } else if(l[0] == 'R' && l[1] == 'I'){
            mostrarRem(removerInicio(&lista));
        } else if(l[0] == 'R' && l[1] == 'F'){
            mostrarRem(removerFim(&lista));
        } else if(l[0] == 'R' && l[1] == '*'){
            int posicao = 0;
            sscanf(l + 2, "%d", &posicao);
            mostrarRem(remover(&lista, posicao));
        }
    }

    mostrarLista(&lista);

    free(frota);
    return 0;
}
